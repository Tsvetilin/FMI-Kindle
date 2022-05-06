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
	String databaseName;

	Book* findBook(const String& title) const;
	bool readDb();
	bool saveDb() const;
	void copyFrom(const Kindle& other);
	void free();

public:
	Kindle();
	Kindle(const String& databaseName);
	Kindle(const Kindle&);
	Kindle& operator= (const Kindle&);
	~Kindle();

	bool login(const String& username, const String& password);
	bool signup(const String& username, const String& password);
	bool logout();

	bool writeBook(const String& title, const String& firstPageContent);
	bool readBook(const String& bookTitle, std::ostream& o);
	bool editBook(const String& bookTitle, const String& newTitle);
	bool editBookPage(const String& bookTitle, size_t pageNumber, const String& content);
	bool addPage(const String& bookTitle, const String& content);

	bool readBookPage(const String& bookTitle, size_t page, std::ostream& o);
	bool rateBook(const String& bookTitle, size_t rate);
	bool commentBook(const String& bookTitle, const String& comment);

	bool printBooks(std::ostream& o)const;
	bool readComments(const String& bookTitle, std::ostream& o) const;
	bool readRates(const String& bookTitle, std::ostream& o) const;
	double getRating(const String& bookTitle) const;

	bool save() const;
};