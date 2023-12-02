#pragma once
/*!	\file	operation.hpp
	\brief	Operation classes declaration and utilities.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Declarations of the Operation class derived from Token and the 
supporting utilities.

	DECL_OPERATION_PERFORM()
	DEF_OPERATION_PERFORM()
	class Operation

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.10.02
	C++ 20 validated

Version 2019.11.05
	C++ 17 cleanup

Version 2016.11.02
	Added 'override' keyword where appropriate.

Version 2012.11.13
	C++ cleanup.

Version 2010.11.09
	Switched boost::shared_ptr<> to std::shared_ptr<>.
	Added TOKEN_PTR_TYPE macro.

Version 2009.12.10
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
#include <ee/operand.hpp>



/*! Operation token base class. */
class Operation : public Token {
public:
	DEF_POINTER_TYPE(Operation)

	[[nodiscard]] virtual unsigned number_of_args() const = 0;
};