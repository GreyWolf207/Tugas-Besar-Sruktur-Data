#ifndef Musik_H
#define Musik_H

#include <iostream>

using namespace std;

// Pointer Definitions
typedef struct ElmSong* AdrSong;
typedef struct ElmPlaylist* AdrPlaylist;
typedef struct ElmUser* AdrUser;

struct Song {
    string title, artist, album;
    int duration;
};

struct User {
    string username, password;
};

struct Playlist {
    string name;
};

// Node Lagu (Grandchild / Global)
struct ElmSong {
    Song info;
    AdrSong next;
};

// Node Playlist (Child)
struct ElmPlaylist {
    Playlist info;
    AdrSong firstSong;
    AdrPlaylist next;
};

// Node User (Parent)
struct ElmUser {
    User info;
    AdrPlaylist firstPlaylist;
    AdrUser next;
};

// List Definitions
struct ListUser {
    AdrUser first;
};

struct ListGlobalSong {
    AdrSong first;
};

struct ListPlaylist {
    AdrPlaylist first;
};

// Manajemen List
void createListUser(ListUser &L);
void createListSong(ListGlobalSong &L);

// Mengecek Empty
bool isEmptysong(ListGlobalSong L);
bool isEmptyUser(ListUser);
bool isEmptyPlaylist(ListPlaylist);

// Manajemen User
AdrUser allocateUser(string user, string pass);
void insertLastUser(ListUser &L, AdrUser P);
void deleteUser(ListUser &L, string username);
AdrUser searchUser(ListUser L, string username);
AdrUser loginUser(ListUser L, string username, string password);

// Manajemen Lagu Global (Admin)
AdrSong allocateSong(string title, string artist, string album, int dur);
void insertLastSong(AdrSong &first, AdrSong P); // Digunakan untuk global & playlist
void deleteSong(AdrSong &first, string title);
AdrSong searchSong(AdrSong first, string title);
void editSong(AdrSong P);
void showSongs(AdrSong first);

// Manajemen Playlist (User)
AdrPlaylist allocatePlaylist(string name);
void insertLastPlaylist(AdrUser U, AdrPlaylist P);
void deletePlaylist(AdrUser U, string playlistName);
AdrPlaylist searchPlaylist(AdrUser U, string playlistName);
void showPlaylists(AdrUser U);
void editPlaylist(AdrPlaylist P, string newName);

// Menambahkan lagu ke playlist
void addSongToPlaylist(AdrPlaylist P, AdrSong GlobalSong);
void playPlaylist(AdrPlaylist P);

#endif
