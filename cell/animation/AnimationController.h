#ifndef ANIMATIONCONTROLLER_H_INCLUDED
#define ANIMATIONCONTROLLER_H_INCLUDED
#include <memory>
#include "AnimationState.h"
#include <vector>

namespace Cell
{
	class AnimationController
	{
	public:
		AnimationController() {}
		~AnimationController() {}

	public:

		bool Tick(double time, uint64_t frameIdx);

		bool AddAnimationClip(AnimationClipPtr clip);

		void PlayAnimation(const std::string animPath, double start_time, bool loop = true);

		void PlayAnimation(const int id, double start_time, bool loop = true);

		void StopAnimation(const std::string animPath);

		const AnimationClipPtr GetAnimationClip(const std::string animPath);

	public:
		AnimationStatePtr m_curAnimState;
	private:

		

		std::vector<AnimationClipPtr> animationClipList;
	};
	using AnimationControllerPtr = std::shared_ptr<AnimationController>;
}
#endif