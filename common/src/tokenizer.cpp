/*!	\file	tokenizer.cpp
	\brief	Tokenizer class implementation.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han


=============================================================
Revision History
-------------------------------------------------------------

Version 2021.10.02
	C++ 20 validated

Version 2019.11.05
	C++ 17 cleanup

Version 2017.11.23
	Added Python-style power operator '**'.

Version 2014.10.29
	C++ 11 refactor.
	Converted Integer::value_type to boost::multiprecision::cpp_int
	Removed BinaryInteger

Version 2012.11.16
	Added BitAnd, BitNot, BitOr, BitXOr, BitShiftLeft, BitShiftRight
	Simplified CHECK_OP macros

Version 2012.11.15
	Replaced BadCharacter with XTokenizer, XBadCharacter, and XNumericOverflow
	Added BinaryInteger, Binary <function>

Version 2012.11.13
	C++ 11 cleanup.

Version 2010.11.09
	Switched boost::shared_ptr<> to std::shared_ptr<>.
	Added TOKEN_PTR_TYPE macro.
	Switched __int64 to long long.

Version 2009.11.25
	Alpha release.


=============================================================

Copyright Garth Santor/Trinh Han

The copyright to the computer program(s) herein
is the property of Garth Santor/Trinh Han, Canada.
The program(s) may be used and/or copied only with
the written permission of Garth Santor/Trinh Han
or in accordance with the terms and conditions
stipulated in the agreement/contract under which
the program(s) have been supplied.
=============================================================*/

#include <ee/tokenizer.hpp>
#include <ee/boolean.hpp>
#include <ee/function.hpp>
#include <ee/integer.hpp>
#include <ee/operator.hpp>
#include <ee/pseudo_operation.hpp>
#include <ee/real.hpp>
#include <ee/variable.hpp>

#include <exception>
#include <limits>
#include <sstream>
#include <stack>
#include <string>
using namespace std;

/** Default constructor loads the keyword dictionary. */
Tokenizer::Tokenizer() {
	keywords_m["abs"]     = keywords_m["Abs"]		= keywords_m["ABS"]		= make<Abs>();
	keywords_m["and"]     = keywords_m["And"]		= keywords_m["AND"]		= make<And>();
	keywords_m["arccos"]  = keywords_m["Arccos"]	= keywords_m["ARCCOS"]	= make<Arccos>();
	keywords_m["arcsin"]  = keywords_m["Arcsin"]	= keywords_m["ARCSIN"]	= make<Arcsin>();
	keywords_m["arctan"]  = keywords_m["Arctan"]	= keywords_m["ARCTAN"]	= make<Arctan>();
	keywords_m["arctan2"] = keywords_m["Arctan2"]	= keywords_m["ARCTAN2"]	= make<Arctan2>();
	keywords_m["ceil"]    = keywords_m["Ceil"]	= keywords_m["CEIL"]		= make<Ceil>();
	keywords_m["cos"]     = keywords_m["Cos"]		= keywords_m["COS"]		= make<Cos>();
	keywords_m["e"]       = keywords_m["E"]								= make<E>();
	keywords_m["exp"]     = keywords_m["Exp"]		= keywords_m["EXP"]		= make<Exp>();
	keywords_m["false"]   = keywords_m["False"]	= keywords_m["FALSE"]	= make<False>();
	keywords_m["floor"]   = keywords_m["Floor"]	= keywords_m["FLOOR"]	= make<Floor>();
	keywords_m["lb"]      = keywords_m["Lb"]		= keywords_m["LB"]		= make<Lb>();
	keywords_m["ln"]      = keywords_m["Ln"]		= keywords_m["LN"]		= make<Ln>();
	keywords_m["log"]     = keywords_m["Log"]		= keywords_m["LOG"]		= make<Log>();
	keywords_m["max"]     = keywords_m["Max"]		= keywords_m["MAX"]		= make<Max>();
	keywords_m["min"]     = keywords_m["Min"]		= keywords_m["MIN"]		= make<Min>();
	keywords_m["mod"]     = keywords_m["Mod"]		= keywords_m["MOD"]		= make<Modulus>();
	keywords_m["nand"]    = keywords_m["Nand"]	= keywords_m["NAND"]		= make<Nand>();
	keywords_m["nor"]     = keywords_m["Nor"]		= keywords_m["NOR"]		= make<Nor>();
	keywords_m["not"]     = keywords_m["Not"]		= keywords_m["NOT"]		= make<Not>();
	keywords_m["or"]      = keywords_m["Or"]		= keywords_m["OR"]		= make<Or>();
	keywords_m["pi"]      = keywords_m["Pi"]		= keywords_m["PI"]		= make<Pi>();
	keywords_m["pow"]     = keywords_m["Pow"]		= keywords_m["POW"]		= make<Pow>();
	keywords_m["result"]  = keywords_m["Result"]	= keywords_m["RESULT"]	= make<Result>();
	keywords_m["sin"]     = keywords_m["Sin"]		= keywords_m["SIN"]		= make<Sin>();
	keywords_m["sqrt"]    = keywords_m["Sqrt"]	= keywords_m["SQRT"]		= make<Sqrt>();
	keywords_m["tan"]     = keywords_m["Tan"]		= keywords_m["TAN"]		= make<Tan>();
	keywords_m["true"]    = keywords_m["True"]	= keywords_m["TRUE"]		= make<True>();
	keywords_m["xnor"]    = keywords_m["Xnor"]	= keywords_m["XNOR"]		= make<Xnor>();
	keywords_m["xor"]     = keywords_m["Xor"]		= keywords_m["XOR"]		= make<Xor>();
}




/** Get an identifier from the expression.
	Assumes that the currentChar is pointing to a alphabetic.
	*/
Token::pointer_type Tokenizer::_get_identifier(Tokenizer::string_type::const_iterator& currentChar, Tokenizer::string_type const& expression) {
	// accumulate identifier
	string_type ident;
	do
		ident += *currentChar++;
	while (currentChar != end(expression) && isalnum(*currentChar));

	// check for predefined identifier
	dictionary_type::iterator iter = keywords_m.find(ident);
	if (iter != end(keywords_m))
		return iter->second;

	// check for variable
	iter = variables_m.find(ident);
	if (iter != variables_m.end())
		return iter->second;

	// add a variable
	Token::pointer_type result = make<Variable>();
	variables_m[ident] = result;
	return result;
}




/** Get a number token from the expression.
	@return One of BinaryInteger, Integer, or Real.
	@param currentChar [in,out] an iterator to the current character.  Assumes that the currentChar is pointing to a digit.
	@param expression [in] the expression being scanned.
*/
Token::pointer_type Tokenizer::_get_number(Tokenizer::string_type::const_iterator& currentChar, Tokenizer::string_type const& expression) {
	assert(isdigit(*currentChar) && "currentChar must pointer to a digit");

	// Either Integer or Real
	string digits(1, *currentChar++);

	while (currentChar != end(expression) && isdigit(*currentChar))
		digits += *currentChar++;

	if (currentChar == end(expression) || (!isdigit(*currentChar) && *currentChar != '.'))
		return make<Integer>(Integer::value_type(digits));

	// a real number
	digits += *currentChar++;
	while (currentChar != end(expression) && isdigit(*currentChar))
		digits += *currentChar++;


	return make<Real>(Real::value_type(digits));
}



/** Tokenize the expression.
	@return a TokenList containing the tokens from 'expression'.
	@param expression [in] The expression to tokenize.
	@note Tokenizer dictionary may be updated if expression contains variables.
	@note Will throws 'BadCharacter' if the expression contains an un-tokenizable character.
	*/
TokenList Tokenizer::tokenize(string_type const& expression) {
	TokenList tokenizedExpression;
	auto currentChar = expression.cbegin();

	for(;;)
	{
		// strip whitespace
		while (currentChar != end(expression) && isspace(*currentChar))
			++currentChar;

		// check of end of expression
		if (currentChar == end(expression)) break;

		// check for a number
		if (isdigit(*currentChar)) {
			tokenizedExpression.push_back(_get_number(currentChar, expression));
			continue;
		}

		// check for 2-character operators
#define CHECK_2OP( symbol1, symbol2, token )\
		if( *currentChar == symbol1 ) {\
			auto nextChar = next(currentChar);\
			if( nextChar != end(expression) && *nextChar == symbol2 ) {\
				currentChar = next(nextChar);\
				tokenizedExpression.push_back( make<token>() );\
				continue;\
			}\
		}
		CHECK_2OP('<', '=', LessEqual)
		CHECK_2OP('>', '=', GreaterEqual)
		CHECK_2OP('=', '=', Equality)
		CHECK_2OP('!', '=', Inequality)
		CHECK_2OP('*', '*', Power)
#undef CHECK_2OP

			// check for 1-character operators
#define CHECK_OP(symbol, token)\
		if( *currentChar == symbol ) {\
			++currentChar;\
			tokenizedExpression.push_back( make<token>() );\
			continue;\
		}
		CHECK_OP('*', Multiplication)
		CHECK_OP('/', Division)
		CHECK_OP('%', Modulus)
		CHECK_OP('(', LeftParenthesis)
		CHECK_OP(')', RightParenthesis)
		CHECK_OP(',', ArgumentSeparator)
		CHECK_OP('<', Less)
		CHECK_OP('>', Greater)
		CHECK_OP('!', Factorial)
		CHECK_OP('=', Assignment)
#undef CHECK_OP


		// check for multi-purpose operators
		if (*currentChar == '+') {
			++currentChar;
			if (!tokenizedExpression.empty() &&
				(is<RightParenthesis>(tokenizedExpression.back()) ||
					is<Operand>(tokenizedExpression.back()) ||
					is<PostfixOperator>(tokenizedExpression.back())))
				tokenizedExpression.push_back(make<Addition>());
			else
				tokenizedExpression.push_back(make<Identity>());
			continue;
		}
		if (*currentChar == '-') {
			++currentChar;
			if (!tokenizedExpression.empty() &&
				(is<RightParenthesis>(tokenizedExpression.back()) ||
					is<Operand>(tokenizedExpression.back()) ||
					is<PostfixOperator>(tokenizedExpression.back())))
				tokenizedExpression.push_back(make<Subtraction>());
			else
				tokenizedExpression.push_back(make<Negation>());
			continue;
		}


		// Identifiers
		if (isalpha(*currentChar)) {
			tokenizedExpression.push_back(_get_identifier(currentChar, expression));
			continue;
		}

		// not a recognized token
		throw XBadCharacter(expression, currentChar - begin(expression));
	}

	return tokenizedExpression;
}
