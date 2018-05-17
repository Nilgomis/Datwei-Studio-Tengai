#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleSceneForest.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "SDL_mixer\include\SDL_mixer.h"
//#include "ModuleBackground.h"

#include "SDL\include\SDL_render.h"


ModuleSceneForest::ModuleSceneForest()
{
	// 1st fade
	midfade.x = 0;
	midfade.y = 0;
	midfade.w = SCREEN_WIDTH;
	midfade.h = SCREEN_HEIGHT;

	// back and sky
	gtrees.x = 15;
	gtrees.y = 367;
	gtrees.w = 810;
	gtrees.h = 224;

	gate.x = 2;
	gate.y = 3;
	gate.w = 87;
	gate.h = 224;

	gate2.x = 89;
	gate2.y = 3;
	gate2.w = 63;
	gate2.h = 224;

	btrees.x = 6;
	btrees.y = 12;
	btrees.w = 320;
	btrees.h = 136;

	ftrees.x = 154;
	ftrees.y = 394;
	ftrees.w = 319;
	ftrees.h = 64;

	rock.x = 828;
	rock.y = 570;
	rock.w = 160;
	rock.h = 21;

	mtrees.x = 6;
	mtrees.y = 154;
	mtrees.w = 320;
	mtrees.h = 224;

	ground.x = 352;
	ground.y = 49;
	ground.w = 64;
	ground.h = 32;

	ggrass.x = 990;
	ggrass.y = 552;
	ggrass.w = 165;
	ggrass.h = 39;

	gtree1.x = 1158;
	gtree1.y = 367;
	gtree1.w = 256;
	gtree1.h = 224;

	gtree2.x = 1417;
	gtree2.y = 367;
	gtree2.w = 672;
	gtree2.h = 224;


	//temples
	temp.x = 174;
	temp.y = 166;
	temp.w = 348;
	temp.h = 61;

	temp1.x = 176;
	temp1.y = 3;
	temp1.w = 155;
	temp1.h = 109;

	//tree
	tree.x = 612;
	tree.y = 25;
	tree.w = 25;
	tree.h = 280;

	//Backgronund before Scroll diagonal1
	end1.x = 0;
	end1.y = 0;
	end1.w = 320;
	end1.h = 224;

	//Trees
	toptree.x = 8;
	toptree.y = 445;
	toptree.w = 15;
	toptree.h = 14;

	ttrees.x = 13;
	ttrees.y = 398;
	ttrees.w = 115;
	ttrees.h = 33;

	gtree3.x = 1417;
	gtree3.y = 367;
	gtree3.w = 408;
	gtree3.h = 224;

	//end grass
	grass.x = 2092;
	grass.y = 552;
	grass.w = 97;
	grass.h = 39;

	//Sky
	sky.x = 8;
	sky.y = 271;
	sky.w = 708;
	sky.h = 121;

	//Mountain
	mount.x = 10;
	mount.y = 71;
	mount.w = 512;
	mount.h = 131;

	//Bamboo
	bamboo.x = 740;
	bamboo.y = 293;
	bamboo.w = 317;
	bamboo.h = 98;

	bamboo2.x = 572;
	bamboo2.y = 105;
	bamboo2.w = 320;
	bamboo2.h = 97;

	//Diagonal
	diagonal1.x = 5;
	diagonal1.y = 5;
	diagonal1.w = 1841;
	diagonal1.h = 704;
}


ModuleSceneForest::~ModuleSceneForest()
{}

// Load assets
bool ModuleSceneForest::Start()
{
	LOG("Loading Forest scene");

	graphics = App->textures->Load("Assets/Sprites/Maps/Forest/Background/gate_sprite.png");
	graphics1 = App->textures->Load("Assets/Sprites/Maps/Forest/Background/background_sprite.png");
	graphics2 = App->textures->Load("Assets/Sprites/Maps/Forest/Background/fade_sprite.png");
	end = App->textures->Load("Assets/Sprites/Maps/Forest/Background/fase2_sprite.png");
	diagonal = App->textures->Load("Assets/Sprites/Maps/Forest/Background/diagonal_sprite.png");
	fade1 = App->textures->Load("Assets/Sprites/Maps/Forest/Background/fade_sprite.png");
	fade2 = App->textures->Load("Assets/Sprites/Maps/Forest/Background/fade2_prite.png");
	/*bg.x = 0;
	bg.y = 0;
	bg.w = 256;
	bg.h = 224;*/

	

	//App->background->Enable();
	App->player->Enable();
	App->player2->Enable();
	App->particles->Enable();
	App->collision->Enable();
	App->enemies->Enable();

	// music
	music = App->audio->LoadMusic("Assets/Audio/WAV/Music/08_Tall_cedar.wav");
	Mix_PlayMusic(music, -1);

	// Colliders ---
	topCollider = App->collision->AddCollider({ 0, 0, 99000, 20 }, COLLIDER_WALL);
	botCollider = App->collision->AddCollider({ 0, SCREEN_HEIGHT - 4, 990000, 16 }, COLLIDER_WALL);
	leftCollider = App->collision->AddCollider({ 0,0,0,SCREEN_HEIGHT }, COLLIDER_WALL);
	rightCollider = App->collision->AddCollider({ SCREEN_WIDTH,0, 0,SCREEN_HEIGHT }, COLLIDER_WALL);

	// Enemies ---
	App->enemies->AddEnemy(ENEMY_TYPES::REDSHIP, 320, 70, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::REDSHIP, 400, 110, 0.25f);
	App->enemies->AddEnemy(ENEMY_TYPES::REDSHIP, 500, 150, 0.5f);
	App->enemies->AddEnemy(ENEMY_TYPES::REDSHIP, 1000, -32, 3);
	App->enemies->AddEnemy(ENEMY_TYPES::REDSHIP, 1200, 225, 3);
	App->enemies->AddEnemy(ENEMY_TYPES::REDSHIP, 1200, -64, 3);
	App->enemies->AddEnemy(ENEMY_TYPES::REDSHIP, 1200, 257, 3);
	App->enemies->AddEnemy(ENEMY_TYPES::REDSHIP, 1400, -81, 4);
	App->enemies->AddEnemy(ENEMY_TYPES::REDSHIP, 1400, 294, 4);
	App->enemies->AddEnemy(ENEMY_TYPES::REDSHIP, 1700, 110, 6);
	App->enemies->AddEnemy(ENEMY_TYPES::REDSHIP, 1700, 70, 6);
	App->enemies->AddEnemy(ENEMY_TYPES::REDSHIP, 1700, 150, 6);
	App->enemies->AddEnemy(ENEMY_TYPES::REDSHIP, 1720, 60, 8);
	App->enemies->AddEnemy(ENEMY_TYPES::REDSHIP, 1800, -32, 7);
	App->enemies->AddEnemy(ENEMY_TYPES::REDSHIP, 1800, 225, 7);
	App->enemies->AddEnemy(ENEMY_TYPES::REDSHIP, 1850, 110, 8);
	App->enemies->AddEnemy(ENEMY_TYPES::REDSHIP, 1850, 160, 8);
	App->enemies->AddEnemy(ENEMY_TYPES::REDSHIP, 2200, 150, 11);
	App->enemies->AddEnemy(ENEMY_TYPES::REDSHIP, 2200, 110, 12);
	App->enemies->AddEnemy(ENEMY_TYPES::REDSHIP, 2200, 70, 13);
	App->enemies->AddEnemy(ENEMY_TYPES::REDSHIP, 2500, 50, 15);
	App->enemies->AddEnemy(ENEMY_TYPES::REDSHIP, 2500, 80, 16);
	App->enemies->AddEnemy(ENEMY_TYPES::REDSHIP, 2500, 140, 17);
	App->enemies->AddEnemy(ENEMY_TYPES::REDSHIP, 2500, 170, 18);
	/*App->enemies->AddEnemy(ENEMY_TYPES::REDSHIP, 250, -32, 20);
	App->enemies->AddEnemy(ENEMY_TYPES::REDSHIP, 250, 225, 20);
	App->enemies->AddEnemy(ENEMY_TYPES::REDSHIP, 170, -64, 20);
	App->enemies->AddEnemy(ENEMY_TYPES::REDSHIP, 170, 257, 20);
	App->enemies->AddEnemy(ENEMY_TYPES::REDSHIP, 200, -81, 22);
	App->enemies->AddEnemy(ENEMY_TYPES::REDSHIP, 200, 294, 22);
	App->enemies->AddEnemy(ENEMY_TYPES::REDSHIP, 200, -81, 25);
	App->enemies->AddEnemy(ENEMY_TYPES::REDSHIP, 200, 294, 25);

	App->enemies->AddEnemy(ENEMY_TYPES::GREENSHIP, 600, 80,100);
	App->enemies->AddEnemy(ENEMY_TYPES::GREENSHIP, 625, 80, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::GREENSHIP, 640, 80, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::GREENSHIP, 665, 80, 100);

	App->enemies->AddEnemy(ENEMY_TYPES::GREENSHIP, 320, 80, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::GREENSHIP, 320, 100, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::GREENSHIP, 320, 120, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::GREENSHIP, 320, 140, 0);*/

	frameTime = 0;
	t2 = 0;
	return true;
}

// Load assets
bool ModuleSceneForest::CleanUp()
{
	LOG("Unloading Temple scene");

	alpha_graph2 = 255;
	fade = true;

	App->collision->Disable();
	App->particles->Disable();
	App->player->Disable();
	App->player2->Disable();
	App->enemies->Disable();
	//App->background->Disable();

	//Unloading Audio
	App->audio->UnloadMusic(music);
	music = nullptr;
	return true;
}

float ModuleSceneForest::Time()
{
	return timer;
}

// Update: draw background
update_status ModuleSceneForest::Update()
{
	//Collision update
	leftCollider->SetPos(App->render->camera.x / SCREEN_SIZE, 0);
	rightCollider->SetPos((SCREEN_WIDTH + App->render->camera.x / SCREEN_SIZE), 0);
	// Move camera forward -----------------------------
	//App->render->camera.x += 1 * SCREEN_SIZE;

	//Repeating backgrounds logic
	/*bgXpos -=0.5f;
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
	}*/

	//Increase the timer which serves to spawn enemies
	frameTime++;
	timer =frameTime/60.000000000f;
	LOG("%f, %f", frameTime,timer);

	// Draw everything --------------------------------------	
	int aux = -10, auxtree = -10, aux2 = 810, aux3 = 1775, aux4 = 780, aux5 = 2031, aux6 = 1390, aux7 = 5119, aux8 = 4690, aux9 = 6140, aux10 = 6630, aux11 = 7880;

	for (int i = 0; i < 6; i++) {
		App->render->Blit(graphics2, aux, 0, &mtrees, 0.55f);
		App->render->Blit(graphics2, aux + 42, 45, &toptree, 0.60f);
		App->render->Blit(graphics2, aux, 58, &btrees, 0.60f);
		App->render->Blit(graphics2, aux + 170, 25, &ttrees, 0.60f);
		App->render->Blit(graphics2, auxtree, 82, &ftrees, 0.65f);

		aux += 320;
		auxtree += 319;
	}

	for (int i = 0; i < 15; i++) {
		App->render->Blit(graphics2, aux4, 193, &ground, 0.75f);
		aux4 += ground.w;
	}

	App->render->Blit(fade1, 0, 0, &midfade, 0.00f);

	if (App->render->camera.x > 5300 && fade == true) {
		if (alpha_fade1 >= SDL_ALPHA_OPAQUE) {
			alpha_fade1 = 0;
			alpha_graph2 = 0;
			alpha_graph1 = 255;
			fade = false;
		}
		else {
			alpha_fade1 += 0.10*speed;
		}
	}

	for (int i = 0; i < 18; i++) {
		App->render->Blit(graphics1, aux6, 0, &end1, 0.65f);
		aux6 += end1.w;
	}

	if (App->render->camera.x > 5300 && fade == false) {
		if (alpha_fade2 > SDL_ALPHA_TRANSPARENT) {
			App->render->Blit(fade2, 0, 0, &midfade, 0.00f);
			alpha_fade2 -= 0.10*speed;
		}
		else {
			alpha_fade1 = 0;
		}

	}

	App->render->Blit(graphics, 1650, 0, &tree, 0.73f);
	App->render->Blit(graphics, 1715, 0, &tree, 0.69f);
	App->render->Blit(graphics, 1830, 0, &tree, 0.71f);

	App->render->Blit(graphics, 2210, 0, &tree, 0.71f);
	App->render->Blit(graphics, 1990, 0, &tree, 0.72f);
	App->render->Blit(graphics, 2105, 0, &tree, 0.73f);

	App->render->Blit(graphics, 2320, 0, &tree, 0.73f);
	App->render->Blit(graphics, 2390, 0, &tree, 0.71f);
	App->render->Blit(graphics, 2475, 0, &tree, 0.72f);

	App->render->Blit(graphics, 0, 0, &gtrees, 0.75f);
	App->render->Blit(graphics, 1610, 185, &ggrass, 0.75f);
	App->render->Blit(graphics, 115, 0, &gate, 0.75f);
	App->render->Blit(graphics, 938, 132, &temp, 0.75f);
	App->render->Blit(graphics, 1400, 92, &temp1, 0.75f);

	for (int i = 0; i < 5; i++) {
		App->render->Blit(graphics, aux2, 203, &rock, 0.75f);
		aux2 += rock.w;
	}

	App->render->Blit(graphics, aux3, 0, &gtree1, 0.75f);

	for (int i = 0; i < 4; i++) {
		App->render->Blit(graphics, aux5, 0, &gtree2, 0.75f);
		aux5 += gtree2.w;
	}
	for (int i = 0; i < 22; i++) {
		App->render->Blit(graphics, aux7, ygrass, &grass, 0.75f);
		aux7 += grass.w;
	}

	App->render->Blit(graphics, 4719, 0, &gtree3, 0.75f);

	if (App->render->camera.x > 28780 && App->render->camera.x > -28880) {
		alpha_end = 255;
		alpha_graph1 = 0;
	}

	for (int i = 0; i < 9; i++) {
		App->render->Blit(end, aux8, 0, &sky, 0.50f);
		aux8 += sky.w;
	}

	for (int i = 0; i < 11; i++) {
		App->render->Blit(end, aux9, SCREEN_HEIGHT - mount.h, &mount, 0.65f);
		aux9 += mount.w;
	}

	for (int i = 0; i < 22; i++) {
		App->render->Blit(end, aux10, SCREEN_HEIGHT - bamboo.h, &bamboo, 0.70f);
		aux10 += bamboo.w;
	}

	for (int i = 0; i < 29; i++) {
		App->render->Blit(end, aux11, SCREEN_HEIGHT - bamboo.h, &bamboo, 0.75f);
		aux11 += bamboo.w;
	}

	App->render->Blit(diagonal, x, y, &diagonal1, 0.75f);

	// background speed


	if (App->render->camera.x < 1700) {
		speed = 9;
	}
	else if (App->render->camera.x > 1700 && App->render->camera.x < 5300) {
		speed = 6;
	}
	else if (App->render->camera.x > 5300 && App->render->camera.x < 8000) {
		speed = 12;
	}
	else if (App->render->camera.x > 8000 && App->render->camera.x < 10000) {
		speed = 0.03;
	}
	else if (App->render->camera.x > 10000 && App->render->camera.x < 13100) {
		speed = 3;
	}
	else if (App->render->camera.x > 13100 && App->render->camera.x < 27340) {
		if (time < 270)
		{
			speed = 0;
			time++;
		}
		else
		{
			speed = 6;
		}

	}
	else if (App->render->camera.x > 27340 && App->render->camera.x < 30205) {
		x = 0.33*speed;
		y += 0.21*speed;
		speed = 6;
	}
	else if (App->render->camera.x > 30205) {
		speed = 6;
	}

	if (App->render->camera.x > 26000 && App->render->camera.x < 27000) {
		ygrass += 0.15*speed;
	}

	// alpha textures
	/*SDL_SetTextureAlphaMod(graphics2, alpha_graph2);
	SDL_SetTextureAlphaMod(graphics1, alpha_graph1);*/
	SDL_SetTextureAlphaMod(fade1, alpha_fade1);
	SDL_SetTextureAlphaMod(fade2, alpha_fade2);
	SDL_SetTextureAlphaMod(end, alpha_end);

	// background movement
	App->player2->position.x += speed / SCREEN_SIZE / 3;
	App->player->position.x += speed / SCREEN_SIZE / 3;
	App->render->camera.x += speed / 3;


	if (time > 30) {
		App->fade->FadeToBlack(this, (Module*)App->end_screen, 2); 
	}


	return UPDATE_CONTINUE;
}

