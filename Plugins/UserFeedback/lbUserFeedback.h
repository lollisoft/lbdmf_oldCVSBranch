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
 p-Mail: See my current address on http://www.lollisoft.de/index.php?module=xarpages&func=display&pid=6
 
 */
/*...e*/

/**
 * \brief Provides an event handler to transform XML via XSLT.
 */
class lbUserFeedback : 
public lb_I_VisitableHelper,
public lb_I_EventHandler
{
public:
	lbUserFeedback();
	virtual ~lbUserFeedback();

	DECLARE_LB_UNKNOWN()
	
	lbErrCodes				LB_STDCALL registerEventHandler(lb_I_Dispatcher* disp);	
	lb_I_Unknown*			LB_STDCALL getUnknown();

	lbErrCodes				LB_STDCALL SendPositiveFeedback(lb_I_Unknown* uk);
	lbErrCodes				LB_STDCALL SendNegativeFeedback(lb_I_Unknown* uk);
	lbErrCodes				LB_STDCALL SendCoolIdeaFeedback(lb_I_Unknown* uk);
	lbErrCodes				LB_STDCALL SendPuzzledFeedback(lb_I_Unknown* uk);
};

