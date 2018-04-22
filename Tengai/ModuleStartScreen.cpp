#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleStartScreen.h"
#include "ModulePlayer2.h"
#include "ModuleSceneTemple.h"
#include "ModulePlayer.h"


// Load assets
ModuleStartScreen::ModuleStartScreen()
{
	

		//Components
		title = { 34, 4, 247, 187 };
		background = { 0, 0, 320, 224 };
		psikyo1 = { 13, 198, 163, 14 };
		atlus1 = { 180, 200, 111, 12 };
		start_button = { 89, 108, 140, 13 };

		//Cloud Layers
		bg1 = { 0, 331, 510, 43 };
		bg2 = { 0, 415, 512, 29 };
		bg3 = { 31, 89, 448, 24 };
		bg4 = { 0, 133, 513, 10 };
		bg5 = { 0, 162, 511, 8 };
		bg6 = { 0, 190, 507, 8 };
		bg7 = { 0, 213, 502, 4 };
	}

ModuleStartScreen::~ModuleStartScreen() {

}

	bool ModuleStartScreen::Init() {

		bool ret = true;

		int aux = 35;
		bool print = true;

		s1 = -18.0;
		s2 = -18.0;
		s3 = -15.0;
		s4 = -15.0;
		s5 = -12.0;
		s6 = -12.0;
		s7 = -9.0;
		s8 = -9.0;
		s9 = -6.0;
		s10 = -6.0;
		s11 = -3.0;
		s12 = -3.0;
		s13 = 0.0;
		s14 = 0.0;


		return ret;
	}
	bool ModuleStartScreen::Start()
	{

		LOG("Loading sky intro");
		App->player2->Disable();

		//Reseting camera positions
		App->render->camera.x = 0;
		App->render->camera.y = 0;
		//App->scene_temple->Disable();//falta afegir un modul per a la pantalla final
		//main sprites
		graphics = App->textures->Load("assets/sprites/UI/StartScreen/button_start.png");
		graphics2 = App->textures->Load("assets/sprites/UI/StartScreen/background.png");
		graphics3 = App->textures->Load("assets/sprites/UI/StartScreen/title&text.png");

		//Loading sprite layers-->Cloud waves scrolling in layers
		background1 = App->textures->Load("assets/sprites/UI/StartScreen/waves.png");

		//Loading Music
		/*music = App->audio->LoadMusic("assets/audio/music/01_Gem_of_hope.ogg");
		Mix_PlayMusic(music, -1);*/
		return true;
	}

	update_status ModuleStartScreen::Update()
	{
		// Switching between scenes
		if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) App->fade->FadeToBlack(this, App->scene_temple, 2);

		//Draw Background
		App->render->Blit(graphics2, 0, 0, &background);


		// Background scrolls -> from last layer to first, 7 layers

		//7
		s13 -= 0.5f;
		if (s13 <= -bg7.w) {
			s13 = 0;
		}
		s14 = s13;
		App->render->Blit(background1, (int)s13, 127, &bg7);
		s14 += bg7.w;
		App->render->Blit(background1, (int)s4, 127, &bg7);

		//6
		s11 -= 0.75f;
		if (s11 <= -bg6.w) {
			s11 = 0;
		}
		s12 = s11;
		App->render->Blit(background1, (int)s11, 132, &bg6);
		s12 += bg6.w;
		App->render->Blit(background1, (int)s12, 132, &bg6);

		//5
		s9 -= 1.00f;
		if (s9 <= -bg5.w) {
			s9 = 0;
		}
		s10 = s9;
		App->render->Blit(background1, (int)s9, 138, &bg5);
		s10 += bg5.w;
		App->render->Blit(background1, (int)s10, 138, &bg5);


		//4
		s7 -= 1.25;
		if (s7 <= -bg4.w) {
			s7 = 0;
		}
		s8 = s7;
		App->render->Blit(background1, (int)s7, 146, &bg4);
		s8 += bg4.w;
		App->render->Blit(background1, (int)s8, 146, &bg4);

		//3
		s5 -= 1.5;
		if (s5 <= -bg3.w) {
			s5 = 0;
		}
		s6 = s5;
		App->render->Blit(background1, (int)s5, 156, &bg3);
		s6 += bg3.w;
		App->render->Blit(background1, (int)s6, 156, &bg3);

		//2
		s3 -= 1.75f;
		if (s3 <= -bg2.w) {
			s3 = 0;
		}
		s4 = s3;
		App->render->Blit(background1, (int)s3, 164, &bg2);
		s4 += bg2.w;
		App->render->Blit(background1, (int)s4, 164, &bg2);

		//1
		s1 -= 2.0f;
		if (s1 <= -bg1.w) {
			s1 = 0;
		}
		s2 = s1;
		App->render->Blit(background1, (int)s1, 180, &bg1);
		s2 += bg1.w;
		App->render->Blit(background1, (int)s1, 180, &bg1);

		// Draw main components
		App->render->Blit(graphics3, 35, 6, &title);
		App->render->Blit(graphics, 15, 200, &psikyo1);
		App->render->Blit(graphics, 180, 202, &atlus1);


		//Blinking start button
		if (print)
		{
			App->render->Blit(graphics, 95, 110, &start_button);
			aux--;
			if (aux <= 0)print = false;
		}
		else {
			aux++;
			if (aux >= 35)print = true;
		}

		return update_status::UPDATE_CONTINUE;
	}

	bool ModuleStartScreen::CleanUp()
	{
		//Unloading textures
		App->textures->Unload(graphics);
		graphics = nullptr;

		//Unloading Audio
		/*App->audio->UnloadMusic(music);
		music = nullptr;
		*/
		return true;
	}
