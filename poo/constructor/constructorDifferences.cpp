#include <iostream>
#include <string>

class Vehicle {
public:
    // Constructor using Member Initialization List
    Vehicle(std::string id, int y, std::string b, std::string m) : identifier(id), year(y), brand(b), model(m) {
        std::cout << "Using Member Initialization List Constructor" << std::endl;
    }

    // Constructor using Assignment in Constructor Body
    Vehicle(std::string& id, int y, std::string& b, std::string& m) {
        std::cout << "Using Assignment in Constructor Body Constructor" << std::endl;
        std::cout << identifier << std::endl;
        identifier = id;
        year = y;
        brand = b;
        model = m;
    }

    void displayInfo() {
        std::cout << "Identifier: " << identifier << ", Year: " << year << ", Brand: " << brand << ", Model: " << model << std::endl;
    }

private:
    std::string identifier;
    int year;
    std::string brand;
    std::string model;
};

int main() {
    // Using Member Initialization List
    Vehicle vehicle1("V123", 2022, "Toyota", "Camry");
    vehicle1.displayInfo();

    std::cout << std::endl;

    // Using Assignment in Constructor Body
    Vehicle vehicle2("V456", 2023, "Honda", "Civic");
    vehicle2.displayInfo();

    return 0;
}