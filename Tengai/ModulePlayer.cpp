#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"


ModulePlayer::ModulePlayer()
{

	// idle animation 
	idle.PushBack({ 38, 0, 29, 28 });
	idle.PushBack({ 75, 0, 29, 28 });
	idle.PushBack({ 112, 0, 29, 28 });

	idle.speed = 0.2f;


	forward.PushBack({ 38, 0, 29, 28 });
	forward.PushBack({ 75, 0, 29, 28 });
	forward.PushBack({ 112, 0, 29, 28 });
	//forward.loop = false;
	forward.speed = 0.2f;

	backward.PushBack({ 216, 1, 24, 26 });
	backward.PushBack({ 183, 0, 22, 27 });
	backward.PushBack({ 149, 0, 24, 27 });
	backward.loop = false;
	backward.speed = 0.2f;

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	position.x = 25;
	position.y = 50;
	bool ret = true;
	destroyed = false;
	player = App->textures->Load("Assets/Sprites/Characters/Sho/Sho_Spritesheet.png");
	col = App->collision->AddCollider({ position.x,position.y,29,28 }, COLLIDER_PLAYER, this);
	return ret;
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
		if (position.x < 270) {
			position.x += speed;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &backward;
		if (position.x > 0) {
			position.x -= speed;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &backward;
		if (position.y > 20) {
			position.y -= speed;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &forward;
		if (position.y < 192) {
			position.y += speed;
		}
	}
	col->SetPos(position.x, position.y);

	// Shooting

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && cooldown <= 0.0f)
	{
		App->particles->AddParticle(App->particles->shoshot, position.x + 20, position.y+10, COLLIDER_PLAYER_SHOT);
	}

	// Draw everything

	if (destroyed == false)
		App->render->Blit(player, position.x, position.y, &(current_animation->GetCurrentFrame()));

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