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
	CheckPlayersCollisions(player1);
	InitBomb(player1);
	player1.Update();
	CheckPlayersCollisions(player2);
	InitBomb(player2);
	player2.Update();
}

void Play::Draw() {

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

bool Play::Collision(Rect _player, Rect other) {
	Vector2 upleft, upright, downright, downleft;
	upleft.x = other.x; upleft.y = other.y;
	upright.x = other.x + other.w; upright.y = other.y;
	downright.x = other.x + other.w; downright.y = other.y + other.h;
	downleft.x = other.x; downleft.y = other.y + other.h;

	if (upleft.x > _player.x && upleft.y > _player.y && upleft.x < (_player.x + _player.w) && upleft.y < (_player.y + _player.h)) { return true; }
	else if (upright.x > _player.x && upright.y > _player.y && upright.x < (_player.x + _player.w) && upright.y < (_player.y + _player.h)) { return true; }
	else if (downright.x > _player.x && downright.y > _player.y && downright.x < (_player.x + _player.w) && downright.y < (_player.y + _player.h)) { return true; }
	else if (downleft.x > _player.x && downleft.y > _player.y && downleft.x < (_player.x + _player.w) && downleft.y < (_player.y + _player.h)) { return true; }
	else return false;
	std::cout << "shit" << std::endl;
}

void Play::CheckPlayersCollisions(Player _player) {

	Vector2 playerGridPosition = _player.getGridPos();	// Recoge la posición del jugador relativa al tablero (x, y por casillas).
	Vector2 playerPosition = _player.getPosition();		// Recoge la posición del jugador absoluta (x,y por píxeles).
	Cell up = map.getCell(playerGridPosition.x, playerGridPosition.y - 1);		// Recoge la casilla que se encuentra arriba del jugador.
	Cell down = map.getCell(playerGridPosition.x, playerGridPosition.y + 1);	// Recoge la casilla que se encuentra abajo del jugador.
	Cell left = map.getCell(playerGridPosition.x - 1, playerGridPosition.y);	// Recoge la casilla que se encuentra a la izquierda del jugador.
	Cell right = map.getCell(playerGridPosition.x + 1, playerGridPosition.y);	// Recoge la casilla que se encuentra a la derecha del jugador.

	//CanMove canMove = _player.getCanMove();

	CanMove canMove = {false, false, false, false };

	if (up.type != Celltype::FLOOR && up.type != Celltype::SKATES && up.type != Celltype::HELMET) {
		if (Collision({ playerPosition.x, playerPosition.y, PLAYER_WIDTH, PLAYER_HEIGHT }, { up.pos.x, up.pos.y, CELL_WIDTH, CELL_WIDTH })) {
			canMove.up = false;
		}
		//canMove.up = false;	std::cout << "hello" << std::endl;
		else { canMove.up = true; }
	}
	else { canMove.up = true; }

	if (down.type != Celltype::FLOOR && down.type != Celltype::SKATES && down.type != Celltype::HELMET) {
		if (Collision({ down.pos.x, down.pos.y, CELL_HEIGHT, CELL_WIDTH }, { playerPosition.x, playerPosition.y, PLAYER_WIDTH, PLAYER_HEIGHT })) {
			canMove.down = false;
		}
		else { canMove.down = true; }
	}
	else { canMove.down = true; }

	if (left.type != Celltype::FLOOR && left.type != Celltype::SKATES && left.type != Celltype::HELMET) {
		if (Collision({ left.pos.x, left.pos.y, CELL_HEIGHT, CELL_WIDTH }, { playerPosition.x, playerPosition.y, PLAYER_WIDTH, PLAYER_HEIGHT })) {
			canMove.left = false;
		}
		else { canMove.left = true; }
	}
	else { canMove.left = true; }

	if (right.type != Celltype::FLOOR && right.type != Celltype::SKATES && right.type != Celltype::HELMET) {
		if (Collision({ right.pos.x, right.pos.y, CELL_HEIGHT, CELL_WIDTH }, { playerPosition.x, playerPosition.y, PLAYER_WIDTH, PLAYER_HEIGHT })) {
			canMove.right = false;
		}
		else { canMove.right = true; }
	}
	else { canMove.right = true; }
	
	//std::cout << "up: " << canMove.up << " down: " << canMove.down << " left: " << canMove.left << " right: " << canMove.right << std::endl;
	_player.setCanMove(canMove);

	/*
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
	}*/
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