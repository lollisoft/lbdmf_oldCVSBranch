
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

/** \brief class FKPK_Mapping.
 * Documentation for FKPK_Mapping
 */
class FKPK_MappingModel : public lb_I_FKPK_Mapping {
public:
	FKPK_MappingModel();
	virtual ~FKPK_MappingModel();

	long		LB_STDCALL addFKPK_Mapping(const char* _pktable, const char* _pkname, const char* _fktable, const char* _fkname,  long _FKPK_MappingID = -1);

	bool		LB_STDCALL selectFKPK_Mapping(long _id);
	int			LB_STDCALL getFKPK_MappingCount();
	bool		LB_STDCALL hasMoreFKPK_Mapping();
	void		LB_STDCALL setNextFKPK_Mapping();
	void		LB_STDCALL finishFKPK_MappingIteration();


	char*		LB_STDCALL get_pktable();
	char*		LB_STDCALL get_pkname();
	char*		LB_STDCALL get_fktable();
	char*		LB_STDCALL get_fkname();

	long		LB_STDCALL get_id();

	bool		LB_STDCALL ismarked();
	void		LB_STDCALL mark();
	void		LB_STDCALL unmark();

	void		LB_STDCALL deleteUnmarked();
	void		LB_STDCALL deleteMarked();

	DECLARE_LB_UNKNOWN()
	DECLARE_EXTENSIBLEOBJECT()

	UAP(lb_I_Container, objectExtensions)
	

	UAP(lb_I_Container, FKPK_Mapping)
	

	UAP(lb_I_String, currentpktable)
			
	UAP(lb_I_String, currentpkname)
			
	UAP(lb_I_String, currentfktable)
			
	UAP(lb_I_String, currentfkname)
			

	
	UAP(lb_I_Long, currentFKPK_MappingID)

	UAP(lb_I_Long, marked)
};

DECLARE_FUNCTOR(instanceOflbFKPK_MappingModel)
