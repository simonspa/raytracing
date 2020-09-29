#pragma once
#include <iostream>

// Wir definiern eine neue Klasse (Datentype) namens Punkt
class Punkt {
// Alle Dinge, auf die man von aussen zugreifen darf:
public:
    /**
     * "Konstruktor" - Funktion, die aufgerufen wird, wenn wir ein neues Objekt vom Typ "Punkt" erzeugen
     * @param x X-Koorinate
     * @param y Y-Koorinate
     */
    Punkt(double x, double y, double z) {
        // Wir speichern die Parameter des Konstruktors in den "privaten" Variablen x_ y_ und z_:
        x_ = x;
        y_ = y;
        z_ = z;
    };

    Punkt() {
      x_ = 0;
      y_ = 0;
      z_ = 0;
    }

    // Wir rufen die "private" Variable x_ ab:
    double x() const { return x_; }
    // Wir rufen die "private" Variable y_ ab:
    double y() const { return y_; }
    double z() const { return z_; }

    friend std::ostream& operator<<(std::ostream& os, const Punkt& p);
// Dinge, auf die nur der Punkt selbst Zuriff hat:
private:
    double x_;
    double y_;
    double z_;
};

// so rechnest du Punkte minus
Punkt operator-(const Punkt &a, const Punkt &b) {
  return Punkt(a.x() - b.x(),a.y() - b.y(),a.z() - b.z());
}

// So rechnest du Punkte plus
Punkt operator+(const Punkt &a, const Punkt &b) {
  return Punkt(a.x() + b.x(),a.y() + b.y(),a.z() + b.z());
}

// So rechnest du eine zahl (double) mal einen Punkt
Punkt operator*(const double &a, const Punkt &b) {
  return Punkt(a * b.x(),a * b.y(),a * b.z());
}


std::ostream& operator<<(std::ostream& os, const Punkt& p) {
    os << p.x() << "," << p.y() << "," << p.z();
    return os;
}
