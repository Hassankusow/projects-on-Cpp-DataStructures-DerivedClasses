// this is my main cpp  file pretty clean and easy to follow ill be using 2-3 tree data structure wich took alot
// dynamic binding i didnt even get to use all the features of dynamic binding due 2-3 tree was hard to implement 
// its insert. i got it to work finally but too late wanted to do alot more in inserting many pokemon different types
// but the assigment is due today

#include "tree.h"
#include "poke.h"

int main() {
    srand(time(0)); // Seed for randomness
    PokemonTree tree;
    Pokemon* player = Pokemon::createPlayerPokemon();
    Pokemon* opponent = Pokemon::createOpponentPokemon();

    if (player && opponent) {
        std::cout << "Your Pokémon: " << player->getName() << " | HP: " << player->getHp() << "\n";
        std::cout << "Opponent's Pokémon: " << opponent->getName() << " | HP: " << opponent->getHp() << "\n";
       
        tree.insert(player);
        tree.insert(opponent);
        //tree.display();
        // Start the battle
        player->battle(player, opponent);
    } else {
        std::cerr << "Error: Unable to initialize player or opponent Pokémon.\n";
    }

    tree.print();

    // Clean up
    delete player;
    delete opponent;

    return 0;
}

