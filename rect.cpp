#include "rect.h"

//constructeur

Rect::Rect() {
    _coord.setPosition(0, 0);
    _w = 0;
    _h = 0;
}

Rect::Rect(int x, int y, int w, int h) {
    assert(w >= 0 && h >= 0);
    _coord.setPosition(x, y);
    _w = w;
    _h = h;
}

Rect::Rect(const Point& coord, int w, int h) {
    assert(w >= 0 && h >= 0);
    _coord = coord;
    _w = w;
    _h = h;
}

//getters

int Rect::getX() const { return _coord.getX(); }
int Rect::getY() const { return _coord.getY(); }
int Rect::getWidth() const { return _w; }
int Rect::getHeight() const { return _h; }
const Point& Rect::getCoord() const { return _coord; }

//setters

void Rect::setX(int x) { _coord.setX(x); }
void Rect::setY(int y) { _coord.setY(y); }
void Rect::setWidth(int w) { assert(w >= 0); _w = w; }
void Rect::setHeight(int h) { assert(h >= 0); _h = h; }
void Rect::setCoord(const Point& coord) { _coord = coord; }

//metodes

bool Rect::contains(const Point& p) const {
    int px = p.getX();
    int py = p.getY();
    int x0 = _coord.getX();
    int y0 = _coord.getY();
    return (px >= x0 && px < x0 + _w && py >= y0 && py < y0 + _h);
}

void Rect::print(std::ostream& output) const {
    output << "Rect: (" << getX() << "," << getY() << ") "
        << "Width: " << _w << ", Height: " << _h << "\n";
}