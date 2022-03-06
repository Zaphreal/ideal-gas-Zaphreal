#pragma once

#include "cinder/gl/gl.h"

using glm::vec2;
using std::vector;
using std::string;

namespace idealgas {

class Molecule {
  public:

    /**
     * Builds a molecule from a given position and velocity, using the
     * default color and radius
     *
     * @param position the vec2 representing the position of the molecule
     * @param velocity the vec2 representing the velocity of the molecule
     */
    Molecule(const vec2& position, const vec2& velocity);

    /**
     * Builds a molecule from a given position, velocity, color, and radius
     *
     * @param position the vec2 representing the position of the molecule
     * @param velocity the vec2 representing the velocity of the molecule
     * @param radius the radius of the molecule
     * @param color the color of the molecule
     */
    Molecule(const vec2 &position, const vec2& velocity, const ci::Color& color,
             float radius);

    /**
     * Copy constructor
     *
     * @param molecule the molecule to copy
     */
    Molecule(const Molecule& molecule);

    //========[Getters]========

    vec2 GetPosition() const;
    vec2 GetVelocity() const;
    ci::Color GetColor() const;
    float GetRadius() const;

    //========[Setters]========

    void SetPosition(const vec2& position);
    void SetVelocity(const vec2& velocity);

  private:
    const ci::Color kDefaultColor = "orange";
    const ci::Color kColor;
    const float kDefaultRadius = 10.0;
    const float kRadius;

    vec2 position_;
    vec2 velocity_;
};

} // namespace idealgas
