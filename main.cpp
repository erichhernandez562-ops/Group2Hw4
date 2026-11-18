#include <iostream>
#include <sstream>
#include "bowling_frame.h"
#include <random>

using namespace std;

std::random_device dev_main;
std::mt19937 rng_main(dev_main());

int current_game_total(Bowling_Frame * first_frame)
{
	Bowling_Frame * temp = first_frame;
	int game_total = 0;
	int temp_total = 0;
	while(temp)
	{
		game_total += temp->frame_score();
		temp = temp->next_frame();
	}
	return game_total;	
}

int main(int argc, char *argv[])
{
    // handle input
    if (argc < 2) {
        cerr << "Usage: a.out <num_players>" << endl;
    } 

    int num_players;
    istringstream in_stream( argv[1] );

    if (!(in_stream >> num_players)) {
        // invalid input
        cerr << "Invalid number: " << argv[1] << endl;
        return 1;
    } else if (num_players <= 0) {
        // non-positive input
        cerr << "Number of players must be positive (" << argv[1] << " < 0)" << endl;
        return 2;
    }

    // initialize pointer array
    Bowling_Frame* frames[num_players];

    for (int i = 0; i < num_players; ++i) {
        frames[i] = new Bowling_Frame(1);
    }

    // extend linked lists
    for (int i = 0; i < num_players; ++i) {
        Bowling_Frame *prev = frames[i];
        for (int fnum = 2; fnum <= 10; ++fnum) {
            Bowling_Frame* curr = new Bowling_Frame(fnum);
            curr->prev_frame(prev);
            prev->next_frame(curr);
            prev = curr;
        }
    }
    // roll 20 times
    for (int i = 0; i < num_players; ++i) {
        for (int j = 0; j < 20; ++j) {
            frames[i]->update_scores();
        }
    }

    // print output
    cout << "Player count is: " << num_players << endl;
    for (int i = 0; i < num_players; ++i) {
        //iterate through linked list and print values
        Bowling_Frame * traverse = frames[i];
        int game_total = current_game_total(traverse); 
        
        while(traverse)
        {
            cout << "Frame " << traverse->frame_num() << ": " << endl
                 << " Score 1: " << traverse->score1() << endl
                 << " Score 2: " << traverse->score2() << endl;

            traverse = traverse->next_frame();
        }
        cout << endl 
             << "Total Game Score for player " << (i+1) << ": " << game_total
             << endl << endl;
    }
}
