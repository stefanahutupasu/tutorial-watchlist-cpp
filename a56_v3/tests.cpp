#include "tests.h"
#include <iostream>

//using namespace std;
/*
void testDomain()
{
	//std::cout << "Domain tests have started to run..." << std::endl;
	
	std::string title = "C++ Tutorial 2020";
	std::string presenter = "Derek Banas";
	std::string link = "https://www.youtube.com/watch?v=6y0bp-mnYU0&ab_channel=DerekBanas";
	Tutorial tutorial = Tutorial(title, presenter, 22, 51, 4500, link);
	//std::cout << "Domain tests have passed first stage..." << std::endl;

	assert(tutorial.getLikes() == 4500);
	assert(tutorial.getMinutes() == 22);
	assert(tutorial.getSeconds() == 51);
	assert(tutorial.getTitle() == title);
	assert(tutorial.getPresenter() == presenter);
	assert(tutorial.getLink() == link);
	//std::cout << "Domain tests have passed second stage..." << std::endl;

	Tutorial empty_tutorial = Tutorial();
	assert(empty_tutorial.getLikes() == 0);
	assert(empty_tutorial.getMinutes() == 0);
	assert(empty_tutorial.getSeconds() == 0);
	assert(empty_tutorial.getTitle() == "");
	assert(empty_tutorial.getPresenter() == "");
	assert(empty_tutorial.getLink() == "");
	//std::cout << "Domain tests have passed third stage..." << std::endl;

	Tutorial copy_of_empty_tutorial = Tutorial(empty_tutorial);
	assert(copy_of_empty_tutorial.getLikes() == 0);
	assert(copy_of_empty_tutorial.getMinutes() == 0);
	assert(copy_of_empty_tutorial.getSeconds() == 0);
	assert(copy_of_empty_tutorial.getTitle() == "");
	assert(copy_of_empty_tutorial.getPresenter() == "");
	assert(copy_of_empty_tutorial.getLink() == "");
	assert(copy_of_empty_tutorial.getNumberOfInstances() == 3);
	assert(empty_tutorial.getNumberOfInstances() == 3);
	assert(tutorial.getNumberOfInstances() == 3);
	copy_of_empty_tutorial.~Tutorial();
	empty_tutorial.~Tutorial();
	assert(tutorial.getNumberOfInstances() == 1);
	//std::cout << "Domain tests have passed fourth stage..." << std::endl;

	Tutorial copy_of_tutorial = Tutorial(tutorial);
	assert(copy_of_tutorial == tutorial);
	Tutorial second_copy_of_tutorial = Tutorial();
	second_copy_of_tutorial = tutorial;
	assert(second_copy_of_tutorial == tutorial);
	assert(second_copy_of_tutorial == copy_of_tutorial);
	//std::cout << "Domain tests have passed fifth stage..." << std::endl;


	copy_of_tutorial.~Tutorial();
	second_copy_of_tutorial.~Tutorial();
	
	assert(tutorial.getNumberOfInstances() == 1);
	Tutorial new_copy_of_tutorial = Tutorial(tutorial);
	std::string newTitle = "What Are Pointers? (C++)";
	std::string newPresenter = "javidx9";
	std::string newLink = "https://www.youtube.com/watch?v=iChalAKXffs&ab_channel=javidx9";
	tutorial.setTitle(newTitle);
	tutorial.setPresenter(newPresenter);
	tutorial.setLink(newLink);
	tutorial.setLikes(13000);
	tutorial.setMinutes(41);
	tutorial.setSeconds(54);
	assert(tutorial.getLikes() == 13000);
	assert(tutorial.getMinutes() == 41);
	assert(tutorial.getSeconds() == 54);
	assert(tutorial.getTitle() == newTitle);
	assert(tutorial.getPresenter() == newPresenter);
	assert(tutorial.getLink() == newLink);
	assert(!(tutorial == new_copy_of_tutorial));
	std::string tutorialString = tutorial.toStringTutorial();
	std::string expectedString = "Title: What Are Pointers? (C++); Presenter: javidx9; Duration: 41:54; Likes: 13000; Link: https://www.youtube.com/watch?v=iChalAKXffs&ab_channel=javidx9";
	assert(tutorialString == expectedString);

	std::cout << "Domain tests have passed last stage..." << std::endl;
	//std::cout << tutorialString << std::endl;


}

void testDynamicVector()
{
	DynamicVector<int> vInt;
	assert(vInt.getSize() == 0);
	vInt.addElement(1);
	vInt.addElement(2);
	DynamicVector<int> vInt_copy = DynamicVector<int>(vInt);
	assert(vInt_copy.getSize() == 2);

	DynamicVector<int> vInt2;
	vInt2.addElement(1);
	vInt2.addElement(2);
	vInt2.addElement(3);
	vInt2.addElement(4);
	vInt2.addElement(5);
	assert(vInt2.getSize() == 5);
	vInt2.addElement(6);
	vInt2.addElement(7);
	vInt2.addElement(8);
	vInt2.addElement(9);
	vInt2.addElement(10);
	vInt2.addElement(11);
	vInt2.addElement(12);
	vInt2.addElement(13);
	assert(vInt2.getSize() == 13);

	vInt_copy = vInt2;
	assert(vInt_copy.getSize() == 13);
	assert(vInt2[7] == 8);
	int elemToSearch = 14;
	assert(vInt2.searchElement(elemToSearch) == -1);
	assert(vInt2.searchElement(4) == 3);
	vInt2.deleteElement(13);
	//vInt2.deleteElement(13);
	assert(vInt2.getSize() == 12);
	assert(vInt2.searchElement(13) == -1);
	vInt2.deleteElement(5);
	//std::cout << vInt2.searchElement(13) << '\n';
	std::cout << "Dynamic vector tests have passed last stage..." << std::endl;

}

void testRepository()
{
	std::string title = "What Are Pointers? (C++)";
	std::string presenter = "javidx";
	std::string link = "https://www.youtube.com/watch?v=iChalAKXffs&ab_channel=javidx9";
	Tutorial tutorial = Tutorial(title, presenter, 41, 54, 13000, link);

	TutorialRepository repo = TutorialRepository();
	repo.addTutorialAsAdmin(tutorial);
	assert(repo.getTutorialByTitle(title) == tutorial);
	repo.allPresenterList();
	assert(repo.getCurrentTutorial() == tutorial);
	
	repo.nextTutorial();
	assert(repo.getCurrentTutorial() == tutorial);
	
	repo.addTutorialToWatchList(title);
	//assert(repo.searchTutorialInWatchList(tutorial) == 0);
	repo.deleteTutorial(title);
	assert(repo.searchTutorialInAdminList(tutorial) == -1);
	repo.addTutorialAsAdmin(tutorial);
	repo.updateTutorial(title, presenter, 43, 54, 13100, link);
	Tutorial new_tutorial = repo.getTutorialByTitle(title);
	assert(new_tutorial.getLikes() == 13100);
	assert(repo.searchTutorialInAdminList(new_tutorial) == 0);
	DynamicVector<Tutorial> admin_v = repo.getAllTutorials();
	DynamicVector<Tutorial> user_v = repo.getWatchList();
	assert(admin_v.getSize() == 1);
	assert(user_v.getSize() == 1);
	
	std::cout << "Repository tests have passed last stage..." << std::endl;


}

void testService()
{
	Service s = Service();
	std::string title = "What Are Pointers? (C++)";
	std::string presenter = "javidx";
	std::string link = "https://www.youtube.com/watch?v=iChalAKXffs&ab_channel=javidx9";
	Tutorial tutorial = Tutorial(title, presenter, 41, 54, 13000, link);
	s.addTutorialAsAdmin(tutorial);
	s.allPresenterList();
	assert(s.getCurrentTutorial() == tutorial);
	s.updateTutorial(title, presenter, 43, 54, 13100, link);
	Tutorial new_tutorial = s.getCurrentTutorial();
	assert(s.getCurrentTutorial() == new_tutorial);
	s.deleteTutorial(title);
	DynamicVector<Tutorial> v = s.getAllTutorials();
	assert(v.getSize() == 0);
	v = s.getWatchList();
	assert(v.getSize() == 0);
	s.addTutorialAsAdmin(tutorial);
	s.addTutorialAsAdmin(new_tutorial);
	assert(s.getCurrentTutorial() == tutorial);
	s.nextTutorial();
	assert(s.getCurrentTutorial() == new_tutorial);
	s.addTutorialToWatchList(title);
	v = s.getWatchList();
	assert(v.getSize() == 1);
	s.deleteTutorialWatchList(title);
	v = s.getWatchList();
	assert(v.getSize() == 0);
	s.addTutorialToWatchList(title);
	assert(s.tutorialInWatchList(title));
	assert(s.tutorialExistsTitle(title));
	s.resetPresenterList(presenter);
	assert(s.getCurrentTutorial() == tutorial);
	s.deleteTutorial(title);
	assert(!s.tutorialExistsTitle(title));
	s.addTutorialAsAdmin(tutorial);
	assert(s.tutorialExistsOb(tutorial));
	s.addTutorialToWatchList(title);
	s.likeTutorialWatchList(title);
	v = s.getWatchList();
	assert(v.getSize() == 0);


	std::cout << "Service tests have passed last stage..." << std::endl;



}



void runTests()
{
	testDomain();
	testDynamicVector();
	testRepository();
	testService();
}
*/

void tests()
{
	Service service = Service();
	service.loadTutorialRepo("t.txt");
	assert(service.getAllTutorials().size() == 10);
	service.setUserListType("t.csv", "csv");
	service.setUserListType("t.html", "html");
	std::string presenter = "Caleb Curry";
	std::vector<Tutorial> filteredTutorials = service.filterTutorialsByPresenter(presenter);
	assert(filteredTutorials.size() == 4);
	assert(service.currentTutorialPosition == 0);
	TXTRepository copy = TXTRepository();
	copy.setList(filteredTutorials);
	Service secondService = Service(&copy);
	std::string title = "aa";
	presenter = "b";
	std::string link = "c";
	Tutorial newTut = Tutorial(title, presenter, 1, 1, 1, link);
	service.addTutorial(newTut);
	assert(service.getAllTutorials().size() == 11);
	Tutorial newTut2 = Tutorial(title, presenter, 1, 1, 2, link);
	service.updateTutorial(newTut2);
	filteredTutorials = service.filterTutorialsByPresenter(presenter);
	assert(filteredTutorials[1] == newTut2);
	service.deleteTutorial(title);
	filteredTutorials = service.filterTutorialsByPresenter(presenter);
	assert(filteredTutorials.size()==1);
	service.saveTutorial();
	assert(service.getWatchList().size() == 1);
	title = "a";
	service.deleteTutorialWatchlist(title);
	assert(service.getWatchList().size() == 0);
	service.saveTutorial();
	assert(service.getWatchList().size() == 1);
	service.deleteTutorialWatchlistLike(title);
	filteredTutorials = service.filterTutorialsByPresenter(presenter);
	newTut2 = filteredTutorials[0];
	link = "link";
	Tutorial newTut3 = Tutorial(title, presenter, 1, 1, 2, link);
	assert(newTut2 == newTut3);
	presenter = "Caleb Curry";
	service.nextTutorial();
	filteredTutorials = service.filterTutorialsByPresenter(presenter);
	service.nextTutorial();
	service.saveTutorial();
	title = "C++ Concepts Explained";
	service.deleteTutorialWatchlist(title);
	assert(service.getWatchList().size() == 0);
	presenter = "";
	service.nextTutorial();
	filteredTutorials = service.filterTutorialsByPresenter(presenter);
	assert(filteredTutorials.size() == 10);


	
}

void runTests()
{
	tests();
}
