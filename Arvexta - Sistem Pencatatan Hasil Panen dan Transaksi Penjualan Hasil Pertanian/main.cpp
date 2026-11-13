// DEKLARASI FILE MAIN.CPP
#include "components/penjualan.hpp"
#include "components/panen.hpp"

// DEKLARASI DATA GLOBAL
vector<Panen> daftar_panen;
vector<Penjualan> daftar_penjualan;
vector<int> sisa_persediaan = {0, 0, 0};

// DEKLARASI FUNGSI LOGIN
bool login();

// MENU UTAMA
void menuUtama() {
    int pilihan;
    do {
        cout << "\n=== SISTEM PENCATATAN HASIL PANEN DAN TRANSAKSI PENJUALAN ===\n";
        cout << "1. Catat Hasil Panen\n";
        cout << "2. Tampilkan Persediaan\n";
        cout << "3. Transaksi Penjualan\n";
        cout << "4. Rekapitulasi Laporan\n";
        cout << "5. Simpan Arsip Laporan\n";
        cout << "6. Keluar\n";
        cout << "Input pilihan (1-6): ";
        cin >> pilihan;

        // VALIDASI INPUT ANGKA
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Input harus berupa angka.\n";
            continue;
        }

        // VALIDASI PILIHAN MENU
        if (pilihan < 1 || pilihan > 6) {
            cout << "Inputan tidak valid. Silahkan pilih angka 1-6.\n";
            continue;
        }

        switch (pilihan) {
            case 1: inputPanen(); break;
            case 2: tampilkanPersediaan(); break;
            case 3: inputPenjualan(); break;
            case 4: rekapLaporan(); break;
            case 5: simpanArsip(); break;
            case 6: cout << "Program selesai.\n"; break;
        }
    } while (pilihan != 6);
}

// PROGRAM UTAMA
int main() {
    if (login()) menuUtama();
    return 0;
}