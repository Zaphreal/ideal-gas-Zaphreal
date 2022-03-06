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


TEST_CASE("1 molecule: 1d movement") {
  vec2 position(150, 150);

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


TEST_CASE("1 molecule: 2d movement") {
  vec2 position(150, 150);

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


TEST_CASE("1 molecule: direct wall collisions") {

  SECTION("AdvanceOneFrame: x wall collision") {
    SECTION("Lower x boundary") {
      vec2 position(110, 150);
      vec2 velocity(-3, 0);
      Molecule init_mol(position, velocity, "orange", 10);
      GasContainer container(vector<Molecule>{init_mol});

      container.AdvanceOneFrame();

      vec2 exp_pos(113, 150);
      vec2 exp_vel(3, 0);
      Molecule mol_after = container.GetMolecules().at(0);

      REQUIRE(exp_pos == mol_after.GetPosition());
      REQUIRE(exp_vel == mol_after.GetVelocity());
    }

    SECTION("Upper x boundary") {
      vec2 position(590, 150);
      vec2 velocity(2, 0);
      Molecule init_mol(position, velocity, "orange", 10);
      GasContainer container(vector<Molecule>{init_mol});

      container.AdvanceOneFrame();

      vec2 exp_pos(588, 150);
      vec2 exp_vel(-2, 0);
      Molecule mol_after = container.GetMolecules().at(0);

      REQUIRE(exp_pos == mol_after.GetPosition());
      REQUIRE(exp_vel == mol_after.GetVelocity());
    }
  }

  SECTION("AdvanceOneFrame: y wall collision") {
    SECTION("Lower y boundary") {
      vec2 position(150, 110);
      vec2 velocity(0, -1);
      Molecule init_mol(position, velocity, "orange", 10);
      GasContainer container(vector<Molecule>{init_mol});

      container.AdvanceOneFrame();

      vec2 exp_pos(150, 111);
      vec2 exp_vel(0, 1);
      Molecule mol_after = container.GetMolecules().at(0);

      REQUIRE(exp_pos == mol_after.GetPosition());
      REQUIRE(exp_vel == mol_after.GetVelocity());
    }

    SECTION("Upper y boundary") {
      vec2 position(150, 390);
      vec2 velocity(0, 2.5);
      Molecule init_mol(position, velocity, "orange", 10);
      GasContainer container(vector<Molecule>{init_mol});

      container.AdvanceOneFrame();

      vec2 exp_pos(150, 387.5);
      vec2 exp_vel(0, -2.5);
      Molecule mol_after = container.GetMolecules().at(0);

      REQUIRE(exp_pos == mol_after.GetPosition());
      REQUIRE(exp_vel == mol_after.GetVelocity());
    }
  }
}


TEST_CASE("1 molecule: angled wall collisions") {

  SECTION("AdvanceOneFrame: x angled wall collision") {
    SECTION("Lower x boundary") {
      vec2 position(110, 150);
      vec2 velocity(-3, -2);
      Molecule init_mol(position, velocity, "orange", 10);
      GasContainer container(vector<Molecule>{init_mol});

      container.AdvanceOneFrame();

      vec2 exp_pos(113, 148);
      vec2 exp_vel(3, -2);
      Molecule mol_after = container.GetMolecules().at(0);

      REQUIRE(exp_pos == mol_after.GetPosition());
      REQUIRE(exp_vel == mol_after.GetVelocity());
    }

    SECTION("Upper x boundary") {
      vec2 position(590, 150);
      vec2 velocity(2, -1.5);
      Molecule init_mol(position, velocity, "orange", 10);
      GasContainer container(vector<Molecule>{init_mol});

      container.AdvanceOneFrame();

      vec2 exp_pos(588, 148.5);
      vec2 exp_vel(-2, -1.5);
      Molecule mol_after = container.GetMolecules().at(0);

      REQUIRE(exp_pos == mol_after.GetPosition());
      REQUIRE(exp_vel == mol_after.GetVelocity());
    }
  }

  SECTION("AdvanceOneFrame: y angled wall collision") {
    SECTION("Lower y boundary") {
      vec2 position(150, 110);
      vec2 velocity(2.5, -1);
      Molecule init_mol(position, velocity, "orange", 10);
      GasContainer container(vector<Molecule>{init_mol});

      container.AdvanceOneFrame();

      vec2 exp_pos(152.5, 111);
      vec2 exp_vel(2.5, 1);
      Molecule mol_after = container.GetMolecules().at(0);

      REQUIRE(exp_pos == mol_after.GetPosition());
      REQUIRE(exp_vel == mol_after.GetVelocity());
    }

    SECTION("Upper y boundary") {
      vec2 position(150, 390);
      vec2 velocity(-3, 2.5);
      Molecule init_mol(position, velocity, "orange", 10);
      GasContainer container(vector<Molecule>{init_mol});

      container.AdvanceOneFrame();

      vec2 exp_pos(147, 387.5);
      vec2 exp_vel(-3, -2.5);
      Molecule mol_after = container.GetMolecules().at(0);

      REQUIRE(exp_pos == mol_after.GetPosition());
      REQUIRE(exp_vel == mol_after.GetVelocity());
    }
  }
}


TEST_CASE("1 molecule: corner collisions") {

  SECTION("(Lower x, Lower y) corner") {
    vec2 position(110, 110);
    vec2 velocity(-3, -2);
    Molecule init_mol(position, velocity, "orange", 10);
    GasContainer container(vector<Molecule>{init_mol});

    container.AdvanceOneFrame();

    vec2 exp_pos(113, 112);
    vec2 exp_vel(3, 2);
    Molecule mol_after = container.GetMolecules().at(0);

    REQUIRE(exp_pos == mol_after.GetPosition());
    REQUIRE(exp_vel == mol_after.GetVelocity());
  }

  SECTION("(Lower x, Upper y) corner") {
    vec2 position(110, 390);
    vec2 velocity(-2, 1.5);
    Molecule init_mol(position, velocity, "orange", 10);
    GasContainer container(vector<Molecule>{init_mol});

    container.AdvanceOneFrame();

    vec2 exp_pos(112, 388.5);
    vec2 exp_vel(2, -1.5);
    Molecule mol_after = container.GetMolecules().at(0);

    REQUIRE(exp_pos == mol_after.GetPosition());
    REQUIRE(exp_vel == mol_after.GetVelocity());
  }

  SECTION("(Upper x, Lower y) corner") {
    vec2 position(590, 110);
    vec2 velocity(2.5, -1);
    Molecule init_mol(position, velocity, "orange", 10);
    GasContainer container(vector<Molecule>{init_mol});

    container.AdvanceOneFrame();

    vec2 exp_pos(587.5, 111);
    vec2 exp_vel(-2.5, 1);
    Molecule mol_after = container.GetMolecules().at(0);

    REQUIRE(exp_pos == mol_after.GetPosition());
    REQUIRE(exp_vel == mol_after.GetVelocity());
  }

  SECTION("(Upper x, Upper y) corner") {
    vec2 position(590, 390);
    vec2 velocity(3, 2.5);
    Molecule init_mol(position, velocity, "orange", 10);
    GasContainer container(vector<Molecule>{init_mol});

    container.AdvanceOneFrame();

    vec2 exp_pos(587, 387.5);
    vec2 exp_vel(-3, -2.5);
    Molecule mol_after = container.GetMolecules().at(0);

    REQUIRE(exp_pos == mol_after.GetPosition());
    REQUIRE(exp_vel == mol_after.GetVelocity());
  }
}


TEST_CASE("2 molecules: basic collision") {
  Molecule mol1(vec2(120, 120), vec2(0.1, 0),
                "red", 1);
  Molecule mol2(vec2(121.4, 121.4), vec2(-0.1, 0),
                "red", 1);

  GasContainer container(vector<Molecule>{mol1, mol2});

  container.AdvanceOneFrame();

  vec2 exp_pos1(120, 119.9);
  vec2 exp_vel1(0, -0.1);
  vec2 exp_pos2(121.4, 121.5);
  vec2 exp_vel2(0, 0.1);

  vector<Molecule> molecules = container.GetMolecules();

  REQUIRE(exp_pos1 == molecules.at(0).GetPosition());
  REQUIRE(exp_vel1 == molecules.at(0).GetVelocity());
  REQUIRE(exp_pos2 == molecules.at(1).GetPosition());
  REQUIRE(exp_vel2 == molecules.at(1).GetVelocity());
}


