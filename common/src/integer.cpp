/*!	\file	integer.cpp
	\brief	Integer class implementation.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Implementations of the Integer class derived from Operand.

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

Version 2012.11.16
	Added Bit operators, Pow

Version 2012.11.15
	Added BinaryInteger, Binary <function>

Version 2012.11.13
	C++ 11 cleanup

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

#include <ee/integer.hpp>
#include <ee/function.hpp>
#include <ee/operator.hpp>
#include <ee/boolean.hpp>
#include <ee/real.hpp>
#include <array>
using namespace std;



[[nodiscard]] Integer::string_type Integer::str() const {
	return value().str();
}

