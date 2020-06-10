#ifndef ANIMATOR_H_INCLUDED
#define ANIMATOR_H_INCLUDED
#include <string>
#include "AnimationController.h"
#include "components/Component.h"
#include <vector>
namespace Cell
{
	class Animator:public Component
	{
	public:
		
		Animator(SceneNode* node) :Component(node) { doTick = true; }

		~Animator();

		void TickComponent(double time, uint64_t frameIndex);

		//void PlayAnimation(const std::string& path, double start_time, bool loop = true);

		void PlayAnimation(const int id, double start_time, bool loop = true);

		//void StopAnimation(const std::string& path);

		bool AddAnimationClip(AnimationClipPtr clip);

		void UpdateSceneNodeTransform(SceneNode* node, const TransformMap& transform);

		void UpdateSceneNodeBSWeight(SceneNode* node, const BlendShapeWeightMap& bsMap);

		const std::vector<float>& GetSkinningMat(SceneNode* node);

		static ClassIDType GetClassID()
		{
			return ClassID(Animator);
		}
	public:
	private:
		AnimationControllerPtr controller;

		std::vector<float> mTransfromData;
	};
	using AnimatorPtr = std::shared_ptr<Animator>;
}
#endif