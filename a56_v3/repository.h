#pragma once
#include "domain.h"
#include <vector>

class TutorialRepository
{
protected:
	
	std::vector<Tutorial> tutorialList;
	
public:
	//constructor
	TutorialRepository() {}
	
	//adds a tutorial 
	void addTutorial(Tutorial tutorialToAdd);
	
	//updates a tutorial 
	void updateTutorial(Tutorial tutorialToUpdate);
	
	//deletes a tutorial 
	void deleteTutorial(Tutorial tutorialToDelete);
	
	//returns a vector containing all tutorials from the database
	std::vector<Tutorial> getAllTutorials() const;

	//returns the number of tutorials in the current repo
	int getNumberOfTutorials();

	//returns a vector containing only tutorials with a given presenter
	std::vector<Tutorial> filterTutorialsByPresenter(std::string& presenter);

	//returns the tutorial on the given position
	Tutorial getTutorialByPosition(int position);

	//returns a tutorial with the given title
	Tutorial getTutorialByTitle(std::string tutorialTitle);

	//changes the TutorialList of the current repo with the given vector
	void setList(std::vector<Tutorial>);

};

class FileRepository : public TutorialRepository {
protected:
	std::string filePath;
public:

	//setter for the filepath
	void setPath(std::string filePath);

	//opens the file with the appropriate application
	void openFile();

	//reads the content of a file
	virtual void readFromFile(std::string filePath) = 0;
	
	//writes to the file the content of the repo
	virtual void writeToFile() = 0;
};

class TXTRepository : public FileRepository {
public:
	void readFromFile(std::string filePath);
	void writeToFile();
};

class CSVRepository : public FileRepository {
public:
	void readFromFile(std::string filePath) { return; }
	void writeToFile();
};

class HTMLRepository : public FileRepository {
public:
	void readFromFile(std::string filePath) { return; }
	void writeToFile();
};


