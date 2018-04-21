#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"

ModuleBackground::ModuleBackground()
{

	//sky
	background.x = 0;
	background.y = 0;
	background.w = 320;
	background.h = 224;
	
}

ModuleBackground::~ModuleBackground()
{}

// Load assets
bool ModuleBackground::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("Sprites/UI/StartScreen/background.png");
	graphics2 = App->textures->Load("Sprites/UI/StartScreen/background.png");
	return ret;
}

// Update: draw background
update_status ModuleBackground::Update()
{
	// Draw everything
	bgXpos--;
	bgXpos2--;
	if (bgXpos <= -320) {
		bgXpos = 320;
	}
	if (bgXpos2 <= -320) {
		bgXpos2 = 320;
	}
	App->render->Blit(graphics, bgXpos, 0, &background, 0.75f);
	App->render->Blit(graphics2, bgXpos2, 0, &background, 0.75f);
	

	return UPDATE_CONTINUE;
}