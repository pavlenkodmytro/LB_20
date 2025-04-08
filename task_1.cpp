#include <iostream>
#include <string>
using namespace std;

class Person
{
public:
    string name;
    int age;
    string city;
};

void print(Person* person)
{
    cout << person->name << " is " << person->age << " years old"
         << " and lives in " << person->city << endl;
}

int main()
{
    Person person;
    person.name = "Harry";
    person.age = 23;
    person.city = "Kyiv"; // City relevant to current location: Ukraine

    cout << "Meet " << person.name << endl;
    print(&person);

    return 0;
}
