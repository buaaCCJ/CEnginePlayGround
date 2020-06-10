#include "SkinningMeshRender.h"
#include "scene/scene_node.h"
#include "Animator.h"
namespace Cell
{
	void SkinningMeshRender::TickComponent(double time, uint64_t frameIdx)
	{
		if (mCurrentBoneNodeDic.size() == mBoneOffsetMat.size())
			return;
		auto root = GetSceneNode()->GetRoot();
		for (auto & bone : mBoneOffsetMat)
		{
			auto sn = root->Find(bone.first);
			if (!sn)
			{
				std::cout << "can not find this sceneNode, something wrong!" << std::endl;
				continue;
			}
			mCurrentBoneNodeDic[bone.first] = sn;
		}
	}
	void SkinningMeshRender::SetMesh(Mesh * _mesh, math::vec3f _min, math::vec3f _max)
	{
		MeshRender::SetMesh(_mesh, _min, _max);
		for (auto & bone : _mesh->mBones)
		{
			mBoneOffsetMat[bone.mName] = bone.mOffsetMatrix;
		}
	}
	const std::vector<float>& SkinningMeshRender::GetSkinningMat()
	{
		std::vector<float>data;
		std::vector<math::mat4f> mTransforms;
		math::mat4f globalInverseMeshTransform = GetSceneNode()->GetGlobalTransform();
		globalInverseMeshTransform = globalInverseMeshTransform.inverse();
		for (int a = 0; a < mesh->mBones.size(); ++a)
		{
			auto sn = mCurrentBoneNodeDic.find(mesh->mBones[a].mName);
			
			if (sn != mCurrentBoneNodeDic.end())
			{
				auto mat = globalInverseMeshTransform * sn->second->GetGlobalTransform()*mesh->mBones[a].mOffsetMatrix;
				mTransforms.push_back(mat);
			}
			else
			{
				std::cout << "something wrong! can not find this node" << mesh->mBones[a].mName << std::endl;
				break;
			}
			
		}
		mTransfromData.resize(mTransforms.size() * 12, 0.0f);
		float* dataptr = mTransfromData.data();
		for (int i = 0; i < mTransforms.size(); i++)
		{
			auto transposed = mTransforms[i].transpose();
			memcpy(dataptr + i * 12, transposed.data, 12 * sizeof(float));
		}
		return mTransfromData;
	}
}