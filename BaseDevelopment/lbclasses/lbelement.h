


/************************************************************************************************************
 * $Locker:  $
 * $Revision: 1.1 $
 * $Name:  $
 * $Id: lbelement.h,v 1.1 2000/03/06 20:54:58 lolli Exp $
 * $Log: lbelement.h,v $
 * Revision 1.1  2000/03/06 20:54:58  lolli
 * Initial revision
 *
 * Revision 1.3  1999/12/14 21:09:02  lolli
 * Bugfixes
 *
 * Revision 1.2  1999/11/25 20:48:49  lothar
 * Checked in due to working directory change
 *
 * Revision 1.1  1999/10/08 21:27:00  Administrator
 * Initial
 *
 ************************************************************************************************************/

#ifndef LB_ELEMENT
#define LB_ELEMENT

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


#include <stdlib.h>

/**
 * lbContainer represents the interface to all containers used.
 * 
 *
 *
 *
 */

class lbKeyBase;
class lbObject;

class DLLEXPORT lbElement {
public:
    lbElement(const lbObject &o, const lbKeyBase &_key, lbElement *_next=NULL);
    lbElement(const lbElement &e) { next = e.getNext(); }
    virtual ~lbElement();

    lbElement* getNext() const {return next; }
    void setNext(lbElement *e){ next = e; }
    lbObject* getObject() const;

//    lbKeyBase &getKey() const { return *key; }
    lbKeyBase *getKey() const
    {
        if (!key) printf("Key in lbElement is null\n");
        return key;
    }

    int operator == (const lbElement &a) const;

    int operator == (const lbKeyBase &key) const;

private:

    lbElement* next;
    lbObject* data;
    lbKeyBase* key;
};
#endif //LB_ELEMENT
