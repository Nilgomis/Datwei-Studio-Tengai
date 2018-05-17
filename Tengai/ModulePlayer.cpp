#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "SDL_mixer\include\SDL_mixer.h"
#include "SDL\include\SDL_gamecontroller.h"
#include "SDL\include\SDL.h"



ModulePlayer::ModulePlayer()
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

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	position.x = SCREEN_WIDTH-startx;
	position.y = SCREEN_HEIGHT-starty;
	destroyed = false;

	player = App->textures->Load("Assets/Sprites/Characters/Junis/Junis_Spritesheet.png");
	col = App->collision->AddCollider({ position.x,position.y,30,28 }, COLLIDER_PLAYER, this);
	attack = App->audio->LoadEffect("Assets/Audio/OGG/Effects/Junis/basic-attack.ogg");

	bool shooting = false;
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(player);
	if (col != nullptr)
		col->to_delete = true;

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	Animation* current_animation = &idle;

	float speed = 2.5f;
	cooldown -= 0.04f;

	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &forward;
			position.x += speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &backward;
			position.x -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &forward;
			position.y -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &forward;
			position.y += speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &backward;

	}
	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &backward;

	}
	col->SetPos(position.x, position.y);

	// Shooting

	if ((App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && cooldown <= 0.0f) || (App->input->controller[BUTTON_A] == KEY_STATE::KEY_DOWN && cooldown <= 0.0f))
	{
		Mix_PlayChannel(-1, attack, 0);
		App->particles->AddParticle(App->particles->junishot, position.x + 20, position.y + 10, COLLIDER_PLAYER_SHOT);
	}

	// Shooting Gamepad
	/*if (SDL_GameControllerGetButton(App->input->gamepad, SDL_CONTROLLER_BUTTON_A) && A == false)
	{
		App->particles->AddParticle(App->particles->junishot, position.x + 20, position.y + 10, COLLIDER_PLAYER_SHOT);
		A = true;
	}

	if (SDL_GameControllerGetButton(App->input->gamepad, SDL_CONTROLLER_BUTTON_A) == false)
	{
		A = false;
	}*/

	// Draw everything

	if (destroyed == false)
		App->render->Blit(player, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == col && destroyed == false && App->fade->IsFading() == false)
	{
		App->fade->FadeToBlack((Module*)App->scene_forest, (Module*)App->intro);

		App->particles->AddParticle(App->particles->explosion, position.x, position.y, COLLIDER_NONE, 150);
		App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, COLLIDER_NONE, 220);
		App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, COLLIDER_NONE, 670);
		App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, COLLIDER_NONE, 480);
		App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, COLLIDER_NONE, 350);

		destroyed = true;
	}
}