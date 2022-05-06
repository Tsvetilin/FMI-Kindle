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
	Feedback(const String& user);
	Feedback() {}
	size_t getRating() const;
	String getUser() const;

	bool setRating(size_t r);
	bool addComment(const String& comment);

	bool printComments(std::ostream& o)const;
	void serialize(std::ostream& o)const;
	void deserialize(std::istream& i);

};