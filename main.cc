/**
 * main.cpp
 * Main Driver Program
 */
#include "spotify.h"

void clearScreen() {
    for(int i=0; i<5; i++) cout << "\n"; 
}

void menuAdmin(ListGlobalSong &LG) {
    int choice;
    char t[50], a[50], al[50], d[10];
    
    do {
        clearScreen();
        cout << "=== ADMIN MENU ===\n";
        cout << "1. Insert Song\n2. Delete Song\n3. Edit Song\n4. Show All Songs\n5. Logout\n";
        cout << "Pilih: "; cin >> choice; 
        
        switch(choice) {
            case 1:
                cin.ignore();
                inputString("Judul : ", t, 50);
                inputString("Artis : ", a, 50);
                inputString("Album : ", al, 50);
                inputString("Durasi: ", d, 10);
                insertLastSong(LG.first, allocateSong(t, a, al, d));
                break;
            case 2:
                cin.ignore();
                showSongs(LG.first);
                inputString("Judul lagu hapus: ", t, 50);
                deleteSong(LG.first, t);
                break;
            case 3:
                cin.ignore();
                showSongs(LG.first);
                inputString("Judul lagu edit: ", t, 50);
                editSong(searchSong(LG.first, t));
                break;
            case 4:
                cout << "\n--- MASTER SONG LIST ---\n";
                showSongs(LG.first);
                cout << "Tekan enter..."; 
                cin.ignore(); cin.get();
                break;
        }
    } while (choice != 5);
}

void menuUser(ListGlobalSong &LG, AdrUser User) {
    int choice;
    char name[50], newName[50], t[50];
    AdrPlaylist P;
    AdrSong S;
    
    do {
        clearScreen();
        cout << "=== USER: " << User->info.username << " ===\n";
        cout << "1. Play Playlist\n2. Search Song (Master)\n3. Create Playlist\n";
        cout << "4. Search Playlist\n5. Edit Playlist\n6. Delete Playlist\n7. Add Song to Playlist\n8. Logout\n";
        cout << "Pilih: "; cin >> choice;

        switch(choice) {
            case 1:
                cin.ignore();
                showPlaylists(User);
                inputString("Pilih Nama Playlist: ", name, 50);
                P = searchPlaylist(User, name);
                if (P) playPlaylist(P);
                else cout << ">> Tidak ketemu.\n";
                cin.get();
                break;
            case 2:
                cin.ignore();
                inputString("Cari Judul: ", t, 50);
                S = searchSong(LG.first, t);
                if (S) cout << "Ditemukan: " << S->info.title << " - " << S->info.artist << "\n";
                else cout << "Tidak ditemukan.\n";
                cin.get();
                break;
            case 3:
                cin.ignore();
                inputString("Nama Playlist Baru: ", name, 50);
                insertLastPlaylist(User, allocatePlaylist(name));
                cout << ">> Playlist dibuat.\n";
                cin.get();
                break;
            case 4:
                cin.ignore();
                inputString("Cari Playlist: ", name, 50);
                P = searchPlaylist(User, name);
                if (P) cout << "Playlist '" << P->info.name << "' ada.\n";
                else cout << "Tidak ada.\n";
                cin.get();
                break;
            case 5:
                cin.ignore();
                showPlaylists(User);
                inputString("Nama Playlist Lama: ", name, 50);
                inputString("Nama Playlist Baru: ", newName, 50);
                P = searchPlaylist(User, name);
                if(P) editPlaylist(P, newName);
                else cout << "Tidak ditemukan.\n";
                cin.get();
                break;
            case 6:
                cin.ignore();
                showPlaylists(User);
                inputString("Hapus Playlist: ", name, 50);
                deletePlaylist(User, name);
                cin.get();
                break;
            case 7: // Fitur MLL: Add Song to Playlist
                cin.ignore();
                cout << "--- DAFTAR LAGU MASTER ---\n";
                showSongs(LG.first);
                inputString("Pilih Judul Lagu: ", t, 50);
                S = searchSong(LG.first, t);
                if (S) {
                    showPlaylists(User);
                    inputString("Masukkan ke Playlist: ", name, 50);
                    P = searchPlaylist(User, name);
                    if (P) addSongToPlaylist(P, S);
                    else cout << "Playlist tidak ada.\n";
                } else {
                    cout << "Lagu tidak ada.\n";
                }
                cin.get();
                break;
        }
    } while (choice != 8);
}

int main() {
    ListUser LU;
    ListGlobalSong LG;
    
    createListUser(LU);
    createListGlobalSong(LG);
    
    // Data Dummy Awal
    insertLastSong(LG.first, allocateSong((char*)"Komang", (char*)"Raim Laode", (char*)"Single", (char*)"03:42"));
    insertLastSong(LG.first, allocateSong((char*)"Sial", (char*)"Mahalini", (char*)"Fabula", (char*)"04:03"));
    insertLastUser(LU, allocateUser((char*)"user1", (char*)"123"));

    int choice;
    char u[50], p[50];
    
    do {
        clearScreen();
        cout << "=== APLIKASI MUSIK C++ (MLL) ===\n";
        cout << "1. Login\n2. Create User\n3. Delete User\n4. Out\n";
        cout << "Pilih: "; cin >> choice;
        
        switch(choice) {
            case 1:
                cin.ignore();
                inputString("Username: ", u, 50);
                inputString("Password: ", p, 50);
                
                if (strCmp(u, "admin") == 0 && strCmp(p, "admin") == 0) {
                    menuAdmin(LG);
                } else {
                    AdrUser loggedIn = loginUser(LU, u, p);
                    if (loggedIn) menuUser(LG, loggedIn);
                    else {
                        cout << "Login Gagal!\n";
                        cin.get();
                    }
                }
                break;
            case 2:
                cin.ignore();
                inputString("New Username: ", u, 50);
                inputString("New Password: ", p, 50);
                insertLastUser(LU, allocateUser(u, p));
                cout << "User Created!\n";
                cin.get();
                break;
            case 3:
                cin.ignore();
                inputString("Username to delete: ", u, 50);
                deleteUser(LU, u);
                cin.get();
                break;
        }
    } while (choice != 4);
    
    return 0;
}