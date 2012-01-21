
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

#include <stdio.h>
#include <string.h>
#ifndef UNIX
#include <windows.h>
#endif
#ifdef UNIX
#endif

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif

/*...sLB_DMFDATAMODEL_DLL scope:0:*/
#define LB_DMFDATAMODEL_DLL
#include <lbdmfdatamodel-module.h>
/*...e*/
#include <lbInterfaces-lbDMFManager.h>
#include <InternalFormatReader_Column_Types.h>

IMPLEMENT_FUNCTOR(instanceOfColumn_TypesInternalFormatReaderExtension, Column_TypesInternalFormatReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(Column_TypesInternalFormatReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

Column_TypesInternalFormatReaderExtension::Column_TypesInternalFormatReaderExtension() {
	_CL_VERBOSE << "Column_TypesInternalFormatReaderExtension::Column_TypesInternalFormatReaderExtension() called." LOG_
}

Column_TypesInternalFormatReaderExtension::~Column_TypesInternalFormatReaderExtension() {
	_CL_VERBOSE << "Column_TypesInternalFormatReaderExtension::~Column_TypesInternalFormatReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL Column_TypesInternalFormatReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: Column_TypesInternalFormatReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL Column_TypesInternalFormatReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Column_Types, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: Column_TypesInternalFormatReaderExtension::setOwningObject() owning parameter is not a lb_I_Column_Types." LOG_
		}
	} else {
		_LOG << "Error: Column_TypesInternalFormatReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL Column_TypesInternalFormatReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: Column_TypesInternalFormatReaderExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_InputStream, iStream)
	} else {
		_LOG << "Error: Column_TypesInternalFormatReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL Column_TypesInternalFormatReaderExtension::execute() {
	// Number of applications
	int   count = 0;
	*iStream >> count;
	
	for (int i = 0; i < count; i++) {
		long  _ID = -1;

		char* _name = NULL;
		char* _tablename = NULL;
		bool _ro = false;
		bool _specialcolumn = false;
		char* _controltype = NULL;
	
		*iStream >> _ID;

		*iStream >> _name;
		*iStream >> _tablename;
		*iStream >> _ro;
		*iStream >> _specialcolumn;
		*iStream >> _controltype;
		_LOG << "Read Column_Types entry from database: " << _name << ", " << _tablename << ", " << _ro << ", " << _specialcolumn << ", " << _controltype << ", " <<  _ID LOG_
		owningObject->addColumn_Types(_name, _tablename, _ro, _specialcolumn, _controltype,  _ID);

		// Leaky !
	}
}



class lbPluginColumn_TypesInternalFormatReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginColumn_TypesInternalFormatReaderExtension();
	
	virtual ~lbPluginColumn_TypesInternalFormatReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukColumn_TypesModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginColumn_TypesInternalFormatReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginColumn_TypesInternalFormatReaderExtension, lbPluginColumn_TypesInternalFormatReaderExtension)

lbErrCodes LB_STDCALL lbPluginColumn_TypesInternalFormatReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginColumn_TypesInternalFormatReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginColumn_TypesInternalFormatReaderExtension::lbPluginColumn_TypesInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginColumn_TypesInternalFormatReaderExtension::lbPluginColumn_TypesInternalFormatReaderExtension() called.\n" LOG_
}

lbPluginColumn_TypesInternalFormatReaderExtension::~lbPluginColumn_TypesInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginColumn_TypesInternalFormatReaderExtension::~lbPluginColumn_TypesInternalFormatReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginColumn_TypesInternalFormatReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginColumn_TypesInternalFormatReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginColumn_TypesInternalFormatReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginColumn_TypesInternalFormatReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginColumn_TypesInternalFormatReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukColumn_TypesModelExtension == NULL) {
		Column_TypesInternalFormatReaderExtension* Column_TypesModelExtension = new Column_TypesInternalFormatReaderExtension();
		
	
		QI(Column_TypesModelExtension, lb_I_Unknown, ukColumn_TypesModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukColumn_TypesModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginColumn_TypesInternalFormatReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukColumn_TypesModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		Column_TypesInternalFormatReaderExtension* Column_TypesModelExtension = new Column_TypesInternalFormatReaderExtension();
		
	
		QI(Column_TypesModelExtension, lb_I_Unknown, ukColumn_TypesModelExtension)
	}
	
	lb_I_Unknown* r = ukColumn_TypesModelExtension.getPtr();
	ukColumn_TypesModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginColumn_TypesInternalFormatReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukColumn_TypesModelExtension != NULL) {
                ukColumn_TypesModelExtension--;
                ukColumn_TypesModelExtension.resetPtr();
        }
}
