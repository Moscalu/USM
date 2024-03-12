/* 1. Lab
    Elaborati clasa Vehicul - serie nr care sa contina un identificator(exemplu mai sus), important e sa fie unic.
    --> Sa contina cel putin 3 caracteristici(an, brand, model)
    --> Sa contina cel putin un constructor(implicit, cu parametri, de copiere)
    --> Sa contina metode de setare (set, get) metoda de validare a identificatorului

    --> Exemplificati utilizarea clasei prin creearea mai multor obiecte, validarea identificatorilor si apelul metodelor.
        algoritmul de validare a IDNV(incepe cu 3 si ultima cifra de control)
*/

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
    // Constructor
    Vehicle(string id, int y, string b, string m) : identifier(id), year(y), brand(b), model(m) {}

    // Getters and setters
    void setIdentifier(string id) { identifier = id; }
    string getIdentifier() const { return identifier; }

    void setYear(int y) { year = y; }
    int getYear() const { return year; }

    void setBrand(string b) { brand = b; }
    string getBrand() const { return brand; }

    void setModel(string m) { model = m; }
    string getModel() const { return model; }

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
    string carInput;

    cout << "Please input the data about a new car: " << endl;
    cin >> carInput;

    // Example usage
    Vehicle car1("3012345678908", 2022, "Toyota", "Camry");
    Vehicle car2("3123456789354", 2023, "Honda", "Accord");

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

    

    return 0;
}