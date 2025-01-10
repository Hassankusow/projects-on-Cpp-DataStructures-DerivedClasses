// attendee.cpp file 


#include "myutil.h"
#include "attendee.h"

using namespace std;

// Constructors
attendee::attendee() : name(nullptr), age(0), type(attendee_type::NONE) {}


attendee::attendee(const char * input_name, attendee_type type) : type(type) {
    name = new char[strlen(input_name) + 1];
    strcpy(name, input_name);
}

attendee::attendee(const char * input_name, int input_age) {
    name = new char[strlen(input_name) + 1];  
    strcpy(name, input_name);  
    age = input_age;  
}
attendee::attendee(const char* input_name, int input_age, attendee_type type) : age(input_age), type(type) {
    name = new char[strlen(input_name) + 1];
    strcpy(name, input_name);
}


// Destructor
attendee::~attendee() {
    delete[] name;
}

// Copy Constructor
attendee::attendee(const attendee & Aattendee) {
    name = new char[strlen(Aattendee.name) + 1];
    strcpy(name, Aattendee.name);
    age = Aattendee.age;
}

// my input functon

void attendee::input_a(attendee**  attendees, int& Count) {
    char temp_name[100];
    char is_animal_input;
    int cur_age;
    // Prompt for name
    cout << "Enter the name of the attendee: ";
    cin.getline(temp_name, 100);


    
    name = new char[strlen(temp_name) + 1];
    strcpy(name, temp_name);

    
    cout << "Enter the age of the attendee: ";
    cin >> age;
    cur_age = age;
    
    cin.ignore();
    
    // i made my life simpler i couldve added type in my constructor list
    //  but dont need to keep track

    cout << "Is the attendee an animal? (y/n): ";
    cin >> is_animal_input;
    is_animal_input = tolower(is_animal_input);

    bool is_animal = (tolower(is_animal_input) == 'y');

    if (is_animal) {
	type = attendee_type::ANIMAL;
        attendees[Count] = new Animal(temp_name, cur_age); // ill create an Animal dynamicaly
    } else if (cur_age < 14) {
	type = attendee_type::CHILD;
        attendees[Count] = new Child(temp_name, cur_age); // ill create a Child dynamicaly 
    } else {
	type = attendee_type::ADULT;
        attendees[Count] = new Adult(temp_name, cur_age); // ill create an Adult dynamicaly
    }
};
// these functions are my getter function
attendee_type attendee::getType() const {
    return type;
}

const char* attendee::getName() const {
    return name;
}

int attendee::getAge() const {
    return age;
};

// these are my setter function
void attendee::setName(const char* name) {
    delete[] this->name;  
    this->name = new char[strlen(name) + 1]; 
    strcpy(this->name, name);
}

void attendee::setAge(int age) {
    this->age = age;
}

void attendee::init(const char* name, int age) {
    setName(name);
    setAge(age);
}


//  display attendee info
ostream & operator<<(ostream & out, const attendee & Aattendee) {
    out << "Attendee Name: " << Aattendee.getName() << endl;
    out << "Attendee Age: " << Aattendee.getAge() << endl;
    return out;
};

// Assignment operator
const attendee& attendee::operator=(const attendee & Aattendee) {
    if (this != &Aattendee) { 
        delete[] name; 
        name = new char[strlen(Aattendee.name) + 1];
        strcpy(name, Aattendee.name);
        age = Aattendee.age;
	type = Aattendee.type;
    }
    return *this;
};
// Derived class constructors
Adult::Adult(const char* name, int age) : attendee(name, age, attendee_type::ADULT) {}

Animal::Animal(const char* name, int age) : attendee(name, age, attendee_type::ANIMAL) {}

Child::Child(const char* name, int age) : attendee(name, age, attendee_type::CHILD) {}
// and here is what i will extract from my maze cpp all for child adult and animal 
void Child::display() const {
    cout << "Child Attendee: " << getName() << ", Age: " << getAge() << endl;
}

void Child::pickCandy() {
    cout << getName() << " picks up candy!" << endl;
}

void Child::navigateMaze() {
    cout << getName() << " navigates through the maze!" << endl;
}

void Animal::display() const {
    cout << "Animal Attendee: " << getName() << ", Age: " << getAge() << endl;
}

void Animal::findTreats() {
    cout << getName() << " is looking for treats!" << endl;
}
void Adult::display() const {
    cout << "Adult Attendee: " << getName() << ", Age: " << getAge() << endl;
}
void Adult::faceJumpScare(){
	cout << " BOOOOO!!!!. better luck next time. " << endl;
}
void Adult::trap(){
	cout<< " its a trap" << endl;
}
