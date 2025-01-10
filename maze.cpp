#include "maze.h"
#include <iostream>
using namespace std;
// constructor for both CLL and adult 
Maze::Maze() : rear(nullptr), adult_lists(5, nullptr) {}

Maze::~Maze() {

   // this is for cll destructor
    if (!isEmpty()) {
        Node* cur = rear->next;
        rear->next = nullptr;

        while (cur) {
            Node* temp = cur;
            cur = cur->next;
            delete temp;
        }
    }

    //this is for array of link list
    for (auto& list : adult_lists) {
        while (list != nullptr) {
            node* temp = list;
            list = list->next;
            delete temp;
        }
    }
}

// this is a bool function to help for my CLL
bool Maze::isEmpty() const {
    return rear == nullptr;
}

// my add child CLL for child 
void Maze::addChild(Child* attendee_data) {
    Node* newNode = new Node(attendee_data);

    if (isEmpty()) {
        rear = newNode;
        rear->next = rear;
    } else {
        newNode->next = rear->next;
        rear->next = newNode;
        rear = newNode;
    }
}

// display function for child 
void Maze::displayChildren() const {
    if (rear == nullptr) {
        cout << "No children in the maze." << endl;
        return;
    }

    Node* temp = rear->next;
    do {
        temp->data->display();
        temp = temp->next;
    } while (temp != rear->next);
}


   


// my CLL function for child 
void Maze::navigateChildren() {
    if (rear == nullptr) {
        cout << "No children in the maze to navigate.\n";
        return;
    }

    Node* temp = rear->next;

    do {
        cout << temp->data->getName() << " enters the haunted maze!" << endl;
        temp->data->navigateMaze();
        temp->data->pickCandy();

        char choice;
        cout << temp->data->getName() << ", do you want to continue navigating the maze? (y/n): ";
        cin >> choice;

        if (tolower(choice) == 'n') {
            cout << temp->data->getName() << " exits the maze!" << endl;
            Node* exitingChild = temp;

            if (exitingChild == rear && exitingChild->next == rear) {
                delete rear;
                rear = nullptr;
                return;
            } else {
                Node* prev = rear;
                while (prev->next != exitingChild) {
                    prev = prev->next;
                }
                prev->next = exitingChild->next;

                if (exitingChild == rear) {
                    rear = prev;
                }
                temp = exitingChild->next; 
                delete exitingChild;
            }
        } else {
            temp = temp->next;
        }
    } while (temp != rear->next && rear != nullptr);
}


// my add function for adults 
void Maze::add_adult(Adult* attendee_data, int index){

if (index < 0 || index >= static_cast<int>(adult_lists.size())) {
        std::cerr << "Invalid index for adult lists." << std::endl;
        return;
    }
    node* newNode = new node(attendee_data);
    newNode->next = adult_lists[index];
    adult_lists[index] = newNode;

}

// my display function for adults 
void Maze::display_adults(int index) const
{
 node* current = adult_lists[index];
    if (!current) {
        cout << "No adults in list " << index << "." << std::endl;
        return;
    }
    cout << "Adults in list " << index << ": ";
    while (current) {
        current->data->display();
        current = current->next;
    }
    cout << endl;

}

// my navigation for adults 
void Maze::navigate_adults() {
    for (size_t i = 0; i < adult_lists.size(); ++i) {
        node* current = adult_lists[i];
        while (current) {
            cout << "Adult " << current->data->getName() << " is navigating through room " << i + 1 << ".\n";

            int steps = 0;
            bool maze_completed = false;

            while (!maze_completed) {
                cout << "Choose a direction (left/right): ";
                string direction;
                cin >> direction;

                if (direction == "right") {
                    steps++;
                    if (steps == 2) {
                        cout << "You are close to finishing the maze!\n";
                        maze_completed = true;
                    } else {
                        cout << "Good choice! Keep going.\n";
                    }
                }
                else if (direction == "left") {
                    if (steps == 0) {
                        current->data->trap();
                    } else if (steps == 1) {
                        current->data->faceJumpScare();
                        steps = 0;
                    }
                }

                cout << "Do you want to continue? (y/n): ";
                char response;
                cin >> response;
                if (response == 'n' || response == 'N') {
                    cout << "Adult " << current->data->getName() << " has exited the maze.\n";
                    return;
                }
            }

            current = current->next;
        }
    }
    cout << "All adults have navigated through the maze.\n";
}

// my add animal function 
void Maze::addAnimal(Animal* animal) {
    animal_list.push_back(animal); 
}

// my navigation function 
void Maze::navigateAnimals() {
    cout << "Welcome to the maze adventure for our animals!\n";

    for (size_t i = 0; i < animal_list.size(); ++i) {
        Animal* currentAnimal = animal_list[i];
        cout << "\nAnimal " << currentAnimal->getName() << " is starting to navigate the maze!\n";

        cout << currentAnimal->getName() << " follows a sweet scent towards the exit!\n";

        char choice;
        cout << "Does " << currentAnimal->getName() << " want to rush towards the treats at the exit? (y/n): ";
        cin >> choice;

        if (tolower(choice) == 'y') {
            cout << currentAnimal->getName() << " races towards the treats, reaching the exit!\n";
            currentAnimal->findTreats();
        } else {
            cout << currentAnimal->getName() << " decides to explore a bit more.\n";
            cout << "But the treats are calling! After some hesitation, " << currentAnimal->getName() << " heads towards the treats.\n";
            currentAnimal->findTreats();
        }
    }

    cout << "\nAll animals have successfully navigated through the maze to find their treats!\n";
}

