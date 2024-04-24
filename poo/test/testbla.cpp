#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <iomanip>

using namespace std;

using DataCalendaristica = struct tm;

enum TipTranzactie {
    depunere,
    extragere,
    transfer
};

class Tranzactie {
public:
    TipTranzactie tip;
    double suma;
    DataCalendaristica data;

    Tranzactie(TipTranzactie tip, double suma, const DataCalendaristica& data) : tip(tip), suma(suma), data(data) {}
};

class CardBancar {
protected:
    string numarCard;
    string numeProprietar;
    double sold;
    DataCalendaristica dataExpirarii;
    vector<Tranzactie> istoric;

public:
    CardBancar(const string& numarCard, const string& numeProprietar, double sold, const DataCalendaristica& dataExpirarii)
    : numarCard(numarCard), numeProprietar(numeProprietar), sold(sold), dataExpirarii(dataExpirarii) {}

    virtual void MiniExtras() const {
        cout << "Numar Card: " << numarCard << "\nNume Proprietar: " << numeProprietar << "\nSold: "  << sold
             << "\nData Expirarii: " << dataExpirarii.tm_mday << "/" << (dataExpirarii.tm_mon + 1) << "/" << (dataExpirarii.tm_year + 1900) << endl;
    }

    virtual void efectueazaTranzactie(TipTranzactie tip, double suma, CardBancar* destinatie = nullptr) {}

protected:
    void adaugaTranzactie(TipTranzactie tip, double suma) {
        time_t t = time(0);
        DataCalendaristica tm = *localtime(&t);
        istoric.push_back(Tranzactie(tip, suma, tm));
        if (tip == depunere) {
            sold += suma;
        } else if (tip == extragere) {
            sold -= suma;
        }
    }
};

class CardDebit : public CardBancar {
    double limitaZilnica;

public:
    CardDebit(const string& numarCard, const string& numeProprietar, double sold, const DataCalendaristica& dataExpirarii, double limitaZilnica)
    : CardBancar(numarCard, numeProprietar, sold, dataExpirarii), limitaZilnica(limitaZilnica) {}

    void MiniExtras() const override {
        CardBancar::MiniExtras();
        cout << "Limita de extragere: "  << limitaZilnica << " lei.\n";
    }

    void efectueazaTranzactie(TipTranzactie tip, double suma, CardBancar* destinatie = nullptr) override {
        if (tip == depunere || (tip == extragere && suma <= limitaZilnica && suma <= sold)) {
            adaugaTranzactie(tip, suma);
        } else if (tip == transfer && suma <= sold && destinatie != nullptr) {
            if (suma > limitaZilnica) {
                cout << "Suma depaseste limita de extragere: " << limitaZilnica << "\n";
                return;
            }
            adaugaTranzactie(extragere, suma);
            destinatie->efectueazaTranzactie(depunere, suma);
        } else {
            cout << "Tranzactie nereusita!" << endl;
        }
    }
};

class CardCredit : public CardBancar {
    double limitaCredit;

public:
    CardCredit(const string& numarCard, const string& numeProprietar, double sold, const DataCalendaristica& dataExpirarii, double limitaCredit)
    : CardBancar(numarCard, numeProprietar, sold, dataExpirarii), limitaCredit(limitaCredit) {}

    void MiniExtras() const override {
        CardBancar::MiniExtras();
        cout << "Limita de credit: "  << limitaCredit << " lei.\n";
    }

    void efectueazaTranzactie(TipTranzactie tip, double suma, CardBancar* destinatie = nullptr) override {
        if (tip == depunere) {
            adaugaTranzactie(tip, suma);
        } else if (tip == extragere && (sold + limitaCredit >= suma)) {
            adaugaTranzactie(tip, suma);
        } else {
            cout << "Tranzactie nereusita!" << endl;
        }
    }
};

void Exemplu1() {
    DataCalendaristica expDate = {};
    expDate.tm_mday = 31; // Ziua
    expDate.tm_mon = 11; // Luna (0-11, deci 11 = Decembrie)
    expDate.tm_year = 125; // Anul de la 1900 (125 + 1900 = 2025)

    CardBancar card ("476583456743", "Vica Popa", 5000, expDate);
    card.MiniExtras();
}

void Exemplu2() {
    // Exemplu de utilizare
    // Crearea și inițializarea struct tm pentru data de expirare
    DataCalendaristica expDate = {};
    expDate.tm_mday = 31; // Ziua
    expDate.tm_mon = 11; // Luna (0-11, deci 11 = Decembrie)
    expDate.tm_year = 125; // Anul de la 1900 (125 + 1900 = 2025)

    // Crearea unui card de debit
    CardDebit cardDebit("1234567890", "Ion Popescu", 3500.0, expDate, 2000.0);
    cardDebit.MiniExtras();

    // Crearea unui card de credit
    CardCredit cardCredit("0987654321", "Ana Ionescu", 500.0, expDate, 5000.0);
    cardCredit.MiniExtras();

    // Simulăm efectuarea unei tranzacții pentru fiecare card
    cout << "\nEfectuăm o tranzacție de debit...\n";
    cardDebit.efectueazaTranzactie(depunere,100.0);
    cardDebit.MiniExtras();

    cout << "\nEfectuăm o tranzacție de credit...\n";
    cardCredit.efectueazaTranzactie(extragere,300.0);
    cardCredit.MiniExtras();
    
    cout<< "\nEfectuăm un transfer de pe Debit pe Credit...\n";
    cardDebit.efectueazaTranzactie(transfer, 2300.0, &cardCredit);
    cardDebit.MiniExtras();
    cardCredit.MiniExtras();
}

int main() {
    Exemplu1();
    Exemplu2();
    return 0;
}
