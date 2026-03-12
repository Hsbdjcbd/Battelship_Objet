/*====================================
AUTEUR : Stanislas Royal
PROJET : General - inclut dans Jeu de Battleship
NOM DU FICHIER : rect.cpp
DATE : 2026-03-11
DESCRIPTION : Classe Objet Rect:: , Sert a contenir
des coordonnes et dimensions d'un rectangle et aisee les operations.
====================================*/
#include "rect.h"


Rect::Rect()
{
	// TODO: color of Point why ??
	// _coord.setColor(7);

	this->setRectangle(0, 0, 0, 0);
}

Rect::Rect(const Rect& r)
{
	this->setHeight(r._h);
	this->setWidth(r._w);

	// Copy Point with x and y and color
	_coord = r._coord;
}

Rect::Rect(int x, int y, int w, int h)
{
	//TODO: _coord.setColor(7);

	this->setRectangle(x, y, w, h);
}

Rect::~Rect()
{
	//not needed, _coord will be deleted and set to zero in ~Point() :-> _coord.setPosition(0, 0);
	_w = _h = 0;
}

int Rect::getWidth() const
{
	return _w;
}

int Rect::getHeight() const
{
	return _h;
}

Point& Rect::getPosition()
{
	return _coord;
}

Point& Rect::getPoint()
{
	return _coord;
}

const Point& Rect::getPosition() const
{
	return _coord;
}

void Rect::setWidth(int w)
{
	assert(w >= 0);

	_w = w;
}

void Rect::setHeight(int h)
{
	assert(h >= 0);

	_h = h;
}

void Rect::setSize(int w, int h)
{
	this->setWidth(w);
	this->setHeight(h);
}

void Rect::setRectangle(int x, int y, int w, int h)
{
	// assert() in Point()::set*()

	this->_coord.setPosition(x, y);

	this->setSize(w, h);
}



int Rect::surface() const {
	return (_w * _h);
}

int Rect::perimetre() const
{
	return ((_w * 2) + (_h * 2));
}

void Rect::print(std::ostream& output) const
{
	output << "(" << _coord.getX() << "," << _coord.getY() << ") " << _w << " X " << _h << std::endl;
}

void Rect::draw(std::ostream& output) const
{
	// TODO: Test _w et _h at : 0, 1, 2, 3

	assert(_coord.getColor() >= 0);
	assert(_coord.getX() >= 0);
	assert(_coord.getY() >= 0);


	Point p0(_coord);

	for (int i = 0; i < _h; i++)
	{
		p0.setY(_coord.getY() + i);
		if (i == 0 || i == (_h - 1))
		{
			for (int j = 0; j < _w; j++)
			{
				// print full line
				p0.setX(_coord.getX() + j);

				p0.draw(output);
			}
		}
		else
		{
			// print first column and last
			p0.setX(_coord.getX());
			p0.draw(output);

			// TODO: Test new if !!!
			if (_w > 0)
			{
				p0.setX(_coord.getX() + _w - 1);
				p0.draw(output);
			}
		}
	}
}

void Rect::read(std::istream& input) {

	// FIXME: Not finished | Verification not robust yet.
	// FIXME:  try not to use getline() ???

	std::string strF;
	std::stringstream ss;
	std::getline(input, strF);

	char lost = ' ';

	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;

	if (strF.length()) // length not 0
	{
		if (strF[0] == '(')
		{
			// TODO: Add more check and error/fail cancellation
			ss.str(strF);
			ss >> lost >> x >> lost >> y >> lost >> w >> lost >> h;

			if (x <= 0)
				x = 0;

			if (y <= 0)
				y = 0;

			if (h <= 0)
				h = 0;

			if (w <= 0)
				w = 0;

			_coord.setPosition(x, y);

			this->setHeight(h);
			this->setWidth(w);

		}
	}
}

std::ostream& operator<<(std::ostream& os, const Rect& r1)
{ // Added in Lab3
	r1.print(os);

	return os;
}
std::istream& operator>>(std::istream& is, Rect& r1)
{ // Added in Lab3
	r1.read(is);

	return is;
}

Rect& Rect::operator=(const Rect& r2)
{
	/* TODO: _w = r2._w;
	_h = r2._h; */

	// use set*() for assert even when copying memory !!
	this->setWidth(r2._w);
	this->setHeight(r2._h);

	_coord = r2._coord;

	return *this;
}

bool Rect::operator==(const Rect& r2) const
{	// TODO: ??? DIMENSIONS ???

	// PERIMETRE :: >>>
	return ((this->perimetre()) == (r2.perimetre()));

	//	return ((this->surface()) == (r2.surface()));

}

bool Rect::operator!=(const Rect& r2) const
{
	return !(this->operator==(r2));
}


bool Rect::operator>(const Rect& r2) const
{ // compare la taille (aire ou perimetre) des rectangles
	return ((this->perimetre()) > (r2.perimetre()));

	//	return ((this->surface()) > (r2.surface()));
}

bool Rect::operator<(const Rect& r2) const
{ // compare la taille (aire ou perimetre) des rectangles
	return ((this->perimetre()) < (r2.perimetre()));

	//	return ((this->surface()) < (r2.surface()));
}

bool Rect::operator>=(const Rect& r2) const
{
	return this->operator==(r2) || this->operator>(r2);
}

bool Rect::operator<=(const Rect& r2) const
{
	return this->operator==(r2) || this->operator<(r2);
}


