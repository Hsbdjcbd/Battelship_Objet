/*====================================
AUTEUR : Stanislas Royal
PROJET : Jeu de Battleship
NOM DU FICHIER : grid.cpp
DATE : 2026-03-11
BASEE SUR : TP1 Programmation Oriente Objet
DESCRIPTION : Classe Objet Grid:: , Sert a contenir les
bateaux de un joueur et les coups manques
====================================*/
#include "grid.h"

using namespace std;



/***********************************************/
/* NE MODIFIEZ PAS LES MÉTHODES QUI SUIVENT !  */
/* ELLES SONT DÉJÀ PLEINEMENT FONCTIONNELLES ! */
/***********************************************/
bool Grid::placeShips() {
	bool collides;
	int maxX, maxY;

	for (int i = 0; i < _nbShips; i++) {
		do {
			if ((_ships[i].getLength() > (GRID_WIDTH - 2)) ||
				(_ships[i].getLength() > (GRID_HEIGHT - 2))) {
				return false;
			}

			collides = false;
			_ships[i].setDirection(Direction(rand() % 2));

			if (_ships[i].getDirection() == HORIZONTAL) {
				maxX = GRID_INNER_MAX_X - _ships[i].getLength();
				maxX = ((maxX < GRID_INNER_MIN_X) ? GRID_INNER_MIN_X : maxX);
				maxY = GRID_INNER_MAX_Y;
			}

			else {
				maxX = GRID_INNER_MAX_X;
				maxY = GRID_INNER_MAX_Y - _ships[i].getLength();
				maxY = ((maxY < GRID_INNER_MIN_Y) ? GRID_INNER_MIN_Y : maxY);
			}

			const int randX = (rand() % (maxX - GRID_INNER_MIN_X + 1) + GRID_INNER_MIN_X);
			const int randY = (rand() % (maxY - GRID_INNER_MIN_Y + 1) + GRID_INNER_MIN_Y);
			_ships[i].setPosition(randX, randY);

			for (int j = 0; j < i; j++) {
				if ((i != j) && _ships[i].checkCollision(_ships[j])) {
					collides = true;
					break;
				}
			}
		} while (collides);
	}

	return true;
}



void Grid::printShipsStatus(ostream& output) const {
	goToXY(GRID_SHIPS_STATUS_X, GRID_SHIPS_STATUS_Y);
	output << "BATEAUX RESTANTS";

	goToXY((GRID_SHIPS_STATUS_X + 23), GRID_SHIPS_STATUS_Y);
	output << "BATEAUX COULES";

	for (int i = 1; i <= _nbShips; i++) {
		if (_ships[i - 1].getSunkStatus()) {
			goToXY((GRID_SHIPS_STATUS_X + 23), (GRID_SHIPS_STATUS_Y + i));
		}
		else {
			goToXY((GRID_SHIPS_STATUS_X), (GRID_SHIPS_STATUS_Y + i));
		}

		_ships[i - 1].print(output);
	}
}

/******************************************************/
/* CODEZ ICI LES AUTRES MÉTHODES DE LA CLASSE "GRID". */
/******************************************************/


bool Grid::initShips()
{
	// should never be called twice
	assert(_nbShips == 0);

#ifdef DEBUG_NO_READ_FILE
	stringstream ss1("Porte-avion (5)\nCroiseur (4)\nContre-torpilleur (3)\nSous-marin (3)\nTorpilleur (2)");
	this->read(ss1);
#else
	std::fstream fichier(GRID_SHIPS_FILENAME, ios::in);

	if (!fichier.is_open())
		criticMessage("ouverture de " + GRID_SHIPS_FILENAME, 1);


	this->read(fichier);

	fichier.close();
#endif

	if (_nbShips == 0)
		criticMessage("lecture des navires echoues _nbShips == 0", 2);

	if (!placeShips())
		criticMessage("placement des bateaux impossibles!!", 3);

	this->hideShips();

	return true;
}

void Grid::hideShips()
{
	// ne doit etre appeler qu'apres avoir charger les bateaux
	assert(_nbShips > 0);

	for (int i = 0; i < _nbShips; i++)
		_ships[i].hide();
}

Grid::Grid()
{
	_nbShips = 0;
	_nbMissedHits = 0;

	_gridOutline.getPosition().setPosition((GRID_INNER_MIN_X - 1), (GRID_INNER_MIN_Y - 1));
	_gridOutline.setSize(GRID_WIDTH, GRID_HEIGHT);
	_gridOutline.getPoint().setDrawingChar('\xB0');

	if (!initShips())
	{ // Ne devrait pas arriver ici puisque criticMessage() dans initShips() ...
		criticMessage("impossible de positionner les bateaux!!", 4);
	}
}

Grid::~Grid()
{
	_nbShips = 0;
	_nbMissedHits = 0;
}

int Grid::getNbRemainingShips() const
{
	assert(_nbShips > 0); // Should always be above zero when Called

	int nb = _nbShips;

	for (int i = 0; i < _nbShips; i++)
		if (_ships[i].getSunkStatus())
			nb--;

	return nb;
}

bool Grid::placeHit(const Point& hitPosition)
{
	int x = hitPosition.getX();
	int y = hitPosition.getY();

	if ((x < GRID_INNER_MIN_X || x > GRID_INNER_MAX_X) ||
		(y < GRID_INNER_MIN_Y || y > GRID_INNER_MAX_Y))
		return false;

	for (int i = 0; i < _nbMissedHits; i++)
		if (_missedHits[i].comparePosition(hitPosition))
			return false;

	for (int i = 0; i < _nbShips; i++)
	{
		switch (_ships[i].placeHit(hitPosition))
		{
		case SHIP_NOT_HIT: // SHIP_NOT_HIT=0
			continue;
		case SHIP_ALREADY_SUNK: // SHIP_ALREADY_SUNK=1 // ship already sunk
		case SHIP_HIT_TWICE: // SHIP_HIT_TWICE=2 // touche a meme place
			return false;
		case SHIP_HIT: // SHIP_HIT=3 // first hit on this point of ship
			return true;
		}
	}

	// Le TIR est Valide : n'a pas toucher une case deja tirer, ni toucher de bateau

	_missedHits[_nbMissedHits] = hitPosition;
	_missedHits[_nbMissedHits].setColor(GRID_MISSED_HITS_COLOR);
	_nbMissedHits++;

	return true;
}

void Grid::draw(std::ostream& output) const
{
	assert(_nbShips > 0); // Should always be above 0 if class initialized right.

	// only print something if in console : otherwise maybe print();
	if (&output == &std::cout)
	{
		_gridOutline.draw(output);

		for (int i = 0; i < _nbShips; i++)
			_ships[i].draw(output);


		for (int i = 0; i < _nbMissedHits; i++)
			_missedHits[i].draw(output);
	}
}

void Grid::read(std::istream& input)
{
#ifdef DEBUG_CODE
	// INFO: Ajouter _nbShips = 0; pour permettre de recharger de nouveau Ships avec read()
	_nbShips = 0;
	// seulement pour test puisque la plupart des actions sont dans le constructeur ...
	// et que les variables ne sont plus au valeur initial ...
#endif
	while (!input.eof())
	{
		std::string ligne;
		std::getline(input, ligne);
		stringstream ssl(ligne);

		if (_nbShips < SHIP_MAX_NB && ligne != "")
		{
			// REF: https://en.cppreference.com/w/cpp/string/basic_string.html
			// Verifier si Format : "String (Int)"  est Respecter de facon basique ...

			// Verification
			//		1 - String end with ')'
			//		2 - String contains '(' /* inutile : and ')' */
			//		3 - Premier et dernier '(' et ')' sont au meme position, donc 1 seul chaque

			if (ligne.back() == ')' &&
				ligne.find('(') != std::string::npos
				/* Inutile :  && ligne.find(')') != std::string::npos */)

				if ((ligne.find('(') == ligne.rfind('(')) &&
					(ligne.find(')') == ligne.rfind(')')))
				{
					_ships[_nbShips].read(ssl);
					_nbShips++;
				}
		}
	}
}

std::ostream& operator<<(std::ostream& output, const Grid& grid)
{
	grid.draw(output);

	return output;
}

std::istream& operator>>(std::istream& input, Grid& grid)
{
	grid.read(input);

	return input;
}