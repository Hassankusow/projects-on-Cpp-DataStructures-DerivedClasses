// .h file for my haunted house which i called maze for short

#include "myutil.h"
#include "attendee.h"
#include <vector>

// my CLL defintion for child function 
class Node {
public:
    Child* data;
    Node* next;

    Node(Child* attendee_data) : data(attendee_data), next(nullptr) {}
    ~Node() { delete data; }
};

// my Array of link list def for adult 
class node {
public:
    Adult* data;
    node* next;

    node(Adult* attendee_data) : data(attendee_data), next(nullptr) {}
    ~node() { delete data; }
};

// my class for my haunted house
class Maze {

private:
    Node* rear; // my CLL pionter 
    vector<node*> adult_lists; // my vector pionter for array of link list 
    vector<Animal*> animal_list; // my vector for not link list for animal

public:
    Maze();  
    ~Maze(); 

    void addChild(Child* attendee_data);  
    void displayChildren() const;        
    void navigateChildren();            

    bool isEmpty() const;

    void add_adult(Adult* attendee_data, int index);
    void display_adults(int index) const;
    void navigate_adults();

   void addAnimal(Animal* attendee_data);
    void navigateAnimals();
    
    

   
};


