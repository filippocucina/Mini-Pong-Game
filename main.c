#include <stdio.h>
#include <stdbool.h>	//Newer Versions of the C Programming Language added this Pre-Processor File. So you can use false or true, instead of the constant library that we created
#include <SDL.h>
#include "constant.h"


int game_is_running = FALSE;
int last_frame_time = 0;	//This is going to keep track of the milliseconds of the last frame that I called
SDL_Window* window = NULL;
SDL_Renderer *renderer = NULL;


/*
	We could also use a single struct called Game Objects to simplify:
	
	struct GameObjects {
		... Code 
	}
	
	but IT JUST WORKS!!!
*/


struct ball {
	float x, y, width, height, velocityY, velocityX;
} ball_game;	//Ball of the Game


struct player {
	float x, y, width, height, velocity_paddleX;
} paddle_player;	//Player of the Game


/*
	SDL Initialization
*/


int initialize_window(void) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)	{ 
		fprintf(stderr, "Error Initializing SDL: %s\n", SDL_GetError());
		return FALSE;
	}

	
	window = SDL_CreateWindow(
		"Pong Game", //Titulo de la Ventana del Juego
		SDL_WINDOWPOS_CENTERED, //Centramos la ventana en el medio X
		SDL_WINDOWPOS_CENTERED, //Centramos la ventana en el medio Y
		WINDOW_WIDTH, //Anchura en X
		WINDOW_HEIGHT, //Altura en Y
		SDL_WINDOW_BORDERLESS //Ventana sin bordes
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
	ball_game.x = (WINDOW_WIDTH / 2);
	ball_game.y = 100;
	ball_game.width = 15;
	ball_game.height = 15;
	ball_game.velocityX = 250;
	ball_game.velocityY = 250;

	paddle_player.width = 100;
	paddle_player.height = 20;
	paddle_player.x = (WINDOW_WIDTH / 2) - (paddle_player.width / 2);
	paddle_player.y = WINDOW_HEIGHT - 50;
	paddle_player.velocity_paddleX = 0;
}


/*
	Game Loop's Functions ↓
*/


void process_input(void) {
	SDL_Event user_event;
	SDL_PollEvent(&user_event);


	switch (user_event.type) {
	case SDL_QUIT:
		game_is_running = FALSE;
		break;


	case SDL_KEYDOWN:
		if (user_event.key.keysym.sym == SDLK_ESCAPE) {
			game_is_running = FALSE;
		}


		if (user_event.key.keysym.sym == SDLK_RIGHT) {
			paddle_player.velocity_paddleX = 320;
		}


		if (user_event.key.keysym.sym == SDLK_LEFT) {
			paddle_player.velocity_paddleX = -320;
		}
		break;


	case SDL_KEYUP:
		if (user_event.key.keysym.sym == SDLK_RIGHT) {
			paddle_player.velocity_paddleX = 0;
		}


		if (user_event.key.keysym.sym == SDLK_LEFT) {
			paddle_player.velocity_paddleX = -0;
		}
		break;
	}	
}


void update(void) {
	int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time); //Reaching the Time to Wait in Milliseconds

	/* 
	if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
		SDL_Delay(time_to_wait);
	}
	*/

	float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f; //Get a Delta Time factor converted in seconds to be used to update my objects


	last_frame_time = SDL_GetTicks(); //The SDL Window Ticks


	//Everything has to be updated in SECONDS!
	ball_game.x += ball_game.velocityX * delta_time;
	ball_game.y += ball_game.velocityY * delta_time;
	paddle_player.x += paddle_player.velocity_paddleX * delta_time;


	//Ball.x Collision with the window's width
	if (ball_game.x <= 0 || ball_game.x + ball_game.width >= WINDOW_WIDTH) {
		ball_game.velocityX = -ball_game.velocityX;
	}


	//Ball.y collision with the window's height
	if (ball_game.y <= 0) {
		ball_game.y = 0;
		ball_game.velocityY = -ball_game.velocityY;
	}


	//Ball and Paddle collision
	if (ball_game.y + ball_game.height >= paddle_player.y && ball_game.x + ball_game.width >= paddle_player.x && ball_game.x <= paddle_player.x + paddle_player.width) { 
		ball_game.y = paddle_player.y - ball_game.height;
		ball_game.velocityY = -ball_game.velocityY;
	}


	//Prevent Paddle from moving outside the boundaries of the window 
	if (paddle_player.x <= 0 || paddle_player.x + paddle_player.width == WINDOW_WIDTH) {
		paddle_player.x = 0;
	}


	//Prevent Paddle from moving outside the boundaries of the window	
	if (paddle_player.x >= WINDOW_WIDTH - paddle_player.width) {
		paddle_player.x = WINDOW_WIDTH - paddle_player.width;
	}


	//Replace the ball in the height of the window
	if (ball_game.y + ball_game.width > WINDOW_HEIGHT) {
		ball_game.x = WINDOW_WIDTH / 2;
		ball_game.y = 0;
	}
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


	SDL_RenderPresent(renderer);  //Swap the Double Buffer (Front Buffer - Back Buffer) or Simple Update The Screen
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

