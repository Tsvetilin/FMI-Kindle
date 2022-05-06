#pragma once

#include "Page.hpp"
#include "Feedback.hpp"
#include "List.hpp"
#include "String.hpp"

#include <iostream>

class Book
{
	size_t id;
	String authorName;
	String title;
	List<Feedback*> feedbacks;
	List<Page*> pages;
	double rating;

	void copyFrom(const Book& other);
	void free();

public:
	Book();
	Book(const String& authorName, const String& title, const String& firstPageContent, size_t uid);
	Book(const Book& other);
	Book& operator= (const Book& other);
	~Book();

	String getAuthor() const;
	String getTitle()const;
	double getRating() const;
	const size_t getId() const;
	const Page* const getPage(size_t pageNo) const;

	bool setTitle(const String& title);
	bool rate(const String& user, size_t rate);
	bool comment(const String& user, const String& comment);

	bool editPage(size_t pageNumber, const String& content);
	bool addPage(const String& content);

	bool printComments(std::ostream& o) const;
	bool printRates(std::ostream& o) const;

	void serialize(std::ostream& o) const;
	void deserialize(std::istream& i);
};


