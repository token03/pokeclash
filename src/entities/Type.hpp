#pragma once

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
  Fairy
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

private:
  TypeChecker() {
    typeMatchups[Type::Fire] = {
        {Type::Grass, 2.0f}, {Type::Water, 0.5f}, {Type::Fire, 0.5f},
        // ...
    };

    typeMatchups[Type::Water] = {
        {Type::Fire, 2.0f}, {Type::Water, 0.5f}, {Type::Grass, 0.5f},
        // ...
    };
  }

  std::unordered_map<Type, std::unordered_map<Type, float>> typeMatchups;

  TypeChecker(TypeChecker const &) = delete;
  void operator=(TypeChecker const &) = delete;
};
