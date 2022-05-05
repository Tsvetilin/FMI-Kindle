#pragma once

#include "User.hpp"
#include "Book.hpp"
#include "List.hpp"

#include <iostream>

class Kindle
{
	List<User*> users;
	List<Book*> books;

	User* currentLoggedUser;
	size_t uidGeneration;

	Book* findBook(String title);
	bool readDb();
	bool saveDb();

public:
	Kindle();
	
	~Kindle();
	bool login(String username, String password);
	bool signup(String username, String password);
	bool logout();
	bool writeBook(String title, String firstPageContent);
	bool readBook(String bookTitle, std::ostream& o);
	bool readBookPage(String bookTitle, size_t page, std::ostream& o);
	bool rateBook(String bookTitle, size_t rate);
	bool commentBook(String bookTitle, String comment);
	bool readComments(String bookTitle, std::ostream& o);
	bool readRates(String bookTitle, std::ostream& o);
	double getRating(String bookTitle);
	bool editBook(String bookTitle, String newTitle);
	bool editBookPage(String bookTitle, size_t pageNumber, String content);
	bool addPage(String bookTitle, String content);
	bool save();
	void printBooks(std::ostream& o);

};