/*====================================
AUTEUR : Simon
PROJET : Jeu de Battleship
NOM DU FICHIER : ship.cpp
DATE : 2026-03-11
BASEE SUR : TP1 Programmation Oriente Objet
DESCRIPTION : Classe Objet Ship:: , Sert a contenir les
points du bateau et l'etat des cases toucher
====================================*/
#include "ship.h"

using namespace std;

/********************************************/
/* NE MODIFIEZ PAS LA MÉTHODE QUI SUIT !    */
/* ELLE EST DÉJÀ PLEINEMENT FONCTIONNELLE ! */
/********************************************/
void Ship::updatePoints() {
	for (int i = 0; i < _length; i++) {
		if (_direction == HORIZONTAL) {
			_points[i].setX(_x + i);
			_points[i].setY(_y);
		}

		else {
			_points[i].setX(_x);
			_points[i].setY(_y + i);
		}
	}
}

Ship::Ship(const std::string& name, int length)
{
	//FIXME: assert(name != "");
	assert(length >= 0); // positive and start at 1 // was : assert(length > 2);
	//	assert(x > GRID_INNER_MIN_X && x < GRID_INNER_MAX_X);
	//	assert(y > GRID_INNER_MIN_Y && y < GRID_INNER_MAX_Y);

	_name = name;
	_x = _y = 0;
	_hasSunk = false;
	_direction = HORIZONTAL;

	// TODO: Sometimes, color not copied from Point to Point ...
	for (int i = 0; i < SHIP_MAX_LENGTH; i++)
		_points[i].setColor(7);

	this->setLength(length);
	this->updatePoints();

}

Ship::~Ship()
{
	_name = "";
	_x = _y = 0;
	_hasSunk = false;
	_length = 0;
	_direction = HORIZONTAL;
}

int Ship::getLength() const
{
	return _length;
}

const Direction& Ship::getDirection() const
{
	return _direction;
}

bool Ship::getSunkStatus() const
{
	return _hasSunk;
	/* WAS
	if (_hasSunk)
		return true;
	else
	{
		// TODO: Update status ??
		return _hasSunk;
	}
	*/
}

void Ship::setPosition(int x, int y)
{
	assert(x >= 0);
	assert(y >= 0);

	// TODO: Grid size limit ??
	_x = x;
	_y = y;

	updatePoints();
}


void Ship::setLength(int length)
{
	assert(length >= 0 && length <= SHIP_MAX_LENGTH);

	_length = length;

	updatePoints();
}

void Ship::setDirection(const Direction& direction)
{
	_direction = direction;

	updatePoints();
}

void Ship::rotate()
{
	if (_direction == HORIZONTAL)
		_direction = VERTICAL;
	else
		_direction = HORIZONTAL;

	updatePoints();
}

void Ship::hide()
{
	for (int i = 0; i < _length; i++)
		_points[i].setColor(SHIP_HIDDEN_COLOR);
}

bool Ship::checkCollision(const Ship& otherShip) const
{
	/*

	Vous devez vérifier qu’aucun des points du bateau « otherShip » reçu en paramètre d’entrée n’empiète (c’est-à-dire, qui a les mêmes coordonnées) sur un des points du bateau implicite. Dès qu’un point empiète sur un autre, il faut retourner « true ». Autrement, la valeur « false » sera retournée à la toute fin de la méthode.

	*/
	for (int i = 0; i < _length; i++)
	{
		for (int j = 0; j < otherShip._length; j++)
		{
			if (_points[i].comparePosition(otherShip._points[j]))
				return true;
		}
	}
	return false;
}

int Ship::placeHit(const Point& hitPosition)
{
	for (int i = 0; i < _length; i++)
	{
		if (_points[i].comparePosition(hitPosition))
		{
			if (_hasSunk)
				return 1; // ship is sunk && hit on SHIP

			if (_points[i].getColor() == SHIP_HIT_COLOR)
				return 2;

			_points[i].setColor(SHIP_HIT_COLOR);

			updateSunkStatus();

			return 3;
		}
	}
}
return 0; // NO HIT ON SHIP
}

void Ship::print(std::ostream& output) const
{
	// TODO: Use assert or IF ??
	// assert(_name != "");
	// assert(_length > 0);
	if (!(_name == "" || _length == 0))
		output << _name << " (" << _length << ")" << std::endl;
}

void Ship::draw(std::ostream& output) const
{
	// TODO: Use assert or IF ??
	// assert(_name != "");
	// assert(_length > 0);
	if (!(_name == "" || _length == 0))
		for (int i = 0; i < _length; i++)
			_points[i].draw(output);
}


void Ship::read(std::istream& input)
{

	std::string ligne = "";


	//int longueur = std::getline(input, ligne);
	//std::cout << ligne << std::endl;
	int length = 0;
	std::string name = "";
	char c;

	input >> name;
	input >> c;        // (
	input >> length;
	input >> c;        // )


	// TODO: Checks
	_name = name;
	setLength(length);
}

std::istream& operator>>(std::istream& input, Ship& ship)
{
	ship.read(input);
	return input;
}

void Ship::updateSunkStatus()
{
	assert(_length > 0); // length cannot be 0 or negative

	int cnt = 0;
	if (_hasSunk)
		return;

	for (cnt = 0; cnt < _length; cnt++)
	{
		if (!(_points[cnt].getColor() == SHIP_HIT_COLOR))
			break;
	}

	if (cnt == _length)
	{
		_hasSunk = true;
		for (int i = 0; i < _length; i++)
		{
			_points[i].setColor(SHIP_SUNK_COLOR);
		}
	}


	/* SIMON

	for (int i = 0; i < _length; i++) {

		if (_points[i].getColor() != SHIP_HIT_COLOR) {
			_hasSunk = false;
			return;
		}
	}

	_hasSunk = true;

	for (int i = 0; i < _length; i++)
		_points[i].setColor(SHIP_SUNK_COLOR);

	*/
}

std::ostream& operator<<(std::ostream& output, const Ship& ship)
{
	ship.draw(output);
	return output;
}
/******************************************************/
/* CODEZ ICI LES AUTRES MÉTHODES DE LA CLASSE "SHIP". */
/******************************************************/

