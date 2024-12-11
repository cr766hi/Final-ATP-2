#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
using namespace std;


struct Song {
    string title;
    string singer;
    Song* next;
};

struct Playlist {
    string name;
    Song* head;
    Playlist* next;
};

// Deklarasi fungsi
void createPlaylist(Playlist*& playlists, const string& name);
void addSong(Playlist* playlist, const string& title, const string& singer);
void displaySongs(const Playlist* playlist);
void removeSong(Playlist* playlist, const string& title);
void sortSongs(Playlist* playlist, bool bySinger);
void saveAllPlaylistsToFile(const Playlist* playlist, const string& filename);
void deletePlaylist(Playlist*& playlists);
void loadFileTxt(Playlist*& playlists, const string& filename);


#endif
