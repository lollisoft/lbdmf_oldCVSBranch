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

#ifdef _MSC_VER

#pragma warning( disable: 4101 )

#endif

// skiplist.cpp
/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.70 $
 * $Name:  $
 * $Id: skiplist.cpp,v 1.70 2012/01/21 18:39:21 lollisoft Exp $
 *
 * $Log: skiplist.cpp,v $
 * Revision 1.70  2012/01/21 18:39:21  lollisoft
 * Got the plugin issue fixed. (When a plugin will load another plugin from an implementations constructor)
 *
 * Revision 1.69  2011/10/16 08:40:56  lollisoft
 * Refactoring produced again some uninitialized variables that havs been fixed now. The app seems to start and esit without errors.
 *
 * Revision 1.68  2011/10/15 21:47:12  lollisoft
 * Removed all code that is obsolete. Current code compiles but still does not run.
 *
 * Revision 1.67  2011/10/15 13:14:05  lollisoft
 * Decided to make a hash cut and removed stuff that everywhere was the cause for crashes on Mac.
 * Currently the code crashes on windows, but lets see how it is working on Mac.
 *
 * Revision 1.66  2011/10/15 06:36:12  lollisoft
 * All current changes including interfaces (starting mass changes).
 *
 * Revision 1.65  2011/10/03 04:43:07  lollisoft
 * Fixes to try cope with rare application crash.
 *
 * Revision 1.64  2011/10/02 10:45:13  lollisoft
 * Removed a possible sporadic crash cause.
 *
 * Revision 1.63  2011/09/25 11:47:02  lollisoft
 * There are still random crashes, but with a new trace function to try log the crash at a null pointer in a string, the crashes again get more rare. Probably still need more cppcheck runs.
 *
 * Revision 1.62  2011/09/25 09:30:14  lollisoft
 * Many bugfixes like missing variable initialization. Used CppCheck for this to get rid of the random crashes.
 * Only lbHook, lbModule, lbclasses and the Basetypes regression test (including headers and interfaces) are
 * fixed. Other modules will follow.
 *
 * Revision 1.61  2011/02/27 10:30:36  lollisoft
 * Changed all copyright entries addresses to match my current postal address.
 *
 * Revision 1.60  2010/05/17 05:44:44  lollisoft
 * Many changes related to support mixing MinGW with Open Watcom.
 *
 * Revision 1.59  2009/12/06 19:20:16  lollisoft
 * Modified build process to use precompiled files.
 * Corrected the long build time problem. It is located in the _LOG macro.
 * Updated wxPropgrid to 1.4.9.1 and updated building against wxMSW 2.8.10.
 *
 * Build works, but running the application fails with not properly initialized error.
 * (0xc0000005)
 *
 * Also updated the iss files for the new planned release.
 *
 * Revision 1.58  2009/06/29 15:01:01  lollisoft
 * Function position must set iteration flag correctly.
 *
 * Revision 1.57  2009/06/10 11:53:59  lollisoft
 * Added functions to enable position in the container to enable 'jumps'.
 *
 * Revision 1.56  2008/11/06 18:45:34  lollisoft
 * Some bugfixes.
 *
 * Revision 1.55  2008/07/25 16:43:50  lollisoft
 * Fixed application crash at exit.
 *
 * Revision 1.54  2008/07/24 20:53:36  lollisoft
 * These changes let the application run on Mac OS X 10.5 (Leopard). But crashes at exit, propably due to changed cleanup logic or changed default variable values (not correctly initialized).
 *
 * Revision 1.53  2008/02/12 21:36:27  lollisoft
 * Added code that allows to store parameter sets into the meta application file.
 *
 * Revision 1.52  2007/08/06 19:10:29  lollisoft
 * Improved installation process on Windows.
 *
 * Revision 1.51  2006/12/10 16:59:41  lollisoft
 * Also check if value is  NULL.
 *
 * Revision 1.50  2006/10/22 18:06:48  lollisoft
 * Bugfix in reference count handling. Internally, do not increase on searching by
 * key, but increase reference count at returning the key.
 *
 * Bugfix in iteration handling. If the iterator was leaved anywhere, the deletion
 * of the objects was affected. Only elements at and after iterator position
 * were deleted.
 *
 * Revision 1.49  2006/07/17 17:37:45  lollisoft
 * Changes dueto bugfix in plugin manager. Repeadable iterator problem.
 * Not correctly finished the iteration, thus plugins in the same DLL wouldn't
 * be found any more after first query.
 *
 * Code works well with improved trmem library, but there is still a crash in
 * database classes (pgODBC library).
 *
 * Revision 1.48  2006/07/02 13:24:02  lollisoft
 * Added feature to not clone objects when inserting into a container.
 *
 * Revision 1.47  2006/02/26 23:46:19  lollisoft
 * Changed build method for shared libraries under Mac OS X
 * to be frameworks. These would be embedable into the
 * application bundle - thus enables better install method.
 *
 * Revision 1.46  2006/02/20 13:00:45  lollisoft
 * Missing return. This would be the cause, why currentKey hasn't worked.
 *
 * Revision 1.45  2006/02/19 12:03:28  lollisoft
 * Populating properties works. Currently it is not possible to
 * add sub properties, but handling categories.
 *
 * Note: Each property name must be unique.
 *
 * Revision 1.44  2006/02/18 19:13:25  lollisoft
 * A todo.
 *
 * Revision 1.43  2006/02/17 23:57:16  lollisoft
 * Added functionality to pass a bunch of properties to the GUI. This then would be shown in a property window.
 *
 * There are additional changes in various classes to let this
 * work properly.
 *
 * Todo: Implement the unpacking and type detection code
 * for each parameter, mapping to wxPropertyGrid entities
 * and handlers that push back the changes.
 *
 * Revision 1.42  2006/01/30 15:54:15  lollisoft
 * Removed the __FILE__ and __LINE__ parameter usage in UAP and QI.
 * This was an unnessesary thing and makes programming easier.
 *
 * Revision 1.41  2005/12/06 15:54:56  lollisoft
 * Changes let the GUI work properly in debug mode. But there is a NULL
 * pointer exeption in release mode near opening a database form.
 *
 * Testing on Mac OS X and Linux.
 *
 * Revision 1.40  2005/11/20 17:26:14  lollisoft
 * Local TRMem count.
 *
 * Revision 1.39  2005/11/11 22:51:30  lollisoft
 * Memory leaks removed. There are currently only 4 chunks leaky.
 * These may be false positives, because one of them is an allocated
 * wxMenu instance, I have not to delete after adding it to a wxMenuBar.
 * wxMenuBar gets an owner (see wxWidgets documentation).
 *
 * Revision 1.38  2005/10/31 21:37:31  lollisoft
 * Compile problems. Removed unused log messages.
 *
 * Revision 1.37  2005/10/31 14:59:55  lollisoft
 * Deflated a macro, but deactivated it.
 *
 * Revision 1.36  2005/10/28 17:28:42  lollisoft
 * Fixed memory leaks in database classes. Using it in console is tested.
 * There now are only three objects leaked.
 *
 * Revision 1.35  2005/07/30 15:56:10  lollisoft
 * Bugfix in get ... At functions.
 *
 * Revision 1.34  2005/06/28 12:04:02  lollisoft
 * Bugfix in skiplist::exists(). Search increases the reference. Must be decreased again.
 *
 * Revision 1.33  2005/06/27 10:32:10  lollisoft
 * Mostly changes to conio.h conflicts while XCode build
 *
 * Revision 1.32  2005/06/01 10:54:57  lollisoft
 * Added the ability to detach contained objects. Ownership leaving.
 *
 * Revision 1.31  2005/05/17 22:59:19  lollisoft
 * Bugfix in reference counting.
 *
 * Storing windows in a selfdeleting (UAP) container would
 * crash. This has been overcome since the bugfix for the
 * containers self has been taken.
 *
 * The wxWidgets controls or windows are not reference
 * counted, or have its own one. So they should not be stored
 * simply in a container of my framework.
 *
 * Special reference increment is done for the specific dialogs.
 *
 * Revision 1.30  2005/05/11 13:19:40  lollisoft
 * Bugfix for reference count error and changed back any _CL_LOG messages to be _CL_VERBOSE only
 *
 * Revision 1.29  2005/05/10 20:20:38  lollisoft
 * Include files changed to be more actially language compilant
 *
 * Revision 1.28  2005/05/04 22:06:37  lollisoft
 * Most logging messages removed and one verbose message added.
 *
 * Revision 1.27  2005/05/01 21:23:56  lollisoft
 * Bugfix in much parts of skiplist implementation. This came from porting
 * of a free java based skiplist :-(
 *
 * Thanks to the trmem code from Open Watcom.
 *
 * Revision 1.26  2005/03/31 09:02:45  lollisoft
 * Copyright text problems under linux.
 *
 * Revision 1.25  2005/03/19 16:38:54  lollisoft
 * Bugfix, if iterate an empty container.
 *
 * Revision 1.24  2005/03/14 18:59:02  lollisoft
 * Various changes and additions to make plugins also work with database forms
 *
 * Revision 1.23  2005/02/10 17:02:33  lollisoft
 * Changes for Mac OS X
 *
 * Revision 1.22  2005/01/23 13:43:05  lollisoft
 * std:: is only under linux working
 *
 * Revision 1.21  2004/06/21 06:32:02  lollisoft
 * Implemented GUI database form creation, but updating fails.
 *
 * Revision 1.20  2004/06/16 22:13:52  lollisoft
 * Logs for debug - skip list may be memory leaky
 *
 * Revision 1.19  2004/06/09 07:03:23  lollisoft
 * Still problems with undeleted container data ??
 *
 * Revision 1.18  2004/01/24 16:15:02  lollisoft
 * minor changes
 *
 * Revision 1.17  2003/12/13 10:56:25  lollisoft
 * Database improovements and changes in my licence adress.
 * The database part is still not working by updating columns
 *
 * Revision 1.16  2003/08/16 18:07:00  lollisoft
 * Added my new address due to move
 *
 * Revision 1.15  2003/07/31 20:18:25  lollisoft
 * Removed logging messages
 *
 * Revision 1.14  2003/06/16 21:49:42  lollisoft
 * Bugfix ??
 *
 * Revision 1.13  2003/02/17 21:34:41  lollisoft
 * Much problems with compilation solved, bu wy came this ??
 *
 * Revision 1.12  2003/01/19 17:31:25  lolli
 * Runs now with MSC
 *
 * Revision 1.11  2002/12/29 16:05:10  lolli
 * Intent to go public
 *
 * Revision 1.10  2002/11/29 19:50:27  lothar
 * Compiles again under linux, but some problems at runtime with DOMString
 *
 * Revision 1.9  2002/10/17 17:35:13  lolli
 * Use of _CL_VERBOSE macro
 *
 * Revision 1.8  2002/10/04 16:53:14  lolli
 * Replaced old LOG macro with the new
 * _LOG << "text" << integer value LOG_
 * combination. This makes sprintf obsolete.
 *
 * Revision 1.7  2002/09/12 18:36:12  lolli
 * Removed some log messages
 *
 * Revision 1.6  2002/09/07 09:57:13  lolli
 * First working callback function
 *
 * Revision 1.5  2002/08/21 18:44:29  lolli
 * Implemented the new container functions for direct access
 *
 * Revision 1.4  2002/06/01 08:59:27  lolli
 * Bug due to position of module definition for export
 *
 * Revision 1.3  2002/05/01 14:17:13  lolli
 * This version does not compile
 *
 * Revision 1.2  2002/04/15 18:24:33  lolli
 * Huge changes - works good
 *
 * Revision 1.1  2002/03/03 08:33:57  lolli
 * Initial non interface based skiplist
 *
 **************************************************************/
/*...e*/
/*...sincludes:0:*/
#ifdef LBDMF_PREC
#include <lbConfigHook.h>
#endif

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
//#include <conio.h>

#ifdef LINUX
#include <string.h>
#endif
#ifdef WINDOWS
#include <string.h>
#endif

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif

/*...sLB_CLASSES_DLL scope:0:*/
#define LB_CLASSES_DLL
#include <lbclasses-module.h>
/*...e*/

#include <skiplist.h>
/*...e*/
/*...sfunctor:0:*/
#ifdef __cplusplus
extern "C" {
#endif

IMPLEMENT_FUNCTOR(instanceOfSkipList, SkipList)

#ifdef __cplusplus
}
#endif
/*...e*/

SkipNode::SkipNode(const SkipNode &s) {
   	myLevel = MAXLEVEL;
   	value = NULL;
    	
   	forward = new SkipNode* [myLevel+1];
   	for (int i=0; i<=myLevel; i++)
  	    forward[i] = NULL;
	_LOGERROR << "Copy constructor of SkipNode called!" LOG_
}


/*...sSkipNode implementation:0:*/
SkipNode::SkipNode() {
   	myLevel = MAXLEVEL;
   	value = NULL;
    	
   	forward = new SkipNode* [myLevel+1];
   	for (int i=0; i<=myLevel; i++)
  	    forward[i] = NULL;
}
    
SkipNode::SkipNode(lb_I_Element* r, int level) {
    myLevel = level;
    value = r;
	
    if (value == NULL) printf("ERROR: Constructor got a NULL pointer as datan");
    forward = new SkipNode* [level+1];
	
    for (int i=0; i<=level; i++)
        forward[i] = NULL;
}

SkipNode::~SkipNode() { 

	if (_TRMemValidate(this) == 0) {
		_CL_LOG << "Error: Object pointer is invalid!" LOG_
	}

	if (forward) {
		for (int i=0; i<=myLevel; i++)
		    forward[i] = NULL;
		delete [] forward; 
	}
}

void SkipNode::detach() {
	/* 
		value = NULL invokes operator = who internally tries to
		release the stored pointer.
		
		detach() is intented to force a membership leaving. So
		invoking detach() is explicid done by the user of the
		container due to the knoledge, that the container not have
		to delete it's data.
		
		This is needed to detach the wxWidgets sample application's
		database dialogs, because the wxWidgets framework worries
		about deleting it's windows.
	*/
	
    	//value = NULL;
	if (value != NULL) value->detachData();
}
/*...e*/


BEGIN_IMPLEMENT_LB_UNKNOWN(Iterator)
	ADD_INTERFACE(lb_I_Iterator)
END_IMPLEMENT_LB_UNKNOWN()


lbErrCodes LB_STDCALL Iterator::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	return ERR_NONE;
}

Iterator::Iterator() {
	iterator = NULL;
	iteration = 0;
	head = NULL;
	skipiterator = NULL;
	flag = 1;
	level = MAXLEVEL;
	count = 0;
	cloning = true;
	_currentKey = NULL;
	container_data = NULL;
}

Iterator::Iterator(SkipNode* _head, int _count) {
	iterator = NULL;
	iteration = 0;
	head = _head;
	skipiterator = NULL;
	flag = 1;
	level = MAXLEVEL;
	count = _count;
	cloning = true;
	_currentKey = NULL;
	container_data = NULL;
}


Iterator::~Iterator() {
	head = NULL;
	skipiterator = NULL;
}

int LB_STDCALL Iterator::Count() { 
        return count; 
} 

int LB_STDCALL Iterator::hasMoreElements() { 
    return can_dump();
} 

lb_I_Unknown* LB_STDCALL Iterator::nextElement() { 
	Elem e = dump_next();
	
	if(e != NULL) {
		_currentKey = e->getKey();
		if (e == NULL) {
			_LOGERROR << "FARAL: Object went to NULL, but not expected." LOG_
			return NULL;
		}
		lb_I_Unknown* u = e->getObject();
		_TRMemValidate(u);
		return u;
	} else {
        _LOG << "Error: Please call hasMoreElements first to check if any elements are available!" LOG_
        return NULL; 
	}
}

lb_I_KeyBase* LB_STDCALL Iterator::currentKey() {
	lb_I_KeyBase* temp;
	_currentKey->queryInterface("lb_I_KeyBase", (void**) &temp, __FILE__, __LINE__);
	return _currentKey;
}

void Iterator::finishIteration() {
	iteration = 0;
}

int Iterator::can_dump() {
	if (count == 0) return 0;
	if (iteration == 0) { 
       	iteration = 1; 
        skipiterator = head; 
		flag = 1;
	} 

	if (skipiterator == NULL) { 
	        iteration = 0; 
	        flag = 1;
	        return 0; 
	} 
	
	return 1;
}

Elem Iterator::dump_next() {
	if (skipiterator != NULL) {
		Elem e = skipiterator->value.getPtr();
		
		while (e == NULL) {
			skipiterator = skipiterator->forward[0];
			if (!skipiterator) return NULL;
			e = skipiterator->value.getPtr();
		}

		skipiterator = skipiterator->forward[0];
		return e;
	} else {
		printf("Return NULL because skipiterator is NULLn");
		return NULL;
	}
}

BEGIN_IMPLEMENT_LB_UNKNOWN(SkipList)
	ADD_INTERFACE(lb_I_Container)
END_IMPLEMENT_LB_UNKNOWN()

lb_I_Iterator* LB_STDCALL SkipList::getIterator() {
	Iterator* it = new Iterator(head, count);
	lb_I_Iterator* _it = NULL;
	it->queryInterface("lb_I_Iterator", (void**) &_it, __FILE__, __LINE__);
	_LOG << "SkipList::getIterator() Returns a list of " << Count()  << " elements" LOG_
	return _it;
}


lbErrCodes LB_STDCALL SkipList::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	UAP(lb_I_Container, source)
	QI(uk, lb_I_Container, source)
	
	if (source != NULL) 
		for (int i = 1; i <= source->Count(); i++) {
			UAP(lb_I_Unknown, uk)
			UAP(lb_I_KeyBase, key)
		
			uk = source->getElementAt(i);
			key = source->getKeyAt(i); 

			insert(&uk, &key);
		}
	
	return ERR_NONE;
}

void LB_STDCALL SkipList::setCloning(bool doClone) {
	cloning = doClone;
}

SkipList::SkipList() {
	iterator = NULL;
	iteration = 0;
	canDeleteObjects = true;
	head = NULL; //new SkipNode();
	skipiterator = NULL;
	flag = 1;
	level = MAXLEVEL;
	count = 0;
	cloning = true;
	_currentKey = NULL;
	container_data = NULL;
}

///todo Cleanup problem, when key used multiple times.
SkipList::~SkipList() {
	// Bugfix. If any search leave the container in any position not at start, 
	// the container wouldn't delete all elements.
	finishIteration();
	if (can_dump() == 1) {
		while (skipiterator) {
			SkipNode* temp = skipiterator;
			skipiterator = skipiterator->forward[0];
	
			if (!canDeleteObjects) {
				temp->detach();
			}
	
			delete temp;		
		}
		
		head = NULL;
	} else {
		if (head) delete head;
	}
}
/*...sSkipList5858Count4041:0:*/
int LB_STDCALL SkipList::Count() { 
        return count; 
} 
/*...e*/
void LB_STDCALL SkipList::detachAll() {
	canDeleteObjects = false;
}
/*...sSkipList5858deleteAll4041:0:*/
void LB_STDCALL SkipList::deleteAll() {
	if (can_dump() == 1) {
		while (skipiterator) {
			SkipNode* temp = skipiterator;
			skipiterator = skipiterator->forward[0];

			if (!canDeleteObjects) {
				temp->detach();
			}
	
			delete temp;		
		}
		
		head = NULL;
	}

	if (head == NULL) head = new SkipNode();
	level = MAXLEVEL;

	iteration = 0;
	skipiterator = NULL;
	count = 0;
} 
/*...e*/
/*...sSkipList5858exists40lb_I_KeyBase4242 const key41:0:*/
int LB_STDCALL SkipList::exists(lb_I_KeyBase** const key) { 
    UAP(lb_I_Unknown, s)
    
    s = search(*key);
    
    if (s == NULL) return 0;	

    return 1; 
} 
/*...e*/
/*...sSkipList5858insert40lb_I_Unknown4242 const e44 lb_I_KeyBase4242 const key41:0:*/
lbErrCodes LB_STDCALL SkipList::insert(lb_I_Unknown** const e, lb_I_KeyBase** const key) { 
        lbErrCodes err = ERR_NONE; 

		_TRMemValidate(e);
	
        lbSkipListElement* el = new lbSkipListElement(*e, *key, cloning);
        

        insert(el);

       	count++;
        
        return err; 
} 
/*...e*/
/*...sSkipList5858remove40lb_I_KeyBase4242 const key41:0:*/
lbErrCodes LB_STDCALL SkipList::remove(lb_I_KeyBase** const key) { 
        lbErrCodes err = ERR_NONE; 
        
        lbSkipListElement* el = new lbSkipListElement(NULL, *key, cloning);
        
        remove(el);
        
        delete el;

        return err; 
} 
/*...e*/
/*...sSkipList5858_insert40lb_I_Unknown4242 const e44 lb_I_KeyBase4242 const key41:0:*/
lbErrCodes LB_STDCALL SkipList::_insert(lb_I_Unknown** const e, lb_I_KeyBase** const key) { 
/*...sbla:0:*/
#ifdef bla
    if (container_data == NULL) { 
        lbElement* _data = new lbElement(*e, *key, cloning); 
         

        _data->queryInterface("lb_I_Element", (void**) &container_data, __FILE__, __LINE__); 
        if (container_data == NULL) _LOG << "Could not get unknown interface of lbElement!" LOG_

        lb_I_Unknown* uk_o = NULL; 
        if ((uk_o = container_data->getObject()) == NULL) { 
                _LOG << "Failed to insert first element in SkipList::insert" LOG_
                return ERR_CONTAINER_INSERT; 
        } else RELEASE(uk_o); 
    } 
    else { 
        lb_I_Element* temp; 
        for (temp = container_data; temp != NULL; temp = temp->getNext()) { 
            lb_I_Element* next = temp->getNext(); 

            if (next != NULL) { 
                if (next->getKey() < *key) { 
                    lbElement* el = new lbElement(*e, *key, cloning, next); 
                     
                    temp->setNext(el); 
                    return ERR_NONE; 
                } 
            } 
            else { 
            	lbElement* el = new lbElement(*e, *key, next); 
            	 
                temp->setNext(el); 
                return ERR_NONE; 
            } 
        } 
    } 
#endif    
/*...e*/
    return ERR_NONE; 
} 
/*...e*/
/*...sSkipList5858_remove40lb_I_KeyBase4242 const key41:0:*/
lbErrCodes LB_STDCALL SkipList::_remove(lb_I_KeyBase** const key) { 
/*...sbla:0:*/
    _LOG << "SkipList::_remove(lb_I_KeyBase** const key) is Obsolete" LOG_ 
/*...e*/
    return ERR_CONTAINER_REMOVE; 
} 
/*...e*/
/*...sSkipList5858hasMoreElements4041:0:*/
int LB_STDCALL SkipList::hasMoreElements() { 
    return can_dump();
} 
/*...e*/
/*...sSkipList5858nextElement4041:0:*/
lb_I_Unknown* LB_STDCALL SkipList::nextElement() { 
	Elem e = dump_next();
	
	if(e != NULL) {
		_currentKey = e->getKey();
		if (e == NULL) {
			_LOGERROR << "FARAL: Object went to NULL, but not expected." LOG_
			return NULL;
		}
		lb_I_Unknown* u = e->getObject();
		_TRMemValidate(u);
		return u;
	} else {
        _LOG << "Error: Please call hasMoreElements first to check if any elements are available!" LOG_
        return NULL; 
	}
} 
/*...e*/

int LB_STDCALL SkipList::position(lb_I_KeyBase** const key) {
    UAP(lb_I_Unknown, s)

    s = search(*key, true);
    
    if (s == NULL) return 0;
	iteration = 1; // else can_dump resets the iteration position!
    return 1; 
}

int LB_STDCALL SkipList::position(int i) {
	int ii = 1;
	
	Elem e;
	
	if (can_dump() == 1) {
		e = dump_next();
		
		while ((e != NULL) && (ii < i)) {
			ii++;
			e = dump_next();
		}
		
		if (ii == i) {
			return 1;
		}
	}
	
	return 0;
}


lb_I_KeyBase* LB_STDCALL SkipList::currentKey() {
	lb_I_KeyBase* temp;
	_currentKey->queryInterface("lb_I_KeyBase", (void**) &temp, __FILE__, __LINE__);
	return _currentKey;
}

/*...sSkipList5858getElement40lb_I_KeyBase4242 const key41:0:*/
lb_I_Unknown* LB_STDCALL SkipList::getElement(lb_I_KeyBase** const key) { 
    lb_I_Unknown* e = search(*key);
    
    if (e == NULL) {
	_CL_VERBOSE << "SkipList::getElement(...) returns a NULL pointer!" LOG_
	_CL_VERBOSE << "SkipList::getElement(...) has " << count << " elements." LOG_
	_CL_VERBOSE << "SkipList::getElement(...) searched for '" << (*key)->charrep() << "'" LOG_
    }
    
    return e;
} 
/*...e*/
/*...sSkipList5858setElement40lb_I_KeyBase4242 key44 lb_I_Unknown4242 const e41:0:*/
void LB_STDCALL SkipList::setElement(lb_I_KeyBase** key, lb_I_Unknown ** const e) { 
    remove(key); 
    insert(e, key); 
}
/*...e*/
/*...slb_I_Unknown42 LB_STDCALL SkipList5858getElementAt40int i41:0:*/
lb_I_Unknown* LB_STDCALL SkipList::getElementAt(int i) {
        int ii = 1;

	Elem e;
	
	if (can_dump() == 1) {
		e = dump_next();

		while ((e != NULL) && (ii < i)) {
			ii++;
			e = dump_next();
		}

		finishIteration();
		
		if (ii == i) return e->getObject();
	}
	
	return NULL;
}
/*...e*/
/*...slb_I_KeyBase42 LB_STDCALL SkipList5858getKeyAt40int i41:0:*/
lb_I_KeyBase* LB_STDCALL SkipList::getKeyAt(int i) {
	int ii = 1;

	Elem e;

	if (can_dump() == 1) {
		e = dump_next();

		while ((e != NULL) && (ii < i)) {
			ii++;
			e = dump_next();
		}

		finishIteration();

		if (ii == i) {
			lb_I_KeyBase* kb = e->getKey();
			lb_I_KeyBase* temp;
			// e->getKey() Does no more increment the reference count. This avoids a leak.
			kb->queryInterface("lb_I_KeyBase", (void**) &temp, __FILE__, __LINE__);
			return kb;
		}
	}

	return NULL;
}
/*...e*/

/*...srandomLevel40void41:0:*/
int randomLevel(void) { // Pick a level on exponential distribution
  int level;
  for (level=0; (rand()%2) == 0; level++); // Do nothing
  return level;
}
/*...e*/
/*...sSkipList5858search40lb_I_KeyBase42 searchKey41:0:*/
lb_I_Unknown* SkipList::search(lb_I_KeyBase* searchKey, bool setIterator) { // Skiplist Search
  SkipNode *x = head;                  // Dummy header node

  if (head == NULL) {
	  _CL_VERBOSE << "lb_I_Unknown* SkipList::search(...) Error: head is NULL!" LOG_
	  return NULL;
  }
  if (x == NULL) {
	_LOG << "Error: NULL pointer while searching in skiplist" LOG_
	return NULL;
  }
  for (int i=level; i>=0; i--) {
    while ((x->forward[i] != NULL) && (x->forward[i]->value != NULL) && (*(x->forward[i]->value->getKey()) < searchKey)) {
      x = x->forward[i];
    }
  }
  x = x->forward[0];  // Move to actual record, if it exists

  if ((x != NULL) && (*(x->value->getKey()) == searchKey)) {
	  if (setIterator) skipiterator = x;
  	return x->value->getObject();
  } else {
  	return NULL;
  }
}
/*...e*/
/*...sSkipList5858insert40Elem newValue41:0:*/
void SkipList::insert(Elem newValue) { // Insert into skiplist
  if (head == NULL) head = new SkipNode();
  SkipNode *x = head;           // Start at header node
  int i;
  int newLevel = randomLevel(); // Select level for new node

  if (newLevel > level) {       // New node will be deepest in list
    AdjustHead(newLevel);       // Add null pointers to header
    level = newLevel;
  }
	  
  SkipNode** update = NULL;    // Update tracks end of each level
  
  update = new SkipNode* [level+1]; 

  for(i=level; i>=0; i--) { // Search for insert position
	  lb_I_Element* e = (x->forward[i] != NULL) ? x->forward[i]->value.getPtr() : NULL;
	  
	  while((x->forward[i] != NULL) && (*e < newValue->getKey())) {
		  x = x->forward[i];
		  e = x->forward[i] != NULL ? x->forward[i]->value.getPtr() : NULL;
		  
		  if ((x->forward[i] != NULL) && (x->forward[i]->value.getPtr() == NULL)) {
			  _LOG << "FATAL: Skiplist may be corrupted!" LOG_
		  }
	  }
	  update[i] = x;              // Keep track of end at level i
  }
  
  UAP(lb_I_Element, el)
  el = newValue;
  el++;
  el++;

  
  
  x = new SkipNode(newValue, newLevel); // Create new node
  
  for (i=0; i<=newLevel; i++) { // Splice into list
    x->forward[i] = update[i]->forward[i]; // Who x points to
    update[i]->forward[i] = x;             // Who y points to
  }

  if (update) {
          for (int i=0; i<=level; i++)
              update[i] = NULL;
          delete [] update;
  }
}
/*...e*/
/*...sSkipList5858remove40Elem searchKey41:0:*/
void SkipList::remove(Elem searchKey) {
    // update holds pointers to next elements of each level
    SkipNode** update = NULL;    // Update tracks end of each level
  
    update = new SkipNode* [level+1]; 
    
    SkipNode *x = head;                  // Dummy header node
    SkipNode *found = NULL;
    
    for (int i=level; i>=0; i--) {

      while ((x->forward[i] != NULL) && (*(x->forward[i]->value) < searchKey->getKey())) {
        x = x->forward[i];
      }
        
      update[i] = x;
    }

    x = x->forward[0];  // Move to actual record, if it exists
    
    if ((x != NULL) && (*(x->value) == searchKey->getKey())) found = x;
    else {
	if (update) {
	        for (int i=0; i<=level; i++)
	            update[i] = NULL;
	        delete [] update;
	}
    	return;
    }

    // element found, so rebuild list without node:
    if (*(found->value) == searchKey->getKey()) {
      for (int i=0; i<=level; i++) {
        if (update[i]->forward[i] == found) {
          update[i]->forward[i] = found->forward[i];
        }
      }
      
      // element can be freed now (would happen automatically):
      found->resetForward();
      
      if (!canDeleteObjects) found->detach();
      
      delete found;
      
      // maybe we have to downcorrect the level of the list: 
      while (level>0  &&  head->forward[level] != NULL && head->forward[level]->value==NULL) {
        level--;
      }
    }
    count--;
  
	if (update) {
	        for (int i=0; i<=level; i++)
	            update[i] = NULL;
	        delete [] update;
	}

}


/*...e*/
/*...sSkipList5858finishIteration4041:0:*/
void SkipList::finishIteration() {
	iteration = 0;
}
/*...e*/
/*...sSkipList5858can_dump4041:0:*/
int SkipList::can_dump() {
	if (count == 0) return 0;
	if (iteration == 0) { 
       	iteration = 1; 
        skipiterator = head; 
		flag = 1;
	} 

	if (skipiterator == NULL) { 
	        iteration = 0; 
	        flag = 1;
	        return 0; 
	} 
	
//	if (flag == 0) return 0;
	
	return 1;
}
/*...e*/
/*...sSkipList5858dump_next4041:0:*/
Elem SkipList::dump_next() {
	if (skipiterator != NULL) {
		Elem e = skipiterator->value.getPtr();
		
		while (e == NULL) {
			skipiterator = skipiterator->forward[0];
			if (!skipiterator) return NULL;
			e = skipiterator->value.getPtr();
		}

		skipiterator = skipiterator->forward[0];
/*...sbla:0:*/
#ifdef bla		
		for(int i=0; i<=skipiterator->myLevel && flag != 0; i++)
			if (skipiterator->forward[i] == NULL){
				printf("No more elements in skiplistn");
		        	flag = 0;
			}
#endif		
/*...e*/
		return e;
	} else {
		printf("Return NULL because skipiterator is NULLn");
		return NULL;
	}
}
/*...e*/

BEGIN_IMPLEMENT_LB_UNKNOWN(lbSkipListElement)
        ADD_INTERFACE(lb_I_Element)
END_IMPLEMENT_LB_UNKNOWN()

lbSkipListElement::lbSkipListElement() { 
	next = NULL; 
	key = NULL; 
	data = NULL;
}

lbSkipListElement::lbSkipListElement(const lb_I_Element &e) { 
	_CL_VERBOSE << "lbSkipListElement(const lb_I_Element &e) called." LOG_
	next = e.getNext(); 
	data = e.getObject();
	key = e.getKey();
}

//IMPLEMENT_LB_ELEMENT(lbSkipListElement)
void LB_STDCALL lbSkipListElement::detachData() {
	data = NULL;
}
lbSkipListElement::lbSkipListElement(const lb_I_Unknown* o, const lb_I_KeyBase* _key, bool doClone, lb_I_Element *_next) {
	data = NULL;
    next = _next;
    if (_next != NULL) {
        _next->queryInterface("lb_I_Element", (void**) &next, __FILE__, __LINE__);
    }
	if (o != NULL) {
		if (doClone) {
			data = o->clone(__FILE__, __LINE__);
			if (data->getRefCount() > 1) {
				_CL_VERBOSE << "Warning: Refcount of data after cloning is more than 1 !!!" LOG_
			}
		} else {
			o->queryInterface("lb_I_Unknown", (void**) &data, __FILE__, __LINE__);
		}
	}

	if (_key == NULL) {
		_LOGERROR << "lbSkipListElement::lbSkipListElement(o, _key, ...) did not get a key, but expected.!" LOG_
		key = NULL;
		return;
	}
	
    lb_I_Unknown* uk_key = NULL;
    key = (lb_I_KeyBase*) _key->clone(__FILE__, __LINE__);
	_CL_VERBOSE << "Added an element with key value of " << key->charrep() LOG_
    if (key != NULL) {
    	if (key->getRefCount() > 1) {
			_CL_VERBOSE << "Warning: Refcount of key after cloning is more than 1 !!!" LOG_
        }
    }
    if (key == NULL) _CL_LOG << "Key cloning in constructor failed. May be a memory problem" LOG_
}

lbSkipListElement::~lbSkipListElement() {
	char ptr[20] = "";
	char ptr1[20] = "";
	sprintf(ptr, "%p", this);
	sprintf(ptr1, "%p", data);
	if (key != NULL) {
		if (key->getRefCount() > 1) {
			_CL_VERBOSE << "Warning: Key wouldn't deleted in container element! (References: " << key->getRefCount() << ")(" << key->charrep() << ")" LOG_
		}
		if (key->deleteState() != 1) {
			_CL_VERBOSE << "Warning: Key wouldn't deleted in container element! (References: " << key->getRefCount() << ")(" << key->charrep() << ")" LOG_
		}
		RELEASE(key);
	}
	if (data != NULL) {
		if (data->getRefCount() > 1) {
			_CL_VERBOSE << "Warning: Data wouldn't deleted in container element! (References: " << data->getRefCount() << ")" LOG_
		}
		if (data->deleteState() != 1) {
			_CL_VERBOSE << "Warning: Data wouldn't deleted in container element! (References: " << data->getRefCount() << ")" LOG_
		}
		RELEASE(data);
	}
	key = NULL;
	
}

lb_I_Unknown* lbSkipListElement::getObject() const {
    lb_I_Unknown* uk = NULL;
    if(data == NULL) {
    	_LOGERROR << "FATAL: Element has no data. Could not return from NULL pointer!!" LOG_
    	return NULL;
    }
    if(!_TRMemValidate(data)) {
    	char buf[20] = "";
    	sprintf(buf, "%p", data);
    	_LOGERROR << "Error: Skiplist element data pointer is invalid! (" << buf << ", lbSkipListElement: " << data->getClassName() << ")" LOG_
    }
    data->queryInterface("lb_I_Unknown", (void**) &uk, __FILE__, __LINE__);
    //_CL_VERBOSE << "Object of " << uk->getClassName() << " has " << uk->getRefCount() << " references." LOG_
    return uk;
}

lb_I_KeyBase* LB_STDCALL lbSkipListElement::getKey() const {
	lb_I_KeyBase* kbase = NULL;
	if(key == NULL) _CL_LOG << "ERROR: Element has no key. Could not return from NULL pointer!!" LOG_
        key->queryInterface("lb_I_KeyBase", (void**) &kbase, __FILE__, __LINE__);
	_CL_VERBOSE << "Key of " << key->getClassName() << " has " << key->getRefCount() << " references. Value is " << kbase->charrep() LOG_
	key->release(__FILE__, __LINE__);
	return kbase;
}

void LB_STDCALL lbSkipListElement::setNext(lb_I_Element *e) {
	e->queryInterface("lb_I_Element", (void**) &next, __FILE__, __LINE__);
}

lb_I_Element* LB_STDCALL lbSkipListElement::getNext() const {
	return next;
}
int LB_STDCALL lbSkipListElement::equals(const lb_I_Element* a) const {
	return 0;
}

int LB_STDCALL lbSkipListElement::equals(const lb_I_KeyBase* _key) const {
	return (*key == _key);
}
int LB_STDCALL lbSkipListElement::lessthan(const lb_I_KeyBase* _key) const {
	return (*key < _key);
}



lbErrCodes LB_STDCALL lbSkipListElement::setData(lb_I_Unknown* uk) {
	_CL_LOG << "lbSkipListElement::setData(...) not implemented yet" LOG_

	return ERR_NOT_IMPLEMENTED;
}
