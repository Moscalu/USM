#include <iostream>
#include <string> 
#include <vector>
using namespace std;

enum TipTranzactie {
    extrage,
    depune  
};

class CardBancar {
    protected:
        string nrCard;
        string titular;
        string dataExipirarii;
        float sold;
    public:
    CardBancar(string nrCard, string titular,string dataExipirarii, float sold) {
        this->nrCard = nrCard;
        this->titular = titular;
        this->dataExipirarii = dataExipirarii;
        this->sold = sold;
    }

    string GetNrCard() {return nrCard;}
    string GetTitular() {return titular;}
    string GetDataExpirarii() {return dataExipirarii;}
    float GetSold() {return sold;}

    void Tranzactie(float suma, TipTranzactie tipTranzactie) {
        if(tipTranzactie== extrage) {
            sold -= suma;
        }

        if(tipTranzactie==depune) {
            sold += suma;
        }
    }

    void MiniExtaras() {
        cout << "********************" << endl;
        cout << "Numarul cardului: " << nrCard <<endl;
        cout << "Titular: " << titular <<endl;
        cout << "Data expirarii: " << dataExipirarii <<endl;
        cout << "Soldul: " << sold <<endl;
        cout << "********************" << endl;
    }
};

class CardCredit: public CardBancar {
    private:
        float limita;
    public:
        CardCredit(string nrCard, string titular,string dataExipirarii, float sold, float l):CardBancar(nrCard, titular, dataExipirarii, sold),limita(l) {}

        void Tranzactie(float suma, TipTranzactie tipTranzactie) {
        if((tipTranzactie == extrage) && (suma<=limita)) {
            sold -= suma;
        } else {
            cout << "Suma depaseste limita" << endl;
        }

        if(tipTranzactie==depune) {
            sold += suma;
        }
    }
};

class ContBancar{
    private:
        string titular;
        string iban;
        float sold;
        vector<CardBancar*> carduri;
    public:
        ContBancar(string t, string i, float s):titular(t), iban(i), sold(s) {}

        string GetTitular() {return titular;}
        string GetIban() {return iban;}
        float GetSold() {return sold;} 

        void AddCard(string nrCard,string dataExipirarii){
            CardBancar* pCard = new CardBancar(nrCard, titular, dataExipirarii, sold);
            carduri.push_back(pCard);
        }

        void AddCardCredit(string nrCard,string dataExipirarii, float limita) {
            CardCredit* pCard = new CardCredit(nrCard, titular, dataExipirarii, sold, limita);
            carduri.push_back(pCard);
        }

        void Informatii() {
            cout << "Titular: " << titular << endl;
            cout << "Iban: " << iban << endl;
            cout << "Carduri: " << endl;
            cout << "========================================" << endl;
            for(auto & card: carduri){
                card->MiniExtaras();
            }
            cout << "========================================" << endl;
        }

        void Tranzactie(string nrCard, TipTranzactie tip, float suma) {
            for(CardBancar* card: carduri) {
                if(card->GetNrCard()==nrCard) {
                    card->Tranzactie(suma, tip);
                }
            }
        }

        ~ContBancar() {
            for(CardBancar* card: carduri) {
                if(card!=NULL) {
                    delete card;
                }
                
            }

            carduri.clear();
        }

};
int main(){
    ContBancar c1("Lupu Nicu", "MD242354h", 3000);
    c1.AddCard("4111158362643567", "10/24");
    c1.AddCard("5374038456045064", "12/28");
    c1.AddCardCredit("4534567892345", "01/33", 1000);
    c1.Informatii();
    cout << endl;
    c1.Tranzactie("4534567892345", depune, 100);
    c1.Tranzactie("4534567892345", extrage, 5000);
    c1.Tranzactie("4111158362643567", extrage, 300);
    c1.Tranzactie("5374038456045064", depune, 400);
    c1.Informatii();
    cout << endl;
    
    return 0;
}