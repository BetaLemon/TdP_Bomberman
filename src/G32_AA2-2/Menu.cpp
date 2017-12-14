#include "Menu.h"
#include <iostream>

Menu::Menu() {
	sceneState = SceneState::RUNNING;
	mouseDown.x = -1; mouseDown.y = -1;

	// PLAY 1 BUTTON:
	play1Butt.text.id = MENU_TEXT_BUTTON_PLAY1;
	play1Butt.text.text = "Play Level 1";
	play1Butt.text.color = { 0,0,0,255 };
	play1Butt.text.w = 100;
	play1Butt.text.h = 50;
	play1Butt.x = (SCREEN_WIDTH / 2) - (play1Butt.text.w / 2);
	play1Butt.y = (SCREEN_HEIGHT / 2) - (play1Butt.text.h / 2) - 200;

	// PLAY 2 BUTTON:
	play2Butt.text.id = MENU_TEXT_BUTTON_PLAY2;
	play2Butt.text.text = "Play Level 2";
	play2Butt.text.color = { 0,0,0,255 };
	play2Butt.text.w = 100;
	play2Butt.text.h = 50;
	play2Butt.x = (SCREEN_WIDTH / 2) - (play2Butt.text.w / 2);
	play2Butt.y = (SCREEN_HEIGHT / 2) - (play2Butt.text.h / 2) - 100;

	// RANKING BUTTON:
	rankButt.text.id = MENU_TEXT_BUTTON_RANK;
	rankButt.text.text = "Ranking";
	rankButt.text.color = { 0,0,0,255 };
	rankButt.text.w = 100;
	rankButt.text.h = 50;
	rankButt.x = (SCREEN_WIDTH / 2) - (rankButt.text.w / 2);
	rankButt.y = (SCREEN_HEIGHT / 2) - (rankButt.text.h / 2) - 0;

	// EXIT BUTTON:
	exitButt.text.id = MENU_TEXT_BUTTON_EXIT;
	exitButt.text.text = "Exit";
	exitButt.text.color = { 0,0,0,255 };
	exitButt.text.w = 100;
	exitButt.text.h = 50;
	exitButt.x = (SCREEN_WIDTH / 2) - (exitButt.text.w / 2);
	exitButt.y = (SCREEN_HEIGHT / 2) - (exitButt.text.h / 2) + 100;
}

Menu::~Menu() {

}

void Menu::EventsHandler() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			// Esto hay que hacerlo en el update:
			sceneState = SceneState::EXIT;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				mouseDown.x = event.button.x;
				mouseDown.y = event.button.y;
			}
		default:
			//mouseDown.x = -1;
			//mouseDown.y = -1;
			break;
		}
	}
}

bool checkClick(Rect button, int x, int y) {
	return (x > button.x && x < (button.x + button.w) && y > button.y && y < (button.y + button.h));
}

void Menu::Update() {
	if (mouseDown.x > 0 && mouseDown.y > 0) {
		std::cout << "Debug me please." << std::endl;
		if (checkClick({ play1Butt.x, play1Butt.y, play1Butt.text.w, play1Butt.text.h }, mouseDown.x, mouseDown.y)) {
			sceneState = SceneState::GOTO_PLAY1;
			std::cout << "Debug me please." << std::endl;
		}
		else if (checkClick({ play2Butt.x, play2Butt.y, play2Butt.text.w, play2Butt.text.h }, mouseDown.x, mouseDown.y)) {
			sceneState = SceneState::GOTO_PLAY2;
		}
		else if (checkClick({ rankButt.x, rankButt.y, rankButt.text.w, rankButt.text.h }, mouseDown.x, mouseDown.y)) {
			sceneState = SceneState::GOTO_RANKING;
		}
		else if (checkClick({ exitButt.x, exitButt.y, exitButt.text.w, exitButt.text.h }, mouseDown.x, mouseDown.y)) {
			sceneState = SceneState::EXIT;
		}
	}
}

void Menu::Draw() {

	Renderer::Instance()->Clear();
	Renderer::Instance()->LoadFont({ MENU_FONT, PATH_FONT + "game_over.ttf", 100 });

	// PLAY 1 BUTTON:
	Renderer::Instance()->LoadTextureText(MENU_FONT, play1Butt.text);
	play1Butt.text.w = Renderer::Instance()->GetTextureSize(MENU_TEXT_BUTTON_PLAY1).x;
	play1Butt.text.h = Renderer::Instance()->GetTextureSize(MENU_TEXT_BUTTON_PLAY1).y;
	play1Butt.x = (SCREEN_WIDTH / 2) - (play1Butt.text.w / 2);
	play1Butt.y = (SCREEN_HEIGHT / 2) - (play1Butt.text.h / 2) - 200;
	Renderer::Instance()->PushImage(MENU_TEXT_BUTTON_PLAY1, { play1Butt.x, play1Butt.y, play1Butt.text.w, play1Butt.text.h });

	Rect tmp;
	// PLAY 2 BUTTON
	Renderer::Instance()->LoadTextureText(MENU_FONT, play2Butt.text);
	play2Butt.text.w = Renderer::Instance()->GetTextureSize(MENU_TEXT_BUTTON_PLAY2).x;
	play2Butt.text.h = Renderer::Instance()->GetTextureSize(MENU_TEXT_BUTTON_PLAY2).y;
	play2Butt.x = (SCREEN_WIDTH / 2) - (play2Butt.text.w / 2);
	play2Butt.y = (SCREEN_HEIGHT / 2) - (play2Butt.text.h / 2) - 100;
	Renderer::Instance()->PushImage(MENU_TEXT_BUTTON_PLAY2, { play2Butt.x, play2Butt.y, play2Butt.text.w, play2Butt.text.h });

	// RANKING BUTTON
	Renderer::Instance()->LoadTextureText(MENU_FONT, rankButt.text);
	rankButt.text.w = Renderer::Instance()->GetTextureSize(MENU_TEXT_BUTTON_RANK).x;
	rankButt.text.h = Renderer::Instance()->GetTextureSize(MENU_TEXT_BUTTON_RANK).y;
	rankButt.x = (SCREEN_WIDTH / 2) - (rankButt.text.w / 2);
	rankButt.y = (SCREEN_HEIGHT / 2) - (rankButt.text.h / 2) - 0;
	Renderer::Instance()->PushImage(MENU_TEXT_BUTTON_RANK, { rankButt.x, rankButt.y, rankButt.text.w, rankButt.text.h });

	// EXIT BUTTON
	Renderer::Instance()->LoadTextureText(MENU_FONT, exitButt.text);
	exitButt.text.w = Renderer::Instance()->GetTextureSize(MENU_TEXT_BUTTON_EXIT).x;
	exitButt.text.h = Renderer::Instance()->GetTextureSize(MENU_TEXT_BUTTON_EXIT).y;
	exitButt.x = (SCREEN_WIDTH / 2) - (exitButt.text.w / 2);
	exitButt.y = (SCREEN_HEIGHT / 2) - (exitButt.text.h / 2) + 100;
	Renderer::Instance()->PushImage(MENU_TEXT_BUTTON_EXIT, { exitButt.x, exitButt.y, exitButt.text.w, exitButt.text.h });

	Renderer::Instance()->Render();
}