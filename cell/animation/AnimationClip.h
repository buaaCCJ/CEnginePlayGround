#ifndef ANIMATIONCLIP_H_INCLUDED
#define ANIMATIONCLIP_H_INCLUDED
#include <memory>
#include "assimp/anim.h"
#include <map>
#include "Animation.h"

namespace Cell
{
	class AnimationClip
	{
	public:
		AnimationClip(const aiAnimation* scene);

		~AnimationClip();

		void Evaluate(double pTime);

		const std::map<std::string, math::mat4f>& GetTransformations() const
		{
			return mTransforms;
		}

		const std::map<unsigned int, float>& GetMorphAnimWeights() const { return mBlendShapeWeights; }

		const float GetDuration()const
		{
			return mAnim->mDuration;
		}
		const float GetLength() const
		{
			return mAnim->mLength;
		}

		const double GetTicksPerSecond()const
		{
			return mAnim->mTicksPerSecond;
		}
		
	public:
		double mFrameSec;

		double mFramePerSec;

	private:

		AnimationPtr mAnim;


		/** The array to store the transformations results of the evaluation */
		std::map<std::string, math::mat4f> mTransforms;

		/** The array to store the blendshape weights of the evaluation */
		std::map<unsigned int, float> mBlendShapeWeights;
	};

	using AnimationClipPtr = std::shared_ptr<AnimationClip>;
}
#endif