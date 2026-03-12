/*====================================
AUTEUR : Simon Fortier
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

/******************************************************/
/* CODEZ ICI LES AUTRES MÉTHODES DE LA CLASSE "SHIP". */
/******************************************************/

Ship::Ship(const std::string& name, int length)
{
	_name = name;
	_x = 0;
	_y = 0;
	_hasSunk = false;
	_direction = HORIZONTAL;

	setLength(length);

	updatePoints();
}

Ship::~Ship()
{
	_name = "";
	_x = 0;
	_y = 0;
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
}

void Ship::setPosition(int x, int y)
{
	assert(x >= 0);
	assert(y >= 0);

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
		setDirection(VERTICAL);
	else
		setDirection(HORIZONTAL);

	updatePoints();
}

void Ship::hide()
{
	// Do nothing if (_length <= 0)
	if (_length > 0)
		for (int i = 0; i < _length; i++)
			if (!(_points[i].getColor() == SHIP_HIT_COLOR || _points[i].getColor() == SHIP_SUNK_COLOR))
			{
#ifdef DEBUG_CODE
				_points[i].setColor(14);
#else
				_points[i].setColor(SHIP_HIDDEN_COLOR);
#endif
			}
}

// loi de la thermodynamique

bool Ship::checkCollision(const Ship& otherShip) const
{
	// Crash if checkCollision() called without setting _length and _name
	assert(_name != "" && _length > 0);

	for (int i = 0; i < _length; i++)
	{
		for (int j = 0; j < otherShip._length; j++)
		{
			if (_points[i].getX() == otherShip._points[j].getX() &&
					_points[i].getY() == otherShip._points[j].getY())
					{
						return true;
					}
		}
	}

	return false;
}

SHIP_HIT_TYPE Ship::placeHit(const Point& hitPosition)
{
	// Crash if placeHit() called without setting _length and _name
	assert(_name != "" && _length > 0);

	for (int i = 0; i < _length; i++)
	{
		if (_points[i].comparePosition(hitPosition))
		{
			if (_hasSunk)
				return SHIP_ALREADY_SUNK /* 1 */; // ship is sunk && hit on SHIP

			if (_points[i].getColor() == SHIP_HIT_COLOR)
				return SHIP_HIT_TWICE /* 2 */;

			_points[i].setColor(SHIP_HIT_COLOR);

			updateSunkStatus();

			return SHIP_HIT /* 3 */;
		}
	}

	return SHIP_NOT_HIT /* 0 */; // NO HIT ON SHIP
}

void Ship::print(std::ostream& output) const
{
	// Do nothing if not initialized with _length || _name

	if (!(_name == "" || _length == 0))
		output << _name << " (" << _length << ")" << std::endl;
}

void Ship::draw(std::ostream& output) const
{
	// Do nothing if not initialized with _length || _name

	if (!(_name == "" || _length == 0))
		for (int i = 0; i < _length; i++)
			_points[i].draw(output);
}

void Ship::read(std::istream& input)
{
	char c; // garbage collector :D

	input >> _name;
	input >> c;        // (
	input >> _length;
	input >> c;        // )

	// call setLength for the assert();
	setLength(_length);
}

std::istream& operator>>(std::istream& input, Ship& ship)
{
	ship.read(input);

	return input;
}

void Ship::updateSunkStatus()
{
	assert(_length > 0); // length cannot be 0 or negative

	for (int i = 0; i < _length; i++)
		if (_points[i].getColor() != SHIP_HIT_COLOR)
			return;

	_hasSunk = true;

	for (int i = 0; i < _length; i++)
		_points[i].setColor(SHIP_SUNK_COLOR);
}

std::ostream& operator<<(std::ostream& output, const Ship& ship)
{
	ship.draw(output);

	return output;
}


