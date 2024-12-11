#include <iostream>
#include "playlist.cpp"

using namespace std;

int main() {
    Playlist* playlists = nullptr;
    int choice;
    string playlistName, title, singer, filename; // Deklarasi variabel

    while (true) {
        cout << "\n=== Playlist Manager ===\n";
        cout << "1. Buat Playlist\n";
        cout << "2. Tambahkan lagu dalam playlist\n";
        cout << "3. Tampilkan Playlist\n";
        cout << "4. Hapus lagu\n";
        cout << "5. Cari lagu (judul)\n";
        cout << "6. Menyimpan Playlist ke file\n";
        cout << "7. Exit\n";
        cout << "8. Mawu masukin file?\n";
        cout << "Masukkan pilihan: ";
        cin >> choice;

        // Memproses pilihan pengguna
        if (choice == 7) {
            cout << "Keluar dari program..." << endl;
            deletePlaylist(playlists);
            break;
        }

        switch (choice) {
            case 1: {
                cout << "Masukkan nama playlist: ";
                cin >> playlistName;
                createPlaylist(playlists, playlistName);
                cout << "Playlist '" << playlistName << "' berhasil dibuat!\n";
                break;
            }
            case 2: {
                cout << "Masukkan nama playlist: ";
                cin >> playlistName;
                Playlist* current = playlists;
                while (current != nullptr && current->name != playlistName) {
                    current = current->next;
                }
                if (current == nullptr) {
                    cout << "Playlist tidak ditemukan!\n";
                } else {
                    cout << "Masukkan judul lagu: ";
                    cin >> title;
                    cout << "Masukkan penyanyi: ";
                    cin >> singer;
                    addSong(current, title, singer);
                    cout << "Lagu berhasil ditambahkan ke playlist '" << playlistName << "'!\n";
                }
                break;
            }
            case 3: {
                Playlist* current = playlists;
                if (current == nullptr) {
                    cout << "Belum ada playlist yang dibuat.\n";
                } else {
                    while (current != nullptr) {
                        cout << "\nPlaylist: " << current->name << endl;
                        displaySongs(current);
                        current = current->next;
                    }
                }
                break;
            }
            case 4: {
                cout << "Masukkan nama playlist: ";
                cin >> playlistName;
                Playlist* current = playlists;
                while (current != nullptr && current->name != playlistName) {
                    current = current->next;
                }
                if (current == nullptr) {
                    cout << "Playlist tidak ditemukan!\n";
                } else {
                    cout << "Masukkan judul lagu yang ingin dihapus: ";
                    cin >> title;
                    removeSong(current, title);
                }
                break;
            }
            case 5: {
                cout << "Masukkan nama playlist: ";
                cin >> playlistName;
                Playlist* current = playlists;
                while (current != nullptr && current->name != playlistName) {
                    current = current->next;
                }
                if (current == nullptr) {
                    cout << "Playlist tidak ditemukan!\n";
                } else {
                    cout << "Masukkan judul lagu yang ingin dicari: ";
                    cin >> title;
                    Song* song = current->head;
                    bool found = false;
                    while (song != nullptr) {
                        if (song->title == title) {
                            cout << "Lagu ditemukan: " << song->title << " oleh " << song->singer << endl;
                            found = true;
                            break;
                        }
                        song = song->next;
                    }
                    if (!found) {
                        cout << "Lagu tidak ditemukan di playlist ini.\n";
                    }
                }
                break;
            }
            case 6: {
    if (playlists == nullptr) {
        cout << "Tidak ada playlist untuk disimpan!\n";
    } else {
        cout << "Masukkan nama file untuk menyimpan semua playlist: ";
        cin >> filename;
        saveAllPlaylistsToFile(playlists, filename);
    }
    break;
}

case 8: {
    cout << "Masukkan nama file untuk dimuat: ";
    cin >> filename;
    loadFileTxt(playlists, filename);
    break;
}

              default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
                break;
        }
    }

    return 0;
}
