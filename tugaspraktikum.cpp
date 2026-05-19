#include <iostream>
#include <string>
using namespace std;

class RekeningBank {
private:
    string namaNasabah;
protected:
    double saldo;

public:
    void setRekening(string nama, double saldoAwal) {
        namaNasabah = nama;
        saldo = saldoAwal;
    }

    string getNama() {
        return namaNasabah;
    }

    double getSaldo() {
        return saldo;
    }

    // pure virtual function
    virtual void potongAdmin() = 0;

    void display() {
        cout << "Nama Nasabah : " << namaNasabah << endl;
        cout << "Saldo Akhir  : Rp " << saldo << endl;
        cout << "-----------------------------------" << endl;
    }
};

class RekeningSyariah : public RekeningBank {
public:
    void potongAdmin() override {
        // prinsip syariah, saldo utuh bebas admin
    }
};

class RekeningKonvensional : public RekeningBank {
public:
    void potongAdmin() override {
        saldo -= 15000;
    }
};

class RekeningPremium : public RekeningBank {
public:
    void potongAdmin() override {
        if (saldo > 10000000) {
            // saldo diatas 10jt bebas admin
        } else {
            // saldo dibawah atau sama dengan 10jt kena 50rb
            saldo -= 50000;
        }
    }
};

int main() {
    // pake pointer dari base class
    RekeningBank* serverBank;

    // 1. Rekening Syariah
    RekeningSyariah nasabah1;
    nasabah1.setRekening("Nasabah A", 5000000);
    serverBank = &nasabah1;
    serverBank->potongAdmin();
    serverBank->display();

    // 2. Rekening Konvensional
    RekeningKonvensional nasabah2;
    nasabah2.setRekening("Nasabah B", 2000000);
    serverBank = &nasabah2;
    serverBank->potongAdmin();
    serverBank->display();

    // 3. Rekening Premium (Saldo <= 10jt)
    RekeningPremium nasabah3;
    nasabah3.setRekening("Nasabah C", 8000000);
    serverBank = &nasabah3;
    serverBank->potongAdmin();
    serverBank->display();

    // 4. Rekening Premium (Saldo > 10jt)
    RekeningPremium nasabah4;
    nasabah4.setRekening("Nasabah D", 15000000);
    serverBank = &nasabah4;
    serverBank->potongAdmin();
    serverBank->display();

    return 0;
}