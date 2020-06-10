#ifndef CELL_FILE_MANAGER_H
#define CELL_FILE_MANAGER_H
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
namespace Cell
{
#define SHADER_PATH "../resources/shaders/"
#define MESH_PAHT "../resources/meshes/"
#define TEXTURE_PAHT "../resources/textures/"
#define RESOURCE_PATH "../resources/"

	const std::string vs_post_process = SHADER_PATH+std::string("screen_quad.vs");
	const std::string ps_post_process = SHADER_PATH + std::string("post_processing.Fs");

	const std::string vs_down_sample = SHADER_PATH + std::string("screen_quad.vs");
	const std::string ps_down_sample = SHADER_PATH + std::string("post/down_sample.fs");

	const std::string vs_gaussian_blur = SHADER_PATH + std::string("screen_quad.vs");
	const std::string ps_gaussian_blur = SHADER_PATH + std::string("post/blur_guassian.fs");

	const std::string vs_ssao = SHADER_PATH + std::string("screen_quad.vs");
	const std::string ps_ssao = SHADER_PATH + std::string("post/ssao.fs");

	const std::string vs_bloonm = SHADER_PATH + std::string("screen_quad.vs");
	const std::string ps_bloonm = SHADER_PATH + std::string("post/bloom.fs");

	const std::string vs_pbr = SHADER_PATH + std::string("pbr.vs");
	const std::string ps_pbr = SHADER_PATH + std::string("pbr.frag");

	const std::string vs_background = SHADER_PATH + std::string("background.vs");
	const std::string ps_background = SHADER_PATH + std::string("background.fs");

	const std::string vs_default = SHADER_PATH + std::string("deferred/g_buffer.vs");
	const std::string ps_default = SHADER_PATH + std::string("deferred/g_buffer.fs");

	const std::string vs_deferred_ambient = SHADER_PATH + std::string("deferred/screen_ambient.vs");
	const std::string ps_deferred_ambient = SHADER_PATH + std::string("deferred/ambient.fs");

	const std::string vs_deferred_irradiance = SHADER_PATH + std::string("deferred/ambient_irradience.vs");
	const std::string ps_deferred_irradiance = SHADER_PATH + std::string("deferred/ambient_irradience.fs");

	const std::string vs_deferred_directional = SHADER_PATH + std::string("deferred/screen_directional.vs");
	const std::string ps_deferred_directional = SHADER_PATH + std::string("deferred/directional.fs");

	const std::string vs_deferred_point = SHADER_PATH + std::string("deferred/point.vs");
	const std::string ps_deferred_point = SHADER_PATH + std::string("deferred/point.fs");

	const std::string vs_alpha_blend = SHADER_PATH + std::string("forward_render.vs");
	const std::string ps_alpha_blend = SHADER_PATH + std::string("forward_render.fs");

	const std::string vs_blit = SHADER_PATH + std::string("screen_quad.vs");
	const std::string ps_blit = SHADER_PATH + std::string("default_blit.fs");

	const std::string vs_shadow_directional = SHADER_PATH + std::string("shadow_cast.vs");
	const std::string ps_shadow_directional = SHADER_PATH + std::string("shadow_cast.fs");

	const std::string vs_debug_light = SHADER_PATH + std::string("light.vs");
	const std::string ps_debug_light = SHADER_PATH + std::string("light.fs");

	//pbr
	const std::string vs_hdr_to_cubemap = SHADER_PATH + std::string("pbr/cube_sample.vs");
	const std::string ps_hdr_to_cubemap = SHADER_PATH + std::string("pbr/spherical_to_cube.fs");

	const std::string vs_pbr_irradiance = SHADER_PATH + std::string("pbr/cube_sample.vs");
	const std::string ps_pbr_irradiance = SHADER_PATH + std::string("pbr/irradiance_capture.fs");

	const std::string vs_pbr_prefilter = SHADER_PATH + std::string("pbr/cube_sample.vs");
	const std::string ps_pbr_prefilter = SHADER_PATH + std::string("pbr/prefilter_capture.fs");

	const std::string vs_integrate_brdf = SHADER_PATH + std::string("screen_quad.vs");
	const std::string ps_integrate_brdf = SHADER_PATH + std::string("pbr/integrate_brdf.fs");

	const std::string vs_pbr_capture = SHADER_PATH + std::string("capture.vs");
	const std::string ps_pbr_capture = SHADER_PATH + std::string("capture.fs");

	const std::string vs_pbr_capture_background = SHADER_PATH + std::string("capture_background.vs");
	const std::string ps_pbr_capture_background = SHADER_PATH + std::string("capture_background.fs");

	const std::string vs_pbr_probe_render = SHADER_PATH + std::string("pbr/probe_render.vs");
	const std::string ps_pbr_probe_render = SHADER_PATH + std::string("pbr/probe_render.fs");

	const std::string vs_plasma_orb = SHADER_PATH + std::string("custom/plasma_orb.vs");
	const std::string ps_plasma_orb = SHADER_PATH + std::string("custom/plasma_orb.fs");

	const std::string vs_postprocessing1 = SHADER_PATH + std::string("screen_quad.vs");
	const std::string ps_postprocessing1 = SHADER_PATH + std::string("custom_post_1.fs");

	const std::string vs_postprocessing2 = SHADER_PATH + std::string("screen_quad.vs");
	const std::string ps_postprocessing2 = SHADER_PATH + std::string("custom_post_2.fs");

	class FileUtil
	{
	public:
		static std::string readFileAsFString(const std::string &filePath)
		{
			std::string path = RESOURCE_PATH + filePath;
			std::fstream file(path.c_str(), std::ios::in | std::ios::binary);
			std::stringstream sstream;

			sstream << file.rdbuf();
			file.close();

			std::string str(sstream.str());
			sstream.clear();

			return str;
		}
	};
}
#endif