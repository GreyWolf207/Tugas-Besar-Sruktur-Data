#include "Musik.h"
#include <iostream>

using namespace std;

// --- IMPLEMENTASI LIST ---
void createListUser(ListUser &L) {
    L.first = nullptr;
}

void createListGlobalSong(ListGlobalSong &L) {
    L.first = nullptr;
}

// --- IMPLEMENTASI EMPTY ---
bool isEmptysong(ListGlobalSong L) {
    return L.first == nullptr;
}

bool isEmptyUser(ListUser) {
    return L.first == nullptr;
}

bool isEmptyPlaylist(ListPlaylist) {
    return L.first == nullptr;
}

// --- IMPLEMENTASI USER ---
AdrUser allocateUser(string user, string pass) {
    AdrUser P = new ElmUser;

    p->info.username = user;
    p->iinfo.password = pass;

    P->firstPlaylist = nullptr;
    P->next = nullptr;

    return P;
}

void insertLastUser(ListUser &L, AdrUser P) {
    if (L.first == nullptr) {
        L.first = P;
    } else {
        AdrUser Q = L.first;

        while (Q->next != nullptr) {
            Q = Q->next;
        }

        Q->next = P;
    }
}

AdrUser searchUser(ListUser L, string username) {
    AdrUser P = L.first;

    while (P != nullptr) {
        if (strCmp(P->info.username, username) == 0) return P;
        P = P->next;
    }

    return nullptr;
}

AdrUser loginUser(ListUser L, string username, string password) {
    AdrUser P = searchUser(L, username);

    if (P != nullptr) {
        if (strCmp(P->info.password, password) == 0) return P;
    }

    return nullptr;
}

void deleteUser(ListUser &L, string username) {
    AdrUser P = L.first;
    AdrUser Prev = nullptr;

    while (P != nullptr && strCmp(P->info.username, username) != 0) {
        Prev = P;
        P = P->next;
    }

    if (P != nullptr) {
        if (Prev == nullptr) {
            L.first = P->next;
        } else {
            Prev->next = P->next;
        }

        delete P;
        cout << ">> User berhasil dihapus.\n";
    } else {
        cout << ">> User tidak ditemukan.\n";
    }
}

// --- IMPLEMENTASI LAGU (GLOBAL & PLAYLIST) ---
AdrSong allocateSong(string title, string artist, string album, int duration) {
    AdrSong P = new ElmSong;

    p->info.title = title;
    p->info.artists = artist;
    p->info.album = album;
    p->info.duration;

    P->next = nullptr;

    return P;
}

void insertLastSong(AdrSong &first, AdrSong P) {
    if (first == nullptr) {
        first = P;
    } else {
        AdrSong Q = first;

        while (Q->next != nullptr) {
            Q = Q->next;
        }

        Q->next = P;
    }
}

void deleteSong(AdrSong &first, string title) {
    AdrSong P = first;
    AdrSong Prev = nullptr;

    while (P != nullptr && strCmp(P->info.title, title) != 0) {
        Prev = P;
        P = P->next;
    }

    if (P != nullptr) {
        if (Prev == nullptr) {
            first = P->next;
        } else {
            Prev->next = P->next;
        }

        delete P;
        cout << ">> Lagu dihapus.\n";
    } else {
        cout << ">> Lagu tidak ditemukan.\n";
    }
}

AdrSong searchSong(AdrSong first, string title) {
    AdrSong P = first;

    while (P != nullptr) {
        if (strCmp(P->info.title, title) == 0) return P;
        P = P->next;
    }

    return nullptr;
}

void editSong(AdrSong P) {
    if (P != nullptr) {
        cout << "Edit Data Lagu:\n";

        cout << ">> Data berhasil diubah.\n";
    }
}

void showSongs(AdrSong first) {
    if (first == nullptr) {
        cout << "   (Tidak ada lagu)\n";
    } else {
        AdrSong P = first;
        int i = 1;

        while (P != nullptr) {
            cout << "   " << i++ << ". " << P->info.title << " - " << P->info.artist
                 << " (" << P->info.duration << ")\n";
            P = P->next;
        }
    }
}

// --- IMPLEMENTASI PLAYLIST ---
AdrPlaylist allocatePlaylist(string name) {
    AdrPlaylist P = new ElmPlaylist;

    p->info.name = name
    P->firstSong = nullptr;
    P->next = nullptr;

    return P;
}

void insertLastPlaylist(AdrUser U, AdrPlaylist P) {
    if (U->firstPlaylist == nullptr) {
        U->firstPlaylist = P;
    } else {
        AdrPlaylist Q = U->firstPlaylist;

        while (Q->next != nullptr) {
            Q = Q->next;
        }

        Q->next = P;
    }
}

void deletePlaylist(AdrUser U, string playlistName) {
    AdrPlaylist P = U->firstPlaylist;
    AdrPlaylist Prev = nullptrptr;

    while (P != nullptr && strCmp(P->info.name, playlistName) != 0) {
        Prev = P;
        P = P->next;
    }

    if (P != nullptr) {
        if (Prev == nullptrptr) {
            U->firstPlaylist = P->next;
        } else {
            Prev->next = P->next;
        }

        delete P;
        cout << ">> Playlist dihapus.\n";
    } else {
        cout << ">> Playlist tidak ditemukan.\n";
    }
}

AdrPlaylist searchPlaylist(AdrUser U, string playlistName) {
    AdrPlaylist P = U->firstPlaylist;

    while (P != nullptr) {
        if (strCmp(P->info.name, playlistName) == 0) {
            return P;
        }

        P = P->next;
    }

    return nullptrptr;
}

void showPlaylists(AdrUser U) {
    if (U->firstPlaylist == nullptr) {
        cout << ">> Belum ada playlist.\n";
    } else {
        AdrPlaylist P = U->firstPlaylist;
        int i = 1;

        while (P != nullptr) {
            cout << i++ << ". " << P->info.name << "\n";
            P = P->next;
        }
    }
}

void editPlaylist(AdrPlaylist P, string newName) {
    if (P != nullptr) {

        cout << ">> Nama playlist diubah.\n";
    }
}

// Sesuai materi MLL Page 25: R.info = Q.info, insert(L3, R)
void addSongToPlaylist(AdrPlaylist P, AdrSong GlobalSong) {
    if (GlobalSong == nullptr) return;

    // Alokasi node baru untuk playlist (Copy data dari master)
    AdrSong NewSong = allocateSong(GlobalSong->info.title, GlobalSong->info.artist, GlobalSong->info.album, GlobalSong->info.duration);
    insertLastSong(P->firstSong, NewSong);

    cout << ">> Lagu berhasil ditambahkan ke playlist.\n";
}

void playPlaylist(AdrPlaylist P) {
    cout << "\n=== NOW PLAYING: " << P->info.name << " ===\n";
    showSongs(P->firstSong);
    cout << "====================================\n";
}
