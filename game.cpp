#include "game.h"

using namespace std;

/***********************************************/
/* CODEZ ICI LES MÉTHODES DE LA CLASSE "GAME". */
/***********************************************/

		Game::Game(){
            _currentPlayerIndex = 0;
            _gameOver = false;

            // Nouveau seed for random

            srand(time(NULL))
        }
		Game::~Game()
        {
            _currentPlayerIndex = 0;
            _gameOver = true;
        }


void Game::play(std::ostream& sortie)
{
    // TODO: Useful?? if one line while() ??
    Point hitMouse;

    while (!_gameOver)
    {
        draw(std::cout);

        // TODO: Test loop
        do
        {
            hitMouse = getMouseClick();
        } while (!_grids[_currentPlayerIndex].placeHit(hitMouse));

        // TODO: Test if no click ??
//        while (!_grids[_currentPlayerIndex].placeHit(getMouseClick()));

        draw();
        sleepMs(500);
        ignoreMouseClicks();

        if (_grids[_currentPlayerIndex].getNbRemainingShips())
        {
            _currentPlayerIndex++;
            _currentPlayerIndex = _currentPlayerIndex % GAME_NB_PLAYERS; // TODO: Test Modulo
        }
        else
            _gameOver = true;
    }

    //    Afficher la partie (pour savoir quel joueur a gagné)
    draw();
}


void Game::draw(std::ostream& output) const

{

    // TODO: Add Code ...
    /*!SECTION
    
    Au début de cette méthode, vous devez effacer l’écran en appelant la fonction « clearScreen() ». 
    Par la suite, si la partie est terminée, vous devez afficher un message indiquant la victoire du joueur ayant coulé tous les bateaux de l’autre joueur. 
    Si la partie est toujours en cours, vous devez afficher le titre du jeu, le tour du joueur, sa grille de jeu et les informations sur les bateaux coulés 
        et ceux restants (des méthodes existent pour cela dans la classe « Grid »).

        TODO: Voir docx pour images ... TITRE, Instructions, 
    */
}

std::ostream& operator<<(std::ostream& output, const Game& game)
{

    // TODO: Add Code ...

    /*!SECTION
    
    Vous devez appeler la méthode « draw() » à partir de la partie reçue en paramètre d’entrée. 
    */
   game.draw(output);
}

/*

* Testez une par une toutes les méthodes de la classe « Game » pour vous assurer qu’elles fonctionnent bien. Conservez vos tests 
* (dans le fichier des jeux d’essais qui vous a été fourni avec le TP1), car vous devrez les décrire et les remettre dans le cadre de ce travail pratique.


*/