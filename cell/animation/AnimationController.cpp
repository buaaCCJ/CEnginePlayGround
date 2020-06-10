#include "Animator.h"
#include <iostream>
bool Cell::AnimationController::Tick(double time, uint64_t frameIdx)
{
	if (m_curAnimState.get())
	{
		m_curAnimState->Tick(time, frameIdx);
		return true;
	}
	return false;
}

bool Cell::AnimationController::AddAnimationClip(AnimationClipPtr clip)
{
	animationClipList.emplace_back(clip);
	return true;
}

void Cell::AnimationController::PlayAnimation(const int id, double start_time, bool loop)
{
	auto anim = animationClipList[id];
	if (anim)
	{
		m_curAnimState.reset(new AnimationState(loop ? AnimationState::State::_LOOPING_ : AnimationState::State::_PLAYING_, start_time, anim));
	}
	else
	{
		std::cout << "can not find this animation by id: " << id << std::endl;
	}
}
