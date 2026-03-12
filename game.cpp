/*====================================
AUTEUR : Stanislas Royal et Simon Fortier
PROJET : Jeu de Battleship
NOM DU FICHIER : game.cpp
DATE : 2026-03-11
BASEE SUR : TP1 Programmation Oriente Objet
DESCRIPTION : Classe Objet Game:: , Sert a contenir les
Grid de chaque joueur et gerer les tours de jeu.
====================================*/
#include "game.h"

using namespace std;

/***********************************************/
/* CODEZ ICI LES MÉTHODES DE LA CLASSE "GAME". */
/***********************************************/

Game::Game() {
	_currentPlayerIndex = 0;
	_gameOver = false;

	// Nouveau seed for random // do not work for first so also put inside main() for first game
	srand(time(NULL));
}

Game::~Game()
{
	_currentPlayerIndex = 0;
	_gameOver = true;
}


void Game::play(std::ostream& sortie)
{
	// Tant qu'il n'y a pas de gagnants
	while (!_gameOver)
	{
		draw(std::cout);

		// Attente de clique valide sur bateau ou dans l'eau
		while (!_grids[_currentPlayerIndex].placeHit(getMouseClick()));

		draw(std::cout);

		sleepMs(PLAYER_TURN_SLEEP_MS); // default 500 ms
		ignoreMouseClicks(); // nettoie le buffer des cliques

		if (_grids[_currentPlayerIndex].getNbRemainingShips())
		{
#ifndef DEBUG_NO_PLAYER_TURN
			_currentPlayerIndex++;
#endif
			_currentPlayerIndex = _currentPlayerIndex % GAME_NB_PLAYERS;
		}
		else
			_gameOver = true;
	}

	//    Afficher la partie (pour savoir quel joueur a gagné)
	draw(std::cout);
}


void Game::draw(std::ostream& output) const

{
	clearScreen(output);

	if (_gameOver)
	{
		output << "Victoire pour Joueur " << _currentPlayerIndex + 1 << std::endl;
		output << "Merci d'avoir joue !" << std::endl;

		conPause(true, -1);
	}
	else
	{
		output << "JEU DE BATTLESHIP : cliquez dans la grille pour tirer" << std::endl;
		output << std::endl << "TOUR DU JOUEUR " << _currentPlayerIndex + 1 << std::endl;

		_grids[_currentPlayerIndex].draw(output);

		_grids[_currentPlayerIndex].printShipsStatus(output);
	}
}

std::ostream& operator<<(std::ostream& output, const Game& game)
{
	game.draw(output);

	return output;
}