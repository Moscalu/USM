#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>

using namespace std;

// Definirea tipului pentru data calendaristică
using DataCalendaristica = struct tm;

// Enumerație pentru tipurile de tranzacții
enum TipTranzactie { depune, extrage, transfera };

// Clasa de bază CardBancar
class CardBancar {
protected:
    string numarCard;
    string numeProprietar;
    DataCalendaristica dataExpirare;
    double soldCont;
    vector<string> istoricTranzactiiVect;

public:
    // Constructor
    CardBancar(string numarCard, string numeProprietar, double soldCont, DataCalendaristica dataExpirare)
        : numarCard(numarCard), numeProprietar(numeProprietar), soldCont(soldCont), dataExpirare(dataExpirare) {}

    // Gettere și settere
    string getNumarCard() const { return numarCard; }
    string getNumeProprietar() const { return numeProprietar; }
    double getSoldCont() const { return soldCont; }
    DataCalendaristica getDataExpirare() const { return dataExpirare; }
    
    void setSoldCont(double sold) { soldCont = sold; }

    // Metoda pentru afișarea miniextrasului
    void MiniExtras() const {
        cout << "Numar Card: " << numarCard << endl;
        cout << "Nume Proprietar: " << numeProprietar << endl;
        cout << "Sold: " << soldCont << endl;
        cout << "Data Expirarii: " << dataExpirare.tm_mday << "/" << dataExpirare.tm_mon + 1 << "/" << dataExpirare.tm_year + 1900 << endl;
    }

    // Metoda pentru afișarea istoricului tranzacțiilor
    void istoricTranzactii() const {
        cout << "Istoricul Tranzactiilor:\n";
        for (const auto& tranzactie : istoricTranzactiiVect) {
            cout << tranzactie << endl;
        }
    }

    // Metodă pentru efectuarea unei tranzacții
    virtual void Tranzactie(TipTranzactie tip, double suma, CardBancar* destinatie = nullptr) {
        // Implementarea acestei metode va fi specifică pentru fiecare clasă derivată
    }
};

// Clasa derivată CardDebit
class CardDebit : public CardBancar {
private:
    double limitaExtragereZilnica;

public:
    // Constructor
    CardDebit(string numarCard, string numeProprietar, double soldCont, DataCalendaristica dataExpirare, double limitaExtragereZilnica)
        : CardBancar(numarCard, numeProprietar, soldCont, dataExpirare), limitaExtragereZilnica(limitaExtragereZilnica) {}

    // Metoda pentru efectuarea unei tranzacții
    void Tranzactie(TipTranzactie tip, double suma, CardBancar* destinatie = nullptr) override {
        if (tip == extrage) {
            if (suma <= soldCont && suma <= limitaExtragereZilnica && fmod(suma, 10) == 0) {
                soldCont -= suma;
                istoricTranzactiiVect.push_back("Extragere: " + to_string(suma) + " lei");
            } else {
                cout << "Nu s-a putut efectua extragerea." << endl;
            }
        } else if (tip == depune) {
            if (suma > 0) {
                soldCont += suma;
                istoricTranzactiiVect.push_back("Depunere: " + to_string(suma) + " lei");
            } else {
                cout << "Nu s-a putut efectua depunerea." << endl;
            }
        }
    }
};

// Clasa derivată CardCredit
class CardCredit : public CardBancar {
private:
    double limitaCredit;

public:
    // Constructor
    CardCredit(string numarCard, string numeProprietar, double soldCont, DataCalendaristica dataExpirare, double limitaCredit)
        : CardBancar(numarCard, numeProprietar, soldCont, dataExpirare), limitaCredit(limitaCredit) {}

    // Metoda pentru efectuarea unei tranzacții
    void Tranzactie(TipTranzactie tip, double suma, CardBancar* destinatie = nullptr) override {
        if (tip == extrage) {
            if (suma <= soldCont + limitaCredit) {
                if (destinatie != nullptr) {
                    if (fmod(suma, 10) == 0) {
                        double comision = suma * 0.02;
                        if (comision > 0) {
                            suma += comision;
                        }
                        soldCont -= suma;
                        destinatie->setSoldCont(destinatie->getSoldCont() + suma);
                        istoricTranzactiiVect.push_back("Extragere (cu comision): " + to_string(suma) + " lei");
                    } else {
                        cout << "Suma trebuie să fie divizibilă cu 10 pentru extragerile prin bancomat." << endl;
                    }
                } else {
                    soldCont -= suma;
                    istoricTranzactiiVect.push_back("Extragere: " + to_string(suma) + " lei");
                }
            } else {
                cout << "Fonduri insuficiente." << endl;
            }
        } else if (tip == depune) {
            if (suma > 0) {
                soldCont += suma;
                istoricTranzactiiVect.push_back("Depunere: " + to_string(suma) + " lei");
            } else {
                cout << "Nu s-a putut efectua depunerea." << endl;
            }
        } else if (tip == transfera) {
            if (destinatie != nullptr && suma > 0 && suma <= soldCont + limitaCredit) {
                soldCont -= suma;
                destinatie->setSoldCont(destinatie->getSoldCont() + suma);
                istoricTranzactiiVect.push_back("Transfer către " + destinatie->getNumeProprietar() + ": " + to_string(suma) + " lei");
            } else {
                cout << "Transferul nu a putut fi efectuat." << endl;
            }
        }
    }
};

// Clasa Proprietar
class Proprietar {
private:
    vector<CardBancar*> listaCarduri;

public:
    // Metodă pentru adăugarea unui card la lista de carduri a proprietarului
    void adaugaCard(CardBancar* card) {
        listaCarduri.push_back(card);
    }

    // Metodă pentru efectuarea unei tranzacții
    void efectueazaTranzactie(CardBancar* card, TipTranzactie tip, double suma, CardBancar* destinatie = nullptr) {
        if (card != nullptr) {
            card->Tranzactie(tip, suma, destinatie);
        } else {
            cout << "Cardul nu există." << endl;
        }
    }

    // Metodă pentru afișarea miniextrasului pentru un anumit card
    void MiniExtras(CardBancar* card) const {
        if (card != nullptr) {
            card->MiniExtras();
        } else {
            cout << "Cardul nu există." << endl;
        }
    }

    // Metodă pentru afișarea miniextraselor pentru toate cardurile
    void MiniExtrasToateCardurile() const {
        for (const auto& card : listaCarduri) {
            card->MiniExtras();
            cout << endl;
        }
    }

    // Metodă pentru afișarea istoricului tranzacțiilor pentru un anumit card
    void afiseazaIstoricTranzactii(CardBancar* card) const {
        if (card != nullptr) {
            card->istoricTranzactii();
        } else {
            cout << "Cardul nu există." << endl;
        }
    }

    // Metodă pentru afișarea istoricului tranzacțiilor pentru toate cardurile
    void afiseazaIstoricTranzactiiToateCardurile() const {
        for (const auto& card : listaCarduri) {
            card->istoricTranzactii();
            cout << endl;
        }
    }
};

int main() {
    // DataCalendaristica expDate = {};
    // expDate.tm_mday = 31; // Ziua
    // expDate.tm_mon = 11; // Luna (0-11, deci 11 = Decembrie)
    // expDate.tm_year = 125; // Anul de la 1900 (125 + 1900 = 2025)

    // CardBancar card ("476583456743", "Vica Popa", 5000, expDate);
    // card.MiniExtras();
        // Exemplu de utilizare
    // Crearea și inițializarea struct tm pentru data de expirare
    DataCalendaristica expDate = {};
    expDate.tm_mday = 31; // Ziua
    expDate.tm_mon = 11; // Luna (0-11, deci 11 = Decembrie)
    expDate.tm_year = 125; // Anul de la 1900 (125 + 1900 = 2025)

    // Crearea unui card de debit
    CardDebit cardDebit("1234567890", "Ion Popescu", 1500.0, expDate, 2000.0);
    cardDebit.MiniExtras();

    // Crearea unui card de credit
    CardCredit cardCredit("0987654321", "Ana Ionescu", 500.0, expDate, 5000.0);
    cardCredit.MiniExtras();

    // Simulăm efectuarea unei tranzacții pentru fiecare card
    cout << "\nEfectuăm o tranzacție de debit...\n";
    cardDebit.Tranzactie(depune,100.0);
    cardDebit.MiniExtras();

    cout << "\nEfectuăm o tranzacție de credit...\n";
    cardCredit.Tranzactie(extrage,300.0);
    cardCredit.MiniExtras();
    
    cout<< "\nEfectuăm un transfer de pe Debit pe Credit...\n";
    cardDebit.Tranzactie(transfera, 300.0, &cardCredit);
    cardDebit.MiniExtras();
    cardCredit.MiniExtras();
    return 0;
}
