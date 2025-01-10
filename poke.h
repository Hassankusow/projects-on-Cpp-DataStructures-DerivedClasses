// this is porgram 3 hassan abdi
// this is for me to learn dynamic binding and its propeties and also use operator overload
// in this program ill be using data structor BST as well
#ifndef POKE_H
#define POKE_H

#include <string>
#include <iostream>

class Pokemon {
protected:
    std::string name; // string name for pokemon
    int attackPower;  // attacl power
    int hp;           // hp
    int defense;      // defense

public:
    Pokemon(std::string name, int attackPower, int hp, int defense)
        : name(name), attackPower(attackPower), hp(hp), defense(defense) {}
   // dynamic binding virtual implementation
    virtual void attack(Pokemon& opponent) = 0;
    virtual void defend() = 0;
    virtual void heal() = 0;

    
// my getter function for attack power
    int getAttackPower() const {
        return attackPower;
    }
// my display status this is used for my tree
    void displayStats() const {
        std::cout << name << " | Attack: " << attackPower << " | HP: " << hp << std::endl;
    }
// this is for the battle function 
    bool isDefeated() const { return hp <= 0; }
// getter functions
    std::string getName() const { return name; }
    void setHp(int newHp) { hp = newHp; }
    int getHp() const { return hp; }
// my destrocutor 
    virtual ~Pokemon() {}
// opertor overloads
    bool operator<(const Pokemon& other) const;
    bool operator>(const Pokemon& other) const;
    // this is my creating pokemon for openenet and user 
    static Pokemon* createPlayerPokemon();
    static Pokemon* createOpponentPokemon();
    static void battle(Pokemon* player, Pokemon* opponent);
    friend std::ostream& operator<<(std::ostream& os, const Pokemon& pokemon);
};

// my derived functions 
class FirePokemon : public Pokemon {
public:
    FirePokemon(std::string name, int attackPower, int hp, int defense)
        : Pokemon(name, attackPower, hp, defense) {}

    void attack(Pokemon& opponent) override;
    void defend() override;
    void heal() override;
};

class WaterPokemon : public Pokemon {
public:
    WaterPokemon(std::string name, int attackPower, int hp, int defense)
        : Pokemon(name, attackPower, hp, defense) {}

    void attack(Pokemon& opponent) override;
    void defend() override;
    void heal() override;
};

class GrassPokemon : public Pokemon {
public:
    GrassPokemon(std::string name, int attackPower, int hp, int defense)
        : Pokemon(name, attackPower, hp, defense) {}

    void attack(Pokemon& opponent) override;
    void defend() override;
    void heal() override;
};

#endif

