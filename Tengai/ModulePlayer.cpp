#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModulePlayer.h"

#include <stdio.h>


ModulePlayer::ModulePlayer()
{
	position.x = 50;
	position.y = 65;

	// idle animation 
	idle.PushBack({ 36, 8, 30, 28 });
	idle.PushBack({ 73, 8, 30, 28 });
	idle.PushBack({ 110, 9, 30, 28 });
	/*do
	{
		idle.PushBack({ 244, 11, 28, 25 });
		idle.PushBack({ 281, 8, 30, 28 });
		idle.PushBack({ 311, 10, 32, 25 });
		idle.PushBack({ 350, 11, 30, 25 });
		idle.PushBack({ 388, 12, 27, 24 });
		idle.PushBack({ 421, 10, 28, 26 });
		idle.PushBack({ 454, 12, 32, 25 });
		idle.PushBack({ 493, 11, 31, 25 });
		idle.PushBack({ 531, 12, 27, 24 });
		idle.PushBack({ 565, 9, 31, 27 });
		idle.PushBack({ 601, 8, 31, 28 });

		idle.speed = 0.2f;
	} while (position.y = 200);*/

	idle.speed = 0.2f;


	forward.PushBack({ 36, 8, 30, 28 });
	forward.PushBack({ 73, 8, 30, 28 });
	forward.PushBack({ 110, 9, 30, 28 });

	/*do
	{
		forward.PushBack({ 244, 11, 28, 25 });
		forward.PushBack({ 281, 8, 30, 28 });
		forward.PushBack({ 311, 10, 32, 25 });
		forward.PushBack({ 350, 11, 30, 25 });
		forward.PushBack({ 388, 12, 27, 24 });
		forward.PushBack({ 421, 10, 28, 26 });
		forward.PushBack({ 454, 12, 32, 25 });
		forward.PushBack({ 493, 11, 31, 25 });
		forward.PushBack({ 531, 12, 27, 24 });
		forward.PushBack({ 565, 9, 31, 27 });
		forward.PushBack({ 601, 8, 31, 28 });

		forward.speed = 0.2f;
	} while (position.y = 200);*/

	forward.speed = 0.2f;

	backward.PushBack({ 181, 8, 23, 28 });
	backward.PushBack({ 147, 8, 25, 28 });
	backward.loop = false;

	backward.speed = 0.2f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("Assets/Sprites/Characters/Sho/Sho spritesheet.png");
	
	destroyed = false;
	position.x = 150;
	position.y = 120;
	score = 0;

	col = App->collision->AddCollider({ position.x, position.y, 32, 16 }, COLLIDER_PLAYER, this);

	font_score = App->fonts->Load("fonts/rtype_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);


	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);
	App->fonts->UnLoad(font_score);
	if (col)
		col->to_delete = true;

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	Animation* current_animation = &idle;

	float speed = 2.5f;

	if(App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
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
	if (App->input->keyboard[SDL_SCANCODE_A] && App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &backward;
	}
	if (App->input->keyboard[SDL_SCANCODE_A] && App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &backward;
	}
	// Shooting

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->shoot, position.x + 20, position.y, COLLIDER_PLAYER_SHOT);
	}

	// Draw everything

	if (destroyed == false)
		App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	// Draw UI (score) --------------------------------------
	// sprintf_s(score_text, 10, "%7d", score);

	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
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