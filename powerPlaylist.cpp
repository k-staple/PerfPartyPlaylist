//Tommy and Kat's final project: creating a perfect party playlist by uploading several people's Apple Music library, determining the favorite genre, and playing 2 songs from that genre for every song not from that genre
//the BST of songs will sort so that songs with greater numPlays go on the left which cuts down on runtime because we select a song by generating a random number and in-order traversing the tree and stopping each song's numPlays from the random number

#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;



struct person {
  int totalPlays;
  BST tree;
};

struct song {
  string genre;
  string title;
  string album;
  string artist;
  int numPlays;
  int length; //seconds
};
  
typename vector<song> BST;
  

int main (int argc, char** argv){

//-------------------Setup Number of people/ songs and build each person's tree
  int numPeople, partyLength;
  vector<*person> musicGurus; //vector of pointers to people that will loop through when playing songs; build songs


  cout << "How many people are contributing songs?" << endl;
  cin >> numPeople;
  cout << "How long is your party?" << endl;
  cin >> partyLength;
  for (int i=0; i< numPeople; i++){
    person* sample;
    musicGurus.push_back(sample);
  }
  
  

  //build tree
  for (int i=0; i< numPeople; i++){
    //read in and update array

    musicGurus[i]->numPlays
  
  

//-------------------count total songs per person and overall genre favorite
//
//
//-------------------generate playlist










}
