#ifndef LB_APPBUS
#define LB_APPBUS

#undef DLLEXPORT

/*...s\35\ifdef APPBUS_DLL:0:*/
#ifdef APPBUS_DLL

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllexport)
#endif

#endif
/*...e*/

/*...s\35\ifndef APPBUS_DLL:0:*/
#ifndef APPBUS_DLL

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllimport)
#endif

#endif
/*...e*/

/*...sbla:0:*/
#ifdef bla
// Here are some statis defined to enable communication on the app bus
enum {
	LB_ABBBUS_ERR
} lbAppBusStatus;
#endif
/*...e*/
/*...slbAppBus:0:*/
class lbTransfer;

class lbAppBus {

public:
	lbAppBus();
	virtual ~lbAppBus();

	lbTransfer* getServerConnection(const char* server);

protected:

	char* bus_master_adr;
	u_short bus_master_port;
};
/*...e*/

/*...slbAppBusClient:0:*/

class lbAppBusClient : public lbAppBus {
public:
	lbAppBusClient();
	virtual ~lbAppBusClient();

	void AnounceClient();
};
/*...e*/

/*...slbAppBusServer:0:*/
class lbAppBusServer : public lbAppBus {
public:
	lbAppBusServer();
	virtual ~lbAppBusServer();
};
/*...e*/
#endif
