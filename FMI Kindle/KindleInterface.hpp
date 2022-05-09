#pragma once

#include "Kindle.hpp"

#include <iostream>

String pageInput(std::istream& inputStream);
void printKindleManual(std::ostream& outputStream);
void useKindleHandler(Kindle& kindle, std::istream& inputStream, std::ostream& outputStream);
