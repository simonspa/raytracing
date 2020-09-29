#pragma once
#include "Punkt.hpp"

class Gerade {

public:
  Gerade(Punkt a, Punkt b) {
    a_ = a;
    u_ = (b - a);

  }

  Punkt at(double t) {
    return (a_ + t * u_);
  }

  Punkt SchnittEbeneYZ(double x) {
      if(u_.x() == 0) {
        throw std::runtime_error("Gerade parallel zu YZ-Ebene");
      }

      double t = a_.x() - x / u_.x();
      return Punkt(x, a_.y() + t * u_.y(), a_.z() + t * u_.z());
  };

  Punkt SchnittEbeneXZ(double y) {
      double t = a_.y() - y / u_.y();
      return Punkt(a_.x() + t * u_.x(), y, a_.z() + t * u_.z());
  };

  Punkt SchnittEbeneXY(double z) {
      double t = a_.z() - z / u_.z();
      return Punkt(a_.x() + t * u_.x(), a_.y() + t * u_.y(), z);
  };


private:
  Punkt a_;
  Punkt u_;
};
