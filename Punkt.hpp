#pragma once
#include <iostream>

// Wir definiern eine neue Klasse (Datentype) namens point
class point {
// Alle Dinge, auf die man von aussen zugreifen darf:
public:
    /**
     * "Konstruktor" - Funktion, die aufgerufen wird, wenn wir ein neues Objekt vom Typ "point" erzeugen
     * @param x X-Koorinate
     * @param y Y-Koorinate
     */
    point(double x, double y, double z) {
        // Wir speichern die Parameter des Konstruktors in den "privaten" Variablen x_ y_ und z_:
        x_ = x;
        y_ = y;
        z_ = z;
    };

    point() {
      x_ = 0;
      y_ = 0;
      z_ = 0;
    }

    // Wir rufen die "private" Variable x_ ab:
    double x() const { return x_; }
    // Wir rufen die "private" Variable y_ ab:
    double y() const { return y_; }
    // Wir rufen die private Variable z_ ab:
    double z() const { return z_; }

    friend std::ostream& operator<<(std::ostream& os, const point& p);
// Dinge, auf die nur der point selbst Zuriff hat:
private:
    double x_;
    double y_;
    double z_;
};

// so rechnest du pointe minus
point operator-(const point &a, const point &b) {
  return point(a.x() - b.x(),a.y() - b.y(),a.z() - b.z());
}

// So rechnest du points plus
point operator+(const point &a, const point &b) {
  return point(a.x() + b.x(),a.y() + b.y(),a.z() + b.z());
}

// So rechnest du eine Zahl (double) mal einen point
point operator*(const double &a, const point &b) {
  return point(a * b.x(),a * b.y(),a * b.z());
}

// So druckt man pointe aus
std::ostream& operator<<(std::ostream& os, const point& p) {
    os << p.x() << "," << p.y() << "," << p.z();
    return os;
}
