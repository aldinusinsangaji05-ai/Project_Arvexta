// DEKLARASI FILE COMPONENTS/PENJUALAN.HPP
#ifndef PENJUALAN_HPP
#define PENJUALAN_HPP

#include "panen.hpp"

// STRUKTUR DATA TRANSAKSI PENJUALAN
struct Penjualan {
    string tanggal;
    string jenis_komoditas;
    int jumlah_terjual;
    double harga_jual;
    double pendapatan;
};

// DEKLARASI DATA DAN FUNGSI PENJUALAN
extern vector<Penjualan> daftar_penjualan;

void inputPenjualan();
double hitungPendapatan(int jumlah_terjual, double harga_jual);
void simpanTransaksi(const Penjualan& penjualan, int indeks_komoditas);
void rekapLaporan();
void simpanArsip();

#endif
