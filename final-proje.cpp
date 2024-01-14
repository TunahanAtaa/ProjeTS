#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <locale.h>

using namespace std;

struct Proje {
    string projeAdi;
    string projeYurutucu;
    int projeBudgesi;
    int projeSuresi;
};

void projeEkle(ofstream& dosya, const Proje& proje);
void projeListele(ifstream& dosya);

int main() {
    
    setlocale(LC_ALL,"Turkish");
	
	const string dosyaAdi = "projeler.txt";

    char devam;

    do {
        // Dosyayý yazma modunda aç, dosya yoksa oluþtur
        ofstream yazmaDosyasi(dosyaAdi.c_str(), ios::app);

        if (!yazmaDosyasi.is_open()) {
            cerr << "Dosya açma hatasý!" << endl;
            return 1;
        }

        Proje yeniProje;

        cout << "Proje Adi: ";
        getline(cin, yeniProje.projeAdi);

        cout << "Proje Yurutucu: ";
        getline(cin, yeniProje.projeYurutucu);

        cout << "Proje Butcesi: ";
        string budceStr;
        getline(cin, budceStr);
        istringstream(budceStr) >> yeniProje.projeBudgesi;

        cout << "Proje Süresi: ";
        string sureStr;
        getline(cin, sureStr);
        istringstream(sureStr) >> yeniProje.projeSuresi;

        projeEkle(yazmaDosyasi, yeniProje);

        yazmaDosyasi.close();

        ifstream okumaDosyasi(dosyaAdi.c_str());

        if (!okumaDosyasi.is_open()) {
            cerr << "Dosya açma hatasý!" << endl;
            return 1;
        }

        projeListele(okumaDosyasi);

        okumaDosyasi.close();

        cout << "Baþka proje eklemek ister misiniz? (e/h): ";
        cin >> devam;
        cin.ignore(); // Boþ newline karakterini temizle

    } while (devam == 'e' || devam == 'E');

    return 0;
}

void projeEkle(ofstream& dosya, const Proje& proje) {
    dosya << proje.projeAdi << ","
          << proje.projeYurutucu << ","
          << proje.projeBudgesi << ","
          << proje.projeSuresi << endl;
}

void projeListele(ifstream& dosya) {
    Proje okunanProje;
    string satir;

    cout << "\nProje Listesi:\n";

    while (getline(dosya, satir)) {
        size_t virgul1 = satir.find(',');
        size_t virgul2 = satir.find(',', virgul1 + 1);
        size_t virgul3 = satir.find(',', virgul2 + 1);

        okunanProje.projeAdi = satir.substr(0, virgul1);
        okunanProje.projeYurutucu = satir.substr(virgul1 + 1, virgul2 - virgul1 - 1);

        istringstream(satir.substr(virgul2 + 1, virgul3 - virgul2 - 1)) >> okunanProje.projeBudgesi;
        istringstream(satir.substr(virgul3 + 1)) >> okunanProje.projeSuresi;

        cout << "Proje Adi: " << okunanProje.projeAdi << endl;
        cout << "Proje Yurutucu: " << okunanProje.projeYurutucu << endl;
        cout << "Proje Butcesi: " << okunanProje.projeBudgesi << endl;
        cout << "Proje Süresi: " << okunanProje.projeSuresi << "\n\n";
    }
}

