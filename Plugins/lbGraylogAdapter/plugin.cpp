/*...sLicence:0:*/
/*
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2015  Lothar Behrens (lothar.behrens@lollisoft.de)

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
/*...sincludes:0:*/
#ifdef LBDMF_PREC
#include <lbConfigHook.h>
#endif

#ifdef WINDOWS
#include <windows.h>
#include <io.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

//#include <conio.h>

#ifdef __WATCOMC__
#include <ctype.h>
#endif
#ifdef __cplusplus
}
#endif

#include <stdio.h>
#ifndef OSX
#include <malloc.h>
#endif
#ifdef OSX
#include <sys/malloc.h>
#endif

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif

/*...sLB_DMFDATAMODEL_DLL scope:0:*/
#define LB_DMFDATAMODEL_DLL
#include <lbdmfdatamodel-module.h>
/*...e*/

/*...e*/

/*...sclass lbPluginModulelbGraylogAdapter:0:*/
class lbPluginModulelbGraylogAdapter : public lb_I_PluginModule {
public:

	lbPluginModulelbGraylogAdapter();
	virtual ~lbPluginModulelbGraylogAdapter();

	DECLARE_LB_UNKNOWN()
	
	void LB_STDCALL initialize();
	void LB_STDCALL install();
	
	DECLARE_PLUGINS()
};
/*...e*/

/*...sclass lbPluginModulelbGraylogAdapter implementation:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginModulelbGraylogAdapter)
        ADD_INTERFACE(lb_I_PluginModule)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOfPluginModule, lbPluginModulelbGraylogAdapter)

BEGIN_PLUGINS(lbPluginModulelbGraylogAdapter)
	ADD_PLUGIN(lbPluginGraylogAdapter, Logging)
END_PLUGINS()

lbPluginModulelbGraylogAdapter::lbPluginModulelbGraylogAdapter() {
	_CL_VERBOSE << "lbPluginModulelbGraylogAdapter::lbPluginModulelbGraylogAdapter() called." LOG_
}

lbPluginModulelbGraylogAdapter::~lbPluginModulelbGraylogAdapter() {
	_CL_VERBOSE << "lbPluginModulelbGraylogAdapter::~lbPluginModulelbGraylogAdapter() called." LOG_
}

void LB_STDCALL lbPluginModulelbGraylogAdapter::initialize() {
	char ptr[20] = "";
	sprintf(ptr, "%p", this);
	
	enumPlugins();
}

void LB_STDCALL lbPluginModulelbGraylogAdapter::install() {

}

lbErrCodes LB_STDCALL lbPluginModulelbGraylogAdapter::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbPluginModulelbGraylogAdapter::setData(...) not implemented yet" LOG_

	if (uk != NULL) {
		_CL_VERBOSE << "Cloning object with " << uk->getRefCount() << " references." LOG_
	}
        
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/
