<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:xmi="http://schema.omg.org/spec/XMI/2.1" xmlns:UML="org.omg.xmi.namespace.UML" exclude-result-prefixes="UML">
<!--
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2002-2013  Lothar Behrens (lothar.behrens@lollisoft.de)

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
<xsl:output method="text"/>

<xsl:template name="XMISysImport.CreateFormularDefinition.Sqlite">
	<xsl:param name="overwriteDatabase"/><!-- When set to yes, DROP rules are created -->
    <xsl:param name="ApplicationName"/>
    <xsl:param name="FieldName"/><!-- The field name of the current UML attribute or property definition -->
    <xsl:param name="DataType"/><!-- The fields corresponding type name -->
    <xsl:param name="ClassId"/><!-- The Id for the current class to create schema information -->
    <xsl:param name="ClassName"/><!-- The Id for the current class to create schema information -->
    <xsl:param name="TableName"/><!-- The Id for the current class to create schema information -->
    <xsl:param name="TargetDBType"/><!-- What database the SQL script should be created for -->
    <xsl:param name="TargetDBVersion"/><!-- What is the version of the database -->

<!-- Mapped to internal type representation. This is not a backend type. -->
<xsl:variable name="MappedDataType">
<xsl:choose>
<xsl:when test="$DataType='float'">Float</xsl:when>
<xsl:when test="$DataType='string'">String</xsl:when>
<xsl:when test="$DataType='phonenumber'">PhoneNumber</xsl:when>
<xsl:when test="$DataType='bigstring'">String</xsl:when>
<xsl:when test="$DataType='date'">String</xsl:when>
<xsl:when test="$DataType='int'">Integer</xsl:when>
<xsl:when test="$DataType='bool'">Bit</xsl:when>
<xsl:otherwise>Undefined</xsl:otherwise>
</xsl:choose>
</xsl:variable>

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) 
SELECT '<xsl:value-of select="$FieldName"/>', '<xsl:value-of select="$TableName"/>', 0, '<xsl:value-of select="$MappedDataType"/>', id FROM "formulare" WHERE name = '<xsl:value-of select="$ClassName"/>' and anwendungid in (select id from anwendungen where name = '<xsl:value-of select="$ApplicationName"/>');

</xsl:template>


<xsl:template name="XMISysImport.CreateFormularDefinitionAssociation.Sqlite">
	<xsl:param name="overwriteDatabase"/><!-- When set to yes, DROP rules are created -->
    <xsl:param name="AssociationId"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="TargetDBType"/><!-- What database the SQL script should be created for -->
    <xsl:param name="TargetDBVersion"/><!-- What is the version of the database -->

<xsl:variable name="PrimaryKeyClassId" select="//UML:Association[@xmi.id=$AssociationId]/UML:Association.connection/UML:AssociationEnd[@aggregation='aggregate']/UML:AssociationEnd.participant/UML:Class/@xmi.idref"/>
<xsl:variable name="ForeignKeyClassId" select="//UML:Association[@xmi.id=$AssociationId]/UML:Association.connection/UML:AssociationEnd[@aggregation='none']/UML:AssociationEnd.participant/UML:Class/@xmi.idref"/>
<xsl:variable name="PrimaryKeyClassName" select="//UML:Class[@xmi.id=$PrimaryKeyClassId]/@name"/>
<xsl:variable name="ForeignKeyClassName" select="//UML:Class[@xmi.id=$ForeignKeyClassId]/@name"/>

<xsl:variable name="assocVisibleName" select="substring-after(substring-before(@name, ')'), '(')"/>

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) 
SELECT '<xsl:value-of select="$PrimaryKeyClassName"/>', '<xsl:value-of select="$ForeignKeyClassName"/>', 1, '<xsl:value-of select="$assocVisibleName"/>', '<xsl:value-of select="$PrimaryKeyClassName"/>', 'Integer', id FROM "formulare" WHERE name = '<xsl:value-of select="$ForeignKeyClassName"/>' and anwendungid in (select id from anwendungen where name = '<xsl:value-of select="$ApplicationName"/>');


</xsl:template>


</xsl:stylesheet>
