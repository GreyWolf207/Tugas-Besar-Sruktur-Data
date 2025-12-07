#include "Musik.h"
#include <iostream>

using namespace std;

int myStrLen(const char* s) {
    int len = 0;
    while (s[len] != '\0') len++;
    return len;
}

int myStrCmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

void myStrCpy(char* dest, const char* src) {
    while ((*dest++ = *src++));
}

void inputString(const char* prompt, char* variable, int maxLength) {
    cout << prompt;
    cin.getline(variable, maxLength);
}

// --- IMPLEMENTASI ADT ---

void createApplication(Application &app) {
    app.headUser = NULL;
    app.headGlobalSong = NULL;
}

// 1. MANAJEMEN LAGU GLOBAL (ADMIN)

void insertGlobalSong(Application &app, char* title, char* artist, char* album, char* duration) {
    Song* newSong = new Song;
    myStrCpy(newSong->title, title);
    myStrCpy(newSong->artist, artist);
    myStrCpy(newSong->album, album);
    myStrCpy(newSong->duration, duration);
    newSong->next = NULL;

    if (app.headGlobalSong == NULL) {
        app.headGlobalSong = newSong;
    } else {
        Song* temp = app.headGlobalSong;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newSong;
    }
    cout << ">> Lagu berhasil ditambahkan ke database master.\n";
}

void showGlobalSongs(Application &app) {
    if (app.headGlobalSong == NULL) {
        cout << ">> Database lagu kosong.\n";
        return;
    }
    Song* temp = app.headGlobalSong;
    int i = 1;
    cout << "\n=== DAFTAR LAGU MASTER ===\n";
    while (temp != NULL) {
        cout << i++ << ". " << temp->title << " - " << temp->artist << " [" << temp->duration << "]\n";
        temp = temp->next;
    }
    cout << "--------------------------\n";
}

Song* searchGlobalSong(Application &app, char* title) {
    Song* temp = app.headGlobalSong;
    while (temp != NULL) {
        if (myStrCmp(temp->title, title) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void deleteGlobalSong(Application &app, char* title) {
    if (app.headGlobalSong == NULL) return;

    Song* temp = app.headGlobalSong;
    Song* prev = NULL;

    while (temp != NULL && myStrCmp(temp->title, title) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        cout << ">> Lagu tidak ditemukan.\n";
        return;
    }

    if (prev == NULL) { // Hapus head
        app.headGlobalSong = temp->next;
    } else {
        prev->next = temp->next;
    }
    delete temp;
    cout << ">> Lagu berhasil dihapus.\n";
}

void editGlobalSong(Application &app, char* title) {
    Song* song = searchGlobalSong(app, title);
    if (song != NULL) {
        cout << "Edit Data (Biarkan kosong jika tidak ingin ubah tidak didukung, ketik ulang):\n";
        inputString("Judul Baru: ", song->title, 100);
        inputString("Artis Baru: ", song->artist, 100);
        inputString("Album Baru: ", song->album, 100);
        inputString("Durasi Baru: ", song->duration, 10);
        cout << ">> Lagu berhasil diupdate.\n";
    } else {
        cout << ">> Lagu tidak ditemukan.\n";
    }
}

// 2. MANAJEMEN USER

void createUser(Application &app, char* user, char* pass) {
    User* newUser = new User;
    myStrCpy(newUser->username, user);
    myStrCpy(newUser->password, pass);
    newUser->headPlaylist = NULL;
    newUser->next = NULL;

    if (app.headUser == NULL) {
        app.headUser = newUser;
    } else {
        User* temp = app.headUser;
        while (temp->next != NULL) temp = temp->next;
        temp->next = newUser;
    }
    cout << ">> User berhasil dibuat.\n";
}

User* loginUser(Application &app, char* user, char* pass) {
    User* temp = app.headUser;
    while (temp != NULL) {
        if (myStrCmp(temp->username, user) == 0 && myStrCmp(temp->password, pass) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void deleteUser(Application &app, char* user) {
    if (app.headUser == NULL) return;
    User* temp = app.headUser;
    User* prev = NULL;

    while (temp != NULL && myStrCmp(temp->username, user) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        cout << ">> User tidak ditemukan.\n";
        return;
    }

    // Harusnya menghapus semua playlist dan lagu user dulu (cleanup), tapi disederhanakan
    if (prev == NULL) {
        app.headUser = temp->next;
    } else {
        prev->next = temp->next;
    }
    delete temp;
    cout << ">> User berhasil dihapus.\n";
}

// 3. MANAJEMEN PLAYLIST

void createPlaylist(User* user, char* name) {
    Playlist* newP = new Playlist;
    myStrCpy(newP->name, name);
    newP->headSong = NULL;
    newP->next = NULL;

    if (user->headPlaylist == NULL) {
        user->headPlaylist = newP;
    } else {
        Playlist* temp = user->headPlaylist;
        while (temp->next != NULL) temp = temp->next;
        temp->next = newP;
    }
    cout << ">> Playlist '" << name << "' berhasil dibuat.\n";
}

Playlist* searchPlaylist(User* user, char* name) {
    Playlist* temp = user->headPlaylist;
    while (temp != NULL) {
        if (myStrCmp(temp->name, name) == 0) return temp;
        temp = temp->next;
    }
    return NULL;
}

void deletePlaylist(User* user, char* name) {
    if (user->headPlaylist == NULL) return;
    Playlist* temp = user->headPlaylist;
    Playlist* prev = NULL;

    while (temp != NULL && myStrCmp(temp->name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        cout << ">> Playlist tidak ditemukan.\n";
        return;
    }
    if (prev == NULL) user->headPlaylist = temp->next;
    else prev->next = temp->next;
    
    delete temp;
    cout << ">> Playlist dihapus.\n";
}

void editPlaylist(User* user, char* oldName, char* newName) {
    Playlist* p = searchPlaylist(user, oldName);
    if (p) {
        myStrCpy(p->name, newName);
        cout << ">> Nama playlist diubah.\n";
    } else {
        cout << ">> Playlist tidak ditemukan.\n";
    }
}

void showPlaylists(User* user) {
    if (user->headPlaylist == NULL) {
        cout << ">> Belum ada playlist.\n";
        return;
    }
    Playlist* temp = user->headPlaylist;
    int i = 1;
    cout << "\n=== PLAYLIST MILIK " << user->username << " ===\n";
    while (temp != NULL) {
        cout << i++ << ". " << temp->name << "\n";
        temp = temp->next;
    }
}

// 4. MANAJEMEN LAGU DALAM PLAYLIST

void addSongToPlaylist(Playlist* playlist, Song* songData) {
    // Kita copy data lagu dari master ke playlist node agar independen
    Song* newSong = new Song;
    myStrCpy(newSong->title, songData->title);
    myStrCpy(newSong->artist, songData->artist);
    myStrCpy(newSong->album, songData->album);
    myStrCpy(newSong->duration, songData->duration);
    newSong->next = NULL;

    if (playlist->headSong == NULL) {
        playlist->headSong = newSong;
    } else {
        Song* temp = playlist->headSong;
        while (temp->next != NULL) temp = temp->next;
        temp->next = newSong;
    }
    cout << ">> Lagu ditambahkan ke playlist.\n";
}

void playPlaylist(Playlist* playlist) {
    if (playlist->headSong == NULL) {
        cout << ">> Playlist kosong.\n";
        return;
    }
    Song* temp = playlist->headSong;
    cout << "\n[ NOW PLAYING - " << playlist->name << " ]\n";
    while (temp != NULL) {
        cout << "🎵 " << temp->title << " - " << temp->artist << "\n";
        // Simulasi next track
        temp = temp->next;
    }
    cout << "[ End of Playlist ]\n";
}