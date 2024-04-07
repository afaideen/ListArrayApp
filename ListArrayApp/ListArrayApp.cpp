#include <cstdio>
#include <cstdlib>
#include <cstring>

// Define a structure for a person
struct Person {
    int age;
    char sex;
    char* firstname;
    char* lastname;
};

// Define a structure for the list
struct List {
    Person** persons;
    size_t size;
};

// Custom implementation of strdup
char* my_strdup(const char* str) {
    size_t len = strlen(str) + 1;
    char* dup = new char[len];
    if (dup)
        strcpy_s(dup, len, str);
    return dup;
}

// Function to create a new person
Person* createPerson(int age, char sex, const char* firstname, const char* lastname) {
    Person* person = new Person;
    if (person == nullptr) {
        fprintf(stderr, "Failed to allocate memory for person\n");
        exit(EXIT_FAILURE);
    }
    person->age = age;
    person->sex = sex;
    person->firstname = my_strdup(firstname);
    person->lastname = my_strdup(lastname);
    if (person->firstname == nullptr || person->lastname == nullptr) {
        fprintf(stderr, "Failed to allocate memory for firstname or lastname\n");
        exit(EXIT_FAILURE);
    }
    return person;
}

// Function to create a new list
List* createList(size_t size) {
    List* list = new List; // or: struct List* list = (struct List*)malloc(sizeof(struct List));
    if (list == nullptr) {
        fprintf(stderr, "Failed to allocate memory for list\n");
        exit(EXIT_FAILURE);
    }
    list->persons = new Person * [size]; // or: list->persons = (struct Person**)malloc(size * sizeof(struct Person*));
    if (list->persons == nullptr) {
        fprintf(stderr, "Failed to allocate memory for persons array\n");
        exit(EXIT_FAILURE);
    }
    list->size = size;
    return list;
}

// Function to add a person to the end of the list
void addToList(List* list, Person* person) {
    Person** temp = reinterpret_cast<Person**>(std::realloc(list->persons, (list->size + 1) * sizeof(Person*)));
    if (temp == nullptr) {
        fprintf(stderr, "Failed to reallocate memory for persons array\n");
        exit(EXIT_FAILURE);
    }
    list->persons = temp;
    list->persons[list->size] = person;
    list->size++;
}

// Function to remove a person from the list at the specified index
void removeFromList(List* list, size_t index) {
    if (index >= list->size) {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }

    // Check if list->persons is nullptr or if list->persons[index] is nullptr
    if (list->persons == nullptr || list->persons[index] == nullptr) {
        fprintf(stderr, "Invalid pointer\n");
        exit(EXIT_FAILURE);
    }

    // Free memory for list->persons[index] and its fields
    delete[] list->persons[index]->firstname;
    delete[] list->persons[index]->lastname;
    delete list->persons[index];

    // Reset list->persons[index] to nullptr
    list->persons[index] = nullptr;

    // Shift remaining elements to fill the gap
    for (size_t i = index; i < list->size - 1; i++) {
        list->persons[i] = list->persons[i + 1];
    }

    // Decrement the size of the list
    list->size--;

    // Reallocate memory for list->persons
    Person** temp = new Person * [list->size];
    if (temp == nullptr && list->size > 0) {
        fprintf(stderr, "Failed to reallocate memory for persons array\n");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < list->size; i++) {
        temp[i] = list->persons[i];
    }
    delete[] list->persons;
    list->persons = temp;
}




// Function to print the list
void printList(List* list) {
    for (size_t i = 0; i < list->size; i++) {
        printf("Person %zu: Age: %d, Sex: %c, Firstname: %s, Lastname: %s\n", i + 1,
            list->persons[i]->age, list->persons[i]->sex,
            list->persons[i]->firstname, list->persons[i]->lastname);
    }
}

// Function to free memory allocated for the list
void freeList(List* list) {
    for (size_t i = 0; i < list->size; i++) {
        delete[] list->persons[i]->firstname;
        delete[] list->persons[i]->lastname;
        delete list->persons[i];
    }
    delete[] list->persons;
    delete list;
}

int main() {

    // Create the list and populate it with person objects
    struct List* mylist = createList(3);
    mylist->persons[0] = createPerson(25, 'm', "John", "Doe");
    mylist->persons[1] = createPerson(30, 'f', "Jane", "Smith");
    mylist->persons[2] = createPerson(40, 'm', "Michael", "Johnson");

    printf("Before removing:\n");
    printList(mylist);

    // Remove person1 from the list
    removeFromList(mylist, 0);

    printf("\nAfter removing:\n");
    printList(mylist);


    // Create and add person objects to the list
    Person* person1 = createPerson(25, 'm', "John", "Doe");
   
    addToList(mylist, person1);

    // Print the list
    printf("After adding:\n");
    printList(mylist);

    // Free memory allocated for the list
    freeList(mylist);

    return 0;
}
