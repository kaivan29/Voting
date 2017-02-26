/** @file Voting.h
 *  @brief Header file with declarations of function.
 *   
 *  Functions are defined in Voting.c++.
 */
#ifndef Voting_h
#define Voting_h

// --------
// includes
// --------

#include <iostream> // istream, ostream
#include <string>   // string
#include <utility>  // pair
#include <vector>

using namespace std;


//! Candidate.
/*!
	Candidates standing in the election.
	This class defines their name, vote_count and position
*/

class Candidate
{
private:
	string name;
	int vote_count;
	int position;
public:
	string get_name(){return name;}
	int get_count(){return vote_count;}
	int get_position(){return position;}
	void set_count(int c){vote_count = c;}
	void increase(){++vote_count;}

	Candidate(string n, int initialPosition)
	{
		name = n;
		vote_count = 0;
		position = initialPosition;
	}
};

//! Ballot.
/*!
	Ballots by the people; stating their preference of the candidate.
	This class defines a vector which stores the preference.
*/
class Ballot
{
private:
	vector<int> preference;
public:
	int get_preference()
	{
		return preference.at(0);
	}
	int next_preference()
	{
		preference.erase(preference.begin()); 
		return preference.at(0);
	}

	Ballot(vector<int> pref)
	{
		preference = pref;
	}
};

// ------------
// voting_read
// ------------

/**
 * read a string and int
 * @param s a string
 * @param size a integer
 * @return a vector of ints
 */
vector<int> voting_read (const string& s, int size);

// ------------
// voting_eval
// ------------

/**
 * read a vector of Candidate and a vector of Ballot
 * @param candidates a vector of Candidate
 * @param ballots a vector of Ballots
 * @return a vector of string
 */
vector<string> voting_eval (vector<Candidate> candidates, vector<Ballot> ballots);

// -------------
// voting_print
// -------------

/**
 * print three ints
 * @param w an ostream
 * @param names a vector of string
 * @param isEOF a Boolean
 */
void voting_print (ostream& w, vector<string> names, bool isEOF);

// -------------
// voting_solve
// -------------

/**
 * @param r an istream
 * @param w an ostream
 */
void voting_solve (istream& r, ostream& w);

// ------------
// get_winners
// ------------

/**
 * read a vector of Candidate and an integer
 * @param candidates a vector of Candidate
 * @param ballotCount an integer
 * @return a vector of Candidate
 */
vector<Candidate> get_winners(vector<Candidate> candidates, int ballotCount);

// ------------
// eliminate_losers
// ------------

/**
 * read a vector of Candidate and a vector of Ballot
 * @param candidates a vector of Candidate
 * @param ballots a vector of Ballots
 */
void eliminate_losers(vector<Candidate>& candidates, vector<Ballot>& ballots);

// ------------
// find_candidate_index
// ------------

/**
 * read a vector of Candidate and an integer
 * @param candidates a vector of Candidate
 * @param preference an integer
 * @return a vector of Candidate
 */
int find_candidate_index(vector<Candidate> candidates, int preference);

#endif // Voting_h
