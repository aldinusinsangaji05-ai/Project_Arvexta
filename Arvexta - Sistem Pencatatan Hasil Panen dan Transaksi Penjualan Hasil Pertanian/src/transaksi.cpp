// DEKLARASI FILE SRC/TRANSAKSI.CPP
#include "../components/penjualan.hpp"

// SIMPAN TRANSAKSI
void simpanTransaksi(const Penjualan& penjualan, int indeks_komoditas) {
    daftar_penjualan.push_back(penjualan);
    sisa_persediaan[indeks_komoditas] -= penjualan.jumlah_terjual;
    cout << "Transaksi berhasil disimpan.\n";
}