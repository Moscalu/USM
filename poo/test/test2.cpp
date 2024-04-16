#include <iostream>
#include <vector>
#include <string>
#include <cmath> // pentru functia fmod
using namespace std;

enum class TipTranzactie { Suplinire, Extragere, Transfer };

// transaction class
class Tranzactie {
private:
    TipTranzactie tip;
    double suma;
    string data;

public:
    Tranzactie(TipTranzactie tip, double suma, const string& data) : tip(tip), suma(suma), data(data) {}

    TipTranzactie getTipTranzactie() const {return tip;}
    double getSuma() const {return suma;}
    string getData() const {return data;}
};

// base class CardBancar
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

    void afiseazaMiniExtras() const {cout << "Card Details:\n";
        cout << "Numar Card: " << numarCard << endl;
        cout << "Nume Proprietar: " << numeProprietar << endl;
        cout << "Data Expirarii: " << dataExpirarii << endl;
        cout << "Sold Cont: " << soldCont << endl;
    }

    void afiseazaIstoricTranzactii() const {cout << "Transaction History:\n";
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

    void adaugaTranzactie(Tranzactie tranzactie) {
        istoricTranzactiiList.push_back(tranzactie);
    }

    virtual void extrageBani(double suma, TipTranzactie tip) {
        if (tip == TipTranzactie::Extragere) {
            // controleaza daca suma este divizibila la 10 pentru extrageri de la bankomat
            if (suma >= 10 && fmod(suma, 10) == 0) { // utilizarea functiei fmod
                if (soldCont >= suma) {
                    soldCont -= suma;
                    adaugaTranzactie(Tranzactie(TipTranzactie::Extragere, suma, "Today"));
                    cout << "Extragere reusita!\n";
                } else {
                    cout << "Fonduri insuficiente!\n";
                }
            } else {
                cout << "Extragerea trebuie sa fie multiplu de 10!\n";
            }
        }
    }

    virtual void transferaBani(CardBancar* destinatie, double suma) {
        if (soldCont >= suma) {
            soldCont -= suma;
            destinatie->soldCont += suma;
            adaugaTranzactie(Tranzactie(TipTranzactie::Transfer, suma, "Today"));
            std::cout << "Transfer reusit!\n";
        } else {
            std::cout << "Fonduri insuficiente pentru transfer!\n";
        }
    }

    virtual void suplimenteazaCont(double suma, TipTranzactie tip) {
        if ((tip == TipTranzactie::Suplinire || tip == TipTranzactie::Transfer) && suma >= 10 && std::fmod(suma, 10) == 0) {
            soldCont += suma;
            adaugaTranzactie(Tranzactie(TipTranzactie::Suplinire, suma, "Today"));
            std::cout << "Suplimentare reusita!\n";
        } else {
            std::cout << "Suma de suplimentare trebuie sa fie multiplu de 10!\n";
        }
    }
};

// Derived class CardDebit
class CardDebit : public CardBancar {
private:
    double limitaExtragereZilnica;
public:
    CardDebit(const string& numarCard, const string& numeProprietar,
              const string& dataExpirarii, double soldCont, double limitaExtragereZilnica) : CardBancar(numarCard, numeProprietar, dataExpirarii, soldCont), limitaExtragereZilnica(limitaExtragereZilnica) {}

    void extrageBani(double suma, TipTranzactie tip) override {
        if (tip == TipTranzactie::Extragere) {
            if (suma >= 10 && fmod(suma, 10) == 0) { // Use fmod
                if (soldCont >= suma && suma <= limitaExtragereZilnica) {
                    soldCont -= suma;
                    adaugaTranzactie(Tranzactie(TipTranzactie::Extragere, suma, "Today"));
                    cout << "Extragere reusita!\n";
                } else {
                    cout << "Suma depaseste limita de extragere zilnica sau fonduri insuficiente!\n";
                }
            } else {
                cout << "Extragerea trebuie sa fie multiplu de 10!\n";
            }
        } else {
            CardBancar::extrageBani(suma, tip);
        }
    }
};

class CardCredit : public CardBancar {
private:
    double limitaCredit;
public:
    CardCredit(const string& numarCard, const string& numeProprietar,
               const string& dataExpirarii, double soldCont, double limitaCredit) : CardBancar(numarCard, numeProprietar, dataExpirarii, soldCont), limitaCredit(limitaCredit) {}

    void extrageBani(double suma, TipTranzactie tip) override {
        if (tip == TipTranzactie::Extragere) {
            if (soldCont + limitaCredit >= suma) {
                soldCont -= suma;
                adaugaTranzactie(Tranzactie(TipTranzactie::Extragere, suma, "Today"));
                cout << "Extragere reusita!\n";
            } else {
                cout << "Suma depaseste limita de credit!\n";
            }
        } else {
            CardBancar::extrageBani(suma, tip);
        }
    }
};

class Proprietar {
private:
    vector<CardBancar*> listaCarduri;
public:
    void adaugaCard(CardBancar* card) {listaCarduri.push_back(card);}

    void efectueazaTranzactie(CardBancar* card, double suma, TipTranzactie tip) {card->extrageBani(suma, tip);}

    void afiseazaMiniExtras(CardBancar* card) const {card->afiseazaMiniExtras();}

    void afiseazaIstoricTranzactii(CardBancar* card) const {card->afiseazaIstoricTranzactii();}

    void afiseazaToateCardurile() const {for (const auto& card : listaCarduri) {
            card->afiseazaMiniExtras();
            card->afiseazaIstoricTranzactii();
        }
    }
};

int main() {
    Proprietar daniel;

    CardDebit cardDebit("1234567890123456", "Moscalu Daniel", "12/24", 1000.0, 500.0);
    CardCredit cardCredit("9876543210987654", "Moscalu Daniel", "06/25", 2000.0, 1000.0);

    daniel.adaugaCard(&cardDebit);
    daniel.adaugaCard(&cardCredit);

    daniel.afiseazaToateCardurile();

    daniel.efectueazaTranzactie(&cardDebit, 200.0, TipTranzactie::Transfer);
    daniel.efectueazaTranzactie(&cardCredit, 500.0, TipTranzactie::Extragere);

    daniel.afiseazaToateCardurile();

    return 0;
}
