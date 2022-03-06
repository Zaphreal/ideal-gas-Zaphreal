#include "molecule.h"

namespace idealgas {

  Molecule::Molecule(const vec2& position, const vec2& velocity) :
      position_(position), velocity_(velocity), kColor(kDefaultColor),
      kRadius(kDefaultRadius) {}

  Molecule::Molecule(const vec2& position, const vec2& velocity,
      const ci::Color& color, float radius) : position_(position),
      velocity_(velocity), kColor(color), kRadius(radius) {}

  Molecule::Molecule(const Molecule& molecule) :
      position_(molecule.GetPosition()), velocity_(molecule.GetVelocity()),
      kColor(molecule.GetColor()), kRadius(molecule.GetRadius()){}


  //==============[Getters]=================

  vec2 Molecule::GetPosition() const {
    return position_;
  }

  vec2 Molecule::GetVelocity() const {
    return velocity_;
  }

  ci::Color Molecule::GetColor() const {
    return kColor;
  }

  float Molecule::GetRadius() const {
    return kRadius;
  }

  //==============[Setters]=================


  void Molecule::SetPosition(const vec2& position) {
    position_ = position;
  }

  void Molecule::SetVelocity(const vec2& velocity) {
    velocity_ = velocity;
  }

}

