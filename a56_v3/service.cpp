#include "service.h"


Service::Service()
{
	this->adminList = new TXTRepository();
	this->userList = new TXTRepository();
	this->currentPresenterList = new TutorialRepository();
	this->tutorialValidator = TutorialValidator();
	this->repoValidator = RepositoryValidator();
	this->currentTutorialPosition = 0;
}

Service::Service(FileRepository* adminList)
{
	this->adminList = adminList;
	this->userList = new TXTRepository();
	this->currentPresenterList = new TutorialRepository();
	this->tutorialValidator = TutorialValidator();
	this->repoValidator = RepositoryValidator();
	this->currentTutorialPosition = 0;
}

void Service::addTutorial(Tutorial tutorial)
{
	this->tutorialValidator.validateTutorial(tutorial);
	this->repoValidator.validateAdd(tutorial, adminList->getAllTutorials());
	adminList->addTutorial(tutorial);
	adminList->writeToFile();
}

void Service::updateTutorial(Tutorial tutorial)
{
	this->tutorialValidator.validateTutorial(tutorial);
	this->repoValidator.validateUpdate(tutorial, adminList->getAllTutorials());
	adminList->updateTutorial(tutorial);
	adminList->writeToFile();
}

void Service::deleteTutorial(std::string& title)
{
	this->repoValidator.validateDelete(title, adminList->getAllTutorials());
	Tutorial tutorialToDelete = Tutorial(title);
	adminList->deleteTutorial(tutorialToDelete);
	adminList->writeToFile();
}

void Service::deleteTutorialWatchlist(std::string& title)
{
	this->repoValidator.validateDelete(title, userList->getAllTutorials());
	Tutorial tutorialToDelete = Tutorial(title);
	userList->deleteTutorial(tutorialToDelete);
	userList->writeToFile();
}

void Service::deleteTutorialWatchlistLike(std::string& title)
{
	this->repoValidator.validateDelete(title, userList->getAllTutorials());
	Tutorial tutorialToDelete = adminList->getTutorialByTitle(title);
	tutorialToDelete.setLikes(tutorialToDelete.getLikes() + 1);
	adminList->updateTutorial(tutorialToDelete);
	currentPresenterList->updateTutorial(tutorialToDelete);
	userList->deleteTutorial(tutorialToDelete);
	adminList->writeToFile();
	userList->writeToFile();
}

std::vector<Tutorial> Service::getAllTutorials() const
{
	return adminList->getAllTutorials();
}

void Service::loadTutorialRepo(std::string filePath)
{
	delete this->adminList;
	this->adminList = new TXTRepository();
	this->adminList->readFromFile(filePath);
}

Tutorial Service::nextTutorial()
{
	currentTutorialPosition++;
	if (currentTutorialPosition < currentPresenterList->getNumberOfTutorials())
		return currentPresenterList->getTutorialByPosition(currentTutorialPosition);

	currentTutorialPosition = 0;
	return currentPresenterList->getTutorialByPosition(currentTutorialPosition);

}

void Service::saveTutorial()
{
	Tutorial tutorialToWatch = currentPresenterList->getTutorialByPosition(currentTutorialPosition);
	this->repoValidator.validateAdd(tutorialToWatch, userList->getAllTutorials());
	userList->addTutorial(tutorialToWatch);
	userList->writeToFile();
}

std::vector<Tutorial> Service::filterTutorialsByPresenter(std::string& presenter)
{
	if(presenter!="")
	{
		this->currentPresenterList->setList(adminList->filterTutorialsByPresenter(presenter));
		return adminList->filterTutorialsByPresenter(presenter);
	}
	else
	{
		this->currentPresenterList->setList(adminList->getAllTutorials());
		return adminList->getAllTutorials();
	}
	
}


std::vector<Tutorial> Service::getWatchList() const
{
	return userList->getAllTutorials();
}

void Service::openWatchList()
{
	this->userList->openFile();
}

void Service::setUserListType(std::string filePath, std::string fileExtension)
{
	if (strcmp(fileExtension.c_str(), "csv") == 0)
	{
		delete this->userList;
		this->userList = new CSVRepository();
	}
	else
	{
		if (strcmp(fileExtension.c_str(), "html") == 0)
		{
			delete this->userList;
			this->userList = new HTMLRepository();
		}
	}
	userList->setPath(filePath);
}
