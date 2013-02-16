/*...sLicence:0:*/
/*
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2002  Lothar Behrens (lothar.behrens@lollisoft.de)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


    The author of this work will be reached by e-Mail or paper mail.
    e-Mail: lothar.behrens@lollisoft.de
    p-Mail: Lothar Behrens
			Ginsterweg 4
 
			65760 Eschborn (germany)
 */
/*...e*/

#ifdef LBDMF_PREC
#include <lbConfigHook.h>
#endif

/*...sLB_CLASSES_DLL scope:0:*/
#define LB_CLASSES_DLL
#include <lbclasses-module.h>
/*...e*/

#define __MISC

/*...sIncludes:0:*/

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>

#ifdef __MINGW32__
#include <stdlib.h>
#endif

#ifdef __WATCOMC__
#include <string.hpp>
#endif

#ifdef _MSC_VER
#define MAX_PATH 512
#endif

#include <stdarg.h>
#ifdef WINDOWS
#include <windows.h>
#endif
#ifdef UNIX

#ifdef __cplusplus
extern "C" {      
#endif            
#include <stdlib.h>
//#include <memory.h>
//#include <conio.h>
#include <limits.h>
#ifdef __cplusplus
}      
#endif            

#endif

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif
//#include <lbInterfaces.h>

#include <lbthread.h>
#include <lb_misc.h>
#include <fstream>
/*...e*/

#ifndef  ISTREAM_DEFINED
#define  ISTREAM_DEFINED

/*...sclass lbInputStream:0:*/
class lbInputStream : public lb_I_InputStream {

/*...spublic:0:*/
public:

    lbInputStream();

    virtual ~lbInputStream() { 
    	if (logmessage != NULL) {
    		free(logmessage);
    		logmessage = NULL;
    	}
    	
    	close();
    }
/*...e*/

    DECLARE_LB_UNKNOWN()

/*...slb_I_InputStream:0:*/

	void LB_STDCALL setFileName(const char* name);
	const char* LB_STDCALL getFileName();
	bool LB_STDCALL open();
	bool LB_STDCALL close();
	
	bool LB_STDCALL read();
    
	lb_I_String* LB_STDCALL getAsString();

	lb_I_InputStream& LB_STDCALL operator>> (int& i);
	lb_I_InputStream& LB_STDCALL operator>> (long& i);
	lb_I_InputStream& LB_STDCALL operator>> (bool& b);
	lb_I_InputStream& LB_STDCALL operator>> (char& c);
	lb_I_InputStream& LB_STDCALL operator>> (char*& string);
/*...e*/

/*...sprivate:0:*/
	private:

	void LB_STDCALL _realloc(int add_size);

	char f[PATH_MAX];
	char* logmessage;
	int lastsize;
	FILE*	fin;
	bool	isOpen;
	
	void*	readBuffer;
	int	max_readBufferSize;
	int	readBufferSize;
	int	offset;
	std::ifstream* _istream;

/*...e*/

};
/*...e*/


#ifdef __cplusplus
extern "C" {       
#endif            

IMPLEMENT_FUNCTOR(instanceOfInputStream, lbInputStream)

#ifdef __cplusplus
}
#endif            

BEGIN_IMPLEMENT_LB_UNKNOWN(lbInputStream)
	ADD_INTERFACE(lb_I_Stream)
        ADD_INTERFACE(lb_I_InputStream)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbInputStream::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbInputStream::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}


/*...slbInputStream\58\\58\lbInputStream\40\\41\:0:*/
lbInputStream::lbInputStream() {
//lbLock lbLock(sect);
	
	
	;
	
	fin = NULL;
	readBuffer = NULL;
	readBufferSize = 0;
	offset = 0;
	max_readBufferSize = 100;
	isOpen = false;
        f[0] = 0;

	_istream = NULL;

        logmessage = NULL;
        lastsize = 0;
}
/*...e*/
void LB_STDCALL lbInputStream::setFileName(const char* name) {
	f[0] = 0;
	strncpy(f, name, PATH_MAX-1);
	if (!FileExists(f)) {
	    _CL_LOG << "Error: File to read from not possible! (" << f << ")" LOG_
	    _LOG << "Error: File to read from not possible! (" << f << ")" LOG_
	}
}

const char* LB_STDCALL lbInputStream::getFileName() {
	return f;
}

lb_I_String* LB_STDCALL lbInputStream::getAsString() {
	UAP_REQUEST(getModuleInstance(), lb_I_String, string)

	if (!isOpen) {
		_LOG << "Error: File is not open." LOG_
		*string = "";
		string++;
		return string.getPtr();	
	}
	
	int size = 0;

#ifndef __WATCOMC__
	std::string s;	
#endif
#ifdef __WATCOMC__
	char* buf = NULL;
	String s;	
#endif

	bool more = false;
	more = std::getline(*_istream, s);
	
#ifndef __WATCOMC__
  while (more) {
	  *string += s.c_str();
	  more = std::getline(*_istream, s);
	  if (more) *string += "\n";
  }
#endif

#ifdef __WATCOMC__ 
  buf = (char*) malloc(1000);
  while (!_istream->eof()) {
	buf[0] = 0;
	_istream->getline(buf, 1000);
	if (strlen(buf) == 0) {
		*string += "\n";
	} else {
		*string += buf;
		*string += "\n";
	}
  }
  free(buf);
#endif
  
  string++;
  return string.getPtr();
}


bool LB_STDCALL lbInputStream::close() {
	if (isOpen) {
		_istream->close();
		delete _istream;
		isOpen = false;
	}

	return true;
}

bool LB_STDCALL lbInputStream::open() {
	if (!isOpen) {
		if (!FileExists(f)) {
			return false;
		}
		_istream = new std::ifstream(f);
	}

	isOpen = true;
	return true;
}

bool LB_STDCALL lbInputStream::read() {
	return false;
}
void LB_STDCALL lbInputStream::_realloc(int add_size) {
} 
 
lb_I_InputStream& LB_STDCALL lbInputStream::operator>> (int& i) {
	if (!isOpen) return *this;

	*_istream >> i;

	return *this;
}

lb_I_InputStream& LB_STDCALL lbInputStream::operator>> (long& i) {
	if (!isOpen) return *this;

	*_istream >> i;

	return *this;
}

lb_I_InputStream& LB_STDCALL lbInputStream::operator>> (bool& b) {
	if (!isOpen) {
		_LOG << "Warning: Tried to read a boolean value on closed file!" LOG_
		return *this;
	}
	
	int _b;

	*_istream >> _b;

	if (_b == 1)
		b = true;
	else
		b = false;
		
	return *this;
}

lb_I_InputStream& LB_STDCALL lbInputStream::operator>> (char& c) {
	if (!isOpen) return *this;

	*_istream >> c;
	
	return *this;
}

lb_I_InputStream& LB_STDCALL lbInputStream::operator>> (char*& _string) {
	char* buf = NULL;
	int size = 0;

#ifndef __WATCOMC__
	std::string s;	
#endif
#ifdef __WATCOMC__
	String s;	
#endif
	
	*_istream >> size;

	_istream->ignore(1, '\n');
#ifndef __WATCOMC__ 
	getline(*_istream, s);
	if (_string != NULL) free(_string);
	_string = strdup(s.c_str());
#endif
#ifdef __WATCOMC__ 
	//*_istream >> s;
	if (_string != NULL) free(_string);
	buf = (char*) malloc(size+1);
	_istream->getline(buf, size+1);
	_string = buf;
#endif

	return *this;
}


#endif //  ISTREAM_DEFINED

