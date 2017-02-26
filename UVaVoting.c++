/** @file UVaVoting.c++
 *  @brief Combination of RunVoting.c++, Voting.c++, and Voting.h for UVa testing purposes
 */

// --------
// includes
// --------
 
#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair
#include <vector>
#include <stdlib.h>

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

// ------------
// voting_read
// ------------

/**
 * read a string and int
 * @param s a string
 * @param size a integer
 * @return a vector of ints
 */
vector<int> voting_read (const string& s, int size) {
    istringstream sin(s);
    vector<int> ballots;
    for(int j = 0; j < size; j++)
    {
        int vote;
        sin >> vote;
        ballots.push_back(vote);
    }
    return ballots;}

// ------------
// voting_eval
// ------------

/**
 * read a vector of Candidate and a vector of Ballot
 * @param candidates a vector of Candidate
 * @param ballots a vector of Ballots
 * @return a vector of string
 */
vector<string> voting_eval (vector <Candidate> candidates, vector <Ballot> ballots) 
{
    vector <string> candidateNames;
    vector<Candidate> winningCandidates;
    while(candidateNames.size() == 0)
    {
        winningCandidates = get_winners(candidates, ballots.size());
        if(winningCandidates.size() > 0)
        {
            for(int i = 0; i < winningCandidates.size(); i++)
            {
                candidateNames.push_back(winningCandidates.at(i).get_name());
            }
        }
        else
        {
            eliminate_losers(candidates, ballots);
        }
    }
    return candidateNames;
}

// ------------
// eliminate_losers
// ------------

/**
 * read a vector of Candidate and a vector of Ballot
 * @param candidates a vector of Candidate
 * @param ballots a vector of Ballots
 */
void eliminate_losers(vector<Candidate>& candidates, vector<Ballot>& ballots)
{
    int loserCount = ballots.size();
    vector<int> loserPositions; 
    for(int i = 0 ; i < candidates.size(); ++i)
    {
        if(candidates.at(i).get_count() < loserCount)
        {
            loserCount = candidates.at(i).get_count();
            loserPositions.clear();
        }
        if(candidates.at(i).get_count() == loserCount)
        {
            loserPositions.push_back(i);
        }
    }
    //erase all the candidates that have lost
    for(int i = loserPositions.size()-1; i >=0; --i)
    {
        candidates.erase(candidates.begin()+loserPositions.at(i));
    }

    for(int i = 0 ; i < ballots.size(); ++i)
    {
        //while it's looking at a candidate that has already lost, find the next candidate
        while(find_candidate_index(candidates, ballots.at(i).get_preference()) == -1)
        {
            ballots.at(i).next_preference();
            if(find_candidate_index(candidates, ballots.at(i).get_preference()) != -1)
            {
                candidates.at(find_candidate_index(candidates, ballots.at(i).get_preference())).increase();
            }
        }
    }

}

// ------------
// find_candidate_index
// ------------

/**
 * read a vector of Candidate and an integer
 * @param candidates a vector of Candidate
 * @param preference an integer
 * @return a vector of Candidate
 */
int find_candidate_index(vector<Candidate> candidates, int preference)
{
    for(int i = 0 ; i < candidates.size(); ++i)
    {
        if(candidates.at(i).get_position() == preference)
        {
            return i;
        }
    }
    return -1;
} 

// ------------
// get_winners
// ------------

/**
 * read a vector of Candidate and an integer
 * @param candidates a vector of Candidate
 * @param ballotCount an integer
 * @return a vector of Candidate
 */
vector<Candidate> get_winners(vector<Candidate> candidates, int ballotCount)
{
    int winnersCount = 0;
    int tiedVotes = -1;
    vector<Candidate> winner;
    if(ballotCount % candidates.size() == 0)
    {
        tiedVotes = ballotCount/candidates.size();
    }
    for(int i = 0; i <candidates.size(); ++i)
    {
        if(candidates.at(i).get_count() > ballotCount/2)
        {
            winner.push_back(candidates.at(i));
            return winner;
        }
        if(candidates.at(i).get_count() == tiedVotes)
        {
            ++winnersCount;
        }
    }
    if(candidates.size() == winnersCount)
    {
        return candidates;
    }
    return winner;
}

// -------------
// voting_print
// -------------

/**
 * print three ints
 * @param w an ostream
 * @param names a vector of string
 * @param isEOF a Boolean
 */
void voting_print (ostream& w, vector<string> names, bool isEOF) {
    for(int i = 0; i < names.size(); ++i)
    {
        
        if(isEOF)
        {
            w << names.at(i) << endl;
        }
        else
        {
            if(i != names.size()-1)
            {
                w << names.at(i) << endl;
            }
            else
            {
                w << names.at(i) << endl << endl;
            }
        }
    }
}

// -------------
// voting_solve
// -------------

/**
 * @param r an istream
 * @param w an ostream
 */
void voting_solve (istream& r, ostream& w) {
    string firstLine;
    getline(r,firstLine);
    //cout << "first line1s == " <<endl;
    //cout << "first line == " << firstLine <<endl;
    int testCases = stoi(firstLine);
    getline(r,firstLine); //skip the next blank line
    int currentCase = 0;
    while (currentCase < testCases)
    {
        vector <Candidate> candidates;
        vector <Ballot> ballots;
        string s;
        int counter = 1;
        getline(r,s);
        int cases = stoi (s);
        while (counter <= cases)
        {
            getline(r,s);
            Candidate c(s, counter);
            candidates.push_back(c);
            counter++;
        }
        if(!r.eof())
        {
            getline(r,s);
        }
        while (!r.eof() && s.compare("") != 0)
        {
            vector<int> votes;
            votes = voting_read(s, cases);
            Ballot b(votes);
            ballots.push_back(b);
            candidates.at(votes.at(0)-1).increase(); //incresing the vote count of the candidate
            getline(r,s);
        } 
        if(r.eof())
        {
            vector<int> votes;
            votes = voting_read(s, cases);
            Ballot b(votes);
            ballots.push_back(b);
            candidates.at(votes.at(0)-1).increase();
        }
        voting_print(w, voting_eval(candidates, ballots), r.eof());
        ++currentCase;
    }

}

int main () {
    using namespace std;
    voting_solve(cin, cout); /** voting_solve() defined in voting.c++ is called with cin, cout as arguments */
    return 0;
}
