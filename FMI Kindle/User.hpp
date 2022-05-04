#pragma once
#pragma warning(disable:4996)

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

	User(String username, String password)
	{
		this->username = username;
		this->password = password;
	}

	bool loginAttempt(String password) const{
		return password==this->password;
	}

	bool readBook(const Book* book) {
		readBooks.add(book);
		return true;
	}

	bool writeBook(Book* book) {
		writtenBooks.add(book);
		return true;
	}

	bool hasReadBook(const Book* book) const {
		return readBooks.contains(book);
	}

	bool isAuthor(Book* book) const {
		return writtenBooks.contains(book);
	}

	bool rateBook(Book* book, size_t rate) {
		if (!hasReadBook(book) || writtenBooks.contains(book)) {
			return false;
		}

		return book->rate(this->username, rate);
	}

	bool commentBook(Book* book, String comment) {
		if (!hasReadBook(book) && !isAuthor(book)) {
			return false;
		}

		return book->comment(this->username, comment);
	}

	String getUsername()const {
		return username;
	}

	bool editBook(Book* book, size_t pageNumber, String content) {
		if (!writtenBooks.contains(book)) {
			return false;
		}

		return book->editPage(pageNumber, content);
	}

	bool editTitle(Book* book, String newTitle) {
		if (!writtenBooks.contains(book)) {
			return false;
		}

		return book->setTitle(newTitle);
	}

	bool addPageToBook(Book* book, String content) {
		if (!writtenBooks.contains(book)) {
			return false;
		}

		return book->addPage(content);
	}

	void serializeUser(std::ostream& o) {
		size_t usernameLen = username.getLength();
		size_t passwordLen = password.getLength();
		size_t countRead = readBooks.getCount();
		size_t countWritten = writtenBooks.getCount();

		o.write((const char*)&usernameLen, sizeof(usernameLen));
		o.write((const char*)username.c_str(), usernameLen+1);

		o.write((const char*)&passwordLen, sizeof(passwordLen));
		o.write((const char*)password.c_str(), passwordLen + 1);

		o.write((const char*)&countRead, sizeof(countRead));
		for (size_t i = 0; i < countRead; i++)
		{
			size_t rid = readBooks[i]->getId();
			o.write((const char*)&rid, sizeof(rid));
		}

		o.write((const char*)&countWritten, sizeof(countWritten));
		for (size_t i = 0; i < countWritten; i++)
		{
			size_t wid = writtenBooks[i]->getId();
			o.write((const char*)&wid, sizeof(wid));
		}
	}
};
