#ifndef CELL_RESOURCES_MESH_LOADER_H
#define CELL_RESOURCES_MESH_LOADER_H

#include <string>
#include <vector>

#include <math/linear_algebra/vmath.h>

struct aiNode;
struct aiScene;
struct aiMesh;
struct aiMaterial;
struct aiString;

namespace Cell
{
    class Renderer;
    class SceneNode;
    class Mesh;
    class Material;
	class AnimMesh;
    /* 

      Mesh load functionality.

    */
    class MeshLoader
    {
    private:
        // NOTE(Joey): keep track of all loaded mesh
        static std::vector<Mesh*> meshStore;

		static std::vector<const aiScene*> aiSceneStore;
    public:
        static void       Clean();

        static SceneNode* LoadMesh(Renderer* renderer, std::string path, bool setDefaultMaterial = true);

    private:
        static SceneNode* processNode(Renderer* renderer, aiNode* aNode, const aiScene* aScene, std::string directory, bool setDefaultMaterial);

		static Mesh*      parseMesh(aiMesh* aMesh, const aiScene* aScene, math::vec3f& out_Min, math::vec3f& out_Max);
		
		static AnimMesh*  parseMesh(aiMesh* aMesh);

        static Material*  parseMaterial(Renderer* renderer, aiMaterial* aMaterial, const aiScene* aScene, std::string directory);

        static std::string processPath(aiString* path, std::string directory);
    };
}
#endif