#pragma once

#include <iostream>

class String {
	char* string;
	size_t length;

	void setString(const char* const);

public:
	String() : String(nullptr) {}
	String(const char* const);
	String(const String&);

	String& operator=(const String&);
	String& operator=(const char* const);

	~String();

	size_t getLength() const;
	void concat(const String&);
	String substr(size_t, size_t);

	const char* c_str() const;

	String& operator+=(const String&);
	String operator+(const String&) const;

	bool operator== (const String&) const;
	bool operator< (const String&) const;
	bool operator> (const String&) const;
	bool operator>= (const String&) const;
	bool operator<= (const String&) const;

	friend std::ostream& operator<<(std::ostream&, const String&);
	friend std::istream& operator>>(std::istream&, String&);

	friend std::istream& getline(std::istream&, String&);

	friend void serializeString(std::ostream&, const String&);
	friend void deserializeString(std::istream&, String&);

};
