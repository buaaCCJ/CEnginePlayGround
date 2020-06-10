cmake_minimum_required(VERSION 3.6.0)

include_directories( ${CENGINE_SRCDIR}/ )
include_directories( ${ST3D_DEPDIR}/GLFW/includes/ )
include_directories( ${ST3D_DEPDIR}/assimp/include/ )
include_directories( ${ST3D_DEPDIR}/eigen/ )
include_directories( ${ST3D_DEPDIR}/ )

include_directories( ${CENGINE_SRCDIR}/camera/ )
include_directories( ${CENGINE_SRCDIR}/animation/ )
include_directories( ${CENGINE_SRCDIR}/glad/ )
include_directories( ${CENGINE_SRCDIR}/imgui/ )
include_directories( ${CENGINE_SRCDIR}/lighting/ )
include_directories( ${CENGINE_SRCDIR}/components/ )
include_directories( ${CENGINE_SRCDIR}/mesh/ )
include_directories( ${CENGINE_SRCDIR}/render/ )
include_directories( ${CENGINE_SRCDIR}/resources/ )
include_directories( ${CENGINE_SRCDIR}/renderer/ )
include_directories( ${CENGINE_SRCDIR}/scene/ )
include_directories( ${CENGINE_SRCDIR}/fg/ )
include_directories( ${CENGINE_SRCDIR}/shading/ )
include_directories( ${CENGINE_SRCDIR}/stb/ )
include_directories( ${CENGINE_SRCDIR}/common/ )
include_directories( ${CENGINE_SRCDIR}/math/ )
include_directories( ${CENGINE_SRCDIR}/math/geometry/ )
include_directories( ${CENGINE_SRCDIR}/math/linear_algebra/ )
include_directories( ${CENGINE_SRCDIR}/math/trigonometry/ )
include_directories( ${CENGINE_SRCDIR}/../ )



include_directories( ${CUTILITY_DIR}/ )
include_directories( ${CUTILITY_DIR}/logging/ )
include_directories( ${CUTILITY_DIR}/random/ )
include_directories( ${CUTILITY_DIR}/timing/ )

set(CENGINE_SRCS

            ${CENGINE_SRCDIR}/cell.h 
            ${CENGINE_SRCDIR}/cell.cpp
			
			${CENGINE_SRCDIR}/components/Animator.h
			${CENGINE_SRCDIR}/components/Animator.cpp
			${CENGINE_SRCDIR}/components/MeshRender.cpp
			${CENGINE_SRCDIR}/components/MeshRender.h
			${CENGINE_SRCDIR}/components/SkinningMeshRender.cpp
			${CENGINE_SRCDIR}/components/SkinningMeshRender.h
			${CENGINE_SRCDIR}/components/Component.h
			
			${CENGINE_SRCDIR}/animation/AnimationLoader.h
			${CENGINE_SRCDIR}/animation/AnimationLoader.cpp
			${CENGINE_SRCDIR}/animation/AnimationController.h
			${CENGINE_SRCDIR}/animation/AnimationController.cpp	
			${CENGINE_SRCDIR}/animation/AnimationState.h
			${CENGINE_SRCDIR}/animation/AnimationState.cpp
			${CENGINE_SRCDIR}/animation/AnimationClip.h
			${CENGINE_SRCDIR}/animation/AnimationClip.cpp
			${CENGINE_SRCDIR}/animation/Animation.h
			
			${CENGINE_SRCDIR}/common/FileManager.h
			${CENGINE_SRCDIR}/common/FileManager.cpp
			
            ${CENGINE_SRCDIR}/glad/glad.h
			${CENGINE_SRCDIR}/glad/glad.c
			${CENGINE_SRCDIR}/glad/khrplatform.h
			
			${CENGINE_SRCDIR}/camera/camera.cpp
			${CENGINE_SRCDIR}/camera/camera.h
			${CENGINE_SRCDIR}/camera/camera_frustum.cpp
			${CENGINE_SRCDIR}/camera/camera_frustum.h
			${CENGINE_SRCDIR}/camera/fly_camera.cpp
			${CENGINE_SRCDIR}/camera/fly_camera.h
			
			${CENGINE_SRCDIR}/imgui/imgui.cpp
			${CENGINE_SRCDIR}/imgui/imgui.h
			${CENGINE_SRCDIR}/imgui/imgui_demo.cpp
			${CENGINE_SRCDIR}/imgui/imgui_draw.cpp
	
			${CENGINE_SRCDIR}/mesh/circle.cpp
			${CENGINE_SRCDIR}/mesh/circle.h
			${CENGINE_SRCDIR}/mesh/cube.cpp
			${CENGINE_SRCDIR}/mesh/cube.h
			${CENGINE_SRCDIR}/mesh/line_strip.cpp
			${CENGINE_SRCDIR}/mesh/line_strip.h
			${CENGINE_SRCDIR}/mesh/mesh.cpp
			${CENGINE_SRCDIR}/mesh/mesh.h
			${CENGINE_SRCDIR}/mesh/plane.cpp
			${CENGINE_SRCDIR}/mesh/plane.h
			${CENGINE_SRCDIR}/mesh/quad.cpp
			${CENGINE_SRCDIR}/mesh/quad.h
			${CENGINE_SRCDIR}/mesh/sphere.cpp
			${CENGINE_SRCDIR}/mesh/sphere.h
			${CENGINE_SRCDIR}/mesh/torus.cpp
			${CENGINE_SRCDIR}/mesh/torus.h
			
			${CENGINE_SRCDIR}/lighting/directional_light.h
			${CENGINE_SRCDIR}/lighting/point_light.h
			
			${CENGINE_SRCDIR}/renderer/command_buffer.cpp
			${CENGINE_SRCDIR}/renderer/command_buffer.h
			${CENGINE_SRCDIR}/renderer/gl_cache.cpp
			${CENGINE_SRCDIR}/renderer/gl_cache.h
			${CENGINE_SRCDIR}/renderer/MaterialLibrary.cpp
			${CENGINE_SRCDIR}/renderer/MaterialLibrary.h
			${CENGINE_SRCDIR}/renderer/PBR.cpp
			${CENGINE_SRCDIR}/renderer/PBR.h
			${CENGINE_SRCDIR}/renderer/pbr_capture.cpp
			${CENGINE_SRCDIR}/renderer/pbr_capture.h
			${CENGINE_SRCDIR}/renderer/PostProcessor.cpp
			${CENGINE_SRCDIR}/renderer/PostProcessor.h
			${CENGINE_SRCDIR}/renderer/render_target.cpp
			${CENGINE_SRCDIR}/renderer/render_target.h
			${CENGINE_SRCDIR}/renderer/renderer.cpp
			${CENGINE_SRCDIR}/renderer/renderer.h
			
			${CENGINE_SRCDIR}/resources/mesh_loader.cpp
			${CENGINE_SRCDIR}/resources/mesh_loader.h
			${CENGINE_SRCDIR}/resources/resources.cpp
			${CENGINE_SRCDIR}/resources/resources.h
			${CENGINE_SRCDIR}/resources/shader_loader.cpp
			${CENGINE_SRCDIR}/resources/shader_loader.h
			${CENGINE_SRCDIR}/resources/texture_loader.cpp
			${CENGINE_SRCDIR}/resources/texture_loader.h
			
			${CENGINE_SRCDIR}/scene/background.cpp
			${CENGINE_SRCDIR}/scene/background.h
			${CENGINE_SRCDIR}/scene/scene.cpp
			${CENGINE_SRCDIR}/scene/scene.h
			${CENGINE_SRCDIR}/scene/scene_node.cpp
			${CENGINE_SRCDIR}/scene/scene_node.h
			
			${CENGINE_SRCDIR}/shading/material.cpp
			${CENGINE_SRCDIR}/shading/material.h
			${CENGINE_SRCDIR}/shading/shader.cpp
			${CENGINE_SRCDIR}/shading/shader.h
			${CENGINE_SRCDIR}/shading/Texture.cpp
			${CENGINE_SRCDIR}/shading/Texture.h
			${CENGINE_SRCDIR}/shading/texture_cube.cpp
			${CENGINE_SRCDIR}/shading/texture_cube.h
			${CENGINE_SRCDIR}/shading/shading_types.h
			${CENGINE_SRCDIR}/shading/shaderUniform.h	
			
			${CENGINE_SRCDIR}/stb/stb_image.cpp
			${CENGINE_SRCDIR}/stb/stb_image.h
			
			
			${CENGINE_SRCDIR}/fg/framegraph.hpp
			${CENGINE_SRCDIR}/fg/realize.hpp
			${CENGINE_SRCDIR}/fg/render_task.hpp
			${CENGINE_SRCDIR}/fg/render_task_base.hpp
			${CENGINE_SRCDIR}/fg/render_task_builder.hpp
			${CENGINE_SRCDIR}/fg/resource.hpp
			${CENGINE_SRCDIR}/fg/resource_base.hpp
			
			${CENGINE_SRCDIR}/math/cmath.h
			${CENGINE_SRCDIR}/math/common.h
			${CENGINE_SRCDIR}/math/geometry/cube.h
			${CENGINE_SRCDIR}/math/geometry/rectangle.h
			${CENGINE_SRCDIR}/math/geometry/plane.h
            ${CENGINE_SRCDIR}/math/geometry/plane.cpp
			
			${CENGINE_SRCDIR}/math/trigonometry/polar.h
            ${CENGINE_SRCDIR}/math/trigonometry/polar.cpp
			${CENGINE_SRCDIR}/math/trigonometry/spherical.h
            ${CENGINE_SRCDIR}/math/trigonometry/spherical.cpp
			${CENGINE_SRCDIR}/math/trigonometry/conversions.h
			${CENGINE_SRCDIR}/math/linear_algebra/vmath.h
			${CENGINE_SRCDIR}/math/linear_algebra/vmath.cpp
			
			  ${CENGINE_SRCDIR}/utility/logging/log.cpp
			${CENGINE_SRCDIR}/utility/logging/log.h
			
            ${CENGINE_SRCDIR}/utility/random/random.cpp
			${CENGINE_SRCDIR}/utility/random/random.h
			
			${CENGINE_SRCDIR}/utility/timing/diagnostics.h
			${CENGINE_SRCDIR}/utility/floating_point.h
			${CENGINE_SRCDIR}/utility/std_types.h
			${CENGINE_SRCDIR}/utility/string_id.h
)
source_group(TREE ${CENGINE_SRCDIR} FILES ${CENGINE_SRCS})

    add_library( cengine STATIC 
	${CENGINE_SRCS}
	)


