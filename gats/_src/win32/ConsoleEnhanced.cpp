/*	\file		ConsoleEnhanced.cpp
	\author		Garth Santor
	\copyright	Garth Santor, Trinh Han
	\date		2021-08-29
	\brief		ConsoleEnhanced class implementation.

=========================================================================
ConsoleEnhanced class implementation.

========================================================================================
Revision History
-------------------------------------------------------------

Version 2021.08.29
	C++ 17 version
	Added to gats::win32 namespace

Version 2015.03.20
	Alpha release.

==========================================================================================
Copyright 2015-21, Garth Santor & Trinh Han

The copyright to the computer program(s) herein
is the property of Garth Santor, Canada.
The program(s) may be used and/or copied only with
the written permission of Garth Santor
or in accordance with the terms and conditions
stipulated in the agreement/contract under which
the program(s) have been supplied.
========================================================================================*/


#include <gats/win32/ConsoleEnhanced.hpp>
#include <algorithm>


namespace gats::win32 {

#pragma region State Management Operations

	/*!	Save the state of the console in a State object.
	*/
	ConsoleEnhanced::State ConsoleEnhanced::GetState() const {
		State cs;
		// Save window caption bar text
		ConsoleCore::GetTitle(cs.consoleTitle_);

		// Save code page information.
		cs.wOutputCodePageID_ = ConsoleCore::GetOutputCodePage();
		cs.wInputCodePageID_ = ConsoleCore::GetInputCodePage();

		// Save cursor shape information.
		ConsoleCore::GetCursorInfo(cs.cursorInfo_);

		// Save the screen buffer
		ConsoleCore::GetScreenBufferInfoEx(cs.screenBufferInfoEx_);
		cs.screenBuffer_.resize(cs.screenBufferInfoEx_.dwSize.X * cs.screenBufferInfoEx_.dwSize.Y);
		auto sr = cs.screenBufferInfoEx_.srWindow;
		ConsoleCore::ReadOutput(cs.screenBuffer_, cs.screenBufferInfoEx_.dwSize, COORD{ 0 }, sr);
		return cs;
	}



	/**	Set the state of the console to saved State object. */
	ConsoleEnhanced& ConsoleEnhanced::SetState(State const& _state) {
		// Set the code page information.
		ConsoleCore::SetInputCodePage(_state.wInputCodePageID_);
		ConsoleCore::SetOutputCodePage(_state.wOutputCodePageID_);

		// Restore the original settings/size
		ConsoleCore::SetWindowInfo(TRUE, SMALL_RECT{ 0 });
		ConsoleCore::SetScreenBufferSize(_state.screenBufferInfoEx_.dwSize);
		ConsoleCore::SetWindowInfo(TRUE, _state.screenBufferInfoEx_.srWindow);

		// Set the screen buffer
		auto screenBufferInfoEx = _state.screenBufferInfoEx_;
		ConsoleCore::SetScreenBufferInfoEx(screenBufferInfoEx);
		ConsoleCore::SetWindowInfo(TRUE, screenBufferInfoEx.srWindow);
		auto sr = _state.screenBufferInfoEx_.srWindow;
		ConsoleCore::WriteOutput(_state.screenBuffer_, screenBufferInfoEx.dwSize, COORD{ 0,0 }, sr);

		// Set the cursor shape and position
		ConsoleCore::SetCursorInfo(_state.cursorInfo_);
		ConsoleCore::SetCursorPosition(_state.screenBufferInfoEx_.dwCursorPosition);

		// Set the window caption bar text
		ConsoleCore::SetTitle(_state.consoleTitle_);
		return *this;
	}

#pragma endregion


#pragma region Window-Buffer Operations

	/*!	Clear the buffer to the current attribute. */
	ConsoleEnhanced& ConsoleEnhanced::Clear() {
		CONSOLE_SCREEN_BUFFER_INFO sbi = ConsoleCore::GetScreenBufferInfo();
		auto length = sbi.dwSize.X*sbi.dwSize.Y;
		ConsoleCore::FillOutputCharacter(L' ', length, COORD{ 0, 0 });
		ConsoleCore::FillOutputAttribute(sbi.wAttributes, length, COORD{ 0,0 });
		ConsoleCore::SetCursorPosition(COORD{ 0,0 });
		return *this;
	}



	/*!	Clear the buffer to the specified attribute. */
	ConsoleEnhanced& ConsoleEnhanced::Clear(Attribute attr) {
		ConsoleCore::SetTextAttribute(attr);
		CONSOLE_SCREEN_BUFFER_INFO sbi = ConsoleCore::GetScreenBufferInfo();
		auto length = sbi.dwSize.X*sbi.dwSize.Y;
		ConsoleCore::FillOutputCharacter(L' ', length, COORD{ 0, 0 });
		ConsoleCore::FillOutputAttribute(sbi.wAttributes, length, COORD{ 0,0 });
		ConsoleCore::SetCursorPosition(COORD{ 0,0 });
		return *this;
	}



	/*!	Set the Width and Height of the console. */
	ConsoleEnhanced& ConsoleEnhanced::SetSize(std::uint16_t width, std::uint16_t height) {
		SMALL_RECT sr{ 0 };
		ConsoleCore::SetWindowInfo(TRUE, sr);

		COORD bufferSize{ SHORT(width), SHORT(height) };
		ConsoleCore::SetScreenBufferSize(bufferSize);

		CONSOLE_SCREEN_BUFFER_INFO sbi = ConsoleCore::GetScreenBufferInfo();

		sr.Top = sr.Left = 0;
		width = std::min((SHORT)width, sbi.dwMaximumWindowSize.X);
		height = std::min((SHORT)height, sbi.dwMaximumWindowSize.Y);
		sr.Right = width - 1;
		sr.Bottom = height - 1;
		ConsoleCore::SetWindowInfo(TRUE, sr);
		return *this;
	}
#pragma endregion

} // End-of-namespace gats::win32