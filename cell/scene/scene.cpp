#include "scene.h"

#include "scene_node.h"
#include "../mesh/mesh.h"
#include "../shading/material.h"
#include <iostream>
#include <stack>
#include "components/MeshRender.h"
namespace Cell
{
    SceneNode* Scene::Root = new SceneNode("root");
    unsigned int Scene::CounterID = 0;    
	std::map<std::string, SceneNode*> cachedSceneNode;
    // --------------------------------------------------------------------------------------------
    void Scene::Clear()
    {       
        Scene::DeleteSceneNode(Root);
        Scene::Root = new SceneNode("root");
    }
    // --------------------------------------------------------------------------------------------
    SceneNode* Scene::MakeSceneNode(const std::string& name)
    {
		if (cachedSceneNode.find(name) != cachedSceneNode.end())
		{
			std::cerr << "we have a secene node with " << name << " ,please check" << std::endl;
			return nullptr;
		}
        SceneNode* node = new SceneNode(name);
		cachedSceneNode[name] = node;

        // keep a global rerefence to this scene node s.t.we can clear the scene's nodes for memory 
        // management: end of program or when switching scenes.
        Root->AddChild(node);
        return node;
    }
    // --------------------------------------------------------------------------------------------
    SceneNode* Scene::MakeSceneNode(const std::string& name, Mesh* mesh, Material* material)
    {
		if (cachedSceneNode.find(name) != cachedSceneNode.end())
		{
			std::cerr << "we have a secene node with " << name << " ,please check" << std::endl;
			return nullptr;
		}
        SceneNode* node = new SceneNode(name);
		MeshRender* mr = node->AddComponent<MeshRender>();
		mr->SetMesh(mesh,math::vec3f(-999,-999,-999),math::vec3f(999, 999, 999));
		mr->SetMaterial(material);
		node->name = name;
        // keep a global rerefence to this scene node s.t. we can clear the scene's nodes for 
        // memory management: end of program or when switching scenes.
        Root->AddChild(node);
		
		cachedSceneNode[name] = node;
        return node;
    }
    // --------------------------------------------------------------------------------------------
    SceneNode* Scene::MakeSceneNode(SceneNode* node)
    {
        SceneNode *newNode = new SceneNode(node->GetName());
		node->CopyData(newNode);

        // traverse through the list of children and add them correspondingly
        std::stack<SceneNode*> nodeStack;
        for (unsigned int i = 0; i < node->GetChildCount(); ++i)
            nodeStack.push(node->GetChildByIndex(i));
        while (!nodeStack.empty())
        {
            SceneNode* child = nodeStack.top();
            nodeStack.pop();
            // similarly, create SceneNode for each child and push to scene node memory list.
            SceneNode* newChild = new SceneNode(child->GetName());
			child->CopyData(newChild);
            newNode->AddChild(newChild);

            for (unsigned int i = 0; i < child->GetChildCount(); ++i)
                nodeStack.push(child->GetChildByIndex(i));
        }

        Root->AddChild(newNode);
        return newNode;
    }
    // --------------------------------------------------------------------------------------------
    void Scene::DeleteSceneNode(SceneNode *node)
    {
        if (node->GetParent())
        {
            node->GetParent()->RemoveChild(node->GetID());
        }
        // all delete logic is contained within each scene node's destructor.
        delete node;
    }
}
