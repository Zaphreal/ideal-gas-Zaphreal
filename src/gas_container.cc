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

    molecules_.emplace_back(position, velocity, kDefaultMoleculeColor,
                            kDefaultRadius);
  }
}


GasContainer::GasContainer(const vector<Molecule>& molecules) {

  for (const Molecule& molecule : molecules) {
    vec2 position = molecule.GetPosition();
    vec2 velocity = molecule.GetVelocity();

    if (position.x < kTopLeft.x || position.y < kTopLeft.y) {
      position = kTopLeft;
    }
    else if (position.x > kBottomRight.x || position.y > kBottomRight.y) {
      position = kBottomRight;
    }

    if (velocity.x < kMinVelocity) {
      velocity.x = kMinVelocity;
    } else if (velocity.x > kMaxVelocity) {
      velocity.x = kMaxVelocity;
    }

    if (velocity.y < kMinVelocity) {
      velocity.y = kMinVelocity;
    } else if (velocity.y > kMaxVelocity) {
      velocity.y = kMaxVelocity;
    }

    molecules_.emplace_back(position, velocity, molecule.GetColor(),
                            molecule.GetRadius());
  }
}


//==========[Getters]============

vector<Molecule> GasContainer::GetMolecules() {
  return molecules_;
}


//==========[Public Methods]===========

void GasContainer::Display() const {
  float total_vel = 0.0;
  for (const Molecule& molecule : molecules_) {
    ci::gl::color(ci::Color(molecule.GetColor()));
    ci::gl::drawSolidCircle(molecule.GetPosition(),
                            molecule.GetRadius());
    total_vel += glm::length(molecule.GetVelocity());
  }
  std::cout << "Total vel: " << total_vel << std::endl;

  ci::gl::color(ci::Color(kBorderColor));
  ci::gl::drawStrokedRect(ci::Rectf(kTopLeft,
                                    kBottomRight));
}


void GasContainer::AdvanceOneFrame() {
  for (size_t idx = 0; idx < molecules_.size(); ++idx) {
    Molecule& molecule = molecules_.at(idx);

    // Adjusts velocity for itself and any molecules this
    // molecule collided with
    HandleCollision(molecule, idx);
    // Handles possible left and right wall collisions
    HandleXMovement(molecule);
    // Handles possible top and bottom wall collisions
    HandleYMovement(molecule);
  }
}


//============[Private Methods]==============

void GasContainer::HandleCollision(Molecule& molecule, unsigned int curr_idx) {
  vec2 pos1 = molecule.GetPosition();
  vec2 vel1 = molecule.GetVelocity();
  float r1 = molecule.GetRadius();

  for (size_t idx = curr_idx + 1; idx < molecules_.size(); ++idx) {
    Molecule& molecule2 = molecules_.at(idx);
    vec2 pos2 = molecule2.GetPosition();
    vec2 vel2 = molecule2.GetVelocity();
    float r2 = molecule2.GetRadius();

    // If the molecules collide on movement
    // and are moving towards each other
    if (glm::distance(pos1, pos2) < r1 + r2 &&
        glm::dot(vel1 - vel2, pos1 - pos2) < 0) {

      float percent = GetCollisionTime(vel1, vel2,pos1,
                                       pos2, r1, r2);
      pos1 += vel1 * percent;
      pos2 += vel2 * percent;
      molecule.SetVelocity(GetCollisionVelocity(vel1, vel2,
                                                pos1, pos2));
      molecule2.SetVelocity(GetCollisionVelocity(vel2, vel1,
                                                 pos2, pos1));
    }
  }
}


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


vec2 GasContainer::GetCollisionVelocity(const vec2& v1, const vec2& v2,
                                        const vec2& x1, const vec2& x2) {
  vec2 v_diff = v1-v2;
  vec2 x_diff = x1-x2;
  return v1 - ((glm::dot(v_diff, x_diff) /
      pow(glm::length(x_diff), 2)) * (x_diff));
}


float GasContainer::GetCollisionTime(const vec2& v1, const vec2& v2,
                                      const vec2& x1, const vec2& x2,
                                      float r1, float r2) {
  // Formula
  // a * t^2 + 2b * t + c = 0
  // Where
  // a = dot product of diff of velocity with itself
  // b = dot product of diff of velocity with diff of position
  // c = dot product of diff of position with itself - (r1+r2)^2
  // Solved for t
  // Solution derived from:
  // https://stackoverflow.com/questions/43577298/
  // calculating-collision-times-between-two-circles-physics
  double a = glm::dot(v2-v1, v2-v1);
  double b = glm::dot(v2-v1, x2-x1);
  double c = glm::dot(x2-x1, x2-x1) - pow(r1 + r2, 2);

  double inside = b*b - a*c;
  if (inside < 0) {
    return 0;
  }
  auto t1 = float((-b + sqrt(inside)) / a);
  auto t2 = float((-b + sqrt(inside)) / a);

  // If collision occurred in the past, return closest to present
  if (t1 < 0 && t2 < 0) {
    return t1 > t2 ? t1 : t2;
  }
  return t1 < t2 ? t1 : t2;
}

}  // namespace idealgas
