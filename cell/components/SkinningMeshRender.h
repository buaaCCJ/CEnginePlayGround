#ifndef SKINNINGMESHRENDER_H
#define SKINNINGMESHRENDER_H
#include "components/MeshRender.h"
#include <map>
#include <assimp/scene.h>

namespace Cell
{
	class SceneNode;
	class SkinningMeshRender:public MeshRender
	{
	public:
		SkinningMeshRender(SceneNode* node) :MeshRender(node) {}

		virtual void TickComponent(double time, uint64_t frameIdx);

		virtual void SetMesh(Mesh* _mesh, math::vec3f _min = math::vec3f(-9999), math::vec3f _max = math::vec3f(9999));

		const std::vector<float>& GetSkinningMat();

	

		static ClassIDType GetClassID()
		{
			return ClassID(SkinningMeshRender);
		}
	public: 
		
		std::map<std::string, SceneNode*> mCurrentBoneNodeDic;

		//bones that belongs to this smr
		std::map<std::string, math::mat4f> mBoneOffsetMat;

		std::vector<float> mTransfromData;

	};
}

#endif