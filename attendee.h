// hassan abdi
// this is for attendee .h file where I declare everything I need for my .h file

#include "myutil.h"

enum class attendee_type { NONE, CHILD, ADULT, ANIMAL };

// Base class
class attendee {
    private:
        char* name;
        int age;
        attendee_type type;

    public:
        attendee();
        attendee(const char* name, attendee_type type);
        attendee(const char* name, int age);
	attendee(const char* name, int age, attendee_type type);
        attendee(const attendee& Aattendee);
        attendee_type getType() const;
        const char* getName() const;
        int getAge() const;
        void setName(const char* name);
        void setAge(int age);
        void init(const char* name, int age);
        ~attendee();
        void input_a(attendee** attendees, int& Count);
        const attendee& operator=(const attendee& Aattendee);
        friend ostream& operator<<(ostream& out, const attendee& Aattendee);
};

// Derived class Adult
class Adult : public attendee {
    public:
        Adult(const char* name, int age);
        void display() const;
        void faceJumpScare();
        void trap();
};

// Derived class Animal
class Animal : public attendee {
    public:
        Animal(const char* name, int age);
        void display() const;
        void findTreats();
};

// Derived class Child
class Child : public attendee {
    public:
        Child(const char* name, int age);
        void display() const;
        void pickCandy();
        void navigateMaze();
};

