#pragma once

#include "Book.hpp"
#include "List.hpp"

class User
{
	String username;
	String password;

	List<const Book*> readBooks;
	List<const Book*> writtenBooks;

public:
	User(){}
	User(const String& username, const String& password);

	String getUsername()const;

	bool loginAttempt(const String& password) const;
	bool hasReadBook(const Book* book) const;
	bool isAuthor(const Book* book) const;

	bool rateBook(Book* book, size_t rate);
	bool commentBook(Book* book, const String& comment);
	bool readBook(const Book* book);
	bool writeBook(const Book* book);
	bool editBook(Book* book, size_t pageNumber, const String& content);
	bool editTitle(Book* book, const String& newTitle);
	bool addPageToBook(Book* book, const String& content);

	void serialize(std::ostream& o) const;
	void deserialize(std::istream& i, const List<Book*> books);
};
