#ifndef CELL_SCENE_SCENE_NODE_H
#define CELL_SCENE_SCENE_NODE_H

#include <vector>
#include <iostream>
#include <math/cmath.h>
//#include "components/Component.h"
#include "components/Animator.h"

namespace Cell
{
    class Scene;
    class Mesh;
    class Material;
    /* NOTE(Joey):

      An individual scene node that links a mesh to a material
      to render the mesh with while at the same time
      maintaining a parent-child hierarchy for transform
      relations.

      Each node can have any number of children (via a linked
      list) and represents a single renderable entity in a
      larger scene where aech child transform on top of their
      parent node.

    */
	class SceneNode
	{
	public:
		std::string name;

		math::mat4f m_LocalTransform;

		math::mat4f m_GlobalTransform;
		math::mat4f m_GlobalPrevTransform;

	private:
		std::vector<SceneNode*> m_Children;
		SceneNode *m_Parent = nullptr;

		math::vec3f m_LocalPosition = math::vec3f(0.0f);
		math::Quatf m_LocalRotation=math::Quatf(); 
		math::vec3f m_LocalScale = math::vec3f(1.0f);

		// mark the current node's tranform as dirty if it needs to be re-calculated this frame
		bool m_Dirty;

		// each node is uniquely identified by a 32-bit incrementing unsigned integer
		unsigned int m_ID;

		static unsigned int CounterID;
	public:
		//SceneNode(unsigned int id);
		SceneNode(const std::string _name) :name(_name) {}
		~SceneNode();

		// scene node transform
		void SetLocalTransform(const math::mat4f& mat);

		math::mat4f GetLocalTransform()const;

		math::mat4f GetGlobalTransform();

		math::mat4f GetGlobalPrevTransform();

		void SetLocalPosition(const math::vec3f& position);

		void SetLocalRotation(const math::Quatf& rotation);

		void SetLocalScale(const math::vec3f& scale);

		void SetLocalScale(const float scale);

		math::vec3f GetLocalPosition();

		math::Quatf GetLocalRotation();

		math::vec3f GetLocalScale();

		math::vec3f GetWorldPosition();

		math::vec3f GetWorldScale();

		void Update(double time, uint64_t frameIdx);

		SceneNode* GetRoot();

		SceneNode* Find(const std::string& name);

		// scene graph 
		unsigned int GetID();
		void AddChild(SceneNode *node);
		void RemoveChild(unsigned int id); // TODO(Joey): think of proper way to unqiuely idetnfiy child nodes (w/ incrementing node ID or stringed hash ID?)
		std::vector<SceneNode*> GetChildren();
		unsigned int            GetChildCount();
		SceneNode              *GetChild(unsigned int id);
		SceneNode              *GetChildByIndex(unsigned int index);
		SceneNode              *GetParent();
		void			       CopyData(SceneNode*);

		std::string GetName() { return name; }

		void SetName(const std::string& _name) { name = _name; }

		std::map<ClassIDType, std::shared_ptr<Component>> components;

		const std::vector<float>& GetBoneMatrix();
	public:
			template <typename T>
			T* AddComponent()
			{
				if (!components.count(T::GetClassID()))
				{
					components[T::GetClassID()].reset(new T(this));
				}
				return dynamic_cast<T*>(components[T::GetClassID()].get());
			}

			template <typename T>
			T* GetComponent()
			{
				auto type = T::GetClassID();
				if(components.count(type))
					return dynamic_cast<T*>(components[type].get());
				return nullptr;
			}
			
			template<typename T>
			void RemoveComponentPtr()
			{
				auto type= T::GetClassID();
				if (components.count(type))
				{
					components[type].reset();
				}
			}
	};
}
#endif