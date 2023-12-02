#pragma once
/*!	\file	integer.hpp
	\brief	Integer class declaration.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Declarations of the Integer class derived from Operand.

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.10.02
	C++ 20 validated

Version 2019.11.05
	C++ 17 cleanup

Version 2014.10.29
	C++ 11 refactor.
	Converted Integer::value_type to boost::multiprecision::cpp_int
	Removed BinaryInteger

Version 2012.11.15
	Added BinaryInteger.

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

#include <ee/operand.hpp>
#include <boost/multiprecision/cpp_int.hpp>



/*! Integer token. */
class Integer : public Operand {
public:
	using value_type = boost::multiprecision::cpp_int;
	DEF_POINTER_TYPE(Integer)
private:
	value_type	value_;
public:
	Integer( value_type value = 0 )
		: value_( value ) { }

	[[nodiscard]]	value_type	value() const { return value_; }
	[[nodiscard]]	string_type	str() const override;
};