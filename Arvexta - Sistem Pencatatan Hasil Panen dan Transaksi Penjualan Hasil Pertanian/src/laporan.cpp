#include "../components/penjualan.hpp"

// REKAPITULASI LAPORAN
void rekapLaporan() {
    int pilihan;
    char konfirmasi;

    do {
        cout << "\n=== REKAPITULASI LAPORAN ===\n";
        cout << "1. Harian\n";
        cout << "2. Mingguan\n";
        cout << "3. Bulanan\n";
        cout << "Pilih periode laporan: ";
        cin >> pilihan;

        // VALIDASI PERIODE LAPORAN
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Input harus berupa angka.\n";
            continue;
        }

        cin.ignore(10000, '\n');

        if (pilihan < 1 || pilihan > 3) {
            cout << "Inputan tidak valid.\n";
            continue;
        }

        // TENTUKAN PERIODE LAPORAN
        string periode;
        if (pilihan == 1) periode = "Harian";
        else if (pilihan == 2) periode = "Mingguan";
        else periode = "Bulanan";

        // INPUT TANGGAL LAPORAN
        string tanggal;
        cout << "Masukkan tanggal acuan (DD-MM-YYYY): ";
        cin >> tanggal;

        // VALIDASI FORMAT TANGGAL
        if (tanggal.length() != 10 || tanggal[2] != '-' || tanggal[5] != '-') {
            cout << "Format tanggal tidak valid. Silahkan isi ulang.\n";
            continue;
        }

        bool valid = true;
        for (int i = 0; i < 10; i++) {
            if (i != 2 && i != 5 && (tanggal[i] < '0' || tanggal[i] > '9'))
                valid = false;
        }

        if (!valid) {
            cout << "Format tanggal tidak valid. Silahkan isi ulang.\n";
            continue;
        }

        int hari, bulan, tahun;
        char pemisah1, pemisah2;
        stringstream ss(tanggal);
        ss >> hari >> pemisah1 >> bulan >> pemisah2 >> tahun;

        if (ss.fail() || pemisah1 != '-' || pemisah2 != '-' ||
            hari < 1 || hari > 31 || bulan < 1 || bulan > 12 || tahun < 1) {
            cout << "Tanggal tidak valid. Silahkan isi ulang.\n";
            continue;
        }

        // AMBIL DATA SESUAI PERIODE
        vector<Panen> data_panen;
        vector<Penjualan> data_penjualan;

        for (const auto& data : daftar_panen) {
            stringstream tanggal_data(data.tanggal);
            int h, b, t;
            char p1, p2;

            tanggal_data >> h >> p1 >> b >> p2 >> t;

            if (tanggal_data.fail() || p1 != '-' || p2 != '-')
                continue;

            bool sesuai = false;

            if (pilihan == 1) {
                sesuai = (h == hari && b == bulan && t == tahun);
            } else if (pilihan == 2) {
                int selisih = (tahun * 365 + bulan * 30 + hari) -
                              (t * 365 + b * 30 + h);
                sesuai = (selisih >= 0 && selisih < 7);
            } else {
                sesuai = (b == bulan && t == tahun);
            }

            if (sesuai)
                data_panen.push_back(data);
        }

        for (const auto& data : daftar_penjualan) {
            stringstream tanggal_data(data.tanggal);
            int h, b, t;
            char p1, p2;

            tanggal_data >> h >> p1 >> b >> p2 >> t;

            if (tanggal_data.fail() || p1 != '-' || p2 != '-')
                continue;

            bool sesuai = false;

            if (pilihan == 1) {
                sesuai = (h == hari && b == bulan && t == tahun);
            } else if (pilihan == 2) {
                int selisih = (tahun * 365 + bulan * 30 + hari) -
                              (t * 365 + b * 30 + h);
                sesuai = (selisih >= 0 && selisih < 7);
            } else {
                sesuai = (b == bulan && t == tahun);
            }

            if (sesuai)
                data_penjualan.push_back(data);
        }

        // VALIDASI KETERSEDIAAN DATA LAPORAN
        if (data_panen.empty() && data_penjualan.empty()) {
            cout << "Data pada periode tersebut tidak tersedia.\n";
            continue;
        }

        // TAMPILKAN REKAPITULASI SETIAP KOMODITAS
        cout << "\n=== LAPORAN PERIODE " << periode << " ===\n";

        for (int i = 0; i < JUMLAH_KOMODITAS; i++) {
            int totalPanen = 0;
            int totalJual = 0;
            double totalPendapatan = 0;

            // HITUNG TOTAL PANEN
            for (const auto& data : data_panen) {
                if (data.jenis_komoditas == komoditas[i])
                    totalPanen += data.jumlah_panen;
            }

            // HITUNG TOTAL PENJUALAN DAN PENDAPATAN
            for (const auto& data : data_penjualan) {
                if (data.jenis_komoditas == komoditas[i]) {
                    totalJual += data.jumlah_terjual;
                    totalPendapatan += data.pendapatan;
                }
            }

            cout << "\n";
            cout << left << setw(20) << "JENIS KOMODITAS" << ": " << komoditas[i] << '\n';
            cout << left << setw(20) << "TOTAL PANEN" << ": " << totalPanen << '\n';
            cout << left << setw(20) << "TOTAL TERJUAL" << ": " << totalJual << '\n';
            cout << left << setw(20) << "TOTAL PENDAPATAN" << ": Rp" << fixed << setprecision(0) << totalPendapatan << '\n';
            cout << left << setw(20) << "SISA PERSEDIAAN" << ": " << sisa_persediaan[i] << '\n';
            cout << "----------------------------------------\n";
        }

        // VALIDASI LAPORAN
        do {
            cout << "Apakah laporan sudah benar? (y/n): ";
            cin >> konfirmasi;

            if (konfirmasi != 'y' && konfirmasi != 'Y' &&
                konfirmasi != 'n' && konfirmasi != 'N') {
                cout << "Inputan tidak valid. Masukkan y atau n.\n";
            }

        } while (konfirmasi != 'y' && konfirmasi != 'Y' &&
                 konfirmasi != 'n' && konfirmasi != 'N');

        if (konfirmasi == 'n' || konfirmasi == 'N') {
            cout << "Laporan tidak disetujui. Kembali ke menu utama.\n";
            return;
        }

        cout << "Laporan berhasil dikonfirmasi.\n";
        return;

    } while (true);
}
