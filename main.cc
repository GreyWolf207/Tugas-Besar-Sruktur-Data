#include "Musik.h"
#include <iostream>

using namespace std;

int main() {

    ListUser users;
    ListGlobalSong songs;

    createListUser(users);
    createListGlobalSong(songs);

    while (true) {
        cout << "\n=== LOGIN PAGE ===\n";
        cout << "1. Login\n2. Create user\n3. Delete user\n4. Out\nPilih: ";
        string pilih; getline(cin, pilih);

        if (pilih == "1") {
            string u,p;
            cout << "\n=== WELCOME ===\n";
            cout << "Username: "; getline(cin, u);
            cout << "Password: "; getline(cin, p);

            if (u == "admin" && p == "admin123") {
                bool stopAdmin = false;

                while (!stopAdmin) {
                    cout << "\n=== ADMIN MENU ===\n";
                    cout << "1. Insert song\n2. Delete song\n3. Edit song\n4. List songs\n5. Logout\nPilih: ";
                    string pa; getline(cin, pa);

                    if (pa == "1") {
                        string t,a,al,du;

                        cout << "\n=== INSERT ===\n";
                        cout << "Judul          : "; getline(cin, t);
                        cout << "Artis          : "; getline(cin, a);
                        cout << "Album          : "; getline(cin, al);
                        cout << "Durasi (mm:ss) : "; getline(cin, du);

                        insertLastGlobalSong(songs, allocateSong(t, a, al, mmssToSeconds(du)));
                    } else if (pa == "2") {
                        cout << "\n=== DELETE ===\n";
                        cout << "Judul lagu: ";
                        string t; getline(cin, t);
                        deleteSongFromGlobal(songs, t);
                    } else if (pa == "3") {
                        cout << "\n=== EDIT ===\n";
                        cout << "Judul lagu: ";
                        string t; getline(cin, t);
                        AdrSong S = searchSongInGlobal(songs, t);

                        if (!S) {
                            continue;
                        }

                        string nt,na,nal,nd;
                        cout << " " << endl;
                        cout << "Judul baru  : "; getline(cin, nt);
                        cout << "Artis baru  : "; getline(cin, na);
                        cout << "Album baru  : "; getline(cin, nal);
                        cout << "Durasi baru : "; getline(cin, nd);

                        Song baru;
                        baru.title = nt;
                        baru.artist = na;
                        baru.album = nal;
                        baru.duration = mmssToSeconds(nd);
                        editSong(S, baru);
                    } else if (pa == "4") {
                         cout << "\n=== SONG LIST ===\n";
                        showSongs(songs.first);
                    } else if (pa == "5") {
                        stopAdmin = true;
                    }
                }
            } else {
                AdrUser U = loginUser(users, u, p);

                if (!U) {
                    continue;
                }

                bool stopUser = false;

                while (!stopUser) {

                    cout << "\n=== USER MENU ===\n";
                    cout << "1. Play\n2. Search song\n3. Create playlist\n";
                    cout << "4. List playlist\n5. Edit playlist\n6. Delete playlist\n7. Logout\nPilih: ";
                    string pu; getline(cin, pu);

                    if (pu == "1") {
                         cout << "\n=== PLAY ===\n";
                        cout << "Judul lagu: ";
                        string t; getline(cin, t);
                        AdrSong S = searchSongInGlobal(songs, t);

                        if (!S) {
                            cout << "Tidak ada.\n";
                        } else {
                            cout << "Now playing: " << S->info.title << endl;
                        }
                    } else if (pu == "2") {
                         cout << "\n=== SEARCH ===\n";
                        cout << "Keyword: ";
                        string q; getline(cin, q);
                        AdrSong C = songs.first;

                        while (C) {
                            if (C->info.title.find(q) != string::npos) {
                                cout << C->info.title << endl;
                            }

                            C = C->next;
                        }
                    } else if (pu == "3") {
                        cout << "\n=== CREATE ===\n";
                        cout << "Nama playlist: ";
                        string pn; getline(cin, pn);
                        insertLastPlaylist(U, allocatePlaylist(pn));
                    } else if (pu == "4") {
                         cout << "\n=== LIST PLAYLIST ===\n";
                        showPlaylists(U);
                    } else if (pu == "5") {
                         cout << "\n=== EDIT ===\n";
                        cout << "Nama playlist: ";
                        string pn; getline(cin, pn);
                        AdrPlaylist P = searchPlaylist(U, pn);

                        if (!P) {
                            continue;
                        }

                        cout << "\n=== PLAYLIST MENU ===\n";
                        cout << "1. Add song\n2. Remove song\n3. Rename\nPilih: ";
                        string ep; getline(cin, ep);

                        if (ep == "1") {
                            cout << "\n=== ADD ===\n";
                            cout << "Judul lagu: ";
                            string t; getline(cin, t);
                            AdrSong S = searchSongInGlobal(songs, t);
                            if (S) addSongToPlaylistFromGlobal(P, S);
                        } else if (ep == "2") {
                            cout << "\n=== REMOVE ===\n";
                            cout << "Judul lagu: ";
                            string t; getline(cin, t);
                            removeSongFromPlaylist(P, t);
                        } else if (ep == "3") {
                            cout << "\n=== RENAME ===\n";
                            cout << "Nama baru: ";
                            string n; getline(cin, n);
                            editPlaylistName(P, n);
                        }
                    } else if (pu == "6") {
                        cout << "\n=== DELETE ===\n";
                        cout << "Nama playlist: ";
                        string pn; getline(cin, pn);
                        deletePlaylist(U, pn);
                    } else if (pu == "7") {
                        stopUser = true;
                    }
                }
            }
        } else if (pilih == "2") {
            string u,p;

            cout << "\n=== CREATE  ===\n";
            cout << "Username baru: "; getline(cin, u);
            cout << "Password baru: "; getline(cin, p);

            if (!usernameExists(users, u)) {
                insertLastUser(users, allocateUser(u,p));
            }
        } else if (pilih == "3") {
            cout << "\n=== DELETE ===\n";
            cout << "Username: ";
            string u; getline(cin, u);

            deleteUser(users, u);
        } else if (pilih == "4") break;
    }

    return 0;
}