// spotify.h
#ifndef SPOTIFY_H
#define SPOTIFY_H

#include <iostream>

using namespace std;

// Struktur untuk Lagu (Song)
struct Song {
    char title[100];
    char artist[100];
    char album[100];
    char duration[10]; // Format mm:ss
    Song* next;
};

// Struktur untuk Playlist
struct Playlist {
    char name[100];
    Song* headSong; // Menunjuk ke lagu pertama dalam playlist
    Playlist* next;
};

// Struktur untuk User
struct User {
    char username[50];
    char password[50];
    Playlist* headPlaylist; // Menunjuk ke playlist pertama user
    User* next;
};

// Struktur Global untuk menyimpan pointer utama
struct Application {
    User* headUser;
    Song* headGlobalSong; // Lagu master (dikelola Admin)
};

// --- FUNGSI BANTUAN (UTILITIES) ---
int myStrCmp(const char* s1, const char* s2);
void myStrCpy(char* dest, const char* src);
void myStrCat(char* dest, const char* src);
int myStrLen(const char* s);
void inputString(const char* prompt, char* variable, int maxLength);

// --- FUNGSI ADT ---

// Manajemen Global
void createApplication(Application &app);

// Manajemen Lagu (Master / Admin)
void insertGlobalSong(Application &app, char* title, char* artist, char* album, char* duration);
void deleteGlobalSong(Application &app, char* title);
void editGlobalSong(Application &app, char* title);
void showGlobalSongs(Application &app);
Song* searchGlobalSong(Application &app, char* title);

// Manajemen User
void createUser(Application &app, char* user, char* pass);
User* loginUser(Application &app, char* user, char* pass);
void deleteUser(Application &app, char* user);

// Manajemen Playlist (User)
void createPlaylist(User* user, char* name);
void deletePlaylist(User* user, char* name);
void editPlaylist(User* user, char* oldName, char* newName);
Playlist* searchPlaylist(User* user, char* name);
void showPlaylists(User* user);

// Manajemen Lagu dalam Playlist
void addSongToPlaylist(Playlist* playlist, Song* songData); // Mengcopy data dari global ke playlist
void playPlaylist(Playlist* playlist);

#endif