#include "SceneIntro.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "SDL/include/SDL_scancode.h"
#include "IntroAnimation.h"
#include "SceneIntro.h"
#include "Presentation.h"
#include "ModulePlayer.h"
#include "LevelManager.h"
#include "ModuleFonts.h"
#include "SDL/include/SDL.h"
#include "WindowSize.h"



IntroAnimation::IntroAnimation(bool startEnabled) :Module(startEnabled)
{
	
}

IntroAnimation ::~IntroAnimation() {

}

bool IntroAnimation::Start() {
	LOG("Loading backgroud assets :)");

	bool ret = true;
	App->audio->Enable();
	App->audio->PlayMusic("assets/Audio/Music/AnimationMusic.ogg");

	introTexture = App->textures->Load("assets/textures/spritesheet_intro.png");
	
	char lookupTableChars[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ.-?!0123456789@/ " };
	menuFont = App->fonts->Load("Assets/Textures/spritesheet_menus.png", lookupTableChars, 1);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	zoom = 4;
	animIndex = 0;
	loop = 0;
	delay = 400;

	yellow = { 0,0 };
	yellowSmall = {0,0};
	blue = { 0,0 };
	blueSmall = { 0,0 };
	smokeM = { 0,0 };
	coffeeLeft = { 0,0 };
	yellowThink = { 0,0 };
	coffeeRight = { 0,0 };
	blackThink = { 0,0 };
	fullBodyThinking = {0,0};
	fullBodyLeaving = { 0,0 };
	fullBodyWoman = {0,0};
	sadMan = {0,0};
	imaginCar = {0,0};

	lastTime = SDL_GetTicks();
	return ret;
}

Update_Status IntroAnimation::Update() {	// plays animation
	currentTime = SDL_GetTicks();

	screen_w = App->winSize->w;
	screen_h = App->winSize->h;

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{


		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 20);

	}

	if (App->lvlManage->godmode == true) {
		if (App->input->keys[SDL_SCANCODE_F4] == KEY_DOWN) {
			App->fade->FadeToBlack(this, (Module*)App->packInVideo, 20);
		}
	}

	switch (animIndex) {
	case 0:
	case 1:
	case 2:
		if (currentTime >= lastTime + 1000) {



			if (oposite == false) {
				oposite = true;
			}
			else {
				oposite = false;
			}
			loop++;
			lastTime = currentTime;
			if (loop == 4) {
				yellow.y = (screen_h - sky.h * zoom) / 2;
				yellow.x = (screen_w - sky.w * zoom) / 2;
				fullBodyWoman = { (screen_w - fullBodyBackOposite.w * zoom) / 2, (screen_h - sky.h * zoom) / 2 + 40 * zoom };

				animIndex++;
				loop = 0;
			}
		}
		//else {

			//if (loop == 4) {
			//	yellow.y = (screen_h - sky.h * zoom) / 2;
			//	yellow.x = (screen_w - sky.w * zoom) / 2;
				
			//	animIndex++;
			//	loop = 0;
			//}
		//}
		break;
	case 3:
	
		if (currentTime > lastTime + 1000) {

			if (yellow.x < (screen_w + sky.w * zoom) / 2) {
				yellow.x += 5*zoom;
			}

			if (yellow.x >= (screen_w + sky.w * zoom) / 2) {
				yellowSmall = { (screen_w - sky.w * zoom) / 2 + sky.w * zoom,  (screen_h - sky.w * zoom) / 2 + 115 * zoom};
				animIndex++;
			}
		}
		else {
			yellow.y = (screen_h - sky.h * zoom) / 2;
			yellow.x = (screen_w - sky.w * zoom) / 2;
		}
	break;

	case 4:
		if (yellowSmall.x> (screen_w - fullBodyBackOposite.w * zoom) / 2 + (fullBodyBackOposite.w+3)*zoom) {
			yellowSmall.x-=3*zoom;
			lastTime = currentTime;
		}
		else if(yellowSmall.x < (screen_w - fullBodyBackOposite.w * zoom) / 2 + (fullBodyBackOposite.w + 3) * zoom){
			yellowSmall.x = (screen_w - fullBodyBackOposite.w * zoom) / 2 + (fullBodyBackOposite.w + 3) * zoom;
			lastTime = currentTime;

		}
		else {
			
		}
		
		if (yellowSmall.y >( screen_h - sky.h * zoom) / 2 + 67 * zoom ) {
			yellowSmall.y -=1 * zoom;
			lastTime = currentTime;
		}
		else if (yellowSmall.y < (screen_h - sky.h * zoom) / 2 + 67 * zoom) {
			yellowSmall.y = (screen_h - sky.h * zoom) / 2 + 67 * zoom;
			
		}
		else {
			
		}
		

		if (currentTime >= lastTime + delay ) {

			loop++;
			lastTime = currentTime;
		}
		else {
			switch (loop) {
			case 1:
				if (currentTime >= lastTime + 1100) {
					if ((coffeeLeft.x != (screen_w - fullBodyBackOposite.w * zoom) / 2 + (fullBodyBackOposite.w + 5) * zoom) && (coffeeLeft.y != (screen_h - sky.h * zoom) / 2 + 41 * zoom)) {
						coffeeLeft = { (screen_w - fullBodyBackOposite.w * zoom) / 2 + (fullBodyBackOposite.w + 5) * zoom ,(screen_h - sky.h * zoom) / 2 + 41 * zoom };

						lastTime = currentTime;
					}
				}
				delay = 2000;
				
				//delay = 500;
				break;
			case 2:
				if ((yellowThink.x != (screen_w - fullBodyBackOposite.w * zoom) / 2 -20 * zoom) && (yellowThink.y != (screen_h - sky.h * zoom) / 2 + 18 * zoom)) {
					yellowThink = { (screen_w - fullBodyBackOposite.w * zoom) / 2 - 20 * zoom , (screen_h - sky.h * zoom) / 2 + 18 * zoom};
					
					lastTime = currentTime;
				}
				delay = 3600;
				//delay = 3000;
				break;
			case 3:
				
					/*if ((blue.x != (screen_w - blueCar.w * zoom) / 2) && (blue.y != (screen_h - blueCar.h * zoom) / 2)) {
						blue = { (screen_w - blueCar.w * zoom) / 2  , (screen_h - blueCar.h * zoom) / 2 };
						lastTime = currentTime;
						delay = 10000;
					}
				*/

				
				if (delay >=1900 ) {
					if (currentTime < lastTime + 2500 ) {

						if (currentTime > lastTime+200 ) {
							coffeeLeft = { 0,0 };
							delay = 15000;
						}
						if (currentTime > lastTime + 800 ) {
							yellowThink = { 0,0 };
							
						}
						if (currentTime > lastTime + 1800 ) {
							if ((blue.x != (screen_w - blueCar.w * zoom) / 2) && (blue.y != (screen_h - blueCar.h * zoom) / 2)) {
								blue = { (screen_w - blueCar.w * zoom) / 2  , (screen_h - blueCar.h * zoom) / 2 };
								//lastTime = currentTime;
								delay = 15000;
							}
						}

					}
					if (currentTime >= lastTime + 2500 ) {
						if ((blue.x > (screen_w - sky.w * zoom) / 2 - blueCar.w * zoom)) {
							blue.x -= 6 * zoom;

						}
						else if (blue.x < (screen_w - sky.w * zoom) / 2 - blueCar.w * zoom) {
							blue.x = (screen_w - sky.w * zoom) / 2 - blueCar.w * zoom;
						}
						else {
							blueSmall = { ((screen_w - sky.w * zoom) / 2 - blueCarSmall.w * zoom) ,(screen_h - sky.h * zoom) / 2 + 130 * zoom };
							delay = 1000;
							lastTime = currentTime;
						}
					}
				}
				//delay = 10000;
				break;
			case 4:
				if (currentTime >= lastTime + 700) {
					if ((blueSmall.x < (screen_w - sky.w * zoom) / 2)) {
						//blueSmall = { ( (screen_w - fullBodyBackOposite.w * zoom) / 2 - (4 + blueCarSmall.w) * zoom) ,(screen_h - sky.h * zoom) / 2 + 81 * zoom };
						blueSmall.x += 3 * zoom;
						delay = 10000;
						//lastTime = currentTime;
					}
					else if (blueSmall.x > (screen_w - sky.w * zoom) / 2) {
						blueSmall.x = (screen_w - sky.w * zoom) / 2;
					}

					if ((blueSmall.y > ((screen_h - sky.h * zoom) / 2) + 81 * zoom)) {
						blueSmall.y -= 1 * zoom;
						delay = 10000;
						//lastTime = currentTime;
					}
					else if (blueSmall.y < ((screen_h - sky.h * zoom) / 2) + 81 * zoom) {
						blueSmall.y = ((screen_h - sky.h * zoom) / 2) + 81 * zoom;
					}
					else if (blueSmall.x == (screen_w - sky.w * zoom) / 2) {
						delay = 2000;

					}

				}

				
				
				break;
			case 5:
				if ((coffeeRight.x != (screen_w - fullBodyBackOposite.w * zoom) / 2 - 23 * zoom) && (coffeeRight.y != (screen_h - sky.h * zoom) / 2 + 41 * zoom)) {
					coffeeRight = { (screen_w - fullBodyBackOposite.w * zoom) / 2 - 23 * zoom ,(screen_h - sky.h * zoom) / 2 + 41 * zoom };
					delay = 1000;
					lastTime = currentTime;
				}
				break;
			case 6:
				delay = 2000;
				if ((fullBodyThinking.x !=  (screen_w - sky.w * zoom) / 2 + 108 * zoom) && (fullBodyThinking.y != (screen_h - sky.h * zoom) / 2 + 40 * zoom )) {
					fullBodyWoman = { 0,0 };
					fullBodyThinking = { (screen_w - sky.w * zoom) / 2 + 108 * zoom, (screen_h - sky.h * zoom) / 2 + 40 * zoom };
					fullBodyLeaving = { 0,0 };
					lastTime = currentTime;
				}
				
				break;
			case 7:
				if ((fullBodyLeaving.x != (screen_w - sky.w * zoom) / 2 + 77 * zoom && (fullBodyLeaving.y != (screen_h - sky.h * zoom) / 2 + 35 * zoom))) {
					fullBodyWoman = { 0,0 };
					fullBodyThinking = { 0,0 };
					fullBodyLeaving = { (screen_w - sky.w * zoom) / 2 + 77 * zoom, (screen_h - sky.h * zoom) / 2 + 35 * zoom };
					coffeeRight = { 0,0 };
					delay = 500;
					lastTime = currentTime;
				}
				break;
			case 8:
				if ((blackThink.x != (screen_w +sky.w * zoom) / 2 - 95 * zoom) && (blackThink.y != (screen_h - sky.h * zoom) / 2 + 42 * zoom)) {
					fullBodyLeaving = { 0,0};
					blackThink = { (screen_w + sky.w * zoom) / 2 - 95 * zoom ,(screen_h - sky.h * zoom) / 2 + 42 * zoom };
					lastTime = currentTime;
				}
				delay = 2500;
				break;
			case 9:
				if (blueSmall.y>(screen_h-sky.h*zoom)/2 + 64*zoom) {
					blueSmall.y-=2*zoom;
					delay = 3000;
				}
				else if ((blueSmall.y < (screen_h - sky.h * zoom) / 2 + 64 * zoom)) {
					blueSmall.y = (screen_h - sky.h * zoom) / 2 + 64 * zoom;

				}
				else {
					animIndex=5;
				}
			
				break;
			//case 6:
			//	if ((blackThink.x != (screen_w - fullBodyBackOposite.w * zoom) / 2 - 20 * zoom) && (blackThink.y != (screen_h - sky.h * zoom) / 2 + 18 * zoom)) {
			//		blackThink = { (screen_w - fullBodyBackOposite.w * zoom) / 2 - 20 * zoom ,(screen_h - sky.h * zoom) / 2 + 18 * zoom };
			//		lastTime = currentTime;
			//	}
			//	break;
			}
			//break;
		}
		break;
	case 5:
		if (blueSmall.y < (screen_h - sky.h * zoom) / 2 + 91 * zoom) {
			blueSmall.y += 2 * zoom;
		}
		if (blueSmall.x > (screen_w - sky.w * zoom) / 2 - blueCarSmall.w * zoom) {
			blueSmall.x -= 4 * zoom;
		}

		if (blueSmall.x <= (screen_w - sky.w * zoom) / 2 - blueCarSmall.w * zoom && blueSmall.y >= (screen_h - sky.h * zoom) / 2 + 91 * zoom) {
			blackThink = {0,0 };
			delay = 1000;
			loop = 0;
			smokeM = { (screen_w - sky.w * zoom) / 2 + 6 * zoom, (screen_h - sky.h * zoom) / 2 + 38 * zoom };
			lastTime = currentTime;
			animIndex = 6;
		}
		break;
	case 6:

		if (sadMan.x != (screen_w - sky.w * zoom) / 2 + 102 * zoom && sadMan.y != (screen_h - sky.h * zoom) / 2 + 45 * zoom) {
			sadMan = { (screen_w - sky.w * zoom) / 2 + 102 * zoom, (screen_h - sky.h * zoom) / 2 + 45 * zoom };
		}
		if (currentTime >= lastTime + 100) {



			if (smokeM.y <= ground.y) {
				smokeM.y += 5 * zoom;
			}
			else {
				delay = 30;
			}

		}

			
			
	

		break;
	default:
		break;
	}
	

	

	
	


//	}
/*
	if (currentTime > lastTime + delay * 14) {
		if (yellowSmall.x <= (screen_w + sky.w * zoom) / 2) {
			yellowSmall.x -= 10;
		}
	}
	if (currentTime > lastTime + delay * 19) {
		if (blue.x <= (screen_w + sky.w * zoom) / 2) {
			blue.x -= 10;
		}
	}
	if (currentTime > lastTime + delay * 26) {
		if (blueSmall.x <= (screen_w + sky.w * zoom) / 2) {
			blueSmall.x += 10;
		}
	}

	if (intro.HasFinished())
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 60);
	}
	
	*/
	
	


	return Update_Status::UPDATE_CONTINUE;
}



Update_Status IntroAnimation::PostUpdate() {

	App->render->Blit(introTexture, (screen_w - sky.w * zoom) / 2, (screen_h - sky.h * zoom) / 2, &sky, 1.0f, true, zoom);


	switch(animIndex){
	case 0:

		

		if (oposite == true) {
			App->render->Blit(introTexture, (screen_w - closeUp.w * zoom) / 2, (screen_h - closeUp.h * zoom) / 2, &closeUp, 1.0f, true, zoom);
		}
		else {
			App->render->Blit(introTexture, (screen_w - closeUpOposite.w * zoom) / 2, (screen_h - closeUpOposite.h * zoom) / 2, &closeUpOposite, 1.0f, true, zoom);
		}
		
		break;
	case 1:
		if (oposite == true) {
			App->render->Blit(introTexture, (screen_w - clouds.w * zoom) / 2, (screen_h - sky.h * zoom) / 2 + 16 * zoom, &clouds, 1.0f, true, zoom);
			App->render->Blit(introTexture, (screen_w - back.w * zoom) / 2, (screen_h - back.h * zoom) / 2, &back, 1.0f, true, zoom);
		}
		else {
			App->render->Blit(introTexture, (screen_w - clouds.w * zoom) / 2, (screen_h - sky.h * zoom) / 2 + 16 * zoom, &clouds, 1.0f, true, zoom);
			App->render->Blit(introTexture, (screen_w - backOposite.w * zoom) / 2, (screen_h - backOposite.h * zoom) / 2, &backOposite, 1.0f, true, zoom);
		}
		break;
	case 2:
		if (oposite == false) {
			App->render->Blit(introTexture, (screen_w - clouds.w * zoom) / 2, (screen_h - sky.h * zoom) / 2 + 16*zoom, &clouds, 1.0f, true, zoom);
			App->render->Blit(introTexture, (screen_w - fullBodyOposite.w * zoom) / 2, (screen_h - fullBodyOposite.h * zoom) / 2 + 1*zoom, &fullBodyOposite, 1.0f, true, zoom);
		}
		else {
			App->render->Blit(introTexture, (screen_w - clouds.w * zoom) / 2, (screen_h - sky.h * zoom) / 2 + 16 * zoom, &clouds, 1.0f, true, zoom);
			App->render->Blit(introTexture, (screen_w - fullBody.w * zoom) / 2, (screen_h - fullBody.h * zoom) / 2 + 1 * zoom, &fullBody, 1.0f, true, zoom);

		}
		break;
	case 3:
		App->render->Blit(introTexture, (screen_w - ground.w * zoom) / 2, (screen_h - sky.h * zoom) / 2 + (sky.h - ground.h) * zoom, &ground, 1.0f, true, zoom);
		App->render->Blit(introTexture, (screen_w - fullBodyBackOposite.w * zoom) / 2, (screen_h - sky.h * zoom) / 2 + 40 * zoom, &fullBodyBackOposite, 1.0f, true, zoom);
		if (yellow.x == (screen_w - sky.w * zoom) / 2) {
			App->render->Blit(introTexture, (screen_w - clouds.w * zoom) / 2, (screen_h - sky.h * zoom) / 2 + 16 * zoom, &clouds, 1.0f, true, zoom);
		}
		App->render->Blit(introTexture, yellow.x, yellow.y, &yellowCar, 1.0f, true, zoom);
		break;
	case 4:
		App->render->Blit(introTexture, (screen_w - ground.w * zoom) / 2, (screen_h - sky.h * zoom) / 2 + (sky.h - ground.h) * zoom, &ground, 1.0f, true, zoom);
		if (fullBodyWoman.x != 0 && fullBodyWoman.y != 0) {
			App->render->Blit(introTexture, fullBodyWoman.x, fullBodyWoman.y, &fullBodyBackOposite, 1.0f, true, zoom);
		}
		if (fullBodyThinking.x != 0 && fullBodyThinking.y != 0) {
			App->render->Blit(introTexture,fullBodyThinking.x, fullBodyThinking.y, &fullBodyBack, 1.0f, true, zoom);
		}
		if (fullBodyLeaving.x != 0 && fullBodyLeaving.y != 0) {
			App->render->Blit(introTexture, fullBodyLeaving.x, fullBodyLeaving.y, &leavingWoman, 1.0f, true, zoom);
		}
		App->render->Blit(introTexture, yellowSmall.x, yellowSmall.y, &yellowCarSmall, 1.0f, true, zoom);
		if (coffeeLeft.x != 0 && coffeeLeft.y != 0) {
			App->render->Blit(introTexture, coffeeLeft.x, coffeeLeft.y, &coffee, 1.0f, true, zoom);
		}
		if (yellowThink.x != 0 && yellowThink.y != 0) {
			App->render->Blit(introTexture, yellowThink.x, yellowThink.y, &disaproval, 1.0f, true, zoom);
		}
		if (coffeeRight.x != 0 && coffeeRight.y != 0) {
			App->render->Blit(introTexture, coffeeRight.x, coffeeRight.y, &coffeeOposite, 1.0f, true, zoom);
		}
		if (blackThink.x != 0 && blackThink.y != 0) {
			App->render->Blit(introTexture, blackThink.x, blackThink.y, &disapoint, 1.0f, true, zoom);
		}
		if (blue.x != 0 && blue.y != 0) {
			App->render->Blit(introTexture, blue.x, blue.y, &blueCar, 1.0f, true, zoom);
		}
		if (blueSmall.x != 0 && blueSmall.y != 0) {
			App->render->Blit(introTexture, blueSmall.x, blueSmall.y, &blueCarSmall, 1.0f, true, zoom);
		}

		break;
	case 5:
		if (blueSmall.x != 0 && blueSmall.y != 0) {
			App->render->Blit(introTexture, blueSmall.x, blueSmall.y, &blueCarSmall, 1.0f, true, zoom);
		}
		App->render->Blit(introTexture, (screen_w - ground.w * zoom) / 2, (screen_h - sky.h * zoom) / 2 + (sky.h - ground.h) * zoom, &ground, 1.0f, true, zoom);
		App->render->Blit(introTexture, yellowSmall.x, yellowSmall.y, &yellowCarSmall, 1.0f, true, zoom);
		if (blackThink.x != 0 && blackThink.y != 0) {
			App->render->Blit(introTexture, blackThink.x, blackThink.y, &disapoint, 1.0f, true, zoom);
		}
		
	case 6:
		if (smokeM.x != 0 && smokeM.y != 0) {
			App->render->Blit(introTexture, smokeM.x, smokeM.y, &smoke, 1.0f, true, zoom);
		}
		App->render->Blit(introTexture, (screen_w - ground.w * zoom) / 2, (screen_h - sky.h * zoom) / 2 + (sky.h - ground.h) * zoom, &ground, 1.0f, true, zoom);
		App->render->Blit(introTexture, yellowSmall.x, yellowSmall.y, &yellowCarSmall, 1.0f, true, zoom);
		if (sadMan.x != 0 && sadMan.y != 0) {
			App->render->Blit(introTexture, sadMan.x, sadMan.y, &sadProtagonist, 1.0f, true, zoom);
		}
		if (imaginCar.x != 0 && imaginCar.y != 0) {
			App->render->Blit(introTexture, imaginCar.x, imaginCar.y, &imagination, 1.0f, true, zoom);
		}
		break;
	default:
		break;
	}
	
	App->render->Blit(introTexture, (screen_w - sky.w * zoom) / 2 + sky.w * zoom -1*zoom, (screen_h - sky.h * zoom) / 2, &black, 1.0f, true, zoom);
	App->render->Blit(introTexture, (screen_w - sky.w * zoom) / 2 + sky.w * zoom - 1 * zoom, (screen_h - sky.h * zoom) / 2 + sky.h*zoom, &black, 1.0f, true, zoom);
	App->render->Blit(introTexture, (screen_w - sky.w * zoom) / 2 , (screen_h - sky.h * zoom) / 2 + sky.h*zoom -1*zoom, &black, 1.0f, true, zoom);
	App->render->Blit(introTexture, (screen_w - sky.w * zoom) / 2, (screen_h - sky.h * zoom) / 2 - sky.h * zoom + 1 * zoom, &black, 1.0f, true, zoom);
	App->render->Blit(introTexture, (screen_w - sky.w * zoom) / 2 - sky.w * zoom, (screen_h - sky.h * zoom) / 2, &black, 1.0f, true, zoom);
	App->render->Blit(introTexture, (screen_w - sky.w * zoom) / 2 - sky.w * zoom, (screen_h - sky.h * zoom) / 2 + sky.h*zoom, &black, 1.0f, true, zoom);
	
	


	if (App->lvlManage->godmode == true) {
		App->fonts->BlitText(App->winSize->w / 2 - 4 * 9 * 3, App->winSize->h - 50 * 3, menuFont, "GOD MODE", 3, 158, 75, 250, (App->winSize->w - 98 * 3) / 2 + 98 * 3 - 5 * 3);
	}

	return Update_Status::UPDATE_CONTINUE;
}

bool IntroAnimation::CleanUp()
{
	App->fonts->UnLoad(menuFont);
	App->textures->Unload(introTexture);
	App->introAnim->Disable();

	return true;
}