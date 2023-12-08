#pragma once
/*!	\file	boolean.hpp
	\brief	Boolean classes declarations.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Declarations of the Booleans classes derived from Operand.  Includes 
the subclasses True and False.

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.10.02
	C++ 20 validated

Version 2019-11-05
	C++ 17 cleanup

Version 2012-11-13
	C++ 11 cleanup

Version 2010-11-09
	Switched boost::shared_ptr<> to std::shared_ptr<>.
	Added TOKEN_PTR_TYPE macro.

Version 2009-11-26
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
#include <ee/operator.hpp>


/*! Boolean token. */
class Boolean : public Operand {
public:
	using value_type = bool;
	DEF_POINTER_TYPE(Boolean)
private:
	value_type	value_;
public:
	Boolean(value_type const& value) : value_(value) { }

	[[nodiscard]]	value_type	value() const { return value_; }
	[[nodiscard]]	string_type	str() const override;
};


/*! Boolean True literal. */
class True : public Boolean {
public:
	True() : Boolean(true) { }
};

/*! Boolean False literal. */
class False : public Boolean {
public:
	False() : Boolean(false) { }
};
