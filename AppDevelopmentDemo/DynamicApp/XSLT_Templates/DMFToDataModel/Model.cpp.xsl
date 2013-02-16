<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:xmi="http://schema.omg.org/spec/XMI/2.1" xmlns:lbDMF="http:///schemas/lbDMF/1"  xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<!--
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2002-2009  Lothar Behrens (lothar.behrens@lollisoft.de)

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
-->
<xsl:import href="../include/exsl.xsl"/>
<xsl:output method="text" indent="no"/>

<xsl:variable name="ApplicationID" select="//lbDMF/@applicationid"/>
<xsl:variable name="OrginalApplicationName" select="//lbDMF/applications/application[@ID=$ApplicationID]/@name"/>
<xsl:variable name="ApplicationName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$OrginalApplicationName"/>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'-'"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'>'"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="' '"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
</xsl:variable>
<!-- here is the template that does the replacement -->
<xsl:template name="SubstringReplace">
	<xsl:param name="stringIn"/>
	<xsl:param name="substringIn"/>
	<xsl:param name="substringOut"/>
	<xsl:choose>
		<xsl:when test="contains($stringIn,$substringIn)">
			<xsl:value-of select="concat(substring-before($stringIn,$substringIn),$substringOut)"/>
			<xsl:call-template name="SubstringReplace">
				<xsl:with-param name="stringIn" select="substring-after($stringIn,$substringIn)"/>
				<xsl:with-param name="substringIn" select="$substringIn"/>
				<xsl:with-param name="substringOut" select="$substringOut"/>
			</xsl:call-template>
		</xsl:when>
		<xsl:otherwise>
			<xsl:value-of select="$stringIn"/>
		</xsl:otherwise>
	</xsl:choose>
</xsl:template>

<xsl:template name="Model.cpp">
	<xsl:param name="ApplicationID"/>
	<xsl:param name="FormularID"/>
	<xsl:param name="FormName"/>
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

#ifdef LBDMF_PREC
#include &lt;lbConfigHook.h&gt;
#endif

#include &lt;stdio.h&gt;
#include &lt;string.h&gt;
#ifndef UNIX
#include &lt;windows.h&gt;
#endif
#ifdef UNIX
#endif

#ifndef LBDMF_PREC
#include &lt;lbConfigHook.h&gt;
#endif

/*...sLB_DMFDATAMODEL_DLL scope:0:*/
#define LB_DMFDATAMODEL_DLL
#include &lt;lbdmfdatamodel-module.h&gt;
/*...e*/
#include &lt;lbInterfaces-<xsl:value-of select="$ApplicationName"/>.h&gt;
#include &lt;Generated_EntityModel<xsl:value-of select="$FormName"/>.h&gt;

IMPLEMENT_FUNCTOR(instanceOf<xsl:value-of select="$FormName"/>Model, <xsl:value-of select="$FormName"/>Model)

BEGIN_IMPLEMENT_LB_UNKNOWN(<xsl:value-of select="$FormName"/>Model)
	ADD_INTERFACE(lb_I_<xsl:value-of select="$FormName"/>)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(<xsl:value-of select="$FormName"/>Model)

<xsl:value-of select="$FormName"/>Model::<xsl:value-of select="$FormName"/>Model() {
	
	REQUEST(getModuleInstance(), lb_I_Container, <xsl:value-of select="$FormName"/>)
	REQUEST(getModuleInstance(), lb_I_Container, objectExtensions)

<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]"><xsl:variable name="FieldName" select="@name"/> <xsl:variable name="TableName" select="@tablename"/>
<xsl:choose><xsl:when test="@isfk='1'"><xsl:value-of select="'    '"/>REQUEST(getModuleInstance(), lb_I_Long, current<xsl:value-of select="@name"/>)
</xsl:when><xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">// Special column <xsl:value-of select="@name"/>
</xsl:when>
<xsl:otherwise>
<xsl:choose><xsl:when test="@dbtype='Bit'"><xsl:value-of select="'    '"/>REQUEST(getModuleInstance(), lb_I_Boolean, current<xsl:value-of select="@name"/>)
</xsl:when><xsl:when test="@dbtype='Float'"><xsl:value-of select="'    '"/>REQUEST(getModuleInstance(), lb_I_Float, current<xsl:value-of select="@name"/>)
</xsl:when><xsl:when test="@dbtype='Integer'"><xsl:value-of select="'    '"/>REQUEST(getModuleInstance(), lb_I_Long, current<xsl:value-of select="@name"/>)
</xsl:when><xsl:when test="@dbtype='String'"><xsl:value-of select="'    '"/>REQUEST(getModuleInstance(), lb_I_String, current<xsl:value-of select="@name"/>)
</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>

</xsl:for-each>
	
	REQUEST(getModuleInstance(), lb_I_Long, current<xsl:value-of select="$FormName"/>ID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE &lt;&lt; "<xsl:value-of select="$FormName"/>Model::<xsl:value-of select="$FormName"/>Model() called." LOG_
}

<xsl:value-of select="$FormName"/>Model::~<xsl:value-of select="$FormName"/>Model() {
	_CL_VERBOSE &lt;&lt; "<xsl:value-of select="$FormName"/>Model::~<xsl:value-of select="$FormName"/>Model() called." LOG_
}

lbErrCodes LB_STDCALL <xsl:value-of select="$FormName"/>Model::setData(lb_I_Unknown*) {
	_LOG &lt;&lt; "Error: <xsl:value-of select="$FormName"/>Model::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

#ifdef bla
lb_I_ExtensionObject* LB_STDCALL <xsl:value-of select="$FormName"/>Model::getExtension(lb_I_String* contextnamespace) {
	// Lookup the matching extension by the context namespace.
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP_REQUEST(getModuleInstance(), lb_I_String, CNS)
	*CNS = contextnamespace;
	*CNS += "_For_<xsl:value-of select="$FormName"/>";
	
	UAP(lb_I_KeyBase, key)
	QI(CNS, lb_I_KeyBase, key)
	
	if (objectExtensions-&gt;exists(*&amp;key)) {
		UAP(lb_I_ExtensionObject, ex)
		UAP(lb_I_KeyBase, key)
		
		uk = objectExtensions->getElement(*&amp;key);
		QI(uk, lb_I_ExtensionObject, ex)
		ex++;
		return ex;
	}
		
	AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_ExtensionObject, dbbackend, extension, "'database plugin'")
	if (extension == NULL) {
		_LOG &lt;&lt; "Error: Did not find extension object for given namespace " &lt;&lt; CNS->charrep() LOG_
		return NULL;
	}
	extension++;
	return extension.getPtr();
}

lb_I_ExtensionObject* LB_STDCALL <xsl:value-of select="$FormName"/>Model::getExtension(const char* contextnamespace) {
/*
	These extensions may be supported until yet. At least the following are required.

	Required
	
	ADD_PLUGIN(lbPluginInputStream,			InputStreamVisitor)
	ADD_PLUGIN(lbPluginDatabaseInputStream,	DatabaseInputStreamVisitor)
	ADD_PLUGIN(lbPluginOutputStream,		OutputStreamVisitor)
	ADD_PLUGIN(lbPluginXMLOutputStream,		XMLOutputStreamVisitor)

	May
	
	ADD_PLUGIN(lbPluginXMLInputStream,		XMLInputStreamVisitor)
	ADD_PLUGIN(lbPluginJSONOutputStream,	JSONOutputStreamVisitor)
	ADD_PLUGIN(lbPluginJSONInputStream,		JSONInputStreamVisitor)
*/
	UAP_REQUEST(getModuleInstance(), lb_I_String, CNS)
	*CNS = contextnamespace;
	return getExtension(*&amp;CNS);
}

	
lbErrCodes LB_STDCALL <xsl:value-of select="$FormName"/>Model::addExtension(lb_I_String* contextnamespace, lb_I_ExtensionObject* extension) {

}

lbErrCodes LB_STDCALL <xsl:value-of select="$FormName"/>Model::addExtension(const char* contextnamespace, lb_I_ExtensionObject* extension) {

}
#endif

long  LB_STDCALL <xsl:value-of select="$FormName"/>Model::add(<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]"><xsl:variable name="FieldName" select="@name"/><xsl:variable name="TableName" select="@tablename"/>
<xsl:choose><xsl:when test="@isfk='1'">long _<xsl:value-of select="$FieldName"/>, </xsl:when>
<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">/* Special column _<xsl:value-of select="@name"/> */</xsl:when>
<xsl:otherwise><xsl:choose>
<xsl:when test="@dbtype='Bit'">bool _<xsl:value-of select="$FieldName"/>, </xsl:when>
<xsl:when test="@dbtype='Float'">float _<xsl:value-of select="$FieldName"/>, </xsl:when>
<xsl:when test="@dbtype='Integer'">long _<xsl:value-of select="$FieldName"/>, </xsl:when>
<xsl:when test="@dbtype='String'">const char* _<xsl:value-of select="$FieldName"/>, </xsl:when>
</xsl:choose>
	</xsl:otherwise>
</xsl:choose>

</xsl:for-each> long _<xsl:value-of select="$FormName"/>ID) {
	lbErrCodes err = ERR_NONE;

<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]"><xsl:variable name="FieldName" select="@name"/> <xsl:variable name="TableName" select="@tablename"/>
<xsl:choose><xsl:when test="@isfk='1'"><xsl:value-of select="'    '"/>UAP_REQUEST(getModuleInstance(), lb_I_Long, __<xsl:value-of select="@name"/>)
</xsl:when><xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">// Special column __<xsl:value-of select="@name"/>
</xsl:when>
<xsl:otherwise>
<xsl:choose><xsl:when test="@dbtype='Bit'"><xsl:value-of select="'    '"/>UAP_REQUEST(getModuleInstance(), lb_I_Boolean, __<xsl:value-of select="@name"/>)
</xsl:when><xsl:when test="@dbtype='Float'"><xsl:value-of select="'    '"/>UAP_REQUEST(getModuleInstance(), lb_I_Float, __<xsl:value-of select="@name"/>)
</xsl:when><xsl:when test="@dbtype='Integer'"><xsl:value-of select="'    '"/>UAP_REQUEST(getModuleInstance(), lb_I_Long, __<xsl:value-of select="@name"/>)
</xsl:when><xsl:when test="@dbtype='String'"><xsl:value-of select="'    '"/>UAP_REQUEST(getModuleInstance(), lb_I_String, __<xsl:value-of select="@name"/>)
</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>

</xsl:for-each>

	UAP_REQUEST(getModuleInstance(), lb_I_Long, __<xsl:value-of select="$FormName"/>ID)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]"><xsl:variable name="FieldName" select="@name"/> <xsl:variable name="TableName" select="@tablename"/>
<xsl:choose><xsl:when test="@isfk='1'"><xsl:value-of select="'    '"/>__<xsl:value-of select="@name"/>-&gt;setData(_<xsl:value-of select="@name"/>);
</xsl:when><xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">// Special column <xsl:value-of select="@name"/>
</xsl:when>
<xsl:otherwise>
<xsl:choose><xsl:when test="@dbtype='Bit'"><xsl:value-of select="'    '"/>__<xsl:value-of select="@name"/>-&gt;setData(_<xsl:value-of select="@name"/>);
</xsl:when><xsl:when test="@dbtype='Float'"><xsl:value-of select="'    '"/>__<xsl:value-of select="@name"/>-&gt;setData(_<xsl:value-of select="@name"/>);
</xsl:when><xsl:when test="@dbtype='Integer'"><xsl:value-of select="'    '"/>__<xsl:value-of select="@name"/>-&gt;setData(_<xsl:value-of select="@name"/>);
</xsl:when><xsl:when test="@dbtype='String'"><xsl:value-of select="'    '"/>*__<xsl:value-of select="@name"/> = _<xsl:value-of select="@name"/>;
</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>

</xsl:for-each>
	
	__<xsl:value-of select="$FormName"/>ID-&gt;setData(_<xsl:value-of select="$FormName"/>ID);

<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]"><xsl:variable name="FieldName" select="@name"/> <xsl:variable name="TableName" select="@tablename"/>
<xsl:choose><xsl:when test="@isfk='1'">
<xsl:value-of select="'    '"/>*paramname = "<xsl:value-of select="@name"/>";
<xsl:value-of select="'    '"/>param-&gt;setUAPLong(*&amp;paramname, *&amp;__<xsl:value-of select="@name"/>);
</xsl:when><xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
// Special column <xsl:value-of select="@name"/>
</xsl:when>
<xsl:otherwise>
<xsl:choose><xsl:when test="@dbtype='Bit'">
<xsl:value-of select="'    '"/>*paramname = "<xsl:value-of select="@name"/>";
<xsl:value-of select="'    '"/>param-&gt;setUAPBoolean(*&amp;paramname, *&amp;__<xsl:value-of select="@name"/>);
</xsl:when><xsl:when test="@dbtype='Float'">
<xsl:value-of select="'    '"/>*paramname = "<xsl:value-of select="@name"/>";
<xsl:value-of select="'    '"/>param-&gt;setUAPFloat(*&amp;paramname, *&amp;__<xsl:value-of select="@name"/>);
</xsl:when><xsl:when test="@dbtype='Integer'">
<xsl:value-of select="'    '"/>*paramname = "<xsl:value-of select="@name"/>";
<xsl:value-of select="'    '"/>param-&gt;setUAPLong(*&amp;paramname, *&amp;__<xsl:value-of select="@name"/>);
</xsl:when><xsl:when test="@dbtype='String'">
<xsl:value-of select="'    '"/>*paramname = "<xsl:value-of select="@name"/>";
<xsl:value-of select="'    '"/>param-&gt;setUAPString(*&amp;paramname, *&amp;__<xsl:value-of select="@name"/>);
</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>

</xsl:for-each>

	*paramname = "<xsl:value-of select="$FormName"/>ID";
	param-&gt;setUAPLong(*&amp;paramname, *&amp;__<xsl:value-of select="$FormName"/>ID);

	*paramname = "marked";
	param-&gt;setUAPLong(*&amp;paramname, *&amp;marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(__<xsl:value-of select="$FormName"/>ID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	<xsl:value-of select="$FormName"/>-&gt;insert(&amp;ukParam, &amp;key);

	return -1;
}

void		LB_STDCALL <xsl:value-of select="$FormName"/>Model::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	<xsl:value-of select="$FormName"/>-&gt;finishIteration();
	while (hasMore<xsl:value-of select="$FormName"/>()) {
		setNext<xsl:value-of select="$FormName"/>();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID-&gt;setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			<xsl:value-of select="$FormName"/>-&gt;remove(&amp;key);
			<xsl:value-of select="$FormName"/>-&gt;finishIteration();
		}
	}
}

void		LB_STDCALL <xsl:value-of select="$FormName"/>Model::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	<xsl:value-of select="$FormName"/>-&gt;finishIteration();
	while (hasMore<xsl:value-of select="$FormName"/>()) {
		setNext<xsl:value-of select="$FormName"/>();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID-&gt;setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			<xsl:value-of select="$FormName"/>-&gt;remove(&amp;key);
			<xsl:value-of select="$FormName"/>-&gt;finishIteration();
		}
	}
}

bool LB_STDCALL <xsl:value-of select="$FormName"/>Model::selectById(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID-&gt;setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = <xsl:value-of select="$FormName"/>-&gt;getElement(&amp;key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]"><xsl:variable name="FieldName" select="@name"/> <xsl:variable name="TableName" select="@tablename"/>
<xsl:choose><xsl:when test="@isfk='1'">
<xsl:value-of select="'    '"/>*paramname = "<xsl:value-of select="@name"/>";
<xsl:value-of select="'    '"/>param-&gt;getUAPLong(*&amp;paramname, *&amp;current<xsl:value-of select="@name"/>);
</xsl:when><xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
// Special column <xsl:value-of select="@name"/>
</xsl:when>
<xsl:otherwise>
<xsl:choose><xsl:when test="@dbtype='Bit'">
<xsl:value-of select="'    '"/>*paramname = "<xsl:value-of select="@name"/>";
<xsl:value-of select="'    '"/>param-&gt;getUAPBoolean(*&amp;paramname, *&amp;current<xsl:value-of select="@name"/>);
</xsl:when><xsl:when test="@dbtype='Float'">
<xsl:value-of select="'    '"/>*paramname = "<xsl:value-of select="@name"/>";
<xsl:value-of select="'    '"/>param-&gt;getUAPFloat(*&amp;paramname, *&amp;current<xsl:value-of select="@name"/>);
</xsl:when><xsl:when test="@dbtype='Integer'">
<xsl:value-of select="'    '"/>*paramname = "<xsl:value-of select="@name"/>";
<xsl:value-of select="'    '"/>param-&gt;getUAPLong(*&amp;paramname, *&amp;current<xsl:value-of select="@name"/>);
</xsl:when><xsl:when test="@dbtype='String'">
<xsl:value-of select="'    '"/>*paramname = "<xsl:value-of select="@name"/>";
<xsl:value-of select="'    '"/>param-&gt;getUAPString(*&amp;paramname, *&amp;current<xsl:value-of select="@name"/>);
</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>

</xsl:for-each>

		*paramname = "<xsl:value-of select="$FormName"/>ID";
		param-&gt;getUAPLong(*&amp;paramname, *&amp;current<xsl:value-of select="$FormName"/>ID);

		*paramname = "marked";
		param-&gt;getUAPLong(*&amp;paramname, *&amp;marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL <xsl:value-of select="$FormName"/>Model::ismarked() {
	if (marked-&gt;getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL <xsl:value-of select="$FormName"/>Model::mark() {
	marked-&gt;setData((long) 1);
}

void LB_STDCALL <xsl:value-of select="$FormName"/>Model::unmark() {
	marked-&gt;setData((long) 0);
}

int  LB_STDCALL <xsl:value-of select="$FormName"/>Model::Count() {
	return <xsl:value-of select="$FormName"/>-&gt;Count();
}

bool  LB_STDCALL <xsl:value-of select="$FormName"/>Model::hasMoreElements() {
	return (<xsl:value-of select="$FormName"/>-&gt;hasMoreElements() == 1);
}

void  LB_STDCALL <xsl:value-of select="$FormName"/>Model::setNextElement() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = <xsl:value-of select="$FormName"/>-&gt;nextElement();
	QI(uk, lb_I_Parameter, param)

<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]"><xsl:variable name="FieldName" select="@name"/> <xsl:variable name="TableName" select="@tablename"/>
<xsl:choose><xsl:when test="@isfk='1'">
<xsl:value-of select="'    '"/>*paramname = "<xsl:value-of select="@name"/>";
<xsl:value-of select="'    '"/>param-&gt;getUAPLong(*&amp;paramname, *&amp;current<xsl:value-of select="@name"/>);
</xsl:when><xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
// Special column <xsl:value-of select="@name"/>
</xsl:when>
<xsl:otherwise>
<xsl:choose><xsl:when test="@dbtype='Bit'">
<xsl:value-of select="'    '"/>*paramname = "<xsl:value-of select="@name"/>";
<xsl:value-of select="'    '"/>param-&gt;getUAPBoolean(*&amp;paramname, *&amp;current<xsl:value-of select="@name"/>);
</xsl:when><xsl:when test="@dbtype='Float'">
<xsl:value-of select="'    '"/>*paramname = "<xsl:value-of select="@name"/>";
<xsl:value-of select="'    '"/>param-&gt;getUAPFloat(*&amp;paramname, *&amp;current<xsl:value-of select="@name"/>);
</xsl:when><xsl:when test="@dbtype='Integer'">
<xsl:value-of select="'    '"/>*paramname = "<xsl:value-of select="@name"/>";
<xsl:value-of select="'    '"/>param-&gt;getUAPLong(*&amp;paramname, *&amp;current<xsl:value-of select="@name"/>);
</xsl:when><xsl:when test="@dbtype='String'">
<xsl:value-of select="'    '"/>*paramname = "<xsl:value-of select="@name"/>";
<xsl:value-of select="'    '"/>param-&gt;getUAPString(*&amp;paramname, *&amp;current<xsl:value-of select="@name"/>);
</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>

</xsl:for-each>
	*paramname = "<xsl:value-of select="$FormName"/>ID";
	param-&gt;getUAPLong(*&amp;paramname, *&amp;current<xsl:value-of select="$FormName"/>ID);

	*paramname = "marked";
	param-&gt;getUAPLong(*&amp;paramname, *&amp;marked);
	
}

void  LB_STDCALL <xsl:value-of select="$FormName"/>Model::finishIteration() {
	<xsl:value-of select="$FormName"/>-&gt;finishIteration();
}

long LB_STDCALL <xsl:value-of select="$FormName"/>Model::get_id() {
	return current<xsl:value-of select="$FormName"/>ID-&gt;getData();
}

<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]"><xsl:variable name="FieldName" select="@name"/> <xsl:variable name="TableName" select="@tablename"/>
<xsl:choose><xsl:when test="@isfk='1'">
long LB_STDCALL <xsl:value-of select="$FormName"/>Model::get_<xsl:value-of select="@name"/>() {
	return current<xsl:value-of select="@name"/>-&gt;getData();
}
</xsl:when><xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
// Special column <xsl:value-of select="@name"/>
</xsl:when>
<xsl:otherwise>
<xsl:choose><xsl:when test="@dbtype='Bit'">
bool LB_STDCALL <xsl:value-of select="$FormName"/>Model::get_<xsl:value-of select="@name"/>() {
	return current<xsl:value-of select="@name"/>-&gt;getData();
}
</xsl:when><xsl:when test="@dbtype='Float'">
float LB_STDCALL <xsl:value-of select="$FormName"/>Model::get_<xsl:value-of select="@name"/>() {
	return current<xsl:value-of select="@name"/>-&gt;getData();
}
</xsl:when><xsl:when test="@dbtype='Integer'">
long LB_STDCALL <xsl:value-of select="$FormName"/>Model::get_<xsl:value-of select="@name"/>() {
	return current<xsl:value-of select="@name"/>-&gt;getData();
}
</xsl:when><xsl:when test="@dbtype='String'">
char* LB_STDCALL <xsl:value-of select="$FormName"/>Model::get_<xsl:value-of select="@name"/>() {
	return current<xsl:value-of select="@name"/>-&gt;charrep();
}
</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>

</xsl:for-each>

class lbPlugin<xsl:value-of select="$FormName"/>Model : public lb_I_PluginImpl {
public:
	lbPlugin<xsl:value-of select="$FormName"/>Model();
	
	virtual ~lbPlugin<xsl:value-of select="$FormName"/>Model();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, uk<xsl:value-of select="$FormName"/>Model)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPlugin<xsl:value-of select="$FormName"/>Model)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPlugin<xsl:value-of select="$FormName"/>Model, lbPlugin<xsl:value-of select="$FormName"/>Model)

lbErrCodes LB_STDCALL lbPlugin<xsl:value-of select="$FormName"/>Model::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE &lt;&lt; "lbPlugin<xsl:value-of select="$FormName"/>Model::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPlugin<xsl:value-of select="$FormName"/>Model::lbPlugin<xsl:value-of select="$FormName"/>Model() {
	_CL_VERBOSE &lt;&lt; "lbPlugin<xsl:value-of select="$FormName"/>Model::lbPlugin<xsl:value-of select="$FormName"/>Model() called.\n" LOG_
}

lbPlugin<xsl:value-of select="$FormName"/>Model::~lbPlugin<xsl:value-of select="$FormName"/>Model() {
	_CL_VERBOSE &lt;&lt; "lbPlugin<xsl:value-of select="$FormName"/>Model::~lbPlugin<xsl:value-of select="$FormName"/>Model() called.\n" LOG_
}

bool LB_STDCALL lbPlugin<xsl:value-of select="$FormName"/>Model::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPlugin<xsl:value-of select="$FormName"/>Model::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPlugin<xsl:value-of select="$FormName"/>Model::initialize() {
}
	
bool LB_STDCALL lbPlugin<xsl:value-of select="$FormName"/>Model::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPlugin<xsl:value-of select="$FormName"/>Model::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (uk<xsl:value-of select="$FormName"/>Model == NULL) {
		<xsl:value-of select="$FormName"/>Model* a<xsl:value-of select="$FormName"/>Model = new <xsl:value-of select="$FormName"/>Model();
		
	
		QI(a<xsl:value-of select="$FormName"/>Model, lb_I_Unknown, uk<xsl:value-of select="$FormName"/>Model)
	} else {
		_CL_VERBOSE &lt;&lt; "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return uk<xsl:value-of select="$FormName"/>Model.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPlugin<xsl:value-of select="$FormName"/>Model::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (uk<xsl:value-of select="$FormName"/>Model == NULL) {

		_CL_VERBOSE &lt;&lt; "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		<xsl:value-of select="$FormName"/>Model* a<xsl:value-of select="$FormName"/>Model = new <xsl:value-of select="$FormName"/>Model();
		
	
		QI(a<xsl:value-of select="$FormName"/>Model, lb_I_Unknown, uk<xsl:value-of select="$FormName"/>Model)
	}
	
	lb_I_Unknown* r = uk<xsl:value-of select="$FormName"/>Model.getPtr();
	uk<xsl:value-of select="$FormName"/>Model.resetPtr();
	return r;
}

void LB_STDCALL lbPlugin<xsl:value-of select="$FormName"/>Model::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (uk<xsl:value-of select="$FormName"/>Model != NULL) {
                uk<xsl:value-of select="$FormName"/>Model--;
                uk<xsl:value-of select="$FormName"/>Model.resetPtr();
        }
}
</xsl:template>
</xsl:stylesheet>