#include "MeshRender.h"
namespace Cell {
	void MeshRender::CollectBlendShapeData(aiMesh * aimesh, std::vector<math::vec3f> base_vertices, std::vector<math::vec3f> base_normals)
	{
		if (!aimesh)return;
		if (aimesh->mNumAnimMeshes > 0)
		{
			isHaveBlendShape = true;
		}
		else
			return;

		std::vector<std::string> names;
		Eigen::MatrixXf vertices;
		Eigen::MatrixXf normals;

		names.resize(aimesh->mNumAnimMeshes);
		const int row_num = base_vertices.size() * 3;
		// init vertices size. first column is base vertex.
		vertices = Eigen::MatrixXf::Zero(row_num, aimesh->mNumAnimMeshes + 1);
		normals = Eigen::MatrixXf::Zero(row_num, aimesh->mNumAnimMeshes + 1);

		// traverse and check name.
		for (int j = 0; j < base_vertices.size(); ++j)
		{
			vertices.block(j * 3, 0, 3, 1) = Eigen::Map<const Eigen::Vector3f>(base_vertices[j]);
			normals.block(j * 3, 0, 3, 1) = Eigen::Map<const Eigen::Vector3f>(base_normals[j]);
		}

		for (int j = 0; j < aimesh->mNumAnimMeshes; ++j)
		{
			const aiAnimMesh* pAnimMesh = aimesh->mAnimMeshes[j];
			names[j] = aimesh->mAnimMeshes[j]->mName.C_Str();

			if (pAnimMesh->mNumVertices != base_vertices.size())
			{
				std::cerr << "pAnimmesh's vertices num != base_vertices: " << pAnimMesh->mNumVertices << " " << base_vertices.size() << std::endl;
				return;
			}
			else
			{
				vertices.col(j + 1) = Eigen::Map<Eigen::VectorXf>(&pAnimMesh->mVertices[0][0], row_num);
				vertices.col(j + 1) -= vertices.col(0);

				normals.col(j + 1) = Eigen::Map<Eigen::VectorXf>(&pAnimMesh->mNormals[0][0], row_num);
				normals.col(j + 1) -= normals.col(0);
			}
		}
		mCurrentBSData.names = names;
		mCurrentBSData.normals = normals;
		mCurrentBSData.vertices = vertices;
		mCurrentBSData.num = aimesh->mNumAnimMeshes + 1;
		mCurrentWeight = Eigen::VectorXf::Zero(mCurrentBSData.num);
		mCurrentWeight[0] = 1;
	}
	void MeshRender::SetBlendShapeWeight(const std::map<unsigned int, float>& weightMap)
	{
		if (!HasBlendShape())return;
		for (auto & iter : weightMap)
		{
			mCurrentWeight[iter.first + 1] = iter.second;
		}
		//first col is always origin vertices, so the weight must be 1
		mCurrentWeight[0] = 1;
	}
	void MeshRender::ApplyVertAnim(bool bNeedUpdateNormal)
	{
		if (!HasBlendShape())return;

		Eigen::VectorXf vertices;
		Eigen::VectorXf normals;
		vertices = mCurrentBSData.vertices * mCurrentWeight;
		normals = mCurrentBSData.normals * mCurrentWeight;

		std::vector<math::vec3f> & pos = mesh->GetPosition();
		std::vector<math::vec3f> & base_normal = mesh->GetNormal();

		if (pos.size() != vertices.size() / 3)
		{
			std::cerr << "blendshape update vertex num: " << vertices.size() << " != origin vertex size: " << pos.size() << std::endl;
			return;
		}
		else
		{
			memcpy(pos.data(), &vertices[0], 3 * pos.size() * sizeof(float));
			memcpy(base_normal.data(), &normals[0], 3 * pos.size() * sizeof(float));
		}

		//update to VBO
		mesh->UpdateVertAndNormalSubData();
	}
}