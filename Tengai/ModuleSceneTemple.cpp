#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleSceneTemple.h"


ModuleSceneTemple::ModuleSceneTemple()
{}

ModuleSceneTemple::~ModuleSceneTemple()
{}

// Load assets
bool ModuleSceneTemple::Start()
{
	LOG("Loading Temple scene");

	background = App->textures->Load("Assets/Sprites/UI/StartScreen/background.png");

	App->player->Enable();
	App->particles->Enable();
	App->collision->Enable();

	// Colliders ---
	App->collision->AddCollider({ 0, 224, 3930, 16 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1375, 0, 111, 96 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1375, 145, 111, 96 }, COLLIDER_WALL);

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

	return true;
}

// Update: draw background
update_status ModuleSceneTemple::Update()
{
	// Move camera forward -----------------------------
	//App->render->camera.x += 1 * SCREEN_SIZE;

	// Draw everything --------------------------------------
	App->render->Blit(background, 0, 0, NULL);

	return UPDATE_CONTINUE;
}