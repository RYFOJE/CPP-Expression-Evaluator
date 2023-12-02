#pragma once
/*!	\file	operand.hpp
	\brief	Operand class and utilities declarations.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Declarations of the Operand class derived from Token and the 
supporting utilities.

	class Operand
	class NoCast
	DECL_OPERAND_PERFORM()
	DEF_OPERAND_PERFORM()
	make_operand()
	get_value()
	OperandList
	dereference()
	make_same()
	up_cast()

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.10.02
	C++ 20 validated

Version 2019.12.10
	make_operand changed to use a parameter pack

Version 2019.11.05
	C++ 17 cleanup

Version 2012.11.13
	C++ cleanup.

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

#include <ee/token.hpp>
#include <cassert>
#include <deque>

/*! Operand token base class. */
class Operand : public Token {
public:
	DEF_POINTER_TYPE(Operand)
	using operand_list_type = std::deque<Operand::pointer_type>;
};


/*! Make a new smart-pointer managed Token object with constructor parameter. */
template <typename T, class... Args> inline Operand::pointer_type [[nodiscard]] make_operand(Args ... params) {
	return Operand::pointer_type(new T(params...));
}


/*! Gets the value from an operand. */
template <typename OPERAND_TYPE>
typename OPERAND_TYPE::value_type [[nodiscard]] value_of(Token::pointer_type const& operand) {
	assert(is<OPERAND_TYPE>(operand));
	return dynamic_cast<OPERAND_TYPE*>(operand.get())->value();
}


/*!	Type for a list of operands. */
using OperandList = Operand::operand_list_type;


