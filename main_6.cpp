// main.cpp
#include <iostream>
#include "cards.h"
#include "deck.h"
#include "player.h"

int main() {
    Deck<Card> cardDeck; // my template member object in main
    Player player1("Player 1");
    Player player2("Player 2");

    Card* player1Card = nullptr; // Store player 1's drawn card
    Card* player2Card = nullptr; // Store player 2's drawn card
    int choice;
// this is example for the user to know what type of game it is.
std::cout << "\n--- Example of Input ---\n";
std::cout << "\nEnter weapon name: Sword of Ares\n";
std::cout << "\nEnter weapon description: The legendary sword of the Fire Lord\n";
std::cout << "\nSince it’s a sword, choose 1 for Sword type and set the rarity to Legendary\n";
std::cout << "\nChoose whether it’s either a ranged or melee weapon\n";
std::cout << "\nAnd finally, enjoy the game!\n";

// a do while loop if the choice is 7 that uses a simple switch case menu 
    do {
        std::cout << "\n--- Main Menu ---\n";
        std::cout << "1. Create Card and Add to Deck\n";
        std::cout << "2. Player 1 Draw Cards\n";
        std::cout << "3. Player 2 Draw Cards\n";
        std::cout << "4. Duel\n";
        std::cout << "5. Delete Card from Deck\n";
        std::cout << "6. Display Deck\n";
        std::cout << "7. Quit\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;
        switch (choice) {
            case 1: {
                std::cin.ignore();
                Card card; // a card member class
                card.createCard(); // call createCard to get the info and store in add card in my template
                cardDeck.addCard(new Card(card));
                std::cout << "Card added to deck!\n";
                break;
            }
            case 2: {
                player1Card = cardDeck.drawCard(); // Draws a card for player 1
                if (player1Card) {
                std::cout << "Player 1 drew: " << *player1Card << "\n";
                player1.calculateScore(player1Card); // Calculates score with the drawn card
        } else {
                std::cout << "The deck is empty, no card drawn for Player 1!\n";
        }
                break;
        }
           case 3: {
                player2Card = cardDeck.drawCard(); // Draws a card for player 2
                if (player2Card) {
                std::cout << "Player 2 drew: " << *player2Card << "\n";
                player2.calculateScore(player2Card); // Calculates score with the drawn card
        } else {
                std::cout << "The deck is empty, no card drawn for Player 2!\n";
        }
                break;
        }
            case 4: {
                std::cout << "--- Duel ---\n";

                if (player1Card && player2Card) {
                // Determine the winner based on the score already calculated
                if (player1.getScore() > player2.getScore()) {
                std::cout << "Player 1 wins the duel!\n";
                } else if (player1.getScore() < player2.getScore()) {
                std::cout << "Player 2 wins the duel!\n";
        } else {
                std::cout << "The duel is a tie!\n";
        }
        } else {
                std::cout << "Both players need to draw a card before dueling.\n";
        }

                break;
                }
            case 5: {
                if (!cardDeck.isEmpty()) {
                    cardDeck.removeCard(cardDeck.getHead());
                    std::cout << "Card removed from the deck.\n";
                } else {
                    std::cout << "The deck is empty. No cards to delete.\n";
                }
                break;
            }
            case 6: {
                cardDeck.displayDeck();
                break;
            }
            case 7:
                std::cout << "Quitting the game.\n";
                break;
            default:
                std::cout << "Invalid option. Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}
//
