#define LB_CONTAINER_DLL

#include <string.h>
#include <lbInclude.h>


void lbObject::setName(const char* d) {
	if (name != NULL) delete name;
    name = strdup(d);
}

const char* lbObject::getName() const {
    return name;
}

lbObject::ObjectTyp lbObject::getType() const {
	if (OTyp == LB_OBJECT) {
		LOG("Derived object has not been initialized correctly!");
	}
	return OTyp;
}
