/*====================================
AUTEUR : Stanislas Royal
PROJET : General - inclut dans Jeu de Battleship
NOM DU FICHIER : point.cpp
DATE : 2026-03-11
DESCRIPTION : Classe Objet Point:: , Sert a contenir
des coordonnes et aisee les operations.
====================================*/
#include "point.h"

/* IMPORTANT */
//	 Le nom d�une classe est toujours au singulier, car une class repr�sente un mod�le unique d�objet.
//	 Les noms des propri�t�s sont �crits en minuscule avec une majuscule � chaque d�but de mot suivant le premier, comme toutes les variables (camelCase).
//	 Les propri�t�s doivent �tre pr�c�d�es du soulign� et �tre sans pr�fixe.
//	Mettre un ent�te de commentaire au d�but du .h comme les ent�tes de programme pour expliquer l�objet. Vous n�avez pas � le faire pour le fichier .cpp.
//	 Privil�gier des noms clairs pour vos propri�t�s et vos m�thodes, plut�t que des commentaires.
//	*/

Point::Point() {
	// _x = _y = 0;
	// _color = 7;	//couleur gris p�le (Lite gray) par d�faut
	Point(0, 0, 7);
}


Point::Point(int x, int y)
{
	_x = x;
	_y = y;
	_color = 7;
	// Point(x, y, 7);
}

Point::Point(int x, int y, int color)
{
	_x = x;
	_y = y;
	_color = color;
}

//Remet les valeurs des propri�t�s � 0 pour effacer toutes traces de nos donn�es

Point::~Point() {
	_x = _y = _color = 0;
	_drawChar = 0;
	_comparaisonExacte = 0;
}


//Cr�er une copie du point pass� en param�tre � l�aide du constructeur de copie

Point::Point(const Point& p) {
	assert(p._color >= 0);
	assert(p._x >= 0);
	assert(p._y >= 0);

	_x = p._x;
	_y = p._y;
	_color = p._color;
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

Point& Point::getPoint() {

	return *this;
}


// setters
/// INFO: N�oubliez donc pas d�ajouter les assert dans vos mutateurs particuli�rement!

void Point::setX(const int x)
{
	assert(x >= 0);
	_x = x;
}

void Point::setY(const int y) {
	assert(y >= 0);
	_y = y;
}

void Point::setColor(const int col) {
	assert(col >= 0);
	_color = col;
}

void Point::setDrawingChar(char chr)
{
	_drawChar = chr;
}

void Point::setPoint(const int x, const int y, const int color)
{
	_x = x;
	_y = y;
	_color = color;

}

void Point::setPosition(const int x, const int y)
{
	_x = x;
	_y = y;
}

Point& Point::operator=(const Point& p2)
{// Added in Lab3
	//surcharge de l�operator= qui permet de mettre les coordonn�es et la couleur du premier point dans le 2e
		// ou cette ligne ci-dessous
		//p1 = p2 = p3;

	_x = p2._x;
	_y = p2._y;
	_color = p2._color;
	_comparaisonExacte = p2._comparaisonExacte;
	_drawChar = p2._drawChar;

	return *this;
}
bool Point::operator==(const Point& p2)
{// Added in Lab3
	//surcharge de l�operator== qui compare 2 points et renvoie vrai s�ils sont � la m�me position
	// et sont de la m�me couleur
	if (_comparaisonExacte)
		return this->comparePosition(p2) && this->compareColor(p2);

	return this->comparePosition(p2);
}

bool Point::operator!=(const Point& p2)
{// Added in Lab3

	//surcharger aussi l�operator!= , pour indiquer si les coordonn�es x ou y sont diff�rentes ou
	//si la couleur est diff�rente
	return (!(this->operator==(p2)));
}

std::ostream& operator<<(std::ostream& os, const Point& p1)
{ // Added in Lab3
	//fonction operator<< qui appelle la m�thode print
	p1.print(os);
	return os;
}
std::istream& operator>>(std::istream& is, Point& p1)
{ // Added in Lab3
	//fonction operator>> qui appelle la m�thode read
	p1.read(is);
	return is;
}

Point Point::operator+(const Point& p2)const
{ // Added in Lab3
	// FIXME: Lost color or no operation on color ...
	// FIXME: Do I need to make sure to be => 0 ??
	Point resultat(*this);

	resultat._x += p2._x;
	resultat._y += p2._y;

	return resultat;
}

Point Point::operator-(const Point& p2) const
{ // Added in Lab3
		// FIXME: Lost color or no operation on color ...
	// FIXME: Do I need to make sure to be => 0 ??
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


// p2.draw(cout);	    //On dessine un point � la position (x, y) en console
// p2.draw(fichier);	//On dessine un point dans un fichier texte en �criture;
void Point::draw(std::ostream& output) const
{

	//assert(_color >= 0);
	assert(_x >= 0);
	assert(_y >= 0);

	//Utiliser la fonction goToXY pour se positionner

	//Changer la couleur du texte en console � partir de la couleur du point

	//Afficher le point avec la couleur sp�cifi�e
	HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD nbCharsWritten = 0;
	COORD loc = { _x, _y };
	char chr = _drawChar;


	if (&output == &std::cout)
	{

		// TODO: Check if Windows ...
//		goToXY(_x, _y); // SI DANS CONSOLE ...

		// changer la couleur pour celle choisie et aucune verification !

		goToXY(_x, _y);
		output << _drawChar;


		FillConsoleOutputAttribute(hconsole, _color, 1, loc, &nbCharsWritten);

		nbCharsWritten = 0;

		// FIXME: Not working, wrong char ...
		FillConsoleOutputCharacterA(hconsole, chr, 1, loc, &nbCharsWritten);




		// To Clear from problem in output ...
		goToXY(0, _y + 2);
	}
	else
		print(output);
}


void Point::print(std::ostream& output) const
{
	output << "(" << _x << "," << _y << ") " << _color << std::endl; // INFO: Do I use endl ??
}

// p2.print(cout);		//on affiche les coordonn�es comme ceci: (x,y) color


void Point::read(std::istream& input)
{

	// fait la lecture d�une seule ligne du fichier (le stream re�u en param�tre) en pla�ant directement les coordonn�es et couleurs dans les propri�t�s
	// FIXME: Not finished
	std::string strF;
	std::stringstream ss;
	std::getline(input, strF);
	char lost = ' ';
	// not the best way to ensure positive number ...
	int x = 0;
	int y = 0;
	int color = 0;

	if (strF.length())
	{
		if (strF[0] == '(')
		{
			// TODO: Add more check and error/fail cancellation
			//std::cout << strF << std::endl;
			ss.str(strF);
			ss >> lost >> x >> lost >> y >> lost >> color;
			//			std::cout << strF << std::endl << "X: " << x << "\tY: " << y << "\tCol: " << color << std::endl;

			if (x >= 0)
				_x = x;
			else
				_x = 0;

			if (y >= 0)
				_y = y;
			else
				_y = 0;

			_color = color;
		}
		//		else
		//			std::cout << "Erreur Lecture Point" << std::endl;

	}


	//	else
	//		std::cout << "VIDE: Lecture Point" << std::endl;

		// FIXME : do not use getline() ...


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

