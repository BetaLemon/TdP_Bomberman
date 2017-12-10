#include "Menu.h"

Menu::Menu() {
	sceneState = SceneState::RUNNING;
}

Menu::~Menu() {

}

void Menu::EventsHandler() {

}

void Menu::Update() {
	
}

void Menu::Draw() {
	Renderer::Instance()->LoadFont({ MENU_FONT, PATH_FONT + "Bomberman.ttf", 30 });
	Renderer::Instance()->LoadTextureText(MENU_FONT, { MENU_TEXT_BUTTON_PLAY, "Play", {255,255,255,255}, 20,10 });
	Renderer::Instance()->PushImage(MENU_FONT, { 10,10,20,10 });
}