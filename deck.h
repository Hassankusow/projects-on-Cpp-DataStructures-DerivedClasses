// deck.h
#ifndef DECK_H
#define DECK_H
// my deck.h file where i use a doubly link list and for my deck class where i store multiple cards to dual
#include <iostream>

template <typename T>
class Node {
public:
    T* card;
    Node<T>* prev;
    Node<T>* next;

    Node(T* card);
};

template <typename T>
class Deck {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    Deck();
    void addCard(T* newCard);
    void removeCard(Node<T>* node);
    T* drawCard();
    bool isEmpty() const;
    void displayDeck() const;
    Node<T>* getHead();
};

#include "deck.tpp"

#endif // DECK_H

