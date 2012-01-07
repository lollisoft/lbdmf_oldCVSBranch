
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

/** \brief class Action_Parameters.
 * Documentation for Action_Parameters
 */
class lbAction_ParametersModel : public lb_I_Action_Parameters {
public:
	lbAction_ParametersModel();
	virtual ~lbAction_ParametersModel();

	long		LB_STDCALL addAction_Parameters(const char* _name, const char* _value, const char* _interface, const char* _description, long _actionid,  long _Action_ParametersID = -1);

	bool		LB_STDCALL selectAction_Parameters(long _id);
	int			LB_STDCALL getAction_ParametersCount();
	bool		LB_STDCALL hasMoreAction_Parameters();
	void		LB_STDCALL setNextAction_Parameters();
	void		LB_STDCALL finishAction_ParametersIteration();


	char*		LB_STDCALL get_name();
	char*		LB_STDCALL get_value();
	char*		LB_STDCALL get_interface();
	char*		LB_STDCALL get_description();
	long		LB_STDCALL get_actionid();
	

	long		LB_STDCALL get_id();

	bool		LB_STDCALL ismarked();
	void		LB_STDCALL mark();
	void		LB_STDCALL unmark();

	void		LB_STDCALL deleteUnmarked();
	void		LB_STDCALL deleteMarked();

	void		LB_STDCALL setOperator(lb_I_Unknown* db);
	lbErrCodes	LB_STDCALL ExecuteOperation(const char* operationName);

	DECLARE_LB_UNKNOWN()
	DECLARE_EXTENSIBLEOBJECT()
	
	UAP(lb_I_Container, Action_Parameters)
	

	UAP(lb_I_String, currentname)
			
	UAP(lb_I_String, currentvalue)
			
	UAP(lb_I_String, currentinterface)
			
	UAP(lb_I_String, currentdescription)
			
	UAP(lb_I_Long, currentactionid)
	

	
	UAP(lb_I_Long, currentAction_ParametersID)

	UAP(lb_I_Long, marked)
};

DECLARE_FUNCTOR(instanceOflbAction_ParametersModel)
