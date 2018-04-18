#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"

ModuleBackground::ModuleBackground()
{

	//sky
	background.x = 8;
	background.y = 24;
	background.w = 511;
	background.h = 785;
	
}

ModuleBackground::~ModuleBackground()
{}

// Load assets
bool ModuleBackground::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("background.png");
	return ret;
}

// Update: draw background
update_status ModuleBackground::Update()
{
	// Draw everything 
	App->render->Blit(graphics, 0, 0, &background, 0.75f);
	
	

	
	App->render->Blit(graphics, 0, 0, &sky);
	

	return UPDATE_CONTINUE;
}