#ifndef __RESULT_SET_METADATA_H__
#define __RESULT_SET_METADATA_H__

#ifdef WINDOWS
 #ifndef DLLEXPORT
  #define DLLEXPORT __declspec(dllimport)
 #endif
#endif
#ifndef WINDOWS
 #define DLLEXPORT
#endif

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "DatabaseStringConverter.h"

class DLLEXPORT ResultSetMetaData : public DatabaseStringConverter
{
public:
  /// Retrieve a column's type
  virtual int GetColumnType(int i) = 0;
  /// Retrieve a column's size
  virtual int GetColumnSize(int i) = 0;
  /// Retrieve a column's name
  virtual wxString GetColumnName(int i) = 0;
  /// Retrieve the number of columns in the result set
  virtual int GetColumnCount() = 0;
  // The table name of given column
  virtual wxString GetTableForColumn(int i) = 0;
  virtual wxString GetTableForColumn(wxString column) = 0;

  enum {
    COLUMN_UNKNOWN = 0,
    COLUMN_NULL,
    COLUMN_INTEGER,
    COLUMN_STRING,
    COLUMN_DOUBLE,
    COLUMN_BOOL,
    COLUMN_BLOB,
    COLUMN_DATE,
    COLUMN_TEXT,
  };
};

#endif // __RESULT_SET_METADATA_H__

