# PerfPartyPlaylist

tclare, kstaple1

Tommy and Kat's final project: creating a perfect party playlist by uploading several people's Apple Music library, determining the favorite genre, and playing 2 songs from that genre for every song not from that genre
the BST of songs will sort so that songs with greater numPlays go on the left which cuts down on runtime. We select a song by generating a random number and in-order traversing the tree. We track each song node's number of Plays and select the song we're on in the tree traversal when the tracked total number of plays equals the random number. For example, if the first song to be traversed has the private member number of Plays equal to 100 and the second song has numPlays equal to 75, and the random number is 103, the traversal would record total number of plays at the first song and at the second song, realize the total number of plays has reached the random number.

To install the code, a user needs the python server and the executable testing2 in the src directory, the index.html in the www directory, and the songsList.txt file. The songsList.txt file includes a csv with Tommy's Apple music library songs, but you could create your own csv file, rename it to songsList.txt, and that instead. Special characters that don't have an ASCII equivalent will appear strange for those letters. We also included a Makefile which includes the option to make test. To run, the user must be in the src directory and run the python server on student00.cse.nd.edu port 9008 or change the host/port in both the python server file and index.html. Then, open a browser with that host and port. To run, click on the drop down menus for party length and number of songs uploaded. Clicking the button with the same options will not generate a different playlist because we have the playlist seed static for demonstrating testing purposes. 

The benchmarking script is in the main directory. To test for correctness, sample inputs and outputs are also included there.

