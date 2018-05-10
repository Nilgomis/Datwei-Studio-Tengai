#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer2.h"


ModulePlayer2::ModulePlayer2()
{

	// idle animation									// JUNIS ANIMATION
	idle.PushBack({ 4, 0, 28, 26 });
	idle.PushBack({ 46, 1, 28, 27 });
	idle.PushBack({ 89, 1, 28, 27 });

	idle.speed = 0.2f;


	forward.PushBack({ 4, 0, 28, 26 });
	forward.PushBack({ 46, 1, 28, 27 });
	forward.PushBack({ 89, 1, 28, 27 });

	forward.speed = 0.2f;

	backward.PushBack({ 0, 36, 26, 24 });
	backward.PushBack({ 41, 35, 20, 27 });
	backward.PushBack({ 79, 33, 17, 29 });
	backward.loop = false;
	backward.speed = 0.2f;

	/*// idle animation									// SHO ANIMATION
	idle.PushBack({ 36, 8, 30, 28 });
	idle.PushBack({ 73, 8, 30, 28 });
	idle.PushBack({ 110, 9, 30, 28 });
	idle.speed = 0.2f;
	forward.PushBack({ 36, 8, 30, 28 });
	forward.PushBack({ 73, 8, 30, 28 });
	forward.PushBack({ 110, 9, 30, 28 });
	forward.loop = false;
	forward.speed = 0.2f;
	backward.PushBack({ 181, 8, 23, 28 });
	backward.PushBack({ 147, 8, 25, 28 });
	backward.loop = false;
	backward.speed = 0.2f;*/

}

ModulePlayer2::~ModulePlayer2()
{}

// Load assets
bool ModulePlayer2::Start()
{
	LOG("Loading player textures");
	position.x = 25;
	position.y = 95;
	bool ret = true;
	destroyed = false;
	player2 = App->textures->Load("Assets/Sprites/Characters/Junis/Junis_Spritesheet.png");
	col = App->collision->AddCollider({ position.x,position.y,30,28 }, COLLIDER_PLAYER, this);
	return ret;
}

// Unload assets
bool ModulePlayer2::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(player2);
	if (col != nullptr)
		col->to_delete = true;

	return true;
}

// Update: draw background
update_status ModulePlayer2::Update()
{
	Animation* current_animation = &idle;

	float speed = 2.5f;
	cooldown -= 0.04f;

	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &forward;
		if (position.x < 270) {
			position.x += speed;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &backward;
		if (position.x > 0) {
			position.x -= speed;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &backward;
		if (position.y > 20) {
			position.y -= speed;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &forward;
		if (position.y < 192) {
			position.y += speed;
		}
	}
	// Shooting
	if (App->input->keyboard[SDL_SCANCODE_KP_0] == KEY_STATE::KEY_DOWN && cooldown <= 0.0f)
	{
		App->particles->AddParticle(App->particles->junishot, position.x + 20, position.y + 10, COLLIDER_PLAYER_SHOT);
	}
	col->SetPos(position.x, position.y);

	// SHooting gamepad
	if (SDL_GameControllerGetButton(App->input->gamepad2, SDL_CONTROLLER_BUTTON_A) && A2 == false)
	{
		App->particles->AddParticle(App->particles->junishot, position.x + 20, position.y + 10, COLLIDER_PLAYER_SHOT);
		A2 = true;
	}

	if (SDL_GameControllerGetButton(App->input->gamepad2, SDL_CONTROLLER_BUTTON_A) == false)
	{
		A2 = false;
	}

	// Draw everything

	if (destroyed == false)
		App->render->Blit(player2, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}

void ModulePlayer2::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == col && destroyed == false && App->fade->IsFading() == false)
	{
		App->fade->FadeToBlack((Module*)App->scene_temple, (Module*)App->intro);

		App->particles->AddParticle(App->particles->explosion, position.x, position.y, COLLIDER_NONE, 150);
		App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, COLLIDER_NONE, 220);
		App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, COLLIDER_NONE, 670);
		App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, COLLIDER_NONE, 480);
		App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, COLLIDER_NONE, 350);

		destroyed = true;
	}
}