//Tommy and Kat's final project: creating a perfect party playlist by uploading several people's Apple Music library, determining the favorite genre, and playing 2 songs from that genre for every song not from that genre
//the BST of songs will sort so that songs with greater numPlays go on the left which cuts down on runtime because we select a song by generating a random number and in-order traversing the tree and stopping each song's numPlays from the random number

#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <unordered_map>
#include <stdio.h>

using namespace std;

#define streq(a, b) (a.compare(b)==0)

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
    void insert(song *);
    void findFav(song * root);
};

struct person {
    int totalPlays;
    BST tree;
};


// Methods


void BST::insert(song * newSong) {
    if (root == nullptr) {
        root = new song{newSong->genre, newSong->title, newSong->album, newSong->artist, 
            newSong->numPlays, newSong->length, newSong->left, newSong->right};
        return;
    }
    song * curr = root;

    // Inserts in the opposite direction of a BST
    song * prev = curr;
    bool wentLeft=0;

    while (curr != nullptr) {
        prev= curr;
        if (newSong->numPlays > curr->numPlays) {
            curr = curr->left;
            wentLeft= 1;
        }
        else {
            curr = curr->right;
            wentLeft=0;
        }

    }

    curr = new song{newSong->genre, newSong->title, newSong->album, newSong->artist, 
        newSong->numPlays, newSong->length, newSong->left, newSong->right};
    if (wentLeft) prev->left= curr;
    else prev->right= curr;

    return;

}


// Functions


void in_order_traverse(song * root) {

    if (root == nullptr) return;
    in_order_traverse(root->left);
    cout << root->title << " " << root-> numPlays <<  endl; //<< (root->left)->title
    in_order_traverse(root->right);
}

void findFav(song * root, int * currNum, int randNum, int * flag, song * foundSong) {
    //cout << "Inside find fav" << endl;
    if (root == nullptr) return;

    if (*flag == 0) findFav(root->left, currNum, randNum,flag, foundSong);
    *currNum += root->numPlays;
    //cout << "currNum " << *currNum << endl;
    if (*currNum >= randNum && (*flag==0)) {
        cout << "Now playing: " << root->title << " with " << root->numPlays << " plays, and time: " <<  
        root->length << endl;
        foundSong->length = root->length;
        *flag = 1; 
        return;
    }
    if (*flag == 0) findFav(root->right, currNum, randNum, flag, foundSong);
}




int main (int argc, char** argv){

    //-------------------Setup Number of people/ songs and build each person's tree
    int numPeople, partyLength;
    vector<person> musicGurus; //vector of pointers to people that will loop through when playing songs; build songs
    unordered_map <string, int> genreCount;
    int playsCounterForRand;

    cout << "How many people are contributing songs?" << endl;
    cin >> numPeople;
    cout << "How long is your party (in minutes)?" << endl;
    cin >> partyLength;
    partyLength *= 60;

    for (int i=0; i< numPeople; i++){
        person sample;
        sample.totalPlays = 0;
        sample.tree.root = NULL;

        musicGurus.push_back(sample);
    }



    //build tree
    ifstream ifs;
    ifs.open("songsList.txt");
    if (!ifs) { return 1; cout << "Error opening file. " << endl; }

    int num_songs, song_time, song_plays;
    string name, time, artist, album, plays, genre;

    cout << "How many total songs will you have? " << endl;
    cin >> num_songs;
    int songPer= num_songs/numPeople;




    for (int i = 0; i < num_songs - num_songs % songPer; i++) {
        song newSong;
        getline(ifs, newSong.title, ',');
        getline(ifs, time, ',');
        getline(ifs, newSong.artist, ',');
        getline(ifs, newSong.album, ',');
        getline(ifs, plays, ',');
        getline(ifs, newSong.genre);

        song_time = (time[0]-48) * 60 + (time[2]-48) * 10 + (time[3]-48);
        //cout << song_time << endl;
        if (newSong.title[0] == '"' || newSong.artist[0] == '"' || newSong.album[0] == '"') continue;
        song_plays = stoi(plays);

        newSong.length= song_time;
        newSong.numPlays= song_plays;
        newSong.left= NULL;
        newSong.right= NULL;
        genreCount[newSong.genre] = genreCount[newSong.genre]+ 1;
        musicGurus[i/songPer].tree.insert(&newSong); // I believe this line is what we need
        musicGurus[i/songPer].totalPlays += newSong.numPlays;
    }

    for (int i = 0; i < musicGurus.size(); i++){
        in_order_traverse(musicGurus[i].tree.root);
        //cout << "plays: " << musicGurus[i].totalPlays << endl;
    }


    // generate random #

    //srand((int)time(NULL)) % 100;

    //% musicGurus[0].totalPlays;
    srand(1);

    int timeElapsed = 0, randNum, total, found, index = 0;
    song foundSong;
    foundSong.length=0;

    while (timeElapsed < partyLength) {

        randNum = rand() % musicGurus[index].totalPlays;
        total = 0;
        found = 0;
        //cout << "rand num " << randNum << endl; 
        //cout << "rand num " << randNum << endl;
        //cout << "total plays for this person " << musicGurus[index].totalPlays << endl;

        //&foundSong = NULL;
        findFav(musicGurus[index].tree.root,&total,randNum, &found, &foundSong);
        timeElapsed += foundSong.length;
        cout << "Party time elapsed: " << timeElapsed/60 << " minutes and " << timeElapsed %60 << 
        " seconds " <<  endl;;
        index++;
        if (index == numPeople) index = 0;

    }

    //read in and update array
    //for 1/3 songs, read in
    //create song
    //push to musicGurus[i]->tree[treeIndex]


    //-------------------count total songs per person and overall genre favorite
    //
    //
    //-------------------generate playlist



    return 0;
}

