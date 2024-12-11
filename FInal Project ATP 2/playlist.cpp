#include <iostream>
#include <fstream>
#include <string>
#include "playlist.h"
using namespace std;

void createPlaylist(Playlist*& playlists, const string& name) {
    Playlist* newPlaylist = new Playlist;
    newPlaylist->name = name;
    newPlaylist->head = nullptr;
    newPlaylist->next = playlists;
    playlists = newPlaylist;
}

void addSong(Playlist* playlist, const string& title, const string& singer) {
    Song* newSong = new Song;
    newSong->title = title;
    newSong->singer = singer;
    newSong->next = playlist->head;
    playlist->head = newSong;
}

void displaySongs(const Playlist* playlist) {
    const Song* current = playlist->head;
    while (current != nullptr) {
        cout << "Title: " << current->title << ", Singer: " << current->singer << endl;
        current = current->next;
    }
}

void removeSong(Playlist* playlist, const string& title) {
    Song *current = playlist->head, *prev = nullptr;

    while (current != nullptr && current->title != title) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Lagu tidak ditemukan!" << endl;
        return;
    }

    if (prev == nullptr) {
        playlist->head = current->next;
    } else {
        prev->next = current->next;
    }

    delete current;
    cout << "Lagu '" << title << "' telah dihapus." << endl;
}

void saveAllPlaylistsToFile(const Playlist* playlists, const string& filename) {
    string filenameWithExt = filename;
    if (filenameWithExt.size() < 4 || filenameWithExt.substr(filenameWithExt.size() - 4) != ".txt") {
        filenameWithExt += ".txt";
    }

    ofstream file(filenameWithExt);
    if (!file) {
        cout << "Gagal membuka file untuk menulis!" << endl;
        return;
    }

    const Playlist* currentPlaylist = playlists;
    while (currentPlaylist != nullptr) {
        file << "Playlist: " << currentPlaylist->name << endl;
        const Song* currentSong = currentPlaylist->head;
        while (currentSong != nullptr) {
            file << currentSong->title << "|" << currentSong->singer << endl;
            currentSong = currentSong->next;
        }
        file << endl; // Pisahkan playlist dengan baris kosong
        currentPlaylist = currentPlaylist->next;
    }

    file.close();
    cout << "Semua playlist telah disimpan ke file '" << filenameWithExt << "'." << endl;
}

void loadFileTxt(Playlist*& playlists, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Gagal membuka file untuk membaca!" << endl;
        return;
    }

    string line, playlistName, title, singer;
    Playlist* currentPlaylist = nullptr;

    while (getline(file, line)) {
        // kalau baris kosong, lewati
        if (line.empty()) {
            continue;
        }

        // kalau baris dimulai dengan "Playlist:", itu artinya nama playlist
        if (line.substr(0, 9) == "Playlist:") {
            playlistName = line.substr(10); // mengambil nama playlist setelah "Playlist: "
            createPlaylist(playlists, playlistName); 
            currentPlaylist = playlists; 
        } else {
            // Membaca judul dan penyanyi dari satu baris (pemisah '|')
            size_t separator = line.find('|');
            if (separator != string::npos) {
                title = line.substr(0, separator);
                singer = line.substr(separator + 1);
                if (currentPlaylist != nullptr) {
                    addSong(currentPlaylist, title, singer); // Tambahkan lagu ke playlist
                }
            }
        }
    }

    file.close();
    cout << "Data dari file '" << filename << "' telah dimuat ke program." << endl;
}

void sortSongs(Playlist* playlist) {
    if (!playlist->head || !playlist->head->next) return; 

    for (Song* i = playlist->head; i->next != nullptr; i = i->next) {
        for (Song* j = i->next; j != nullptr; j = j->next) {
           
            if (i->title > j->title) {
               
                swap(i->title, j->title);
                swap(i->singer, j->singer);
            }
        }
    }
}


void deletePlaylist(Playlist*& playlists) {
    while (playlists != nullptr) {
        Playlist* tempPlaylist = playlists;
        Song* currentSong = playlists->head;

        while (currentSong != nullptr) {
            Song* tempSong = currentSong;
            currentSong = currentSong->next;
            delete tempSong;
        }

        playlists = playlists->next;
        delete tempPlaylist;
    }
}
