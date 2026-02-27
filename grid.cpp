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



/*

* Testez une par une toutes les méthodes de la classe « Grid » pour vous assurer qu’elles fonctionnent bien. Conservez vos tests (dans le fichier des jeux d’essais qui vous a été fourni avec le TP1), car vous devrez les décrire et les remettre dans le cadre de ce travail pratique.
*
*
*/


bool Grid::initShips()
{

	// TODO: Read file, and call ship.read() ??

	/*

	Cette méthode sert à importer les différents bateaux qui se retrouveront dans la grille de jeu pour disputer une partie de Battleship. L’importation des bateaux doit se faire à partir du fichier (voir l’exemple de fichier ci-dessus) dont le nom est enregistré dans la constant « GRID_SHIPS_FILENAME ». Dans la méthode « initShips() », vous devez donc ouvrir le fichier, procéder à sa lecture au moyen de la méthode « read() » de la grille, puis fermer ce fichier. Si l’ouverture/la lecture du fichier s’est bien déroulée, il faut ensuite procéder au placement des bateaux dans la grille de jeu en appelant la méthode « placeShips() » (méthode déjà fournie). Si le placement réussit (valeur « true » retournée), vous devez cacher les bateaux dans la grille de jeu via la méthode « hideShips() » (méthode que vous coderez ci-après). Si le placement échoue (valeur « false » retournée), assurez-vous de faire planter le programme, car le jeu de Battleship ne peut pas s’amorcer sans que les bateaux n’aient été tous placés.

	*/

	std::fstream fichier;

	//FIXME: ouvrirFichier(fichier, GRID_SHIPS_FILENAME);

	if (this->read(fichier))
	{
		fichier.close();
		return true;
	}
	else
	{
		fichier.close();
		return false;
	}

}

void Grid::hideShips()
{
	for (int i = 0; i < _nbShips; i++)
		_ships[i].hide();
}

Grid::Grid()
{
	_nbShips = 0;
	_nbMissedHits = 0;

	//_gridOutline.setPosition((GRID_INNER_MIN_X - 1), (GRID_INNER_MIN_Y - 1));
	//_gridOutline.setSize(GRID_WIDTH, GRID_HEIGHT);

	initShips(); // TODO: Check return value ??

}

Grid::~Grid()
{
	_nbShips = 0;
	_nbMissedHits = 0;
}

int Grid::getNbRemainingShips() const
{
	int nb = 0;
	// TODO: Try me !
	for (int i = 0; i < _nbShips; i++)
		nb += _ships[i].getSunkStatus();

	return nb;
}

bool Grid::placeHit(const Point& hitPosition)
{
	int x = hitPosition.getX();
	int y = hitPosition.getY();

	// Outside Game GRID : TODO: Test me!
	if ((x < GRID_INNER_MIN_X || x > GRID_INNER_MAX_X) || (y < GRID_INNER_MIN_Y || y > GRID_INNER_MAX_Y))
		return false;

	for (int i = 0; i < _nbMissedHits; i++)
	{
		// TODO: Does compare check color and if so ...
		if (_missedHits[i] == hitPosition)
			return false;
	}


	// TODO: Check ... and create check for ships.Somethgin
/* FIXME:
Si le point « hitPosition » tombe sur un bateau déjà coulé ou encore sur un point déjà touché d’un des bateaux, l’endroit est invalide. Par contre, si le point « hitPosition » tombe sur un point encore intouché d’un des bateaux, l’endroit est valide. Servez-vous de la méthode « placeHit() » de la classe « Ship » pour vérifier ces cas.
*/

// Le TIR est Valide : n'a pas toucher une case deja tirer, ni retirer a une place precedente


// TODO: TRY ME!!!
	_missedHits[_nbMissedHits] = hitPosition;
	_missedHits[_nbMissedHits].setColor(GRID_MISSED_HITS_COLOR);
	_nbMissedHits++;

	return true;
}

void Grid::draw(std::ostream& output)
{
	/*
	Vous devez afficher le contour de la grille, les bateaux (même s’ils sont cachés : il finiront par apparaître progressivement au fur et à mesure qu’ils seront touchés) et les tirs manqués.
	*/

}

void Grid::read(std::istream& input)
{
	/*

	Vous devez utiliser la méthode « read() » de la classe « Ship » pour enregistrer les noms et les longueurs de chaque bateau du tableau « _ships[] » à la manière d’une lecture dans un fichier (le paramètre d’entrée « input » pourrait en effet représenter un fichier). Vous devez donc vous assurer d’arrêter la lecture si vous arrivez à la fin du fichier ou si le nombre de bateaux atteint/dépasse la constante « SHIP_MAX_NB ». N’oubliez pas d’ajuster la valeur de la propriété « _nbShips » selon le nombre de bateaux lus. Voici un exemple de fichier qui pourrait être lu avec la méthode « read() » de la grille pour importer les bateaux dans la grille de jeu :

	*/

}

std::ostream& operator<<(std::ostream& output, const Grid& grid)
{
	/*
	Vous devez appeler la méthode « draw() » à partir de la grille reçue en paramètre d’entrée.
	*/
	grid.draw(output);
}

std::istream& operator>>(std::istream& input, Grid& grid)
{
	/*
	Vous devez appeler la méthode « read() » à partir de la grille reçue en paramètre d’entrée.
	*/
	grid.read(input);
}