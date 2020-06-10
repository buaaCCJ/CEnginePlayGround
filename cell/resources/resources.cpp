#include "resources.h"

#include "shader_loader.h"
#include "texture_loader.h"
#include "mesh_loader.h"
#include "AnimationLoader.h"
#include "../scene/scene.h"
#include "../scene/scene_node.h"

#include <utility/string_id.h>
#include <utility/logging/log.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <stack>
#include <vector>
#include "common/FileManager.h"
#include "renderer/renderer.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "components/MeshRender.h"
#include "components/SkinningMeshRender.h"
namespace Cell
{
	std::map<unsigned int, Shader>      Resources::m_Shaders = std::map<unsigned int, Shader>();
	std::map<unsigned int, Texture>     Resources::m_Textures = std::map<unsigned int, Texture>();
	std::map<unsigned int, TextureCube> Resources::m_TexturesCube = std::map<unsigned int, TextureCube>();
	std::map<unsigned int, SceneNode*>  Resources::m_Meshes = std::map<unsigned int, SceneNode*>();
	// --------------------------------------------------------------------------------------------
	void Resources::Init()
	{
		// initialize default assets/resources that should  always be available, regardless of 
		// configuration.        
		Texture placeholderTexture;
	}
	void Resources::Clean()
	{
		// traverse all stored mesh scene nodes and delete accordingly.
		// Note that this time we don't care about deleting dangling pointers as each scene node is
		// unique and shouldn't reference other scene nodes than their children.
		for (auto it = m_Meshes.begin(); it != m_Meshes.end(); it++)
		{
			delete it->second;
		}
	}

	// --------------------------------------------------------------------------------------------
	Shader* Resources::LoadShader(std::string name, std::string vsPath, std::string fsPath, std::vector<std::string> defines)
	{
		vsPath = RESOURCE_PATH + vsPath;
		fsPath = RESOURCE_PATH + fsPath;

		unsigned int id = SID(name);

		// if shader already exists, return that handle
		if (Resources::m_Shaders.find(id) != Resources::m_Shaders.end())
			return &Resources::m_Shaders[id];

		Shader shader = ShaderLoader::Load(name, vsPath, fsPath, defines);
		Resources::m_Shaders[id] = shader;
		return &Resources::m_Shaders[id];
	}
	// --------------------------------------------------------------------------------------------
	Shader* Resources::GetShader(std::string name)
	{
		unsigned int id = SID(name);

		// if shader exists, return that handle
		if (Resources::m_Shaders.find(id) != Resources::m_Shaders.end())
		{
			return &Resources::m_Shaders[id];
		}
		else
		{
			Log::Message("Requested shader: " + name + " not found!", LOG_WARNING);
			return nullptr;
		}
	}
	// --------------------------------------------------------------------------------------------
	Texture* Resources::LoadTexture(std::string name, std::string path, GLenum target, GLenum format, bool srgb)
	{
		path = RESOURCE_PATH + path;
		unsigned int id = SID(name);

		// if texture already exists, return that handle
		if (Resources::m_Textures.find(id) != Resources::m_Textures.end())
			return &Resources::m_Textures[id];

		Log::Message("Loading texture file at: " + path + ".", LOG_INIT);

		Texture texture = TextureLoader::LoadTexture(path, target, format, srgb);

		Log::Message("Succesfully loaded: " + path + ".", LOG_INIT);

		// make sure texture got properly loaded
		if (texture.Width > 0)
		{
			Resources::m_Textures[id] = texture;
			return &Resources::m_Textures[id];
		}
		else
		{
			return nullptr;
		}
	}
	// --------------------------------------------------------------------------------------------
	Texture* Resources::LoadHDR(std::string name, std::string path)
	{
		path = RESOURCE_PATH + path;
		unsigned int id = SID(name);

		// if texture already exists, return that handle
		if (Resources::m_Textures.find(id) != Resources::m_Textures.end())
			return &Resources::m_Textures[id];

		Texture texture = TextureLoader::LoadHDRTexture(path);
		// make sure texture got properly loaded
		if (texture.Width > 0)
		{
			Resources::m_Textures[id] = texture;
			return &Resources::m_Textures[id];
		}
		else
		{
			return nullptr;
		}
	}
	// --------------------------------------------------------------------------------------------
	Texture* Resources::GetTexture(std::string name)
	{
		unsigned int id = SID(name);

		// if shader exists, return that handle
		if (Resources::m_Textures.find(id) != Resources::m_Textures.end())
		{
			return &Resources::m_Textures[id];
		}
		else
		{
			Log::Message("Requested texture: " + name + " not found!", LOG_WARNING);
			return nullptr;
		}
	}
	// --------------------------------------------------------------------------------------------
	TextureCube* Resources::LoadTextureCube(std::string name, std::string folder)
	{
		unsigned int id = SID(name);

		// if texture already exists, return that handle
		if (Resources::m_TexturesCube.find(id) != Resources::m_TexturesCube.end())
			return &Resources::m_TexturesCube[id];

		TextureCube texture = TextureLoader::LoadTextureCube(folder);
		Resources::m_TexturesCube[id] = texture;
		return &Resources::m_TexturesCube[id];
	}
	// --------------------------------------------------------------------------------------------
	TextureCube* Resources::GetTextureCube(std::string name)
	{
		unsigned int id = SID(name);

		// if shader exists, return that handle
		if (Resources::m_TexturesCube.find(id) != Resources::m_TexturesCube.end())
		{
			return &Resources::m_TexturesCube[id];
		}
		else
		{
			Log::Message("Requested texture cube: " + name + " not found!", LOG_WARNING);
			return nullptr;
		}
	}
	// --------------------------------------------------------------------------------------------
	SceneNode* Resources::LoadMesh(Renderer* renderer, std::string name, std::string path,bool bSetDefaultMaterial)
	{
		path = RESOURCE_PATH + path;
		unsigned int id = SID(name);

		// if mesh's scene node was already loaded before, copy the scene node's memory and return 
		// the copied reference. We return a copy as the moment the global scene deletes the 
		// returned node, all other and next requested scene nodes of this model will end up as
		// dangling pointers.
		if (Resources::m_Meshes.find(id) != Resources::m_Meshes.end())
		{
			return Scene::MakeSceneNode(Resources::m_Meshes[id]);
		}

		// MeshLoader::LoadMesh initializes a scene node hierarchy on the heap. We are responsible 
		// for managing the memory; keep a reference to the root node of the model scene. 
		SceneNode* node = MeshLoader::LoadMesh(renderer, path, bSetDefaultMaterial);

		Resources::m_Meshes[id] = node;

		// return a copied reference through the scene to prevent dangling pointers. 
		// See description above.
		//return Scene::MakeSceneNode(node);
		return node;
	}
	bool Resources::LoadAnimationClip(SceneNode * node, std::string path)
	{
		if (!node)
			return false;
		path = RESOURCE_PATH + path;
		Assimp::Importer importer;
		const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_CalcTangentSpace);

		if (!scene || /*scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE ||*/ !scene->mRootNode)
		{
			Log::Message("Assimp failed to load model at path: " + path, LOG_ERROR);
			return nullptr;
		}

		std::string directory = path.substr(0, path.find_last_of("/"));

		Log::Message("Succesfully loaded: " + path + ".", LOG_INIT);

		auto ret = AnimationLoader::LoadAnimation(scene, node);
		if (!ret)
			Log::Message("Assimp failed to load animation: " + path + ".", LOG_INIT);
		return ret;
	}
	bool Resources::LoadMaterialFromJson(Renderer* renderer, SceneNode * node, std::string path)
	{
		using namespace rapidjson;
		std::string fileParam = FileUtil::readFileAsFString(path);
		Document doc;
		if (doc.Parse(fileParam.c_str()).HasParseError())
		{
			throw std::string("parse error\n");
			return false;
		}
		auto & matArray = doc.GetArray();
		for (auto & d : matArray)
		{
			Value & mat = d["material"];

			std::string mesh_name = d["meshname"].GetString();
			int meshGroupIdx = d["meshGroupIdx"].GetInt();
			std::string shader_name = mat["shader_name"].GetString();
			std::string vs_name = mat["vs_shader"].GetString();
			std::string ps_name = mat["ps_shader"].GetString();
			Cell::Shader*   customShader = Cell::Resources::LoadShader(shader_name, vs_name, ps_name);
			Cell::Material* custMat = renderer->CreateCustomMaterial(customShader);
			custMat->Type = MATERIAL_DEFAULT;
			Value & params = mat["param"];
			int slot = 4;
			auto  ParserTexture = [&](const std::string& name) {
				if (params.HasMember(name.c_str()))
				{
					auto path = params[name.c_str()].GetString();
					auto tex = Cell::Resources::LoadTexture(name, path);
					if (tex)
						custMat->SetTexture(name, tex, slot++);
					else
						std::cerr << "can not load texture" << std::endl;
				}
			};

			ParserTexture("TexAlbedo");
			ParserTexture("TexNormal");
			//ParserTexture("TexMetallic");
			//ParserTexture("TexRoughness");
			ParserTexture("TexAO");

			for (auto & iter : custMat->m_Uniforms)
			{
				if (params.HasMember(iter.first.c_str()))
				{
					switch (iter.second->Type)
					{
					case SHADER_TYPE::SHADER_TYPE_FLOAT:
					{
						float value = params[iter.first.c_str()].GetFloat();
 						custMat->SetFloat(iter.first, value);
						break;
					}
					default:
						break;
					}
				}
			}

			SceneNode* child_node = node->Find(mesh_name);
			if (child_node)
			{
				auto setMaterial = [&](SceneNode* InNode, Material* InMat)
				{
					auto smr = InNode->GetComponent<SkinningMeshRender>();
					if (smr)
					{
						smr->SetMaterial(InMat);
						return true;
					}
					auto mr = InNode->GetComponent<MeshRender>();
					if (mr)
					{
						mr->SetMaterial(InMat);
						return true;
					}
					return false;
				};
				bool ret = false;
				//support one skinning mesh render with many materials which is similar as unity
				if (child_node->GetChildCount() == 0)
				{
					ret = setMaterial(child_node, custMat);
				}
				else
				{
					auto realNode = child_node->GetChildByIndex(meshGroupIdx);
					ret = setMaterial(realNode, custMat);
				}

				if (!ret)
				{
					std::cerr << "can not find child node with material: " << child_node->GetName() << std::endl;
				}
			}
		}
		
		return true;
	}
	// --------------------------------------------------------------------------------------------
	SceneNode* Resources::GetMesh(std::string name)
	{
		unsigned int id = SID(name);

		// if mesh's scene node was already loaded before, copy the scene node's memory and return 
		// the copied reference. We return a copy as the moment the global scene deletes the 
		// returned node, all other and next requested scene nodes of this model will end up as
		// dangling pointers.
		if (Resources::m_Meshes.find(id) != Resources::m_Meshes.end())
		{
			return Scene::MakeSceneNode(Resources::m_Meshes[id]);
		}
		else
		{
			Log::Message("Requested mesh: " + name + " not found!", LOG_WARNING);
			return nullptr;
		}
	}
}