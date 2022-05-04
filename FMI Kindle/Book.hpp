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
	Book(String authorName, String title, String firstPageContent, size_t uid);
	String getAuthor() const;
	String getTitle()const;
	double getRating() const;
	bool setTitle(String title);
	Book();
	const size_t getId() const;
	bool rate(String user, size_t rate);
	bool comment(String user, String comment);
	const Page* const getPage(size_t pageNo) const;
	bool printComments(std::ostream& o);
	bool printRates(std::ostream& o);
	bool editPage(size_t pageNumber, String content);
	bool addPage(String content);
	void serialize(std::ostream& o);
};