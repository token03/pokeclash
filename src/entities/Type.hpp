#pragma once
#include <pugixml.hpp>
#include <string>
#include <unordered_map>

enum class Type {
  Normal,
  Fire,
  Water,
  Grass,
  Electric,
  Ice,
  Fighting,
  Poison,
  Ground,
  Flying,
  Psychic,
  Bug,
  Rock,
  Ghost,
  Dragon,
  Dark,
  Steel,
  Fairy,
  None,
};

class TypeChecker {
public:
  static TypeChecker &getInstance() {
    static TypeChecker instance;
    return instance;
  }

  float getMultiplier(Type attacker, Type defender) {
    if (typeMatchups[attacker].count(defender) > 0)
      return typeMatchups[attacker][defender];
    else
      return 1.0f;
  }

  float getMultiplier(Type attacker1, Type attacker2, Type defender) {
    float multiplier1 = getMultiplier(attacker1, defender);
    float multiplier2 = getMultiplier(attacker2, defender);

    return multiplier1 * multiplier2;
  }

  static Type mapStringToType(const std::string &typeName) {
    if (typeName == "Normal")
      return Type::Normal;
    else if (typeName == "Fire")
      return Type::Fire;
    else if (typeName == "Water")
      return Type::Water;
    else if (typeName == "Grass")
      return Type::Grass;
    else if (typeName == "Electric")
      return Type::Electric;
    else if (typeName == "Ice")
      return Type::Ice;
    else if (typeName == "Fighting")
      return Type::Fighting;
    else if (typeName == "Poison")
      return Type::Poison;
    else if (typeName == "Ground")
      return Type::Ground;
    else if (typeName == "Flying")
      return Type::Flying;
    else if (typeName == "Psychic")
      return Type::Psychic;
    else if (typeName == "Bug")
      return Type::Bug;
    else if (typeName == "Rock")
      return Type::Rock;
    else if (typeName == "Ghost")
      return Type::Ghost;
    else if (typeName == "Dragon")
      return Type::Dragon;
    else if (typeName == "Dark")
      return Type::Dark;
    else if (typeName == "Steel")
      return Type::Steel;
    else if (typeName == "Fairy")
      return Type::Fairy;
    else if (typeName == "")
      return Type::None;
    else
      throw std::runtime_error("Invalid type name: " + typeName);
  }

private:
  TypeChecker() { loadTypeMatchup("../src/data/Types.xml"); }

  void loadTypeMatchup(const std::string &filename) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(filename.c_str());

    if (!result) {
      throw std::runtime_error("Failed to load XML file: " + filename);
    }

    pugi::xml_node typeMatchupsNode = doc.child("TypeMatchups");
    for (pugi::xml_node typeNode : typeMatchupsNode.children("Type")) {
      Type type = mapStringToType(typeNode.attribute("name").value());
      for (pugi::xml_node effectivenessNode :
           typeNode.children("Effectiveness")) {
        Type against =
            mapStringToType(effectivenessNode.attribute("against").value());
        float effectiveness =
            std::stof(effectivenessNode.attribute("value").value());
        typeMatchups[type][against] = effectiveness;
      }
    }
  }

  std::unordered_map<Type, std::unordered_map<Type, float>> typeMatchups;
  TypeChecker(TypeChecker const &) = delete;
  void operator=(TypeChecker const &) = delete;
};
