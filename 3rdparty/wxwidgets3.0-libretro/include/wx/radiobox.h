///////////////////////////////////////////////////////////////////////////////
// Name:        wx/radiobox.h
// Purpose:     wxRadioBox declaration
// Author:      Vadim Zeitlin
// Modified by:
// Created:     10.09.00
// Copyright:   (c) Vadim Zeitlin
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

#ifndef _WX_RADIOBOX_H_BASE_
#define _WX_RADIOBOX_H_BASE_

#include "wx/defs.h"

#if wxUSE_RADIOBOX

#include "wx/ctrlsub.h"

extern WXDLLIMPEXP_DATA_CORE(const char) wxRadioBoxNameStr[];

// ----------------------------------------------------------------------------
// wxRadioBoxBase is not a normal base class, but rather a mix-in because the
// real wxRadioBox derives from different classes on different platforms: for
// example, it is a wxStaticBox in wxUniv and wxMSW but not in other ports
// ----------------------------------------------------------------------------

class WXDLLIMPEXP_CORE wxRadioBoxBase : public wxItemContainerImmutable
{
public:
    virtual ~wxRadioBoxBase();

    // change/query the individual radio button state
    virtual bool Enable(unsigned int n, bool enable = true) = 0;
    virtual bool Show(unsigned int n, bool show = true) = 0;
    virtual bool IsItemEnabled(unsigned int n) const = 0;
    virtual bool IsItemShown(unsigned int n) const = 0;

    // return number of columns/rows in this radiobox
    unsigned int GetColumnCount() const { return m_numCols; }
    unsigned int GetRowCount() const { return m_numRows; }

    // return the next active (i.e. shown and not disabled) item above/below/to
    // the left/right of the given one
    int GetNextItem(int item, wxDirection dir, long style) const;

    // just silently ignore the help text, it's better than requiring using
    // conditional compilation in all code using this function
    void SetItemHelpText(unsigned int WXUNUSED(n),
                         const wxString& WXUNUSED(helpText))
    {
    }

    // returns the radio item at the given position or wxNOT_FOUND if none
    // (currently implemented only under MSW and GTK)
    virtual int GetItemFromPoint(const wxPoint& WXUNUSED(pt)) const
    {
        return wxNOT_FOUND;
    }


protected:
    wxRadioBoxBase()
    {
        m_numCols =
        m_numRows =
        m_majorDim = 0;

    }

    virtual wxBorder GetDefaultBorder() const { return wxBORDER_NONE; }

    // return the number of items in major direction (which depends on whether
    // we have wxRA_SPECIFY_COLS or wxRA_SPECIFY_ROWS style)
    unsigned int GetMajorDim() const { return m_majorDim; }

    // sets m_majorDim and also updates m_numCols/Rows
    //
    // the style parameter should be the style of the radiobox itself
    void SetMajorDim(unsigned int majorDim, long style);

private:
    // the number of elements in major dimension (i.e. number of columns if
    // wxRA_SPECIFY_COLS or the number of rows if wxRA_SPECIFY_ROWS) and also
    // the number of rows/columns calculated from it
    unsigned int m_majorDim,
                 m_numCols,
                 m_numRows;

};

#if defined(__WXUNIVERSAL__)
    #include "wx/univ/radiobox.h"
#elif defined(__WXMSW__)
    #include "wx/msw/radiobox.h"
#elif defined(__WXMOTIF__)
    #include "wx/motif/radiobox.h"
#elif defined(__WXGTK20__)
    #include "wx/gtk/radiobox.h"
#elif defined(__WXGTK__)
    #include "wx/gtk1/radiobox.h"
#elif defined(__WXMAC__)
    #include "wx/osx/radiobox.h"
#elif defined(__WXCOCOA__)
    #include "wx/cocoa/radiobox.h"
#elif defined(__WXPM__)
    #include "wx/os2/radiobox.h"
#endif

#endif // wxUSE_RADIOBOX

#endif // _WX_RADIOBOX_H_BASE_
