// deck.tpp

// a Node class constructor
template <typename T>
Node<T>::Node(T* card) : card(card), prev(nullptr), next(nullptr) {}

// Deck class constructor
template <typename T>
Deck<T>::Deck() : head(nullptr), tail(nullptr) {}

// Add a card to the deck
template <typename T>
void Deck<T>::addCard(T* newCard) {
    Node<T>* newNode = new Node<T>(newCard);
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

// In deck.tpp, change getHead() to return Node<T>* instead of T*
template <typename T>
Node<T>* Deck<T>::getHead() {
    return head;  // Return the head node directly
}


// Remove a specific card node from the deck
template <typename T>
void Deck<T>::removeCard(Node<T>* node) {
    if (node == nullptr) {
        return;
    }
    if (node == head) {  // If the node to remove is the head
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;  // If list is now empty
        }
    } else if (node == tail) {  // If the node to remove is the tail
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        }
    } else {  // If the node is in the middle
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    delete node;  // Free memory
}


// Draw a random card from the deck
template <typename T>
T* Deck<T>::drawCard() {
    if (isEmpty()) return nullptr;

    // Ill count the number of cards in the deck
    int deckSize = 0;
    Node<T>* current = head;
    while (current != nullptr) {
        deckSize++;
        current = current->next;
    }

    // Generate a random index
    int randomIndex = rand() % deckSize;

    // Traverse to the random index
    current = head;
    for (int i = 0; i < randomIndex; i++) {
        current = current->next;
    }

    // Get the card and remove it from the deck
    T* card = current->card;
    removeCard(current);

    return card;
}

// Check if the deck is empty
template <typename T>
bool Deck<T>::isEmpty() const {
    return head == nullptr;
}
// displaying template
template <typename T>
void Deck<T>::displayDeck() const {
    Node<T>* current = head;
    while (current != nullptr) {
        std::cout << *(current->card) << " ";
        current = current->next;
    }
    std::cout << std::endl;
}


