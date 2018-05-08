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
#include <set>

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
    cout << root->title << " " << root-> numPlays <<  " " << root-> genre << endl; //<< (root->left)->title
    in_order_traverse(root->right);
}

void findFav(song * root, int * currNum, int randNum, int * flag, song * foundSong) {
    //cout << "Inside find fav" << endl;
    if (root == nullptr) return;

    if (*flag == 0) findFav(root->left, currNum, randNum,flag, foundSong);
    *currNum += root->numPlays;
    //cout << "currNum " << *currNum << endl;
    if (*currNum >= randNum && (*flag==0)) {
        //cout << "   Found fav: " << root->title << " with " << root->numPlays << " plays, and time: " <<  
        //root->length << root->genre<< endl;
        foundSong-> genre= root->genre;
        foundSong->length = root->length;
        foundSong->title= root-> title;
        foundSong->numPlays= root-> numPlays;
        foundSong-> album= root-> album;
        foundSong-> artist= root-> artist;
        foundSong-> left= root-> left;
        foundSong -> right = root-> right;
        *flag = 1; 
        return;
    }
    if (*flag == 0) findFav(root->right, currNum, randNum, flag, foundSong);
}


void delete_tree(song * n) { // Recursively deconstruct binary trees
    if (n->left) delete_tree(n->left);
    if (n->right) delete_tree(n->right);
    delete n;
}



int main (int argc, char** argv){

    //-------------------Setup Number of people/ songs and build each person's tree
    int numPeople = 3, partyLength;
    vector<person> musicGurus; //vector of pointers to people that will loop through when playing songs; build songs
    unordered_map <string, int> genreCount;
    int playsCounterForRand;

    //cout << "How many people are contributing songs?" << endl;
    //cin >> numPeople;
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

    cout << "How many total songs will you have?" << endl;
    cin >> num_songs;
    int songPer= num_songs/numPeople;



    int numSongsInserted=0;
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
        numSongsInserted ++;

    }

    //calc favorite genre 
    int compareCount=0;
    string favGenre="";
    for (auto it = genreCount.begin(); it != genreCount.end(); it++){
        if (it-> second > compareCount){
            compareCount = it->second;
            favGenre= it->first;
            //cout << "\nfav Genre \n" << favGenre << " " << it->second << endl;
        }
    }


    /* for (int i = 0; i < musicGurus.size(); i++){
       in_order_traverse(musicGurus[i].tree.root);
    //cout << "plays: " << musicGurus[i].totalPlays << endl;
    }

*/
    srand (0); //http://en.cppreference.com/w/cpp/numeric/random/srand

    int timeElapsed = 0, randNum, total, found, index = 0;
    int favSongsPlayed=0, wouldHaveBeenTime=0;
    int totalingSongs=0;
    song foundSong, unpopularSong;
    foundSong.length=0;
    queue <song> unpopular;
    queue <song> popular;
    vector <song> playlist;
    set<string> already_played;

    while (timeElapsed < partyLength) {

        randNum = rand() % musicGurus[index].totalPlays;
        total = 0;
        found = 0;
        totalingSongs++;

        //play two songs from popular genre right away followed by unpopular genre song, if exists. If have already played 2 from favorite genre, play 1 unpopular; Regardless, do something with the foundSong, whether that's play it right away, add to unpopular queue, or add to popular queue
        if (totalingSongs <= numSongsInserted){
            findFav(musicGurus[index].tree.root,&total,randNum, &found, &foundSong);
            if (already_played.count(foundSong.title)==0) {

                timeElapsed += foundSong.length;
                //cout << "_" << favGenre << "_  _" << foundSong.genre << "_ " << endl;
                if (favGenre.compare(0,3,foundSong.genre,0,3)==0){
                    popular.push(foundSong);
                    //cout << "pushed popular " << foundSong.title << endl;
                } else {
                    unpopular.push(foundSong);
                    //cout << "pushed unpopular" << foundSong.title << endl;
                }

                already_played.insert(foundSong.title);
            }
            //cout << "time el" << timeElapsed << endl;
            index++;
            if (index == numPeople) index = 0;


        }
        //cout << "after time el" << endl;

    }
    int timeElapsedRuntime=0;

    song popularSong;
    int backupIndex=0;
    while (timeElapsedRuntime <= partyLength){
        song popularSong;
        song unpopularSong;
        if (!popular.empty()){
            if (favSongsPlayed == 2 && !unpopular.empty() ){
                unpopularSong= unpopular.front();
                playlist.push_back(unpopularSong);
                timeElapsedRuntime += unpopularSong.length;
                        
                if (timeElapsedRuntime % 60 < 10) {
                    cout << unpopularSong.title << " (" << unpopularSong.artist << ")," << timeElapsedRuntime/60 << ":0" << timeElapsedRuntime % 60  <<  endl;
                } else {
                   cout << unpopularSong.title << " (" << unpopularSong.artist << ")," << timeElapsedRuntime / 60 << ":" << timeElapsedRuntime % 60 << endl; 
                }
                unpopular.pop();
                favSongsPlayed =0;

            }
            popularSong= popular.front();
            timeElapsedRuntime += popularSong.length;
            //cout << popularSong.title << "," << timeElapsedRuntime/60 << ":" << timeElapsedRuntime %60  <<  endl;
            if (timeElapsedRuntime % 60 < 10) {
                    cout << popularSong.title << " (" << popularSong.artist << ")," << timeElapsedRuntime/60 << ":0" << timeElapsedRuntime % 60  <<  endl;
                } else {
                   cout << popularSong.title << " (" << popularSong.artist << ")," << timeElapsedRuntime / 60 << ":" << timeElapsedRuntime % 60 << endl; 
                }

            playlist.push_back(popularSong);

            favSongsPlayed++;
            popular.pop();


        }
        else if (!unpopular.empty()){
            unpopularSong= unpopular.front();
            timeElapsedRuntime += unpopularSong.length;
             if (timeElapsedRuntime % 60 < 10) {
                    cout << unpopularSong.title << " (" << unpopularSong.artist << ")," << timeElapsedRuntime/60 << ":0" << timeElapsedRuntime % 60  <<  endl;
                } else {
                   cout << unpopularSong.title << " (" << unpopularSong.artist << ")," << timeElapsedRuntime / 60 << ":" << timeElapsedRuntime % 60 << endl; 
                }

                        playlist.push_back(unpopularSong);

            unpopular.pop();
        } else {
            //cout << playlist[backupIndex].title << "," << timeElapsedRuntime/60 << ":" << timeElapsedRuntime %60 <<  endl;
           if (timeElapsedRuntime % 60 < 10) {
                    cout << playlist[backupIndex].title << " (" << playlist[backupIndex].artist << ")," << timeElapsedRuntime/60 << ":0" << timeElapsedRuntime % 60  <<  endl;
                } else {
                   cout << playlist[backupIndex].title << " (" << playlist[backupIndex].artist << ")," << timeElapsedRuntime / 60 << ":" << timeElapsedRuntime % 60 << endl; 
                }
 
            backupIndex++;
            timeElapsedRuntime+= playlist[backupIndex].length;
            if (backupIndex == num_songs){
                backupIndex=0;
            }
        }

    }
   
       while (timeElapsed <= partyLength){
       findFav(musicGurus[index].tree.root,&total,randNum, &found, &foundSong);
       totalingSongs++;
       if (totalingSongs <= numSongsInserted){
       if (favSongsPlayed == 2 && !unpopular.empty() ){
       unpopularSong= unpopular.front();
       timeElapsed += unpopularSong.length;
       cout << "Party time elapsed: " << timeElapsed/60 << " minutes and " << timeElapsed %60 << " seconds " << "title genre " << unpopularSong.title << "  " << unpopularSong.genre <<  endl;
       unpopular.pop();
       favSongsPlayed =0;
       }
       if (foundSong.genre == favGenre){
       timeElapsed += foundSong.length;
       cout << "Party time elapsed: " << timeElapsed/60 << " minutes and " << timeElapsed %60 << " seconds " << "title genre " << foundSong.title << "  " << foundSong.genre << endl;
       favSongsPlayed++;
       } else {
       unpopular.push(foundSong);
       }
       }
       else {   //have accessed number of songs put in so need to play from the queue to fill up to the time
       unpopularSong= unpopular.front();
       timeElapsed += unpopularSong.length;
       cout << "Party time elapsed: " << timeElapsed/60 << " minutes and " << timeElapsed %60 << " seconds " << "title genre " << unpopularSong.title << "  " << unpopularSong.genre <<  endl;
       unpopular.pop(); 
       }
       }
       
    //read in and update array
    //for 1/3 songs, read in
    //create song
    //push to musicGurus[i]->tree[treeIndex]

    for (int a = 0; a < musicGurus.size(); a++) {
        delete_tree(musicGurus[a].tree.root);
    }

    //generate popular and unpopular queue. If a song's genre is the favorite genre, add it to the popular queue right away. 
    return 0;
}
