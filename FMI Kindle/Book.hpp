#pragma once
#pragma warning(disable:4996)

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

	void setAuthorName(String authorName) {
		this->authorName = authorName;
	}

public:
	Book(String authorName, String title, String firstPageContent, size_t uid) {
		addPage(firstPageContent);
		setTitle(title);
		setAuthorName(authorName);
		id = uid;
	}

	String getAuthor() const{
		return authorName;
	}

	String getTitle()const {
		return title;
	}

	double getRating() const {
		if (feedbacks.getCount() == 0) {
			return -1;
		}

		double ratingSum = 0;
		size_t ratingCount = 0;
		for (size_t i = 0; i < feedbacks.getCount(); i++)
		{
			int currentRating = feedbacks[i]->getRating();
			if (currentRating > 0) {
				++ratingCount;
				ratingSum += currentRating;
			}
		}

		if (ratingCount == 0) {
			return -1;
		}

		return ratingSum / ratingCount;
	}

	bool setTitle(String title) {
		this->title = title;
		return true;
	}

	Book(){}

	const size_t getId() const{
		return id;
	}


	bool rate(String user,size_t rate) {
		for (size_t i = 0; i < feedbacks.getCount(); i++)
		{
			if (feedbacks[i]->getUser()==user) {
				return feedbacks[i]->setRating(rate);
			}
		}

		Feedback* f = new Feedback(user);
		feedbacks.add(f);
		return f->setRating(rate);
	}

	bool comment(String user, String comment) {
		for (size_t i = 0; i < feedbacks.getCount(); i++)
		{
			if (feedbacks[i]->getUser()== user) {
				return feedbacks[i]->addComment(comment);
			}
		}

		Feedback* f = new Feedback(user);
		feedbacks.add(f);
		return f->addComment(comment);
	}

	const Page* const getPage(size_t pageNo) const {
		return pages[pageNo];
	}

	bool printComments(std::ostream& o) {
		for (size_t i = 0; i < feedbacks.getCount(); i++)
		{
			feedbacks[i]->printComments(o);
		}

		return o.good();
	}

	bool printRates(std::ostream& o) {
		for (size_t i = 0; i < feedbacks.getCount(); i++)
		{
			int r = feedbacks[i]->getRating();
			if (r!= -1) {
				o << feedbacks[i]->getUser() << " rated " << r << " stars!";
			}
		}

		return o.good();
	}

	bool editPage(size_t pageNumber, String content) {
		if (pageNumber > pages.getCount()) {
			return false;
		}

		return pages[pageNumber - 1]->setContent(content);
	}

	bool addPage(String content) {
		Page* page = new Page(content, pages.getCount()+1);
		pages.add(page);
		
		return true;
	}

	void serialize(std::ostream& o) {
		size_t authorNameLen = authorName.getLength();
		size_t titleLen = title.getLength();
		size_t pagesCount = pages.getCount();
		size_t feedbacksCount = feedbacks.getCount();

		o.write((const char*)&id, sizeof(id));
		o.write((const char*)&rating, sizeof(rating));

		o.write((const char*)&pagesCount, sizeof(pagesCount));
		for (size_t i = 0; i < pagesCount; i++)
		{
			pages[i]->serialize(o);
		}

		o.write((const char*)&authorNameLen, sizeof(authorNameLen));
		o.write((const char*)authorName.c_str(), authorNameLen + 1);

		o.write((const char*)&titleLen, sizeof(titleLen));
		o.write((const char*)title.c_str(), titleLen + 1);

		o.write((const char*)&feedbacksCount, sizeof(feedbacksCount));
		for (size_t i = 0; i < feedbacksCount; i++)
		{
			feedbacks[i]->serialize(o);
		}
	}
};