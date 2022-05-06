#include "Helper.hpp"
#include "String.hpp"

String matchCmd(const String& input) {
	size_t startIndex = 0;

	while (input[startIndex] == ' ') {
		++startIndex;
	}

	size_t wordLength = 0;
	while (input[startIndex + wordLength] != ' ' && input[startIndex + wordLength] != '\0') {
		++wordLength;
	}

	return input.substr(startIndex, wordLength);
}

String skipCmd(const String& input) {

	size_t startIndex = 0;
	size_t wordLength = 0;
	while (input[startIndex] == ' ') {
		if (input[startIndex] == '\0') {
			return String();
		}
		++startIndex;
	}

	while (input[startIndex + wordLength] != ' ' && input[startIndex + wordLength] != '\0') {
		++wordLength;
	}

	return input.substr(startIndex + wordLength, input.getLength() - startIndex - wordLength);
}

String getQuotes(const String& input) {

	size_t startIndex = 0;
	size_t wordLength = 0;

	while (input[startIndex] != '"') {
		if (input[startIndex] == '\0') {
			return String();
		}
		++startIndex;
	}

	while (input[startIndex + wordLength] != '"' && input[startIndex + wordLength] != '\0') {
		++wordLength;
	}

	return input.substr(startIndex, wordLength);
}

size_t parseToUInt(const String& input) {
	size_t index = 0;
	size_t result = 0;

	while (input[index] == ' ') {
		if (input[index] == '\0') {
			return 0;
		}
		++index;
	}

	while (isNumber(input[index])) {
		result += input[index] - '0';
		++index;
	}

	if (input[index] != ' ' && input[index] != '\0') {
		return 0;
	}

	return result;
}

String getLastArgument(const String& input) {
	size_t index = input.getLength() - 1;

	while (input[index] == ' ' && index>=0) {
		--index;
	}
	
	while (input[index] != ' ' && index>=0) {
		--index;
	}

	return input.substr(index, input.getLength() - index);
}


bool isNumber(char c) {
	return c >= '0' && c <= '9';
}