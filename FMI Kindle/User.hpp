#pragma once

#include "Book.hpp"
#include "List.hpp"

class User
{
	String username;
	String password;

	List<const Book*> readBooks;
	List<Book*> writtenBooks;

public:
	User(){}
	User(String username, String password);

	String getUsername()const;

	bool loginAttempt(String password) const;
	bool hasReadBook(const Book* book) const;
	bool isAuthor(Book* book) const;

	bool rateBook(Book* book, size_t rate);
	bool commentBook(Book* book, String comment);
	bool readBook(const Book* book);
	bool writeBook(Book* book);
	bool editBook(Book* book, size_t pageNumber, String content);
	bool editTitle(Book* book, String newTitle);
	bool addPageToBook(Book* book, String content);

	void serializeUser(std::ostream& o) const;
};
