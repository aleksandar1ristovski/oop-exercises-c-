//
// Created by Aleksandar Ristovski on 28.5.26.
//
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

class Koncert {
    string naziv;
    string lokacija;
    float cena;
    static float popust;
public:
    Koncert() {}

    Koncert(string naziv,
            string lokacija,
            float cena) {
        this->naziv = naziv;
        this->lokacija = lokacija;
        this->cena = cena;
    }

    virtual float osnovnaCena() {
        return cena *(1- popust);
    }

    string getNaziv() {
        return naziv;
    }

    static float getSezonskiPopust(){
        return popust;
    }

    static void setSezonskiPopust(float p) {
        popust=p;
    }
};

float Koncert::popust = 0.20;

class ElektronskiKoncert : public Koncert {
    char *imeDJ;
    double vremetraenje;
    bool dnevna;
public:
    ElektronskiKoncert() {
        strcpy(imeDJ, "TOSO");
        vremetraenje = 0;
        dnevna = false;
    }

    ElektronskiKoncert(string naziv,
                       string lokacija,
                       float cena, char *imeDJ,
                       double vremetraenje,
                       bool dnevna) : Koncert(naziv, lokacija, cena) {
        this->imeDJ = new char[strlen(imeDJ)+1];
        strcpy(this->imeDJ, imeDJ);
        this->vremetraenje = vremetraenje;
        this->dnevna = dnevna;
    }

    ElektronskiKoncert(const ElektronskiKoncert &e) : Koncert(e) {
        this->imeDJ = new char[strlen(e.imeDJ)+1];
        strcpy(this->imeDJ, e.imeDJ);
        this->vremetraenje = e.vremetraenje;
        this->dnevna = e.dnevna;
    }

    ElektronskiKoncert &operator=(const ElektronskiKoncert &e) {
        if (this != &e) {
            Koncert::operator=(e);
            delete[] imeDJ;

            this->imeDJ = new char[strlen(e.imeDJ)+1];
            strcpy(this->imeDJ, e.imeDJ);
            this->vremetraenje = e.vremetraenje;
            this->dnevna = e.dnevna;
        }
        return *this;
    }

    float osnovnaCena() override {
        float momentalnaCena = Koncert::osnovnaCena();
        if (dnevna) {
            momentalnaCena -= 50;
        } else {
            momentalnaCena += 100;
        }
        if (vremetraenje > 7) {
            return momentalnaCena + 360;
        }
        if (vremetraenje > 5) {
            return momentalnaCena + 150;
        }
        return momentalnaCena;
    }
};

void najskapKoncert(Koncert **koncerti, int n) {
    int index = -1, max = 0;
    int counter = 0;
    for (int i = 0; i < n; i++) {
        ElektronskiKoncert *e = dynamic_cast<ElektronskiKoncert *>(koncerti[i]);
        if (e != nullptr) {
            counter++;
            if (koncerti[i]->osnovnaCena() > max) {
                max = koncerti[i]->osnovnaCena();
                index = i;
            }
        }
    }
    cout << "Najskap koncert: " << koncerti[index]->getNaziv() << " " << koncerti[index]->osnovnaCena() << endl;
    cout << "Elektronski koncerti: " << counter << " od vkupno " << n << endl;
    return;
}

bool prebarajKoncert(Koncert **koncerti, int n, char *naziv, bool elektronski) {
    if (elektronski) {
        for (int i = 0; i < n; i++) {
            ElektronskiKoncert *e = dynamic_cast<ElektronskiKoncert *>(koncerti[i]);
            if (e != nullptr && koncerti[i]->getNaziv() == naziv) {
                cout << koncerti[i]->getNaziv() << " " << koncerti[i]->osnovnaCena() << endl;
                return true;
            }
        }
        return false;
    }
    for (int i = 0; i < n; i++) {
        if (koncerti[i]->getNaziv() == naziv) {
            cout << koncerti[i]->getNaziv() << " " << koncerti[i]->osnovnaCena() << endl;
            return true;
        }
    }
    return false;
}

int main() {

    int tip, n, novaCena;
    char naziv[100], lokacija[100], imeDJ[40];
    bool dnevna;
    float cenaBilet, novPopust;
    float casovi;

    cin >> tip;
    if (tip == 1) {//Koncert
        cin >> naziv >> lokacija >> cenaBilet;
        Koncert k1(naziv, lokacija, cenaBilet);
        cout << "Kreiran e koncert so naziv: " << k1.getNaziv() << endl;
    } else if (tip == 2) {//cena - Koncert
        cin >> naziv >> lokacija >> cenaBilet;
        Koncert k1(naziv, lokacija, cenaBilet);
        cout << "Osnovna cena na koncertot so naziv " << k1.getNaziv() << " e: " << k1.osnovnaCena() << endl;
    } else if (tip == 3) {//ElektronskiKoncert
        cin >> naziv >> lokacija >> cenaBilet >> imeDJ >> casovi >> dnevna;
        ElektronskiKoncert s(naziv, lokacija, cenaBilet, imeDJ, casovi, dnevna);
        cout << "Kreiran e elektronski koncert so naziv " << s.getNaziv() << " i sezonskiPopust "
             << s.getSezonskiPopust() << endl;
    } else if (tip == 4) {//cena - ElektronskiKoncert
        cin >> naziv >> lokacija >> cenaBilet >> imeDJ >> casovi >> dnevna;
        ElektronskiKoncert s(naziv, lokacija, cenaBilet, imeDJ, casovi, dnevna);
        cout << "Cenata na elektronskiot koncert so naziv " << s.getNaziv() << " e: " << s.osnovnaCena() << endl;
    } else if (tip == 5) {//najskapKoncert

    } else if (tip == 6) {//prebarajKoncert
        Koncert **koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area", "BorisTrajkovski", 350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand", "Belgium", 8000, "Afrojack", 7.5, false);
        koncerti[2] = new ElektronskiKoncert("SeaDance", "Budva", 9100, "Tiesto", 5, true);
        koncerti[3] = new Koncert("Superhiks", "PlatoUkim", 100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso", "Mykonos", 8800, "Guetta", 3, true);
        char naziv[100];
        najskapKoncert(koncerti, 5);
    } else if (tip == 7) {//prebaraj
        Koncert **koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area", "BorisTrajkovski", 350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand", "Belgium", 8000, "Afrojack", 7.5, false);
        koncerti[2] = new ElektronskiKoncert("SeaDance", "Budva", 9100, "Tiesto", 5, true);
        koncerti[3] = new Koncert("Superhiks", "PlatoUkim", 100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso", "Mykonos", 8800, "Guetta", 3, true);
        char naziv[100];
        bool elektronski;
        cin >> elektronski;
        if (prebarajKoncert(koncerti, 5, "Area", elektronski))
            cout << "Pronajden" << endl;
        else cout << "Ne e pronajden" << endl;

        if (prebarajKoncert(koncerti, 5, "Area", !elektronski))
            cout << "Pronajden" << endl;
        else cout << "Ne e pronajden" << endl;

    } else if (tip == 8) {//smeni cena
        Koncert **koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area", "BorisTrajkovski", 350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand", "Belgium", 8000, "Afrojack", 7.5, false);
        koncerti[2] = new ElektronskiKoncert("SeaDance", "Budva", 9100, "Tiesto", 5, true);
        koncerti[3] = new Koncert("Superhiks", "PlatoUkim", 100);
        koncerti[2]->setSezonskiPopust(0.9);
        najskapKoncert(koncerti, 4);
    }

    return 0;
}
