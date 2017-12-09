#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_image.h>	// Fons de pantalla - personatge - moviment
#include <SDL_ttf.h>	// Fonts - textos - botons
#include <SDL_mixer.h>  // Música - sons
#include <iostream>
#include <time.h>

//Game general information
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FPS 60

//Scenes:
enum class Scene{MENU,GAME};
enum class Move{UP, DOWN, LEFT, RIGHT, NONE};

int main(int, char*[]) {

	//INIT SCENE:
	Scene activeScene = Scene::MENU;

	// --- INIT ---
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw "No es pot inicialitzar SDL subsystems";

	// --- TIME ---
	clock_t lastTime = clock();
	float timeDown = 10.;
	int deltaTime = 0;

	// --- WINDOW ---
	SDL_Window *window{ SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
	if (window == nullptr) throw "No es pot inicialitzar SDL_Window";

	// --- RENDERER ---
	SDL_Renderer *renderer{ SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };
	if (renderer == nullptr) throw "No es pot inicialitzar SDL_Renderer";

	// --- SPRITES ---	(textures)
	const Uint8 imgFlags{ IMG_INIT_PNG | IMG_INIT_JPG };
	if (!(IMG_Init(imgFlags) & imgFlags)) throw "Error: SDL_image init";

		// Background MENU
	SDL_Texture *bgTexture{ IMG_LoadTexture(renderer, "../../res/img/bg.jpg") };
	if (bgTexture == nullptr) throw "No s'han pogut crear les textures";
	SDL_Rect bgRect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		//Background GAME
	SDL_Texture *bgGameTexture{ IMG_LoadTexture(renderer, "../../res/img/bgCastle.jpg") };
	if (bgGameTexture == nullptr) throw "No s'han pogut crear les textures";
	// reutilizamos bgRect.

		// Cursor MENU
	SDL_Texture *cursorTexture{ IMG_LoadTexture(renderer, "../../res/img/kintoun.png") };
	if (cursorTexture == nullptr) throw "No s'han pogut crear les textures";
	SDL_Rect cursorRect{ 0,0,350,189 };

		// Player GAME
	SDL_Texture *playerTexture{ IMG_LoadTexture(renderer, "../../res/img/spCastle.png") };
	if (playerTexture == nullptr) throw "No s'ha pogut crear la textura del jugador.";
	SDL_Rect playerRect, playerPosition;
	int textWidth, textHeight, frameWidth, frameHeight;
	SDL_QueryTexture(playerTexture, NULL, NULL, &textWidth, &textHeight);
	frameWidth = textWidth / 12;
	frameHeight = textHeight / 8;
	playerPosition.x = playerPosition.y = 0;
	playerRect.x = playerRect.y = 0;
	playerPosition.h = playerRect.h = frameHeight;
	playerPosition.w = playerRect.w = frameWidth;
	int frameTime = 0;

	Move move = Move::NONE;
	
		// For player motion smoothing
	SDL_Rect cursorTarget{ 0,0,100,100 };

		// --- Animated Sprite ---
	/*SDL_Texture *cursorTexture{ IMG_LoadTexture(renderer, "../../res/img/sp01.png") };
	SDL_Rect playerRect, playerPosition;
	int textWidth, textHeight, frameWidth, frameHeight;
	SDL_QueryTexture(cursorTexture, NULL, NULL, &textWidth, &textHeight);
	frameWidth = textWidth / 6;
	frameHeight = textHeight / 1;
	playerPosition.x = playerPosition.y = 0;
	playerRect.x = playerRect.y = 0;
	playerPosition.h = playerRect.h = frameHeight;
	playerPosition.w = playerRect.w = frameWidth;
	int frameTime = 0;*/

	// --- TEXT ---
	if (TTF_Init() != 0) throw "No es pot inicialitzar SDL_ttf";

	TTF_Font * font{ TTF_OpenFont("../../res/ttf/saiyan.ttf",80) };
	if (font == nullptr) throw "No es pot inicialitzar the TTF_Font";

	SDL_Surface *tmpSurf{ TTF_RenderText_Blended(font, "Play", SDL_Color{255,150,0,255}) };
	if (tmpSurf == nullptr) throw "No s'ha pogut crear la superfície.";
	SDL_Texture *textTexture{ SDL_CreateTextureFromSurface(renderer, tmpSurf) };
	SDL_Rect textRect{ 100,50,tmpSurf->w, tmpSurf->h };

	SDL_Surface *tmpSurf2{ TTF_RenderText_Blended(font, "Exit", SDL_Color{ 255,0,0,255 }) };
	if (tmpSurf2 == nullptr) throw "No s'ha pogut crear la superfície.";
	SDL_Texture *textTexture2{ SDL_CreateTextureFromSurface(renderer, tmpSurf2) };
	SDL_Rect textRect2{ 100,200,tmpSurf2->w, tmpSurf2->h };

	SDL_FreeSurface(tmpSurf);
	SDL_FreeSurface(tmpSurf2);
	TTF_CloseFont(font);

	// --- AUDIO ---
	const Uint8 mixFlags{ MIX_INIT_MP3 | MIX_INIT_OGG };
	if (!(Mix_Init(mixFlags)& mixFlags)) throw "Error: SDL_mixer init";

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		throw "Unable to initialize SDL_mixer audio systems";
	}
	Mix_Music * soundtrack{ Mix_LoadMUS("../../res/au/mainTheme.mp3") };
	if (!soundtrack) throw "Unable to load the Mix_Music soundtrack";
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
	//Mix_PlayMusic(soundtrack, -1);	// -1 per a un loop. 1 per a una vegada...

	// --- GAME LOOP ---
	SDL_Event event;

	struct Mouse {
		std::pair <int, int> ButtonDown;
		std::pair <int, int> Motion;
		SDL_MouseButtonEvent Button;
	};

	struct Mouse Mouse;
	SDL_Keycode KeyDown = SDLK_0;

	bool isRunning = true;
	while (isRunning){
		// HANDLE EVENTS
		/// Es muy mala praxis tener cambios del gameplay en el handle events. Esto tendría que estar en el Update.

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:		isRunning = false; break;
			case SDL_KEYDOWN:
				KeyDown = event.key.keysym.sym;
				break;
/*
				// En lugar de esto habria que tener variables que almacenen el input.
				if (event.key.keysym.sym == SDLK_ESCAPE) isRunning = false; break;
				if (event.key.keysym.sym == SDLK_w){
					move == Move::UP;
				}
				if (event.key.keysym.sym == SDLK_a) {
					move == Move::LEFT;
				}
				if (event.key.keysym.sym == SDLK_s) {
					move == Move::DOWN;
				}
				if (event.key.keysym.sym == SDLK_d) {
					move == Move::RIGHT;
				}*/
			//case SDL_MOUSEMOTION: playerRect.x = event.motion.x; playerRect.y = event.motion.y; break;  //Motion without smoothing
			case SDL_MOUSEMOTION:	// Motion with smoothing.
				Mouse.Motion.first = event.motion.x;
				Mouse.Motion.second = event.motion.y;
				break;
			case SDL_MOUSEBUTTONDOWN:
				Mouse.ButtonDown.first = event.motion.x;
				Mouse.ButtonDown.second = event.motion.y;
				Mouse.Button.button = event.button.button;
				break;

			default:;
			}
		}

		// UPDATE

		// Recomenado para saquitos usar un vector que contenga los SDL_Rect.!!!

		// Para las colisiones podríamos hacer un Colisions.h con las funciones que comprueban la colisión.
		/* ejemplo: 
			bool Colision(SDL_Rect origen, SDL_Rect, target){

				return( ... || ... || ... || ... ); // las cuatro esquinas.
			}
			
			bool ColisionWalls(SDL_Rect inside, SDL_Rect container){
				return( ... || ... || ... || ... );
			}

			se recomienda usar el namespace. Por ejemplo:
			namespace Colisions{
				// Las funciones, como Colision()
			}
		*/

		if (KeyDown == SDLK_ESCAPE) isRunning = false;
		if (activeScene == Scene::GAME) {
			if (KeyDown == SDLK_w) {
				move == Move::UP;
			}
			if (KeyDown == SDLK_a) {
				move == Move::LEFT;
			}
			if (KeyDown == SDLK_s) {
				move == Move::DOWN;
			}
			if (KeyDown == SDLK_d) {
				move == Move::RIGHT;
			}
			else {
				move == Move::NONE;
			}
		}

		// IF Scene is MENU and Mouse But.Dow. is on Text:
		if (Mouse.ButtonDown.first > textRect.x && Mouse.ButtonDown.first < (textRect.x + textRect.w) && Mouse.ButtonDown.second > textRect.y && Mouse.ButtonDown.second < (textRect.y + textRect.h)) {
			//Mix_PlayMusic(soundtrack, -1);	// -1 per a un loop. 1 per a una vegada...
			if (activeScene == Scene::MENU) {
				activeScene = Scene::GAME;
			}
		}
		// If Scene is MENU and Mouse.But.Dw. is on Exit Text:
		if (Mouse.ButtonDown.first > textRect2.x && Mouse.ButtonDown.first < (textRect2.x + textRect2.w) && Mouse.ButtonDown.second > textRect2.y && Mouse.ButtonDown.second < (textRect2.y + textRect2.h)) {
			//Mix_PauseMusic();	// -1 per a un loop. 1 per a una vegada...
			if (activeScene == Scene::MENU) {
				exit(0);
			}
		}

		deltaTime = (clock() - lastTime);
		lastTime = clock();
		deltaTime /= CLOCKS_PER_SEC;
		timeDown -= deltaTime;
		//std::cout << timeDown << std::endl;

		if (activeScene == Scene::MENU) {
			cursorTarget.x = Mouse.Motion.first - (cursorRect.w / 2);
			cursorTarget.y = Mouse.Motion.second - (cursorRect.h / 2);

			cursorRect.x += (cursorTarget.x - cursorRect.x) / 10;
			cursorRect.y += (cursorTarget.y - cursorRect.y) / 10;
		}
		if (activeScene == Scene::GAME) {
			switch (move) {
				case Move::UP:
					std::cout << "up" << std::endl;
					playerPosition.y--;
					break;
				case Move::DOWN:
					std::cout << "down" << std::endl;
					playerPosition.y++;
					break;
				case Move::LEFT:
					std::cout << "left" << std::endl;
					playerPosition.x--;
					break;
				case Move::RIGHT:
					std::cout << "right" << std::endl;
					playerPosition.x++;
					break;
				case Move::NONE:
					std::cout << "none" << std::endl;
					// nothing
					break;
			}
			frameTime++;
			if (FPS / frameTime <= 9) {
				frameTime = 0;
				playerRect.x += frameWidth;
				if (playerRect.x >= (textWidth/4))
					playerRect.x = 0;
			}
		}

		/*frameTime++;
		if (FPS / frameTime <= 9) {
			frameTime = 0;
			playerRect.x += frameWidth;
			if (playerRect.x >= textWidth)
				playerRect.x = 0;
		}*/

		// DRAW
		SDL_RenderClear(renderer);

		if (activeScene == Scene::MENU) {
			//Background
			SDL_RenderCopy(renderer, bgTexture, nullptr, &bgRect);
			//Animated Sprite

			// Text
			SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
			SDL_RenderCopy(renderer, textTexture2, nullptr, &textRect2);
			// Cursor
			SDL_RenderCopy(renderer, cursorTexture, nullptr, &cursorRect);
			
		}
			
		if (activeScene == Scene::GAME) {
			// Background
			SDL_RenderCopy(renderer, bgGameTexture, nullptr, &bgRect);
			// Player
			SDL_RenderCopy(renderer, playerTexture, &playerRect, &playerPosition);

		}

		SDL_RenderPresent(renderer);	// es lo que finalmente muestra el buffer por ventana.

	}

	// --- DESTROY ---
	SDL_DestroyTexture(bgTexture);
	SDL_DestroyTexture(cursorTexture);
	SDL_DestroyTexture(textTexture);
	SDL_DestroyRenderer(renderer);
	Mix_CloseAudio();
	SDL_DestroyWindow(window);

	// --- QUIT ---
	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
	return 0;
}