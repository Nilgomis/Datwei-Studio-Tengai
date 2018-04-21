#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleStartScreen.h"

ModuleStartScreen::ModuleStartScreen()
{}

ModuleStartScreen::~ModuleStartScreen()
{}

// Load assets
bool ModuleStartScreen::Start()
{
	LOG("Loading Temple intro");

	background = App->textures->Load("Assets/Sprites/UI/StartScreen/background.png");

	App->render->camera.x = App->render->camera.y = 0;

	return true;
}

// UnLoad assets
bool ModuleStartScreen::CleanUp()
{
	LOG("Unloading Temple scene");

	App->textures->Unload(background);

	return true;
}

// Update: draw background
update_status ModuleStartScreen::Update()
{
	App->render->Blit(background, 0, 0, NULL);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_DOWN && App->fade->IsFading() == false)
	{
		App->fade->FadeToBlack(this, (Module*)App->scene_temple);
	}

	return UPDATE_CONTINUE;
}