#include "repository.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

void TutorialRepository::addTutorial(Tutorial tutorialToAdd)
{
	this->tutorialList.push_back(tutorialToAdd);
}

void TutorialRepository::updateTutorial(Tutorial tutorialToUpdate)
{
	
	auto tutorialIterator = std::find_if(this->tutorialList.begin(), this->tutorialList.end(), [&tutorialToUpdate]( Tutorial& obj) {return obj.getTitle() == tutorialToUpdate.getTitle(); });

	if (tutorialIterator != this->tutorialList.end())
	{
		this->tutorialList.at(tutorialIterator - this->tutorialList.begin()) = tutorialToUpdate;
	}

}

void TutorialRepository::deleteTutorial(Tutorial tutorialToDelete)
{
	
	auto tutorialIterator = std::find_if(this->tutorialList.begin(), this->tutorialList.end(), [&tutorialToDelete](Tutorial& obj) {return obj.getTitle() == tutorialToDelete.getTitle(); });

	if (tutorialIterator != this->tutorialList.end())
	{
		this->tutorialList.erase(tutorialIterator);
	}
}


std::vector<Tutorial> TutorialRepository::getAllTutorials() const
{
	
	return this->tutorialList;
}


int TutorialRepository::getNumberOfTutorials()
{
	return this->tutorialList.size();
}

std::vector<Tutorial> TutorialRepository::filterTutorialsByPresenter(std::string& presenter)
{
	std::vector<Tutorial> filteredTutorials(this->tutorialList.size());
	auto tutorialsIterator = std::copy_if(this->tutorialList.begin(), this->tutorialList.end(), filteredTutorials.begin(), [presenter](Tutorial tutorial) {return (tutorial.getPresenter() == presenter ); });
	filteredTutorials.resize(std::distance(filteredTutorials.begin(), tutorialsIterator));
	return filteredTutorials;
}

Tutorial TutorialRepository::getTutorialByPosition(int position)
{
	return this->tutorialList[position];
}

Tutorial TutorialRepository::getTutorialByTitle(std::string tutorialTitle)
{
	for (Tutorial element : tutorialList)
	{
		if (tutorialTitle == element.getTitle())
			return element;
	}
}

void FileRepository::setPath(std::string filePath)
{
	this->filePath = filePath;
}

void FileRepository::openFile()
{
	system(this->filePath.c_str());
}

void TXTRepository::readFromFile(std::string filePath)
{
	this->filePath = filePath;
	ifstream file(filePath);
	if (!file.is_open())return;

	Tutorial tutorial = Tutorial();
	while (file >> tutorial)
	{
		addTutorial(tutorial);
	}
	file.close();
}

void TXTRepository::writeToFile()
{
	ofstream file(this->filePath);
	if (!file.is_open())return;

	for (auto tutorial : getAllTutorials())
	{
		// file << tutorial.getTitle().c_str() << "," << tutorial.getPresenter().c_str() << "," << tutorial.getMinutes() << "," << tutorial.getSeconds() << "," << tutorial.getLikes() << "," << tutorial.getLink().c_str() << "\n";
		file << tutorial;
	}

	file.close();
}


void CSVRepository::writeToFile()
{
	ofstream file(this->filePath);
	if (!file.is_open())return;

	for (auto tutorial : getAllTutorials())
	{
		file << tutorial.getTitle().c_str() << "," << tutorial.getPresenter().c_str() << "," << tutorial.getMinutes() << "," << tutorial.getSeconds() << "," << tutorial.getLikes() << "," << tutorial.getLink().c_str() << "\n";
	}

	file.close();
}

void HTMLRepository::writeToFile()
{
	ofstream file(this->filePath);
	if (!file.is_open()) return;

	file << "<!DOCTYPE html>";
	file << "<html>";
	file << "	<head>";
	file << "		<title>Tutorials Watchlist</title>";
	file << "	</head>";
	file << "	<body>";
	file << "		<table border=" << char(34) << "1" << char(34) << ">";
	file << "		<tr>";
	file << "			<td>Title</td>";
	file << "			<td>Presenter</td>";
	file << "			<td>Duration</td>";
	file << "			<td>Likes</td>";
	file << "			<td>Link</td>";
	file << "		</tr>";

	for (auto movie : getAllTutorials()) {
		file << "		<tr>";
		file << "			<td>" << movie.getTitle().c_str() << "</td>";
		file << "			<td>" << movie.getPresenter().c_str() << "</td>";
		file << "			<td>" << movie.getMinutes() << ":" << movie.getSeconds() << "</td>";
		//file << "			<td>" << movie.getSeconds() << "</td>";
		file << "			<td>" << movie.getLikes() << "</td>";
		file << "			<td><a href=" << '"' << movie.getLink().c_str() << '"' << ">Link</a></td>";
		file << "		</tr>";
	}
	file << "		</table>";
	file << "	</body>";
	file << "</html>";
	file.close();

}


void TutorialRepository::setList(std::vector<Tutorial> list)
{
	this->tutorialList = list;
}
