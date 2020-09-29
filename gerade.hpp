#pragma once
#include "Punkt.hpp"

class Gerade {

public:
  //Das ist eine Gerade
  Gerade(Punkt a, Punkt b) {
    // Die Dinger gibt es auch ausserhalb der Klammer, a und b nicht.
    a_ = a;
    u_ = (b - a);

  }
//Du bist auf der Geraden. Der Punkt wird ausgespuckt und t wird rein gegeben.
  Punkt at(double t) {
    return (a_ + t * u_);
  }

  // So berechnet man den Schnittpunkt mit einer ebene, die nur einen X-Wert hat.
  Punkt SchnittEbeneYZ(double x) {
      // gucke ob die Gerade Parallel zu der Ebene ist.
      if(u_.x() == 0) {
        throw std::runtime_error("Gerade parallel zu YZ-Ebene");
      }

      double t = a_.x() - x / u_.x();
      return Punkt(x, a_.y() + t * u_.y(), a_.z() + t * u_.z());
  };

  // So berechnet man den Schnittpunkt mit einer ebene, die nur einen Y-Wert hat.
  Punkt SchnittEbeneXZ(double y) {
      // gucke ob die Gerade Parallel zu der Ebene ist.
      if(u_.y() == 0) {
        throw std::runtime_error("Gerade parallel zu XZ-Ebene");
      }

      double t = a_.y() - y / u_.y();
      return Punkt(a_.x() + t * u_.x(), y, a_.z() + t * u_.z());
  };

  // So berechnet man den Schnittpunkt mit einer ebene, die nur einen Z-Wert hat.
  Punkt SchnittEbeneXY(double z) {
      // gucke ob die Gerade Parallel zu der Ebene ist.
      if(u_.z() == 0) {
        throw std::runtime_error("Gerade parallel zu XY-Ebene");
      }

      double t = a_.z() - z / u_.z();
      return Punkt(a_.x() + t * u_.x(), a_.y() + t * u_.y(), z);
  };


private:
  /*a_ Aufpunkt
    u_ b-a
    koennen nicht veraendert werden, die gibt es auch ausserhalb der Klammer, aber nur in der Klasse
  */
  Punkt a_;
  Punkt u_;
};
