#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Engine class definition
class Engine {
private:
    string type;
    int horsepower;

public:
    // Constructor
    Engine(string t, int hp) : type(t), horsepower(hp) {}

    // ... Other getter and setter methods for type, horsepower...
    void setType(string t) { type = t; }
    string getType() const { return type; }

    void setHorsepower(int h) { horsepower = h; }
    int getHorsepower() { return horsepower; }
    // Method to get information about the Engine
    void getData() const {
        cout << "Type: " << type << endl;
        cout << "Horsepower: " << horsepower << endl;
    }

};

// Forward declaration of Vehicle class
class Vehicle;

class UserInput {
public:
    static vector<Vehicle> createVehicle(int numCars) {
        vector<Vehicle> vehicles;
        string id, b, m;
        int y;

        for (int i = 0; i < numCars; i++) {
            cout << "Enter please the ID of the car" << (i + 1) << ": "; 
            cin >> id; //while (id.length() == 10) {}
            cout << "Enter please the Year of the car" << (i + 1) << ": ";
            cin >> y;
            cout << "Enter please the Brand of the car" << (i + 1) << ": ";
            cin >> b;
            cout << "Enter please the Model of the car" << (i + 1) << ": ";
            cin >> m;
            cout << endl;

            // Create a new Vehicle object
            Vehicle newVehicle(id, y, b, m);

            // Create a new Engine object
            string engineType;
            int engineHorsepower;

            cout << "Enter the Engine Type for car " << (i + 1) << ": ";
            cin >> engineType;
            cout << "Enter the Engine Horsepower for car " << (i + 1) << ": ";
            cin >> engineHorsepower;
            cout << endl;

            // Use the fully qualified name for the Engine class
            Vehicle::Engine* newEngine = new Vehicle::Engine(engineType, engineHorsepower);

            // Set the Engine for the Vehicle
            newVehicle.setEngine(newEngine);

            vehicles.push_back(Vehicle(id, y, b, m));
        }
    
         return vehicles;
    }
};

class Vehicle {
private:
    string identifier;
    int year;
    string brand;
    string model;
    // Composition relationship: Vehicle has an Engine
    Engine* engine; // Pointer to Engine object
    friend class Engine;

public:
    //string id;
    // Constructors
    Vehicle(string id, int y, string b, string m) : identifier(id), year(y), brand(b), model(m) {}
    // Vehicle(string indentifier, int year, string brand, string model) : identifier(identifier), year(year), brand(brand), model(model) {}
    // Vehicle() : identifier(""), year(0), brand(""), model("") {}
    // Vehicle(const Vehicle& other) : identifier(other.identifier), year(other.year), brand(other.brand), model(other.model) {}

    // Note that const is used just to let developers to know that this method will not modify any variables. Also an important note is that the compiler
    // will return an error if the method will change any variables.
    void getData() const {
        // Note that inside the same class I can access private vars so to access it from another will be needed to use getters.
        cout << "Identifier: " << identifier << endl;
        cout << "Year: " << year << endl;
        cout << "Brand: " << brand << endl;
        cout << "Model " << model << endl;

        // Display Engine details if available
        if (engine != nullptr) {
            cout << "Engine Details:" << endl;
            engine->getData();
        }
    }

    void setIdentifier(string id) { identifier = id; }
    string getIdentifier() const { return identifier; }

    void setYear(int y) { year = y; }
    int getYear() { return year; }

    void setBrand(string b) { brand = b; }
    string getBrand() const { return brand; }

    void setModel(string m) { model = m; }
    string getModel() const { return model; }

    void setEngine(Engine* e) {
        // Cleanup existing engine before assigning a new one
        delete engine;
        engine = e;
    }

    // // Method to validate identifier
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

    // Destructor to clean up the dynamically allocated Engine object
    ~Vehicle() {
        delete engine;
    }

    // Friend declaration to allow Engine class access to private members
    friend class Engine;
};

int main() {
    // Testing with data insertion.
    int numCars;
    cout << "How much cars do you want to add?" << endl;
    cin >> numCars;

    vector<Vehicle> newVehicles = UserInput::createVehicle(numCars);

    // Display information for each vehicle
    for (const auto& vehicle : newVehicles) {
        vehicle.getData();
        cout << endl;
    }

    // Example usage
    // Vehicle car1("3012345678908", 2022, "Toyota", "Camry");
    // Vehicle car2("3123456789354", 2023, "Honda", "Accord");
    // car2.getData();

    // Validate identifiers
    // if (car1.validateIdentifier()) {
    //     cout << "Car 1 identifier is valid." << endl;
    // } else {
    //     cout << "Car 1 identifier is invalid." << endl;
    // }

    return 0;
}