#pragma once
#include <iostream>
#include <vector>

class Tutorial
{
private:
	std::string title;
	std::string presenter;
	int minutes;
	int seconds;
	int likes;
	std::string link;



public:

	static int numberOfInstances;
	static int getNumberOfInstances();

	//default constructor
	Tutorial();
	//constructor with parameters
	Tutorial(std::string& title, std::string& presenter, int minutes,int seconds, int likes, std::string& link);
	
	Tutorial(std::string& title);
	
	//copy constructor
	Tutorial(const Tutorial& tutorial);
	//destructor
	~Tutorial();
	//assignement operator
	Tutorial operator= (const Tutorial& tutorial);
	//returns True if the current tutorial has the same characteristics as the given tutorial
	bool operator== (const Tutorial& tutorial);
	//setter for the title
	void setTitle(std::string& newTitle);
	//setter for the presenter's name
	void setPresenter(std::string& newPresenter);
	//setter for the minutes
	void setMinutes(int newMinutes);
	//setter for the seconds
	void setSeconds(int newSeconds);
	//setter for the likes
	void setLikes(int newLikes);
	//setter for the link
	void setLink(std::string& newLink);
	//getter for the title
	std::string getTitle();
	//getter for the presenter
	std::string getPresenter();
	//getter for the minutes
	int getMinutes();
	//getter fot the seconds
	int getSeconds();
	//getter for the number of likes
	int getLikes();
	//getter for the link
	std::string getLink();
	//returns the tutorial's details as a more organized string, ready for output
	std::string toStringTutorial();

	//extraction operator for reading from txt file
	friend std::istream& operator>>(std::istream& inputStream, Tutorial& tutorial);
	friend std::ostream& operator<<(std::ostream& outputStream, Tutorial& tutorial);
};

