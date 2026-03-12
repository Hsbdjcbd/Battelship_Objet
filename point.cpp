/*====================================
AUTEUR : Stanislas Royal
PROJET : General - inclut dans Jeu de Battleship
NOM DU FICHIER : point.cpp
DATE : 2026-03-11
DESCRIPTION : Classe Objet Point:: , Sert a contenir
des coordonnes et aisee les operations.
====================================*/
#include "point.h"

Point::Point() {

	// Create a new Point() to copy via operator=() ... not right resources-wise ...
	//*this = Point(0, 0, 7);

	setPoint(0, 0, 7);
}

Point::Point(int x, int y)
{
	setPoint(x, y, 7);
}

Point::Point(int x, int y, int color)
{
	setPoint(x, y, color);
}

//Remet les valeurs des proprietes a 0 pour effacer toutes traces de nos donnees

Point::~Point() {
	_x = _y = _color = 0;
	_drawChar = 0;
	_comparaisonExacte = 0;
}


//Creer une copie du point passe en parametre a l'aide du constructeur de copie

Point::Point(const Point& p) {

	setPoint(p._x, p._y, p._color);

	_drawChar = p._drawChar;
	_comparaisonExacte = p._comparaisonExacte;
}




int Point::getX() const
{
	return this->_x;
}

int Point::getY() const
{
	return _y;
}

int Point::getColor() const
{
	return _color;
}

char Point::getDrawingChar() const
{
	return _drawChar;
}

Point& Point::getPoint()
{
	return *this;
}


// setters
/// INFO: N'oubliez donc pas d'ajouter les assert dans vos mutateurs particuli'rement!

void Point::setX(const int x)
{
	assert(x >= 0);

	_x = x;
}

void Point::setY(const int y)
{
	assert(y >= 0);

	_y = y;
}

void Point::setColor(const int col)
{
	assert(col >= 0);

	_color = col;
}

void Point::setDrawingChar(char chr)
{
	_drawChar = chr;
}

void Point::setPoint(const int x, const int y, const int color)
{
	setX(x);
	setY(y);
	setColor(color);
}

void Point::setPosition(const int x, const int y)
{
	setX(x);
	setY(y);
}

Point& Point::operator=(const Point& p2)
{// Added in Lab3
	//surcharge de l'operator= qui permet de mettre les coordonnees et la couleur du premier point dans le 2e
		// ou cette ligne ci-dessous
		//p1 = p2 = p3;

	// use setPoint() for assert();
	setPoint(p2._x, p2._y, p2._color);

	_comparaisonExacte = p2._comparaisonExacte;
	_drawChar = p2._drawChar;

	return *this;
}

bool Point::operator==(const Point& p2)
{// Added in Lab3
	//surcharge de l'operator== qui compare 2 points et renvoie vrai s'ils sont a la meme position
	// et sont de la meme couleur

	// TODO: Add setCompareMode(int);

	if (_comparaisonExacte)
		return this->comparePosition(p2) && this->compareColor(p2);

	return this->comparePosition(p2);
}

bool Point::operator!=(const Point& p2)
{// Added in Lab3

	//surcharger aussi l'operator!= , pour indiquer si les coordonnees x ou y sont differentes ou
	//si la couleur est differente
	return (!(this->operator==(p2)));
}

std::ostream& operator<<(std::ostream& os, const Point& p1)
{ // Added in Lab3
	//fonction operator<< qui appelle la methode print
	p1.print(os);
	return os;
}
std::istream& operator>>(std::istream& is, Point& p1)
{ // Added in Lab3
	//fonction operator>> qui appelle la methode read
	p1.read(is);
	return is;
}

Point Point::operator+(const Point& p2)const
{ // Added in Lab3
	Point resultat(*this);

	resultat._x += p2._x;
	resultat._y += p2._y;

	return resultat;
}

Point Point::operator-(const Point& p2) const
{ // Added in Lab3
	Point resultat(*this);

	resultat._x -= p2._x;
	resultat._y -= p2._y;

	if (resultat._x < 0)
		resultat._x = 0;

	if (resultat._y < 0)
		resultat._y = 0;

	return resultat;
}

float distance(const Point& p1, const Point& p2)
{ // Added in Lab3
	return sqrtf(((p2._x - p1._x) ^ 2 + (p2._y - p1._y) ^ 2));
}

bool Point::comparePosition(const Point& p2) const
{
	return (_x == p2._x && _y == p2._y);
}

bool Point::compareColor(const Point& p2) const
{
	return (_color == p2._color);
}


// p2.draw(cout);	    //On dessine un point a la position (x, y) en console
// p2.draw(fichier);	//On dessine un point dans un fichier texte en ecriture;
void Point::draw(std::ostream& output) const
{

	assert(_color >= 0);
	assert(_x >= 0);
	assert(_y >= 0);

	//REVIEW - Not Cross-platform compatible

	HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD nbCharsWritten = 0;
	COORD loc = { _x, _y };

	if (&output == &std::cout)
	{

		// TODO: Check if Windows Console or Windows Terminal ...
//		goToXY(_x, _y); // SI DANS CONSOLE ...

		// changer la couleur pour celle choisie et aucune verification !

		goToXY(_x, _y);
		output << _drawChar;

		FillConsoleOutputAttribute(hconsole, _color, 1, loc, &nbCharsWritten);

		nbCharsWritten = 0;

		// FIXME: Not working, wrong char ? ...
		// FillConsoleOutputCharacterA(hconsole, _drawChar, 1, loc, &nbCharsWritten);

		// To Clear from problem in output ...
		// goto to 2 line after Point()
		goToXY(0, _y + 2);
	}
	else
		print(output);
}


void Point::print(std::ostream& output) const
{
	output << "(" << _x << "," << _y << ") " << _color << std::endl; // INFO: Do I use endl ??
}


void Point::read(std::istream& input)
{
	// FIXME: Not finished
	std::string strF;
	std::stringstream ss;
	std::getline(input, strF);

	char lost = ' ';

	int x = 0;
	int y = 0;
	int color = 0;

	if (strF.length())
	{
		if (strF[0] == '(')
		{
			// TODO: Add more check and error/fail cancellation

			ss.str(strF);
			ss >> lost >> x >> lost >> y >> lost >> color;

			if (x < 0)
				x = 0;

			_x = x;


			if (y < 0)
				y = 0;

			_y = y;

			if (color < 0)
				color = 7; // default color of Point::Point()

			_color = color;
		}
	}
}

/// INFO: Voici une fonction (comprendre ici�: PAS une m�thode de la classe Point)
// PAS UNE METHODE de Point
//fonction pour se positionner dans l'�cran � x,y
void goToXY(int xpos, int ypos) {
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos;
	scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}

