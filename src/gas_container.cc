#include "gas_container.h"

namespace idealgas {

using glm::vec2;


GasContainer::GasContainer() {
  vec2 radius_vec(kDefaultRadius);

  for (unsigned int count = 0; count < kInitNumMolecules; ++count) {
    vec2 position = GetRandomVec2(kTopLeft + radius_vec,
                                  kBottomRight - radius_vec);
    vec2 velocity = GetRandomVec2(vec2(kMinVelocity),
                                  vec2(kMaxVelocity));

}

void GasContainer::Display() const {
  for (const Molecule& molecule : molecules_) {
    ci::gl::color(ci::Color(molecule.GetColor()));
    ci::gl::drawSolidCircle(molecule.GetPosition(),
                            molecule.GetRadius());
  }

  ci::gl::color(ci::Color(kBorderColor));
  ci::gl::drawStrokedRect(ci::Rectf(kTopLeft,
                                    kBottomRight));
}


void GasContainer::AdvanceOneFrame() {
  for (size_t idx = 0; idx < molecules_.size(); ++idx) {
    Molecule& molecule = molecules_.at(idx);

    // Handles possible left and right wall collisions
    HandleXMovement(molecule);
    // Handles possible top and bottom wall collisions
    HandleYMovement(molecule);
  }
}


//============[Private Methods]==============


void GasContainer::HandleXMovement(Molecule& molecule) const {
  vec2 pos = molecule.GetPosition();
  vec2 vel = molecule.GetVelocity();
  float radius = molecule.GetRadius();

  // No wall collision
  if (pos.x + vel.x - radius > kTopLeft.x &&
      pos.x + vel.x + radius < kBottomRight.x) {

    pos.x += vel.x;
  } else {
    // Left wall collision
    if (pos.x + vel.x - radius <= kTopLeft.x) {
      pos.x = kTopLeft.x + (kTopLeft.x - (pos.x + vel.x - radius)) + radius;
    }
    // Right wall collision
    else {
      pos.x = kBottomRight.x + (kBottomRight.x - (pos.x + vel.x + radius) -
          radius);
    }
    vel.x *= -1;
    molecule.SetVelocity(vel);
  }
  molecule.SetPosition(pos);
}


void GasContainer::HandleYMovement(Molecule& molecule) const {
  vec2 pos = molecule.GetPosition();
  vec2 vel = molecule.GetVelocity();
  float radius = molecule.GetRadius();

  // No wall collision
  if (pos.y + vel.y - radius > kTopLeft.y &&
      pos.y + vel.y + radius < kBottomRight.y) {

    pos.y += vel.y;
  } else {
    // Top wall collision
    if (pos.y + vel.y - radius <= kTopLeft.y) {
      pos.y = kTopLeft.y + (kTopLeft.y - (pos.y + vel.y - radius)) + radius;
    }
    // Bottom wall collision
    else {
      pos.y = kBottomRight.y + (kBottomRight.y - (pos.y + vel.y + radius)) -
          radius;
    }
    vel.y *= -1;
    molecule.SetVelocity(vel);
  }
  molecule.SetPosition(pos);
}


vec2 GasContainer::GetRandomVec2(const vec2& lower_bound, const vec2&
                                 upper_bound) {
  // RNG code obtained from
  // https://stackoverflow.com/questions/7560114/random-number-c-in-some-range
  std::random_device rd;          // obtain a random number from hardware
  std::mt19937 gen(rd());     // seed the generator
  std::uniform_real_distribution<> distr_x(lower_bound.x,
                                           upper_bound.x);
  std::uniform_real_distribution<> distr_y(lower_bound.y,
                                           upper_bound.y);

  return {distr_x(gen), distr_y(gen)};
}


}  // namespace idealgas
