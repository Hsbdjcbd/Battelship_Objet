#pragma once
#include <cassert>
#include <fstream>

class Point {
private:
    int _x, _y;      // coordonnées du point
    int _color;      // couleur du point

public:
    Point();                     // constructeur par défaut sert a quasiment fuckall
    Point(int x, int y);         // constructeur avec paramètres
    Point(const Point& p);       // constructeur de copie
    //~Point();                    // destructeur sert a fuckall

    int getX() const;
    int getY() const;
    int getColor() const;

    Point getPoint() const;

    void setX(const int x);                              // modifie la coordonnée x
    void setY(const int y);                              // modifie la coordonnée y
    void setPosition(const int x, const int y);         // modifie x et y
    void setColor(const int color);                      // modifie la couleur
    void setPoint(const int x, const int y, const int color); // modifie x, y et couleur
    void afficher() const;
    void draw(std::ostream& output) const;
    void print(std::ostream& output) const;  // affiche (x,y) color
    void read(std::istream& input);

};

// Prototype de la fonction externe
void goToXY(int xpos, int ypos);

