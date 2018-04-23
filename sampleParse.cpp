#include <iostream>
#include <fstream>
#include <string>



using namespace std;

int main() {

    ifstream ifs;
    ifs.open("songsList.txt");
    if (!ifs) { return 1; cout << "Error opening file. " << endl; }
   
    int num_songs, song_time, song_plays;
    string name, time, artist, album, plays, genre;

    cout << "How many songs will you have? " << endl;
    cin >> num_songs;

    for (int i = 0; i < num_songs; i++) {
        getline(ifs, name, ',');
        getline(ifs, time, ',');
        getline(ifs, artist, ',');
        getline(ifs, album, ',');
        getline(ifs, plays, ',');
        getline(ifs, genre);

        song_time = (time[0]-48) * 60 + (time[2]-48) * 10 + (time[3]-48);
        //cout << "song time: " << song_time << endl;
        song_plays = stoi(plays);
        //cout << "song plays: " << song_plays << endl;
    }


    

    return 0;
}
