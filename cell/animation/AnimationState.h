#ifndef ANIMATIONSTATE_H_INCLUDED
#define ANIMATIONSTATE_H_INCLUDED
#include "AnimationClip.h"

namespace Cell
{
	using TransformMap = std::map<std::string, math::mat4f>;
	using BlendShapeWeightMap = std::map<unsigned int, float>;
	class SceneNode;
	class AnimationState
	{

	public:
		enum class State
		{
			_STOPING_,
			_PAUSING_,
			_PLAYING_,
			_LOOPING_
		};

		AnimationState() = default;

		AnimationState(State _state, double _startTime, const AnimationClipPtr _clip);

		~AnimationState();

		virtual void Tick(double, uint64_t);

		const TransformMap& GetTransformMap() { return clip->GetTransformations(); }

		const BlendShapeWeightMap& GetBSWeightMap() { return clip->GetMorphAnimWeights(); }

	public:
		State state;

		double startTime = 0.0;

		const AnimationClipPtr clip = nullptr;

		double lastUpdateSec = 0.0;
		double lastUpdateTick = 0.0;
		double secPerTick = 0.0;
		
	};

	using AnimationStatePtr = std::shared_ptr<AnimationState>;
}
#endif