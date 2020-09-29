#include <iostream>

#include "Punkt.hpp"

#include "gerade.hpp"

#define DEBUG 1

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
     * Hilfsfunktion um zu berechnen ob Punkt x in einer Dimension zwischen Punkten a und b liegt. Wenn das in einer stimmt, dann ist das auch in den Anderen so, da die Schnittpunkte auf der Geraden zwischen a und b liegen.
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

      // Neue Gerade!
      Gerade G(a, b);


//Versuche:
	try {
      //
	    Punkt links = G.SchnittEbeneYZ(- breite / 2);
      //Sagt wo der Schnittpunkt mit der Ebene ist. (der Punkt heisst links)(nur wenn DEBUG an ist)
      if(DEBUG) std::cout << "Schnittpunkt mit linker Ebene ist: " << links << std::endl;
      // Prueft ob der Punkt links auf der Seitenflaeche von dem Quader ist, wenn ja, dann...
	    if((links.z() >= -hoehe && links.z() <= 0) && (links.y() >= laenge / 2 && links.y() <= - laenge / 2)) {
                // sagt der wo der SChnittpunkt ist. (nur wenn DEBUG an ist)
                if(DEBUG) std::cout << "Schnittpunkt mit linker Seitenflaeche ist: " << links << std::endl;
                // Ueberpruefen, ob der Schnittpunkt wirlich zwischen a und b liegt und somit der Schnittpunkt sein kann:
                if(between(a, b, links)) {
                  //Wenn ja, dann gib links zurueck, da der der Schnittpunkt ist.
                    return links;
                    // sonst sagt der (nur wenn DEBUG an ist)
                  } else if (DEBUG) {
                    // das
                    std::cout << "Schnittpunkt mit linker Seitenflaeche nicht zwischen den Punkten." << std::endl;
                }
            // Der schnittpunkt ist nicht auf den Quader aber auf der Seitenflaeche
            } else if(DEBUG) {
                std::cout << "Kein Schnittpunkt mit linker Seitenflaeche." << std::endl;
            }
        //Wenn das nicht funktioniert,also es keinen SChnittpunktmit linker Ebene gibt, mach das:
       } catch(std::runtime_error& e) {
         // sagt was der Fehler ist (e)
          if(DEBUG) std::cout << e.what() << std::endl;
       }

  try {
       	     Punkt rechts = G.SchnittEbeneYZ(breite / 2);
             if(DEBUG) std::cout << "Schnittpunkt mit rechter Ebene ist: " << rechts << std::endl;
       	     if((rechts.z() >= -hoehe && rechts.z() <= 0) && (rechts.y() >= laenge / 2 && rechts.y() <= - laenge / 2)) {
                if(DEBUG) std::cout << "Schnittpunkt mit rechter Seitenflaeche ist: " << rechts << std::endl;
                if(between(a, b, rechts)) {
                	return rechts;
                } else if (DEBUG) {
                  std::cout << "Schnittpunkt mit rechter Seitenflaeche nicht zwischen den Punkten." << std::endl;
                }
            } else if(DEBUG) {
              std::cout << "Kein Schnittpunkt mit rechter Seitenflaeche." << std::endl;
            }
	     } catch(std::runtime_error& e) {
           if(DEBUG) std::cout << e.what() << std::endl;
       }

  try {
            Punkt unten = G.SchnittEbeneXY(-hoehe);
            if(DEBUG) std::cout << "Schnittpunkt mit unterer Ebene ist: " << unten << std::endl;
            if((unten.x() >= - breite / 2 && unten.x() <= breite / 2) && (unten.y() >= - laenge / 2 && unten.y() <= laenge / 2)) {
                if(DEBUG) std::cout << "Schnittpunkt mit unterer Seitenflaeche ist: " << unten << std::endl;
                if(between(a, b, unten)) {
                  return unten;
                } else if (DEBUG) {
                  std::cout << "Schnittpunkt mit unterer Seitenflaeche nicht zwischen den Punkten." << std::endl;
              }
          } else if(DEBUG) {
            std::cout << "Kein Schnittpunkt mit unterer Seitenflaeche." << std::endl;
          }
      } catch(std::runtime_error& e) {
          if(DEBUG) std::cout << e.what() << std::endl;
        }
	//Vorne:

  try {
          Punkt vorne = G.SchnittEbeneXZ(laenge / 2);
          if(DEBUG) std::cout << "Schnittpunkt mit vorderer Ebene ist: " << vorne << std::endl;
	         if((vorne.y() >= - laenge / 2 && vorne.y() <= laenge / 2) && (vorne.z() >= - hoehe && vorne.z()<= 0 )) {
                if(DEBUG) std::cout << "Schnittpunkt mit vorderer Seitenflaeche ist: " << vorne << std::endl;
                if(between(a, b, vorne)) {
                  return vorne;
                } else if (DEBUG) {
                  std::cout << "Schnittpunkt mit vorderer Seitenflaeche nicht zwischen den Punkten." << std::endl;
                }
        } else if(DEBUG) {
          std::cout << "Kein Schnittpunkt mit vorderer Seitenflaeche." << std::endl;
        }
      } catch(std::runtime_error& e) {
          if(DEBUG) std::cout << e.what()<< std::endl;
        }
	//Hinten:

  try {
          Punkt hinten = G.SchnittEbeneXZ(laenge / 2);
          if(DEBUG) std::cout << "Schnittpunkt mit hinterer Ebene ist: " << hinten << std::endl;
	        if((hinten.y() >= - laenge / 2 && hinten.y() <= laenge / 2) && (hinten.z() >= - hoehe && hinten.z()<= 0 )) {
                if(DEBUG) std::cout << "Schnittpunkt mit hinterer Seitenflaeche ist: " << hinten << std::endl;
                if(between(a, b, hinten)) {
                  return hinten;
                } else if (DEBUG) {
                  std::cout << "Schnittpunkt mit hinterer Seitenflaeche nicht zwischen den Punkten." << std::endl;
            }
        } else if(DEBUG) {
          std::cout << "Kein Schnittpunkt mit hinterer Seitenflaeche." << std::endl;
        }
      } catch(std::runtime_error& e) {
          if(DEBUG) std::cout << e.what()<< std::endl;
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
    Punkt zwei(1, -3, -2);
    Gerade G(eins,zwei);

    std::cout << eins << " - " << zwei << " = " << (eins - zwei) << std::endl;
    std::cout << "G(5) = " << G.at(5) << std::endl;

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
