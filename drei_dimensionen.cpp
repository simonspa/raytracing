#include <iostream>

#define DEBUG 1

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

std::ostream& operator<<(std::ostream& os, const Punkt& p) {
    os << p.x() << "," << p.y() << "," << p.z();
    return os;
}

// Wir definieren eine neue Klasse (Datentyp), benannt nach dem Siliziumdetektor-Dings:
class Implant {
public:
    /**
     * Konstruktor
     * @param b Breite des Dings ( x Koordinate )
     * @param h Hoehe des Dings (z Koorinate)
     *@paran l laenge des Dings (y Koorinate)
     */
    Implant(double b, double l, double h) {
        laenge = l;
        breite = b;
        hoehe = h;
    };

    /**
     * Berechnet die Flaeche des Implants
     * @return Flaeche
     */
    double flaeche() const {
        return laenge * breite;
    };

    double volumen() const {
        return hoehe * breite * laenge;
    };

    /**
     * Funktion zur Berechnung des Schnittpunks der Geraden durch zwei Punkte a und b mit der linken Seite des Implants
     * @param  a Ein Punkt
     * @param  b Anderer Punkt
     * @return  Schnittpunkt auf geraden der linken Seite
     */
     //Schnittpunkt hat x,y,z und 3 differenzen (lange strecken), 3 kurze strecken => lage des schnittpunkts
     //x= -breite/2  y= a.y() - kurz_y z=
    Punkt schnittpunktLinks(Punkt a, Punkt b) const {
        double differenz_x = b.x() - a.x();
        if(differenz_x == 0) {
            throw std::runtime_error("");
        }

        double differenz_y = b.y() - a.y();
        double differenz_z = b.z() - a.z();

        double kurz_x = a.x() + breite/2;
        double kurz_y = kurz_x * differenz_y / differenz_x;
        double kurz_z = kurz_x * differenz_z / differenz_x;

        return Punkt(- breite / 2, a.y() - kurz_y,a.z() - kurz_z);
    };

    /**
     * siehe schnittpunktLinks
     */

    Punkt schnittpunktRechts(Punkt a, Punkt b) const {

        double differenz_x = b.x() - a.x();
        if(differenz_x == 0) {
            throw std::runtime_error("");
        }

        double differenz_y = b.y() - a.y();
        double differenz_z = b.z() - a.z();

        double kurz_x = a.z() - breite/2;
        double kurz_y = kurz_x * differenz_y / differenz_x;
        double kurz_z = kurz_x * differenz_z / differenz_x;


        return Punkt(+ breite / 2, a.y() - kurz_y, a.z() - kurz_z);
    };

    /**
     * siehe schnittpunktLinks
     */
    Punkt schnittpunktUnten(Punkt a, Punkt b) const {
        double differenz_x = b.x() - a.x();
        double differenz_y = b.y() - a.y();
        double differenz_z = b.z() - a.z();
        if(differenz_z == 0) {
            throw std::runtime_error("");
        }

	       double kurz_z = a.z() + hoehe;
	       double kurz_y = kurz_z * differenz_y / differenz_z;
         double kurz_x = kurz_z * differenz_x / differenz_z;

        return Punkt(a.x() - kurz_x, a.y() - kurz_y, - hoehe );
    };

/** x= laenge / 2
y= a.y - kurz_y
z= a.z - kurz_z
*/
    Punkt schnittpunktVorne (Punkt a, Punkt b) const {
      double differenz_x = b.x() - a.x();
      double differenz_y = b.y() - a.y();
      if(differenz_y == 0) {
          throw std::runtime_error("");
      }
      double differenz_z = b.z() - a.z();

      double kurz_y = laenge / 2;
      double kurz_x = kurz_y * differenz_x / differenz_y;
      double kurz_z = kurz_y * differenz_z / differenz_y;

      return Punkt(a.x() - kurz_x, kurz_y, a.z() - kurz_z );


    }
/**
x=
y=
z=
*/
    Punkt schnittpunktHinten (Punkt a, Punkt b) const {
      double differenz_x = b.x() - a.x();
      double differenz_y = b.y() - a.y();
      if(differenz_y == 0) {
          throw std::runtime_error("");
      }
      double differenz_z = b.z() - a.z();

      double kurz_y = - laenge / 2;
      double kurz_x = kurz_y * differenz_x / differenz_y;
      double kurz_z = kurz_y * differenz_z / differenz_y;

      return Punkt(a.x() - kurz_x, kurz_y, a.z() - kurz_z );


    }


    /**
     * Hilfsfunktion um zu berechnen ob Punkt x zwischen Punkten a und b liegt.
     * @return True wenn dazwischen, false wenn nicht.
     */
    bool between(Punkt a, Punkt b, Punkt x) const {
        return (x.y() <= a.y() && x.y() >= b.y()) || (x.y() >= a.y() && x.y() <= b.y());
    };

    /**
     * Funktion zur Bestimmung des Schnittpunks der Verbindungslinie zweier Punkte mit dem Implant:
     * @param  a Ein Punkt ausserhalb
     * @param  b Ein Punkt innheralb
     * @return   Schnittpunkt
     * @throws runtime_error wenn kein Schnittpunkt gefunden werden kann
     */
    Punkt schnittpunkt(Punkt a, Punkt b) const {

      // Checken ob a definitiv innen und b definitv aussen ist:
      

	try {
	    Punkt links = schnittpunktLinks(a, b);
      if(DEBUG) std::cout << "Schnittpunkt mit linker Ebene ist: " << links << std::endl;
	    if((links.z() >= -hoehe && links.z() <= 0) && (links.y() >= laenge / 2 && links.y() <= - laenge / 2)) {
                if(DEBUG) std::cout << "Schnittpunkt mit linker Seitenflaeche ist: " << links << std::endl;
                // Ueberpruefen, ob der Schnittpunkt wirlich zwischen a und b liegt und somit der Schnittpunkt sein kann:
                if(between(a, b, links)) {
                    return links;
                  } else if (DEBUG) {
                    std::cout << "Schnittpunkt mit linker Seitenflaeche nicht zwischen den Punkten." << std::endl;
                }
            } else if(DEBUG) {
              if(DEBUG) std::cout << "Kein Schnittpunkt mit linker Seitenflaeche." << std::endl;
            }
       } catch(...) {
           if(DEBUG) std::cout << "Kein Schnittpunkt mit linker Ebene." << std::endl;
       }

  try {
       	     Punkt rechts = schnittpunktRechts(a, b);
             if(DEBUG) std::cout << "Schnittpunkt mit rechter Ebene ist: " << rechts << std::endl;
       	     if((rechts.z() >= -hoehe && rechts.z() <= 0) && (rechts.y() >= laenge / 2 && rechts.y() <= - laenge / 2)) {
                if(DEBUG) std::cout << "Schnittpunkt mit rechter Seitenflaeche ist: " << rechts << std::endl;
                if(between(a, b, rechts)) {
                	return rechts;
                } else if (DEBUG) {
                  std::cout << "Schnittpunkt mit rechter Seitenflaeche nicht zwischen den Punkten." << std::endl;
                }
            } else if(DEBUG) {
              if(DEBUG) std::cout << "Kein Schnittpunkt mit rechter Seitenflaeche." << std::endl;
            }
	     } catch(...) {
           if(DEBUG) std::cout << "Kein Schnittpunkt mit rechter Ebene." << std::endl;
       }

  try {
            Punkt unten = schnittpunktUnten(a,b);
            if(DEBUG) std::cout << "Schnittpunkt mit unterer Ebene ist: " << unten << std::endl;
            if((unten.x() >= - breite / 2 && unten.x() <= breite / 2) && (unten.y() >= - laenge / 2 && unten.y() <= laenge / 2)) {
                if(DEBUG) std::cout << "Schnittpunkt mit unterer Seitenflaeche ist: " << unten << std::endl;
                if(between(a, b, unten)) {
                  return unten;
                } else if (DEBUG) {
                  std::cout << "Schnittpunkt mit unterer Seitenflaeche nicht zwischen den Punkten." << std::endl;
              }
          } else if(DEBUG) {
            if(DEBUG) std::cout << "Kein Schnittpunkt mit unterer Seitenflaeche." << std::endl;
          }
      } catch(...) {
          if(DEBUG) std::cout << "Kein Schnittpunkt mit unterer Ebene." << std::endl;
        }
	//Vorne:

  try {
          Punkt vorne = schnittpunktVorne(a, b);
          if(DEBUG) std::cout << "Schnittpunkt mit vorderer Ebene ist: " << vorne << std::endl;
	         if((vorne.y() >= - laenge / 2 && vorne.y() <= laenge / 2) && (vorne.z() >= - hoehe && vorne.z()<= 0 )) {
                if(DEBUG) std::cout << "Schnittpunkt mit vorderer Seitenflaeche ist: " << vorne << std::endl;
                if(between(a, b, vorne)) {
                  return vorne;
                } else if (DEBUG) {
                  std::cout << "Schnittpunkt mit vorderer Seitenflaeche nicht zwischen den Punkten." << std::endl;
                }
        } else if(DEBUG) {
          if(DEBUG) std::cout << "Kein Schnittpunkt mit vorderer Seitenflaeche." << std::endl;
        }
      } catch(...) {
          if(DEBUG) std::cout << "Kein Schnittpunkt mit vorderer Ebene." << std::endl;
        }
	//Hinten:

  try {
          Punkt hinten = schnittpunktHinten(a, b);
          if(DEBUG) std::cout << "Schnittpunkt mit hinterer Ebene ist: " << hinten << std::endl;
	        if((hinten.y() >= - laenge / 2 && hinten.y() <= laenge / 2) && (hinten.z() >= - hoehe && hinten.z()<= 0 )) {
                if(DEBUG) std::cout << "Schnittpunkt mit hinterer Seitenflaeche ist: " << hinten << std::endl;
                if(between(a, b, hinten)) {
                  return hinten;
                } else if (DEBUG) {
                  std::cout << "Schnittpunkt mit hinterer Seitenflaeche nicht zwischen den Punkten." << std::endl;
            }
        } else if(DEBUG) {
          if(DEBUG) std::cout << "Kein Schnittpunkt mit hinterer Seitenflaeche." << std::endl;
        }
      } catch(...) {
          if(DEBUG) std::cout << "Kein Schnittpunkt mit hinterer Ebene." << std::endl;
        }

        throw std::runtime_error("Kein Schnittpunkt");
    };
private:
    double breite;
    double hoehe;
    double laenge;
};


// Hauptfunktion, die aufgerufen wird, wenn man das Programm startet:
// Muss einmal (exakt einmal!) exitstieren!
int main() {

    // Lasst uns ein Implant definieren ("Wir erzeugen ein Objekt der Klasse Implant")
    Implant meins(4, 4, 4);

    // Siehe oben - nur mit Punkten...
    // Hier wird immer der "Konstruktor" der Klasse aufgerufen!
    Punkt eins(0, 1, -2);
    Punkt zwei(3, -3, -2);

    // Versuche mal folgendes...
    try {
        Punkt schnitt = meins.schnittpunkt(eins, zwei);

        std::cout << "Schnittpunkt: " << schnitt.x() << ", " << schnitt.y() << ", " << schnitt.z() << std::endl;

        // Gib dem Terminal eine Null zurueck: "Alles klar, keine Probleme gehabt!"
        return 0;

    } catch(std::runtime_error& e) {
        // ...wenn's schief geht, dann drucke das hier:
        std::cout << "Problem: " << e.what() << std::endl;
    }

    // Das ging in die Hose, sag das mal nach oben weiter:
    return 1;
}
