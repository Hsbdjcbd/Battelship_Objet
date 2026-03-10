#pragma once
#include "point.h"
#include <iostream>
#include <cassert>

class Rect {
private:
    Point _coord;   // coordonnées du point supérieur gauche du rectangle
    int _w;         // largeur
    int _h;         // hauteur

public:
    // Constructeurs
    Rect();                       // par défaut
    Rect(int x, int y, int w, int h); // avec paramètres
    Rect(const Point& coord, int w, int h); // avec Point

    // Getters
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    const Point& getCoord() const;

    // Setters
    void setX(int x);
    void setY(int y);
    void setWidth(int w);
    void setHeight(int h);
    void setCoord(const Point& coord);

    // Méthodes
    bool contains(const Point& p) const;  // Vérifie si un point est à l’intérieur du rectangle
    void print(std::ostream& output) const;
};