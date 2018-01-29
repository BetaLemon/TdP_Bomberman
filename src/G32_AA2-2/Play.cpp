#include "Play.h"

Play::Play() {
	sceneState = SceneState::RUNNING;
	map = Map(1);
	Renderer::Instance()->LoadTexture(PLAY_BG, PATH_IMG + "bgGame.jpg");
	Renderer::Instance()->LoadFont({ HUD_FONT, PATH_FONT + "game_over.ttf", 60 });
}

Play::Play(int level) {
	sceneState = SceneState::RUNNING;

	Renderer::Instance()->LoadTexture(PLAY_BG, PATH_IMG + "bgGame.jpg");
	Renderer::Instance()->LoadFont({ HUD_FONT, PATH_FONT + "game_over.ttf", 60 });

	map = Map(level);
	switch (level) {
	case 1:
		player1 = Player(0, { (CELL_WIDTH * 11) - CELL_WIDTH/2, (CELL_HEIGHT * 2) + HUD_HEIGHT - CELL_HEIGHT/2});
		player2 = Player(1, {(CELL_WIDTH * 11) - CELL_WIDTH / 2, (CELL_HEIGHT * 4) + HUD_HEIGHT - CELL_HEIGHT / 2});
		break;
	case 2:
		player1 = Player(0, { 576,120 });
		player2 = Player(1, { 576,200 });
		break;
	default:;
	}

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
		music.AddSoundtrack(PLAY_SOUND, PATH_AU + "game_theme.mp3");
		music.Play(PLAY_SOUND);
	}

}

Play::~Play() {

}

void Play::EventsHandler() {
	const Uint8 *keyboardArray = SDL_GetKeyboardState(NULL);
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN) {
			player1.setPlayerState(event,keyboardArray);
			player2.setPlayerState(event,keyboardArray);
			// Esto tendr�a que estar en Update:
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				sceneState = SceneState::GOTO_MENU;
			}
			/*if (event.key.keysym.sym == SDLK_SPACE) {
				sceneState = SceneState::GOTO_SETSCORE;
			}*/
		}
	}
}

PlayerMoveAllow Play::CanPlayerMove(Player _player) {

	Rect player;
	player.x = _player.getGridPos().x;
	player.y = _player.getGridPos().y;
	player.w = PLAYER_WIDTH;
	player.h = PLAYER_HEIGHT;

	PlayerMoveAllow canMove = { true, true, true, true };

	Cell up, down, left, right;
	up = map.getCell({ player.x, player.y - 1});
	down = map.getCell({ player.x, player.y + 1 });
	left = map.getCell({ player.x - 1, player.y });
	right = map.getCell({ player.x + 1, player.y });

	up.pos = map.getCellPixPos(up.pos);
	down.pos = map.getCellPixPos(down.pos);
	left.pos = map.getCellPixPos(left.pos);
	right.pos = map.getCellPixPos(right.pos);

	if (up.type == Celltype::FIXED || up.type == Celltype::DESTRUCTIBLE) {
		canMove.up = false;
	}
	if (down.type == Celltype::FIXED || down.type == Celltype::DESTRUCTIBLE) {
		canMove.down = false;
	}
	if (left.type == Celltype::FIXED || left.type == Celltype::DESTRUCTIBLE) {
		canMove.left = false;
	}
	if (right.type == Celltype::FIXED || right.type == Celltype::DESTRUCTIBLE) {
		canMove.right = false;
	}

	return canMove;
}

void Play::PlayerCollision(Player* p1, Player* p2) {
	PlayerMoveAllow canMove1 = p1->getCanMove();
	PlayerMoveAllow canMove2 = p2->getCanMove();

	Vector2 pos1 = p1->getGridPos(); std::cout << pos1.x << " " << pos1.y << std::endl;
	Vector2 pos2 = p2->getGridPos(); std::cout << pos2.x << " " << pos2.y << std::endl;

	if (pos1.x == pos2.x && pos1.y == pos2.y - 1) { canMove1.down = false; canMove2.up = false; }	// p1 is above p2.
	if (pos1.x == pos2.x && pos1.y == pos2.y + 1) { canMove1.up = false; canMove2.down = false; }	// p1 is below p2.
	if (pos1.x == pos2.x - 1 && pos1.y == pos2.y) { canMove1.right = false; canMove2.left = false; }	// p1 is to the right of p2.
	if (pos1.x == pos2.x + 1 && pos1.y == pos2.y) { canMove1.left = false; canMove2.right = false; }	// p1 is to the left of p2.

	p1->setCanMove(canMove1);
	p2->setCanMove(canMove2);
}

int Play::explodeMap(Vector2 center) {

	int cellCount = 0;
	map.destroyCell(center);
	if (map.getCell({ center.x, center.y - 1 }).type == Celltype::DESTRUCTIBLE) {	// [x, y-1]
		map.destroyCell({ center.x, center.y - 1 });
		cellCount++;
	}
	else if (map.getCell({ center.x, center.y - 2 }).type == Celltype::DESTRUCTIBLE) {	// [x, y-2]
		if (map.getCell({ center.x, center.y - 1 }).type == Celltype::FLOOR) {
			map.destroyCell({ center.x, center.y - 2 });
			cellCount++;
		}
	}
	if (map.getCell({ center.x, center.y + 1 }).type == Celltype::DESTRUCTIBLE) {	// [x, y+1]
		map.destroyCell({ center.x, center.y + 1 });
		cellCount++;
	}
	else if (map.getCell({ center.x, center.y + 2 }).type == Celltype::DESTRUCTIBLE) {	// [x, y+2]
		if (map.getCell({ center.x, center.y + 1 }).type == Celltype::FLOOR) {
			map.destroyCell({ center.x, center.y + 2 });
			cellCount++;
		}
	}
	if (map.getCell({ center.x + 1, center.y }).type == Celltype::DESTRUCTIBLE) {	// [x+1, y]
		map.destroyCell({ center.x + 1, center.y });
		cellCount++;
	}
	else if (map.getCell({ center.x + 2, center.y }).type == Celltype::DESTRUCTIBLE) {	// [x+2, y]
		if (map.getCell({ center.x + 1, center.y }).type == Celltype::FLOOR) {
			map.destroyCell({ center.x + 2, center.y });
			cellCount++;
		}
	}
	if (map.getCell({ center.x - 1, center.y }).type == Celltype::DESTRUCTIBLE) {	// [x-1, y]
		map.destroyCell({ center.x - 1, center.y });
		cellCount++;
	}
	else if (map.getCell({ center.x - 2, center.y }).type == Celltype::DESTRUCTIBLE) {	// [x-2, y]
		if (map.getCell({ center.x - 1, center.y }).type == Celltype::FLOOR) {
			map.destroyCell({ center.x - 2, center.y });
			cellCount++;
		}
	}

	Vector2 p = player1.getGridPos();
	if (center.x == p.x && center.y == p.y) { player2.addPoints(DEATH_POINTS); }
	if (center.x + 1 == p.x && center.y == p.y) { player2.addPoints(DEATH_POINTS); }
	if (center.x + 2 == p.x && center.y == p.y) { player2.addPoints(DEATH_POINTS); }
	if (center.x == p.x && center.y + 1 == p.y) { player2.addPoints(DEATH_POINTS); }
	if (center.x == p.x && center.y + 2 == p.y) { player2.addPoints(DEATH_POINTS); }
	if (center.x == p.x && center.y - 1 == p.y) { player2.addPoints(DEATH_POINTS); }
	if (center.x == p.x && center.y - 2 == p.y) { player2.addPoints(DEATH_POINTS); }
	if (center.x - 1 == p.x && center.y == p.y) { player2.addPoints(DEATH_POINTS); }
	if (center.x - 2 == p.x && center.y == p.y) { player2.addPoints(DEATH_POINTS); }

	p = player2.getGridPos();
	if (center.x == p.x && center.y == p.y) { player1.addPoints(DEATH_POINTS); }
	if (center.x + 1 == p.x && center.y == p.y) { player1.addPoints(DEATH_POINTS); }
	if (center.x == p.x && center.y + 1 == p.y) { player1.addPoints(DEATH_POINTS); }
	if (center.x == p.x && center.y - 1 == p.y) { player1.addPoints(DEATH_POINTS); }
	if (center.x - 1 == p.x && center.y == p.y) { player1.addPoints(DEATH_POINTS); }

	return cellCount;
}

BombRange Play::explodeRange(Vector2 center) {
	BombRange range = {2,2,2,2};

	// Calculating range:
	if (map.getCell({ center.x, center.y - 1 }).type != Celltype::FLOOR) {	// [x, y-1]
		range.up = 0;
	}
	if (map.getCell({ center.x, center.y - 2 }).type != Celltype::FLOOR) {	// [x, y-2]
		range.up = 1;
	}
	if (map.getCell({ center.x, center.y + 1 }).type != Celltype::FLOOR) {	// [x, y+1]
		range.down = 0;
	}
	if (map.getCell({ center.x, center.y + 2 }).type != Celltype::FLOOR) {	// [x, y+2]
		range.down = 1;
	}
	if (map.getCell({ center.x + 1, center.y }).type != Celltype::FLOOR) {	// [x+1, y]
		range.right = 0;
	}
	if (map.getCell({ center.x + 2, center.y }).type != Celltype::FLOOR) {	// [x+2, y]
		range.right = 1;
	}
	if (map.getCell({ center.x - 1, center.y }).type != Celltype::FLOOR) {	// [x-1, y]
		range.left = 0;
	}
	if (map.getCell({ center.x - 2, center.y }).type != Celltype::FLOOR) {	// [x-2, y]
		range.left = 1;
	}
	return range;
}

void Play::Update() {

	player1.setCanMove(CanPlayerMove(player1));
	player2.setCanMove(CanPlayerMove(player2));

	PlayerCollision(&player1, &player2);

	player1.Update();
	player2.Update();

	if (map.getCell(player1.getGridPos()).type == Celltype::FLOOR) {
		if (player1.getPlayerState() == BOMB) InitBomb(player1);
	}
	if (map.getCell(player2.getGridPos()).type == Celltype::FLOOR) {
		if (player2.getPlayerState() == BOMB) InitBomb(player2);
	}

	Bomb tmp = player1.getBomb();
	if (tmp.getState() == BombState::ACTIVE) {
		BombRange rng = explodeRange(tmp.getGridPos());
		player1.setBombRange(rng);
		if (tmp.hasExploded()) {
			player1.addPoints(explodeMap(tmp.getGridPos()) * BLOCK_POINTS);
		}
	}
	tmp = player2.getBomb();
	if (tmp.getState() == BombState::ACTIVE) {
		BombRange rng = explodeRange(tmp.getGridPos());
		player2.setBombRange(rng);
		if (tmp.hasExploded()) {
			player2.addPoints(explodeMap(tmp.getGridPos()) * BLOCK_POINTS);
		}
	}
	/*
	BombRange tmpRange = { 0,0,0,0 };
	player2.setBombRange(tmpRange);
	if (tmp.hasExploded()) { player1.addPoints(explodeMap(tmp.getGridPos()) * BLOCK_POINTS); tmpRange = explodeRange(tmp.getGridPos()); }
	if (tmp.getState() == BombState::ACTIVE) { player1.setBombRange(tmpRange); }
	tmp = player2.getBomb();
	player2.setBombRange(tmpRange);
	if (tmp.hasExploded()) { player2.addPoints(explodeMap(tmp.getGridPos()) * BLOCK_POINTS); tmpRange = explodeRange(tmp.getGridPos()); }
	//if (tmp.getState() == BombState::ACTIVE) { player2.setBombRange(tmpRange); }*/
}

void Play::Draw() {

	Renderer::Instance()->Clear();

	// Background:
	Renderer::Instance()->PushImage(PLAY_BG, { 0,0,SCREEN_WIDTH, SCREEN_HEIGHT });

	// HUD:
		// player 1 life:
	std::string tmp = "P1 LIFE: " + std::to_string(player1.getLife());
	Text lifePlayer1 = { HUD_TEXT_LIFE_PLAYER1, tmp ,{ 0, 0, 0, 255 }, 15, 5 };
	Vector2 tmpSize;
	tmpSize = Renderer::Instance()->GetTextureSize(HUD_TEXT_LIFE_PLAYER1);
	Renderer::Instance()->LoadTextureText(HUD_FONT, lifePlayer1);
	Renderer::Instance()->PushImage(HUD_TEXT_LIFE_PLAYER1, { 25, 0, tmpSize.x, tmpSize.y });

		// player 2 life:
	tmp = "P2 LIFE: " + std::to_string(player2.getLife());
	Text lifePlayer2 = { HUD_TEXT_LIFE_PLAYER2, tmp ,{ 0, 0, 0, 255 }, 15, 5 };
	tmpSize = Renderer::Instance()->GetTextureSize(HUD_TEXT_LIFE_PLAYER2);
	Renderer::Instance()->LoadTextureText(HUD_FONT, lifePlayer2);
	Renderer::Instance()->PushImage(HUD_TEXT_LIFE_PLAYER2, { SCREEN_WIDTH - 150, 0, tmpSize.x, tmpSize.y });

		// player 1 points:
	tmp = "P1 POINTS: " + std::to_string(player1.getPoints());
	Text pointsPlayer1 = { HUD_TEXT_POINTS_PLAYER1, tmp ,{ 0, 0, 0, 255 }, 15, 5 };
	tmpSize = Renderer::Instance()->GetTextureSize(HUD_TEXT_POINTS_PLAYER1);
	Renderer::Instance()->LoadTextureText(HUD_FONT, pointsPlayer1);
	Renderer::Instance()->PushImage(HUD_TEXT_POINTS_PLAYER1, { 25, 20, tmpSize.x, tmpSize.y });

		// player 2 points:
	tmp = "P2 POINTS: " + std::to_string(player2.getPoints());
	Text pointsPlayer2 = { HUD_TEXT_POINTS_PLAYER2, tmp ,{ 0, 0, 0, 255 }, 15, 5 };
	tmpSize = Renderer::Instance()->GetTextureSize(HUD_TEXT_POINTS_PLAYER2);
	Renderer::Instance()->LoadTextureText(HUD_FONT, pointsPlayer2);
	Renderer::Instance()->PushImage(HUD_TEXT_POINTS_PLAYER2, { SCREEN_WIDTH - 180, 20, tmpSize.x, tmpSize.y });

	// Tiles:
	map.Map::Draw();

	// Player:
	player1.Player::Draw();
	player2.Player::Draw();

	Renderer::Instance()->Render();
}



void Play::InitBomb(Player _player) {

	if (_player.getBomb().getState() == WAITING) {

		switch (_player.getPlayerFacing()) {
		case UP: {

			Vector2 tmp(_player.getGridPos().x, _player.getGridPos().y - 1);
			if (map.getCell(tmp).type == FLOOR)
			_player.setPlayerStateToNONE();
			break;
		}
		case DOWN: {
			Vector2 tmp(_player.getGridPos().x, _player.getGridPos().y + 1);
			if (map.getCell(tmp).type == FLOOR)
				_player.getBomb().Init(tmp);
			_player.setPlayerStateToNONE();
			break;
		}
		case LEFT: {
			Vector2 tmp(_player.getGridPos().x - 1, _player.getGridPos().y);
			if (map.getCell(tmp).type == FLOOR)
				_player.getBomb().Init(tmp);
			_player.setPlayerStateToNONE();
			break;
		}
		case RIGHT: {
			Vector2 tmp(_player.getGridPos().x + 1, _player.getGridPos().y);
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