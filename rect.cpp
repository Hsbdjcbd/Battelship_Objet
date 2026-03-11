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
	_coord.setColor(7);
	_coord.setPosition(0, 0);
	_w = _h = 0;
}
Rect::Rect(const Rect& r)
{
	_w = r._w;
	_h = r._h;
	_coord = r._coord;
}

Rect::Rect(int x, int y, int w, int h) {

	//  Attention, un rectangle ne peut pas avoir de coordonn�es ou de dimensions n�gatives, sinon on g�n�rera une exception.
/*	assert(x >= 0);
	assert(y >= 0);
	assert(w >= 0);
	assert(h >= 0);
	*/
	_coord.setColor(7);
	_coord.setPosition(x, y);
	this->setRectangle(x, y, w, h);
	/*
	_coord.setPosition(x, y);
	_w = w;
	//si ce constructeur est appel� avec seulement 2 int
	_h = h;
	//les 2 autres seront initialis�s � 0

	*/
}

Rect::~Rect()
{
	//not needed, _coord will be deleted and set to zero in ~Point() // _coord.setPosition(0, 0);
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
	assert(w >= 0);
	assert(h >= 0);

	_w = w;
	_h = h;
}

void Rect::setRectangle(int x, int y, int w, int h)
{
	assert(x >= 0);
	assert(y >= 0);
	assert(w >= 0);
	assert(h >= 0);

	this->setSize(w, h);
	this->setHeight(h);
	this->setWidth(w);

	this->_coord.setPosition(x, y);


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
			p0.setX(_coord.getX() + _w - 1);
			p0.draw(output);
		}
	}


}

void Rect::read(std::istream& input) {

	// fait la lecture d�une seule ligne du fichier (le stream re�u en param�tre) en pla�ant directement les coordonn�es et couleurs dans les propri�t�s
	// FIXME: Not finished
	std::string strF;
	std::stringstream ss;
	std::getline(input, strF);
	char lost = ' ';
	// not the best way to ensure positive number ...
	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;

	if (strF.length())
	{
		if (strF[0] == '(')
		{
			// TODO: Add more check and error/fail cancellation
			ss.str(strF);
			ss >> lost >> x >> lost >> y >> lost >> w >> lost >> h;

			if (x >= 0)
				x = 0;

			_coord.setX(x);

			if (y <= 0)
				y = 0;

			_coord.setY(y);


			if (h >= 0)
				_h = h;
			else
				_h = 0;

			if (w >= 0)
				_w = w;
			else
				_w = 0;
		}
		//		else
		//			std::cout << "Erreur Lecture Rect" << std::endl;

	}


	//	else
	//		std::cout << "VIDE: Lecture Point" << std::endl;

		// FIXME : do not use getline() ...
}

std::ostream& operator<<(std::ostream& os, const Rect& r1)
{ // Added in Lab3
	//fonction operator<< qui appelle la m�thode print
	r1.print(os);
	return os;
}
std::istream& operator>>(std::istream& is, Rect& r1)
{ // Added in Lab3
	//fonction operator>> qui appelle la m�thode read
	r1.read(is);
	return is;
}

Rect& Rect::operator=(const Rect& r2)
{
	_w = r2._w;
	_h = r2._h;
	_coord = r2._coord;

	return *this;
}

bool Rect::operator==(const Rect& r2) const
{ // l�operator== qui compare les dimensions des rectangles
	/// TODO: ??? DIMENSIONS ???


	// PERIMETRE :: >>>
	return ((this->perimetre()) == (r2.perimetre()));

	//	return ((this->surface()) == (r2.surface()));

}
bool Rect::operator!=(const Rect& r2) const
{
	return !(this->operator==(r2));
}


bool Rect::operator>(const Rect& r2) const
{ //surcharge de l�operator> qui compare la taille (aire ou p�rim�tre) des rectangles
	return ((this->perimetre()) > (r2.perimetre()));

	//	return ((this->surface()) > (r2.surface()));
}
bool Rect::operator<(const Rect& r2) const
{ //surcharge de l�operator< qui compare la taille (aire ou p�rim�tre) des rectangles


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



/*

getWidth, getHeight, et getPosition.Vous devrez coder deux
versions de cette derni�re m�thode : une version qui retournera une r�f�rence non constante vers le point _coord et une autre
version qui retournera une r�f�rence constante vers ce point :
� Version non const : Point & getPosition();
� Version const : const Point& getPosition() const; */


