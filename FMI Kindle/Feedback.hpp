#pragma once
#pragma warning(disable:4996)

#include <iostream>
#include "List.hpp"
#include "String.hpp"

class Feedback
{
	String user;
	List<String> comments;
	int rating;

public:
	Feedback(String user) {
		this->user = user;
		rating = -1;
	}

	bool addComment(String comment) {
		comments.add(comment);
		return true;
	}

	size_t getRating() const {
		return rating;
	}

	bool setRating(size_t r) {
		if (r > 10) {
			return false;
		}

		rating = r;
		return true;
	}

	bool printComments(std::ostream& o) {
		for (size_t i = 0; i < comments.getCount(); i++)
		{
			o << user << " wrote: " << comments[i] << std::endl;
		}

		return true;
	}

	String getUser() {
		return user;
	}

	void serialize(std::ostream& o) {
		size_t userLen = user.getLength();
		size_t commentsCount = comments.getCount();

		o.write((const char*)&(userLen), sizeof(userLen));
		o.write((const char*)&user, sizeof(userLen)+1);

		o.write((const char*)&rating, sizeof(rating));

		o.write((const char*)&commentsCount, sizeof(commentsCount));
		for (size_t i = 0; i < commentsCount; i++)
		{
			size_t l = comments[i].getLength();
			o.write((const char*)&l, sizeof(l));
			o.write((const char*)comments[i].c_str(), l + 1);
		}
	}
};