/*  PCSX2 - PS2 Emulator for PCs
 *  Copyright (C) 2002-2010  PCSX2 Dev Team
 *
 *  PCSX2 is free software: you can redistribute it and/or modify it under the terms
 *  of the GNU Lesser General Public License as published by the Free Software Found-
 *  ation, either version 3 of the License, or (at your option) any later version.
 *
 *  PCSX2 is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 *  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *  PURPOSE.  See the GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along with PCSX2.
 *  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

// Dependencies.h : Contains classes required by all Utilities headers.
//   This file is included by most .h files provided by the Utilities class.

// --------------------------------------------------------------------------------------
//  Forward Declarations Section
// --------------------------------------------------------------------------------------

class wxOutputStream;
class wxFileOutputStream;
class wxFFileOutputStream;

class wxStreamBase;
class wxInputStream;
class wxFileInputStream;
class wxFFileInputStream;

class wxPoint;
class wxRect;
class wxSize;

extern const wxSize wxDefaultSize;
extern const wxPoint wxDefaultPosition;

namespace Threading
{
	class Mutex;
	class Semaphore;
	class pxThread;
}

namespace Exception
{
	class BaseException;
}

// This should prove useful....
#define wxsFormat wxString::Format

#ifdef PCSX2_DEBUG
#	define tryDEBUG				try
#	define catchDEBUG(clause)	catch(clause)
#else
#	define tryDEBUG				if(true)
#	define catchDEBUG(clause)	if(false)
#endif

#if defined(PCSX2_DEVBUILD) || defined(PCSX2_DEBUG)
#	define tryDEVEL				try
#	define catchDEVEL			catch(clause)
#else
#	define tryDEBUG				if(true)
#	define catchDEBUG(clause)	if(false)
#endif

// --------------------------------------------------------------------------------------
//  ImplementEnumOperators  (macro)
// --------------------------------------------------------------------------------------
// This macro implements ++/-- operators for any conforming enumeration.  In order for an
// enum to conform, it must have _FIRST and _COUNT members defined, and must have a full
// compliment of sequential members (no custom assignments) --- looking like so:
//
// enum Dummy {
//    Dummy_FIRST,
//    Dummy_Item = Dummy_FIRST,
//    Dummy_Crap,
//    Dummy_COUNT
// };
//
// The macro also defines utility functions for bounds checking enumerations:
//   EnumIsValid(value);   // returns TRUE if the enum value is between FIRST and COUNT.
//   EnumAssert(value);
//
// It also defines a *prototype* for converting the enumeration to a string.  Note that this
// method is not implemented!  You must implement it yourself if you want to use it:
//   EnumToString(value);
//
#define ImplementEnumOperators( enumName ) \
	static __fi enumName& operator++	( enumName& src ) { src = (enumName)((int)src+1); return src; } \
	static __fi enumName& operator--	( enumName& src ) { src = (enumName)((int)src-1); return src; } \
	static __fi enumName operator++	( enumName& src, int ) { enumName orig = src; src = (enumName)((int)src+1); return orig; } \
	static __fi enumName operator--	( enumName& src, int ) { enumName orig = src; src = (enumName)((int)src-1); return orig; } \
 \
	static __fi bool operator<	( const enumName& left, const pxEnumEnd_t& )	{ return (int)left < enumName##_COUNT; } \
	static __fi bool operator!=( const enumName& left, const pxEnumEnd_t& )	{ return (int)left != enumName##_COUNT; } \
	static __fi bool operator==( const enumName& left, const pxEnumEnd_t& )	{ return (int)left == enumName##_COUNT; } \
 \
	static __fi bool EnumIsValid( enumName id ) { \
		return ((int)id >= enumName##_FIRST) && ((int)id < enumName##_COUNT); } \
	static __fi bool EnumAssert( enumName id ) { \
		return pxAssert( EnumIsValid(id) ); } \
 \
	extern const wxChar* EnumToString( enumName id )

class pxEnumEnd_t { };
static const pxEnumEnd_t pxEnumEnd = {};

// --------------------------------------------------------------------------------------
//  DeclareNoncopyableObject
// --------------------------------------------------------------------------------------
// This macro provides an easy and clean method for ensuring objects are not copyable.
// Simply add the macro to the head or tail of your class declaration, and attempts to
// copy the class will give you a moderately obtuse compiler error that will have you
// scratching your head for 20 minutes.
//
// (... but that's probably better than having a weird invalid object copy having you
//  scratch your head for a day).
//
// Programmer's notes:
//  * We intentionally do NOT provide implementations for these methods, which should
//    never be referenced anyway.

//  * I've opted for macro form over multi-inherited class form (Boost style), because
//    the errors generated by the macro are considerably less voodoo.  The Boost-style
//    The macro reports the exact class that causes the copy failure, while Boost's class
//    approach just reports an error in whatever "NoncopyableObject" is inherited.
//
//  * This macro is the same as wxWidgets' DECLARE_NO_COPY_CLASS macro.  This one is free
//    of wx dependencies though, and has a nicer typeset. :)
//
#ifndef DeclareNoncopyableObject
#	define DeclareNoncopyableObject(classname)	\
	private:									\
	explicit classname(const classname&);		\
	classname& operator=(const classname&)
#endif


// --------------------------------------------------------------------------------------
//  ScopedBool  -  Makes sure a boolean is set back to FALSE when current scope is left
// --------------------------------------------------------------------------------------
// Exception-safe way of tracking entry and exit of various functions of execution zones.
//
class ScopedBool
{
protected:
	bool*	m_boolme;

public:
	ScopedBool(bool& boolme)
	{
		boolme = true;
		m_boolme = &boolme;
	}

	~ScopedBool() throw()
	{
		*m_boolme = false;
	}
};

#include <wx/string.h>
#include <wx/intl.h>
#include <wx/log.h>

#include <stdexcept>
#include <cstring>		// string.h under c++
#include <cstdio>		// stdio.h under c++
#include <cstdlib>
#include <vector>
#include <list>

#include "Pcsx2Defs.h"

static const sptr _64kb		= 0x10000;
static const sptr _16kb		= _64kb / 4;
static const sptr _128kb	= _64kb * 2;
static const sptr _256kb	= _128kb * 2;

static const s64 _1mb		= 0x100000;
static const s64 _8mb		= _1mb * 8;
static const s64 _16mb		= _1mb * 16;
static const s64 _32mb		= _1mb * 32;
static const s64 _64mb		= _1mb * 64;
static const s64 _256mb		= _1mb * 256;
static const s64 _1gb		= _256mb * 4;
static const s64 _4gb		= _1gb * 4;


// ===========================================================================================
//  i18n/Translation Feature Set!
// ===========================================================================================

extern const wxChar* __fastcall pxExpandMsg( const wxChar* key, const wxChar* englishContent );
extern const wxChar* __fastcall pxGetTranslation( const wxChar* message );
extern bool pxIsEnglish( int id );

extern wxString fromUTF8( const char* src );
extern wxString fromAscii( const char* src );

// --------------------------------------------------------------------------------------
//  wxLt(x)   [macro]
// --------------------------------------------------------------------------------------
// macro provided for tagging translation strings, without actually running them through the
// translator (which the _() does automatically, and sometimes we don't want that).  This is
// a shorthand replacement for wxTRANSLATE.
//
#ifndef wxLt
#	define wxLt(a)		wxT(a)
#endif

// --------------------------------------------------------------------------------------
//  pxE(x)   [macro]
// --------------------------------------------------------------------------------------
// Translation Feature: pxE is used as a method of dereferencing very long english text
// descriptions via a "key" identifier.  In this way, the english text can be revised without
// it breaking existing translation bindings.  Make sure to add pxE to your PO catalog's
// source code identifiers, and then reference the source code to see what the current
// english version is.
//
// Valid prefix types:
//
// .Panel:   Key-based translation of a panel or dialog text; usually either a header or
//           checkbox description, by may also include some controls with long labels.
//           These have the highest translation priority.
//
// .Popup:   Key-based translation of a popup dialog box; either a notice, confirmation,
//           or error.  These typically have very high translation priority (roughly equal
//           or slightly less than pxE_Panel).
//
// .Error    Key-based translation of error messages, typically used when throwing exceptions
//           that have end-user errors.  These are normally (but not always) displayed as popups
//           to the user.  Translation priority is medium.
//
// .Wizard   Key-based translation of a heading, checkbox item, description, or other text
//           associated with the First-time wizard.  Translation of these items is considered
//           lower-priority to most other messages; but equal or higher priority to tooltips.
//
// .Tooltip: Key-based translation of a tooltip for a control on a dialog/panel.  Translation
//           of these items is typically considered "lowest priority" as they usually provide
//           the most tertiary of info to the user.
//

#define pxE(key, english)			pxExpandMsg( wxT(key),						english )

#include "Utilities/Assertions.h"
#include "Utilities/Exceptions.h"
#include "Utilities/ScopedPtr.h"
#include "Utilities/ScopedAlloc.h"
