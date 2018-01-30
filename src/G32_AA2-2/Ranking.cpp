#include "Ranking.h"

Ranking::Ranking(bool mode) {
	sceneState = SceneState::RUNNING;
	writeMode = mode;
	mouseDown.x = -1; mouseDown.y = -1;

	//FillEmptyBinary(PATH_FILES + "ranking.bin"); //SÓLO LO USO PARA CUANDO HE DE CREAR UN .BIN LIMPIO.
	ReadBinary(PATH_FILES + "ranking.bin");

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
	if (writeMode) {
		playScore = getPlayScore(PATH_FILES + "tmp.bin");
	}
	else {
		// Back Button:
		backButton.text = { RANKING_TEXT, "-back to Menu-",{ 0,0,0,255 }, 100, 100 };
		backButton.x = (SCREEN_WIDTH / 2) - (backButton.text.w / 2);
		backButton.y = (SCREEN_HEIGHT / 2) - (backButton.text.h / 2) + 300;
	}
	finishedInput = false;
	playerName = "[type name, then ENTER]";
}

void Ranking::FillEmptyBinary(std::string path) {
	for (int i = 0; i < 10; i++) {
		ranking[i].name = "[EMPTY]";
		ranking[i].points = 0;
	}
	std::string outNames[10];
	int outPoints[10];

	for (int i = 0; i < 10; i++) {
		outNames[i] = ranking[i].name;
		outPoints[i] = ranking[i].points;
	}

	std::ofstream binFileOUT(path, std::ios::out | std::ios::binary);
	for (int i = 0; i < 10; i++) {
		size_t len = outNames[i].size();
		binFileOUT.write(reinterpret_cast<char*>(&len), sizeof(size_t));
		binFileOUT.write(outNames[i].c_str(), outNames[i].size());
		//binFileOUT.write('\0', sizeof(char));
	}
	binFileOUT.write(reinterpret_cast<char *>(&outPoints), sizeof(int) * 10);

	binFileOUT.close();
}

int Ranking::getPlayScore(std::string path) {
	int tmp;
	std::ifstream binFileIN(path, std::ios::in | std::ios::binary);
	binFileIN.read(reinterpret_cast<char*>(&tmp), sizeof(int));
	binFileIN.close();
	return tmp;
}

void Ranking::ReadBinary(std::string path) {
	std::string inNames[10];
	int inPoints[10];

	std::ifstream binFileIN (path, std::ios::in | std::ios::binary);
	for (int i = 0; i < 10; i++) {
		size_t len;
		//std::getline(binFileIN, inNames[i], '\0');
		binFileIN.read(reinterpret_cast<char*>(&len), sizeof(size_t));
		char* tmp = new char[len];
		binFileIN.read(tmp, len);
		//tmp[len] = '\0';
		inNames[i] = "";
		inNames[i].append(tmp, len);
	}
	
	binFileIN.read(reinterpret_cast<char *>(&inPoints), sizeof(int) * 10);

	for (int i = 0; i < 10; i++) {
		ranking[i] = { inNames[i], inPoints[i] };
	}

	binFileIN.close();
}

void Ranking::WriteBinary(std::string path) {
	std::string outNames[10];
	int outPoints[10];

	for (int i = 0; i < 10; i++) {
		outNames[i] = ranking[i].name;
		outPoints[i] = ranking[i].points;
	}

	std::ofstream binFileOUT(path, std::ios::out | std::ios::binary);
	for (int i = 0; i < 10; i++) {
		size_t len = outNames[i].size();
		binFileOUT.write(reinterpret_cast<char*>(&len), sizeof(size_t));
		binFileOUT.write(outNames[i].c_str(), outNames[i].size());
		//binFileOUT.write('\0', sizeof(char));
	}
	binFileOUT.write(reinterpret_cast<char *>(&outPoints), sizeof(int) * 10);

	binFileOUT.close();
}

Ranking::~Ranking() {

}

void Ranking::EventsHandler() {
	if (writeMode) {
		SDL_Event event;
		if (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				sceneState = SceneState::EXIT;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_RETURN) {
					finishedInput = true;
				}
				break;
			case SDL_TEXTINPUT:
				if (!finishedInput) {
					if (playerName == "[type name, then ENTER]") {
						playerName.clear();
					}
					playerName.append(event.text.text);
					//strcat(playerName, event.text.text);
					//if (event.text.text == '\n') { finishedInput = true; }
				}
				break;
			}
		}
	}
	else {
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
}

bool Ranking::checkClick(Rect button, int x, int y) {
	return (x > button.x && x < (button.x + button.w) && y > button.y && y < (button.y + button.h));
}

void Ranking::Update() {
	if (writeMode) {
		/*std::string tmpName;
		std::cout << "Enter name:";
		std::cin >> tmpName;*/

		if (finishedInput) {
			int isRank = -1;
			for (int i = 0; i < 10; i++) {
				if (ranking[i].points < playScore) {
					isRank = i;
					break;
				}
			}
			if (isRank < 0) {
				sceneState = SceneState::GOTO_RANKING;
			}
			else {
				Entry carry[2];
				//carry[isRank % 2 != 0] = { tmpName, playScore };
				carry[isRank % 2 != 0] = { playerName, playScore };
				for (int i = isRank; i < 10; i++) {
					carry[i % 2 == 0] = ranking[i];
					ranking[i] = carry[i % 2 != 0];
				}
			}
			WriteBinary(PATH_FILES + "ranking.bin");
			for (int i = 0; i < 10; i++) {
				std::cout << ranking[i].name << " " << ranking[i].points << std::endl;
			}
			sceneState = SceneState::GOTO_RANKING;
		}
	}
	else {
		if (checkClick({ backButton.x, backButton.y, backButton.text.w, backButton.text.h }, mouseDown.x, mouseDown.y)) {
			sceneState = SceneState::GOTO_MENU;
		}
	}
}

void Ranking::Draw() {
	Renderer::Instance()->Clear();
	Renderer::Instance()->LoadFont({ RANKING_FONT, PATH_FONT + "game_over.ttf", 100 });

	if (writeMode) {
		Text title = { RANKING_TEXT, "Enter name:" ,{ 0,0,0,255 }, 100, 100 };
		Renderer::Instance()->LoadTextureText(RANKING_FONT, title);
		title.w = Renderer::Instance()->GetTextureSize(RANKING_TEXT).x;
		title.h = Renderer::Instance()->GetTextureSize(RANKING_TEXT).y;
		Vector2 pos;
		pos.x = (SCREEN_WIDTH / 2) - (title.w / 2);
		pos.y = (SCREEN_HEIGHT / 2) - (title.h / 2) - 150;
		Renderer::Instance()->PushImage(RANKING_TEXT, { pos.x, pos.y, title.w, title.h });

		title = { RANKING_TEXT, playerName ,{ 0,0,0,255 }, 100, 100 };
		Renderer::Instance()->LoadTextureText(RANKING_FONT, title);
		title.w = Renderer::Instance()->GetTextureSize(RANKING_TEXT).x;
		title.h = Renderer::Instance()->GetTextureSize(RANKING_TEXT).y;
		pos.x = (SCREEN_WIDTH / 2) - (title.w / 2);
		pos.y = (SCREEN_HEIGHT / 2) - (title.h / 2) - 100;
		Renderer::Instance()->PushImage(RANKING_TEXT, { pos.x, pos.y, title.w, title.h });

		//sceneState = SceneState::GOTO_RANKING;
	}
	else {
		Text title = { RANKING_TEXT, "RANKING", {0,0,0,255}, 100, 100 };
		Renderer::Instance()->LoadTextureText(RANKING_FONT, title);
		title.w = Renderer::Instance()->GetTextureSize(RANKING_TEXT).x;
		title.h = Renderer::Instance()->GetTextureSize(RANKING_TEXT).y;
		Vector2 pos;
		pos.x = (SCREEN_WIDTH / 2) - (title.w / 2);
		pos.y = (SCREEN_HEIGHT / 2) - (title.h / 2) - 300;
		Renderer::Instance()->PushImage(RANKING_TEXT, { pos.x, pos.y, title.w, title.h });

		for (int i = 0; i < 10; i++) {
			std::string pts = std::to_string(i+1) + " - " + ranking[i].name + ": " + std::to_string(ranking[i].points);
			//std::string pts = "Haha";
			Text tmp = { RANKING_TEXT , pts, {0,0,0,255}, 100, 100 };
			Renderer::Instance()->LoadTextureText(RANKING_FONT, tmp);
			tmp.w = Renderer::Instance()->GetTextureSize(RANKING_TEXT).x;
			tmp.h = Renderer::Instance()->GetTextureSize(RANKING_TEXT).y;
			pos.x = (SCREEN_WIDTH / 2) - (tmp.w / 2);
			pos.y = (SCREEN_HEIGHT / 2) - (tmp.h / 2) -250 + 50*i;
			Renderer::Instance()->PushImage(RANKING_TEXT, { pos.x, pos.y, tmp.w, tmp.h });
		}

		Renderer::Instance()->LoadTextureText(RANKING_FONT, backButton.text);
		backButton.text.w = Renderer::Instance()->GetTextureSize(RANKING_TEXT).x;
		backButton.text.h = Renderer::Instance()->GetTextureSize(RANKING_TEXT).y;
		backButton.x = (SCREEN_WIDTH / 2) - (backButton.text.w / 2);
		backButton.y = (SCREEN_HEIGHT / 2) - (backButton.text.h / 2) + 300;
		Renderer::Instance()->PushImage(RANKING_TEXT, { backButton.x, backButton.y, backButton.text.w, backButton.text.h });
	}
	Renderer::Instance()->Render();
}