#pragma once
#include "domain.h"
#include "repository.h"
#include <string>
#include <vector>

class TutorialException : public std::exception {
private:
	std::string errorMessage;
public:
	TutorialException(std::string errorMessage);
	std::string getError() const noexcept;
};

class TutorialValidator {
public:
	static void validateTutorial(Tutorial& tutorial);
};

class RepositoryValidator {
public:
	void validateAdd(Tutorial& tutorial, std::vector<Tutorial> tutorialList);
	void validateUpdate(Tutorial& tutorial, std::vector<Tutorial> tutorialList);
	void validateDelete(std::string tutorialTitle, std::vector<Tutorial> tutorialList);
	bool existingElement(Tutorial tutorial, std::vector<Tutorial> vector);
};