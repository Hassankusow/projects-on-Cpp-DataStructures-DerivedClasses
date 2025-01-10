#include "poke.h"
// this made it really simple i create a player of my choosing
Pokemon* Pokemon::createPlayerPokemon() {
    int choice;
    std::cout << "Choose your Pokémon: 1) Charizard (Fire) 2) Blastoise (Water) 3) Venusaur (Grass)\n";
    std::cin >> choice;

    if (choice == 1) {
        return new FirePokemon("Charizard", 50, 200, 70);
    } else if (choice == 2) {
        return new WaterPokemon("Blastoise", 50, 200, 80);
    } else if (choice == 3) {
        return new GrassPokemon("Venusaur", 50, 200, 60);
    } else {
        std::cout << "Invalid choice! Defaulting to Charizard.\n";
        return new FirePokemon("Charizard", 50, 200, 70);
    }
}
// this is a oppenent pokemon of random chosen 
Pokemon* Pokemon::createOpponentPokemon() {
    int randChoice = rand() % 3 + 1;
    if (randChoice == 1) {
        return new FirePokemon(" Charizard", 50, 200, 70);
    } else if (randChoice == 2) {
        return new WaterPokemon(" Blastoise", 50, 200, 80);
    } else {
        return new GrassPokemon(" Venusaur", 50, 200, 60);
    }
}
// this is my function where they battle 
void Pokemon::battle(Pokemon* player, Pokemon* opponent) {
    if (player == nullptr || opponent == nullptr) {
        std::cerr << "Error: Invalid player or opponent pointer.\n";
        return;
    }
    
    while (!player->isDefeated() && !opponent->isDefeated()) {
        // Player's turn
        int action;
        std::cout << "\nYour turn! Choose action: 1) Attack 2) Defend 3) Heal: ";
        std::cin >> action;

        bool playerDefends = false;

        if (action == 1) {
            player->attack(*opponent);
        } else if (action == 2) {
            player->defend();
            playerDefends = true;
        } else if (action == 3) {
            player->heal();
        } else {
            std::cout << "Invalid choice. You attack by default.\n";
            player->attack(*opponent);
        }

        if (opponent->isDefeated()) {
            std::cout << "\nYou won the battle! Opponent's " << opponent->getName() << " has been defeated.\n";
            break;
        }

        // Opponent's turn
        int opponentAction = rand() % 3 + 1;
        std::cout << "Opponent's turn: ";

        bool opponentDefends;
        opponentDefends = false;

        if (opponentAction == 1) {
            if (!playerDefends) {
                opponent->attack(*player);
            }
        } else if (opponentAction == 2) {
            opponent->defend();
            opponentDefends = true;
        } else if (opponentAction == 3) {
            opponent->heal();
        }

        if (player->isDefeated()) {
            std::cout << "\nYou lost the battle! Your " << player->getName() << " has been defeated.\n";
            break;
        }

        std::cout << "\nYour Pokémon: " << player->getName()  << " | HP: " << player->getHp() << std::endl;
        std::cout << "Opponent's Pokémon: " << opponent->getName() << " | HP: " << opponent->getHp() << std::endl;
        if (opponentDefends) {
        std::cout << " ";
    }}
    
}
// my derived pokemons atack defend and heal functions
void FirePokemon::attack(Pokemon& opponent) {
    std::cout << name << " use flamethrower!" << std::endl;
    opponent.setHp(opponent.isDefeated() ? 0 : opponent.getHp() - attackPower);
}

void FirePokemon::defend() {
    std::cout << name << " counter with fire shield !" << std::endl;
}

void FirePokemon::heal() {
    std::cout << name << " use fire energy to heal!" << std::endl;
    setHp(getHp() + 10);
}

void WaterPokemon::attack(Pokemon& opponent) {
    std::cout << name << " use watter cannon!" << std::endl;
    opponent.setHp(opponent.isDefeated() ? 0 : opponent.getHp() - attackPower);
}

void WaterPokemon::defend() {
    std::cout << name << " counter with water absorb!" << std::endl;
}

void WaterPokemon::heal() {
    std::cout << name << " heal with aqua layer !" << std::endl;
    setHp(getHp() + 10);
}

void GrassPokemon::attack(Pokemon& opponent) {
    std::cout << name << " use vine whip!" << std::endl;
    opponent.setHp(opponent.isDefeated() ? 0 : opponent.getHp() - attackPower);
}

void GrassPokemon::defend() {
    std::cout << name << " counter with razor leaf!" << std::endl;
}

void GrassPokemon::heal() {
    std::cout << name << " heal with floral heal!" << std::endl;
    setHp(getHp() + 10);
}

// i am using three operator overload one to compare attack power and one for output 
std::ostream& operator<<(std::ostream& os, const Pokemon& pokemon) {
    os << "Pokemon name: " << pokemon.getName()
       << " | Attack: " << pokemon.attackPower
       << " | HP: " << pokemon.getHp()
       << " | Defense: " << pokemon.defense;
    return os;
}

bool Pokemon::operator<(const Pokemon& other) const {
    return attackPower < other.attackPower; // Compare by attack power
}

bool Pokemon::operator>(const Pokemon& other) const {
    return attackPower > other.attackPower; // Compare by attack power
}

