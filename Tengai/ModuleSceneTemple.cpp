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
//#include "ModuleBackground.h"
#include "ModuleFadeToBlack.h"


ModuleSceneTemple::ModuleSceneTemple()
{}

ModuleSceneTemple::~ModuleSceneTemple()
{}

// Load assets
bool ModuleSceneTemple::Start()
{
	LOG("Loading Temple scene");

	background = App->textures->Load("Assets/Sprites/Tile_temple.png");
	bg.x = 0;
	bg.y = 0;
	bg.w = 256;
	bg.h = 224;

	//App->background->Enable();
	App->player->Enable();
	App->player2->Enable();
	App->particles->Enable();
	App->collision->Enable();
	App->enemies->Enable();

	// Colliders ---
	//App->collision->AddCollider({ 0, 224, 3930, 16 }, COLLIDER_WALL);
	//App->collision->AddCollider({ 1375, 0, 111, 96 }, COLLIDER_WALL);
	//App->collision->AddCollider({ 1375, 145, 111, 96 }, COLLIDER_WALL);

	// Enemies ---
	App->enemies->AddEnemy(ENEMY_TYPES::DEMONWHEEL, 320, 70, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::DEMONWHEEL, 320, 110, 0.25f);
	App->enemies->AddEnemy(ENEMY_TYPES::DEMONWHEEL, 320, 150, 0.5f);
	App->enemies->AddEnemy(ENEMY_TYPES::DEMONWHEEL, 250, -32, 3);
	App->enemies->AddEnemy(ENEMY_TYPES::DEMONWHEEL, 250, 225, 3);
	App->enemies->AddEnemy(ENEMY_TYPES::DEMONWHEEL, 170, -64, 3);
	App->enemies->AddEnemy(ENEMY_TYPES::DEMONWHEEL, 170, 257, 3);
	App->enemies->AddEnemy(ENEMY_TYPES::DEMONWHEEL, 200, -81, 4);
	App->enemies->AddEnemy(ENEMY_TYPES::DEMONWHEEL, 200, 294, 4);
	App->enemies->AddEnemy(ENEMY_TYPES::DEMONWHEEL, 320, 110, 6);
	App->enemies->AddEnemy(ENEMY_TYPES::DEMONWHEEL, 350, 70, 6);
	App->enemies->AddEnemy(ENEMY_TYPES::DEMONWHEEL, 350, 150, 6);
	App->enemies->AddEnemy(ENEMY_TYPES::DEMONWHEEL, 340, 60, 8);
	App->enemies->AddEnemy(ENEMY_TYPES::DEMONWHEEL, 170, -32, 7);
	App->enemies->AddEnemy(ENEMY_TYPES::DEMONWHEEL, 170, 225, 7);
	App->enemies->AddEnemy(ENEMY_TYPES::DEMONWHEEL, 335, 110, 8);
	App->enemies->AddEnemy(ENEMY_TYPES::DEMONWHEEL, 340, 160, 8);
	App->enemies->AddEnemy(ENEMY_TYPES::DEMONWHEEL, 320, 150, 11);
	App->enemies->AddEnemy(ENEMY_TYPES::DEMONWHEEL, 320, 110, 12);
	App->enemies->AddEnemy(ENEMY_TYPES::DEMONWHEEL, 320, 70, 13);
	App->enemies->AddEnemy(ENEMY_TYPES::DEMONWHEEL, 320, 50, 15);
	App->enemies->AddEnemy(ENEMY_TYPES::DEMONWHEEL, 320, 80, 16);
	App->enemies->AddEnemy(ENEMY_TYPES::DEMONWHEEL, 320, 140, 17);
	App->enemies->AddEnemy(ENEMY_TYPES::DEMONWHEEL, 320, 170, 18);
	App->enemies->AddEnemy(ENEMY_TYPES::DEMONWHEEL, 250, -32, 20);
	App->enemies->AddEnemy(ENEMY_TYPES::DEMONWHEEL, 250, 225, 20);
	App->enemies->AddEnemy(ENEMY_TYPES::DEMONWHEEL, 170, -64, 20);
	App->enemies->AddEnemy(ENEMY_TYPES::DEMONWHEEL, 170, 257, 20);
	App->enemies->AddEnemy(ENEMY_TYPES::DEMONWHEEL, 200, -81, 22);
	App->enemies->AddEnemy(ENEMY_TYPES::DEMONWHEEL, 200, 294, 22);
	App->enemies->AddEnemy(ENEMY_TYPES::DEMONWHEEL, 200, -81, 25);
	App->enemies->AddEnemy(ENEMY_TYPES::DEMONWHEEL, 200, 294, 25);

	//App->enemies->AddEnemy(ENEMY_TYPES::PEGTOP, 600, 80,100);
	//App->enemies->AddEnemy(ENEMY_TYPES::PEGTOP, 625, 80, 100);
	//App->enemies->AddEnemy(ENEMY_TYPES::PEGTOP, 640, 80, 100);
	//App->enemies->AddEnemy(ENEMY_TYPES::PEGTOP, 665, 80, 100);

	frameTime = 0;
	t2 = 0;
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
	App->enemies->Disable();
	//App->background->Disable();

	return true;
}

float ModuleSceneTemple::Time()
{
	return timer;
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

	//Increase the timer which serves to spawn enemies
	frameTime++;
	timer =frameTime/60.000000000f;
	LOG("%f, %f", frameTime,timer);

	// Draw everything --------------------------------------
	App->render->Blit(background, bgXpos, 0, &bg);
	App->render->Blit(background, bgXpos2, 0, &bg);
	App->render->Blit(background, bgXpos3, 0, &bg);

	if (timer > 30) {
		App->fade->FadeToBlack(this, (Module*)App->end_screen, 2); 
	}

	return UPDATE_CONTINUE;
}