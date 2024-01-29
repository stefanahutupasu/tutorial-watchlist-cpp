#define _CRT_SECURE_NO_WARNINGS
#include "ui.h"
#include <string>
#include <cstring>
#include <iostream>
#include <sstream>

using namespace std;

UI::UI()
{
	FileRepository* adminList = new TXTRepository();
	this->service = Service(adminList);
}

bool UI::checkIfNumber(std::string& stringToCheck)
{
	int length = stringToCheck.length();
	for (int index = 0; index < length; index++)
		if (stringToCheck[index] < '0' || stringToCheck[index] > '9')
			return false;

	return true;
}

std::vector<std::string> tokenizeUI(std::string stringToBeRead, char delimiter)
{
	std::vector <std::string> result;
	std::stringstream ss(stringToBeRead);
	std::string token;
	while (getline(ss, token, delimiter))
		result.push_back(token);

	return result;
}


void UI::UIAddTutorial(char* parameters)
{
	std::string title, presenter, link;
	int minutes, seconds, likes;

	
	std::vector<std::string> tokens = tokenizeUI(parameters, ',');
	if (tokens.size() != 6)
	{
		cout << "Invalid numbers of parameters for the add function!\n";
		return;
	}
	
	title = tokens[0];
	presenter = tokens[1];
	minutes = atoi(tokens[2].c_str());
	seconds = atoi(tokens[3].c_str());
	likes = atoi(tokens[4].c_str());
	link = tokens[5];

	try
	{
		Tutorial tutorialToAdd = Tutorial(title, presenter, minutes, seconds, likes, link);
		service.addTutorial(tutorialToAdd);
		cout << "Tutorial added successfully!\n";
	}

	catch (TutorialException& exception)
	{
		cout << exception.getError() << endl;
	}

}

void UI::UIUpdateTutorial(char* parameters)
{
	std::string title, presenter, link;
	int minutes, seconds, likes;
	
	std::vector<std::string> tokens = tokenizeUI(parameters, ',');
	if (tokens.size() != 6)
	{
		cout << "Invalid numbers of parameters for the update function!\n";
		return;
	}

	title = tokens[0];
	presenter = tokens[1];
	minutes = atoi(tokens[2].c_str());
	seconds = atoi(tokens[3].c_str());
	likes = atoi(tokens[4].c_str());
	link = tokens[5];
	
	try
	{
		Tutorial tutorialToUpdate = Tutorial(title, presenter, minutes, seconds, likes, link);
		service.updateTutorial(tutorialToUpdate);
		cout << "Tutorial updated successfully!\n";
	}

	catch (TutorialException& exception)
	{
		cout << exception.getError() << endl;
	}
}

void UI::UIDeleteTutorial(char* parameters)
{
	std::string title;

	parameters = strtok(parameters, "\n");
	title = parameters;
	try
	{
		service.deleteTutorial(title);
		cout << "Tutorial deleted successfully!\n";
	}

	catch (TutorialException& exception)
	{
		cout << exception.getError() << endl;
	}
}

void UI::UIListAll()
{
	std::vector<Tutorial> tutorialList = service.getAllTutorials();

	for (auto tutorial : tutorialList)
		cout << tutorial.toStringTutorial().c_str() << endl;
}

void UI::UINext()
{
	Tutorial nextTutorial = service.nextTutorial();
	cout << nextTutorial.toStringTutorial().c_str() << endl;
}

void UI::UIFilter(char* parameters)
{
	std::string filterParameter = "";
	if (parameters != NULL)
	{
		parameters = strtok(parameters, "\n");
		filterParameter = parameters;
		
	}
	else cout << "You are now watching all tutorials, one by one.\n";
	
	std::vector<Tutorial> filteredTutorials = service.filterTutorialsByPresenter(filterParameter);
	if (filteredTutorials.size() == 0)
		cout << "Seems like there are no tutorials with that given presenter...\n";
	else 
		if(parameters != NULL)
			cout << "You are now watching tutorials by " << parameters << ".\n";
	
	for (auto tutorial : filteredTutorials)
	{
		cout << tutorial.toStringTutorial().c_str() << endl;
		break;
	}
	
	service.currentTutorialPosition = 0;
	


}

void UI::UIAddToWatchlist()
{
	std::string title;

	//parameters = strtok(parameters, ",\n");
	
	try
	{
		service.saveTutorial();
		cout << "Tutorial successfully added to the watchlist!\n";
	}

	catch (TutorialException& exception)
	{
		cout << exception.getError() << endl;
	}
}

void UI::UISetFilePath(char* parameters)
{
	service.loadTutorialRepo(parameters);
}


void UI::UIWatchlistLocation(char* parameters)
{
	parameters = strtok(parameters, ".");
	std::string filePath = parameters;

	parameters = strtok(NULL, "\n");
	std::string fileExtension = parameters;

	filePath += ".";
	filePath += fileExtension;

	this->service.setUserListType(filePath, fileExtension);

}

void UI::UIDeleteFromWatchlist(char* parameters)
{
	std::string title;

	parameters = strtok(parameters, "\n");
	title = parameters;
	try
	{
		service.deleteTutorialWatchlist(title);
		cout << "Tutorial deleted successfully from the watchlist!\n";
	}

	catch (TutorialException& exception)
	{
		cout << exception.getError() << endl;
	}
}

void UI::UIDeleteFromWatchlistLike(char* parameters)
{
	std::string title;

	parameters = strtok(parameters, "\n");
	title = parameters;
	try
	{
		service.deleteTutorialWatchlistLike(title);
		cout << "Tutorial deleted successfully from the watchlist! Thank you for the like!\n";
	}

	catch (TutorialException& exception)
	{
		cout << exception.getError() << endl;
	}
}


void UI::UIListWatchlist()
{
	std::vector<Tutorial> tutorialList = service.getWatchList();

	for (auto tutorial : tutorialList)
		cout << tutorial.toStringTutorial().c_str() << endl;

	service.openWatchList();
}

void UI::UIPrintMenu()
{
	cout << "First 3 commands must be:\n";
	cout <<  "fileLocation <file name>, watchlistLocation <file name>, mode <admin/user>\n";
	cout << "\n";
	cout << "Available commands:\n";
	cout << "|| Admin Mode ||\n";
	cout << "0. Change the repository file >> fileLocation <file name>\n";
	cout << "1. Change to user mode >> mode user\n";
	cout << "2. List all tutorials >> list\n";
	cout << "3. Add a tutorial >> add <title>,<presenter>,<minutes>,<seconds>,<likes>,<link>\n";
	cout << "4. Update a tutorial >> update <title>,<presenter>,<minutes>,<seconds>,<likes>,<link>\n";
	cout << "5. Delete a tutorial >> delete <title>\n";
	cout << "6.  Exit the program >> exit\n";
	cout << "\n|| User Mode ||\n";
	cout << "0. Set the watchlist file and extension >> watchlistLocation <file name>";
	cout << "1. Change to admin mode >> mode admin\n";
	cout << "2. View tutorials with a given presenter, one by one >> list <presenter>\n";
	cout << "3. View all tutorials, one by one >> list \n";
	cout << "4. View next tutorial >> next\n";
	cout << "5. Save the current tutorial to the watchlist >> save\n";
	cout << "6. Delete a tutorial from the watchlist >> delete <title>\n";
	cout << "7. Like and delete a tutorial from the watchlist >> like <title>\n";
	cout << "8. Exit the program >> exit\n\n";

}

void UI::run()
{
	char command[256];
	char* token;
	int mode = 0;

	UIPrintMenu();

	for (int index = 0; index < 3; index++)
	{
		cin.getline(command, 256);
		token = strtok(command, "\n");

		if (strcmp(token, "mode admin") == 0)
		{
			mode = 1;
			cout << "You are now in administrator mode.\n";
		}
		else if (strcmp(token, "mode user") == 0)
		{
			mode = 2;
			cout << "You are now in user mode.\n";
		}
		else
		{
			token = strtok(command, " ");
			if (strcmp(token, "fileLocation") == 0)
			{
				token = strtok(NULL, "\n");
				UISetFilePath(token);
			}

			else if (strcmp(token, "watchlistLocation") == 0)
			{
				token = strtok(NULL, "\n");
				this->UIWatchlistLocation(token);
			}
			else return;
		}
	}
	//ok pana aici cred
	while (true)
	{
		cin.getline(command, 256);
		token = strtok(command, " ,");
		if (strcmp(token, "mode") == 0)
		{
			token = strtok(NULL, " ,");
			if (strcmp(token, "admin") == 0)
			{
				mode = 1;
				cout << "You are now in administrator mode.\n";
			}
			else if (strcmp(token, "user") == 0)
			{
				mode = 2;
				cout << "You are now in user mode.\n";
			}
			else return;
		}

		else if (mode == 1)
		{
			if (strcmp(token, "add") == 0)
			{
				token = strtok(NULL, "\n");
				if (token == NULL)
					cout << "No parameters given for the add function!\n";
				else
				UIAddTutorial(token);
			}
			else if (strcmp(token, "update") == 0)
			{
				token = strtok(NULL, "\n");
				if (token == NULL)
					cout << "No parameters given for the update function!\n";
				else
				UIUpdateTutorial(token);
			}
			else if (strcmp(token, "delete") == 0)
			{
				token = strtok(NULL, "\n");
				if (token == NULL)
					cout << "No parameter given for the delete function!\n";
				else
				UIDeleteTutorial(token);
			}
			else if (strcmp(token, "list") == 0)
				UIListAll();
			else if (strcmp(token, "exit") == 0)
				return;
			else if (strcmp(token, "fileLocation") == 0)
			{
				token = strtok(NULL, "\n");
				UISetFilePath(token);
			}
			else
				cout << "Invalid command!\n";
		}
		//
		else
		{
			if (strcmp(token, "next") == 0)
				UINext();
			else if (strcmp(token, "save") == 0)
			{
				//token = strtok(NULL, "\n");
				UIAddToWatchlist();
			}

			else if (strcmp(token, "list") == 0)
			{
				token = strtok(NULL, "\n");
				//if (token == NULL)
					//cout << "No parameter given for the l function!\n";
				//else
				UIFilter(token);
			}

			else if (strcmp(token, "watchlist") == 0)
			{
				UIListWatchlist();
			}

			else if (strcmp(token, "delete") == 0)
			{
				token = strtok(NULL, "\n");
				if (token == NULL)
					cout << "No parameter given for the delete function!\n";
				else
					UIDeleteFromWatchlist(token);
			}

			else if (strcmp(token, "like") == 0)
			{
				token = strtok(NULL, "\n");
				if (token == NULL)
					cout << "No parameter given for the delete+like function!\n";
				else
					UIDeleteFromWatchlistLike(token);
			}

			else if (strcmp(token, "exit") == 0)
				return;

			else
				cout << "Invalid input!\n";
		}
	}

}
/*
void UI::UIAddTutorialAsAdmin(Tutorial& tutorialToAdd)
{
	std::string title = tutorialToAdd.getTitle();
	if(!service.tutorialExistsTitle(title))
	{
		service.addTutorialAsAdmin(tutorialToAdd);
		cout << "Tutorial was added successfully to the database!\n";
	}
	else cout << "Tutorial already exists!\n";
		
}

void UI::UIUpdateTutorial(std::string& title, std::string& presenter, int minutes, int seconds, int likes, std::string& link)
{
	
	if (service.tutorialExistsTitle(title))
	{
		service.updateTutorial(title, presenter, minutes, seconds, likes, link);
		cout << "The specified tutorial has been updated successfully!\n";
	}
	else cout << "The specified tutorial is not part of the database!\n";
	
}

void UI::UIDeleteTutorial(std::string& title)
{
	if (service.tutorialExistsTitle(title))
	{
		service.deleteTutorial(title);
		cout << "The specified tutorial has been deleted successfully!\n";
	}
	else cout << "You cannot delete a tutorial that does not exist in the database!\n";
}

void UI::UIDeleteTutorialWatchList(std::string& title)
{
	if (service.tutorialInWatchList(title))
	{
		service.deleteTutorialWatchList(title);
		cout << "The specified tutorial has been deleted successfully from your watchlist!\n";
	}
	else cout << "You cannot delete a tutorial that does not exist in the watchlist!\n";
}

void UI::UILikeTutorialWatchList(std::string& title)
{
	if (service.tutorialInWatchList(title))
	{
		//tutorial = service.
		service.likeTutorialWatchList(title);
		cout << "Thank you for your like! The specified tutorial has been deleted successfully from your watchlist!\n";
	}
	else cout << "You cannot delete a tutorial that does not exist in the watchlist!\n";
}

void UI::UIAddTutorialToWatchList()
{
	std::string title = service.getCurrentTutorial().getTitle();
	service.addTutorialToWatchList(title);
	cout << "The current tutorial has been added to your watchlist!\n";
}

void UI::UIListAll()
{
	DynamicVector<Tutorial> allTutorials = service.getAllTutorials();
	for (int index = 0; index < allTutorials.getSize(); index++)
		cout << allTutorials[index].toStringTutorial() << endl;
}

void UI::UIListWatchList()
{
	DynamicVector<Tutorial> userWatchList = service.getWatchList();
	for (int index = 0; index < userWatchList.getSize(); index++)
		cout << userWatchList[index].toStringTutorial() << endl;
}

void UI::UIWatchCurrentTutorial()
{
	cout << service.getCurrentTutorial().toStringTutorial() << endl;
	std::string link = service.getCurrentTutorial().getLink();
	//system(std::string("start " + link).c_str());
}

void UI::UINext()
{
	service.nextTutorial();
}

void UI::UIPlay()
{
	std::string link = service.getCurrentTutorial().getLink();
	system(std::string("start " + link).c_str());
}

void UI::UIWatchAll()
{
	//service.resetCurrent();
	service.allPresenterList();
	UIWatchCurrentTutorial();
}

void UI::UIWatchPresenter(std::string& presenter)
{
	service.resetPresenterList(presenter);
	UIWatchCurrentTutorial();
}

void UI::UIPrintAdminMenu()
{
	cout << "||Administrator Mode||\n" << "Available commands: \n" << "Switch to User Mode >> mode user\n" << "Add tutorial to database >> add title,presenter,minutes,seconds,likes,link\n" << "Update a tutorial with a given title >> update title,presenter,minutes,seconds,likes,link\n" << "Delete a tutorial from the database >> delete title\n" << "View the database >> list\n" << "Exit >> exit\n";
}

void UI::UIPrintUserMenu()
{
	cout << "||User Mode||\n" << "Available commands: \n" << "Switch to Administrator Mode >> mode admin\n" << "Watch tutorials with a given presenter >> presenter name\n" << "Watch next tutorial >> next\n" << "Play tutorial in browser >> play\n" << "Add current tutorial to your watchlist >> add\n" << "View your watchlist >> watchlist\n" << "Delete a tutorial from your watchlist >> delete title\n" <<"Like a tutorial before deleting it from the watchlist >> like title\n" << "Exit >> exit\n";
}

void UI::UIInitializeRepo()
{
	std::string title = "Intro to C++";
	std::string presenter = "Caleb Curry";
	std::string link = "https://www.youtube.com/watch?v=OTroAxvRNbw&list=PL_c9BZzLwBRJVJsIfe97ey45V4LP_HXiG&index=4&ab_channel=CalebCurry";
	Tutorial t1 = Tutorial(title, presenter, 9, 32, 6700, link);
	service.addTutorialAsAdmin(t1);
	title = "What Are Pointers?";
	presenter = "javidx9";
	link = "https://www.youtube.com/watch?v=iChalAKXffs&ab_channel=javidx9";
	Tutorial t2 = Tutorial(title, presenter, 41, 54, 13000, link);
	service.addTutorialAsAdmin(t2);
	title = "C++ Concepts Explained";
	presenter = "Caleb Curry";
	link = "https://www.youtube.com/watch?v=i0B_0b3EKFs&list=PL_c9BZzLwBRJVJsIfe97ey45V4LP_HXiG&index=6&ab_channel=CalebCurry";
	Tutorial t3 = Tutorial(title, presenter, 8, 30, 2300, link);
	service.addTutorialAsAdmin(t3);
	title = "Variables";
	presenter = "Mike Dane";
	link = "https://www.youtube.com/watch?v=K8Rqul0V8_U&list=PLLAZ4kZ9dFpOSzRXG05goZMgsvXwDDL6g&index=7&ab_channel=MikeDane";
	Tutorial t4 = Tutorial(title, presenter, 12, 10, 267, link);
	service.addTutorialAsAdmin(t4);
	title = "Forbidden C++";
	presenter = "javidx9";
	link = "https://www.youtube.com/watch?v=j0_u26Vpb4w&ab_channel=javidx9";
	Tutorial t5 = Tutorial(title, presenter, 33, 10, 26000, link);
	service.addTutorialAsAdmin(t5);
	title = "Lambda Expressions";
	presenter = "Derek Banas";
	link = "https://www.youtube.com/watch?v=482weZjwVHY&ab_channel=DerekBanas";
	Tutorial t6 = Tutorial(title, presenter, 25, 20, 768, link);
	service.addTutorialAsAdmin(t6);
	title = "Getting Started";
	presenter = "Caleb Curry";
	link = "https://www.youtube.com/watch?v=aVqZ3lZD8Qk&list=PL_c9BZzLwBRJVJsIfe97ey45V4LP_HXiG&index=5&ab_channel=CalebCurry";
	Tutorial t7 = Tutorial(title, presenter, 6, 26, 2200, link);
	service.addTutorialAsAdmin(t7);
	title = "Install C++";
	presenter = "Derek Banas";
	link = "https://www.youtube.com/watch?v=DamuE8TM3xo&ab_channel=DerekBanas";
	Tutorial t8 = Tutorial(title, presenter, 6, 55, 1500, link);
	service.addTutorialAsAdmin(t8);
	title = "Setup & Hello World";
	presenter = "Mike Dane";
	link = "https://www.youtube.com/watch?v=q4zIPCmPlqI&list=PLLAZ4kZ9dFpOSzRXG05goZMgsvXwDDL6g&index=5&ab_channel=MikeDane";
	Tutorial t9 = Tutorial(title, presenter, 4, 10, 213, link);
	service.addTutorialAsAdmin(t9);
	title = "C++ Strings";
	presenter = "Caleb Curry";
	link = "https://www.youtube.com/watch?v=qUcHK3zVp1I&ab_channel=CalebCurry";
	Tutorial t10 = Tutorial(title, presenter, 9, 58, 160, link);
	service.addTutorialAsAdmin(t10);

}


void UI::run()
{
	int printMenu = 0;
	char command[256];

	fgets(command, sizeof(command), stdin);
	char* commandParameter;
	commandParameter = strtok(command, " \n");

	if (commandParameter == NULL)
	{
		return;
	}

	else if (strcmp(commandParameter, "mode") == 0)
	{
		commandParameter = strtok(NULL, "\n");
		if (strcmp(commandParameter, "admin") == 0)
		{
			mode = 1;
		}

		else
			if (strcmp(commandParameter, "user") == 0)
			{
				mode = 2;
			}
			else
				return;
	}

	else
		return;

	while (1)
	{
		if (mode == 1)
		{
			if (printMenu == 0)
			{
				UIPrintAdminMenu();
				printMenu = 1;
			}

			fgets(command, sizeof(command), stdin);
			char* commandParameter;
			commandParameter = strtok(command, " \n");

			if (strcmp(commandParameter, "mode") == 0)
			{
				commandParameter = strtok(NULL, "\n");

				if (strcmp(commandParameter, "admin") == 0)
					mode = 1;
				else
					if (strcmp(commandParameter, "user") == 0)
					{
						mode = 2;
						printMenu = 0;
					}
					else
						cout << "Invalid command!\n";
			}

			else if (strcmp(commandParameter, "add") == 0)
			{
				commandParameter = strtok(NULL, ",");
				if (commandParameter != NULL)
				{
					std::string title = commandParameter;

					commandParameter = strtok(NULL, ",");
					if (commandParameter != NULL)
					{
						std::string presenter = commandParameter;
						while (presenter[0] == ' ')
							presenter.erase(presenter.begin());

						commandParameter = strtok(NULL, ",");
						std::string minutes = commandParameter;
						if (checkIfNumber(minutes))
						{
							int minutes = atoi(commandParameter);

							commandParameter = strtok(NULL, ",");
							std::string seconds = commandParameter;
							if (checkIfNumber(seconds))
							{
								int seconds = atoi(commandParameter);

								commandParameter = strtok(NULL, ",");
								std::string likes = commandParameter;
								if (checkIfNumber(likes))
								{
									int likes = atoi(commandParameter);

									commandParameter = strtok(NULL, "\n ");
									if (commandParameter != NULL)
									{
										std::string link = commandParameter;

										Tutorial tutorialToAdd = Tutorial(title, presenter, minutes, seconds, likes, link);

										UIAddTutorialAsAdmin(tutorialToAdd);
									}
								}
								else
									cout << "Invalid input!\n";
							}

							else
								cout << "Invalid input!\n";
						}
						else
							cout << "Invalid input!\n";
					}
					else
						cout << "Invalid input!\n";
				}
				else
					cout << "Invalid input!\n";
			}

			else if (strcmp(commandParameter, "update") == 0)
			{
				commandParameter = strtok(NULL, ",");
				if (commandParameter != NULL)
				{
					std::string title = commandParameter;

					commandParameter = strtok(NULL, ",");
					if (commandParameter != NULL)
					{
						std::string presenter = commandParameter;
						while (presenter[0] == ' ')
							presenter.erase(presenter.begin());

						commandParameter = strtok(NULL, ",");
						std::string minutes = commandParameter;
						if (checkIfNumber(minutes))
						{
							int minutes = atoi(commandParameter);

							commandParameter = strtok(NULL, ",");
							std::string seconds = commandParameter;
							if (checkIfNumber(seconds))
							{
								int seconds = atoi(commandParameter);

								commandParameter = strtok(NULL, ",");
								std::string likes = commandParameter;
								if (checkIfNumber(likes))
								{
									int likes = atoi(commandParameter);

									commandParameter = strtok(NULL, "\n ");
									if (commandParameter != NULL)
									{
										std::string link = commandParameter;

										UIUpdateTutorial(title, presenter, minutes, seconds, likes, link);
									}
								}
								else
									cout << "Invalid input!\n";
							}

							else
								cout << "Invalid input!\n";
						}
						else
							cout << "Invalid input!\n";
					}
					else
						cout << "Invalid input!\n";
				}
				else
					cout << "Invalid input!\n";
			}

			else if (strcmp(commandParameter, "delete") == 0)
			{
				commandParameter = strtok(NULL, "\n");
				std::string title = commandParameter;

				UIDeleteTutorial(title);
			}

			else if (strcmp(commandParameter, "list") == 0)
			{
				UIListAll();
			}

			else if (strcmp(commandParameter, "exit") == 0)
				return;

			else
				cout << "Invalid command, try again!\n";
		}
		
		if (mode == 2)
		{
			if (printMenu == 0)
			{
				UIPrintUserMenu();
				printMenu = 1;
			}

			fgets(command, sizeof(command), stdin);
			char* commandParameter;
			commandParameter = strtok(command, " \n");

			if (strcmp(commandParameter, "mode") == 0)
			{
				commandParameter = strtok(NULL, "\n");

				if (strcmp(commandParameter, "admin") == 0)
				{
					mode = 1;
					printMenu = 0;
				}
					
				else
					if (strcmp(commandParameter, "user") == 0)
					{
						mode = 2;
					}
					else
						cout << "Invalid command!\n";
			}
			else if (strcmp(commandParameter, "exit") == 0)
				return;
			else if (strcmp(commandParameter, "presenter") == 0)
			{
				commandParameter = strtok(NULL, "\n");
				if (commandParameter == NULL)
				{
					cout << "Watching all\n";
					UIWatchAll();
				}
				else {
					cout << "Watching a presenter\n";
					std::string presenter = commandParameter;
					UIWatchPresenter(presenter);
				}
			}
			else if (strcmp(commandParameter, "next") == 0)
			{
				cout << "Next tutorial\n";
				UINext();
				UIWatchCurrentTutorial();
			}
			else if (strcmp(commandParameter, "play") == 0)
			{
				UIPlay();
			}

			else if (strcmp(commandParameter, "add") == 0)
			{
				UIAddTutorialToWatchList();
			}

			else if (strcmp(commandParameter, "watchlist") == 0)
			{
				UIListWatchList();
			}

			else if (strcmp(commandParameter, "delete") == 0)
			{
				commandParameter = strtok(NULL, "\n");
				std::string title = commandParameter;

				UIDeleteTutorialWatchList(title);
			}
			else if (strcmp(commandParameter, "like") == 0)
			{
				commandParameter = strtok(NULL, "\n");
				std::string title = commandParameter;

				UILikeTutorialWatchList(title);
			}
			else
				cout << "Invalid command, try again!\n";
		}
		
	}
}

*/
