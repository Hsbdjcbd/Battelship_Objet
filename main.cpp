/*====================================
AUTEUR : Simon et Stanislas Royal
PROJET : Jeu de Battleship
NOM DU FICHIER : main.cpp
DATE : 2026-03-11
BASEE SUR : TP1 Programmation Oriente Objet
DESCRIPTION : Point d'entrer du programme
====================================*/
#include "game.h"

using namespace std;




int main() {
	/******************************************************/
	/* PLACEZ VOS TESTS ICI, MAIS RETIREZ-LES DU "MAIN()" */
	/* UNE FOIS QUE VOTRE JEU DE BATTLESHIP EST COMPLÉTÉ. */
	/******************************************************/

	// Nouveau seed for random // do not work for first so also put inside main() for first game
	srand(time(NULL));

#ifdef DEBUG_INFINITE_GAME
	while (true)
	{
#endif // DEBUG_INFINITE_GAME

		Game game;
		game.play(cout);

#ifdef DEBUG_INFINITE_GAME
	}
#endif // DEBUG_INFINITE_GAME


	return 0;
}