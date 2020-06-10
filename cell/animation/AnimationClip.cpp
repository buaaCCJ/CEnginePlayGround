#include "AnimationClip.h"
#include <math/cmath.h>
#include <set>
#include <unordered_map>
#include "Animation.h"
#include <iostream>

Cell::AnimationClip::AnimationClip(const aiAnimation * anim)
{
	mFramePerSec = anim->mTicksPerSecond > DBL_EPSILON ? anim->mTicksPerSecond : 25.0;
	mFrameSec = 1.0 / mFramePerSec;

	mAnim.reset(new Animation);
	mAnim->mDuration = anim->mDuration;
	mAnim->mName = anim->mName.C_Str();
	mAnim->mTicksPerSecond = anim->mTicksPerSecond;
	mAnim->mLength = mAnim->mDuration / mAnim->mTicksPerSecond;

	for (int cid = 0; cid < anim->mNumChannels; ++cid) {
		auto channel = anim->mChannels[cid];
		if (channel) {
			NodeAnimPtr node_anim(new NodeAnim());
			node_anim->NodeName = channel->mNodeName.C_Str();

			if (channel->mPositionKeys) {
				node_anim->mNumPositionKeys = channel->mNumPositionKeys;
				node_anim->mNumRotationKeys = channel->mNumRotationKeys;
				node_anim->mNumScalingKeys = channel->mNumScalingKeys;

				node_anim->mPositionKeys.resize(channel->mNumPositionKeys);
				for (int pid = 0; pid < channel->mNumPositionKeys; ++pid) {
					const auto& key = channel->mPositionKeys[pid];
					node_anim->mPositionKeys[pid].mTime = key.mTime;
					node_anim->mPositionKeys[pid].mValue = math::vec3f(key.mValue.x, key.mValue.y, key.mValue.z);
				}
			}
			node_anim->mScalingKeys.resize(channel->mNumScalingKeys);
			if (channel->mScalingKeys) {
				for (int sid = 0; sid < channel->mNumScalingKeys; ++sid) {
					const auto& key = channel->mScalingKeys[sid];
					node_anim->mScalingKeys[sid].mTime = key.mTime;
					node_anim->mScalingKeys[sid].mValue=math::vec3f(key.mValue.x, key.mValue.y, key.mValue.z);
				}
			}
			node_anim->mRotationKeys.resize(channel->mNumRotationKeys);
			if (channel->mRotationKeys) {
				for (int rid = 0; rid < channel->mNumRotationKeys; ++rid) {
					const auto& key = channel->mRotationKeys[rid];
					
					node_anim->mRotationKeys[rid].mTime = key.mTime;
					node_anim->mRotationKeys[rid].mValue = key.mValue;
				}
			}
			mAnim->mChannels.emplace_back(node_anim);
		}
	}

	for (int cid = 0; cid < anim->mNumMorphMeshChannels; ++cid) {
		auto channel = anim->mMorphMeshChannels[cid];
		if (channel) {
			MeshMorphAnimPtr morph_anim(new MeshMorphAnim);
		
			if (channel->mKeys) {
				morph_anim->mKeys.resize(channel->mNumKeys);
				morph_anim->mName = channel->mName.C_Str();
				morph_anim->mNumKeys = channel->mNumKeys;
				for (int kid = 0; kid < channel->mNumKeys; ++kid) 
				{
					const auto& key = channel->mKeys[kid];
					morph_anim->mKeys[kid].mTime = key.mTime;
					morph_anim->mKeys[kid].mNumValuesAndWeights = key.mNumValuesAndWeights;
					morph_anim->mKeys[kid].mValues.resize(key.mNumValuesAndWeights);
					morph_anim->mKeys[kid].mWeights.resize(key.mNumValuesAndWeights);

					for (int a = 0; a < key.mNumValuesAndWeights; a++)
					{
						morph_anim->mKeys[kid].mValues[a] = key.mValues[a];
						morph_anim->mKeys[kid].mWeights[a] = key.mWeights[a];

						std::cout << "key: " << kid << " idx: " << a << " values: " << morph_anim->mKeys[kid].mValues[a] << " weights:" << key.mWeights[a] << std::endl;


					}
					//memcpy(morph_anim->mKeys[kid].mValues.data(), key.mValues, key.mNumValuesAndWeights*sizeof(unsigned int ));
				//	memcpy(morph_anim->mKeys[kid].mWeights.data(), key.mWeights, key.mNumValuesAndWeights* sizeof(double));
				}
			}
			mAnim->mMorphMeshChannels.emplace_back(morph_anim);
		}
	}
}

Cell::AnimationClip::~AnimationClip()
{
}

void Cell::AnimationClip::Evaluate(double pTime)
{
	auto time = pTime;
	for (unsigned int a = 0; a < mAnim->mChannels.size(); a++)
	{
		auto & channel = mAnim->mChannels[a];

		//position
		math::vec3f  presentPosition(0, 0, 0);
		if (channel->mNumPositionKeys > 0)
		{
			//find present frame num
			unsigned int frame = 0;
			while (frame < channel->mNumPositionKeys - 1)
			{
				if (time < channel->mPositionKeys[frame + 1].mTime)
					break;
				frame++;
			}

			// interpolate between this frame's value and next frame's value
			unsigned int nextFrame = (frame + 1) % channel->mNumPositionKeys;

			auto & key = channel->mPositionKeys[frame];
			auto & nextKey = channel->mPositionKeys[nextFrame];

			double diffTime = nextKey.mTime - key.mTime;
			if (diffTime < DBL_EPSILON)
				diffTime += mAnim->mDuration;

			if (diffTime > DBL_EPSILON)
			{
				float factor = float((time - key.mTime) / diffTime);
				presentPosition = key.mValue + (nextKey.mValue - key.mValue) * factor;
			}
			else
			{
				presentPosition = key.mValue;
			}
		}
		// rotation
		aiQuaternion presentRotation(1, 0, 0, 0);
		if (channel->mNumRotationKeys > 0)
		{
			unsigned int frame = 0;
			while (frame < channel->mNumRotationKeys - 1)
			{
				if (time < channel->mRotationKeys[frame + 1].mTime)
					break;
				frame++;
			}

			// interpolate between this frame's value and next frame's value
			unsigned int nextFrame = (frame + 1) % channel->mNumRotationKeys;
			
			auto & key = channel->mRotationKeys[frame];
			auto & nextKey = channel->mRotationKeys[nextFrame];

			double diffTime = nextKey.mTime - key.mTime;
			if (diffTime < DBL_EPSILON)
				diffTime += mAnim->mDuration;

			if (diffTime > DBL_EPSILON)
			{
				float factor = float((time - key.mTime) / diffTime);
				aiQuaternion::Interpolate(presentRotation, key.mValue, nextKey.mValue, factor);
			}
			else
			{
				presentRotation = key.mValue;
			}

		}

		// scale
		math::vec3f presentScaling(1, 1, 1);
		if (channel->mNumScalingKeys > 0)
		{
			unsigned int frame = 0;
			while (frame < channel->mNumScalingKeys - 1)
			{
				if (time < channel->mScalingKeys[frame + 1].mTime)
					break;
				frame++;
			}

			// interpolation
			unsigned int nextFrame = (frame + 1) % channel->mNumScalingKeys;

			auto & key = channel->mScalingKeys[frame];
			auto & nextKey = channel->mScalingKeys[nextFrame];

			double diffTime = nextKey.mTime - key.mTime;
			if (diffTime < DBL_EPSILON)
				diffTime += mAnim->mDuration;

			if (diffTime > DBL_EPSILON)
			{
				float factor = float((time - key.mTime) / diffTime);
				presentScaling = key.mValue + (nextKey.mValue - key.mValue) * factor;
			}
			else
			{
				presentScaling = key.mValue;
			}
		}

		math::mat4f& mat = mTransforms[channel->NodeName];
		mat = aiMatrix4x4(presentRotation.GetMatrix());
		mat[0] *= presentScaling.x; mat[1] *= presentScaling.x; mat[2] *= presentScaling.x;
		mat[4] *= presentScaling.y; mat[5] *= presentScaling.y; mat[6] *= presentScaling.y;
		mat[8] *= presentScaling.z; mat[9] *= presentScaling.z; mat[10] *= presentScaling.z;
		mat[12] = presentPosition.x; mat[13] = presentPosition.y; mat[14] = presentPosition.z;
	}

	for (unsigned int a = 0; a < mAnim->mMorphMeshChannels.size(); a++)
	{
		auto & channel = mAnim->mMorphMeshChannels[a];

		if (channel->mNumKeys > 0)
		{
			unsigned int frame = 0;

			while (frame < channel->mNumKeys - 1)
			{
				if (time < channel->mKeys[frame + 1].mTime)
					break;
				frame++;
			}
			// interpolate between this frame's value and next frame's value
			unsigned int nextFrame = (frame + 1) % channel->mNumKeys;

			auto & key = channel->mKeys[frame];
			auto & nextKey = channel->mKeys[nextFrame];

			double diffTime = nextKey.mTime - key.mTime;
			if (diffTime < DBL_EPSILON)
				diffTime += mAnim->mDuration;
			std::set<unsigned int> values;
			std::unordered_map<unsigned int, double>key_map;
			std::unordered_map<unsigned int, double>nextkey_map;

			mBlendShapeWeights.clear();
			for (int m = 0; m < key.mNumValuesAndWeights; m++)
			{
				key_map[key.mValues[m]] = key.mWeights[m];
				values.insert(key.mValues[m]);
			}
			for (int m = 0; m < nextKey.mNumValuesAndWeights; m++)
			{
				nextkey_map[nextKey.mValues[m]] = nextKey.mWeights[m];
				values.insert(nextKey.mValues[m]);
			}
			if (diffTime > DBL_EPSILON)
			{
				float factor = float((time - key.mTime) / diffTime);

				for (auto &iter : values)
				{
					double curValue = 0.0, nextValue = 0.0;
					if (key_map.find(iter) != key_map.end())
						curValue = key_map[iter];
					if (nextkey_map.find(iter) != nextkey_map.end())
						nextValue = nextkey_map[iter];
					mBlendShapeWeights[iter] = curValue + (nextValue - curValue) * factor;
				}
			}
			else
			{
			}
		}
	}
}
