#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "Scoreboard.h"
#include <sstream>

//add score by score pair
void Scoreboard::addScore(const Scoreboard::Score& s)
{
	// Add score
	scores.push_back(s);
	// Sort highest to lowest
	sort(scores.begin(), scores.end(), greater<>());
}

//add score by score and name
void Scoreboard::addScore(int score, string name)
{
	Score temp;
	temp.first = score;
	temp.second = name;
	
	if(!contains(score,name))
		scores.push_back(temp);

	sort(scores.begin(), scores.end(), greater<>());

}

//a function to see if it already contains the same entree
bool Scoreboard::contains(int score, std::string name)
{
	for (auto i = 0; i < scores.size(); i++)
		if (scores[i].first == score && scores[i].second.compare(name.c_str()) == 0)
			return true;
		
	
	return false;

}

//not sure if this is needed still
// Print high scores
sf::String Scoreboard::printScores()
{
	std::ostringstream sout;
	sout << "***************** High Scores ******************" << endl;
	sout << "Name    Score" << endl;
	for (int i = 0; i < 3; i++)
	{
		sout << scores[i].second << " : ";
		sout << scores[i].first << endl;
	}
	return sout.str();
}




//assuming everything on the text file is in format:
/*
score,name
1,p a t
200,83owpe

*/
void Scoreboard::readScoresFromFile(const string& fileName)
{
	ifstream fin(fileName);//assuming each score is stored score, name

	if (!fin) {
		//THROW EXCEPTION HERE
	}
	else {
		while (!fin.eof())
		{
			string scoreTemp, nameTemp;
			getline(fin, scoreTemp, ',');
			getline(fin, nameTemp);
			Score add;
			add.first = stoi(scoreTemp);
			add.second = nameTemp;

			addScore(add);
		}
	}

}


void Scoreboard::writeScoresToFile(const string& fileName)
{
	ofstream fout(fileName);

	//fout << this;

	fout.close();

}


Scoreboard::Scoreboard()
{
	Score defaultScore;
	defaultScore.first = 0;
	defaultScore.second = "-----";
	for (auto i = 0; i < 10; i++)
		scores.push_back(defaultScore);

	//read from the file
	readScoresFromFile("inputScoreFile.txt");


	//write to the file
	//writeScoresToFile("inputScoreFile.txt");

}

