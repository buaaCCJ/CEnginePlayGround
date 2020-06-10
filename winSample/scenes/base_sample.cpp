/**
 *Copyright © 2020 chenchengju. All rights reserved.
 *Filename:
 *Author: chenchengju
 *Data:
 *
 *Description：
 */
#include "base_sample.hpp"
GameEngineBaseApp* GameEngineBaseApp::mApp = nullptr;
GameEngineBaseApp * GameEngineBaseApp::GetApp()
{
	return mApp;
}

bool GameEngineBaseApp::Initialize()
{
	Log::Message("Initializing GLFW", LOG_INIT);
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
	glfwWindowHint(GLFW_RESIZABLE, true);

	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, _WinTitle.c_str(), nullptr, nullptr);
	if (window == nullptr)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

bool GameEngineBaseApp::InitRender()
{
	Log::Message("Initializing render system", LOG_INIT);
	renderer = Cell::Init(window, (GLADloadproc)glfwGetProcAddress);
	renderer->SetRenderSize(SCR_WIDTH, SCR_HEIGHT);
	renderer->SetCamera(&camera);
	Log::Message("Render system initialized", LOG_INIT);
	return true;
}

bool GameEngineBaseApp::SetUpCallBack(GLFWframebuffersizefun frameBufferFunc, GLFWkeyfun keyFunc, GLFWcursorposfun mousePosFunc, GLFWmousebuttonfun mouseButtonFunc, GLFWscrollfun mouseScrollFunc)
{
	// register callbacks
	glfwSetFramebufferSizeCallback(window, frameBufferFunc);
	glfwSetKeyCallback(window, keyFunc);
	glfwSetCursorPosCallback(window, mousePosFunc);
	glfwSetMouseButtonCallback(window, mouseButtonFunc);
	glfwSetScrollCallback(window, mouseScrollFunc);
}
