#include <iostream>
#include <string>
using namespace std;

class Vehicle {
private:
    string identifier;
    int year;
    string brand;
    string model;

public:
    //string id;
    // Constructors
    Vehicle(string id, int y, string b, string m) : identifier(id), year(y), brand(b), model(m) {}
    // Vehicle(string indentifier, int year, string brand, string model) : identifier(identifier), year(year), brand(brand), model(model) {}
    // Vehicle() : identifier(""), year(0), brand(""), model("") {}
    // Vehicle(const Vehicle& other) : identifier(other.identifier), year(other.year), brand(other.brand), model(other.model) {}

    // Note that const is used just to let developers to know that this method will not modify any variables. Also an important note is that the compiler
    // will return an error if the method will change any variables.
    void getData() {
        // Note that inside the same class I can access private vars so to access it from another will be needed to use getters.
        cout << "Identifier: " << identifier << endl;
        cout << "Year: " << year << endl;
        cout << "Brand: " << brand << endl;
        cout << "Model " << model << endl;
    }

    void setIdentifier(string id) { identifier = id; }
    string getIdentifier() const { return identifier; }

    void setYear(int y) { year = y; }
    int getYear() { return year; }

    void setBrand(string b) { brand = b; }
    string getBrand() const { return brand; }

    void setModel(string m) { model = m; }
    string getModel() const { return model; }

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
};

class UserInput {
public:
    static Vehicle createVehicle() {
        string id, b, m;
        int y, c;

        // cout << "How much cars do you want to add?";
        // cin >> c;
        cout << "Enter please the ID of the car: "; 
        cin >> id;
        cout << "Enter please the Year of the car: ";
        cin >> y;
        cout << "Enter please the Brand of the car: ";
        cin >> b;
        cout << "Enter please the Model of the car: ";
        cin >> m;
    
         return Vehicle(id, y, b, m);
    }
};

int main() {
    // Testing with data insertion.
    int counter;
    cout << "How much cars do you want to add?" << endl;
    cin >> counter;

    for (int i = 0; i <= counter; i++) {
        Vehicle car = UserInput::createVehicle();
    }

    // Vehicle newVehicle = UserInput::createVehicle();
    // newVehicle.getData();

    // Vehicle car1("3012345678908", 2022, "Toyota", "Camry");
    // car1.getData();

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