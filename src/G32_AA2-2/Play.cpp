#include "Play.h"

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
	SDL_Event event;
	if (event.type = SDL_KEYDOWN) {
		player1.setPlayerState(event);
	}
}
void Play::Update() {
	CheckPlayersCollisions(player1);
	InitBomb(player1);
	player1.Update();
	CheckPlayersCollisions(player2);
	InitBomb(player2);
	player2.Update();
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

	Renderer::Instance()->Render();
}

void Play::CheckPlayersCollisions(Player _player) {

	Cell upCell = map.getCell((int)_player.getPosition().x, (int)_player.getPosition().y - 1);
	SDL_Rect upColl = { upCell.pos.x, upCell.pos.y, 48, 48 };
	Cell downCell = map.getCell((int)_player.getPosition().x, (int)_player.getPosition().y + 1);
	SDL_Rect downColl = { downCell.pos.x, downCell.pos.y, 48, 48 };
	Cell leftCell = map.getCell((int)_player.getPosition().x-1, (int)_player.getPosition().y);
	SDL_Rect leftColl = { leftCell.pos.x, leftCell.pos.y, 48, 48 };
	Cell rightCell = map.getCell((int)_player.getPosition().x+1, (int)_player.getPosition().y);
	SDL_Rect rightColl = { rightCell.pos.x, rightCell.pos.y, 48, 48 };

	SDL_Rect result;

	
	switch (_player.getPlayerState()) {
		case UP:
			if (upCell.type != FLOOR || upCell.type != HELMET || upCell.type != SKATES)
				if (SDL_IntersectRect(&_player.getCollider(), &upColl,&result)) {
					_player.setPlayerStateToNONE();
				}
			break;
		case DOWN:
			if (downCell.type != FLOOR || downCell.type != HELMET || downCell.type != SKATES)
				if (SDL_IntersectRect(&_player.getCollider(), &downColl, &result)) {
					_player.setPlayerStateToNONE();
				}
			break;
		case LEFT:
			if (leftCell.type != FLOOR || leftCell.type != HELMET || leftCell.type != SKATES)
				if (SDL_IntersectRect(&_player.getCollider(), &leftColl, &result)) {
					_player.setPlayerStateToNONE();
				}
			break;
		case RIGHT:
			if (rightCell.type != FLOOR || rightCell.type != HELMET || rightCell.type != SKATES)
				if (SDL_IntersectRect(&_player.getCollider(), &rightColl, &result)) {
					_player.setPlayerStateToNONE();
				}
			break;
	}
}

void Play::CalculateBombExplosions(Player _player) {
	if (_player.getBomb().getTimer() > 3.0f) {
		
	}
}

void Play::InitBomb(Player _player) {
	Cell cell;
	if (_player.getPlayerState() == BOMB && _player.getBomb().getState()==DESACTIVE) {
		switch (_player.getPlayerFacing()) {
			case UP:
				cell = map.getCell(_player.getPosition().x, _player.getPosition().y - 1);
				_player.getBomb().Init(cell.pos);
				break;
			case DOWN:
				cell = map.getCell(_player.getPosition().x, _player.getPosition().y + 1);
				_player.getBomb().Init(cell.pos);
				break;
			case LEFT:
				cell = map.getCell(_player.getPosition().x-1, _player.getPosition().y);
				_player.getBomb().Init(cell.pos);
				break;
			case RIGHT:
				cell = map.getCell(_player.getPosition().x+1, _player.getPosition().y);
				_player.getBomb().Init(cell.pos);
				break;
		}
	}
	else if (_player.getPlayerState() == BOMB && _player.getBomb().getState() != DESACTIVE) {
		_player.setPlayerStateToNONE();
	}
}