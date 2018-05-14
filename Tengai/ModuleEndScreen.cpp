#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleStartScreen.h"
#include "ModulePlayer2.h"
#include "ModuleSceneForest.h"
#include "ModulePlayer.h"
#include "ModuleEndScreen.h"

ModuleEndScreen::ModuleEndScreen() 
{
	outro = { 0,0,320,224 };

}

ModuleEndScreen::~ModuleEndScreen()
{}

bool ModuleEndScreen::Start() {

	LOG("Loading End Screen");
	App->scene_forest->Disable();
	App->player->Disable();
	App->player2->Disable();
	screen_outro = App->textures->Load("assets/sprites/outro.png");
	
	return true;
}

/*bool ModuleEndScreen::Init() {
	bool ret = true;
	return ret;

}*/

update_status ModuleEndScreen::Update() {
	
	App->render->Blit(screen_outro, 0, 0, &outro);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) App->fade->FadeToBlack(this, App->intro, 2);

	return update_status::UPDATE_CONTINUE;
}


bool ModuleEndScreen::CleanUp()
{
	//Unloading textures
	App->textures->Unload(screen_outro);
	screen_outro = nullptr;

	//Unloading Audio
	/*App->audio->UnloadMusic(music);
	music = nullptr;
	*/
	return true;
}
