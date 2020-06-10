#include "AnimationLoader.h"

#include "resources.h"

#include "../renderer/renderer.h"
#include "../mesh/mesh.h" 
#include "../shading/material.h"
#include "../scene/scene_node.h"
#include "../shading/texture.h"

#include <utility/logging/log.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Cell
{
	std::vector<aiAnimation*> AnimationLoader::animationStore = std::vector<aiAnimation*>();

	void AnimationLoader::Clean()
	{
		for (unsigned int i = 0; i < AnimationLoader::animationStore.size(); ++i)
		{
			delete AnimationLoader::animationStore[i];
		}
	}

	bool AnimationLoader::LoadAnimation(const aiScene* aScene, SceneNode* sceneNode)
	{
		if (!aScene || !sceneNode)return false;
		if (aScene->mNumAnimations == 0)return true;
		Animator* mAnimator = sceneNode->AddComponent<Animator>();
		for (int i = 0; i < aScene->mNumAnimations; i++)
		{
			mAnimator->AddAnimationClip(std::make_shared<AnimationClip>(aScene->mAnimations[i]));
		}
	}

}