#include "Musik.h"
#include <iostream>

using namespace std;

//CREATE LIST
void createListUser(ListUser &L) {
    L.first = nullptr;
}

void createListGlobalSong(ListGlobalSong &L) {
    L.first = nullptr;
}

// ALLOCATE
AdrUser allocateUser(const string &username, const string &password) {
    AdrUser P = new ElmUser;

    P->info.username = username;
    P->info.password = password;
    P->firstPlaylist = nullptr;
    P->next = nullptr;

    return P;
}

AdrPlaylist allocatePlaylist(const string &name) {
    AdrPlaylist P = new ElmPlaylist;

    P->info.name = name;
    P->firstSong = nullptr;
    P->next = nullptr;

    return P;
}

AdrSong allocateSong(const string &title, const string &artist, const string &album, int duration) {
    AdrSong P = new ElmSong;

    P->info.title = title;
    P->info.artist = artist;
    P->info.album = album;
    P->info.duration = duration;
    P->next = nullptr;

    return P;
}

// INSERT
void insertLastUser(ListUser &L, AdrUser P) {
    if (L.first == nullptr) {
        L.first = P;
    } else {
        AdrUser Q = L.first;

        while (Q->next) {
            Q = Q->next;
        }

        Q->next = P;
    }
}

void insertLastPlaylist(AdrUser U, AdrPlaylist P) {
    if (U->firstPlaylist == nullptr) {
        U->firstPlaylist = P;
    } else {
        AdrPlaylist Q = U->firstPlaylist;

        while (Q->next) {
            Q = Q->next;
        }

        Q->next = P;
    }
}

void insertLastSong(AdrSong &first, AdrSong P) {
    if (first == nullptr) {
        first = P;
    } else {
        AdrSong Q = first;

        while (Q->next) {
            Q = Q->next;
        }

        Q->next = P;
    }
}

void insertLastGlobalSong(ListGlobalSong &L, AdrSong P) {
    insertLastSong(L.first, P);
}

// LOGIN
AdrUser loginUser(const ListUser &L, const string &username, const string &password) {
    AdrUser P = L.first;

    while (P) {
        if (P->info.username == username && P->info.password == password) {
            return P;
        }

        P = P->next;
    }

    return nullptr;
}

bool usernameExists(const ListUser &L, const string &username) {
    return (searchUser(L, username) != nullptr);
}

// SEARCH
AdrUser searchUser(const ListUser &L, const string &username) {
    AdrUser P = L.first;

    while (P) {
        if (P->info.username == username) {
            return P;
        }

        P = P->next;
    }

    return nullptr;
}

AdrPlaylist searchPlaylist(AdrUser U, const string &playlistName) {
    AdrPlaylist P = U->firstPlaylist;

    while (P) {
        if (P->info.name == playlistName) {
            return P;
        }

        P = P->next;
    }

    return nullptr;
}

AdrSong searchSong(AdrSong first, const string &title) {
    AdrSong P = first;

    while (P) {
        if (P->info.title == title) {
            return P;
        }

        P = P->next;
    }

    return nullptr;
}

AdrSong searchSongInGlobal(const ListGlobalSong &L, const string &title) {
    return searchSong(L.first, title);
}

// DELETE
void deleteUser(ListUser &L, const string &username) {
    AdrUser P = L.first, Prev = nullptr;

    while (P && P->info.username != username) {
        Prev = P;
        P = P->next;
    }

    if (!P) {
        return;
    }

    if (Prev == nullptr) {
        L.first = P->next;
    } else {
        Prev->next = P->next;
    }
}

void deletePlaylist(AdrUser U, const string &playlistName) {
    AdrPlaylist P = U->firstPlaylist, Prev = nullptr;

    while (P && P->info.name != playlistName) {
        Prev = P;
        P = P->next;
    }

    if (!P) {
        return;
    }

    if (Prev == nullptr) {
        U->firstPlaylist = P->next;
    } else {
        Prev->next = P->next;
    }
}

void deleteSongFromGlobal(ListGlobalSong &L, const string &title) {
    AdrSong P = L.first, Prev = nullptr;

    while (P && P->info.title != title) {
        Prev = P;
        P = P->next;
    }

    if (!P) {
        return;
    }

    if (Prev == nullptr) {
        L.first = P->next;
    } else {
        Prev->next = P->next;
    }
}

void removeSongFromPlaylist(AdrPlaylist PL, const string &songTitle) {
    AdrSong S = PL->firstSong, Prev = nullptr;

    while (S && S->info.title != songTitle) {
        Prev = S;
        S = S->next;
    }

    if (!S) {
        return;
    }

    if (Prev == nullptr) {
        PL->firstSong = S->next;
    } else {
        Prev->next = S->next;
    }
}

// ADD
void addSongToPlaylistFromGlobal(AdrPlaylist P, AdrSong G) {
    AdrSong copy = allocateSong(G->info.title, G->info.artist, G->info.album, G->info.duration);
    insertLastSong(P->firstSong, copy);
}

// EDIT
void editSong(AdrSong P, const Song &newData) {
    if (P) {
        P->info = newData;
    }
}

void editPlaylistName(AdrPlaylist P, const string &newName) {
    if (P) {
        P->info.name = newName;
    }
}

// SHOW
void showSongs(AdrSong first) {
    int i = 1;

    while (first) {
        cout << i++ << ". " << first->info.title << " - " << first->info.artist << " (" << secondsToMMSS(first->info.duration) << ")\n";
        first = first->next;
    }
}

void showPlaylists(AdrUser U) {
    AdrPlaylist P = U->firstPlaylist;

    while (P) {
        cout << "- " << P->info.name << "\n";
        P = P->next;
    }
}

void showSongsInPlaylist(AdrPlaylist P) {
    showSongs(P->firstSong);
}

void playPlaylist(AdrPlaylist P) {
    cout << "\n=== PLAYLIST : " << P->info.name << " ===\n";
    showSongs(P->firstSong);
}

// HELPER
int mmssToSeconds(const string &mmss) {
    int pos = mmss.find(':');
    int m = stoi(mmss.substr(0, pos));
    int s = stoi(mmss.substr(pos + 1));

    return m * 60 + s;
}

string secondsToMMSS(int sec) {
    int m = sec / 60, s = sec % 60;
    return to_string(m) + ":" + (s < 10 ? "0" : "") + to_string(s);
}