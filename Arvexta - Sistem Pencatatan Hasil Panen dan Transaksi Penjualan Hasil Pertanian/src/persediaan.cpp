// DEKLARASI FILE SRC/PERSEDIAAN.CPP
#include "../components/panen.hpp"

// TAMPILKAN PERSEDIAAN
void tampilkanPersediaan() {
    cout << "\n=== DAFTAR SISA PERSEDIAAN ===\n";
    for (int i = 0; i < sisa_persediaan.size(); i++) {
        cout << "Jenis Komoditas: " << komoditas[i] << '\n';
        cout << "Sisa Persediaan: " << sisa_persediaan[i] << '\n';
        cout << "-----------------------------\n";
    }
}
