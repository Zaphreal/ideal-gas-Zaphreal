#include <catch2/catch.hpp>

#include <gas_container.h>

using idealgas::GasContainer;
using idealgas::Molecule;

TEST_CASE("Molecule creation") {

  SECTION("Basic molecule") {
    vec2 position(10);
    vec2 velocity(5);
    ci::Color expected_color = "orange";
    float expected_radius = 10.0f;
    Molecule molecule(position, velocity);

    SECTION("Test position and velocity stored correctly") {
      REQUIRE(position == molecule.GetPosition());
      REQUIRE(velocity == molecule.GetVelocity());
    }

    SECTION("Assert used default radius and color") {
      REQUIRE(expected_color == molecule.GetColor());
      REQUIRE(expected_radius == molecule.GetRadius());
    }
  }

  SECTION("Complex molecule") {
    vec2 position(-132.19052, 23129.3234);
    vec2 velocity(32.846, -203.001);
    ci::Color color = "purple";
    float radius = 31.83f;
    Molecule molecule(position, velocity, color, radius);

    SECTION("Test variables initialized correctly") {
      REQUIRE(position == molecule.GetPosition());
      REQUIRE(velocity == molecule.GetVelocity());
      REQUIRE(color == molecule.GetColor());
      REQUIRE(radius == molecule.GetRadius());
    }
  }
}


TEST_CASE("Changing molecule position") {

  vec2 position(10);
  vec2 velocity(5);
  Molecule molecule(position, velocity);

  REQUIRE(position == molecule.GetPosition());

  vec2 expected(15);
  molecule.SetPosition(expected);

  REQUIRE(expected == molecule.GetPosition());
  REQUIRE(velocity == molecule.GetVelocity());
}


TEST_CASE("Changing molecule velocity") {

  vec2 position(10);
  vec2 velocity(5);
  Molecule molecule(position, velocity);

  REQUIRE(velocity == molecule.GetVelocity());

  vec2 expected(-5, 5);
  molecule.SetVelocity(expected);

  REQUIRE(expected == molecule.GetVelocity());
  REQUIRE(position == molecule.GetPosition());
}

