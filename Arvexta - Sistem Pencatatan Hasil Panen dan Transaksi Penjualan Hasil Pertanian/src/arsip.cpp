// DEKLARASI FILE SRC/ARSIP.CPP
#include "../components/penjualan.hpp"
#include <ctime>
#include <sstream>
#include <limits>

// ALGORITMA SIMPAN ARSIP LAPORAN
void simpanArsip() {
    int pilihan;
    if (daftar_panen.empty() && daftar_penjualan.empty()) {
        cout << "Laporan yang akan disimpan tidak tersedia\n";
        return;
    }
    do {
        cout << "\n=== SIMPAN ARSIP LAPORAN ===\n";
        cout << "1. Harian\n";
        cout << "2. Mingguan\n";
        cout << "3. Bulanan\n";
        cout << "Pilih periode laporan: ";
        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Inputan tidak valid\n";
            continue;
        }
        if (pilihan < 1 || pilihan > 3) {
            cout << "Inputan tidak valid\n";
            continue;
        }
        break;
    } while (true);

    string periode;
    if (pilihan == 1) periode = "Harian";
    else if (pilihan == 2) periode = "Mingguan";
    else periode = "Bulanan";

    time_t waktu = time(nullptr);
    tm* waktu_lokal = localtime(&waktu);
    char tanggal_hari_ini[11];
    strftime(tanggal_hari_ini, sizeof(tanggal_hari_ini), "%d-%m-%Y", waktu_lokal);

    int hari, bulan, tahun;
    char pemisah1, pemisah2;
    stringstream ss(tanggal_hari_ini);
    ss >> hari >> pemisah1 >> bulan >> pemisah2 >> tahun;

    vector<Panen> data_panen;
    vector<Penjualan> data_penjualan;

    auto sesuaiPeriode = [&](const string& tanggal) {
        int h, b, t;
        char p1, p2;
        stringstream tanggal_data(tanggal);
        tanggal_data >> h >> p1 >> b >> p2 >> t;
        if (tanggal_data.fail() || p1 != '-' || p2 != '-') return false;

        if (pilihan == 1)
            return h == hari && b == bulan && t == tahun;

        if (pilihan == 3)
            return b == bulan && t == tahun;

        tm awal = {};
        awal.tm_mday = hari;
        awal.tm_mon = bulan - 1;
        awal.tm_year = tahun - 1900;
        awal.tm_hour = 12;
        time_t waktu_acuan = mktime(&awal);

        tm tanggal_dipilih = {};
        tanggal_dipilih.tm_mday = h;
        tanggal_dipilih.tm_mon = b - 1;
        tanggal_dipilih.tm_year = t - 1900;
        tanggal_dipilih.tm_hour = 12;
        time_t waktu_data = mktime(&tanggal_dipilih);

        double selisih = difftime(waktu_acuan, waktu_data) / (60 * 60 * 24);
        return selisih >= 0 && selisih < 7;
    };

    for (const auto& data : daftar_panen)
        if (sesuaiPeriode(data.tanggal)) data_panen.push_back(data);

    for (const auto& data : daftar_penjualan)
        if (sesuaiPeriode(data.tanggal)) data_penjualan.push_back(data);

    if (data_panen.empty() && data_penjualan.empty()) {
        cout << "Laporan yang akan disimpan tidak tersedia\n";
        return;
    }

    ofstream arsip("arsip_panen.txt", ios::app);
    if (!arsip.is_open()) {
        cout << "Arsip laporan gagal disimpan\n";
        return;
    }

    arsip << "====================================\n";
    arsip << "TANGGAL ARSIP      : " << tanggal_hari_ini << '\n';
    arsip << "PERIODE LAPORAN    : " << periode << '\n';
    arsip << "====================================\n";

    for (int i = 0; i < JUMLAH_KOMODITAS; i++) {
        int totalPanen = 0;
        int totalJual = 0;
        double totalPendapatan = 0;

        for (const auto& data : data_panen)
            if (data.jenis_komoditas == komoditas[i])
                totalPanen += data.jumlah_panen;

        for (const auto& data : data_penjualan) {
            if (data.jenis_komoditas == komoditas[i]) {
                totalJual += data.jumlah_terjual;
                totalPendapatan += data.pendapatan;
            }
        }

        arsip << "\nJENIS KOMODITAS    : " << komoditas[i] << '\n';
        arsip << "TOTAL PANEN        : " << totalPanen << '\n';
        arsip << "TOTAL TERJUAL      : " << totalJual << '\n';
        arsip << "TOTAL PENDAPATAN   : Rp" << fixed << setprecision(0) << totalPendapatan << '\n';
        arsip << "SISA PERSEDIAAN    : " << sisa_persediaan[i] << '\n';
        arsip << "====================================\n";
    }

    arsip << '\n';
    arsip.close();
    cout << "Laporan berhasil diarsipkan\n";
}
