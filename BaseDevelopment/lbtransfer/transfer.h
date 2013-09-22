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
#ifndef LB_TRANSFER
#define LB_TRANSFER

#include <lbInterfaces-sub-transfer.h>

//class lbComponentDictionary;
class lbSocket;

enum LB_TRANSFER_STATE {
	LB_STATE_UNINITIALIZED,
	LB_STATE_CONNECTED,
};

/*...slbTransferDataObject:0:*/
/**
 * This class is needed for the container
 */

class lbTransferDataObject : public lb_I_Transfer_DataObject { // : public lbObject {
public:
	lbTransferDataObject();
	virtual ~lbTransferDataObject();

	void LB_STDCALL setTransferData(pLB_TRANSFER_DATA pData);
	pLB_TRANSFER_DATA LB_STDCALL getTransferData() const;

	DECLARE_LB_UNKNOWN()

private:
	void setType();
#ifdef USE_CLONE
	lbObject* clone() const;
#endif
	pLB_TRANSFER_DATA mydata;
	ObjectTyp OTyp;
};
/*...e*/
/*...slbTransferData:0:*/
/**
 * This class represents the buffer to be send over a socket. A object of type lbObject
 * should be able to created over a constructor with a parameter of this type. 
 */
class lbTransferData : public
		lb_I_Transfer_Data
{
public:
	lbTransferData();
	virtual ~lbTransferData();
    lbTransferData(const lb_I_Transfer_Data & t);
	lb_I_Transfer_Data& LB_STDCALL assign(lb_I_Transfer_Data const & t);

	void LB_STDCALL setServerSide(int _serverside);
	
	DECLARE_LB_UNKNOWN()

	/**
	 * Packet functions to form packets fit to internet packet size.
	 * Use hasMorePackets() for the while 
	 */

	int LB_STDCALL hasMorePackets() const;
	pLB_TRANSFER_DATA LB_STDCALL getNextPacket() const;

	int LB_STDCALL getPacketCount() const;
	LB_PACKET_TYPE LB_STDCALL getNextPacketType();

	int LB_STDCALL getCurrentPos() const;

	int LB_STDCALL addPacket(pLB_TRANSFER_DATA data);

	int LB_STDCALL resetPositionCount();
	int LB_STDCALL incrementPosition();
	int LB_STDCALL getPacketType(LB_PACKET_TYPE & type);

	int LB_STDCALL deleteAll();

	bool LB_STDCALL isServerSide() const { return serverside == 1; }

	DWORD LB_STDCALL getClientPid() const  { return clientPid; }
	void LB_STDCALL setClientPid(DWORD _pid) { clientPid = _pid; }

	char* LB_STDCALL getClientHost() const { return clientHost->charrep(); }
	void LB_STDCALL setClientHost(char* host) { *clientHost = host; }

	DWORD LB_STDCALL getClientTid() const { return clientTid; }
	void LB_STDCALL setClientTid(DWORD _tid) { clientTid = _tid; }

	lbErrCodes LB_STDCALL requestString(char* ident, char*& data);
	lbErrCodes LB_STDCALL requestBoolean(char* ident, bool& data);
	
	lbErrCodes LB_STDCALL requestString(char* ident);
	
	lbErrCodes LB_STDCALL requestInteger(char* ident, int& data);
	
	lbErrCodes LB_STDCALL requestULong(char* ident, unsigned long& data);

	lbErrCodes LB_STDCALL makeProtoErrAnswer(const char* msg, const char* where);
/*...ssetters:8:*/
	/**
	 * Data member operations
	 */

	void LB_STDCALL add(int i);
	void LB_STDCALL add(const char* c);
	void LB_STDCALL add(short s);
	void LB_STDCALL add(long l);
	void LB_STDCALL add(unsigned short us);
	void LB_STDCALL add(unsigned long ul);
	void LB_STDCALL add(const void* buf, int len);
/*...e*/

/*...sgetters:8:*/
	lbErrCodes LB_STDCALL get(int& i);
	lbErrCodes LB_STDCALL get(char* & c);
	lbErrCodes LB_STDCALL get(short & s);
	lbErrCodes LB_STDCALL get(long & l);
	lbErrCodes LB_STDCALL get(unsigned short & us);
	lbErrCodes LB_STDCALL get(unsigned long & ul);

	lbErrCodes LB_STDCALL get(void* & v, int & len);
/*...e*/
	
	/**
	 * The really function who is adding
	 */
	void LB_STDCALL LB_STDCALL add(const void* buf, int len, LB_PACKET_TYPE type);


	/**
	 * Use dictionary yet
	 */

	UAP(lb_I_Container, elements)
	//UAP(lb_I_Container, elementscopy)
	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Integer, intKey)
	 
/*	 
	lbComponentDictionary* elements;
	lbComponentDictionary* elementscopy;
*/	
	int packet_count;
	int currentPos;
public:	
	UAP(lb_I_String, clientHost)
	DWORD clientPid;
	DWORD clientTid;
	int serverside;
	
	lbCritSect* transferSection;
};
/*...e*/
/*...slbTransfer:0:*/
class lbTransfer : public lb_I_Transfer {
public:
	lbTransfer();
	virtual ~lbTransfer();

	DECLARE_LB_UNKNOWN()

	/**
	 * The target parameter is build up like an internet address.
	 * Exsample: //anakin/service/subservice
	 */
	lbErrCodes LB_STDCALL init(char *target, bool asServer);

	lbErrCodes LB_STDCALL close();

	int LB_STDCALL isConnected();

	/**
	 * Wait for a request after having got a connectin.
	 */
	lb_I_Transfer* LB_STDCALL accept();

	void LB_STDCALL operator<< (lb_I_Transfer_Data* req);
	void LB_STDCALL operator>> (lb_I_Transfer_Data* res);

	/**
	 * This function allows checking for validness of this instance
	 */
	int LB_STDCALL isValid();

	int LB_STDCALL gethostname(lb_I_String* name);
	
	lbErrCodes LB_STDCALL getLastError();
	int LB_STDCALL setSockConnection(lb_I_Socket* s);

private:
	lbTransfer(lb_I_Transfer* t);
	
	int recv(lb_I_Transfer_Data* data);
	int send(lb_I_Transfer_Data* data);

	int resetServerStateMachine();
	lbErrCodes sendDatatype(char* type);
	int waitforAnswer(char* answer);
	int sendDataCount(int c);
	int sendBuffer(byte* buf, int len);
	int sendString(char* type);
	int waitForString(char* & string);
	int waitForDataCount(int & c);
	lbErrCodes waitForDatatype(char* & result);
	int waitForBuffer(byte * & buffer, int & len);

	UAP(lb_I_String, hostName)
	UAP(lb_I_String, portName)
	
	UAP(lb_I_Socket, sock)
	int laststate;
	int connected;
	
	LB_TRANSFER_STATE state;
	
	lbErrCodes lastError;
	
	/**
	 * This authentification parameters are initialized once per
	 * thread. Then it is used when ever data is transferred.
	 */
	char AuthUser[100];
	char AuthPass[100];
};
/*...e*/

char* getStringFromEnumeration(LB_PACKET_TYPE type);

/*...sifdef __cplusplus:0:*/
#ifdef __cplusplus
extern "C" {
#endif
/*...e*/

DECLARE_FUNCTOR(instanceOflbTransfer)
DECLARE_FUNCTOR(instanceOflbTransferData)
DECLARE_FUNCTOR(instanceOflbTransferDataObject)

/*...sendif __cplusplus:0:*/
#ifdef __cplusplus
}
#endif
/*...e*/

#endif // LB_TRANSFER
