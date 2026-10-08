//
// Created by Aleksandar Ristovski on 20.5.26.
//
#include <iostream>
#include <cstring>

using namespace std;

class Library {
protected:
    string name;
    string city;
    int subscription;
    bool isOpenForWeekends;
public:
    Library(string n, string c, int s, bool i) {
        name = n;
        city = c;
        subscription = s;
        isOpenForWeekends = s;
    }

    virtual void printDetail() = 0;

    virtual double calculateMembershipCardCost() = 0;

    bool getIsOpen(){
        return isOpenForWeekends;
    }

};

class AcademicLibrary : public Library {
    bool isAllowedToExplore;
    int specialPieces;
public:
    AcademicLibrary(string n, string c, int s, bool i, bool isA, int SP) : Library(n, c, s, i) {
        isAllowedToExplore = isA;
        specialPieces = SP;
    }

    double calculateMembershipCardCost() override {
        if (isAllowedToExplore) return subscription * 1.24 + specialPieces * 6;
        return subscription + specialPieces * 6;
    }

    void printDetail() override {
        cout << name << " - " << "(Academic) " << city << " " << specialPieces << " " << calculateMembershipCardCost()
             << endl;
    }
};

class NationalLibrary : public Library {
    bool hasCultureEducation;
    int oldBooks;
public:
    NationalLibrary(string n, string c, int s, bool i, bool hasC, int OB) : Library(n, c, s, i) {
        hasCultureEducation = hasC;
        oldBooks = OB;
    }

    double calculateMembershipCardCost() override {
        if (hasCultureEducation) return subscription * 0.93 + oldBooks * 15;
        return subscription + oldBooks * 15;
    }

    void printDetail() override {
        cout << name << " - (National) " << city << " " << oldBooks << " " << calculateMembershipCardCost()<<endl;
    }
    bool getHasCultureEducation(){
        return hasCultureEducation;
    }
};

int findMostExpensiveNationalLibrary(Library **l, int n) {
    int max = 0;
    int maxIndex = -1;
    for (int i = 0; i < n; i++) {
        if (dynamic_cast<NationalLibrary *>(l[i])) {
            if (l[i]->calculateMembershipCardCost() > max) {
                max = l[i]->calculateMembershipCardCost();
                maxIndex = i;
            }
            if(l[i]->calculateMembershipCardCost() == max && l[i]->getIsOpen()){
                maxIndex = i;
            }
        }
    }
    if(max==0){
        return -1;
    }
    return maxIndex;
}

int main() {
    int n, testCase, type;
    cin >> testCase >> n;
    cin.ignore();

    Library** m = new Library*[n];

    for (int i = 0; i < n; ++i) {
        string name;
        string city;
        float base_price;
        bool weekend_working;

        cin >> type;
        cin.ignore();
        getline(cin, name);
        getline(cin, city);
        cin >> base_price;
        cin.ignore();
        cin >> weekend_working;
        cin.ignore();

        if (type == 1) {
            bool open_cooperation;
            int specialized_articles;

            cin >> open_cooperation >> specialized_articles;
            cin.ignore();

            m[i] = new AcademicLibrary(name, city, base_price, weekend_working, open_cooperation, specialized_articles);
        } else {
            bool cultural_program;
            int national_articles;

            cin >> cultural_program >> national_articles;
            cin.ignore();

            m[i] = new NationalLibrary(name, city, base_price, weekend_working, cultural_program, national_articles);
        }
    }

    if(testCase == 1){
        cout << "Abstract and child classes OK" << endl;
    }
    else if(testCase == 2){
        for(int i = 0; i < n; i++){
            cout << m[i]->calculateMembershipCardCost() << endl;
        }
        cout << "calculateMembershipCardCost method OK" << endl;
    }
    else if(testCase == 3){
        for(int i = 0; i < n; i++){
            m[i]->printDetail();
        }
        cout << "printDetail method OK" << endl;
    }
    else if(testCase == 4){
        int most_expensive_nat_lib_index = findMostExpensiveNationalLibrary(m, n);
        if(most_expensive_nat_lib_index>=0){
            m[most_expensive_nat_lib_index]->printDetail();
        }else{
            cout << "National Library not found in the array!"<<endl;
        }
        cout << "findMostExpensiveNationalLibrary method OK" << endl;
    }


    for (int i = 0; i < n; ++i) {
        delete m[i];
    }

    delete[] m;

    return 0;
}
