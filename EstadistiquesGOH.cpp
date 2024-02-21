#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <algorithm>
using namespace std;
typedef struct record;

int opcio;

struct Equip
{
    string tipus;
    string nom;
    string instal;
    int preu;
    int perdua;
};

void mostrarLlista(const char* fileName) {
    ifstream file(fileName, ios::binary);
    if (!file) {
        cout << "No s'ha pogut obrir el fitxer." << endl;
        return;
    }

    string tipus, nom, instal;
    int preu, perdua;

    while (file) {
        file.read(reinterpret_cast<char*>(&tipus), sizeof(tipus));
        file.read(reinterpret_cast<char*>(&nom), sizeof(nom));
        file.read(reinterpret_cast<char*>(&instal), sizeof(instal));
        file.read(reinterpret_cast<char*>(&preu), sizeof(preu));
        file.read(reinterpret_cast<char*>(&perdua), sizeof(perdua));

        if (file) {
            cout << "------------------------" << endl;
            cout << "Tipus: " << tipus << endl;
            cout << "Nom: " << nom << endl;
            cout << "Instalacio: " << instal << endl;
            cout << "Preu: " << preu << endl;
            cout << "Perdua d'humanitat: " << perdua << endl;
            cout << "------------------------" << endl;
        }
    }

    file.close();
}

double calcularMitjanaPreus(const char* fileName) {
    ifstream file(fileName, ios::binary);
    if (!file) {
        cout << "No s'ha pogut obrir el fitxer." << endl;
        return  0;
    }

    double sumaPreus = 0;
    int numCiberparts = 0;
    int preu;

    while (file) {
        file.read(reinterpret_cast<char*>(&preu), sizeof(preu));
        if (file) {
            sumaPreus += preu;
            numCiberparts++;
        }
    }

    file.close();

    if (numCiberparts == 0) {
        return  0; 
    }

    return sumaPreus / numCiberparts;
}


int main()
{
    const char* fileName = "dades.dat";
    ofstream file(fileName, ios::app | ios::binary);
    double mitjana = 0; 

    do {
        string tipus;
        string nom;
        string instal;
        int preu;
        int perdua;

        cout << "1. Afegir mes ciberequip" << endl;
        cout << "2. Mostrar llista de ciberequip" << endl;
        cout << "3. Mostrar mitjana dels preus del ciberequip" << endl;
        cout << "4. Sortir" << endl;
        cin >> opcio;

        switch (opcio) {

        case   1:
            cout << "Benvingut al Seleccionador de Cyberequip!" << endl;
            cout << "Tipus de Cyberpart?" << endl;
            cout << "Cibermoda, Neuronal, Ciberoptics, Ciberaudio, Intern, Ciberextremitats?" << endl;
            cin >> tipus;

            cout << "Nom de la ciberpart?" << endl;
            cin >> nom;

            cout << "Instalacio?" << endl;
            cout << "Centre comercial, Clinica, Hospital?" << endl;
            cin >> instal;

            cout << "Preu?" << endl;
            cin >> preu;

            cout << "Perdua d'humanitat?" << endl;
            cin >> perdua;

            file.write(reinterpret_cast<const char*>(&tipus), sizeof(tipus));
            file.write(reinterpret_cast<const char*>(&nom), sizeof(nom));
            file.write(reinterpret_cast<const char*>(&instal), sizeof(instal));
            file.write(reinterpret_cast<const char*>(&preu), sizeof(preu));
            file.write(reinterpret_cast<const char*>(&perdua), sizeof(perdua));
            file.close();

            cout << "Afegir mes ciberequip?   1. Si   3. No" << endl;
            cin >> opcio;
            break;

        case   2:
            mostrarLlista(fileName);
            break;

        case   3:
            mitjana = calcularMitjanaPreus(fileName);
            if (mitjana != 0) {
                cout << "La mitjana dels preus de totes les ciberparts es: " << mitjana << endl;
            }
            break;

        case   4:
            cout << "Tencant sesio..." << endl;
            break;
        }

    } while (opcio != 4);

    return   0;
}
