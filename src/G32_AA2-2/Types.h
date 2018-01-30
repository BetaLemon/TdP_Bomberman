#pragma once
#include <string>
#include <SDL.h>

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

	using Rect = struct  Rect{ int  x; int y; int w; int h; };

	using Color = struct Color { Uint8 r; Uint8 g; Uint8 b; Uint8 a; };
	
	struct Vector2 {
		int x; int y;
		Vector2(int valueX = 0.0f, int valueY = 0.0f) : x{ valueX }, y{ valueY } {}
	};

	using Font = struct {
		std::string id;
		std::string path;
		int size;
	};

	using Text = struct {
		std::string id;
		std::string text;
		Color color;
		int w;
		int h;
	};

	struct Button {
		Text text;
		int x, y;
	};

	struct Clock {
		int prevTickTime = 0;
		int delta = 0;
		int SDLDeltaTicks = 0;
		void tick() {
			int tickTime = SDL_GetTicks() - SDLDeltaTicks;
			delta = tickTime - prevTickTime;
			prevTickTime = tickTime;
		}
	};

	enum class Key {UP, DOWN, LEFT, RIGHT, NONE};
