#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleEnemies.h"
#include "ModuleStartScreen.h"
#include "ModuleSceneTemple.h"
#include "ModuleBackground.h"


ModuleSceneTemple::ModuleSceneTemple()
{}

ModuleSceneTemple::~ModuleSceneTemple()
{}

// Load assets
bool ModuleSceneTemple::Start()
{
	LOG("Loading Temple scene");

	background = App->textures->Load("Assets/Sprites/Tile_temple.png");
	background2 = App->textures->Load("Assets/Sprites/Tile_temple.png");
	background3 = App->textures->Load("Assets/Sprites/Tile_temple.png");
	bg.x = 0;
	bg.y = 0;
	bg.w = 256;
	bg.h = 224;

	//App->background->Enable();
	App->player->Enable();
	App->player2->Enable();
	App->particles->Enable();
	App->collision->Enable();

	

	// Enemies ---
	App->enemies->AddEnemy(ENEMY_TYPES::DEMONWHEEL, 600, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::DEMONWHEEL, 625, 80 );
	App->enemies->AddEnemy(ENEMY_TYPES::DEMONWHEEL, 640, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::DEMONWHEEL, 665, 80);

	App->enemies->AddEnemy(ENEMY_TYPES::PEGTOP, 600, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::PEGTOP, 625, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::PEGTOP, 640, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::PEGTOP, 665, 80);

	//Mix_PlayMusic(scene_temple, -1);

	return true;
}

// UnLoad assets
bool ModuleSceneTemple::CleanUp()
{
	LOG("Unloading Temple scene");

	App->textures->Unload(background);

	App->collision->Disable();
	App->particles->Disable();
	App->player->Disable();
	App->player2->Disable();
	//App->background->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneTemple::Update()
{
	// Move camera forward -----------------------------
	//App->render->camera.x += 1 * SCREEN_SIZE;

	//Repeating backgrounds logic
	bgXpos -=0.5f;
	bgXpos2 -= 0.5f;
	bgXpos3 -= 0.5f;
	if (bgXpos <= -256) {
		bgXpos = 512;
	}
	if (bgXpos2 <= -256) {
		bgXpos2 = 512;
	}
	if (bgXpos3 <= -256) {
		bgXpos3 = 512;
	}

	// Draw everything --------------------------------------
	App->render->Blit(background, bgXpos, 0, &bg);
	App->render->Blit(background2, bgXpos2, 0, &bg);
	App->render->Blit(background3, bgXpos3, 0, &bg);

	return UPDATE_CONTINUE;
}