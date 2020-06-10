#ifndef COMPONENTtt_H
#define COMPONENTtt_H
#include "stdint.h"
namespace Cell
{
#define ClassID(x)                CLASS_##x
#define	DefineClassID(x,classID)  ClassID(x) = classID,

	enum ClassIDType {
		DefineClassID(Undefined, -1)
		DefineClassID(Component, 0)
		DefineClassID(Animator, 1)
		DefineClassID(MeshRender, 2)
		DefineClassID(SkinningMeshRender, 3)

	};

	class SceneNode;
	class Component
	{
	public:
		Component(SceneNode* _sn) :rootNode(_sn) {}
		virtual ~Component() {}

		SceneNode* GetSceneNode() { return rootNode; }

		static ClassIDType GetClassID()
		{
			return ClassID(Component);
		}

		virtual void OnTick(double time, uint64_t frameIndex)
		{
			if (enabled && doTick) TickComponent(time, frameIndex);
		}

	protected:
		virtual void TickComponent(double time, uint64_t frameIdx) { std::cout << "update component" << std::endl; }


	public:
		SceneNode* rootNode;
		bool enabled = true;

		bool doTick = false;

	};
}
#endif