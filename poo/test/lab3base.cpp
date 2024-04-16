#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

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
    string dataExpirarii;
    double soldCont;
    vector<Tranzactie> istoricTranzactiiList;
public:
    CardBancar(const string& numarCard, const string& numeProprietar, 
               const string& dataExpirarii, double soldCont) 
        : numarCard(numarCard), numeProprietar(numeProprietar), 
          dataExpirarii(dataExpirarii), soldCont(soldCont) {}

    string getNumarCard() const {return numarCard;}
    string getNumeProprietar() const {return numeProprietar;}
    string getDataExpirarii() const {return dataExpirarii;}
    double getSoldCont() const {return soldCont;}

    void setSoldCont(double newSoldCont) {soldCont = newSoldCont;}

    void afiseazaMiniExtras() const {
        cout << "Card Details:\n";
        cout << "Numar Card: " << numarCard << endl;
        cout << "Nume Proprietar: " << numeProprietar << endl;
        cout << "Data Expirarii: " << dataExpirarii << endl;
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
              const string& dataExpirarii, double soldCont, double limita)
        : CardBancar(numarCard, numeProprietar, dataExpirarii, soldCont), 
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
               const string& dataExpirarii, double soldCont, double limita)
        : CardBancar(numarCard, numeProprietar, dataExpirarii, soldCont), 
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
    void afiseazaMiniExtras(CardBancar* card) {
        card->afiseazaMiniExtras();
    }

    // Method to display transaction history for a specific card
    void afiseazaIstoricTranzactii(CardBancar* card) {
        card->afiseazaIstoricTranzactii();
    }

    // Method to display mini statement and transaction history for all cards
    void afiseazaToateCardurile() {
        for (const auto& card : listaCarduri) {
            card->afiseazaMiniExtras();
            card->afiseazaIstoricTranzactii();
        }
    }
};

int main() {
    // Create cards for testing
    CardDebit cardDebit("1234567890123456", "John Doe", "2024-12-31", 5000.0, 1000.0);
    CardCredit cardCredit("9876543210987654", "Jane Smith", "2025-12-31", 2000.0, 5000.0);

    // Create owner and add cards
    Proprietar owner;
    owner.adaugaCard(&cardDebit);
    owner.adaugaCard(&cardCredit);

    // Test transactions
    owner.efectueazaTranzactie(&cardDebit, 500.0, TipTranzactie::Extragere);
    owner.efectueazaTranzactie(&cardCredit, 1000.0, TipTranzactie::Extragere);

    // Display mini statement and transaction history for all cards
    owner.afiseazaToateCardurile();

    return 0;
}
