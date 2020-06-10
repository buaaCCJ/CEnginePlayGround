#pragma once
#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED
#include "math/cmath.h"
#include <vector>
namespace Cell
{
	struct VectorKey
	{
		/** The time of this key */
		double mTime;

		math::vec3f mValue;

	};
	struct QuatKey
	{
		double mTime;
		aiQuaternion mValue;
	};
	struct MeshMorphKey
	{
		/** The time of this key */
		double mTime;

		/** The values and weights at the time of this key */
		std::vector<unsigned int> mValues;
		std::vector<double> mWeights;
		/** The number of values and weights */
		unsigned int mNumValuesAndWeights;

		MeshMorphKey()
			: mTime(0.0)
			, mNumValuesAndWeights(0) {}
		~MeshMorphKey()
		{
		}
	};

	class NodeAnim
	{
	public:
		std::string NodeName;

		/** The number of position keys */
		unsigned int mNumPositionKeys;
		std::vector<VectorKey> mPositionKeys;

		/** The number of rotation keys */
		unsigned int mNumRotationKeys;
		std::vector<QuatKey> mRotationKeys;


		/** The number of scaling keys */
		unsigned int mNumScalingKeys;
		std::vector <VectorKey> mScalingKeys;

		NodeAnim()
			: mNumPositionKeys(0)
			, mNumRotationKeys(0)
			, mNumScalingKeys(0)
			
		{}
		~NodeAnim()
		{
			
		}

	};

	class MeshMorphAnim
	{
	public:
		std::string mName;

		/** Size of the #mKeys array. Must be 1, at least. */
		unsigned int mNumKeys;

		std::vector<MeshMorphKey> mKeys;

		MeshMorphAnim()
			: mNumKeys()
			, mKeys()
		{}


		~MeshMorphAnim()
		{
		}
	};
	using NodeAnimPtr = std::shared_ptr<NodeAnim>;
	using NodeAnimTake = std::vector<NodeAnimPtr>;
	using MeshMorphAnimPtr = std::shared_ptr<MeshMorphAnim>;
	using MeshMorphAnimTake = std::vector<MeshMorphAnimPtr>;
	class Animation
	{
	public:

		std::string mName;
		/** Duration of the animation in ticks.  */
		double mDuration;

		float mLength = 0.0;

		/** Ticks per second. 0 if not specified in the imported file */
		double mTicksPerSecond;

		NodeAnimTake  mChannels;

		MeshMorphAnimTake mMorphMeshChannels;

		Animation()
			: mDuration(-1.)
			, mTicksPerSecond(0.) {}

		~Animation() {
		}
	};

	
	using AnimationPtr = std::shared_ptr<Animation>;

}
#endif