// DEKLARASI FILE COMPONENTS/PANEN.HPP
#ifndef PANEN_HPP
#define PANEN_HPP

#include "data.hpp"

// STRUKTUR DATA HASIL PANEN
struct Panen {
    string jenis_komoditas;
    string tanggal;
    int jumlah_panen;
};

// DEKLARASI DATA DAN FUNGSI SISTEM PANEN
extern vector<Panen> daftar_panen;
extern vector<int> sisa_persediaan;

void inputPanen();
void tampilkanPersediaan();

#endif
