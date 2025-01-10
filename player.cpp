//
// player.cpp
//
#include "player.h"
#include <iostream>
// constructor 
Player::Player(const std::string& playerName) : name(playerName), health(100), score(0) {}
//i wanted to do suffle deck and then using the head this is my deck.tpp where i do the work
// but made it random its just random selected index in my dll list
void Player::drawCards(Deck<Card>& cardDeck) {
    Card* card = cardDeck.drawCard();
    if (card != nullptr) {
        std::cout << "Player drew: " << *card << std::endl;
    } else {
        std::cout << "The deck is empty, no card drawn!" << std::endl;
    }
}
// this is where i use my getter function for pionts and caculate who wins in main
void Player::calculateScore(Card* card) {
    if (card != nullptr) {
        score += card->getPoints();
    }
}
// last minute edit dont have time to implement this i wanted to implment player 1 and 2 
// duallig multiple times and health resiceds everytime a person looses a turn thats where 
// you can see my bool function down below 
void Player::displayStatus() const {
    std::cout << "Player: " << name << ", Health: " << health << ", Score: " << score << "\n";
}
// ill finish this in my own time this i could make into a full stack project
bool Player::takeTurn(Deck<Card>* cardDeck) {
    
    return true;
}
// this is getter function to return the score
int Player::getScore() const {
    return score;
}

