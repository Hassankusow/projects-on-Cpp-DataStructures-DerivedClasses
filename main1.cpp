#include "myutil.h"
#include "maze.h"
#include <iostream>

using namespace std;
// my main function
int main() {
    Maze maze; // my hounted house class

    const int MAX_ATTENDEES = 10; // i made it so the max is 10 
    attendee* attendees[MAX_ATTENDEES]; // pionter for attendee and made it 10 this is for output
    // child class pionter
     // animal class pionter
     // adult class pionter 
    int attendeeCount = 0;
    char addMore;
    int index= 0;
    do{
    
        
        cout << "Would you like to add an attendee? (y/n): ";
        cin >> addMore;
        cin.ignore();

        if (tolower(addMore) == 'y') {
    attendees[attendeeCount] = new attendee();
    attendees[attendeeCount]->input_a(attendees, attendeeCount);

    // Check the attendee type explicitly
    switch (attendees[attendeeCount]->getType()) {
        case attendee_type::ANIMAL:
            maze.addAnimal(static_cast<Animal*>(attendees[attendeeCount]));
            cout << "Animal detected: " << attendees[attendeeCount]->getName() << endl;
            maze.navigateAnimals();
            break;

        case attendee_type::CHILD:
            maze.addChild(static_cast<Child*>(attendees[attendeeCount]));
            maze.navigateChildren();
            cout << "\nDisplaying all children in the maze:\n";
            maze.displayChildren();
            break;

        case attendee_type::ADULT:
            maze.add_adult(static_cast<Adult*>(attendees[attendeeCount]), index);
            cout << "Adult added to index " << index << endl;
            index++;
            maze.navigate_adults();
            break;

        default:
            cout << "Unknown attendee type!\n";
            break;
    }

    attendeeCount++;
}
    }while(attendeeCount < MAX_ATTENDEES && tolower(addMore) == 'y');

   cout << "\nList of Attendees:\n";
    if (attendeeCount == 0) {
        cout << "No attendees to display.\n";
    } else {
        for (int i = 0; i < attendeeCount; i++) {
           if (attendees[i] != nullptr) {
	    	cout << *attendees[i]; 
	   }
        }

    }

    
    
    return 0;
}


