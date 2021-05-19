#pragma once
#include "Punkt.hpp"

class Gerade {

public:
  //Das ist eine Gerade
  Gerade(point a, point b) {
    // Die Dinger gibt es auch ausserhalb der Klammer, a und b nicht.
    a_ = a;
    u_ = (b - a);

  }
//Du bist auf der Geraden. Der Punkt wird ausgespuckt und t wird rein gegeben.
  point at(double t) {
    return (a_ + t * u_);
  }

  // So berechnet man den Schnittpunkt mit einer ebene, die nur einen X-Wert hat.
  point SchnittEbeneYZ(double x) {
      // gucke ob die Gerade Parallel zu der Ebene ist.
      if(u_.x() == 0) {
        throw std::runtime_error("Gerade parallel zu YZ-Ebene");
      }

      double t = (x - a_.x()) / u_.x();
      return at(t);
  };

  // So berechnet man den Schnittpunkt mit einer ebene, die nur einen Y-Wert hat.
  point SchnittEbeneXZ(double y) {
      // gucke ob die Gerade Parallel zu der Ebene ist.
      if(u_.y() == 0) {
        throw std::runtime_error("Gerade parallel zu XZ-Ebene");
      }

      double t = (y - a_.y()) / u_.y();
      return at(t);
  };

  // So berechnet man den Schnittpunkt mit einer ebene, die nur einen Z-Wert hat.
  point SchnittEbeneXY(double z) {
      // gucke ob die Gerade Parallel zu der Ebene ist.
      if(u_.z() == 0) {
        throw std::runtime_error("Gerade parallel zu XY-Ebene");
      }

      double t = (z - a_.z()) / u_.z();
      return at(t);
  };


private:
  /*a_ Aufpunkt
    u_ b-a
    koennen nicht veraendert werden, die gibt es auch ausserhalb der Klammer, aber nur in der Klasse
  */
  point a_;
  point u_;
};
