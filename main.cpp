// opening statements
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <ctime>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;  // these statements are for the time delay between moves

int game_loop();
// PURPOSE: this calls all of the other functions
// game_loop reduces the amount of code within the main() function
// INPUTS: none
// RETURNS: 0, outputs all of the events that occur as well as the game stats per team


int event_generator();
//PURPOSE: this generates a random number that represents the number of events that occur during the game
//INPUTS: none
//RETURNS: a random int between 1 and 30, inclusive


int events_in_first_half(int total_number_of_events);
// PURPOSE: this randomly chooses a number that is in between 1 and the total number of events
// this way, the events are randomly split between the first and second half of the game
// INPUTS: none
// RETURNS: the number of events in the first half of the game as an integer


int events_in_second_half(int total_number_of_events, int events_in_first_half_game);
// PURPOSE: this calculates the number of events in the second half of the game
// INPUT: total number of events and the number of events in the first half
// OUTPUT: returns the number of events that occur in the second half as an integer

int move_generator();
//PURPOSE: this generates a scenario for each event that occurs during the game
//INPUTS: none
//RETURNS: this generates a random number between 1 and 6, inclusive
//each number represents a unique scenario

int foul();
/* PURPOSE: a random integer is generated to decide if a card was given for the foul
 * INPUTS: none
 * RETURNS: prints string that displays whether or not a card was given, returns 0
 * */

int goal_scored();
/* PURPOSE: this generates a random number that is associated with a statement
that determines whether or not the team has scored a goal, saved by goalkeeper
or defender, or blocked by a player who is not the last defender
 INPUTS: none
 RETURNS: prints string that says whether or not the goal was scored, returns 0
 */

int game_stats_team_a();
// this prints out the game stats for team a at the end of each half
// only contains the headers
// no inputs, no returned values

int game_stats_team_b();
// this prints out the game stats for team b at the end of each half
// only contains the headers
// no inputs, no returned values

int main(){ //main function that calls game loop function
    game_loop(); 
    return 0;
};

int game_loop() { // this calls all other functions
    //variable declarations
    int total_number_of_events;
    int a = 1, b; // initialize variables for events in first half
    int team_a_yellow_cards = 0, team_a_red_cards = 0, team_a_fouls = 0, team_a_points = 0, team_a_shots_on_goal = 0;
    int team_a_shots_off_goal = 0, team_a_blocked_shots = 0; //store stats for team a
    int team_b_yellow_cards = 0, team_b_red_cards = 0, team_b_fouls = 0, team_b_points = 0, team_b_shots_on_goal = 0;
    int team_b_shots_off_goal = 0, team_b_blocked_shots = 0; //store stats for team b

    // determine the number of events that occur during the game
    total_number_of_events = event_generator(); //calls the function that generates a random number of events
    // determine the number of events that occur during the
    int events_in_first_half_game = events_in_first_half(total_number_of_events);
    // echo
    cout << "The random number that you generated is " << total_number_of_events << "." << endl;
    cout << "This number represents the total number of events that occur during the game. " << endl << endl;

    // while loop generates unique events for every single event that occurs during the first half of the game
    while (a <= events_in_first_half_game) {
        b = move_generator(); // calls move_generator function which is random
        a++;

        sleep_for(10ns);
        sleep_until(system_clock::now() + 1s); // one second sleep delay between seeing each event occur

        if (b == 1) {
            cout << "Team A has shot at target. ";
            int team_a_shot = goal_scored();
            if (team_a_shot == 0) {
                team_a_points++;
                team_a_shots_on_goal++;
            } else if (team_a_shot == 1) {
                team_b_blocked_shots++; // note that a blocked shot counts as a shot blocked by the other team
                // and not as a shot by the shooting team that was blocked
                team_a_shots_on_goal++;
            } else if (team_a_shot == 2) {
                team_a_shots_off_goal++;
            } else{
                team_b_blocked_shots++;
            }
        } else if (b == 2) {
            cout << "Team B has shot at target. ";
            int team_b_shot = goal_scored();
            if (team_b_shot == 0) {
                team_b_points++;
                team_b_shots_on_goal++;
            } else if (team_b_shot == 1) {
                team_b_shots_on_goal++;
            } else if (team_b_shot == 2) {
                team_b_shots_off_goal++;
            } else {
                team_a_blocked_shots++;
            }
        } else if (b == 3) {
            cout << "Team B has committed a foul. "
                    "Team A was awarded a free kick. ";
            int team_b_foul = goal_scored();
            if (team_b_foul == 0) {
                team_a_points++;
                team_a_shots_on_goal++;
            } else if (team_b_foul == 1) {
                team_a_shots_on_goal++;
            } else if (team_b_foul == 2) {
                team_a_shots_off_goal++;

            } else {
                team_b_blocked_shots++;
            }
            int foul_b_card = foul();
            team_b_fouls++;
            if (foul_b_card) {
                if (foul_b_card == 1) {
                    team_b_yellow_cards++;
                } else {
                    team_b_red_cards++;
                }
            }
        } else if (b == 4) {
            cout << "Team A has committed a foul. "
                    "Team B was awarded a free kick. ";
            int team_a_foul = goal_scored();
            if (team_a_foul == 0) {
                team_b_points++;
                team_b_shots_on_goal++;
            } else if (team_a_foul == 1) {
                team_b_shots_on_goal++;
            } else if (team_a_foul == 2) {
                team_b_shots_off_goal++;
            } else {
                team_a_blocked_shots++;
            }
            int foul_a_card = foul();
            team_a_fouls++;
            if (foul_a_card) {
                if (foul_a_card == 1) {
                    team_a_yellow_cards++;
                } else {
                    team_a_red_cards++;
                }
            }
        }else if (b == 5) {
            cout << "Team B has committed a foul close to the goal. "
                    "Team A was awarded a penalty. ";
            int team_a_penalty = goal_scored();
            if (team_a_penalty == 0) {
                team_a_points++;
                team_a_shots_on_goal++;
            } else if (team_a_penalty == 1) {
                team_a_shots_on_goal++;
            } else if (team_a_penalty == 2) {
                team_a_shots_off_goal++;
            } else {
                team_b_blocked_shots++;
            }
            int foul_number_b = foul();
            team_b_fouls++;
            if (foul_number_b>0) {
                if (foul_number_b == 1)
                    team_b_yellow_cards++;
                else
                    team_b_red_cards++;
            }
        } else if (b == 6) {
            cout << "Team A has committed a foul close to the goal. "
                    "Team B was awarded a penalty. ";
            int team_b_penalty = goal_scored();
            if (team_b_penalty == 0) {
                team_b_points++;
                team_b_shots_on_goal++;
            } else if (team_b_penalty == 1) {
                team_b_shots_on_goal++;
            } else if (team_b_penalty == 2) {
                team_b_shots_off_goal++;
            } else {
                team_a_blocked_shots++;
            }
            int foul_number_a = foul();
            team_a_fouls++;
            if (foul_number_a>0) {
                if (foul_number_a == 1) {
                    team_a_yellow_cards++;
                } else {
                    team_a_red_cards++;
                }
            }
        }
        cout << endl;
    }

    game_stats_team_a(); // calls the function that prints out headers for team A's stats
    cout << team_a_points << "\t\t " << team_a_points << "-" << team_b_points << "\t " << team_a_shots_on_goal
         << "\t\t\t\t\t\t\t " << team_a_shots_off_goal << "\t\t\t\t\t " <<team_a_blocked_shots
         << "\t\t\t\t" <<team_a_fouls << "\t\t " << team_a_yellow_cards <<"\t\t\t\t " << team_a_red_cards << endl;
    
    game_stats_team_b(); // calls the function that prints out headers for team B's stats
    cout << team_b_points << "\t\t " << team_b_points << "-" << team_a_points << "\t " << team_b_shots_on_goal
         << "\t\t\t\t\t\t\t " << team_b_shots_off_goal << "\t\t\t\t\t " <<team_b_blocked_shots
         << "\t\t\t\t" <<team_b_fouls << "\t\t " << team_b_yellow_cards <<"\t\t\t\t " << team_b_red_cards;
    
    cout << endl << endl << endl << "END OF FIRST HALF" << endl << endl << endl;

    sleep_for(10ns); // time break in between the first half and the second half
    sleep_until(system_clock::now() + 5s);

    //second half of the game, essentially the same code for the first half
    int c = 1, d;

    int events_in_second_half_game = events_in_second_half(total_number_of_events, events_in_first_half_game);
    //calls the function that calculates the number of events that occur in the second half

    // while loop generates unique events for every single event that occurs during the second half of the game
    while (c <= events_in_second_half_game) {
        d = move_generator();
        c++;

        sleep_for(10ns);
        sleep_until(system_clock::now() + 1s);

        if (d == 1) {
            cout << "Team A has shot at target. ";
            int team_a_shot = goal_scored();
            if (team_a_shot == 0) {
                team_a_points++;
                team_a_shots_on_goal++;
            } else if (team_a_shot == 1) {
                team_a_shots_on_goal++;
            } else if (team_a_shot == 2) {
                team_a_shots_off_goal++;
            } else{
                team_b_blocked_shots++;
            }
        } else if (d == 2) {
            cout << "Team B has shot at target. ";
            int team_b_shot = goal_scored();
            if (team_b_shot == 0) {
                team_b_points++;
                team_b_shots_on_goal++;
            } else if (team_b_shot == 1) {
                team_b_shots_on_goal++;
            } else if (team_b_shot == 2) {
                team_b_shots_off_goal++;
            } else {
                team_a_blocked_shots++;
            }
        } else if (d == 3) {
            cout << "Team B has committed a foul. "
                    "Team A was awarded a free kick. ";
            int team_b_foul = goal_scored();
            if (team_b_foul == 0) {
                team_a_points++;
                team_a_shots_on_goal++;
            } else if (team_b_foul == 1) {
                team_a_shots_on_goal++;
            } else if (team_b_foul == 2) {
                team_a_shots_off_goal++;
            } else {
                team_b_blocked_shots++;
            }
            int foul_b_card = foul();
            team_b_fouls++;
            if (foul_b_card) {
                if (foul_b_card == 1) {
                    team_b_yellow_cards++;
                } else {
                    team_b_red_cards++;
                }
            }
        } else if (d == 4) {
            cout << "Team A has committed a foul. "
                    "Team B was awarded a free kick. ";
            int team_a_foul = goal_scored();
            if (team_a_foul == 0) {
                team_b_points++;
                team_b_shots_on_goal++;
            } else if (team_a_foul == 1) {
                team_b_shots_on_goal++;
            } else if (team_a_foul == 2) {
                team_b_shots_off_goal++;
            } else {
                team_a_blocked_shots++;
            }
            int foul_a_card = foul();
            team_a_fouls++;
            if (foul_a_card) {
                if (foul_a_card == 1) {
                    team_a_yellow_cards++;
                } else {
                    team_a_red_cards++;
                }
            }
        }else if (d == 5) {
            cout << "Team B has committed a foul close to the goal. "
                    "Team A was awarded a penalty. ";
            int team_a_penalty = goal_scored();
            if (team_a_penalty == 0) {
                team_a_points++;
                team_a_shots_on_goal++;
            } else if (team_a_penalty == 1) {
                team_a_shots_on_goal++;
            } else if (team_a_penalty == 2) {
                team_a_shots_off_goal++;
            } else {
                team_b_blocked_shots++;
            }
            int foul_number_b = foul();
            team_b_fouls++;
            if (foul_number_b>0) {
                if (foul_number_b == 1)
                    team_b_yellow_cards++;
                else
                    team_b_red_cards++;
            }
        } else if (d == 6) {
            cout << "Team A has committed a foul close to the goal. "
                    "Team B was awarded a penalty. ";
            int team_b_penalty = goal_scored();
            if (team_b_penalty == 0) {
                team_b_points++;
                team_b_shots_on_goal++;
            } else if (team_b_penalty == 1) {
                team_b_shots_on_goal++;
            } else if (team_b_penalty == 2) {
                team_b_shots_off_goal++;
            } else {
                team_a_blocked_shots++;
            }
            int foul_number_a = foul();
            team_a_fouls++;
            if (foul_number_a>0) {
                if (foul_number_a == 1) {
                    team_a_yellow_cards++;
                } else {
                    team_a_red_cards++;
                }
            }
        }
        cout << endl;
    }
    game_stats_team_a();
    cout << team_a_points << "\t\t " << team_a_points << "-" << team_b_points << "\t " << team_a_shots_on_goal
         << "\t\t\t\t\t\t\t " << team_a_shots_off_goal << "\t\t\t\t\t " <<team_a_blocked_shots
         << "\t\t\t\t" <<team_a_fouls << "\t\t " << team_a_yellow_cards <<"\t\t\t\t " << team_a_red_cards << endl;

    game_stats_team_b();
    cout << team_b_points << "\t\t " << team_b_points << "-" << team_a_points << "\t " << team_b_shots_on_goal
         << "\t\t\t\t\t\t\t " << team_b_shots_off_goal << "\t\t\t\t\t " <<team_b_blocked_shots
         << "\t\t\t\t" <<team_b_fouls << "\t\t " << team_b_yellow_cards <<"\t\t\t\t " << team_b_red_cards;

    //outputs a statement that says that the second half is completed
    cout << endl << endl << endl << "END OF SECOND HALF" << endl << endl << endl;

    //return statement
    return 0;
}

int event_generator(){
    srand(time(NULL)); //this generates a random integer every time it is called
    int random_number = rand() % 30 + 1;

    //returns the number of events that occur throughout the game
    return random_number;
}

int events_in_first_half(int number_of_events){
    int events_in_first_half_game = rand() % number_of_events + 1;

    return events_in_first_half_game;
}

int events_in_second_half(int total_number_of_events, int events_in_first_half){
    int second_half = total_number_of_events - events_in_first_half;
    
    return second_half;
}

int move_generator() {
    int random_number = rand() % 6 + 1;
    
    return random_number;
}

int foul() {
    int random_number = rand() % 3;
    if (random_number == 0)
        cout << "No card was given. ";
    else if (random_number ==1)
        cout << "A yellow card was given. ";
    else if (random_number ==2)
        cout << "A red card was given. ";

    return random_number;
}

int goal_scored(){
    int random_number = rand() % 4;
    if (random_number == 0)
        cout << "The team has scored a goal. ";
    else if (random_number == 1)
        cout << "The shot was made on goal but saved by the goalkeeper or last defender. ";
    else if (random_number == 2)
        cout << "The shot was made off goal. ";
    else
        cout << "The shot was blocked by a player who is not the last defender. ";
    
    return random_number;
}

int game_stats_team_a(){
    cout <<"\nTeam A Stats" << endl;
    cout << "Points \t Score \t Number of shots on goal \t Shots off goal \t Shots blocked \t"
            "Fouls \t Yellow cards \t Red cards \n";
    
    return 0;
}

int game_stats_team_b(){
    cout <<"\nTeam B Stats" << endl;
    cout << "Points \t Score \t Number of shots on goal \t Shots off goal \t Shots blocked \t"
            "Fouls \t Yellow cards \t Red cards \n";
    
    return 0;
}
