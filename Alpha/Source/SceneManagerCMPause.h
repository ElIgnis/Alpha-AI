#ifndef SCENE_MANAGER_CM_PAUSE_H
#define SCENE_MANAGER_CM_PAUSE_H

#include "SceneManagerSelection.h"

class SceneManagerCMPause : public SceneManagerSelection
{
public:
	SceneManagerCMPause();
	~SceneManagerCMPause();

	void Init(const int width, const int height, ResourcePool* RP, InputManager* controls);
	void Update(double dt);
	void Render();
	void Exit();

	void BindShaders();
	void InitShader();
	void InitLight();
	void InitCamera();

	void UpdateSelection();

	void RenderLight();
	void RenderBG();
	void RenderStaticObject();
	void RenderMobileObject();
};

#endif