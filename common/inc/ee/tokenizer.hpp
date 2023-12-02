#pragma once
/*!	\file	tokenizer.hpp
	\brief	Tokenizer class declaration for Expression Evaulator.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

============================================================ =
Revision History
------------------------------------------------------------ -

Version 2021.10.02
	C++ 20 validated

Version 2019.11.05
	C++ 17 cleanup

Version 2017.11.23
	Added Python - style power operator '**'.

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

Copyright Garth Santor / Trinh Han

The copyright to the computer program(s) herein
is the property of Garth Santor / Trinh Han, Canada.
The program(s) may be used and /or copied only with
the written permission of Garth Santor / Trinh Han
or in accordance with the terms and conditions
stipulated in the agreement / contract under which
the program(s) have been supplied.
============================================================= */

#include <ee/token.hpp>
#include <map>
#include <string>


/*! Tokenizer class is used to create lists of tokens from expression strings.
	It maintains a dictionary of variable tokens introduced by the expression strings.
	*/
class Tokenizer {
	// Block copying
	Tokenizer(Tokenizer const&) = delete;
	Tokenizer& operator = (Tokenizer const&) = delete;

// TYPES
public:
	using string_type = Token::string_type;

	class XTokenizer : public std::exception {
		string_type	expression_m;
		std::size_t	location_m;
	public:
		XTokenizer(string_type const& expression, std::size_t location, char const* msg)
			: std::exception(msg)
			, expression_m(expression)
			, location_m(location)
		{ }

		/*! Gets the expression string containing the bad character. */
		[[nodiscard]] constexpr string_type expression() const { return expression_m; }

		/*! Gets the location of the bad character in the expression string. */
		[[nodiscard]] constexpr std::size_t	location() const { return location_m; }
	};

	/** Bad character exception class. */
	struct XBadCharacter : public XTokenizer {
	XBadCharacter(string_type const& expression, std::size_t location)
		: XTokenizer(expression, location, "Tokenizer::Bad character in expression.") { }
	};

	/**	Numeric overflow exception class. */
	struct XNumericOverflow : public XTokenizer {
		XNumericOverflow( string_type const& expression, size_t location )
			: XTokenizer( expression, location, "Tokenizer::Too many digits in number." ) { }
	};

private:
	using dictionary_type = std::map<string_type, Token::pointer_type>;

// ATTRIBUTES
private:
	dictionary_type	keywords_m;
	dictionary_type variables_m;

// OPERATIONS
public:
	Tokenizer();
	TokenList tokenize(string_type const& expression);

private:
	[[nodiscard]] Token::pointer_type _get_identifier(Tokenizer::string_type::const_iterator& currentChar, Tokenizer::string_type const& expression);
	[[nodiscard]] Token::pointer_type _get_number(Tokenizer::string_type::const_iterator& currentChar, Tokenizer::string_type const& expression);
};

