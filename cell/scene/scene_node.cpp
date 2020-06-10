#include "scene/scene_node.h"

#include "scene.h"

#include "../mesh/mesh.h"
#include "../shading/material.h"

#include <assert.h>
#include <iostream>
namespace Cell
{
    // --------------------------------------------------------------------------------------------
    SceneNode::~SceneNode()
    {
        // traverse the list of children and delete accordingly.
        for (unsigned int i = 0; i < m_Children.size(); ++i)
        {
            // it should not be possible that a scene node is childed by more than one
            // parent, thus we don't need to care about deleting dangling pointers.
            delete m_Children[i];
        }
    }
	void SceneNode::SetLocalTransform(const math::mat4f & mat)
	{
		m_LocalTransform = mat;
	}
	math::mat4f SceneNode::GetLocalTransform() const
	{
		 return m_LocalTransform; 
	}
	math::mat4f SceneNode::GetGlobalTransform()
	{
		if (!GetParent())
			return m_LocalTransform;
		else
			return GetParent()->GetGlobalTransform()*m_LocalTransform;
	}
	math::mat4f SceneNode::GetGlobalPrevTransform()
	{
		//temp
		return GetGlobalTransform();
	}

	void SceneNode::SetLocalPosition(const math::vec3f & position)
	{
		m_LocalTransform.at(3, 0) += position.x;
		m_LocalTransform.at(3, 1) += position.y;
		m_LocalTransform.at(3, 2) += position.z;
		m_LocalPosition = position;
	}
	void SceneNode::SetLocalRotation(const math::Quatf & rotation)
	{
		m_LocalTransform.Decompose(m_LocalScale, m_LocalRotation, m_LocalPosition);
		m_LocalTransform = math::mat4f::Compose(m_LocalScale, rotation, m_LocalPosition);
		m_LocalRotation = rotation;
	}
	void SceneNode::SetLocalScale(const math::vec3f & scale)
	{
		m_LocalTransform.Decompose(m_LocalScale, m_LocalRotation, m_LocalPosition);
		m_LocalTransform = math::mat4f::Compose(scale, m_LocalRotation, m_LocalPosition);
		m_LocalScale = scale;
	}
	void SceneNode::SetLocalScale(const float scale)
	{
		m_LocalTransform.Decompose(m_LocalScale, m_LocalRotation, m_LocalPosition);
		m_LocalScale = math::vec3f(scale);
		m_LocalTransform = math::mat4f::Compose(scale, m_LocalRotation, m_LocalPosition);

	}

    // --------------------------------------------------------------------------------------------
    math::vec3f SceneNode::GetLocalPosition()
    {
		m_LocalTransform.Decompose(m_LocalScale, m_LocalRotation, m_LocalPosition);
		return m_LocalPosition;
    }
    // --------------------------------------------------------------------------------------------
    math::Quatf SceneNode::GetLocalRotation()
    {
		m_LocalTransform.Decompose(m_LocalScale, m_LocalRotation, m_LocalPosition);
        return m_LocalRotation;
    }
    // --------------------------------------------------------------------------------------------
    math::vec3f SceneNode::GetLocalScale()
    {
		m_LocalTransform.Decompose(m_LocalScale, m_LocalRotation, m_LocalPosition);
        return m_LocalScale;
    }
    // --------------------------------------------------------------------------------------------
    math::vec3f SceneNode::GetWorldPosition()
    {
        math::mat4f transform = GetGlobalTransform();
		
        return math::vec3f(transform.at(3,0), transform.at(3, 1), transform.at(3, 2));
    }
    // --------------------------------------------------------------------------------------------
    math::vec3f SceneNode::GetWorldScale()
    {
		math::mat4f transform = GetGlobalTransform();

		math::vec3f scale;
		math::vec3f pos;
		math::Quatf rot;
		transform.Decompose(scale, rot, pos);
        return scale;
    }
	void SceneNode::Update(double time, uint64_t frameIdx)
	{
		//update all components
		for (auto & component :components)
		{
			if (component.second)
				component.second->OnTick(time, frameIdx);
		}
		for (auto & child : m_Children)
			child->Update(time, frameIdx);
	}
	SceneNode * SceneNode::GetRoot()
	{
		SceneNode* parent = nullptr;
		SceneNode* cur = this;
		while (cur)
		{
			if (cur->GetParent())
				cur = cur->GetParent();
			else {
				parent = cur;
				break;
			}
		}
		return parent;
	}
	SceneNode * SceneNode::Find(const std::string & _name)
	{
		if (name == _name)
			return this;
		for (int i = 0; i < GetChildCount(); i++)
		{
			SceneNode* pSceneNode = m_Children[i]->Find(_name);
			if (pSceneNode != nullptr)return pSceneNode;
		}
		return nullptr;
	}
    // --------------------------------------------------------------------------------------------
    unsigned int SceneNode::GetID()
    {
        return m_ID;
    }
    // --------------------------------------------------------------------------------------------
    void SceneNode::AddChild(SceneNode *node)
    {
        // check if this child already has a parent. If so, first remove this scene node from its 
        // current parent. Scene nodes aren't allowed to exist under multiple parents.
        if (node->m_Parent)
        {
            node->m_Parent->RemoveChild(node->m_ID);
        }
        node->m_Parent = this;
        m_Children.push_back(node);
    }
    // --------------------------------------------------------------------------------------------
    void SceneNode::RemoveChild(unsigned int id)
    {
        auto it = std::find(m_Children.begin(), m_Children.end(), GetChild(id));
        if(it != m_Children.end())
            m_Children.erase(it);
    }
    // --------------------------------------------------------------------------------------------
    std::vector<SceneNode*> SceneNode::GetChildren()
    {
        return m_Children;
    }
    // --------------------------------------------------------------------------------------------
    unsigned int SceneNode::GetChildCount()
    {
        return m_Children.size();
    }
    // --------------------------------------------------------------------------------------------
    SceneNode *SceneNode::GetChild(unsigned int id)
    {
        for (unsigned int i = 0; i < m_Children.size(); ++i)
        {
            if(m_Children[i]->GetID() == id)
                return m_Children[i];
        }
        return nullptr;
    }
    // --------------------------------------------------------------------------------------------
    SceneNode* SceneNode::GetChildByIndex(unsigned int index)
    {
        assert(index < GetChildCount());
        return m_Children[index];
    }
    // --------------------------------------------------------------------------------------------
    SceneNode *SceneNode::GetParent()
    {
        return m_Parent;
    }
	void SceneNode::CopyData(SceneNode* newNode)
	{
		newNode->name = name;
		newNode->components = components;
	}
   
	const std::vector<float>& SceneNode::GetBoneMatrix()
	{
		/*Animator* animator=nullptr;
		SceneNode* cur = this;
		while (cur)
		{
			animator = cur->GetComponent<Animator>();
			if (animator != nullptr)
			{
				break;
			}
			cur = cur->GetParent();
		}
		if (animator != nullptr)
			return animator->GetSkinningMat(this);
		static std::vector<float> data;
		return data;*/
		static std::vector<float> data;
		return data; 
	}
}