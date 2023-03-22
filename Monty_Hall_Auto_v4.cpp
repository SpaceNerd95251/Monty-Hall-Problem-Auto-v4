// Monty_Hall_Auto_v4.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Started: 03/21/2023
// The Monty Hall problem, except it auto iterates itself many times.
// v4 uses logical deductions to make the program simpler, and also much faster by removing some calls to distribution(generator)

#include <iostream>     //for cout cin
#include <time.h>       //for the seed for the random number generator, otherwise it will be the same every run
#include <random>       //because the regular rand() function isn't random enough; this does however increase runtime
using namespace std;    //I always do this

int main()
{
    //sets up our variables for the door with the car behind it and the door the computer guesses
    int car_door, guess;
    //sets up a variable for the number of iterations to run for, unsigned since you cannot run negative iterations and this gives us a larger maximum number of trials
    unsigned int iterations{ 10 };
    //sets up stats for total wins and losses
    double wins{ 0 }, losses{ 0 }, total_attempts{ 0 }, percent_won;
    //uses current unix time as seed for rand
    srand(time(0));

    //asks the user how many times should the problem loop, to get more trials and thus more accurate data
    cout << "Welcome to the Monty Hall problem! How many iterations would you like to run? (Input as a positive integer)" << endl;
    cin >> iterations;
    cout << "The program will now run " << iterations << " iterations of the Monty Hall problem, switching its guess every time.\n" << endl;

    //marks when it starts, for timing purposes
    cout << "Starting...\n";

    //construct a trivial random generator engine from a time-based seed:
    default_random_engine generator(time(0));
    uniform_int_distribution<int> distribution(0, 2);

    //Loops for however many iterations the user specified
    for (unsigned int i = 0; i < iterations; i++)
    {

        //randomly sets the value of the car door (the winner) to be either 0, 1, or 2, which will represent door a, b, and c respectively
        car_door = distribution(generator);

        //computer guesses a random door
        guess = distribution(generator);

        //if its current guess is correct, and it always switches its guess, it will always switch to the wrong guess when its current guess is correct, thus always losing
        if (guess == car_door)
            losses++;
        //if its current guess is wrong, logic says the unguessed unrevealed door is correct, so if it switches every time it will always switch to that.
        //We don't even need to simulate the switch, since we know it wins
        else
            wins++;

        total_attempts++;

    }

    //gives final stats
    percent_won = ((wins / total_attempts) * 100);
    cout << "Done!\nTotal wins: " << wins << " Total losses: " << losses << " Total iterations: " << total_attempts << endl;
    cout << "Percentage won is " << percent_won << "; theoretical value is 66.66666...%" << endl;

    return 0;

}
