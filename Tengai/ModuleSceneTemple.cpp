#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
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

	// Colliders ---
	App->collision->AddCollider({ 0, 224, 3930, 16 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1375, 0, 111, 96 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1375, 145, 111, 96 }, COLLIDER_WALL);

	// Enemies ---
	App->enemies->AddEnemy(ENEMY_TYPES::FIREWHEEL, 600, 80, 10);
	App->enemies->AddEnemy(ENEMY_TYPES::FIREWHEEL, 625, 80, 20);
	App->enemies->AddEnemy(ENEMY_TYPES::FIREWHEEL, 640, 80, 30);
	App->enemies->AddEnemy(ENEMY_TYPES::FIREWHEEL, 665, 80, 40);

	App->enemies->AddEnemy(ENEMY_TYPES::PEGTOP, 600, 80, 10);
	App->enemies->AddEnemy(ENEMY_TYPES::PEGTOP, 625, 80, 20);
	App->enemies->AddEnemy(ENEMY_TYPES::PEGTOP, 640, 80, 30);
	App->enemies->AddEnemy(ENEMY_TYPES::PEGTOP, 665, 80, 40);
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