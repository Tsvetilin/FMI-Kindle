#pragma once
#include <iostream>
#include "String.hpp"

class Page
{
	String content;
	size_t number;

public:
	Page();
	Page(const String& content, size_t number);

	String getContent() const;

	bool setContent(const String& content);

	void serialize(std::ostream& o)const;
	void deserialize(std::istream& i);
};
