#define LB_TOOLS_DLL

#include <lbInclude.h>

// TLS index of the slot where we store the pointer to the current thread
static DWORD s_tlsThisThread = 0xFFFFFFFF;

/*...slbThreadInternal:0:*/
/*...sclass lbThreadInternal:0:*/
class lbThreadInternal {
public:
    lbThreadInternal()
    {
        lb_hThread = 0;
    }

    // create a new (suspended) thread (for the given thread object)
    lbThreadError Create(lbThread *thread);

    // suspend/resume/terminate
    lbThreadError suspend();
    lbThreadError resume();
    // thread state

    // thread handle and id
    HANDLE getHandle() const { return lb_hThread; }
    DWORD  getId() const { return lb_ThreadId; }

    // thread function
    static DWORD WinThreadStart(lbThread *thread);

private:
    HANDLE        lb_hThread;    // handle of the thread
    DWORD         lb_ThreadId;  // thread id
};
/*...e*/

/*...slbThreadInternal\58\\58\Create\40\lbThread \42\thread\41\:0:*/
lbThreadError lbThreadInternal::Create(lbThread *thread) {
    lb_hThread = ::CreateThread
                  (
                    NULL,                               // default security
                    0,                                  // default stack size
                    (LPTHREAD_START_ROUTINE)            // thread entry point
                    lbThreadInternal::WinThreadStart,   //
                    (LPVOID)thread,                     // parameter
                    CREATE_SUSPENDED,                   // flags
                    &lb_ThreadId                        // [out] thread id
                  );

    if ( lb_hThread == NULL )
    {
    	// Do some logging
    	LOG("lbThreadInternal: Could not create a thread");

        return LB_THREAD_ERROR;
    }
    if ( ::SetThreadPriority(lb_hThread, THREAD_PRIORITY_NORMAL) == 0 )
    {
    	LOG("lbThreadInternal: Could not set ThreadPriority");
    	return LB_THREAD_ERROR;
    }
    
    return LB_THREAD_NO_ERROR;
}
/*...e*/

/*...slbThreadInternal\58\\58\suspend\40\\41\:0:*/
lbThreadError lbThreadInternal::suspend() {
    DWORD nSuspendCount = ::SuspendThread(lb_hThread);
    if ( nSuspendCount == (DWORD)-1 )
    {
        LOG("lbThreadInternal: Can not suspend thread");

        return LB_THREAD_ERROR;
    }

//    m_state = STATE_PAUSED;

    return LB_THREAD_NO_ERROR;
}
/*...e*/

/*...slbThreadInternal\58\\58\resume\40\\41\:0:*/
lbThreadError lbThreadInternal::resume() {
    DWORD nSuspendCount = ::ResumeThread(lb_hThread);
    if ( nSuspendCount == (DWORD)-1 )
    {
        LOG("lbThreadInternal: Can not resume thread");

        return LB_THREAD_ERROR;
    }

//    m_state = STATE_RUNNING;

    return LB_THREAD_NO_ERROR;
}
/*...e*/

/*...slbThreadInternal\58\\58\WinThreadStart\40\lbThread \42\thread\41\:0:*/
DWORD lbThreadInternal::WinThreadStart(lbThread *thread)
{
    // store the thread object in the TLS
    if ( !::TlsSetValue(s_tlsThisThread, thread) )
    {
        LOG("Can not start thread: error writing TLS.");

        return (DWORD)-1;
    }

    DWORD ret = (DWORD)thread->Entry();
    //thread->p_ThreadImpl->SetState(STATE_EXITED);
    LOG("lbThreadInternal: Do not call OnExit()");
    //thread->OnExit();

    delete thread;

    return ret;
}
/*...e*/
/*...e*/
/*...slbThread:0:*/
lbThread::lbThread() {
}

lbThread::~lbThread() {
}

lbThreadError lbThread::run() {
/*...sCreate if needed:2:*/
  if (pThreadImpl->getHandle() == NULL) {
  	pThreadImpl->Create(this);
  }
/*...e*/
/*...sLet it run:2:*/
  return pThreadImpl->resume();
/*...e*/
}

lbThreadError lbThread::stop() {
  return LB_THREAD_ERROR;
}
/*...e*/

