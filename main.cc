#include "Musik.h"
#include <iostream>

using namespace std;

int main() {
    ListUser users;
    ListGlobalSong songs;
    AdrSong playFront = nullptr, playRear = nullptr;

    createListUser(users);
    createListGlobalSong(songs);

    bool run = true;

    while (run) {
        string pilih;

        cout << "\n===== AMBATUSING =====\n";
        cout << "1. Login\n2. Create User\n3. Delete User\n4. Exit\nPilih: ";
        cin >> pilih;

        if (pilih == "1") {
            string u,p;

            cout << "\n===== LOGIN =====\n";
            cout << "Username : "; cin >> u;
            cout << "Password : "; cin >> p;

            if (u == "admin" && p == "admin123") {
                bool admin = true;

                while (admin) {
                    string a;

                    cout << "\n===== ADMIN MENU =====\n";
                    cout << "1. Add Song\n2. Delete Song\n3. Edit Song\n4. Song List\n5. Logout\nPilih: ";
                    cin >> a;

                    if (a == "1") {
                        string t,ar,al,du;

                        cout << "\n===== ADD SONG =====\n";
                        cout << "Judul          : "; cin >> t;
                        cout << "Artis          : "; cin >> ar;
                        cout << "Album          : "; cin >> al;
                        cout << "Durasi (mm:ss) : "; cin >> du;

                        insertLastGlobalSong(songs, allocateSong(t,ar,al,mmssToSeconds(du)));
                    } else if (a == "2") {
                        string t;

                        cout << "\n===== DELETE SONG =====\n";
                        cout << "Judul : "; cin >> t;

                        deleteSongFromGlobal(songs, t);
                    } else if (a == "3") {
                        string t;

                        cout << "\n===== EDIT SONG =====\n";
                        cout << "Judul lagu yang diedit : ";
                        cin >> t;

                        AdrSong S = searchSongInGlobal(songs, t);

                        if (S) {
                            Song newData;
                            string du;

                            cout << "Judul          : "; cin >> newData.title;
                            cout << "Artis          : "; cin >> newData.artist;
                            cout << "Album          : "; cin >> newData.album;
                            cout << "Durasi (mm:ss) : "; cin >> du;

                            newData.duration = mmssToSeconds(du);
                            editSong(S, newData);

                            cout << "Lagu berhasil diedit.\n";
                        } else {
                            cout << "Lagu tidak ditemukan.\n";
                        }
                    } else if (a == "4") {
                        cout << "\n===== SONG LIST ===== \n";
                        showSongs(songs.first);
                    } else admin = false;
                }
            } else {
                AdrUser U = loginUser(users, u, p);

                if (U) {
                    bool user = true;
                    while (user) {
                        string pu;

                        cout << "\n===== USER MENU =====\n";
                        cout << "1. Play Song/Playlist\n2. Search Song\n3. Create Playlist\n";
                        cout << "4. Search Playlist\n5. Edit Playlist\n6. Delete Playlist\n";
                        cout << "7. Play Next (Queue)\n8. Logout\nPilih: ";
                        cin >> pu;

                        if (pu == "1") {
                            string x;

                            cout << "\n===== PLAY =====\n";
                            cout << "1. Song\n2. Playlist\nPilih : ";
                            cin >> x;

                            if (x == "1") {
                                string t;

                                cout << "\nJudul : "; cin >> t;
                                enqueuePlaySong(playFront, playRear, searchSongInGlobal(songs, t));
                            } else {
                                string pn;

                                cout << "\nNama : "; cin >> pn;
                                AdrPlaylist P = searchPlaylist(U, pn);

                                if (P) {
                                    AdrSong S = P->firstSong;

                                    while (S) {
                                        enqueuePlaySong(playFront, playRear, S);
                                        S = S->next;
                                    }
                                }
                            }
                        } else if (pu == "2") {
                            string t;

                            cout << "\n===== SEARCH SONG =====\n";
                            cout << "Judul : "; cin >> t;

                            AdrSong S = searchSongInGlobal(songs, t);

                            if (S) {
                                cout << S->info.title << endl;
                            }
                        } else if (pu == "3") {
                            string pn;

                            cout << "\n===== CREATE PLAYLIST =====\n";
                            cout << "Nama : "; cin >> pn;

                            insertLastPlaylist(U, allocatePlaylist(pn));
                        } else if (pu == "4") {
                            string pn;

                            cout << "\n===== SEARCH PLAYLIST =====\n";
                            cout << "Nama : "; cin >> pn;

                            if (searchPlaylist(U, pn)) {
                                cout << "Playlist ditemukan\n";
                            } else {
                                cout << "Tidak ditemukan\n";
                            }
                        } else if (pu == "5") {
                            string pn;

                            cout << "\n===== EDIT PLAYLIST =====\n";
                            cout << "Nama : "; cin >> pn;

                            AdrPlaylist P = searchPlaylist(U, pn);

                            if (P) {
                                string e;

                                cout << "1.Add Song\n2.Remove Song\n3.Rename\nPilih :";
                                cin >> e;

                                if (e == "1") {
                                    string t;

                                    cout << "\nJudul : "; cin >> t;
                                    AdrSong S = searchSongInGlobal(songs, t);

                                    if (S) {
                                        addSongToPlaylistFromGlobal(P, S);
                                    }
                                } else if (e == "2") {
                                    string t;

                                    cout << "\nJudul : "; cin >> t;
                                    removeSongFromPlaylist(P, t);
                                } else {
                                    string n;

                                    cout << "\nNama : "; cin >> n;
                                    editPlaylistName(P, n);
                                }
                            }
                        } else if (pu == "6") {
                            string pn;

                            cout << "\n===== DELETE PLAYLIST =====\n";
                            cout << "Nama : "; cin >> pn;

                            deletePlaylist(U, pn);
                        } else if (pu == "7") {
                            playNextFromQueue(playFront);
                        } else {
                            user = false;
                        }
                    }
                }
            }
        } else if (pilih == "2") {
            string u,p;

            cout << "\n===== CREATE USER =====\n";
            cout << "Username : "; cin >> u;
            cout << "Password : "; cin >> p;

            if (!usernameExists(users, u)) {
                insertLastUser(users, allocateUser(u,p));
            }
        } else if (pilih == "3") {
            string u;

            cout << "\n===== DELETE USER =====\n";
            cout << "Username : "; cin >> u;

            deleteUser(users, u);
        } else run = false;
    }

    return 0;
}
