#include "game.h"

using namespace std;

int main() {
	/******************************************************/
	/* PLACEZ VOS TESTS ICI, MAIS RETIREZ-LES DU "MAIN()" */
	/* UNE FOIS QUE VOTRE JEU DE BATTLESHIP EST COMPLÉTÉ. */
	/******************************************************/
	srand(time(NULL));
	Game game;
	game.play(cout);
	
	return 0;
}

