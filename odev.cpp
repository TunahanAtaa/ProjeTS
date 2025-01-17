#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <string>


using namespace std;

void kayitEkle();
void kayitListele();
void kayitSil();
void kayitGuncelle();
void kayitAra();

struct Yemek
{
    char id[10];
    char ad[30];
    int fiyat;
};

Yemek y;

int main() {

    char secim;

    do{ 
        
        system("clear"); //Linux kullandığım için cls değil.

        cout<<"Fast Food Otomasyonuna Hosgeldiniz!"<<endl;
        cout<<"Lutfen isleminizi seciniz."<<endl;
        cout<<"1- Kayit Ekle"<<endl;
        cout<<"2- Kayit Listele"<<endl;
        cout<<"3- Kayit Sil"<<endl;
        cout<<"4- Kayit Güncelle"<<endl;
        cout<<"5- Kayit Ara"<<endl;
        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        

        cin>>secim;

        switch(secim){
            case '1':
            {
                kayitEkle();
                break;
            }
            
            case '2':
            {
                kayitListele();
                break;
            }
            
            case '3':
            {
                kayitSil();
                break;
            }
            
            case '4':
            {
                kayitGuncelle();
                break;
            }
            
            case '5':
            {
                kayitAra();
                break;
            }
        }


    cout<<endl;
    cout<<"Ana menuye dönmek ister misiniz?"<<endl;
    cin>>secim;

    }while(secim=='e'||secim=='E');
    



    return 0;
}

void kayitEkle(){
    
    ofstream yaz("bilgiler.dat", ios::binary | ios::app);

    if (!yaz) {
        cout << "Dosya acilamadi!" << endl;
        return;
    }

    char secim;
    do {
        cout << "Yemek ID giriniz: ";
        cin >> y.id;
        cin.ignore(); 

        string yemekAdi;
        cout << "Yemek adi giriniz: ";
        getline(cin, yemekAdi); 
        strncpy(y.ad, yemekAdi.c_str(), sizeof(y.ad) - 1); 
        y.ad[sizeof(y.ad) - 1] = '\0'; 

        cout << "Fiyati giriniz: ";
        cin >> y.fiyat;
        cin.ignore(); 

        yaz.write((char*)&y, sizeof(y));

        cout << endl;
        cout << "Eklemeye devam etmek ister misin? (e/E için evet): ";
        cin >> secim;
        cin.ignore(); 
    } while (secim == 'e' || secim == 'E');

    yaz.close();

    
}

void kayitListele(){

    ifstream oku("bilgiler.dat", ios::binary | ios::app);
    oku.seekg(0,ios::end);
    int adet=oku.tellg()/sizeof(y);

    if(adet>0){
        for(int i=0; i<adet; i++){
            
            oku.seekg(i*sizeof(y));
            oku.read((char*)&y,sizeof(y));

            cout<<endl;
            cout<<i+1<<". Kayit: "<<endl;
            cout<<"ID: "<<y.id<<endl;
            cout<<"Yemek ismi: "<<y.ad<<endl;
            cout<<"Fiyat: "<<y.fiyat<<endl;
        }

        oku.close();

    }
    else{
        cout<<endl;
        cout<<"Kayit Bulunamadi"<<endl;
    }

}

void kayitSil() {
    ifstream oku("bilgiler.dat", ios::binary);
    ofstream yaz("gecici.dat", ios::binary);

    if (!oku || !yaz) {
        cout << "Dosya acilamadi!" << endl;
        return;
    }

    char silinecek_id[10];
    cout << "Silinecek kaydin ID'sini giriniz (Tüm kayıtları silmek için * yazın): ";
    cin >> silinecek_id;

    bool silindi = false;

    if (strcmp(silinecek_id, "*") == 0) {
        oku.close();
        yaz.close();
        remove("bilgiler.dat");
        cout << "Tüm kayıtlar basariyla silindi!" << endl;
        return;
    }

    while (oku.read((char*)&y, sizeof(y))) {
        if (strcmp(y.id, silinecek_id) != 0) {
            yaz.write((char*)&y, sizeof(y));
        } else {
            silindi = true;
        }
    }

    oku.close();
    yaz.close();

    remove("bilgiler.dat");
    rename("gecici.dat", "bilgiler.dat");

    if (silindi) {
        cout << "Kayit basariyla silindi!" << endl;
    } else {
        cout << "Kayit bulunamadi!" << endl;
    }
}


void kayitGuncelle(){
    fstream dosya("bilgiler.dat", ios::binary | ios::in | ios::out);

    if (!dosya) {
        cout << "Dosya acilamadi!" << endl;
        return;
    }

    char guncellenecek_id[10];
    cout << "Guncellenecek kaydin ID'sini giriniz: ";
    cin >> guncellenecek_id;

    bool bulundu = false;
    while (dosya.read((char*)&y, sizeof(y))) {
        if (strcmp(y.id, guncellenecek_id) == 0) {
            cout << "Yeni yemek adini giriniz: ";
            cin >> y.ad;
            cout << "Yeni fiyatini giriniz: ";
            cin >> y.fiyat;

            dosya.seekp(-sizeof(y), ios::cur);
            dosya.write((char*)&y, sizeof(y));
            bulundu = true;
            cout << "Kayit basariyla guncellendi!" << endl;
            break;
        }
    }

    if (!bulundu) {
        cout << "Kayit bulunamadi!" << endl;
    }

    dosya.close();
}

void kayitAra(){
    ifstream oku("bilgiler.dat", ios::binary);

    if (!oku) {
        cout << "Dosya acilamadi!" << endl;
        return;
    }

    char aranacak_id[10];
    cout << "Aranacak kaydin ID'sini giriniz: ";
    cin >> aranacak_id;

    bool bulundu = false;
    while (oku.read((char*)&y, sizeof(y))) {
        if (strcmp(y.id, aranacak_id) == 0) {
            cout << "Kayit bulundu:" << endl;
            cout << "ID: " << y.id << endl;
            cout << "Yemek ismi: " << y.ad << endl;
            cout << "Fiyat: " << y.fiyat << endl;
            bulundu = true;
            break;
        }
    }

    if (!bulundu) {
        cout << "Kayit bulunamadi!" << endl;
    }

    oku.close();
}