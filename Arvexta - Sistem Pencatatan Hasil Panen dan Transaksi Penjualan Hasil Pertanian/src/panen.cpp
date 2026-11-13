// DEKLARASI FILE SRC/PANEN.CPP
#include "../components/panen.hpp"

// INPUT HASIL PANEN
void inputPanen() {
    Panen panen;
    int pilihan;
    do {
        cout << "\n=== CATAT HASIL PANEN ===\n";
        cout << "Tanggal panen (DD-MM-YYYY): ";
        cin >> panen.tanggal;
        for (int i = 0; i < JUMLAH_KOMODITAS; i++) cout << i + 1 << ". " << komoditas[i] << '\n';
        cout << "Pilih jenis komoditas: ";
        cin >> pilihan;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Pilihan harus berupa angka. Silahkan isi ulang.\n";
            continue;
        }
        cout << "Jumlah panen: ";
        cin >> panen.jumlah_panen;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Jumlah panen harus berupa angka. Silahkan isi ulang.\n";
            continue;
        }

        // VALIDASI DATA HASIL PANEN
        bool valid = panen.tanggal.length() == 10 && panen.tanggal[2] == '-' && panen.tanggal[5] == '-' && pilihan >= 1 && pilihan <= JUMLAH_KOMODITAS && panen.jumlah_panen > 0;
        for (int i = 0; i < 10; i++) if (i != 2 && i != 5 && (panen.tanggal[i] < '0' || panen.tanggal[i] > '9')) valid = false;

        if (valid) {
            int i = pilihan - 1;
            panen.jenis_komoditas = komoditas[i];
            daftar_panen.push_back(panen);
            sisa_persediaan[i] += panen.jumlah_panen;
            cout << "Hasil panen berhasil disimpan.\n";
            break;
        } else {
            cout << "Data tidak valid. Silahkan isi ulang.\n";
        }
    } while (true);
}