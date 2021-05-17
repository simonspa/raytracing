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
    bool between(point a, point b, point x) const {
        return (x.y() <= a.y() && x.y() >= b.y()) || (x.y() >= a.y() && x.y() <= b.y());
    };

    /**
     * Funktion zur Bestimmung des Schnittpunks der Verbindungslinie zweier Punkte mit dem Implant:
     * @param  a Ein Punkt ausserhalb
     * @param  b Ein Punkt innheralb
     * @return   Schnittpunkt
     * @throws runtime_error wenn kein Schnittpunkt gefunden werden kann
     */
    point schnittpunkt(point a, point b) const {

      // Neue Gerade!
      Gerade G(a, b);


//Versuche:
	try {
      //
	    point links = G.SchnittEbeneYZ(- breite / 2);
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
       	     point rechts = G.SchnittEbeneYZ(breite / 2);
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
            point unten = G.SchnittEbeneXY(-hoehe);
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
          point vorne = G.SchnittEbeneXZ(laenge / 2);
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
          point hinten = G.SchnittEbeneXZ(-laenge / 2);
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
