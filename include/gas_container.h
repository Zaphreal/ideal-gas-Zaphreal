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
   * Creates a GasContainer from a vector of molecules. Any molecules whose
   * positions or velocities are outside of the container's limits will be
   * pushed into the container.
   *
   * @param molecules a vector of Molecules
   */
  explicit GasContainer(const vector<Molecule>& molecules);

  //==========[Getters]===========

  vector<Molecule> GetMolecules();

  //==========[Methods]===========

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
   * Adjusts the velocities of the current molecule and any molecules
   * it might collide with according to the equation of 2d elastic collisions
   *
   * @param molecule the Molecule to handle movement for
   * @param idx the molecule's index within the molecules vector
   */
  void HandleCollision(Molecule& molecule, unsigned int curr_idx);

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

  /**
   * Calculates post-collision velocity of a target molecule using 2d elastic
   * collision formula
   *
   * @param v1 velocity of target molecule
   * @param v2 velocity of collided molecule
   * @param x1 position of target molecule
   * @param x2 position of collided molecule
   * @return a vec2 of the post-collision velocity of the target molecule
   */
  static vec2 GetCollisionVelocity(const vec2& v1, const vec2& v2,
                                   const vec2& x1, const vec2& x2);

};

}  // namespace idealgas
