#include <stdio.h>
#include <SDL2/SDL.h>
#include "./constant.h"


int game_is_running = FALSE;
SDL_Window* window = NULL;
SDL_Renderer *renderer = NULL;


/*
  funcion para crear la Ventana
*/


SDL_Window* window = NULL;
SDL_Renderer *renderer = NULL;


int initialize_window(void){
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error Initializing SDL: %s\n", SDL_GetError());
		return FALSE;
	}
	
	window = SDL_CreateWindow(
			NULL, //No tiene Titulo la ventana del juego
			SDL_WINDOWPOS_CENTERED, //Centramos la ventana en el medio X
			SDL_WINDOWPOS_CENTERED, //Centramos la ventana en el medio Y
			WINDOW_WIDTH, //Altura en X
			WINDOW_HEIGHT, //Altura en Y
			SDL_WINDOW_BORDERLESS //Ventana sin decoracion
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

	//Si no se Dispara el renderizado, muestra error
	if (!renderer) {	
		fprintf(stderr, "Error creating SDL Renderer: %s\n", 
		SDL_GetError());
		return FALSE;
	}

	 	
	return TRUE;
}


/*
	Funciones del Game Loop
*/

void setup() {
	//TODO:

}

void process_input() {
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

void update() {


}

void render() {


}

void destroy_window() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

//Funcion Principal

int main(int argc, char *argv[])
{
	
	game_is_running = initialize_window();

	/*
	  	Set Up function is called once in the beginning 
	  	and it is not attached in the Game Loop
	  	We use it to set the game_objects position, Enviroment, Colors and more!
	
	*/

	setup();


	/*
                En cada Game Loop, es comprimido de tres principales secciones:
                1- Se inicializa la Entrada del jugador
                2- El juego se actualiza
                3- Se renderiza en la pantalla
 	*/

	while (game_is_running) {
		process_input();
		update();
		render();
	}
	
	destroy_window();

	return 0;
}
