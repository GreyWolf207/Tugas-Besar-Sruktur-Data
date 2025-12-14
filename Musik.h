#ifndef MUSIK_H
#define MUSIK_H

#include <iostream>
using namespace std;

// ADDRESS
typedef struct ElmSong* AdrSong;
typedef struct ElmPlaylist* AdrPlaylist;
typedef struct ElmUser* AdrUser;

// DATA
struct Song {
    string title;
    string artist;
    string album;
    int duration;
};

struct Playlist {
    string name;
};

struct User {
    string username;
    string password;
};

// ELEMEN
struct ElmSong {
    Song info;
    AdrSong next;
};

struct ElmPlaylist {
    Playlist info;
    AdrSong firstSong;
    AdrPlaylist next;
};

struct ElmUser {
    User info;
    AdrPlaylist firstPlaylist;
    AdrUser next;
};

// LIST
struct ListUser {
    AdrUser first;
};

struct ListGlobalSong {
    AdrSong first;
};

// CREATE
void createListUser(ListUser &L);
void createListGlobalSong(ListGlobalSong &L);

// ALLOCATE
AdrUser allocateUser(string username, string password);
AdrPlaylist allocatePlaylist(string name);
AdrSong allocateSong(string title, string artist, string album, int duration);

// INSERT
void insertLastUser(ListUser &L, AdrUser P);
void insertLastPlaylist(AdrUser U, AdrPlaylist P);
void insertLastSong(AdrSong &first, AdrSong P);
void insertLastGlobalSong(ListGlobalSong &L, AdrSong P);

// LOGIN
AdrUser loginUser(ListUser &L, string username, string password);
bool usernameExists(ListUser &L, string username);

// SEARCH
AdrUser searchUser(ListUser &L, string username);
AdrPlaylist searchPlaylist(AdrUser U, string playlistName);
AdrSong searchSong(AdrSong first, string title);
AdrSong searchSongInGlobal(ListGlobalSong &L, string title);

// DELETE
void deleteUser(ListUser &L, string username);
void deletePlaylist(AdrUser U, string playlistName);
void deleteSongFromGlobal(ListGlobalSong &L, string title);
void removeSongFromPlaylist(AdrPlaylist P, string songTitle);

// PLAYLIST
void addSongToPlaylistFromGlobal(AdrPlaylist P, AdrSong G);

// EDIT
void editSong(AdrSong P, Song newData);
void editPlaylistName(AdrPlaylist P, string newName);

// SHOW
void showSongs(AdrSong first);
void showPlaylists(AdrUser U);
void playPlaylist(AdrPlaylist P);

// HELPER
int mmssToSeconds(string mmss);
string secondsToMMSS(int sec);

// QUEUE SONG
void enqueuePlaySong(AdrSong &front, AdrSong &rear, AdrSong S);
void playNextFromQueue(AdrSong &front);

#endif
