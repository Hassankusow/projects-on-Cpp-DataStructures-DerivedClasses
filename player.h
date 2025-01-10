#ifndef PLAYER_H
#define PLAYER_H
// this is my player class small class that uses my template and pionts from cards class
//    to determine who the winner is when player 1 and 2 dual
#include <string>
#include "deck.h"
#include "cards.h"

class Player {
private:
    std::string name;
    int health;
    int score;

public:
    Player(const std::string& playerName);
    void drawCards(Deck<Card> & cardDeck);
    void calculateScore(Card * aCard);
    void displayStatus() const;
    bool takeTurn(Deck<Card> * cardDeck);
    int getScore() const;
};

#endif // PLAYER_H

