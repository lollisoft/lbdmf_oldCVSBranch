


/************************************************************************************************************
 * $Locker:  $
 * $Revision: 1.1.1.1 $
 * $Name:  $
 * $Id: lbobject.h,v 1.1.1.1 2000/03/06 20:54:58 lolli Exp $
 * $Log: lbobject.h,v $
 * Revision 1.1.1.1  2000/03/06 20:54:58  lolli
 * Imported
 *
 * Revision 1.3  2000/01/23 14:35:04  lolli
 * Corrected error in revision conflict
 *
 * Revision 1.1  1999/10/08 21:27:01  Administrator
 * Initial
 *
 ************************************************************************************************************/

#ifndef _LB_OBJECT_
#define _LB_OBJECT_

#undef DLLEXPORT

#ifdef LB_CONTAINER_DLL

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllexport)
#endif

#endif

#ifndef LB_CONTAINER_DLL

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllimport)
#endif

#endif


#include <stdio.h>

//class lbKeyBase;

class DLLEXPORT lbObject {
public:
    lbObject() {
		name = NULL;
		// Set to undefined state
		OTyp = LB_OBJECT;
	}

	lbObject(const lbObject &o) {
		setName(o.getName());
	}
    
    virtual ~lbObject() {}

	/**
	 * The type of an object
	 */
	enum ObjectTyp { LB_OBJECT, LB_GUIOBJECT, LB_WXGUIOBJECT, LB_DATA_TRANSFER_OBJECT };

	ObjectTyp getType() const;

	/**
	 * A object has a name
	 */
    void setName(const char* d);
    const char* getName() const;

	/**
	 * Abstract functions
	 */
	virtual void setType() = 0;
	virtual lbObject* clone() const = 0;

	

protected:

    char *name;
	ObjectTyp OTyp;
};




#endif //LB_OBJECT
