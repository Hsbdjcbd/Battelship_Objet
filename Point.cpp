#include "Point.h"
#include <cassert>
#include <windows.h>
#include <iostream>


Point::Point() {
    _x = 0;
    _y = 0;
    _color = 7;
}

Point::Point(int x, int y) {
    _x = x;
    _y = y;
    _color = 7;
}


Point::Point(const Point& p) {
    _x = p._x;
    _y = p._y;
    _color = p._color;
}


Point::~Point() {
    _x = 0;
    _y = 0;
    _color = 0;
}

int Point::getX() const {
    return _x;
}

int Point::getY() const {
    return _y;
}

int Point::getColor() const {
    return _color;
}

Point Point::getPoint() const {
    return *this;
}


void Point::setX(const int x) {
    assert(x >= 0)
    _x = x;
}

void Point::setY(const int y) {
    assert(y >= 0);
    _y = y;
}

void Point::setPosition(const int x, const int y) {
    assert(x >= 0 && y >= 0);
    _x = x;
    _y = y;
}

void Point::setColor(const int color) {
    assert(color >= 0 && color <= 15);
    _color = color;
}

void Point::setPoint(const int x, const int y, const int color) {
    assert(x >= 0 && y >= 0);
    assert(color >= 0 && color <= 15);
    _x = x;
    _y = y;
    _color = color;
}

void goToXY(int xpos, int ypos) {
    COORD scrn;
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = static_cast<SHORT>(xpos); 
    scrn.Y = static_cast<SHORT>(ypos);
    SetConsoleCursorPosition(hOutput, scrn);
}

void Point::afficher() const {
    goToXY(_x, _y);


    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _color);

    std::cout << "\xFE";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void Point::draw(std::ostream& output) const {

    if (&output == &std::cout) {

        goToXY(_x, _y);

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _color);

        output << "\xFE";

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
    else {
        
        output << "(" << _x << "," << _y << ")■";
    }
}

void Point::print(std::ostream& output) const {
    output << "(" << _x << "," << _y << ") " << _color << std::endl;
}


void Point::read(std::istream& input){

    char trash;

    input >> trash  // (
        >> _x
        >> trash   // ,
        >> _y
        >> trash   // )
        >> _color;
}

