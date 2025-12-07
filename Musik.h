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

// CREATE LIST
void createListUser(ListUser &L);
void createListGlobalSong(ListGlobalSong &L);

// ALLOCATE
AdrUser allocateUser(const string &username, const string &password);
AdrPlaylist allocatePlaylist(const string &name);
AdrSong allocateSong(const string &title, const string &artist, const string &album, int duration);

// INSERT
void insertLastUser(ListUser &L, AdrUser P);
void insertLastPlaylist(AdrUser U, AdrPlaylist P);
void insertLastSong(AdrSong &first, AdrSong P);
void insertLastGlobalSong(ListGlobalSong &L, AdrSong P);

// LOGIN
AdrUser loginUser(const ListUser &L, const string &username, const string &password);
bool usernameExists(const ListUser &L, const string &username);

// SEARCH
AdrUser searchUser(const ListUser &L, const string &username);
AdrPlaylist searchPlaylist(AdrUser U, const string &playlistName);
AdrSong searchSong(AdrSong first, const string &title);
AdrSong searchSongInGlobal(const ListGlobalSong &L, const string &title);

// DTELETE
void deleteUser(ListUser &L, const string &username);
void deletePlaylist(AdrUser U, const string &playlistName);
void deleteSongFromGlobal(ListGlobalSong &L, const string &title);
void removeSongFromPlaylist(AdrPlaylist P, const string &songTitle);

// ADD SONG
void addSongToPlaylistFromGlobal(AdrPlaylist P, AdrSong GlobalSong);

// EDIT
void editSong(AdrSong P, const Song &newData);
void editPlaylistName(AdrPlaylist P, const string &newName);

// SHOW
void showSongs(AdrSong first);
void showPlaylists(AdrUser U);
void showSongsInPlaylist(AdrPlaylist P);
void playPlaylist(AdrPlaylist P);

// HELPER
int mmssToSeconds(const string &mmss);
string secondsToMMSS(int seconds);

#endif
