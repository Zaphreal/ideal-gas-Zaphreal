#include <catch2/catch.hpp>

#include <gas_container.h>

using idealgas::GasContainer;
using idealgas::Molecule;

TEST_CASE("Gas container construction") {
  GasContainer container;

  REQUIRE(container.kInitNumMolecules == container.GetMolecules().size());

  SECTION("Assert all molecules have default radius and color") {
    for (const Molecule& molecule : container.GetMolecules()) {
      REQUIRE(container.kDefaultRadius == molecule.GetRadius());
      REQUIRE(container.kDefaultMoleculeColor == molecule.GetColor());
    }
  }

  SECTION("Assert molecule positions are within default borders") {
    for (const Molecule& molecule : container.GetMolecules()) {
      vec2 position = molecule.GetPosition();
      REQUIRE(container.kTopLeft.x <= position.x);
      REQUIRE(container.kTopLeft.y <= position.y);
      REQUIRE(container.kBottomRight.x >= position.x);
      REQUIRE(container.kBottomRight.y >= position.y);
    }
  }

  SECTION("Assert molecule velocities are within default limits") {
    for (const Molecule& molecule : container.GetMolecules()) {
      vec2 velocity = molecule.GetVelocity();
      REQUIRE(container.kMinVelocity <= velocity.x);
      REQUIRE(container.kMinVelocity <= velocity.y);
      REQUIRE(container.kMaxVelocity >= velocity.x);
      REQUIRE(container.kMaxVelocity >= velocity.y);
    }
  }
}


TEST_CASE("1 molecule: No collisions") {
  vec2 position(150, 150);

  SECTION("AdvanceOneFrame: 1d velocity vectors") {
    SECTION("+x velocity") {
      vec2 velocity(1, 0);
      Molecule init_mol(position, velocity);
      GasContainer container(vector<Molecule>{init_mol});

      container.AdvanceOneFrame();

      vec2 expected = position + velocity;
      Molecule mol_after = container.GetMolecules().at(0);

      REQUIRE(expected == mol_after.GetPosition());
    }

    SECTION("-x velocity") {
      vec2 velocity(-1, 0);
      Molecule init_mol(position, velocity);
      GasContainer container(vector<Molecule>{init_mol});

      container.AdvanceOneFrame();

      vec2 expected = position + velocity;
      Molecule mol_after = container.GetMolecules().at(0);

      REQUIRE(expected == mol_after.GetPosition());
    }

    SECTION("+y velocity") {
      vec2 velocity(0, 1);
      Molecule init_mol(position, velocity);
      GasContainer container(vector<Molecule>{init_mol});

      container.AdvanceOneFrame();

      vec2 expected = position + velocity;
      Molecule mol_after = container.GetMolecules().at(0);

      REQUIRE(expected == mol_after.GetPosition());
    }

    SECTION("-y velocity") {
      vec2 velocity(0, -1);
      Molecule init_mol(position, velocity);
      GasContainer container(vector<Molecule>{init_mol});

      container.AdvanceOneFrame();

      vec2 expected = position + velocity;
      Molecule mol_after = container.GetMolecules().at(0);

      REQUIRE(expected == mol_after.GetPosition());
    }
  }


  SECTION("AdvanceOneFrame: 2d velocity vectors") {
    SECTION("(+x, +y) velocity") {
      vec2 velocity(1, 1);
      Molecule init_mol(position, velocity);
      GasContainer container(vector<Molecule>{init_mol});

      container.AdvanceOneFrame();

      vec2 expected = position + velocity;
      Molecule mol_after = container.GetMolecules().at(0);

      REQUIRE(expected == mol_after.GetPosition());
    }

    SECTION("(+x, -y) velocity") {
      vec2 velocity(1, -1);
      Molecule init_mol(position, velocity);
      GasContainer container(vector<Molecule>{init_mol});

      container.AdvanceOneFrame();

      vec2 expected = position + velocity;
      Molecule mol_after = container.GetMolecules().at(0);

      REQUIRE(expected == mol_after.GetPosition());
    }

    SECTION("(-x, y) velocity") {
      vec2 velocity(-1, 1);
      Molecule init_mol(position, velocity);
      GasContainer container(vector<Molecule>{init_mol});

      container.AdvanceOneFrame();

      vec2 expected = position + velocity;
      Molecule mol_after = container.GetMolecules().at(0);

      REQUIRE(expected == mol_after.GetPosition());
    }

    SECTION("(-x, -y) velocity") {
      vec2 velocity(-1, -1);
      Molecule init_mol(position, velocity);
      GasContainer container(vector<Molecule>{init_mol});

      container.AdvanceOneFrame();

      vec2 expected = position + velocity;
      Molecule mol_after = container.GetMolecules().at(0);

      REQUIRE(expected == mol_after.GetPosition());
    }
  }
}
