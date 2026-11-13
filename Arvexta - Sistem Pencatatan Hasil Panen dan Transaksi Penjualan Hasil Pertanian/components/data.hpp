// DEKLARASI FILE COMPONENTS/DATA.HPP
#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

// STRUKTUR DATA PENGGUNA
struct Pengguna {
    string username;
    string password;
};

// DATA KOMODITAS
const int JUMLAH_KOMODITAS = 3;
const string komoditas[JUMLAH_KOMODITAS] = {"Cengkeh", "Pala", "Kelapa"};

#endif
