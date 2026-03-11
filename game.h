/*====================================
AUTEUR : Stanislas Royal
PROJET : Jeu de Battleship
NOM DU FICHIER : game.h
DATE : 2026-03-11
BASEE SUR : TP1 Programmation Oriente Objet
DESCRIPTION : Classe Objet Game:: , Sert a contenir les
Grid de chaque joueur et gerer les tours de jeu.
====================================*/
#pragma once

#include <iostream>
// Added by STAN
#include <sstream>
// ^^ Added by STAN
#include "mesConstantes.h"
#include "mesFonctions.h"
#include "grid.h"

/********************************/
/* NE MODIFIEZ PAS CE FICHIER ! */
/* IL EST DÉJÀ COMPLET !        */
/********************************/
class Game {
private:
	Grid _grids[GAME_NB_PLAYERS];
	int _currentPlayerIndex;
	bool _gameOver;

public:
	Game();
	~Game();

	void play(std::ostream& sortie);
	void draw(std::ostream& output) const;
};

std::ostream& operator<<(std::ostream& output, const Game& game);