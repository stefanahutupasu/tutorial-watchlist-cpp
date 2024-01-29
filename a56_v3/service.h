#pragma once
#include "repository.h"
#include "domain.h"
#include "validator.h"

class Service
{
private:
	FileRepository* adminList;
	FileRepository* userList;
	TutorialRepository* currentPresenterList;
	TutorialValidator tutorialValidator;
	RepositoryValidator repoValidator;

public:
	int currentTutorialPosition;

	//constrcutor
	Service();

	//constructor with a given admin repo
	Service(FileRepository* adminList);

	//adds a tutorial to the admin list
	void addTutorial(Tutorial tutorial);

	//updates a tutorial with the given title; the title remains unchanged
	void updateTutorial(Tutorial tutorial);

	//deletes the tutorial with the given title from the admin controlled database
	void deleteTutorial(std::string& title);

	//deletes a tutorial from the user's watchlist
	void deleteTutorialWatchlist(std::string& title);

	//deletes a tutorial from the user's watchlist and updates it by adding a new like
	void deleteTutorialWatchlistLike(std::string& title);

	//returns a vector containing all tutorials from the admin list
	std::vector<Tutorial> getAllTutorials() const;

	//loads the admin list from the given file
	void loadTutorialRepo(std::string filePath);

	//iterates the tutorial in the watching queue
	Tutorial nextTutorial();

	//saves the current tutorial to the watchlist
	void saveTutorial();

	//returns a vector containing all tutorials with the given presenter
	std::vector<Tutorial> filterTutorialsByPresenter(std::string& presenter);

	//returns a vector containing all tutorials from the watchlist
	std::vector<Tutorial> getWatchList() const;

	//opens the watchlist with the appropriate application
	void openWatchList();

	//sets the watchlist repo type (html/cvs)
	void setUserListType(std::string filepath, std::string fileExtension);

}; 