#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleSceneTemple.h"
#include "ModuleStartScreen.h"
//#include "ModuleBackground.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleFonts.h"


Application::Application()
{
	modules[0] = window			= new ModuleWindow();
	modules[1] = render			= new ModuleRender();
	modules[2] = input			= new ModuleInput();
	modules[3] = textures		= new ModuleTextures();
	modules[4] = fonts			= new ModuleFonts();
	modules[5] = intro			= new ModuleStartScreen();
	modules[6] = scene_temple	= new ModuleSceneTemple();
	modules[7] = enemies		= new ModuleEnemies();
	//modules[7] = background		= new ModuleBackground();
	modules[8] = player			= new ModulePlayer();
	modules[9] = particles		= new ModuleParticles();
	modules[10] = collision		= new ModuleCollision();
	modules[11] = fade			= new ModuleFadeToBlack();
}	

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;

	// disables stopped modules
	scene_temple->Disable();
	player->Disable();
	collision->Disable();
	enemies->Disable();
	//

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}