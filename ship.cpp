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

Ship::Ship(const std::string& name, int length) { //constructeur

	_name = name;
	_x = 0;
	_y = 0;
	_direction = HORIZONTAL;
	_hasSunk = false;

	setLength(length);

	updatePoints();
}

Ship::~Ship() {  //destructeur

	_name = "";
	_x = 0;
	_y = 0;
	_direction = HORIZONTAL;
	_length = 0;
	_hasSunk = false;
}

//getters

int Ship::getLength() const {
	return _length;
}

const Direction& Ship::getDirection() const {
	return _direction;
}

bool Ship::getSunkStatus() const {
	return _hasSunk;
}

//setters

void Ship::setPosition(int x, int y) {

	assert(x >= 0);
	assert(y >= 0);

	_x = x;
	_y = y;

	updatePoints();
}

void Ship::setLength(int length) {

	assert(length >= 0);
	assert(length <= SHIP_MAX_LENGTH);

	_length = length;

	updatePoints();
}

void Ship::setDirection(const Direction& direction) {

	_direction = direction;

	updatePoints();
}

//rotate

void Ship::rotate() {

	if (_direction == HORIZONTAL)
		_direction = VERTICAL;
	else
		_direction = HORIZONTAL;

	updatePoints();
}

//hide

void Ship::hide() {
	for (int i = 0; i < _length; i++)
		_points[i].setColor(SHIP_HIDDEN_COLOR);
}

//loi de la termodynamique

bool Ship::checkCollision(const Ship& otherShip) const {

	for (int i = 0; i < _length; i++) {

		for (int j = 0; j < otherShip._length; j++) {

			if (_points[i].getX() == otherShip._points[j].getX() &&
				_points[i].getY() == otherShip._points[j].getY()) {

				return true;
			}
		}
	}

	return false;
}

//direct hit

int Ship::placeHit(const Point& hitPosition) {

	for (int i = 0; i < _length; i++) {

		if (_points[i].getX() == hitPosition.getX() &&
			_points[i].getY() == hitPosition.getY()) {

			if (_hasSunk)
				return 1;

			if (_points[i].getColor() == SHIP_HIT_COLOR)
				return 2;

			_points[i].setColor(SHIP_HIT_COLOR);

			updateSunkStatus();

			return 3;
		}
	}

	return 0;
}

//print

void Ship::print(std::ostream& output) const {

	output << _name << " (" << _length << ")";
}

//draw

void Ship::draw(std::ostream& output) const {

	for (int i = 0; i < _length; i++)
		_points[i].draw(output);
}

//read

void Ship::read(std::istream& input) {

	char c;

	input >> _name;
	input >> c;        // (
	input >> _length;
	input >> c;        // )

	setLength(_length);
}

//operator

std::ostream& operator<<(std::ostream& output, const Ship& ship) {

	ship.draw(output);
	return output;
}

std::istream& operator>>(std::istream& input, Ship& ship) {

	ship.read(input);
	return input;
}

//couler

void Ship::updateSunkStatus() {

	for (int i = 0; i < _length; i++) {

		if (_points[i].getColor() != SHIP_HIT_COLOR) {
			return;
		}
	}

	_hasSunk = true;

	for (int i = 0; i < _length; i++)
		_points[i].setColor(SHIP_SUNK_COLOR);
}