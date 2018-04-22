#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
//#include "ModuleAudio.h"
#include "ModuleSceneTemple.h"
#include "ModuleStartScreen.h"
#include "ModuleBackground.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleFont.h"

Application::Application()
{
	int i = 0;
	modules[i++] = window			= new ModuleWindow();
	modules[i++] = render			= new ModuleRender();
	modules[i++] = input			= new ModuleInput();
	modules[i++] = textures			= new ModuleTextures();
	//modules[i++] = audio			= new ModuleAudio();
	modules[i++] = intro			= new ModuleStartScreen();
	modules[i++] = scene_temple		= new ModuleSceneTemple();
	modules[i++] = enemies			= new ModuleEnemies();
	modules[i++] = player			= new ModulePlayer();
	modules[i++] = player2			= new ModulePlayer2();
	modules[i++] = particles		= new ModuleParticles();
	modules[i++] = collision		= new ModuleCollision();
	modules[i++] = font				= new ModuleFont();
	modules[i++] = fade				= new ModuleFadeToBlack();
	modules[i++] = background		= new ModuleBackground();
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
	player2->Disable();
	collision->Disable();
	background->Disable();
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