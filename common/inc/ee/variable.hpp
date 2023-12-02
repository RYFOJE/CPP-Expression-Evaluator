#pragma once
/*!	\file	variable.hpp
	\brief	Variable class declaration.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Declarations of the Variable class derived from Operand.

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.10.26
	C++ 20 validated

Version 2019.11.05
	C++ 17 cleanup

Version 2012.11.13
	C++ 11 cleanup

Version 2010.11.09
	Switched boost::shared_ptr<> to std::shared_ptr<>.
	Added TOKEN_PTR_TYPE macro.

Version 2009.11.26
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

#include <ee/operand.hpp>


/*! Variable operand token. */
class Variable : public Operand {
public:
	DEF_POINTER_TYPE(Variable)
	using value_type = Operand::pointer_type;
private:
	value_type	value_m;
public:
	Variable() = default;
	[[nodiscard]]	value_type	value() const { return value_m; }
					void		set(Operand::pointer_type const& value) { value_m = value; }
	[[nodiscard]]	string_type	str() const override;
};
