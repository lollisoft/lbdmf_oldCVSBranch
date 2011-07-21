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
<xsl:import href="TypeMapping.xsl"/>
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

<!-- This template creates a pair of files per formular name -->
<xsl:template name="Entity.h">
	<xsl:param name="ApplicationID"/>
	<xsl:param name="FormularID"/>
	<xsl:param name="FormName"/>
///TODO: Implement entity header code.	
/** \brief class <xsl:value-of select="$FormName"/>Entity.
 * Documentation for <xsl:value-of select="$FormName"/>Entity
 */
class <xsl:value-of select="$FormName"/>Entity :
public lb_I_<xsl:value-of select="$FormName"/> {
public:
<xsl:value-of select="'    '"/>/** \brief Get the field id.
<xsl:value-of select="'     '"/>*/
<xsl:value-of select="'    '"/>virtual lb_I_Integer* get_id();

<xsl:value-of select="'    '"/>/** \brief Set the field id.
<xsl:value-of select="'     '"/>*/
<xsl:value-of select="'    '"/>virtual lbErrCodes set_id(lb_I_Integer* value);

<xsl:for-each select="//packagedElement[@xmi:id=$FormularID]/ownedAttribute[@xmi:type='uml:Property']">
<xsl:variable name="backendType"><xsl:call-template name="MapType"/></xsl:variable>
<xsl:if test="$backendType!='lb_I_Collection'">
<xsl:if test="@name!=''">
<xsl:value-of select="'    '"/>/** \brief Get the field <xsl:value-of select="@name"/>.
<xsl:value-of select="'     '"/>*/
<xsl:value-of select="'    '"/>virtual <xsl:value-of select="$backendType"/>* get_<xsl:value-of select="@name"/>();

<xsl:value-of select="'    '"/>/** \brief Set the field <xsl:value-of select="@name"/>.
<xsl:value-of select="'     '"/>*/
<xsl:value-of select="'    '"/>virtual lbErrCodes set_<xsl:value-of select="@name"/>(<xsl:value-of select="$backendType"/>* value);
</xsl:if>
</xsl:if>
</xsl:for-each>

protected:

<xsl:value-of select="'    '"/>UAP(lb_I_Integer, id)
<xsl:for-each select="//packagedElement[@xmi:id=$FormularID]/ownedAttribute[@xmi:type='uml:Property']">
<xsl:variable name="backendType"><xsl:call-template name="MapType"/></xsl:variable>
<xsl:if test="$backendType!='lb_I_Collection'">
<xsl:if test="@name!=''">
<xsl:value-of select="'    '"/>UAP(<xsl:value-of select="$backendType"/>, <xsl:value-of select="@name"/>)
</xsl:if>
</xsl:if>
</xsl:for-each>
};

DECLARE_FUNCTOR(instanceOf<xsl:value-of select="$FormName"/>Entity)
</xsl:template>
</xsl:stylesheet>