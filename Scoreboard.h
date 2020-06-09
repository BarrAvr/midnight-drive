#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Scoreboard
{

public:
	using Score = pair<int, string>;
	Scoreboard() ;

	void readScoresFromFile(const string& fileName);
	void writeScoresToFile(const string& fileName);

	~Scoreboard() = default;
	void addScore(const Score&);
	void addScore(int score, string name);
	bool contains(int score, std::string name);

	sf::String printScores();
	vector<Score> getScores() { return scores; }

private:
	vector<Score> scores;

};

//GETTING AN ERROR HERE, SOS
/*
ostream& operator<<(ostream& out, Scoreboard& s)
{
	for (int i = 0; i < s.getScores().size(); i++)
	{
		//we dont want to be outputting any "0,-----" to the file
		if (!(s.getScores()[i].first = 0 && s.getScores()[i].second.compare("-----")))
			out << s.getScores()[i].first << "," << s.getScores()[i].second << std::endl;
	}
	return out;
 }
*/

#endif //SCOREBOARD_H