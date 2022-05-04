#pragma once

#include <iostream>

#include "String.hpp"

class Page
{
	String content;
	size_t number;

public:
	Page(String content, size_t number);

	String getContent() const;

	bool setContent(String content);

	void serialize(std::ostream& o)const;
};
