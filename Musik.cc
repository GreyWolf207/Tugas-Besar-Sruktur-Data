#include "Musik.h"
#include <iostream>

using namespace std;

// CREATE
void createListUser(ListUser &L) {
    L.first = nullptr;
}

void createListGlobalSong(ListGlobalSong &L) {
    L.first = nullptr;
}

// ALLOCATE
AdrUser allocateUser(string username, string password) {
    AdrUser P = new ElmUser;

    P->info.username = username;
    P->info.password = password;
    P->firstPlaylist = nullptr;
    P->next = nullptr;

    return P;
}

AdrPlaylist allocatePlaylist(string name) {
    AdrPlaylist P = new ElmPlaylist;

    P->info.name = name;
    P->firstSong = nullptr;
    P->next = nullptr;

    return P;
}

AdrSong allocateSong(string title, string artist, string album, int duration) {
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
    if (!L.first) {
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
    if (!U->firstPlaylist) {
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
    if (!first) {
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
AdrUser loginUser(ListUser &L, string username, string password) {
    AdrUser P = L.first;

    while (P) {
        if (P->info.username == username && P->info.password == password) {
            return P;
        }

        P = P->next;
    }

    return nullptr;
}

bool usernameExists(ListUser &L, string username) {
    return searchUser(L, username) != nullptr;
}

// SEARCH
AdrUser searchUser(ListUser &L, string username) {
    AdrUser P = L.first;

    while (P) {
        if (P->info.username == username) {
            return P;
        }

        P = P->next;
    }

    return nullptr;
}

AdrPlaylist searchPlaylist(AdrUser U, string playlistName) {
    AdrPlaylist P = U->firstPlaylist;

    while (P) {
        if (P->info.name == playlistName) {
            return P;
        }

        P = P->next;
    }

    return nullptr;
}

AdrSong searchSong(AdrSong first, string title) {
    while (first) {
        if (first->info.title == title) {
            return first;
        }

        first = first->next;
    }

    return nullptr;
}

AdrSong searchSongInGlobal(ListGlobalSong &L, string title) {
    return searchSong(L.first, title);
}

// DELETE
void deleteUser(ListUser &L, string username) {
    AdrUser P = L.first, prev = nullptr;

    while (P && P->info.username != username) {
        prev = P;
        P = P->next;

    }

    if (!P) {
        return;
    }

    if (!prev) {
        L.first = P->next;
    } else {
        prev->next = P->next;
    }
}

void deletePlaylist(AdrUser U, string playlistName) {
    AdrPlaylist P = U->firstPlaylist, prev = nullptr;

    while (P && P->info.name != playlistName) {
        prev = P;
        P = P->next;
    }

    if (!P) {
        return;
    }

    if (!prev) {
        U->firstPlaylist = P->next;
    } else {
        prev->next = P->next;
    }
}

void deleteSongFromGlobal(ListGlobalSong &L, string title) {
    AdrSong P = L.first, prev = nullptr;

    while (P && P->info.title != title) {
        prev = P;
        P = P->next;
    }

    if (!P) {
        return;
    }

    if (!prev) {
        L.first = P->next;
    } else {
        prev->next = P->next;
    }
}

void removeSongFromPlaylist(AdrPlaylist P, string songTitle) {
    AdrSong S = P->firstSong, prev = nullptr;

    while (S && S->info.title != songTitle) {
        prev = S;
        S = S->next;
    }

    if (!S) {
        return;
    }

    if (!prev) {
        P->firstSong = S->next;
    } else {
        prev->next = S->next;
    }
}

// PLAYLIST
void addSongToPlaylistFromGlobal(AdrPlaylist P, AdrSong G) {
    AdrSong S = allocateSong( G->info.title, G->info.artist, G->info.album, G->info.duration);
    insertLastSong(P->firstSong, S);
}

// EDIT
void editSong(AdrSong P, Song newData) {
    if (P) {
        P->info = newData;
    }
}

void editPlaylistName(AdrPlaylist P, string newName) {
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
        cout << "- " << P->info.name << endl;
        P = P->next;
    }
}

void playPlaylist(AdrPlaylist P) {
    cout << "PLAYLIST: " << P->info.name << endl;
    showSongs(P->firstSong);
}

// HELPER
int mmssToSeconds(string mmss) {
    int m = 0, s = 0, i = 0;

    while (mmss[i] != ':') {
        m = m * 10 + (mmss[i] - '0');
        i++;
    }

    i++;

    while (mmss[i] != '\0') {
        s = s * 10 + (mmss[i] - '0');
        i++;
    }

    return m * 60 + s;
}

string secondsToMMSS(int sec) {
    int m = sec / 60;
    int s = sec % 60;
    return to_string(m) + ":" + (s < 10 ? "0" : "") + to_string(s);
}

// QUEUE SONG
void enqueuePlaySong(AdrSong &front, AdrSong &rear, AdrSong S) {
    if (!S) {
        cout << "Lagu tidak ditemukan.\n";
        return;
    }

    AdrSong Q = allocateSong(S->info.title, S->info.artist, S->info.album, S->info.duration);

    if (!front) {
        front = rear = Q;
    } else {
        rear->next = Q;
        rear = Q;
    }

    cout << "Lagu masuk ke queue.\n";
}

void playNextFromQueue(AdrSong &front) {
    if (!front) {
        cout << "Queue kosong.\n";
        return;
    }

    cout << "Now Playing: " << front->info.title << " - " << front->info.artist << endl;

    AdrSong temp = front;
    front = front->next;
    temp = nullptr;
}
