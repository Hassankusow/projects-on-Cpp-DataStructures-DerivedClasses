// this is my cards header file where i create my weapons name discription type combat style
// a the power level of the card by random

#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
#include <random> // this is for calculating my power level

// Enum for Rarity of weapons
enum class Rarity { Common, Rare, Legendary };

// Enum for Weapon types
enum class WeaponType { Sword, Bow, Spear };

// Enum for Combat types
enum class CombatType { Melee, Ranged };
// card class
class Card {
public: 
    Card();
    Card(const std::string& name, const std::string& description);
    Card(const Card& other);
    Card& operator=(const Card& other);
    bool operator==(const Card& other) const;
    bool operator!=(const Card& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Card& card);
    friend std::istream& operator>>(std::istream& is, Card& card);

    void createCard();

    const std::string& getName() const;
    const std::string& getDescription() const;
    int getPoints() const;
    void setPoints(int newPoints);
    void setName(const std::string& name);
    void setDescription(const std::string& description);

protected:
    std::string name;
    std::string description;
    int points;
};
// weapons type and rarity  class
class Weapon : public Card {
public:
    Weapon(const std::string& name, const std::string& description, WeaponType type, Rarity rarity);
    WeaponType getType() const { return type; }
    Rarity getRarity() const { return rarity; }
    int calculate_points() const;

private:
    WeaponType type;
    Rarity rarity;
    int attackStrength;
};

// cards combat style class
class Combat : public Card {
public:
    Combat(const std::string& name, const std::string& description, CombatType type, WeaponType weaponType);
    CombatType getCombatType() const { return type; }
    WeaponType getWeaponType() const { return weaponType; }
    int calculateCombatPoints() const;

private:
    CombatType type;
    WeaponType weaponType;
};
// power level and duration by random class
class Power : public Card {
public:
    Power(const std::string& name, const std::string& description, int duration);
    int getPowerLevel() const { return powerLevel; }
    int getDuration() const { return duration; }
    double calculatePowerEffect() const;

private:
    int powerLevel;
    int duration;
};

#endif // CARD_H

