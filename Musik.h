#ifndef MUSIK_H_INCLUDED
#define MUSIK_H_INCLUDED

#include <iostream>

using namespace std;

typedef struct Lagu* adrLag;
typedef struct User* adrUsr;
typedef struct Playlist* adrPla;

struct Lagu {
    string judul, artis, album;
    int durasi;
};

struct User {
    int ID;
    string username;
};

struct Playlist {
    string namaPlaylist, namaUser;
    int jumlahLagu;
};

struct elmLag {
    Lagu info;
    adrLag next;
};

struct elmUsr {
    User info;
    adrLag next;
};

struct elmPla {
    Playlist info;
    adrPla next;
};

struct ListLag {
    adrLag first, last;
};

struct ListUsr {
    adrUsr first, last;
};

struct ListPla {
    adrPla first, last;
};

void createSongList(ListLag L);
void createUserList(ListUsr U);
void createPlaylistList(ListPla P);

adrLag allocateSong(Lagu L);
adrUsr allocateUser(User U);
adrPla allocatePlaylist(Playlist P);

void printInfo();

void insertSong();
void editSong();
void deleteSong();

#endif // MUSIK_H_INCLUDED
