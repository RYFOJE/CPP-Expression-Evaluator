/*!	\file	variable.cpp
	\brief	Variable class implementation.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Implementation of the Variable class derived from Operand.

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.10.26
	C++ 20 validated

Version 2019.11.05
	C++ 17 cleanup

Version 2012.11.13
	C++ 11 cleanup

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

#include <ee/variable.hpp>

[[nodiscard]] Token::string_type Variable::str() const {
	if (!value_m)
		return Token::string_type("Variable: null");
	return value_m->str();
}
