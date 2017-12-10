#include "Play.h"

Play::Play(int level) {
	switch (level) {
	case 1:
		
		break;
	case 2:
		break;
	default:;
	}
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
	player1.Update();
	CheckPlayersCollisions(player2);
	player2.Update();
}

void Play::CheckPlayersCollisions(Player _player) {
	switch (_player.getPlayerState()) {
		case UP:
			if (map.getCell(_player.getPosition().x, _player.getPosition().y - 1).type != FLOOR || map.getCell(_player.getPosition().x, _player.getPosition().y - 1).type != HELMET || map.getCell(_player.getPosition().x, _player.getPosition().y - 1).type != SKATES)
				_player.setPlayerStateToNONE();
			break;
		case DOWN:
			if (map.getCell(_player.getPosition().x, _player.getPosition().y + 1).type != FLOOR || map.getCell(_player.getPosition().x, _player.getPosition().y + 1).type != HELMET || map.getCell(_player.getPosition().x, _player.getPosition().y + 1).type != SKATES)
				_player.setPlayerStateToNONE();
			break;
		case LEFT:
			if (map.getCell(_player.getPosition().x-1, _player.getPosition().y).type != FLOOR || map.getCell(_player.getPosition().x-1, _player.getPosition().y ).type != HELMET || map.getCell(_player.getPosition().x-1, _player.getPosition().y).type != SKATES)
				_player.setPlayerStateToNONE();
			break;
		case RIGHT:
			if (map.getCell(_player.getPosition().x + 1, _player.getPosition().y).type != FLOOR || map.getCell(_player.getPosition().x + 1, _player.getPosition().y).type != HELMET || map.getCell(_player.getPosition().x + 1, _player.getPosition().y).type != SKATES)
				_player.setPlayerStateToNONE();
			break;
	}
}

void Play::Draw() {

}