#include "Play.h"
#include <iostream>
Play::Play() {
	sceneState = SceneState::RUNNING;
	map = Map(1);
}

Play::Play(int level) {
	sceneState = SceneState::RUNNING;
	map = Map(level);
	player1 = Player(0, {576,120});
	player2 = Player(1, { 576,200});
}

Play::~Play() {

}

void Play::EventsHandler() {
	const Uint8 *keyboardArray = SDL_GetKeyboardState(NULL);
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type = SDL_KEYDOWN) {
			player1.setPlayerState(event,keyboardArray);
			player2.setPlayerState(event,keyboardArray);
		}
	}
}
void Play::Update() {
	
	player1.Update();
	player2.Update();
	if (player1.getPlayerState() == BOMB) InitBomb(player1);
	if (player2.getPlayerState() == BOMB) InitBomb(player2);
	
}

void Play::Draw() {

	// !!! HE PUESTO QUE PLAY DIBUJA A MAP. ESTÁ BIEN ????

	Renderer::Instance()->Clear();

	// Background:
	Renderer::Instance()->LoadTexture(PLAY_BG, PATH_IMG + "bgGame.jpg");
	Renderer::Instance()->PushImage(PLAY_BG, { 0,0,SCREEN_WIDTH, SCREEN_HEIGHT });

	// Tiles:
	map.Map::Draw();

	// Player:
	player1.Player::Draw();
	player2.Player::Draw();
	player1.getBomb().Bomb::Draw();
	player2.getBomb().Bomb::Draw();

	Renderer::Instance()->Render();
}



void Play::InitBomb(Player _player) {

	if (_player.getBomb().getState() == WAITING) {

		switch (_player.getPlayerFacing()) {
		case UP: {

			Vector2 tmp(_player.getPlayerGrid().x, _player.getPlayerGrid().y - 1);
			if (map.getCell(tmp).type == FLOOR)
				_player.getBomb().Init(tmp);
			_player.setPlayerStateToNONE();
			break;
		}
		case DOWN: {
			Vector2 tmp(_player.getPlayerGrid().x, _player.getPlayerGrid().y + 1);
			if (map.getCell(tmp).type == FLOOR)
				_player.getBomb().Init(tmp);
			_player.setPlayerStateToNONE();
			break;
		}
		case LEFT: {
			Vector2 tmp(_player.getPlayerGrid().x - 1, _player.getPlayerGrid().y);
			if (map.getCell(tmp).type == FLOOR)
				_player.getBomb().Init(tmp);
			_player.setPlayerStateToNONE();
			break;
		}
		case RIGHT: {
			Vector2 tmp(_player.getPlayerGrid().x + 1, _player.getPlayerGrid().y);
			std::cout << map.getCell(tmp).type;
			if (map.getCell(tmp).type == FLOOR)
				_player.getBomb().Init(tmp);
			_player.setPlayerStateToNONE();
			break;
		}
		}
	}
	else if (_player.getBomb().getState() == ACTIVE) {
		_player.setPlayerStateToNONE();
	}
}

