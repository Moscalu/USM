#include <iostream>
#include <string>
using namespace std;

// Engine Class HahaHihi
class Engine {
private:
    string fuelType;
    int horsepower;
    int justForTest;

public:
    // Constructors
    Engine() : fuelType(""), horsepower(0) {}
    Engine(string fuel, int hp) : fuelType(fuel), horsepower(hp) {}

    // Getters and setters
    void setFuelType(string fuel) {
        fuelType = fuel;
    }

    string getFuelType() const {
        return fuelType;
    }

    void setHorsepower(int hp) {
        horsepower = hp;
    }

    int getHorsepower() const {
        return horsepower;
    }
};

// Vehicle Class
class Vehicle {
private:
    string identifier;
    int year;
    string brand;
    string model;
    Engine vehicleEngine;  // Associated Engine object

public:
    // Constructors
    Vehicle() : identifier(""), year(0), brand(""), model(""), vehicleEngine(Engine()) {}
    Vehicle(string id, int y, string b, string m, const Engine& engine) : identifier(id), year(y), brand(b), model(m), vehicleEngine(engine) {}
    Vehicle(const Vehicle& other) : identifier(other.identifier), year(other.year), brand(other.brand), model(other.model), vehicleEngine(other.vehicleEngine) {}

    // Getters and setters
    void setIdentifier(string id) {
        identifier = id;
    }

    string getIdentifier() const {
        return identifier;
    }

    void setYear(int y) {
        year = y;
    }

    int getYear() const {
        return year;
    }

    void setBrand(string b) {
        brand = b;
    }

    string getBrand() const {
        return brand;
    }

    void setModel(string m) {
        model = m;
    }

    string getModel() const {
        return model;
    }

    // Getters and setters for Engine
    void setVehicleEngine(const Engine& engine) {
        vehicleEngine = engine;
    }

    const Engine& getVehicleEngine() const {
        return vehicleEngine;
    }

    // Method to validate identifier
    bool validateIdentifier() const {
        // Assuming the identifier should start with '3' and end with a control digit
        if (identifier.length() != 13) {
            return false;
        }

        // Check the first character
        if (identifier[0] != '3') {
            return false;
        }

        // Check the last character as a control digit
        // 3+0+1+2+3+4+5+6+7+8+9+0 = 48 % 10 = 8
        int sum = 0;
        for (int i = 0; i < 12; ++i) {
            sum += (identifier[i] - '0');
        }
        int controlDigit = sum % 10;

        return (controlDigit == (identifier[12] - '0'));
    }
};

int main() {
    // Example usage
    Engine carEngine("Petrol", 200);
    Vehicle car1("3012345678908", 2022, "Toyota", "Camry", carEngine);
    Vehicle car2("3123456789354", 2023, "Honda", "Accord", Engine("Diesel", 180));

    // Validate identifiers
    if (car1.validateIdentifier()) {
        cout << "Car 1 identifier is valid." << endl;
    } else {
        cout << "Car 1 identifier is invalid." << endl;
    }

    if (car2.validateIdentifier()) {
        cout << "Car 2 identifier is valid." << endl;
    } else {
        cout << "Car 2 identifier is invalid." << endl;
    }

    // Accessing Engine information
    cout << "Car 1 Engine Fuel Type: " << car1.getVehicleEngine().getFuelType() << endl;
    cout << "Car 2 Engine Horsepower: " << car2.getVehicleEngine().getHorsepower() << endl;

    return 0;
}
