// DEKLARASI FILE SRC/PENDAPATAN.CPP
#include "../components/penjualan.hpp"

// ALGORITMA HITUNG PENDAPATAN
double hitungPendapatan(int jumlah_terjual, double harga_jual) {
    double pendapatan = jumlah_terjual * harga_jual;
    if (pendapatan <= 0) {
        cout << "Pendapatan tidak valid. Periksa jumlah jual dan harga jual.\n";
        return 0;
    }
    return pendapatan;
}