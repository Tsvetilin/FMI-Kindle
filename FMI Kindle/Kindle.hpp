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

	Book* findBook(String title) {
		for (size_t i = 0; i < books.getCount(); i++)
		{
			if (books[i]->getTitle()== title) {
				return books[i];
			}
		}

		return nullptr;
	}

public:
	Kindle() :currentLoggedUser(nullptr), uidGeneration(0) {
		readDb();
	}

	void readDb() {

	}
	void saveDb() {

	}

	~Kindle() {

	}

	bool login(String username, String password) {
		for (size_t i = 0; i < users.getCount(); i++)
		{
			if (username==users[i]->getUsername()) {
				return (users[i]->loginAttempt(password)) && (currentLoggedUser=users[i]);
			}
		}

		return false;
	}

	bool signup(String username, String password) {
		for (size_t i = 0; i < users.getCount(); i++)
		{
			if (username== users[i]->getUsername()) {
				return false;
			}
		}

		User* user = new User(username, password);
		users.add(user);
		return true;
	}

	bool logout() {
		saveDb();
		currentLoggedUser = nullptr;
		return true;
	}

	bool writeBook(String title, String firstPageContent) {
		if (currentLoggedUser == nullptr) {
			return false;
		}

		for (size_t i = 0; i < books.getCount(); i++)
		{
			if (books[i]->getAuthor()== currentLoggedUser->getUsername() && 
				books[i]->getTitle()== title) {
				return false;
			}
		}

		Book* book = new Book(currentLoggedUser->getUsername(), title, firstPageContent,uidGeneration);
		books.add(book);
		return currentLoggedUser->writeBook(book);
	}

	bool readBook(String bookTitle, std::ostream& o) {
		return readBookPage(bookTitle, 1, o);
	}

	bool readBookPage(String bookTitle, size_t page, std::ostream& o) {
		if (currentLoggedUser == nullptr) {
			return false;
		}

		Book* book = findBook(bookTitle);
		if (book == nullptr) {
			return false;
		}

		currentLoggedUser->readBook(book);

		if (!o.good()) {
			return false;
		}

		o << book->getPage(page-1)->getContent();
		return o.good();
	}

	bool rateBook(String bookTitle, size_t rate) {
		if (currentLoggedUser == nullptr) {
			return false;
		}

		Book* book = findBook(bookTitle);
		if (book == nullptr) {
			return false;
		}

		return currentLoggedUser->rateBook(book, rate);	
	}

	bool commentBook(String bookTitle, String comment) {
		if (currentLoggedUser == nullptr) {
			return false;
		}

		Book* book = findBook(bookTitle);
		if (book == nullptr) {
			return false;
		}

		return currentLoggedUser->commentBook(book, comment);
	}

	bool readComments(String bookTitle, std::ostream& o) {
		if (currentLoggedUser == nullptr) {
			return false;
		}

		Book* book = findBook(bookTitle);
		if (book == nullptr) {
			return false;
		}

		if (!o.good()) {
			return false;
		}

		return book->printComments(o);
	}

	bool readRates(String bookTitle, std::ostream& o) {
		if (currentLoggedUser == nullptr) {
			return false;
		}

		Book* book = findBook(bookTitle);
		if (book == nullptr) {
			return false;
		}

		if (!o.good()) {
			return false;
		}

		return book->printRates(o);
	}

	int getRating(String bookTitle) {
		if (currentLoggedUser == nullptr) {
			return -2;
		}

		Book* book = findBook(bookTitle);
		if (book == nullptr) {
			return -2;
		}

		return book->getRating();
	}

	bool editBook(String bookTitle, String newTitle) {
		if (currentLoggedUser == nullptr) {
			return false;
		}

		Book* book = findBook(bookTitle);
		if (book == nullptr) {
			return false;
		}

		return currentLoggedUser->editTitle(book, newTitle);
	}

	bool editBookPage(String bookTitle, size_t pageNumber, String content) {
		if (currentLoggedUser == nullptr) {
			return false;
		}

		Book* book = findBook(bookTitle);
		if (book == nullptr) {
			return false;
		}

		return currentLoggedUser->editBook(book, pageNumber, content);
	}

	bool addPage(String bookTitle, String content) {
		if (currentLoggedUser == nullptr) {
			return false;
		}

		Book* book = findBook(bookTitle);
		if (book == nullptr) {
			return false;
		}

		return currentLoggedUser->addPageToBook(book, content);
	}

	bool save() {

	}

	void printBooks(std::ostream& o) {
		for (size_t i = 0; i < books.getCount(); i++)
		{
			o << (i + 1) << ". " << books[i]->getTitle() << " by " << books[i]->getAuthor() << std::endl;
		}
	}

};