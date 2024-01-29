#include "validator.h"

TutorialException::TutorialException(std::string errorMessage)
{
	this->errorMessage = errorMessage;
}

std::string TutorialException::getError() const noexcept
{
	return this->errorMessage;
}

void TutorialValidator::validateTutorial(Tutorial& tutorial)
{
	if(tutorial.getMinutes() < 0 or tutorial.getSeconds() < 0 or (tutorial.getMinutes()==0&&tutorial.getSeconds()==0) or tutorial.getLink().size()==0)
		throw TutorialException("Invalid tutorial!");
}

void RepositoryValidator::validateAdd(Tutorial& tutorial, std::vector<Tutorial> tutorialList)
{
	if (existingElement(tutorial, tutorialList))
		throw TutorialException("Existing tutorial!");
}

void RepositoryValidator::validateUpdate(Tutorial& tutorial, std::vector<Tutorial> tutorialList)
{
	if (!existingElement(tutorial, tutorialList))
		throw TutorialException("Inexistent tutorial!");
}

void RepositoryValidator::validateDelete(std::string tutorialTitle, std::vector<Tutorial> tutorialList)
{
	for (Tutorial element : tutorialList)
	{
		if (tutorialTitle == element.getTitle())
			return;
	}
	throw TutorialException("Inexistent tutorial!");
}

bool RepositoryValidator::existingElement(Tutorial tutorial, std::vector<Tutorial> tutorialList)
{
	for (Tutorial element : tutorialList)
	{
		if (tutorial.getTitle() == element.getTitle())
			return true;
	}
	return false;
}
