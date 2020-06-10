#include "Animator.h"
#include "scene_node.h"
Cell::AnimationState::AnimationState(State _state, double _startTime, const AnimationClipPtr _clip)
	:state(_state),startTime(_startTime),clip(_clip)
{
	secPerTick = 1.0 / clip->GetTicksPerSecond();
}

Cell::AnimationState::~AnimationState()
{

}

void Cell::AnimationState::Tick(double time, uint64_t frameIdx)
{
	if (state == State::_PAUSING_ || state == State::_STOPING_)
		return;
	if (clip)
	{
		//normalize time
		time -= startTime;
		float normalizeTime = 0.0;
		if (lastUpdateTick < 1e-5 || (time - lastUpdateSec) >= secPerTick) 
		{
			lastUpdateTick += 1.0;
			lastUpdateSec = time;
		}

		if (lastUpdateTick > clip->GetDuration()) {
			if (state == State::_PLAYING_) {
				state = State::_STOPING_;
			}
			else {
				if (clip->GetDuration ()> 0)
					lastUpdateTick = fmod(lastUpdateTick, clip->GetDuration());
			}
		}


		clip->Evaluate(lastUpdateTick);
	}
}
