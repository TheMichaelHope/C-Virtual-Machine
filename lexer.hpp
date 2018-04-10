#ifndef LEXER_HPP
#define LEXER_HPP

#include <istream>
#include "token.hpp"

using namespace std;

TokenList tokenize(std::istream & ins);

#endif
