﻿#include <iostream>
#include <windows.h>
#include <fstream>
#include <gamemachine.h>
#include <gmgl.h>
#include <gmdx11.h>
#include <gmui.h>
#include <gmm.h>
#include "demostration_world.h"

namespace
{
	gm::GMRenderEnvironment s_env = gm::GMRenderEnvironment::DirectX11;
}

gm::GMRenderEnvironment GetRenderEnv()
{
	return s_env;
}

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	char * lpCmdLine,
	int nCmdShow
)
{
	gm::IFactory* factory = nullptr;
	if (GetRenderEnv() == gm::GMRenderEnvironment::OpenGL)
	{
		factory = new gm::GMGLFactory();
	}
	else
	{
#if GM_USE_DX11
		if (gm::GMQueryCapability(gm::GMCapability::SupportDirectX11))
			factory = new gm::GMDX11Factory();
		else
			factory = new gm::GMGLFactory();
#else
		SetRenderEnv(gm::GMRenderEnvironment::OpenGL);
		factory = new gm::GMGLFactory();
#endif
	}

	gm::GMWindowAttributes mainAttrs;
	mainAttrs.instance = hInstance;

	gm::IWindow* mainWindow = nullptr;
	gmui::GMUIFactory::createMainWindow(hInstance, &mainWindow, GetRenderEnv());
	mainWindow->create(mainAttrs);

	gm::GMWindowAttributes consoleAttrs;
	consoleAttrs.windowName = L"GameMachineConsoleWindow";
	consoleAttrs.dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_THICKFRAME | WS_SYSMENU;
	consoleAttrs.dwExStyle = WS_EX_CLIENTEDGE;
	consoleAttrs.rc.right = 700;
	consoleAttrs.rc.bottom = 400;

	gm::GMConsoleHandle consoleHandle;
	gmui::GMUIFactory::createConsoleWindow(hInstance, consoleHandle);
	if (consoleHandle.window)
		consoleHandle.window->create(consoleAttrs);

	GM.init(
		mainWindow,
		consoleHandle,
		factory,
		new DemostrationEntrance(),
		GetRenderEnv()
	);

	GM.startGameMachine();
	return 0;
}