#pragma once

#include <iostream>

#include "String.hpp"

template<typename T>
void serializePrimitive(std::ostream& o, const T& data) {
	o.write((const char*)&data, sizeof(data));
}

template<typename T>
void deserializePrimitive(std::istream& i, const T& data) {
	i.read((char*)&data, sizeof(data));
}

bool isNumber(char c);

String matchCmd(const String& input);
String skipCmd(const String& input);
String getQuotes(const String& input); 
size_t parseToUInt(const String& input);
String getLastArgument(const String& input);