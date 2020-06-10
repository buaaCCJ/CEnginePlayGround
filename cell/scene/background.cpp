#include "background.h"

#include "scene.h"

#include "../renderer/renderer.h"
#include "../resources/resources.h"
#include "../shading/material.h"
#include "../shading/shader.h"
#include "../shading/texture_cube.h"
#include "../mesh/cube.h"
#include "components/MeshRender.h"
namespace Cell
{
    // --------------------------------------------------------------------------------------------
    Background::Background() : SceneNode("Background")
    {
        Scene::Root->AddChild(this);

		MeshRender* mr = AddComponent<MeshRender>();
		mr->SetMaterial(new Cell::Material(Resources::LoadShader("background", "shaders/background.vs", "shaders/background.fs")));
		mr->SetMesh(new Cell::Cube(), math::vec3f(-99999.0), math::vec3f(99999.0));

		auto mat = mr->GetMaterial();
        // default material configuration
		mat->SetFloat("Exposure", 1.0f);
		mat->DepthCompare = GL_LEQUAL;
		mat->Cull = false;
		mat->ShadowCast = false;
		mat->ShadowReceive = false;
    }
    // --------------------------------------------------------------------------------------------
    Background::~Background()
    {

    }
    // --------------------------------------------------------------------------------------------
    void Background::SetCubemap(TextureCube* cubemap)
    {
        m_CubeMap = cubemap;

		auto mat = GetComponent<MeshRender>()->GetMaterial();

		mat->SetTextureCube("background", m_CubeMap, 0);
    }
};