#pragma once

#include <iostream>
#include "List.hpp"
#include "String.hpp"

class Feedback
{
	String user;
	List<String> comments;
	int rating;

public:
	Feedback(String user);
	bool addComment(String comment);
	size_t getRating() const;
	String getUser();
	bool setRating(size_t r);
	bool printComments(std::ostream& o);
	void serialize(std::ostream& o);
};