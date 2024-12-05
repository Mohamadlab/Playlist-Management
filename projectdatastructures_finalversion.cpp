#include <iostream>
#include <string>
#include <ctime> // For srand
#include <cstdlib> // For rand

using namespace std;

// Define a structure for a song
struct Song {
    string title;
    string artist;
    int duration; // Duration of the song in seconds
    Song* next;
    Song* prev;

    // Constructor
    Song(string _title, string _artist, int _duration) : title(_title), artist(_artist), duration(_duration), next(nullptr), prev(nullptr) {}
};

// Define a class for the playlist
class Playlist {
private:
    Song* head;
    Song* tail;
    Song* currentSong;
    int size;

public:
    // Constructor
    Playlist() : head(nullptr), tail(nullptr), currentSong(nullptr), size(0) {}

    // Destructor to deallocate memory
    ~Playlist() {
        while (head != nullptr) {
            Song* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Function to add a song to the playlist
    void addSong(string title, string artist, int duration) {
        Song* newSong = new Song(title, artist, duration);
        if (head == nullptr) {
            head = newSong;
            tail = newSong;
            currentSong = newSong;
        } else {
            tail->next = newSong;
            newSong->prev = tail;
            tail = newSong;
        }
        size++;
    }

    // Function to play the current song
    void playCurrentSong() {
        if (currentSong != nullptr)
            cout << "Now playing: " << currentSong->title << " - " << currentSong->artist << " (" << currentSong->duration << " seconds)" << endl;
        else
            cout << "No song is currently selected." << endl;
    }

    // Function to move to the next song
    void nextSong() {
        if (currentSong != nullptr && currentSong->next != nullptr)
            currentSong = currentSong->next;
        else
            cout << "End of playlist reached." << endl;
    }

    // Function to move to the previous song
    void prevSong() {
        if (currentSong != nullptr && currentSong->prev != nullptr)
            currentSong = currentSong->prev;
        else
            cout << "Beginning of playlist reached." << endl;
    }

    // Function to display the playlist
    void displayPlaylist() {
        Song* current = head;
        cout << "Playlist:" << endl;
        while (current != nullptr) {
            cout << "Title: " << current->title << ", Artist: " << current->artist << ", Duration: " << current->duration << " seconds" << endl;
            current = current->next;
        }
    }

    // Function to remove a song from the playlist
    void removeSong(string title) {
        Song* current = head;
        while (current != nullptr) {
            if (current->title == title) {
                if (current == head) {
                    head = head->next;
                    if (head != nullptr)
                        head->prev = nullptr;
                    delete current;
                    size--;
                    return;
                } else if (current == tail) {
                    tail = tail->prev;
                    tail->next = nullptr;
                    delete current;
                    size--;
                    return;
                } else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                    delete current;
                    size--;
                    return;
                }
            }
            current = current->next;
        }
        cout << "Song '" << title << "' not found in the playlist." << endl;
    }

    // Function to repeat the playlist
    void repeatPlaylist() {
        if (size == 0) {
            cout << "Playlist is empty." << endl;
            return;
        }
        Song* temp = head;
        cout << "Repeating playlist:" << endl;
        while (temp != nullptr) {
            cout << "Title: " << temp->title << ", Artist: " << temp->artist << ", Duration: " << temp->duration << " seconds" << endl;
            temp = temp->next;
        }
    }

    // Function to shuffle the playlist
    void shufflePlaylist() {
        if (size == 0) {
            cout << "Playlist is empty." << endl;
            return;
        }

        // Seed the random number generator
        srand(time(nullptr));

        // Create an array to store shuffled indices
        int* indices = new int[size];
        for (int i = 0; i < size; ++i)
            indices[i] = i;

        // Shuffle the indices
        for (int i = size - 1; i > 0; --i) {
            int j = rand() % (i + 1);
            swap(indices[i], indices[j]);
        }

        // Traverse the shuffled indices and play songs accordingly
        cout << "Shuffled playlist:" << endl;
        for (int i = 0; i < size; ++i) {
            Song* temp = head;
            for (int j = 0; j < indices[i]; ++j)
                temp = temp->next;
            cout << "Title: " << temp->title << ", Artist: " << temp->artist << ", Duration: " << temp->duration << " seconds" << endl;
        }

        delete[] indices;
    }
};

// Function to display menu options
void displayMenu() {
    cout << "========== Playlist Management System ==========" << endl;
    cout << "1. Add a song" << endl;
    cout << "2. Remove a song" << endl;
    cout << "3. Shuffle the playlist" << endl;
    cout << "4. Repeat the playlist" << endl;
    cout << "5. Display playlist" << endl;
    cout << "6. Play current song" << endl;
    cout << "7. Move to next song" << endl;
    cout << "8. Move to previous song" << endl;
    cout << "9. Exit" << endl;
    cout << "Enter your choice: ";
}

int main()
{
    Playlist myPlaylist;

    int choice;
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                string title, artist;
                int duration;
                cout << "Enter song title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter artist name: ";
                getline(cin, artist);
                cout << "Enter duration (in seconds): ";
                cin >> duration;
                myPlaylist.addSong(title, artist, duration);
                cout << "Song added to the playlist." << endl;
                break;
            }
            case 2: {
                string title;
                cout << "Enter song title to remove: ";
                cin.ignore();
                getline(cin, title);
                myPlaylist.removeSong(title);
                break;
            }
            case 3:
                myPlaylist.shufflePlaylist();
                break;
            case 4:
                myPlaylist.repeatPlaylist();
                break;
            case 5:
                myPlaylist.displayPlaylist();
                break;
            case 6:
                myPlaylist.playCurrentSong();
                break;
            case 7:
                myPlaylist.nextSong();
                break;
            case 8:
                myPlaylist.prevSong();
                break;
            case 9:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }
    } while (choice != 9);

    return 0;
}
