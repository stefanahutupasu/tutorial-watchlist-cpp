#pragma once
#include "service.h"
#include "domain.h"
#include <iostream>
#include <string>

class UI
{
private:
	Service service;
	//int mode;

public:

	UI();// : mode(0) {}

	bool checkIfNumber(std::string& stringToCheck);

	void UIAddTutorial(char* parameters);

	void UIUpdateTutorial(char* parameters);

	void UIDeleteTutorial(char* parameters);

	void UIListAll();

	void UINext();

	void UIFilter(char* parameters);

	void UIAddToWatchlist();

	void UISetFilePath(char* parameters);

	void UIWatchlistLocation(char* parameters);


	void UIDeleteFromWatchlist(char* parameters);

	void UIDeleteFromWatchlistLike(char* parameters);

	void UIListWatchlist();

	void UIPrintMenu();

	void run();

	
};