#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

enum class TipulTranzactiei {
    suplinire,
    extragere,
    transfer
};

class Tranzactie {
private:
    TipulTranzactiei tipTranzactie;
    double suma;
    string data;
public:
    Tranzactie(TipulTranzactiei tip, double suma) : tipTranzactie(tip), suma(suma) {
        time_t timpulCurent = time(nullptr);
        tm* timpulLocal = localtime(&timpulCurent);

        char buffer[80];
        strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timpulLocal);
        data = string(buffer);
    }

    string getData() {return data;}

};

class CardBancar {
private:
    double soldCont;
    string numarCard;
    string numeProprietar;
    string dataExpirarii;
public:
    CardBancar(string numar, string nume, string data) : numarCard(numar), numeProprietar(nume), dataExpirarii(data) { setDataExpirarii(); }

    void setDataExpirarii() {
        time_t timpulCurent = time(nullptr);
        tm* timpulLocal = localtime(&timpulCurent);
        timpulLocal->tm_year += 4;
        mktime(timpulLocal); // Normalizarea formatarii timpului pentru ca sa ne asiguram ca 1. Anul sa nu depaseasca limita valida sau sa devina invalida din cauza unui an bisect 2. Sumarea nu ia in consideratie anii bisecti 3. Validarea
        char buffer[80];
        strftime(buffer, 80, "%m/%y", timpulLocal);
        dataExpirarii = string(buffer);
    }

    void setNumeProprietar() {}
    void setNumarCard() {}

    string getNumarCard() {return numarCard;}
    string getNumeProprietar() {return numeProprietar;}
    string getDataExpirarii() {return dataExpirarii;}

    void afiseazaMiniExtras() {

    }

    void afiseazaTranzactii() {

    }
    
};

class CardDebit {

};

class CardCredit {

};

class Proprietar {

};

int main() {

    CardBancar newcard("11111", "Moscalu", "05/24");
    Tranzactie newtranzaction(TipulTranzactiei::suplinire, 200);

    cout << newtranzaction.getData() << endl;

    cout << newcard.getDataExpirarii() << endl;

    return 0;
}


// Develop a program to manage the bank cards of an individual.

// The program will contain the following classes:

// 1. Base Class CardBancar:

//     Common attributes for all cards: număr card, nume proprietar, data expirării, sold cont 

//     Common methods: 
//          constructor
//          getters and setters for attributes
//          afiseazaMiniExtras() to display the current balance and card details
//          istoricTranzactii() to display the transaction history
//     There will be 4 withdrawal modes: Bancomat, Bancă, Terminal, Transfer

//     There will be 3 account replenishment modes: Bancomat, Bancă, Transfer
//          ! Withdrawals and replenishments via ATM will only be possible for amounts divisible by 10.

// 2. Derived Class CardDebit:

//     Additional attribute: limita de extragere zilnică
//          daily withdrawal limit
//     Implement specific methods for managing withdrawals, respecting the withdrawal limit.

// 3. Derived Class CardCredit:

//     Additional attribute: limita de credit
//          credit limit
//     Implement specific methods for transactions, allowing the account balance to be exceeded up to the credit limit.
//     If the withdrawal is made through an ATM, a 2% commission will be applied to the withdrawn amount.

// 4. Owner Class:

//     Attributes: lista de carduri
//          list of cards (debit and credit).
//     Methods:
//          add card
//          perform transaction (replenishment, withdrawal, transfer between own cards)
//          display mini statement and transaction history for a specific card or all cards

// 5. Transaction Class:

//     Attributes: tip tranzactie (suplinire, extragere, transfer), suma, data
//          transaction type (replenishment, withdrawal, transfer)
//          amount
//          date
//     Methods:
//          constructor
//          getters
    
// Note: In C++, for the DataCalendaristica, you can use the "struct tm" type from the <ctime> library.

// Example:

// using DataCalendaristica = struct tm

// DataCalendaristica dataExp = {};
// dataExp.tm_mday = 31; // Day
// dataExp.tm_mon = 11; // Month (0-11, so 11 = December)
// dataExp.tm_year = 124; // Year since 1900 (124 + 1900 = 2024)