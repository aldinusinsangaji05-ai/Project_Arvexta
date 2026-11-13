// DEKLARASI FILE SRC/LOGIN.CPP
#include "../components/data.hpp"

// FUNGSI LOGIN
bool login() {
    // 
    Pengguna pengguna;
    do {
        cout << "\n=== LOGIN PETANI ===\n";
        cout << "Username: ";
        cin >> pengguna.username;
        cout << "Password: ";
        cin >> pengguna.password;
        // VALIDASI LOGIN
        if (pengguna.username == "petani" && pengguna.password == "12345") {
            cout << "Login berhasil.\n";
            return true;
        } else {
            cout << "Username atau password tidak sesuai. Silahkan isi ulang\n";
        }
    } while (true);
}
