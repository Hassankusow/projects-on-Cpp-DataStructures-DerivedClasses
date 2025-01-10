#include "cards.h"
#include <cstdlib>
// my constructor defult and copy constructors
Card::Card() : name(""), description(""), points(0) {}
Card::Card(const std::string& name, const std::string& description) : name(name), description(description), points(0) {}
Card::Card(const Card& other) : name(other.name), description(other.description), points(other.points) {}

Card& Card::operator=(const Card& other) {
    if (this != &other) {
        name = other.name;
        description = other.description;
        points = other.points;
    }
    return *this;
}
// if it is card or not
bool Card::operator==(const Card& other) const { return name == other.name && description == other.description && points == other.points; }
bool Card::operator!=(const Card& other) const { return !(*this == other); }

// Getter for name
const std::string& Card::getName() const {
    return name;
}

// Getter for description
const std::string& Card::getDescription() const {
    return description;
}
// Getter for pionts
int Card::getPoints() const {
    return points;
}

// Setter for points
void Card::setPoints(int newPoints) {
    points = newPoints;
}
// assigment operator outnput
std::ostream& operator<<(std::ostream& os, const Card& card) {
    os << "Name: " << card.name << "\nDescription: " << card.description << "\nPoints: " << card.points;
    return os;
}
// assigment overload opertor input
std::istream& operator>>(std::istream& is, Card& card) {
    std::cout << "Enter Weapons Card name: ";
    std::getline(is, card.name);
    std::cout << "Enter Weapons Card description: ";
    std::getline(is, card.description);
    return is;
}
// this is where a create my card and calculate wepons piont level this is for main
void Card::createCard() {
    std::cin >> *this;

    Weapon weapon(name, description, WeaponType::Sword, Rarity::Rare);
    int weaponPoints = weapon.calculate_points();

    Combat combat(name, description, CombatType::Melee, weapon.getType());
    int combatPoints = combat.calculateCombatPoints();

    Power power(name, description, 5);
    double powerEffect = power.calculatePowerEffect();

    points = weaponPoints + combatPoints + static_cast<int>(powerEffect);

    std::cout << "Weapon Points: " << weaponPoints << "\n";
    std::cout << "Combat Points: " << combatPoints << "\n";
    std::cout << "Power Effect Points: " << powerEffect << "\n";
    std::cout << "Total Points: " << points << "\n";
}
// constructor for weapon derived class
Weapon::Weapon(const std::string& name, const std::string& description, WeaponType type, Rarity rarity)
    : Card(name, description), type(type), rarity(rarity) {}
// this is where i caculate the pionts for weapon rarity and type using enum class in my header file
int Weapon::calculate_points() const {
    int points = 0;

    int weapon_choice;
    std::cout << "Enter weapon type (1 for Sword, 2 for Bow, 3 for Spear): ";
    std::cin >> weapon_choice;

    WeaponType selectedType;
    switch (weapon_choice) {
        case 1:
            selectedType = WeaponType::Sword;
            points += 30;
            break;
        case 2:
            selectedType = WeaponType::Bow;
            points += 20;
            break;
        case 3:
            selectedType = WeaponType::Spear;
            points += 10;
            break;
        default:
            std::cout << "Invalid choice. Defaulting to Sword.\n";
            selectedType = WeaponType::Sword;
            points += 30;
            break;
    }
    std::cout << "Weapon type selected: " << static_cast<int>(selectedType) << "\n";

    std::cout << "Enter weapon rarity (1 for Common, 2 for Rare, 3 for Legendary): ";
    int rarity_choice;
    std::cin >> rarity_choice;

    Rarity selectedRarity;
    switch (rarity_choice) {
        case 1:
            selectedRarity = Rarity::Common;
            points += 10;
            break;
        case 2:
            selectedRarity = Rarity::Rare;
            points += 20;
            break;
        case 3:
            selectedRarity = Rarity::Legendary;
            points += 30;
            break;
        default:
            std::cout << "Invalid rarity choice. Defaulting to Common.\n";
            selectedRarity = Rarity::Common;
            points += 10;
            break;
    }
     std::cout << "Weapon rarity selected: " << static_cast<int>( selectedRarity) << "\n";
    return points;
}
// this is my constructor for my combat style weapons card
Combat::Combat(const std::string& name, const std::string& description, CombatType type, WeaponType weaponType)
    : Card(name, description), type(type), weaponType(weaponType) {}
// this is where i caculte the pionts for my combat style using enum classes in header file
int Combat::calculateCombatPoints() const {
    int combat_choice;
    std::cout << "Enter combat type (1 for Melee, 2 for Ranged): ";
    std::cin >> combat_choice;
    int points = 0;
    CombatType selectedCombatType;
    if (combat_choice == 1) {
        selectedCombatType = CombatType::Melee;
    } else {
        selectedCombatType = CombatType::Ranged;
    }
    if (selectedCombatType == CombatType::Melee) {
        if (weaponType == WeaponType::Sword) {
            points += 30;
        } else if (weaponType == WeaponType::Spear) {
            points += 20;
        } else if (weaponType == WeaponType::Bow) {
            points += 10;
        }
    } else if (selectedCombatType == CombatType::Ranged) {
        if (weaponType == WeaponType::Bow) {
            points += 30;
        } else if (weaponType == WeaponType::Spear) {
            points += 20;
        } else if (weaponType == WeaponType::Sword) {
            points += 10;
        }
    }

    return points;
}
// constructor for my power derived class
Power::Power(const std::string& name, const std::string& description, int duration)
    : Card(name, description), duration(duration) {
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned>(time(0)));
        seeded = true;
    }
    powerLevel = 10 + rand() % 11;
}
// this is where i calculate effect with the help in my constructor class doing all the work there
double Power::calculatePowerEffect() const { return powerLevel * duration; }
