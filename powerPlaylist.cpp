//Tommy and Kat's final project: creating a perfect party playlist by uploading several people's Apple Music library, determining the favorite genre, and playing 2 songs from that genre for every song not from that genre
//the BST of songs will sort so that songs with greater numPlays go on the left which cuts down on runtime because we select a song by generating a random number and in-order traversing the tree and stopping each song's numPlays from the random number

#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <fstream>
using namespace std;





struct song {
	string genre;
	string title;
	string album;
	string artist;
	int numPlays;
	int length; //seconds
	song* left;
	song* right;
};

struct BST{
	song* root;
};

struct person {
	int totalPlays;
	BST tree;
};


int main (int argc, char** argv){

	//-------------------Setup Number of people/ songs and build each person's tree
	int numPeople, partyLength;
	vector<person*> musicGurus; //vector of pointers to people that will loop through when playing songs; build songs


	cout << "How many people are contributing songs?" << endl;
	cin >> numPeople;
	cout << "How long is your party?" << endl;
	cin >> partyLength;
	for (int i=0; i< numPeople; i++){
		person* sample;
		musicGurus.push_back(sample);
	}



	//build tree
	ifstream ifs;
	ifs.open("songsList.txt");
	if (!ifs) { return 1; cout << "Error opening file. " << endl; }

	int num_songs, song_time, song_plays;
	string name, time, artist, album, plays, genre;

	cout << "How many songs will you have? " << endl;
	cin >> num_songs;
        int songPer= num_songs/numPeople;


	for (int i=0; i< numPeople; i++){


		for (int i = 0; i < songPer; i++) {
 			song newSong;
			getline(ifs, newSong.title, ',');
			getline(ifs, time, ',');
			getline(ifs, newSong.artist, ',');
			getline(ifs, newSong.album, ',');
			getline(ifs, plays, ',');
			getline(ifs, newSong.genre);

			song_time = (time[0]-48) * 60 + (time[2]-48) * 10 + (time[3]-48);
                        cout << plays;
			song_plays = stoi(plays);

			newSong.length= song_time;
			newSong.numPlays= song_plays;
			newSong.left= NULL;
			newSong.right= NULL;
						
		}
		//read in and update array
		//for 1/3 songs, read in
		//create song
		//push to musicGurus[i]->tree[treeIndex]

          }
	

			//-------------------count total songs per person and overall genre favorite
			//
			//
			//-------------------generate playlist








	return 0;

}
