// DEKLARASI FILE SRC/PENJUALAN.CPP
#include "../components/penjualan.hpp"

// ALGORITMA INPUT TRANSAKSI PENJUALAN
void inputPenjualan() {
    Penjualan penjualan;
    int pilihan;
    char konfirmasi;
    do {
        cout << "\n=== TRANSAKSI PENJUALAN ===\n";
        cout << "Tanggal penjualan (DD-MM-YYYY): ";
        cin >> penjualan.tanggal;
        for (int i = 0; i < JUMLAH_KOMODITAS; i++) cout << i + 1 << ". " << komoditas[i] << '\n';
        cout << "Pilih jenis komoditas: ";
        cin >> pilihan;
        cout << "Jumlah yang terjual: ";
        cin >> penjualan.jumlah_terjual;
        cout << "Harga jual per satuan: Rp";
        cin >> penjualan.harga_jual;

        // VALIDASI DATA TRANSAKSI PENJUALAN
        if (penjualan.tanggal.length() == 10 && penjualan.tanggal[2] == '-' && penjualan.tanggal[5] == '-' && pilihan >= 1 && pilihan <= JUMLAH_KOMODITAS && penjualan.jumlah_terjual > 0 && penjualan.harga_jual > 0) {
            bool valid = true;
            for (int j = 0; j < 10; j++) if (j != 2 && j != 5 && (penjualan.tanggal[j] < '0' || penjualan.tanggal[j] > '9')) valid = false;

            if (!valid) {
                cout << "Data tidak valid. Silahkan isi ulang.\n";
                continue;
            }

            int i = pilihan - 1;
            penjualan.jenis_komoditas = komoditas[i];

            // VALIDASI KECUKUPAN PERSEDIAAN
            if (penjualan.jumlah_terjual > sisa_persediaan[i]) {
                cout << "Persediaan tidak mencukupi. Sesuaikan jumlah jual.\n";
                continue;
            }

            // HITUNG PENDAPATAN
            penjualan.pendapatan = hitungPendapatan(penjualan.jumlah_terjual, penjualan.harga_jual);

            // TAMPILKAN RINCIAN TRANSAKSI
            cout << "\n=== RINCIAN TRANSAKSI ===\n";
            cout << left << setw(20) << "TANGGAL" << ": " << penjualan.tanggal << '\n';
            cout << left << setw(20) << "JENIS KOMODITAS" << ": " << penjualan.jenis_komoditas << '\n';
            cout << left << setw(20) << "JUMLAH TERJUAL" << ": " << penjualan.jumlah_terjual << '\n';
            cout << left << setw(20) << "HARGA JUAL" << ": Rp" << fixed << setprecision(0) << penjualan.harga_jual << '\n';
            cout << left << setw(20) << "PENDAPATAN" << ": Rp" << fixed << setprecision(0) << penjualan.pendapatan << '\n';
            cout << "Rincian transaksi benar? (y/n): ";
            cin >> konfirmasi;

            // VALIDASI KONFIRMASI TRANSAKSI
            if (konfirmasi == 'y' || konfirmasi == 'Y') {
                simpanTransaksi(penjualan, i);
                break;
            } else if (konfirmasi == 'n' || konfirmasi == 'N') {
                cout << "Petani memperbaiki input.\n";
            } else {
                cout << "Inputan tidak valid.\n";
            }
        } else {
            cout << "Data tidak valid. Silahkan isi ulang.\n";
        }
    } while (true);
}