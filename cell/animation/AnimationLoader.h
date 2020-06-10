#ifndef CELL_RESOURCES_ANIMATION_LOADER_H
#define CELL_RESOURCES_ANIMATION_LOADER_H

#include <string>
#include <vector>

#include <math/linear_algebra/vmath.h>

struct aiNode;
struct aiScene;
struct aiMesh;
struct aiMaterial;
struct aiString;
struct aiAnimation;

namespace Cell
{
    class Renderer;
    class SceneNode;
    class Mesh;
    class Material;

    /* 

      Mesh load functionality.

    */
    class AnimationLoader
    {
    private:
        // NOTE(Chenc): keep track of all loaded animation
        static std::vector<aiAnimation*> animationStore;
    public:
        static void       Clean();

        static bool LoadAnimation(const aiScene* aScene,SceneNode* sceneNode);
    private:
       /* static SceneNode* processNode(Renderer* renderer, aiNode* aNode, const aiScene* aScene, std::string directory, bool setDefaultMaterial);
        static Mesh*      parseMesh(aiMesh* aMesh, const aiScene* aScene, math::vec3f& out_Min, math::vec3f& out_Max);
        static Material*  parseMaterial(Renderer* renderer, aiMaterial* aMaterial, const aiScene* aScene, std::string directory);

        static std::string processPath(aiString* path, std::string directory);*/
    };
}
#endif