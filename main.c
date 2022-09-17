#include <stdio.h>
#include <SDL.h>
#include "./constant.h"


int game_is_running = FALSE;
int last_frame_time = 0;	//This is going to keep track of the milliseconds of the last frame that I called
SDL_Window* window = NULL;
SDL_Renderer *renderer = NULL;


struct ball {
	float x, y, width, height;
} ball_game;	//Ball of the Game


struct player {
	float x, y, width, height;
} paddle_player;	//Player of the Game


/*
  funcion para inicializar SDL
*/


int initialize_window(void) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)	{ 
		fprintf(stderr, "Error Initializing SDL: %s\n", SDL_GetError());
		return FALSE;
	}

	
	window = SDL_CreateWindow(
		"Ventana del Juego", //Titulo de la Ventana del Juego
		SDL_WINDOWPOS_CENTERED, //Centramos la ventana en el medio X
		SDL_WINDOWPOS_CENTERED, //Centramos la ventana en el medio Y
		WINDOW_WIDTH, //Altura en X
		WINDOW_HEIGHT, //Altura en Y
		SDL_WINDOW_OPENGL //Ventana sin decoracion
	);


	if (!window) {
		fprintf(stderr, "Error creating SDL: %s\n", SDL_GetError());
		return FALSE;
	}
	

	renderer = SDL_CreateRenderer(
			window, //La ventana donde el renderizado se muestra, 
			-1, //el índice del controlador de representación que se va a 
			//inicializar o -1 para inicializar el primero que admite 
			//los indicadores solicitados 
			0 //0, o uno o más SDL_RendererFlags O juntos
	);


	if (!renderer) {	//Si no se Dispara el renderizado, muestra mensaje de error	
		fprintf(stderr, "Error creating SDL Renderer: %s\n", 
		SDL_GetError());
		return FALSE;
	}
	

	return TRUE;
}


void setup(void) {
	ball_game.x = 399;
	ball_game.y = 180;
	ball_game.width = 15;
	ball_game.height = 15;


	paddle_player.x = 370;
	paddle_player.y = 540;
	paddle_player.width = 90;
	paddle_player.height = 13;
}


/*
	Game Loop's Functions ↓
*/


void process_input(void) {
	SDL_Event event;
	SDL_PollEvent(&event);
	

	switch(event.type) {
		case SDL_QUIT:
			game_is_running = FALSE;
		break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				game_is_running = FALSE;
			}
		break;


	}	
}


void update(void) {
	int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time); //Reaching the Time to Wait in Milliseconds
	

	if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
		SDL_Delay(time_to_wait);
	}


	float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f; //Get a Delta Time factor converted in seconds to be used to update my objects
	

	last_frame_time = SDL_GetTicks(); //The SDL Window Ticks


	//Everything has to be updated in SECONDS!
	ball_game.x += 80 * delta_time;
	ball_game.y += 60 * delta_time;
}


void render(void) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);


	SDL_Rect ball = {
		(int)ball_game.x,
		(int)ball_game.y,
		(int)ball_game.width,
		(int)ball_game.height
	};


	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &ball);


	SDL_Rect paddle = {
		(int)paddle_player.x,
		(int)paddle_player.y,
		(int)paddle_player.width,
		(int)paddle_player.height
	};
	

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &paddle);


	SDL_RenderPresent(renderer);  //Swap the Double Buffer (Front Buffer - Back Buffer)
}


void destroy_window(void) {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


int main(int argc, char **argv) //Funcion Principal
{	
	game_is_running = initialize_window();


	setup();
	

	while (game_is_running) {
		process_input();
		update();
		render(); 
	}


	destroy_window();


	return 0;
}

