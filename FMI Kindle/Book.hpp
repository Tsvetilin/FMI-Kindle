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

	void setAuthorName(String authorName);

public:
	Book();
	Book(String authorName, String title, String firstPageContent, size_t uid);

	String getAuthor() const;
	String getTitle()const;
	double getRating() const;
	const size_t getId() const;
	const Page* const getPage(size_t pageNo) const;

	bool setTitle(String title);
	bool rate(String user, size_t rate);
	bool comment(String user, String comment);

	bool editPage(size_t pageNumber, String content);
	bool addPage(String content);

	bool printComments(std::ostream& o) const;
	bool printRates(std::ostream& o) const;

	void serialize(std::ostream& o) const;
};