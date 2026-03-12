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
	// NOTE: Rect(Point p, int hauteur, int largeur);

	Rect(int x, int y, int w = 0, int h = 0);

	Rect(const Rect& r);

	~Rect(); // destructeur pour reinitialiser memoire a ZERO


	// getteurs

	int getWidth() const;
	int getHeight() const;



	const Point& getPosition() const;
	Point& getPosition();
	Point& getPoint();


	/// Setteurs

	void setWidth(int w);
	void setHeight(int h);
	void setSize(int w, int h);
	void setRectangle(int x, int y, int w = 0, int h = 0);

	// NOTE: void setPosition(int x, int y) { _coord.setPosition(x,y); }

	// operator

	Rect& operator=(const Rect& r2);

	bool operator==(const Rect& r2) const;
	bool operator!=(const Rect& r2) const;
	bool operator>(const Rect& r2) const;
	bool operator<(const Rect& r2) const;

	bool operator>=(const Rect& r2) const;
	bool operator<=(const Rect& r2) const;


	// Methodes autres

	void draw(std::ostream& output) const;

	// NOTE: serialize format ?? : (x,y) color h X w    instead of (x,y) h X w

	void print(std::ostream& output) const;

	void read(std::istream& input);


	int surface() const;

	int perimetre()const;

};

std::ostream& operator<<(std::ostream& os, const Rect& r1);
std::istream& operator>>(std::istream& is, Rect& r1);