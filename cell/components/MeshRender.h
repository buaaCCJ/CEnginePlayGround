#ifndef MESHRENDER_H
#define MESHRENDER_H
#include <memory>
#include "mesh/mesh.h" 
#include "shading/material.h"
#include <Eigen/Eigen>
#include "components/Component.h"
#include <assimp/scene.h>

namespace Cell
{
	class MeshRender:public Component
	{
	public:
		MeshRender() = default;
		MeshRender(SceneNode* node) :Component(node) { doTick = true; }
		~MeshRender() {}

		//component
		 virtual void SetMesh(Mesh* _mesh, math::vec3f _min=math::vec3f(-9999), math::vec3f _max = math::vec3f(9999)) { mesh = _mesh; BoxMax = _max; BoxMin = _min; }

		void SetMaterial(Material* _mat) { material = _mat; }

		void SetBoundingBox(math::vec3f _min = math::vec3f(-9999), math::vec3f _max = math::vec3f(9999)) { BoxMin = _min; BoxMax = _max; }

		math::vec3f GetBoundingBoxMin() { return BoxMin; }

		math::vec3f GetBoundingBoxMax() { return BoxMax; }

		Material* GetMaterial() { return material; }

		Mesh* GetMesh() { return mesh; }

		void CollectBlendShapeData(aiMesh* mesh, std::vector<math::vec3f> vertices, std::vector<math::vec3f> normals);

		bool HasBlendShape() { return isHaveBlendShape; }

		void SetBlendShapeWeight(const std::map<unsigned int, float>& weightMap);

		void ApplyVertAnim(bool bNeedUpdateNormal = true);

		struct BlendShape
		{
			//vertices.col(0)is origin vertex, others are the differences between the blendshape and the original model
			Eigen::MatrixXf vertices;
			Eigen::MatrixXf normals;
			Eigen::MatrixXi faces;
			std::vector<std::string> names;
			//contains orgin mesh, so num=real blendshape num+1
			int num;
			BlendShape() :num(0) {}
		};
		static ClassIDType GetClassID()
		{
			return ClassID(MeshRender);
		}
	protected:
		virtual void TickComponent(double time, uint64_t frameIdx) { if (HasBlendShape())ApplyVertAnim(); }

		Mesh* mesh=nullptr;
		Material* material=nullptr;

		// bounding box 
		math::vec3f BoxMin = math::vec3f(-99999.0f);
		math::vec3f BoxMax = math::vec3f(99999.0f);

		bool isHaveBlendShape = false;

		BlendShape mCurrentBSData;

		Eigen::VectorXf mCurrentWeight;
	};
	using MeshRenderPtr = std::shared_ptr<MeshRender>();
}

#endif