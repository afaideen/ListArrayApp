#include <iostream>
#include <string>
#include <list>
#include <algorithm> // For std::sort

class Person {
public:
    // Constructor to initialize attributes
    Person(const std::string& firstname, const std::string& lastname, int age, const std::string& sex, bool married)
        : firstname(firstname), lastname(lastname), age(age), sex(sex), married(married) {}

    // Attributes
    std::string firstname;
    std::string lastname;
    int age;
    std::string sex;
    bool married;
};

// Comparator function for sorting by age (descending)
struct CompareByAge {
    bool operator()(const Person& person1, const Person& person2) const {
        return person1.age > person2.age;
    }
};

// Predicate function for removing the person named Bob
struct RemoveBob {
    bool operator()(const Person& person) const {
        return person.firstname == "Bob";
    }
};



int main() {
    // Create three Person instances
    Person person1("Alice", "Smith", 30, "female", true);
    Person person2("Bob", "Johnson", 25, "male", true);
    Person person3("Charlie", "Brown", 22, "male", false);
    Person person4("Han", "Isaac", 43, "male", false);

    // Create a list of Persons
    std::list<Person> personList;
    personList.push_back(person1);
    personList.push_back(person2);
    personList.push_back(person3);

    // Remove the person named Bob from the list
    personList.remove_if(RemoveBob());
    //personList.remove(person2);
    personList.push_back(person4);

    // Sort the list by age (descending)
    personList.sort(CompareByAge());

    // Print information for each person in the updated list
    for (std::list<Person>::const_iterator it = personList.begin(); it != personList.end(); ++it) {
        const Person& person = *it;
        std::cout << "First Name: " << person.firstname << std::endl;
        std::cout << "Last Name: " << person.lastname << std::endl;
        std::cout << "Age: " << person.age << std::endl;
        std::cout << "Sex: " << person.sex << std::endl;
        std::cout << "Marriage status: " << (person.married ? "Married" : "Single") << std::endl;
        std::cout << std::endl;
    }

    return 0;
}
