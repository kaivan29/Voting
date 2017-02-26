/** @file TestVoting.c++
 *  @brief Runs unit tests for the whole of Voting.c++. Primarily
 *  tests the edge cases of voting_eval.
 */

// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2015
// Glenn P. Downing
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair

#include "gtest/gtest.h"

#include "Voting.h"

using namespace std;

// -----------
// TestVoting
// -----------

// ----
// read
// ----

TEST(VotingFixture, read_1) {
    string s("1 4 5 2 3\n");
    vector<int> votes = voting_read(s, 5);
    ASSERT_EQ( 1, votes.at(0));
    ASSERT_EQ( 4, votes.at(1));
    ASSERT_EQ( 5, votes.at(2));
    ASSERT_EQ( 2, votes.at(3));
    ASSERT_EQ( 3, votes.at(4));
}

TEST(VotingFixture, read_2) {
    string s("55 65 100\n");
    vector<int> votes = voting_read(s, 3);
    ASSERT_EQ( 55, votes.at(0));
    ASSERT_EQ( 65, votes.at(1));
    ASSERT_EQ( 100, votes.at(2));
}

TEST(VotingFixture, read_3) {
    string s("4 3 20 99 105\n");
    vector<int> votes = voting_read(s, 5);
    ASSERT_EQ( 4, votes.at(0));
    ASSERT_EQ( 3, votes.at(1));
    ASSERT_EQ( 20, votes.at(2));
    ASSERT_EQ( 99, votes.at(3));
    ASSERT_EQ( 105, votes.at(4));
}

// ----
// eval
// ----

TEST(VotingFixture, eval_1) {
    vector <Candidate> candidates;
    vector <Ballot> ballots;
    Candidate c("Kaivan Shah", 1);
    candidates.push_back(c);
    Candidate d("Lyee Chong", 2);
    candidates.push_back(d);
    vector<string> candidate_names = voting_eval (candidates, ballots);
    ASSERT_EQ( "Kaivan Shah", candidate_names.at(0));
    ASSERT_EQ( "Lyee Chong", candidate_names.at(1));
}

TEST(VotingFixture, eval_2) {
    vector <Candidate> candidates;
    vector <Ballot> ballots;
    Candidate c("Kaivan Shah", 1);
    c.increase();
    candidates.push_back(c);
    Candidate d("Lyee Chong", 2);
    candidates.push_back(d);

    vector<int> votes;
    votes.push_back(1);
    votes.push_back(2);
    Ballot b(votes);
    ballots.push_back(b);
    vector<string> candidate_names = voting_eval (candidates, ballots);
    ASSERT_EQ( "Kaivan Shah", candidate_names.at(0));
}

TEST(VotingFixture, eval_3) {
    vector <Candidate> candidates;
    vector <Ballot> ballots;
    Candidate c("Kaivan Shah", 1);
    candidates.push_back(c);
    Candidate d("Lyee Chong", 2);
    d.increase();
    candidates.push_back(d);

    vector<int> votes;
    votes.push_back(2);
    votes.push_back(1);
    Ballot b(votes);
    ballots.push_back(b);
    vector<string> candidate_names = voting_eval (candidates, ballots);
    ASSERT_EQ( "Lyee Chong", candidate_names.at(0));
}


// -----
// print
// -----

TEST(VotingFixture, print_not_EOF) {
    ostringstream w;
    vector<string> candidateNames;
    candidateNames.push_back("John Doe");
    candidateNames.push_back("Jane Smith");
    candidateNames.push_back("Sirchan Sirchan");
    voting_print(w, candidateNames, false);
    ASSERT_EQ("John Doe\nJane Smith\nSirchan Sirchan\n\n", w.str());
}

TEST(VotingFixture, print_at_EOF) {
    ostringstream w;
    vector<string> candidateNames;
    candidateNames.push_back("John Doe");
    candidateNames.push_back("Jane Smith");
    candidateNames.push_back("Sirchan Sirchan");
    voting_print(w, candidateNames, true);
    ASSERT_EQ("John Doe\nJane Smith\nSirchan Sirchan\n", w.str());
}

TEST(VotingFixture, print_single_name) {
    ostringstream w;
    vector<string> candidateNames;
    candidateNames.push_back("John Doe");
    voting_print(w, candidateNames, true);
    ASSERT_EQ("John Doe\n", w.str());
}

TEST(VotingFixture, print_single_name_not_eof) {
    ostringstream w;
    vector<string> candidateNames;
    candidateNames.push_back("John Doe");
    voting_print(w, candidateNames, false);
    ASSERT_EQ("John Doe\n\n", w.str());
}


// -----
// find index
// -----

TEST(VotingFixture, index_1) {
    vector <Candidate> candidates;
    Candidate c("Kaivan Shah", 1);
    candidates.push_back(c);
    Candidate d("Lyee Chong", 2);
    candidates.push_back(d);
    Candidate e("Kai Shaw", 3);
    candidates.push_back(e);
    Candidate f("Lai Chong", 4);
    candidates.push_back(f);
    int preference = 3;
    int index = find_candidate_index(candidates, preference);
    ASSERT_EQ( 2,index);
}

TEST(VotingFixture, index_2) {
    vector <Candidate> candidates;
    Candidate c("Kaivan Shah", 1);
    candidates.push_back(c);
    Candidate d("Lyee Chong", 2);
    candidates.push_back(d);
    int preference = 3;
    int index = find_candidate_index(candidates, preference);
    ASSERT_EQ( -1,index);
}

TEST(VotingFixture, index_3) {
    vector <Candidate> candidates;
    Candidate c("Kaivan Shah", 1);
    candidates.push_back(c);
    Candidate d("Lyee Chong", 2);
    candidates.push_back(d);
    int preference = 2;
    int index = find_candidate_index(candidates, preference);
    ASSERT_EQ( 1,index);
}

TEST(VotingFixture, index_4) {
    vector <Candidate> candidates;
    Candidate c("Kaivan Shah", 2);
    candidates.push_back(c);
    Candidate d("Lyee Chong", 1);
    candidates.push_back(d);
    int preference = 2;
    int index = find_candidate_index(candidates, preference);
    ASSERT_EQ( 0,index);
}

TEST(VotingFixture, index_5) {
    vector <Candidate> candidates;
    Candidate c("Kaivan Shah", 1);
    candidates.push_back(c);
    Candidate d("Lyee Chong", 2);
    candidates.push_back(d);
    int preference = 1;
    int index = find_candidate_index(candidates, preference);
    ASSERT_EQ( 0,index);
}

// -----
// get winners
// -----


TEST(VotingFixture, winners_1) {
    vector <Candidate> candidates;
    vector <Ballot> ballots;
    Candidate c("Kaivan Shah", 1);
    candidates.push_back(c);
    Candidate d("Lyee Chong", 2);
    candidates.push_back(d);
    vector<Candidate> candidate_names = get_winners (candidates, 0);
    ASSERT_EQ( "Kaivan Shah", candidate_names.at(0).get_name());
    ASSERT_EQ( "Lyee Chong", candidate_names.at(1).get_name());
}

TEST(VotingFixture, winners_2) {
    vector <Candidate> candidates;
    vector <Ballot> ballots;
    Candidate c("Kaivan Shah", 1);
    candidates.push_back(c);
    c.increase();
    c.increase();
    Candidate d("Lyee Chong", 2);
    candidates.push_back(d);
    d.increase();
    Candidate e("Kai Shaw", 3);
    candidates.push_back(e);
    e.increase();
    Candidate f("Lai Chong", 4);
    f.increase();
    candidates.push_back(f);
    vector<Candidate> candidate_names = get_winners (candidates, 2);
    ASSERT_EQ( 0, candidate_names.size());
}

// -----
// solve
// -----

TEST(VotingFixture, solve_single_case) {
    istringstream r("1\n\n"
                    "3\n"
                    "John Doe\n"
                    "Jane Smith\n"
                    "Sirchan Sirchan\n"
                    "1 2 3\n"
                    "3 2 1\n"
                    "2 1 3\n"
                    "2 3 1\n"
                    "1 3 2");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_EQ("Jane Smith\n", w.str());
}

TEST(VotingFixture, solve_single_case_one_ballot) {
    istringstream r("1\n\n"
                    "3\n"
                    "John Doe\n"
                    "Jane Smith\n"
                    "Sirchan Sirchan\n"
                    "1 2 3");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_EQ("John Doe\n", w.str());
}

TEST(VotingFixture, solve_multiple_cases_one_ballot) {
    istringstream r("2\n\n"
                    "3\n"
                    "John Doe\n"
                    "Jane Smith\n"
                    "Sirchan Sirchan\n"
                    "3 2 1\n\n"
                    "2\n"
                    "John Doe\n"
                    "Potato Joe\n"
                    "2 1");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_EQ("Sirchan Sirchan\n\nPotato Joe\n", w.str());
}


TEST(VotingFixture, solve_multiple_cases) {
    istringstream r("2\n\n"
                    "3\n"
                    "John Doe\n"
                    "Jane Smith\n"
                    "Sirchan Sirchan\n"
                    "1 2 3\n"
                    "3 2 1\n"
                    "2 1 3\n"
                    "2 3 1\n"
                    "1 3 2\n\n"
                    "4\n"
                    "John Doe\n"
                    "Jane Smith\n"
                    "Sirchan Sirchan\n"
                    "Potato Joe\n"
                    "1 2 4 3\n"
                    "3 4 2 1\n"
                    "2 1 4 3\n"
                    "2 3 1 4\n"
                    "1 3 2 4\n"
                    "3 4 3 2");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_EQ("Jane Smith\n\n"
                "John Doe\n"
                "Jane Smith\n"
                "Sirchan Sirchan\n", w.str());
}
/*
g++-4.8 -pedantic -std=c++11 -Wall -fprofile-arcs -ftest-coverage Voting.c++ TestVoting.c++ -o TestVoting -lgtest -lgtest_main -pthread
Voting.c++: In function ‘std::vector<std::basic_string<char> > voting_eval(std::vector<Candidate>, std::vector<Ballot>)’:
Voting.c++:49:55: warning: comparison between signed and unsigned integer expressions [-Wsign-compare]
             for(int i = 0; i < winningCandidates.size(); i++)
                                                       ^
Voting.c++: In function ‘void eliminate_losers(std::vector<Candidate>&, std::vector<Ballot>&)’:
Voting.c++:66:41: warning: comparison between signed and unsigned integer expressions [-Wsign-compare]
     for(int i = 0 ; i < candidates.size(); ++i)
                                         ^
Voting.c++:84:38: warning: comparison between signed and unsigned integer expressions [-Wsign-compare]
     for(int i = 0 ; i < ballots.size(); ++i)
                                      ^
Voting.c++: In function ‘int find_candidate_index(std::vector<Candidate>, int)’:
Voting.c++:101:41: warning: comparison between signed and unsigned integer expressions [-Wsign-compare]
     for(int i = 0 ; i < candidates.size(); ++i)
                                         ^
Voting.c++: In function ‘std::vector<Candidate> get_winners(std::vector<Candidate>, int)’:
Voting.c++:120:39: warning: comparison between signed and unsigned integer expressions [-Wsign-compare]
     for(int i = 0; i <candidates.size(); ++i)
                                       ^
Voting.c++:132:29: warning: comparison between signed and unsigned integer expressions [-Wsign-compare]
     if(candidates.size() == winnersCount)
                             ^
Voting.c++: In function ‘void voting_print(std::ostream&, std::vector<std::basic_string<char> >, bool)’:
Voting.c++:144:35: warning: comparison between signed and unsigned integer expressions [-Wsign-compare]
     for(int i = 0; i < names.size(); ++i)
                                   ^
Voting.c++:153:34: warning: comparison between signed and unsigned integer expressions [-Wsign-compare]
             if(i != names.size()-1)
                                  ^
valgrind ./TestVoting                                       >  TestVoting.tmp 2>&1
gcov-4.8 -b Voting.c++     | grep -A 5 "File 'Voting.c++'"     >> TestVoting.tmp
gcov-4.8 -b TestVoting.c++ | grep -A 5 "File 'TestVoting.c++'" >> TestVoting.tmp
cat TestVoting.tmp
==11760== Memcheck, a memory error detector
==11760== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==11760== Using Valgrind-3.10.0.SVN and LibVEX; rerun with -h for copyright info
==11760== Command: ./TestVoting
==11760== 
Running main() from gtest_main.cc
[==========] Running 21 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 21 tests from VotingFixture
[ RUN      ] VotingFixture.read_1
[       OK ] VotingFixture.read_1 (32 ms)
[ RUN      ] VotingFixture.read_2
[       OK ] VotingFixture.read_2 (4 ms)
[ RUN      ] VotingFixture.read_3
[       OK ] VotingFixture.read_3 (5 ms)
[ RUN      ] VotingFixture.eval_1
[       OK ] VotingFixture.eval_1 (60 ms)
[ RUN      ] VotingFixture.eval_2
[       OK ] VotingFixture.eval_2 (32 ms)
[ RUN      ] VotingFixture.eval_3
[       OK ] VotingFixture.eval_3 (7 ms)
[ RUN      ] VotingFixture.print_not_EOF
[       OK ] VotingFixture.print_not_EOF (16 ms)
[ RUN      ] VotingFixture.print_at_EOF
[       OK ] VotingFixture.print_at_EOF (5 ms)
[ RUN      ] VotingFixture.print_single_name
[       OK ] VotingFixture.print_single_name (4 ms)
[ RUN      ] VotingFixture.print_single_name_not_eof
[       OK ] VotingFixture.print_single_name_not_eof (3 ms)
[ RUN      ] VotingFixture.index_1
[       OK ] VotingFixture.index_1 (7 ms)
[ RUN      ] VotingFixture.index_2
[       OK ] VotingFixture.index_2 (4 ms)
[ RUN      ] VotingFixture.index_3
[       OK ] VotingFixture.index_3 (4 ms)
[ RUN      ] VotingFixture.index_4
[       OK ] VotingFixture.index_4 (4 ms)
[ RUN      ] VotingFixture.index_5
[       OK ] VotingFixture.index_5 (4 ms)
[ RUN      ] VotingFixture.winners_1
[       OK ] VotingFixture.winners_1 (6 ms)
[ RUN      ] VotingFixture.winners_2
[       OK ] VotingFixture.winners_2 (9 ms)
[ RUN      ] VotingFixture.solve_single_case
[       OK ] VotingFixture.solve_single_case (43 ms)
[ RUN      ] VotingFixture.solve_single_case_one_ballot
[       OK ] VotingFixture.solve_single_case_one_ballot (3 ms)
[ RUN      ] VotingFixture.solve_multiple_cases_one_ballot
[       OK ] VotingFixture.solve_multiple_cases_one_ballot (4 ms)
[ RUN      ] VotingFixture.solve_multiple_cases
[       OK ] VotingFixture.solve_multiple_cases (6 ms)
[----------] 21 tests from VotingFixture (270 ms total)

[----------] Global test environment tear-down
[==========] 21 tests from 1 test case ran. (298 ms total)
[  PASSED  ] 21 tests.
==11760== 
==11760== HEAP SUMMARY:
==11760==     in use at exit: 0 bytes in 0 blocks
==11760==   total heap usage: 966 allocs, 966 frees, 93,190 bytes allocated
==11760== 
==11760== All heap blocks were freed -- no leaks are possible
==11760== 
==11760== For counts of detected and suppressed errors, rerun with: -v
==11760== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
File 'Voting.c++'
Lines executed:100.00% of 102
Branches executed:100.00% of 216
Taken at least once:61.57% of 216
Calls executed:85.14% of 175
Creating 'Voting.c++.gcov'
File 'TestVoting.c++'
Lines executed:100.00% of 189
Branches executed:75.05% of 1058
Taken at least once:37.52% of 1058
Calls executed:58.52% of 1186
Creating 'TestVoting.c++.gcov'
*/
