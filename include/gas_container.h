#pragma once

#include <random>
#include "cinder/gl/gl.h"
#include "molecule.h"

using glm::vec2;
using std::vector;
using std::string;

namespace idealgas {

/**
 * The container in which all of the gas particles are contained. This class
 * stores all of the particles and updates them on each frame of the simulation.
 */
class GasContainer {
 public:
  constexpr static size_t kInitNumMolecules = 15;
  constexpr static float kDefaultRadius = 10.0;
  constexpr static float kMinVelocity = -3.0;
  constexpr static float kMaxVelocity = 3.0;

  const vec2 kTopLeft = vec2(100, 100);
  const vec2 kBottomRight = vec2(600, 400);
  const ci::Color kDefaultMoleculeColor = "orange";
  const ci::Color kBorderColor = "white";

  //=========[Constructors]========

  /**
   * Creates a default GasContainer
   */
  GasContainer();

  /**
   * Displays the container walls and the current positions of the particles.
   */
  void Display() const;

  /**
   * Updates the positions and velocities of all particles (based on the rules
   * described in the assignment documentation).
   */
  void AdvanceOneFrame();

 private:
  vector<Molecule> molecules_;

  /**
   * Adjusts the X position of a molecule according to its velocity
   * and container walls
   * @param molecule the Molecule to handle movement for
   */
  void HandleXMovement(Molecule& molecule) const;

  /**
   * Adjusts the Y position of a molecule according to its velocity
   * and container walls
   * @param molecule the Molecule to handle movement for
   */
  void HandleYMovement(Molecule& molecule) const;

  /**
   * Gives a pseudo-random vec2 between the upper and lower bounds
   *
   * @param lower_bound a vec2 containing lower bound coords
   * @param upper_bound a vec2 containing upper bound coords
   * @return a pseudo-random vec2 between the provided bounds
   */
  static vec2 GetRandomVec2(const vec2& lower_bound, const vec2& upper_bound);

};

}  // namespace idealgas
