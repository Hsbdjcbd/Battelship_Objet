/*====================================
AUTEUR : Stanislas Royal
PROJET : General - inclut dans Jeu de Battleship
NOM DU FICHIER : rect.h
DATE : 2026-03-11
DESCRIPTION : Classe Objet Rect:: , Sert a contenir
des coordonnes et dimensions d'un rectangle et aisee les operations.
====================================*/
#pragma once

#include <assert.h>
#include <Windows.h>
#include <iostream>

#include "point.h"



class Rect {
private:
	Point _coord;	//coordonn�es du point sup�rieur gauche du rectangle
	int _w;			//largeur
	int _h;			//hauteur



public:
	// Nous allons cr�er un constructeur sans param�tre, un constructeur avec une coordonn�e et les dimensions du rectangle en
	//		param�tre, qui peut avoir une valeur par d�faut � 0.

	Rect();
	/* Le constructeur sans param�tre n�a qu�� initialiser la largeur et la hauteur � 0, car le point est construit automatiquement � 0
gr�ce au constructeur sans param�tre cr�� dans la classe Point. */
// Rect(Point p, int hauteur, int largeur);
	Rect(int x, int y, int w = 0, int h = 0);
	Rect(const Rect& r);
	~Rect(); // desctructeur pour reinitialiser memoire a ZERO



	// getteurs

	int getWidth() const;
	int getHeight() const;



	const Point& getPosition() const;
	Point& getPosition();
	Point& getPoint();


	/// Setteurs


	/// setWidth, setHeight, setSize, setRectangle. Pour la
/// 	m�thode setRectangle, faites passer les 4 param�tres soit x et y pour le point ainsi que la largeur et la hauteur.

	void setWidth(int w);
	void setHeight(int h);
	void setSize(int w, int h);
	void setRectangle(int x, int y, int w = 0, int h = 0);


	// operator

	Rect& operator=(const Rect& r2);

	bool operator==(const Rect& r2) const;
	bool operator!=(const Rect& r2) const;
	bool operator>(const Rect& r2) const;
	bool operator<(const Rect& r2) const;


	bool operator>=(const Rect& r2) const;
	bool operator<=(const Rect& r2) const;





	// Methodes autres

	// Pour la m�thode read, faites un appel � la m�thodes read de la classe Point. En ce qui concerne la m�thode draw, vous
	//		aurez probablement besoin de la coder � l�aide de boucles sans n�cessairement faire appel � la m�thode draw du Point.

	void draw(std::ostream& output) const;

	void print(std::ostream& output) const;		// (x,y) color h X w

	void read(std::istream& input);				// (x,y) color h X w


	int surface() const;

	int perimetre()const;

};

std::ostream& operator<<(std::ostream& os, const Rect& r1);
std::istream& operator>>(std::istream& is, Rect& r1);