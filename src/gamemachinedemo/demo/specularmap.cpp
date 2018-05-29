﻿#include "stdafx.h"
#include "specularmap.h"
#include <linearmath.h>
#include <gmmodelreader.h>
#include <gmimagebuffer.h>

#ifndef WHEEL_DELTA
#define WHEEL_DELTA 120
#endif

namespace
{
	const gm::GMCameraLookAt s_lookAt = gm::GMCameraLookAt(
		GMVec3(0, -.2f, 1),
		GMVec3(0, .2f, 0)
	);
}

void Demo_SpecularMap::setLookAt()
{
	D(d);
	gm::GMCamera& camera = GM.getCamera();
	camera.setPerspective(Radians(75.f), 1.333f, .1f, 3200);
	camera.lookAt(s_lookAt);
	d->lookAtRotation = Identity<GMQuat>();
}

void Demo_SpecularMap::init()
{
	D(d);
	Base::init();

	// 创建对象
	getDemoWorldReference() = new gm::GMDemoGameWorld();

	{
		gm::ITexture* texture = nullptr;
		gm::GMToolUtil::createTexture("cube_diffuse.png", &texture);
		getDemoWorldReference()->getAssets().insertAsset(gm::GMAssetType::Texture, texture);

		gm::GMModel* cube = nullptr;
		gm::GMPrimitiveCreator::createCube(gm::GMPrimitiveCreator::one3(), &cube);

		gm::GMShader& shader = cube->getShader();
		shader.getMaterial().ks = GMVec3(1);
		shader.getMaterial().kd = GMVec3(1);
		shader.getMaterial().shininess = 99;
		gm::GMToolUtil::addTextureToShader(shader, texture, gm::GMTextureType::Diffuse);

		gm::GMToolUtil::createTexture("cube_specular.png", &texture);
		getDemoWorldReference()->getAssets().insertAsset(gm::GMAssetType::Texture, texture);
		gm::GMToolUtil::addTextureToShader(shader, texture, gm::GMTextureType::Specular);

		gm::GMAsset asset = getDemoWorldReference()->getAssets().insertAsset(gm::GMAssetType::Model, cube);
		d->gameObject = new gm::GMGameObject(asset);
		d->gameObject->setTranslation(Translate(GMVec3(-.2f, 0, .5f)));
		d->gameObject->setScaling(Scale(GMVec3(.1f, .1f, .1f)));
		d->gameObject->setRotation(Rotate(PI, GMVec3(0, 1, 0)));
	}

	{
		gm::ITexture* texture = nullptr;
		gm::GMToolUtil::createTexture("cube_diffuse.png", &texture);
		getDemoWorldReference()->getAssets().insertAsset(gm::GMAssetType::Texture, texture);

		gm::GMModel* cube = nullptr;
		gm::GMPrimitiveCreator::createCube(gm::GMPrimitiveCreator::one3(), &cube);

		gm::GMShader& shader = cube->getShader();
		shader.getMaterial().ks = GMVec3(1);
		shader.getMaterial().kd = GMVec3(1);
		shader.getMaterial().shininess = 99;
		gm::GMToolUtil::addTextureToShader(shader, texture, gm::GMTextureType::Diffuse);

		gm::GMAsset asset = getDemoWorldReference()->getAssets().insertAsset(gm::GMAssetType::Model, cube);
		d->gameObject2 = new gm::GMGameObject(asset);
		d->gameObject2->setTranslation(Translate(GMVec3(.2f, 0, .5f)));
		d->gameObject2->setScaling(Scale(GMVec3(.1f, .1f, .1f)));
		d->gameObject2->setRotation(Rotate(PI, GMVec3(0, 1, 0)));
	}

	asDemoGameWorld(getDemoWorldReference())->addObject("cube with specular map", d->gameObject);
	asDemoGameWorld(getDemoWorldReference())->addObject("cube without specular map", d->gameObject2);
}

void Demo_SpecularMap::handleMouseEvent()
{
	D(d);
	gm::IMouseState& ms = GM.getMainWindow()->getInputMananger()->getMouseState();
	gm::GMMouseState state = ms.mouseState();
	if (state.wheel.wheeled)
	{
		gm::GMfloat delta = .001f * state.wheel.delta / WHEEL_DELTA;
		GMFloat4 scaling;
		{
			GetScalingFromMatrix(d->gameObject->getScaling(), scaling);
			scaling[0] += delta;
			scaling[1] += delta;
			scaling[2] += delta;
			if (scaling[0] > 0 && scaling[1] > 0 && scaling[2] > 0)
			{
				d->gameObject->setScaling(Scale(GMVec3(scaling[0], scaling[1], scaling[2])));
				d->gameObject2->setScaling(Scale(GMVec3(scaling[0], scaling[1], scaling[2])));
			}
		}
	}

	if (state.downButton & gm::GMMouseButton_Left)
	{
		d->mouseDownX = state.posX;
		d->mouseDownY = state.posY;
		d->draggingL = true;
		GM.getMainWindow()->setLockWindow(true);
	}
	else if (state.upButton & gm::GMMouseButton_Left)
	{
		d->draggingL = false;
		GM.getMainWindow()->setLockWindow(false);
	}
	if (state.downButton & gm::GMMouseButton_Right)
	{
		d->mouseDownX = state.posX;
		d->mouseDownY = state.posY;
		d->draggingR = true;
		GM.getMainWindow()->setLockWindow(true);
	}
	else if (state.upButton & gm::GMMouseButton_Right)
	{
		d->draggingR = false;
		GM.getMainWindow()->setLockWindow(false);
	}
}

void Demo_SpecularMap::handleDragging()
{
	D(d);
	gm::IMouseState& ms = GM.getMainWindow()->getInputMananger()->getMouseState();
	gm::GMMouseState state = ms.mouseState();

	if (d->draggingL)
	{
		gm::GMfloat rotateX = d->mouseDownX - state.posX;

		GMQuat q = Rotate(d->gameObject->getRotation(),
			PI * rotateX / GM.getGameMachineRunningStates().renderRect.width,
			GMVec3(0, 1, 0));
		d->gameObject->setRotation(q);
		d->gameObject2->setRotation(q);

		d->mouseDownX = state.posX;
		d->mouseDownY = state.posY;
	}
	else if (d->draggingR)
	{
		gm::GMfloat rotateX = d->mouseDownX - state.posX;
		gm::GMfloat rotateY = d->mouseDownY - state.posY;
		GMVec3 lookAt3 = Normalize(s_lookAt.lookAt);
		GMVec4 lookAt = GMVec4(lookAt3, 1.f);
		GMQuat q = Rotate(d->lookAtRotation,
			PI * rotateX / GM.getGameMachineRunningStates().renderRect.width,
			GMVec3(0, 1, 0));
		d->lookAtRotation = q;
		q = Rotate(d->lookAtRotation,
			PI * rotateY / GM.getGameMachineRunningStates().renderRect.width,
			GMVec3(1, 0, 0));
		d->lookAtRotation = q;
		gm::GMCameraLookAt cameraLookAt = {
			GMVec4(s_lookAt.lookAt, 1.f) * QuatToMatrix(q),
			s_lookAt.position
		};
		GM.getCamera().lookAt(cameraLookAt);
		d->mouseDownX = state.posX;
		d->mouseDownY = state.posY;
	}
}

void Demo_SpecularMap::setDefaultLights()
{
	D(d);
	if (isInited())
	{
		gm::ILight* light = nullptr;
		GM.getFactory()->createLight(gm::GMLightType::Direct, &light);
		GM_ASSERT(light);
		gm::GMfloat lightPos[] = { 0, 0, 0 };
		light->setLightPosition(lightPos);
		gm::GMfloat color[] = { 1, 1, 1 };
		light->setLightColor(color);
		GM.getGraphicEngine()->addLight(light);
	}
}

void Demo_SpecularMap::event(gm::GameMachineHandlerEvent evt)
{
	D_BASE(db, Base);
	D(d);
	Base::event(evt);
	switch (evt)
	{
	case gm::GameMachineHandlerEvent::FrameStart:
		break;
	case gm::GameMachineHandlerEvent::FrameEnd:
		break;
	case gm::GameMachineHandlerEvent::Simulate:
		getDemoWorldReference()->simulateGameWorld();
		break;
	case gm::GameMachineHandlerEvent::Render:
		getDemoWorldReference()->renderScene();
		break;
	case gm::GameMachineHandlerEvent::Activate:
	{
		handleMouseEvent();
		handleDragging();

		gm::IInput* inputManager = GM.getMainWindow()->getInputMananger();
		gm::IKeyboardState& kbState = inputManager->getKeyboardState();
		if (kbState.keyTriggered('N'))
			switchNormal();

		break;
	}
	case gm::GameMachineHandlerEvent::Deactivate:
		break;
	case gm::GameMachineHandlerEvent::Terminate:
		break;
	default:
		break;
	}
}
