#include "domain.h"
#include <string>
#include <cstring>
#include <iostream>
#include <sstream>

//using namespace std;

int Tutorial::numberOfInstances = 0;

int Tutorial::getNumberOfInstances()
{
	return numberOfInstances;
}

Tutorial::Tutorial() : title(""), presenter(""), minutes(0),seconds(0), likes(0), link("")
{
	numberOfInstances++;
}

Tutorial::Tutorial(std::string& title, std::string& presenter, int minutes, int seconds, int likes, std::string& link)
{
	this->title = title;
	this->presenter = presenter;
	this->minutes = minutes;
	this->seconds = seconds;
	this->likes = likes;
	this->link = link;
	numberOfInstances++;
}

Tutorial::Tutorial(std::string& title)
{
	this->title = title;
	this->presenter = "";
	this->minutes = 0;
	this->seconds = 0;
	this->likes = 0;
	this->link = "";
	numberOfInstances++;
}

Tutorial::Tutorial(const Tutorial& tutorial)
{
	this->title = tutorial.title;
	this->presenter = tutorial.presenter;
	this->minutes = tutorial.minutes;
	this->seconds = tutorial.seconds;
	this->likes = tutorial.likes;
	this->link = tutorial.link;
	numberOfInstances++;
}

Tutorial::~Tutorial()
{
	//std::cout << "Destructor called." << std::endl;
	numberOfInstances--;
}

Tutorial Tutorial::operator=(const Tutorial& tutorial)
{
	this->title = tutorial.title;
	this->presenter = tutorial.presenter;
	this->minutes = tutorial.minutes;
	this->seconds = tutorial.seconds;
	this->likes = tutorial.likes;
	this->link = tutorial.link;
	return *this;
}

bool Tutorial::operator==(const Tutorial& tutorial)
{
	if (this->title == tutorial.title && this->presenter == tutorial.presenter && this->minutes == tutorial.minutes && this->seconds == tutorial.seconds && this->likes == tutorial.likes && this->link == tutorial.link)
		return true;
	return false;
}

void Tutorial::setTitle(std::string& newTitle)
{
	this->title = newTitle;
}

void Tutorial::setPresenter(std::string& newPresenter)
{
	this->presenter = newPresenter;
}

void Tutorial::setLikes(int newLikes)
{
	this->likes = newLikes;
}

void Tutorial::setMinutes(int newMinutes)
{
	this->minutes = newMinutes;
}

void Tutorial::setSeconds(int newSeconds)
{
	this->seconds = newSeconds;
}

void Tutorial::setLink(std::string& newLink)
{
	this->link = newLink;
}

std::string Tutorial::getTitle()
{
	return this->title;
}

std::string Tutorial::getPresenter()
{
	return this->presenter;
}

int Tutorial::getLikes()
{
	return this->likes;
}

int Tutorial::getMinutes()
{
	return this->minutes;
}

int Tutorial::getSeconds()
{
	return this->seconds;
}

std::string Tutorial::getLink()
{
	return this->link;
}

std::string Tutorial::toStringTutorial()
{
	std::string data = "Title: ";
	data += this->title;
	data += "; Presenter: ";
	data += this->presenter;
	data += "; Duration: ";
	data += std::to_string(this->minutes);
	data += ":";
	data += std::to_string(this->seconds);
	data += "; Likes: ";
	data += std::to_string(this->likes);
	data += "; Link: ";
	data += this->link;

	return data;

}

std::vector<std::string> tokenize(std::string stringToBeRead, char delimiter)
{
	std::vector <std::string> result;
	std::stringstream ss(stringToBeRead);
	std::string token;
	while (getline(ss, token, delimiter))
		result.push_back(token);

	return result;
}

std::istream& operator>>(std::istream& inputStream, Tutorial& tutorial)
{
	std::string line;
	getline(inputStream, line);

	std::vector<std::string> tokens = tokenize(line, ',');
	if (tokens.size() != 6)
		return inputStream;
	tutorial.title = tokens[0];
	tutorial.presenter = tokens[1];
	std::string::size_type sizeType;
	tutorial.minutes = std::stoi(tokens[2], &sizeType);
	tutorial.seconds = std::stoi(tokens[3], &sizeType);
	tutorial.likes = std::stoi(tokens[4], &sizeType);
	tutorial.link = tokens[5];

	return inputStream;
}

std::ostream& operator<<(std::ostream& outputStream, Tutorial& tutorial)
{
	//outputStream.width(30);
	outputStream << tutorial.title << ",";
	//outputStream.width(30);
	outputStream << tutorial.presenter << ",";
	//outputStream.width(30);
	outputStream << tutorial.minutes << ",";
	//outputStream.width(30);
	outputStream << tutorial.seconds << ",";
	//outputStream.width(30);
	outputStream << tutorial.likes << ",";
	//outputStream.width(30);
	outputStream << tutorial.link << std::endl;
	return outputStream;

}
