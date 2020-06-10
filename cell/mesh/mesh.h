#ifndef CELL_MESH_H
#define CELL_MESH_H

#include <vector>
#include <functional>
#include <iostream>
#include <math/linear_algebra/vmath.h>
#include <math/cmath.h>
#include <Eigen/Eigen>
namespace Cell
{
    /*

      Manually define a list of topology types as we don't want to directly link a mesh to an 
      OpenGL toplogy type as this would reduce the renderer's cross compatbility.

      Yes, yes I know that we still have OpenGL indices in here (VAO, VBO, EBO) which we'll 
      get rid of in a cross renderer way soon enough.

    */
    enum TOPOLOGY
    {
        POINTS,
        LINES,
        LINE_STRIP,
        TRIANGLES,
        TRIANGLE_STRIP,
        TRIANGLE_FAN,
    };
	class Bone
	{
	public:
		Bone(const std::string& _name, const math::mat4f& _mat)
			:mName(_name), mOffsetMatrix(_mat) {}

		std::string mName;
		math::mat4f mOffsetMatrix;
	};
	class AnimMesh
	{
		//vertices.col(0)is origin vertex, others are the differences between the blendshape and the original model
		Eigen::MatrixXf vertices;
		Eigen::MatrixXf normals;
		Eigen::MatrixXi faces;
		std::vector<std::string> names;
		//contains orgin mesh, so num=real blendshape num+1
		int num;
		AnimMesh() :num(0) {}
	};
    /* 

      Base Mesh class. A mesh in its simplest form is purely a list of vertices, with some added 
      functionality for easily setting up the hardware configuration relevant for rendering.

    */
    class Mesh
    {
        // NOTE(Joey): public for now for testing and easy access; will eventually be private and only visible to renderer (as a friend class)
    public:
        unsigned int m_VAO = 0;
        unsigned int m_VBO;
        unsigned int m_EBO;
		bool bIsHaveBone = false;
		bool isSuitGPUSkin() { return mNumBones <= 80; }
    public:
        std::vector<math::vec3f> Positions;
        std::vector<math::vec2f> UV;
        std::vector<math::vec3f> Normals;
        std::vector<math::vec3f> Tangents;
        std::vector<math::vec3f> Bitangents;
		std::vector<math::vec4f> BoneIndices;
		std::vector<math::vec4f> BoneWeights;
		std::vector<Bone> mBones;

		int mNumBones = 0;

        TOPOLOGY Topology = TRIANGLES;
        std::vector<unsigned int> Indices;

        // support multiple ways of initializing a mesh
        Mesh();
        Mesh(std::vector<math::vec3f> positions, std::vector<unsigned int> indices);
        Mesh(std::vector<math::vec3f> positions, std::vector<math::vec2f> uv, std::vector<unsigned int> indices);
        Mesh(std::vector<math::vec3f> positions, std::vector<math::vec2f> uv, std::vector<math::vec3f> normals, std::vector<unsigned int> indices);
        Mesh(std::vector<math::vec3f> positions, std::vector<math::vec2f> uv, std::vector<math::vec3f> normals, std::vector<math::vec3f> tangents, std::vector<math::vec3f> bitangents, std::vector<unsigned int> indices);

        // set vertex data manually
        // TODO(Joey): not sure if these are required if we can directly set vertex data from public fields; construct several use-cases to test.
        void SetPositions(std::vector<math::vec3f> positions);

		std::vector<math::vec3f>& GetPosition() { return Positions; }

        void SetUVs(std::vector<math::vec2f> uv);

        void SetNormals(std::vector<math::vec3f> normals);

		std::vector<math::vec3f>& GetNormal() { return Normals; }

        void SetTangents(std::vector<math::vec3f> tangents, std::vector<math::vec3f> bitangents); // NOTE(Joey): you can only set both tangents and bitangents at the same time to prevent mismatches

        // commits all buffers and attributes to the GPU driver
        void Finalize(bool interleaved = true);
		//void Finalize(bool interleaved = false);

        // generate triangulated mesh from signed distance field
		void FromSDF(std::function<float (math::vec3f)>& sdf, float maxDistance, uint16_t gridResolution);

		void UpdateVertAndNormalSubData();

    private:
        void calculateNormals(bool smooth = true);
        void calculateTangents();
    };
}
#endif