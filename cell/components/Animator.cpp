#include "Animator.h"
#include "scene/scene_node.h"
#include "components/MeshRender.h"
#include "components/SkinningMeshRender.h"
Cell::Animator::~Animator()
{
}

void Cell::Animator::TickComponent(double time, uint64_t frameIndex)
{
	if (!controller.get())
		return;

	auto ret=controller->Tick(time, frameIndex);
	if (ret)
	{
		TransformMap transformMap = controller->m_curAnimState->GetTransformMap();
		BlendShapeWeightMap bsMap = controller->m_curAnimState->GetBSWeightMap();
		UpdateSceneNodeTransform(GetSceneNode(), transformMap);
		UpdateSceneNodeBSWeight(GetSceneNode(), bsMap);
	}
}

void Cell::Animator::PlayAnimation(const int id, double start_time, bool loop)
{
	if (!controller.get())
		return;
	controller->PlayAnimation(id, start_time, loop);
}

bool Cell::Animator::AddAnimationClip(AnimationClipPtr clip)
{
	if (!controller)
		controller.reset(new AnimationController());

	return controller->AddAnimationClip(clip);
}

void Cell::Animator::UpdateSceneNodeTransform(SceneNode* node, const TransformMap& transform)
{
	if (!node)
		return;

	auto iter = transform.find(node->name);
	if (iter != transform.end())
		node->SetLocalTransform(iter->second);
	for (auto & child_node : node->GetChildren())
	{
		UpdateSceneNodeTransform(child_node, transform);
	}
	return;
}

void Cell::Animator::UpdateSceneNodeBSWeight(SceneNode * node, const BlendShapeWeightMap & bsMap)
{
	if (!node)
		return;

	SkinningMeshRender* smr = node->GetComponent<SkinningMeshRender>();
	if (smr)
		smr->SetBlendShapeWeight(bsMap);
	for (auto & item : node->GetChildren())
	{
		UpdateSceneNodeBSWeight(item, bsMap);
	}
}

const std::vector<float>& Cell::Animator::GetSkinningMat(SceneNode* node)
{
	std::vector<float>data;
	std::vector<math::mat4f> mTransforms;
	if (!node)
		return data;

	TransformMap transformMap = controller->m_curAnimState->GetTransformMap();
	MeshRender* mr = node->GetComponent<MeshRender>();
	for (int a = 0; a < mr->GetMesh()->mBones.size(); a++)
	{
		auto & bone = mr->GetMesh()->mBones[a];
		auto iter = transformMap.find(bone.mName);
		if (iter != transformMap.end())
		{
			mTransforms.push_back(iter->second*bone.mOffsetMatrix);
		}
		else
		{
			std::cerr << "can not find this bone, something wrong: " << bone.mName << std::endl;
		}
	}
	mTransfromData.resize(mTransforms.size() * 12, 0.0f);
	float* dataptr = mTransfromData.data();
	for (int i = 0; i < mTransforms.size(); i++)
	{
		auto transposed = mTransforms[i].transpose();
		memcpy(dataptr + i * 12, transposed.data, 12 * sizeof(float));
	}
	return mTransfromData;
}
