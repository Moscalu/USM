#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;
using DataCalendaristica = struct tm;

enum class TipTranzactie {Suplinire, Extragere, Transfer};

class Tranzactie {
private:
    TipTranzactie tipTranzactie;
    double suma;
    string data;
public:
    Tranzactie(TipTranzactie tip, double suma) : tipTranzactie(tip), suma(suma) {
        time_t currentTime = time(nullptr);
        tm* localTime = localtime(&currentTime);
        char buffer[80];
        strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", localTime);
        data = string(buffer);
    }

    TipTranzactie getTipTranzactie() const {return tipTranzactie;}
    double getSuma() const {return suma;}
    string getData() const {return data;}
};

// Base class CardBancar
class CardBancar {
protected:
    string numarCard;
    string numeProprietar;
    DataCalendaristica dataExpirarii;
    double soldCont;
    vector<Tranzactie> istoricTranzactiiList;
public:
    CardBancar(const string& numarCard, const string& numeProprietar, 
               double soldCont, const DataCalendaristica& dataExpirarii) 
        : numarCard(numarCard), numeProprietar(numeProprietar), 
          dataExpirarii(dataExpirarii), soldCont(soldCont) {}

    string getNumarCard() const {return numarCard;}
    string getNumeProprietar() const {return numeProprietar;}
    DataCalendaristica getDataExpirarii() const {return dataExpirarii;}
    double getSoldCont() const {return soldCont;}

    void setSoldCont(double newSoldCont) {soldCont = newSoldCont;}
    void setDataExpirarii(DataCalendaristica newDataExpirarii) {dataExpirarii = newDataExpirarii;}
    void setNumarCard(string newNumarCard) {numarCard = newNumarCard;}
    void setNumeProprietar(string newNumeProprietar) {numeProprietar = newNumeProprietar;}

    void afiseazaafiseazaMiniExtras() const {
        cout << "Card Details:\n";
        cout << "Numar Card: " << numarCard << endl;
        cout << "Nume Proprietar: " << numeProprietar << endl;
        cout << "Data Expirarii: " << (dataExpirarii.tm_mday) << "/" << dataExpirarii.tm_mon << "/" << dataExpirarii.tm_year << endl;
        cout << "Sold Cont: " << soldCont << endl;
    }

    void afiseazaIstoricTranzactii() const {
        cout << "Transaction History:\n";
        for (const auto& transaction : istoricTranzactiiList) {
            string transactionType;
            switch (transaction.getTipTranzactie()) {
                case TipTranzactie::Suplinire:
                    transactionType = "Suplinire";
                    break;
                case TipTranzactie::Extragere:
                    transactionType = "Extragere";
                    break;
                case TipTranzactie::Transfer:
                    transactionType = "Transfer";
                    break;
            }
            cout << "Tip: " << transactionType << ", Suma: " << transaction.getSuma() 
                      << ", Data: " << transaction.getData() << endl;
        }
    }

    // Method to add transaction to history
    void adaugaTranzactie(Tranzactie tranzactie) {
        istoricTranzactiiList.push_back(tranzactie);
    }

    // Method to perform withdrawal
    virtual void extrageBani(double suma, TipTranzactie tip) {
        // Method implementation to perform withdrawal
    }

    // Method to perform replenishment
    virtual void suplimenteazaCont(double suma, TipTranzactie tip) {
        // Method implementation to perform replenishment
    }
};

// Derived class CardDebit
class CardDebit : public CardBancar {
private:
    double limitaExtragereZilnica;
public:
    // Constructor
    CardDebit(const string& numarCard, const string& numeProprietar, 
              const DataCalendaristica& dataExpirarii, double soldCont, double limita)
        : CardBancar(numarCard, numeProprietar, soldCont, dataExpirarii), 
          limitaExtragereZilnica(limita) {}

    // Method to perform withdrawal with daily limit check
    void extrageBani(double suma, TipTranzactie tip) override {
        // Perform withdrawal
        soldCont -= suma;
        // Add transaction to history
        adaugaTranzactie(Tranzactie(tip, suma));
    }
};

// Derived class CardCredit
class CardCredit : public CardBancar {
private:
    double limitaCredit;

public:
    // Constructor
    CardCredit(const string& numarCard, const string& numeProprietar, 
               const DataCalendaristica& dataExpirarii, double soldCont, double limita)
        : CardBancar(numarCard, numeProprietar, soldCont, dataExpirarii), 
          limitaCredit(limita) {}

    // Method to perform withdrawal with credit limit check and commission for ATM withdrawals
    void extrageBani(double suma, TipTranzactie tip) override {
        // Apply commission for ATM withdrawals
        if (tip == TipTranzactie::Extragere) {
            suma *= 1.02; // Apply 2% commission
        }
        // Perform withdrawal
        soldCont -= suma;
        // Add transaction to history
        adaugaTranzactie(Tranzactie(tip, suma));
    }
};

// Owner class
class Proprietar {
private:
    vector<CardBancar*> listaCarduri;
public:
    // Method to add card to owner's list
    void adaugaCard(CardBancar* card) {
        listaCarduri.push_back(card);
    }

    // Method to perform transaction (replenishment, withdrawal, transfer)
    void efectueazaTranzactie(CardBancar* card, double suma, TipTranzactie tip) {
        if (tip == TipTranzactie::Suplinire) {
            card->suplimenteazaCont(suma, tip);
        } else {
            card->extrageBani(suma, tip);
        }
    }

    // Method to display mini statement for a specific card
    void afiseazaafiseazaMiniExtras(CardBancar* card) {
        card->afiseazaafiseazaMiniExtras();
    }

    // Method to display transaction history for a specific card
    void afiseazaIstoricTranzactii(CardBancar* card) {
        card->afiseazaIstoricTranzactii();
    }

    // Method to display mini statement and transaction history for all cards
    void afiseazaToateCardurile() {
        for (const auto& card : listaCarduri) {
            card->afiseazaafiseazaMiniExtras();
            card->afiseazaIstoricTranzactii();
        }
    }
};

int main() {
    // // Create cards for testing
    // CardDebit cardDebit("1234567890123456", "John Doe", "2024-12-31", 5000.0, 1000.0);
    // CardCredit cardCredit("9876543210987654", "Jane Smith", "2025-12-31", 2000.0, 5000.0);

    DataCalendaristica expDate = {};
    expDate.tm_mday = 31; // Ziua
    expDate.tm_mon = 11; // Luna (0-11, deci 11 = Decembrie)
    expDate.tm_year = 125; // Anul de la 1900 (125 + 1900 = 2025)

    CardBancar card ("476583456743", "Vica Popa", 5000, expDate);
    card.afiseazaMiniExtras();

    // Crearea unui card de debit
    CardDebit cardDebit("1234567890", "Ion Popescu", 1500.0, expDate, 2000.0);
    cardDebit.afiseazaMiniExtras();

    // Crearea unui card de credit
    CardCredit cardCredit("0987654321", "Ana Ionescu", 500.0, expDate, 5000.0);
    cardCredit.afiseazaMiniExtras();

    // Simulăm efectuarea unei tranzacții pentru fiecare card
    cout << "\nEfectuăm o tranzacție de debit...\n";
    cardDebit.Tranzactie(depune,100.0);
    cardDebit.afiseazaMiniExtras();

    cout << "\nEfectuăm o tranzacție de credit...\n";
    cardCredit.Tranzactie(extrage,300.0);
    cardCredit.afiseazaMiniExtras();
    
    cout<< "\nEfectuăm un transfer de pe Debit pe Credit...\n";
    cardDebit.Tranzactie(transfera, 300.0, &cardCredit);
    cardDebit.afiseazaMiniExtras();
    cardCredit.afiseazaMiniExtras();
    // // Create owner and add cards
    // Proprietar owner;
    // owner.adaugaCard(&cardDebit);
    // owner.adaugaCard(&cardCredit);

    // // Test transactions
    // owner.efectueazaTranzactie(&cardDebit, 500.0, TipTranzactie::Extragere);
    // owner.efectueazaTranzactie(&cardCredit, 1000.0, TipTranzactie::Extragere);

    // // Display mini statement and transaction history for all cards
    // owner.afiseazaToateCardurile();

    return 0;
}


    // DataCalendaristica expDate = {};
    // expDate.tm_mday = 31; // Ziua
    // expDate.tm_mon = 11; // Luna (0-11, deci 11 = Decembrie)
    // expDate.tm_year = 125; // Anul de la 1900 (125 + 1900 = 2025)

    // CardBancar card ("476583456743", "Vica Popa", 5000, expDate);
    // card.afiseazaMiniExtras();


// Develop a program to manage the bank cards of an individual.

// The program will contain the following classes:

// 1. Base Class CardBancar:

//     Common attributes for all cards: număr card, nume proprietar, data expirării, sold cont 

//     Common methods: 
//          constructor
//          getters and setters for attributes
//          afiseazaafiseazaMiniExtras() to display the current balance and card details
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