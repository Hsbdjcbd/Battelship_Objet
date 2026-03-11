/*====================================
AUTEUR : Stanislas Royal
PROJET : General - inclut dans Jeu de Battleship
NOM DU FICHIER : point.h
DATE : 2026-03-11
DESCRIPTION : Classe Objet Point:: , Sert a contenir
des coordonnes et aisee les operations.
====================================*/
#pragma once

#include <assert.h>
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <string>

class Point
{
private:
	int _x, _y;		//coordonn�es du point
	int _color;		//couleur du point
	bool _comparaisonExacte = true;
	char _drawChar = '\xFE';

public:
	// constructeur
	Point();				//initialise le point � l�origine
	Point(int x, int y);	//initialise le point � (x,y)
	Point(int x, int y, int color);

	// destructeur
	~Point();				//remet le point � l�origine et couleur a zero
	// le destructeur de point est appel� � l�accolade fermante du main car c�est l�
		//que le compilateur tente de d�truire le point

	// Copieur
	Point(const Point& p);



	// METHODES

	// getters			CLASS::fn() const; TO NOT MODIFY CLASS

	int getX() const;
	int getY() const;
	int getColor() const;
	char getDrawingChar() const;

	Point& getPoint();



	// setters


	/* Voici le prototype de la m�thode setX. Codez sa d�finition, ainsi les m�thodes
	// MOI IL ME MANQUAIT LES const ??
//	setY(const int y)
// setPosition(const int x, const int y)
// setColor(const int color)
// setPoint(const int x, const int y, const int color). */

	void setX(const int x);			//modifie la coordonn�e x
	void setY(const int y);			//modifie la coordonn�e y
	void setColor(const int col);	//modifie la couleur
	void setDrawingChar(char chr);

	void setPoint(const int x, const int y, const int color);
	void setPosition(const int x, const int y);


	// methodes autres

	void draw(std::ostream& output) const;

	void print(std::ostream& output) const;

	void read(std::istream& input);

	bool comparePosition(const Point& p2) const;
	bool compareColor(const Point& p2) const;


	// Operators

	Point& operator=(const Point& p2);
	bool operator==(const Point& p2);
	bool operator!=(const Point& p2);

	Point operator+(const Point& p2)const;
	Point operator-(const Point& p2)const;


	// Fonctions amies

	friend float distance(const Point& p1, const Point& p2);
};

std::ostream& operator<<(std::ostream& os, const Point& p1);
std::istream& operator>>(std::istream& is, Point& p1);



void goToXY(int xpos, int ypos);

// float distance(const Point p1, const Point p2);

// return sqrt( ( p2.x - p1.x )^2 + ( p2.y - p1.y )^2 );
// <cmath>