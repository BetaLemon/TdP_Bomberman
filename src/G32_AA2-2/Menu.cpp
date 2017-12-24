#include "Menu.h"

Menu::Menu() {
	sceneState = SceneState::RUNNING;
	mouseDown.x = -1; mouseDown.y = -1;

	rapidxml::xml_document<> config;
	std::ifstream file(PATH_FILES + "config.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	config.parse<0>(&content[0]);

	rapidxml::xml_node<> *root = config.first_node("Game");	// <Game>
	//musicRunning = atoi(root->first_node("Music")->value());
	if (atoi(root->first_node("Music")->value()) == 0) {
		musicRunning = false;
	}
	else {
		musicRunning = true;
		music.AddSoundtrack(MENU_SOUND, PATH_AU + "menu.mp3");
		music.Play(MENU_SOUND);
	}

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

	// TOGGLE MUSIC BUTTON:
	musicButt.text.id = MENU_TEXT_BUTTON_MUSIC;
	musicButt.text.text = "Toggle Music";
	musicButt.text.color = { 0,0,0,255 };
	musicButt.text.w = 100;
	musicButt.text.h = 50;
	musicButt.x = (SCREEN_WIDTH / 2) - (musicButt.text.w / 2);
	musicButt.y = (SCREEN_HEIGHT / 2) - (musicButt.text.h / 2) + 100;

	// EXIT BUTTON:
	exitButt.text.id = MENU_TEXT_BUTTON_EXIT;
	exitButt.text.text = "Exit";
	exitButt.text.color = { 0,0,0,255 };
	exitButt.text.w = 100;
	exitButt.text.h = 50;
	exitButt.x = (SCREEN_WIDTH / 2) - (exitButt.text.w / 2);
	exitButt.y = (SCREEN_HEIGHT / 2) - (exitButt.text.h / 2) + 200;
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

bool Menu::checkClick(Rect button, int x, int y) {
	return (x > button.x && x < (button.x + button.w) && y > button.y && y < (button.y + button.h));
}

void Menu::Update() {

	if (mouseDown.x > 0 && mouseDown.y > 0) {

		if (checkClick({ play1Butt.x, play1Butt.y, play1Butt.text.w, play1Butt.text.h }, mouseDown.x, mouseDown.y)) {
			sceneState = SceneState::GOTO_PLAY1;
		}
		else if (checkClick({ play2Butt.x, play2Butt.y, play2Butt.text.w, play2Butt.text.h }, mouseDown.x, mouseDown.y)) {
			sceneState = SceneState::GOTO_PLAY2;
		}
		else if (checkClick({ rankButt.x, rankButt.y, rankButt.text.w, rankButt.text.h }, mouseDown.x, mouseDown.y)) {
			sceneState = SceneState::GOTO_RANKING;
		}
		else if (checkClick({ musicButt.x, musicButt.y, musicButt.text.w, musicButt.text.h }, mouseDown.x, mouseDown.y)) {
			//musicRunning = !musicRunning;

			rapidxml::xml_document<> config;
			std::ifstream file(PATH_FILES + "config.xml");
			std::stringstream buffer;
			buffer << file.rdbuf();
			file.close();
			std::string content(buffer.str());
			config.parse<rapidxml::parse_no_data_nodes>(&content[0]);

			rapidxml::xml_node<> *root = config.first_node("Game");	// <Game>
			if (musicRunning) {
				root->first_node("Music")->value("0");
			}
			else {
				root->first_node("Music")->value("1");
			}

			std::ofstream file_stored(PATH_FILES + "config.xml");
			file_stored << config;
			file_stored.close();
			config.clear();

			sceneState = SceneState::GOTO_MENU;
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

//	Rect tmp;
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

	// MUSIC BUTTON
	Renderer::Instance()->LoadTextureText(MENU_FONT, musicButt.text);
	musicButt.text.w = Renderer::Instance()->GetTextureSize(MENU_TEXT_BUTTON_MUSIC).x;
	musicButt.text.h = Renderer::Instance()->GetTextureSize(MENU_TEXT_BUTTON_MUSIC).y;
	musicButt.x = (SCREEN_WIDTH / 2) - (musicButt.text.w / 2);
	musicButt.y = (SCREEN_HEIGHT / 2) - (musicButt.text.h / 2) + 100;
	Renderer::Instance()->PushImage(MENU_TEXT_BUTTON_MUSIC, { musicButt.x, musicButt.y, musicButt.text.w, musicButt.text.h });

	// EXIT BUTTON
	Renderer::Instance()->LoadTextureText(MENU_FONT, exitButt.text);
	exitButt.text.w = Renderer::Instance()->GetTextureSize(MENU_TEXT_BUTTON_EXIT).x;
	exitButt.text.h = Renderer::Instance()->GetTextureSize(MENU_TEXT_BUTTON_EXIT).y;
	exitButt.x = (SCREEN_WIDTH / 2) - (exitButt.text.w / 2);
	exitButt.y = (SCREEN_HEIGHT / 2) - (exitButt.text.h / 2) + 200;
	Renderer::Instance()->PushImage(MENU_TEXT_BUTTON_EXIT, { exitButt.x, exitButt.y, exitButt.text.w, exitButt.text.h });

	Renderer::Instance()->Render();
}