#pragma once
/*!	\file	token.hpp
	\brief	Token class declaration.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Declarations of the Token class.

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.10.02
	C++ 20 validated

Version 2019.11.05
	C++ 17 cleanup

Version 2012.11.13
	C++ 11 cleanup

Version 2010.11.20
	Changed parameter of is_convertable_from to const&

Version 2010.11.09
	Switched boost::shared_ptr<> to std::shared_ptr<>.
	Added TOKEN_PTR_TYPE macro.

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

#include <memory>
#include <utility>
#include <string>
#include <typeinfo>
#include <vector>
#include <ostream>



/*! Defines the appropriate type of smart pointer used in this system. */
#define DEF_POINTER_TYPE(_TT) using pointer_type = std::shared_ptr<_TT>;



/*! Token base class. */
class Token {
public:
	DEF_POINTER_TYPE(Token)
	using string_type = std::string;
	
	// Block copying
	Token(Token const&) = delete;
	Token& operator = (Token const&) = delete;

	constexpr Token() = default;
	virtual ~Token() = default;
	[[nodiscard]] virtual string_type str() const;
};



/*! Make a new smart-pointer managed Token object. */
template <typename T> [[nodiscard]] inline 
Token::pointer_type make() { return Token::pointer_type(new T); }



/*! Make a new smart-pointer managed Token object with constructor parameter. */
template <typename T, typename U> [[nodiscard]] inline 
Token::pointer_type make(U const& param) { return Token::pointer_type(new T(param)); }



/*! Compare two tokens for same value. */
[[nodiscard]] inline 
bool operator == (Token::pointer_type const& lhs, Token::pointer_type const& rhs) {
#if !defined(NDEBUG)
	auto l = lhs->str();
	auto r = rhs->str();
#endif
	return lhs->str() == rhs->str();
}



/*! Test for family membership. */
template <typename CAST_TYPE, typename ORIGINAL_TYPE>
[[nodiscard]] inline bool is(ORIGINAL_TYPE const& tkn) {
	return dynamic_cast<CAST_TYPE const*>(tkn.get()) != nullptr;
}



/*! Test for family membership. */
template <typename CAST_TYPE, typename ORIGINAL_TYPE>
[[nodiscard]] inline bool is(ORIGINAL_TYPE const * tknPtr) {
	return dynamic_cast<CAST_TYPE const*>(tknPtr) != nullptr;
}



/*! Convert to subclass type. */
template <typename CONVERTED_TYPE>
[[nodiscard]] inline typename CONVERTED_TYPE::pointer_type convert(Token::pointer_type const& tkn) {
	return std::dynamic_pointer_cast<CONVERTED_TYPE>(tkn);
}



/*! Container of tokens. */
using TokenList = std::vector<Token::pointer_type>;



/*! stream operators */
inline std::ostream& operator << (std::ostream& os, Token const& token) {
	return os << token.str();
}

inline std::ostream& operator << (std::ostream& os, Token::pointer_type const& token) {
	return os << token->str();
}
