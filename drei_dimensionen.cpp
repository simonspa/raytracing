#define DEBUG 1

#include <iostream>

#include "Punkt.hpp"

#include "gerade.hpp"

#include "implant.hpp"


// Hauptfunktion, die aufgerufen wird, wenn man das Programm startet:
// Muss einmal (exakt einmal!) exitstieren!
int main() {

    // Lasst uns ein Implant definieren ("Wir erzeugen ein Objekt der Klasse Implant")
    Implant meins( 4, 4, 4);

    // Siehe oben - nur mit Punkten...
    // Hier wird immer der "Konstruktor" der Klasse aufgerufen!
    Punkt eins(1, -1, -2.5);
    Punkt zwei(2, 4, -2.5);
    Gerade G(eins,zwei);

    std::cout << eins << " - " << zwei << " = " << (eins - zwei) << std::endl;
    std::cout << "G(5) = " << G.at(5) << std::endl;

    // Versuche mal folgendes...
    try {
        Punkt schnitt = meins.schnittpunkt(eins, zwei);

        std::cout << "Schnittpunkt: " << schnitt.x() << ", " << schnitt.y() << ", " << schnitt.z() << std::endl;

        if (G.enthaelt(schnitt)){
          std::cout << "Test lief schief" << std::endl;
        }
        else{
          std::cout << "Test hat geklappt" << std::endl;
        }
        // Gib dem Terminal eine Null zurueck: "Alles klar, keine Probleme gehabt!"
        return 0;

    } catch(std::runtime_error& e) {
        // ...wenn's schief geht, dann drucke das hier:
        std::cout << "Problem: " << e.what() << std::endl;
    }



    // Das ging in die Hose, sag das mal nach oben weiter:
    return 1;
}
