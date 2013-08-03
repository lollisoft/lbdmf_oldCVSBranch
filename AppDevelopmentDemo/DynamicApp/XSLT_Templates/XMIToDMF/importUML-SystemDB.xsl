<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:xmi="http://schema.omg.org/spec/XMI/2.1" xmlns:lbDMF="http:///schemas/lbDMF/1">
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
<!-- Template to create base class file for fixed database forms -->
<xsl:import href="importUMLClassAsDMFForm.xsl"/>
<xsl:import href="importUMLApplicationTables.xsl"/>
<xsl:import href="createDefaultStoredProcs.xsl"/>
<xsl:import href="importUMLReports.xsl"/>

<xsl:import href="XMISettings.xsl"/>

<xsl:output method="text"/>

<!-- Stylesheet parameters that will overwrite those given from the XMISettings.xsl file. -->
<xsl:param name="XSLDatabaseBackendSystem"/>
<xsl:param name="XSLDatabaseBackendApplication"/>
<xsl:param name="overwriteDatabase"/>

<xsl:param name="UMLImportDBName"/>
<xsl:param name="UMLImportDBUser"/>
<xsl:param name="UMLImportDBPass"/>

<xsl:variable name="database_name"><xsl:if test="$UMLImportDBName=''"><xsl:value-of select="$settingsfile_database_name"/></xsl:if><xsl:if test="$UMLImportDBName!=''"><xsl:value-of select="$UMLImportDBName"/></xsl:if></xsl:variable>
<xsl:variable name="database_user"><xsl:if test="$UMLImportDBUser=''"><xsl:value-of select="$settingsfile_database_user"/></xsl:if><xsl:if test="$UMLImportDBUser!=''"><xsl:value-of select="$UMLImportDBUser"/></xsl:if></xsl:variable>
<xsl:variable name="database_pass"><xsl:if test="$UMLImportDBPass=''"><xsl:value-of select="$settingsfile_database_pass"/></xsl:if><xsl:if test="$UMLImportDBPass!=''"><xsl:value-of select="$UMLImportDBPass"/></xsl:if></xsl:variable>

<xsl:variable name="targetdatabase"><xsl:if test="$XSLDatabaseBackendSystem=''"><xsl:value-of select="$settingsfile_targetdatabase"/></xsl:if><xsl:if test="$XSLDatabaseBackendSystem!=''"><xsl:value-of select="$XSLDatabaseBackendSystem"/></xsl:if></xsl:variable>

<!-- ********** Select your database target ********** -->

<!--
<xsl:variable name="DefaultDatabaseSystem" select="'MSSQL'"/>
-->
<xsl:variable name="DefaultDatabaseSystem" select="'PostgreSQL'"/>

<xsl:variable name="TargetDBType">
	<xsl:if test="$targetdatabase = 'DatabaseLayerGateway'">Sqlite</xsl:if>
	<xsl:if test="$targetdatabase = 'PostgreSQL'">PostgreSQL</xsl:if>
	<xsl:if test="$targetdatabase = 'MSSQL'">MSSQL</xsl:if>
	<xsl:if test="$targetdatabase = 'Sqlite'">Sqlite</xsl:if>
	<xsl:if test="$targetdatabase = ' '"><xsl:value-of select="$DefaultDatabaseSystem"/></xsl:if>
	<xsl:if test="$targetdatabase = ''"><xsl:value-of select="$DefaultDatabaseSystem"/></xsl:if>
</xsl:variable>
<xsl:variable name="TargetDBVersion">
	<xsl:if test="$targetdatabase = 'DatabaseLayerGateway'">1.2.3</xsl:if>
	<xsl:if test="$targetdatabase = ' '">7.4</xsl:if>
	<xsl:if test="$targetdatabase = ''">7.4</xsl:if>
</xsl:variable>

<!-- ************************************************* -->

	<xsl:template match="text()|@*">
		<xsl:value-of select="."/>
	</xsl:template>
	<xsl:template match="text()|@*"/>

<xsl:template match="packagedElement"> 
<xsl:value-of select="$activity"/></xsl:template>


	<xsl:template match="/">
-- Speedup many times
BEGIN TRANSACTION;

-- Params XSLDatabaseBackendSystem: <xsl:value-of select="$XSLDatabaseBackendSystem"/>
-- Params XSLDatabaseBackendApplication: <xsl:value-of select="$XSLDatabaseBackendApplication"/>
-- Params overwriteDatabase: <xsl:value-of select="$overwriteDatabase"/>

-- Params targetdatabase generated: <xsl:value-of select="$targetdatabase"/>

--
-- SQL script created for <xsl:value-of select="$TargetDBType"/>
--

		<!-- Generate System database definition -->
		<xsl:variable name="_AppName"><xsl:value-of select="//packagedElement[@xmi:type='uml:Class']/xmi:Extension/stereotype[@name='form']/../../../@name"/></xsl:variable>

		<xsl:variable name="AppName">
		<xsl:if test="$_AppName=''"><xsl:value-of select="//packagedElement[@xmi:type='uml:Class']/../@name"/></xsl:if>
		<xsl:if test="$_AppName!=''"><xsl:value-of select="//packagedElement[@xmi:type='uml:Class']/xmi:Extension/stereotype[@name='form']/../../../@name"/></xsl:if>		
		</xsl:variable>
		
-- Application is <xsl:value-of select="$AppName"/>. Package is <xsl:value-of select="//packagedElement[@xmi:type='uml:Class']/../@name"/>
-- Using database settings as of name=<xsl:value-of select="$database_name"/>, user=<xsl:value-of select="$database_user"/>
		
		<xsl:call-template name="createDefaultStoredProcs">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="ApplicationName" select="$AppName"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDBType"/>
			<xsl:with-param name="TargetDatabaseVersion" select="$TargetDBVersion"/>
			<xsl:with-param name="database_name" select="$database_name"/>
			<xsl:with-param name="database_user" select="$database_user"/>
			<xsl:with-param name="database_pass" select="$database_pass"/>

		</xsl:call-template>	
	
		<xsl:for-each select="//packagedElement[@xmi:type='uml:Class']">
			<xsl:choose>
				<xsl:when test="./xmi:Extension/stereotype[@name='form']">
		-- Class <xsl:value-of select="@name"/> of type FORM found.
					<xsl:call-template name="importDMFForm">
						<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
						<xsl:with-param name="ApplicationName" select="../@name"/>
						<xsl:with-param name="TargetDatabaseType" select="$TargetDBType"/>
						<xsl:with-param name="TargetDatabaseVersion" select="$TargetDBVersion"/>
					</xsl:call-template>
				</xsl:when>
				<xsl:when test="./xmi:Extension/stereotype[@name='entity']">
		-- Class <xsl:value-of select="@name"/> of type FORM found.
					<xsl:call-template name="importDMFEntity">
						<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
						<xsl:with-param name="ApplicationName" select="$AppName"/>
						<xsl:with-param name="TargetDatabaseType" select="$TargetDBType"/>
						<xsl:with-param name="TargetDatabaseVersion" select="$TargetDBVersion"/>
					</xsl:call-template>
				</xsl:when>
				<xsl:when test="./xmi:Extension/stereotype[@name='report']">
		-- Class <xsl:value-of select="@name"/> of type FORM found.
					<xsl:call-template name="importDMFReport">
						<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
						<xsl:with-param name="ApplicationName" select="../@name"/>
						<xsl:with-param name="TargetDatabaseType" select="$TargetDBType"/>
						<xsl:with-param name="TargetDatabaseVersion" select="$TargetDBVersion"/>
						<xsl:with-param name="TargetReportSystem" select="'OpenRPT'"/>
					</xsl:call-template>
				</xsl:when>
				<xsl:when test="./xmi:Extension/stereotype[@name='lbDMF:form']">
		-- Class <xsl:value-of select="@name"/> of type FORM found.
					<xsl:call-template name="importDMFForm">
						<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
						<xsl:with-param name="ApplicationName" select="../@name"/>
						<xsl:with-param name="TargetDatabaseType" select="$TargetDBType"/>
						<xsl:with-param name="TargetDatabaseVersion" select="$TargetDBVersion"/>
					</xsl:call-template>
				</xsl:when>
				<xsl:when test="./xmi:Extension/stereotype[@name='lbDMF:report']">
		-- Class <xsl:value-of select="@name"/> of type FORM found.
					<xsl:call-template name="importDMFReport">
						<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
						<xsl:with-param name="ApplicationName" select="../@name"/>
						<xsl:with-param name="TargetDatabaseType" select="$TargetDBType"/>
						<xsl:with-param name="TargetDatabaseVersion" select="$TargetDBVersion"/>
						<xsl:with-param name="TargetReportSystem" select="'OpenRPT'"/>
					</xsl:call-template>
				</xsl:when>
				<xsl:when test="./xmi:Extension/stereotype[@name='entity']">
				<!-- Class <xsl:value-of select="@name"/> of type ENTITY found.
					<xsl:call-template name="importApplicationTable">
						<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
						<xsl:with-param name="ApplicationName" select="../@name"/>
						<xsl:with-param name="TargetDatabaseType" select="$TargetDBType"/>
						<xsl:with-param name="TargetDatabaseVersion" select="$TargetDBVersion"/>
					</xsl:call-template>
				-->	
			</xsl:when>
			</xsl:choose>
		</xsl:for-each>


		<xsl:for-each select="//packagedElement[@xmi:type='uml:Dependency']">
		<xsl:variable name="supplier" select="./@supplier"/>
		<xsl:variable name="client" select="./@client"/>
		<xsl:if test="//packagedElement[@xmi:id=$supplier]/xmi:Extension/stereotype/@name='report'">
-- Create report link from '<xsl:value-of select="$supplier"/>' to '<xsl:value-of select="$client"/>'
		
INSERT INTO "actions" (name, typ, source) VALUES ('Print <xsl:value-of select="//packagedElement[@xmi:id=$supplier]/@name"/>', 1, '');
INSERT INTO "action_steps" (bezeichnung, a_order_nr, what, type, actionid) VALUES ('Printing step', 1, 'lala', (select id from action_types where action_handler = 'instanceOflbDMFXslt'), (select id from actions where name = 'Print <xsl:value-of select="//packagedElement[@xmi:id=$supplier]/@name"/>'));
INSERT INTO "formular_actions" (formular, action, event) VALUES ((select id from formulare where name = '<xsl:value-of select="//packagedElement[@xmi:id=$client]/@name"/>'), (select id from actions where name = 'Print <xsl:value-of select="//packagedElement[@xmi:id=$supplier]/@name"/>'), 'evt_Print<xsl:value-of select="//packagedElement[@xmi:id=$client]/@name"/>_<xsl:value-of select="//packagedElement[@xmi:id=$supplier]/@name"/>"/>');
		</xsl:if>
		</xsl:for-each>

<!-- Generate Application database model -->
<!--
	<xsl:for-each select="//packagedElement[@xmi:type='uml:Class']">
		<xsl:choose>
			<xsl:when test="./xmi:Extension/stereotype[@name='form']">
			</xsl:when>
			<xsl:when test="./xmi:Extension/stereotype[@name='entity']">

	<xsl:call-template name="importApplicationTableRelation">
		<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
		<xsl:with-param name="ApplicationName" select="../@name"/>
		<xsl:with-param name="TargetDatabaseType" select="$TargetDBType"/>
		<xsl:with-param name="TargetDatabaseVersion" select="$TargetDBVersion"/>
	</xsl:call-template>
	
		</xsl:when>
		</xsl:choose>
	</xsl:for-each>
-->





    <xsl:for-each select="//ownedOperation"><xsl:variable name="function" select="@name"/>
	<xsl:if test="./xmi:Extension/stereotype/@name='validator'">
-- Activity operation for class <xsl:value-of select="../@name"/> in package <xsl:value-of select="../../@name"/> is <xsl:value-of select="@name"/>.
-- Operation is a validator using activity <xsl:value-of select="./xmi:Extension/taggedValue[@tag='validator']/@value"/>
		<xsl:variable name="activity" select="@name"/>
		<xsl:variable name="activityID" select="//packagedElement[@xmi:type = 'uml:Activity'][@name = $activity]/@xmi:id"/>
<!--<xsl:apply-templates select="../../packagedElement[@xmi:type = 'uml:Activity'][@name = $function]"/>-->
-- Activity ID is '<xsl:value-of select="$activityID"/>'
		<xsl:if test="$activityID=''">-- Activity not found.</xsl:if>
		<xsl:if test="$activityID!=''">-- Activity '<xsl:value-of select="$activity"/>' found.
			<xsl:call-template name="convertActivityTolbDMFActivity">
			<xsl:with-param name="ID" select="$activityID"/>
			<xsl:with-param name="Name" select="$activity"/>
			<xsl:with-param name="FormName" select="../@name"/>
			<xsl:with-param name="ApplicationName" select="$AppName"/>
			<xsl:with-param name="TypeName" select="'FormValidator'"/>
			</xsl:call-template>
		</xsl:if>
	</xsl:if>

<!-- The plain workflow stereotype may be obsolete, if I am using the profile. -->

	<xsl:if test="./xmi:Extension/stereotype/@name='workflow'">
-- Activity operation for class <xsl:value-of select="../@name"/> in package <xsl:value-of select="../../@name"/> is <xsl:value-of select="@name"/>.
-- Operation is a validator using activity <xsl:value-of select="./xmi:Extension/taggedValue[@tag='validator']/@value"/>
		<xsl:variable name="activity" select="@name"/>
		<xsl:variable name="activityID" select="//packagedElement[@xmi:type = 'uml:Activity'][@name = $activity]/@xmi:id"/>
<!--<xsl:apply-templates select="../../packagedElement[@xmi:type = 'uml:Activity'][@name = $function]"/>-->
-- Activity ID is '<xsl:value-of select="$activityID"/>'
		<xsl:if test="$activityID=''">-- Activity not found.</xsl:if>
		<xsl:if test="$activityID!=''">-- Activity '<xsl:value-of select="$activity"/>' found.
			<xsl:call-template name="convertActivityTolbDMFActivity">
			<xsl:with-param name="ID" select="$activityID"/>
			<xsl:with-param name="Name" select="$activity"/>
			<xsl:with-param name="FormName" select="../@name"/>
			<xsl:with-param name="ApplicationName" select="$AppName"/>
			<xsl:with-param name="TypeName" select="'Buttonpress'"/>
			</xsl:call-template>
		</xsl:if>
	</xsl:if>

	<xsl:if test="./xmi:Extension/stereotype/@name='lbDMF:workflow'">
-- Activity operation for class <xsl:value-of select="../@name"/> in package <xsl:value-of select="../../@name"/> is <xsl:value-of select="@name"/>.
-- Operation is a validator using activity <xsl:value-of select="./xmi:Extension/taggedValue[@tag='validator']/@value"/>
		<xsl:variable name="activity" select="@name"/>
		<xsl:variable name="activityID" select="//packagedElement[@xmi:type = 'uml:Activity'][@name = $activity]/@xmi:id"/>
<!--<xsl:apply-templates select="../../packagedElement[@xmi:type = 'uml:Activity'][@name = $function]"/>-->
-- Activity ID is '<xsl:value-of select="$activityID"/>'
		<xsl:if test="$activityID=''">-- Activity not found.</xsl:if>
		<xsl:if test="$activityID!=''">-- Activity '<xsl:value-of select="$activity"/>' found.
			<xsl:call-template name="convertActivityTolbDMFActivity">
			<xsl:with-param name="ID" select="$activityID"/>
			<xsl:with-param name="Name" select="$activity"/>
			<xsl:with-param name="ApplicationName" select="$AppName"/>
			<xsl:with-param name="FormName" select="../@name"/>
			<xsl:with-param name="TypeName" select="'Buttonpress'"/>
			</xsl:call-template>
		</xsl:if>
	</xsl:if>

</xsl:for-each>
-- Script ready.
COMMIT;
</xsl:template>

<xsl:template name="convertActivityTolbDMFActivity">
    <xsl:param name="ID"/>
    <xsl:param name="Name"/>
    <xsl:param name="FormName"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="TypeName"/> <!-- The action type name as registered. -->
<xsl:choose>
	<xsl:when test="$TargetDBType='PostgreSQL'">
INSERT INTO "action_types" ("bezeichnung", "action_handler", "module") VALUES ('<xsl:value-of select="$Name"/>_<xsl:value-of select="$ID"/>', 'instanceOflbAction', 'lbDatabaseForm');

INSERT INTO "actions" ("name", "typ", "source", "target") VALUES ('<xsl:value-of select="$Name"/>_<xsl:value-of select="$ID"/>', (select "id" from "action_types" where "bezeichnung" = '<xsl:value-of select="$TypeName"/>'), '<xsl:value-of select="./ownedParameter/@name"/>', '');

INSERT INTO "formular_actions" ("formular", "action", "event") VALUES ((select "id" from "formulare" where "name" = '<xsl:value-of select="$FormName"/>'), (select "id" from "actions" where "name" = '<xsl:value-of select="$Name"/>_<xsl:value-of select="$ID"/>'), 'event<xsl:value-of select="$Name"/>_<xsl:value-of select="$ID"/>_<xsl:value-of select="$TypeName"/>');
	</xsl:when>
	<xsl:when test="$TargetDBType='Sqlite'">
-- Generate statemachine for <xsl:value-of select="$ID"/>
-- select "CreateActivityOnMissing"('<xsl:value-of select="$ID"/>', '<xsl:value-of select="$Name"/>');

-- Delete old statemachine
delete from "action_step_parameter" where "action_step_id" in (select id from "action_steps" where "actionid" in (select "id" from "actions" where "target" = '<xsl:value-of select="$ID"/>' AND "anwendungenid" = (select id from "anwendungen" where name = '<xsl:value-of select="$ApplicationName"/>')));
delete from "action_step_transitions" where "description" = '_<xsl:value-of select="$ID"/>';
delete from "action_steps" where "actionid" in (select "id" from "actions" where "target" = '<xsl:value-of select="$ID"/>' AND "anwendungenid" = (select id from "anwendungen" where name = '<xsl:value-of select="$ApplicationName"/>'));
delete from "formular_actions" where action in (select id from actions where "target" = '<xsl:value-of select="$ID"/>' AND "anwendungenid" = (select id from "anwendungen" where name = '<xsl:value-of select="$ApplicationName"/>'));
delete from "actions" where "target" = '<xsl:value-of select="$ID"/>' AND "anwendungenid" = (select id from "anwendungen" where name = '<xsl:value-of select="$ApplicationName"/>');

-- A form validator should be used before saving the changes to the database

INSERT OR IGNORE INTO "action_types" ("bezeichnung", "action_handler", "module") VALUES ('<xsl:value-of select="$Name"/>_<xsl:value-of select="$ID"/>', 'instanceOflbAction', 'lbDatabaseForm');

INSERT OR IGNORE INTO "actions" ("name", "typ", "source", "target", "anwendungenid") VALUES (
'<xsl:value-of select="$Name"/>', 
(select "id" from "action_types" where "bezeichnung" = '<xsl:value-of select="$TypeName"/>'),
'<xsl:value-of select="./ownedParameter/@name"/>',
'<xsl:value-of select="$ID"/>', 
(select id from "anwendungen" where name = '<xsl:value-of select="$ApplicationName"/>'));

INSERT OR IGNORE INTO "formular_actions" ("formular", "action", "event") VALUES (
(select "id" from "formulare" where "name" = '<xsl:value-of select="$FormName"/>'), 
(select "id" from "actions" where "target" = '<xsl:value-of select="$ID"/>'),
'event<xsl:value-of select="$Name"/>_<xsl:value-of select="$ID"/>_<xsl:value-of select="$TypeName"/>');
	</xsl:when>
	<xsl:when test="$TargetDBType='MSSQL'">
	</xsl:when>
</xsl:choose>

<xsl:choose>
	<xsl:when test="$TargetDBType='PostgreSQL'">
-- Create activity nodes for Sqlite
<xsl:for-each select="//packagedElement[@xmi:id=$ID]/node">
	<xsl:variable name="step" select="position()"/>
	<xsl:variable name="nodetype" select="@xmi:type"/>
		<xsl:variable name="stereotype" select="./xmi:Extension/stereotype/@name"/>
	<xsl:choose>
		<xsl:when test="$nodetype='uml:InitialNode'">
INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = '<xsl:value-of select="$Name"/>_<xsl:value-of select="$ID"/>'), '<xsl:value-of select="./@xmi:id"/>', '<xsl:value-of select="$step"/>', (select "id" from "action_types" where "bezeichnung" = 'InitialNode'), '');
		</xsl:when>
		<xsl:when test="$nodetype='uml:SendSignalAction'">
		<xsl:variable name="comment" select="./ownedComment/@body"/>
INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = '<xsl:value-of select="$Name"/>_<xsl:value-of select="$ID"/>'), '<xsl:value-of select="./@xmi:id"/>', '<xsl:value-of select="$step"/>', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '<xsl:value-of select="$comment"/>');
<xsl:for-each select="./xmi:Extension/taggedValue">
INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('<xsl:value-of select="./@tag"/>', '<xsl:value-of select="./@value"/>', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = '<xsl:value-of select="../../@xmi:id"/>'));
</xsl:for-each>

		</xsl:when>
		<xsl:when test="$nodetype='uml:DecisionNode'">
INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = '<xsl:value-of select="$Name"/>_<xsl:value-of select="$ID"/>'), '<xsl:value-of select="./@xmi:id"/>', '<xsl:value-of select="$step"/>', (select "id" from "action_types" where "bezeichnung" = 'DecisionNode'), '');
		</xsl:when>
		<xsl:when test="$nodetype='uml:OpaqueAction'">
		<xsl:variable name="comment" select="./ownedComment/@body"/>
INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = '<xsl:value-of select="$Name"/>_<xsl:value-of select="$ID"/>'), '<xsl:value-of select="./@xmi:id"/>', '<xsl:value-of select="$step"/>', (select "id" from "action_types" where "bezeichnung" = 'OpaqueAction'), '<xsl:value-of select="$comment"/>');
		</xsl:when>
		<xsl:when test="$nodetype='uml:FinalNode'">
INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = '<xsl:value-of select="$Name"/>_<xsl:value-of select="$ID"/>'), '<xsl:value-of select="./@xmi:id"/>', '<xsl:value-of select="$step"/>', (select "id" from "action_types" where "bezeichnung" = 'FinalNode'), '');
		</xsl:when>
		<xsl:when test="$nodetype='uml:ActivityParameterNode'">
INSERT INTO "action_parameters" ("name", "value", "interface", "description", "actionid") VALUES ('<xsl:value-of select="./@name"/>', '', 'lb_I_String', 'A description ...', (select "id" from "actions" where "name" = '<xsl:value-of select="../@name"/>_<xsl:value-of select="../@xmi:id"/>'));
		</xsl:when>
		<xsl:otherwise>
-- Nodetype <xsl:value-of select="$nodetype"/> not known.
		</xsl:otherwise>
	</xsl:choose>
</xsl:for-each>
-- Create activity transitions
<xsl:for-each select="//packagedElement[@xmi:id=$ID]/edge">
	<xsl:variable name="edgetype" select="@xmi:type"/>
	<xsl:variable name="stereotype" select="./xmi:Extension/stereotype/@name"/>
	<xsl:choose>
		<xsl:when test="$edgetype='uml:ControlFlow'">
			<xsl:variable name="expression" select="./guard[@xmi:type='uml:OpaqueExpression']/body"/>
			<xsl:variable name="transid" select="./@transformation"/>
			<xsl:variable name="transformation" select="//ownedBehavior[@xmi:type='uml:OpaqueBehavior'][@xmi:id=$transid]/body"/>
INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('<xsl:value-of select="$expression"/>', '<xsl:value-of select="@name"/>_<xsl:value-of select="$ID"/>', (select id from "action_steps" where "bezeichnung" = '<xsl:value-of select="./@source"/>'), (select id from "action_steps" where "bezeichnung" = '<xsl:value-of select="./@target"/>'));
<xsl:if test="$transformation!=''">
UPDATE "action_step_transitions" set "expression" = '<xsl:value-of select="$transformation"/>' where "src_actionid" = (select id from "action_steps" where "bezeichnung" = '<xsl:value-of select="./@source"/>') and dst_actionid = (select id from "action_steps" where "bezeichnung" = '<xsl:value-of select="./@target"/>');
</xsl:if>
		</xsl:when>
		<xsl:otherwise>
-- Nodetype <xsl:value-of select="$edgetype"/> not known.
		</xsl:otherwise>
	</xsl:choose>
</xsl:for-each>
-- Rename activity nodes for Sqlite
<xsl:for-each select="//packagedElement[@xmi:id=$ID]/node">
	<xsl:variable name="step" select="position()"/>
	<xsl:variable name="nodetype" select="@xmi:type"/>
		<xsl:variable name="stereotype" select="./xmi:Extension/stereotype/@name"/>
	<xsl:choose>
		<xsl:when test="$nodetype='uml:InitialNode'">
UPDATE "action_steps" set "bezeichnung" = '<xsl:value-of select="./@name"/>' where "bezeichnung" = '<xsl:value-of select="./@xmi:id"/>';
		</xsl:when>
		<xsl:when test="$nodetype='uml:SendSignalAction'">
		<xsl:variable name="comment" select="./ownedComment/@body"/>
		<xsl:variable name="signalname" select="./xmi:Extension/taggedValue[@tag='signal']/@value"/>
UPDATE "action_steps" set "bezeichnung" = '<xsl:value-of select="$signalname"/>' where "bezeichnung" = '<xsl:value-of select="./@xmi:id"/>';
		</xsl:when>
		<xsl:when test="$nodetype='uml:DecisionNode'">
UPDATE "action_steps" set "bezeichnung" = '<xsl:value-of select="./@name"/>' where "bezeichnung" = '<xsl:value-of select="./@xmi:id"/>';
		</xsl:when>
		<xsl:when test="$nodetype='uml:OpaqueAction'">
		<xsl:variable name="comment" select="./ownedComment/@body"/>
UPDATE "action_steps" set "bezeichnung" = '<xsl:value-of select="./@name"/>' where "bezeichnung" = '<xsl:value-of select="./@xmi:id"/>';
		</xsl:when>
		<xsl:when test="$nodetype='uml:FinalNode'">
UPDATE "action_steps" set "bezeichnung" = 'FinalNode' where "bezeichnung" = '<xsl:value-of select="./@xmi:id"/>';
		</xsl:when>
		<xsl:otherwise>
-- Nodetype <xsl:value-of select="$nodetype"/> not known.
		</xsl:otherwise>
	</xsl:choose>
</xsl:for-each>
	</xsl:when>
	<xsl:when test="$TargetDBType='Sqlite'">
-- Create activity nodes for Sqlite
<xsl:for-each select="//packagedElement[@xmi:id=$ID]/node">
	<xsl:variable name="step" select="position()"/>
	<xsl:variable name="nodetype" select="@xmi:type"/>
		<xsl:variable name="stereotype" select="./xmi:Extension/stereotype/@name"/>
	<xsl:choose>
		<xsl:when test="$nodetype='uml:InitialNode'">
INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = '<xsl:value-of select="$ID"/>'), '<xsl:value-of select="./@xmi:id"/>', '<xsl:value-of select="$step"/>', (select "id" from "action_types" where "bezeichnung" = 'InitialNode'), '');
		</xsl:when>
		<xsl:when test="$nodetype='uml:SendSignalAction'">
		<xsl:variable name="comment" select="./ownedComment/@body"/>
INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = '<xsl:value-of select="$ID"/>'), '<xsl:value-of select="./@xmi:id"/>', '<xsl:value-of select="$step"/>', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '<xsl:value-of select="$comment"/>');
<xsl:for-each select="./xmi:Extension/taggedValue">
INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('<xsl:value-of select="./@tag"/>', '<xsl:value-of select="./@value"/>', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = '<xsl:value-of select="../../@xmi:id"/>'));
</xsl:for-each>

		</xsl:when>
		<xsl:when test="$nodetype='uml:DecisionNode'">
INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = '<xsl:value-of select="$ID"/>'), '<xsl:value-of select="./@xmi:id"/>', '<xsl:value-of select="$step"/>', (select "id" from "action_types" where "bezeichnung" = 'DecisionNode'), '');
		</xsl:when>
		<xsl:when test="$nodetype='uml:OpaqueAction'">
		<xsl:variable name="comment" select="./ownedComment/@body"/>
INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = '<xsl:value-of select="$ID"/>'), '<xsl:value-of select="./@xmi:id"/>', '<xsl:value-of select="$step"/>', (select "id" from "action_types" where "bezeichnung" = 'OpaqueAction'), '<xsl:value-of select="$comment"/>');
		</xsl:when>
		<xsl:when test="$nodetype='uml:FinalNode'">
INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = '<xsl:value-of select="$ID"/>'), '<xsl:value-of select="./@xmi:id"/>', '<xsl:value-of select="$step"/>', (select "id" from "action_types" where "bezeichnung" = 'FinalNode'), '');
		</xsl:when>
		<xsl:when test="$nodetype='uml:ActivityParameterNode'">
INSERT OR IGNORE INTO "action_parameters" ("name", "value", "interface", "description", "actionid") VALUES ('<xsl:value-of select="./@name"/>', '', 'lb_I_String', 'A description ...', (select "id" from "actions" where "target" = '<xsl:value-of select="$ID"/>'));
		</xsl:when>
		<xsl:otherwise>
-- Nodetype <xsl:value-of select="$nodetype"/> not known.
		</xsl:otherwise>
	</xsl:choose>
</xsl:for-each>
-- Create activity transitions
<xsl:for-each select="//packagedElement[@xmi:id=$ID]/edge">
	<xsl:variable name="edgetype" select="@xmi:type"/>
	<xsl:variable name="stereotype" select="./xmi:Extension/stereotype/@name"/>
	<xsl:choose>
		<xsl:when test="$edgetype='uml:ControlFlow'">
			<xsl:variable name="expression" select="./guard[@xmi:type='uml:OpaqueExpression']/body"/>
			<xsl:variable name="transid" select="./@transformation"/>
			<xsl:variable name="transformation" select="//ownedBehavior[@xmi:type='uml:OpaqueBehavior'][@xmi:id=$transid]/body"/>
INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('<xsl:value-of select="$expression"/>', '<xsl:value-of select="@name"/>_<xsl:value-of select="$ID"/>', (select id from "action_steps" where "bezeichnung" = '<xsl:value-of select="./@source"/>'), (select id from "action_steps" where "bezeichnung" = '<xsl:value-of select="./@target"/>'));
<xsl:if test="$transformation!=''">
UPDATE "action_step_transitions" set "expression" = '<xsl:value-of select="$transformation"/>' where "src_actionid" = (select id from "action_steps" where "bezeichnung" = '<xsl:value-of select="./@source"/>') and dst_actionid = (select id from "action_steps" where "bezeichnung" = '<xsl:value-of select="./@target"/>');
</xsl:if>
		</xsl:when>
		<xsl:otherwise>
-- Nodetype <xsl:value-of select="$edgetype"/> not known.
		</xsl:otherwise>
	</xsl:choose>
</xsl:for-each>
-- Rename activity nodes for Sqlite
<xsl:for-each select="//packagedElement[@xmi:id=$ID]/node">
	<xsl:variable name="step" select="position()"/>
	<xsl:variable name="nodetype" select="@xmi:type"/>
		<xsl:variable name="stereotype" select="./xmi:Extension/stereotype/@name"/>
	<xsl:choose>
		<xsl:when test="$nodetype='uml:InitialNode'">
UPDATE "action_steps" set "bezeichnung" = '<xsl:value-of select="./@name"/>' where "bezeichnung" = '<xsl:value-of select="./@xmi:id"/>';
		</xsl:when>
		<xsl:when test="$nodetype='uml:SendSignalAction'">
		<xsl:variable name="comment" select="./ownedComment/@body"/>
		<xsl:variable name="signalname" select="./xmi:Extension/taggedValue[@tag='signal']/@value"/>
UPDATE "action_steps" set "bezeichnung" = '<xsl:value-of select="$signalname"/>' where "bezeichnung" = '<xsl:value-of select="./@xmi:id"/>';
		</xsl:when>
		<xsl:when test="$nodetype='uml:DecisionNode'">
UPDATE "action_steps" set "bezeichnung" = '<xsl:value-of select="./@name"/>' where "bezeichnung" = '<xsl:value-of select="./@xmi:id"/>';
		</xsl:when>
		<xsl:when test="$nodetype='uml:OpaqueAction'">
		<xsl:variable name="comment" select="./ownedComment/@body"/>
UPDATE "action_steps" set "bezeichnung" = '<xsl:value-of select="./@name"/>' where "bezeichnung" = '<xsl:value-of select="./@xmi:id"/>';
		</xsl:when>
		<xsl:when test="$nodetype='uml:FinalNode'">
UPDATE "action_steps" set "bezeichnung" = 'FinalNode' where "bezeichnung" = '<xsl:value-of select="./@xmi:id"/>';
		</xsl:when>
		<xsl:otherwise>
-- Nodetype <xsl:value-of select="$nodetype"/> not known.
		</xsl:otherwise>
	</xsl:choose>
</xsl:for-each>
	</xsl:when>
	<xsl:when test="$TargetDBType='MSSQL'">
-- Create activity nodes for MSSQL
<xsl:for-each select="//packagedElement[@xmi:id=$ID]/node">
	<xsl:variable name="nodetype" select="@xmi:type"/>
		<xsl:variable name="stereotype" select="./xmi:Extension/stereotype/@name"/>
	<xsl:choose>
		<xsl:when test="$nodetype='uml:InitialNode'">
-- Node <xsl:value-of select="$nodetype"/>.
select "CreateInitialNode"('<xsl:value-of select="$ID"/>', '<xsl:value-of select="$Name"/>', '<xsl:value-of select="./@xmi:id"/>', '<xsl:value-of select="./@name"/>', '<xsl:value-of select="$stereotype"/>');
		</xsl:when>
		<xsl:when test="$nodetype='uml:DecisionNode'">
-- Node <xsl:value-of select="$nodetype"/>.
select "CreateDecisionNode"('<xsl:value-of select="$ID"/>', '<xsl:value-of select="$Name"/>', '<xsl:value-of select="./@xmi:id"/>', '<xsl:value-of select="./@name"/>', '<xsl:value-of select="$stereotype"/>');
		</xsl:when>
		<xsl:when test="$nodetype='uml:OpaqueAction'">
-- Node <xsl:value-of select="$nodetype"/>.
select "CreateOpaqueAction"('<xsl:value-of select="$ID"/>', '<xsl:value-of select="$Name"/>', '<xsl:value-of select="./@xmi:id"/>', '<xsl:value-of select="./@name"/>', '<xsl:value-of select="$stereotype"/>', '<xsl:value-of select="./body"/>'); 
		</xsl:when>
		<xsl:when test="$nodetype='uml:FinalNode'">
		</xsl:when>
		<xsl:otherwise>
-- Nodetype <xsl:value-of select="$nodetype"/> not known.
		</xsl:otherwise>
	</xsl:choose>
</xsl:for-each>
-- Create activity transitions
<xsl:for-each select="//packagedElement[@xmi:id=$ID]/edge">
	<xsl:variable name="edgetype" select="@xmi:type"/>
	<xsl:variable name="stereotype" select="./xmi:Extension/stereotype/@name"/>
	<xsl:choose>
		<xsl:when test="$edgetype='uml:ControlFlow'">
			<xsl:variable name="expression" select="./guard[@xmi:type='uml:OpaqueExpression']/body"/>
select "CreateControlFlow"('<xsl:value-of select="$ID"/>', '<xsl:value-of select="$Name"/>', '<xsl:value-of select="./@xmi:id"/>', '<xsl:value-of select="./@name"/>', '<xsl:value-of select="$stereotype"/>', '<xsl:value-of select="./@source"/>', '<xsl:value-of select="./@target"/>', '<xsl:value-of select="$expression"/>');
		</xsl:when>
		<xsl:otherwise>
-- Nodetype <xsl:value-of select="$edgetype"/> not known.
		</xsl:otherwise>
	</xsl:choose>
</xsl:for-each>
-- Create activity desicions
<xsl:for-each select="//packagedElement[@xmi:id=$ID]/node">
	<xsl:variable name="nodetype" select="@xmi:type"/>
		<xsl:variable name="stereotype" select="./xmi:Extension/stereotype/@name"/>
	<xsl:choose>
		<xsl:when test="$nodetype='uml:DecisionNode'">
			<xsl:variable name="decision" select="./@xmi:id"/>
			<xsl:variable name="incoming" select="./incoming/@xmi:idref"/>
			<xsl:for-each select="./outgoing">
-- Node <xsl:value-of select="$nodetype"/>.
select "CreateDecisionPath"('<xsl:value-of select="$ID"/>', '<xsl:value-of select="$Name"/>', '<xsl:value-of select="$decision"/>', '<xsl:value-of select="./@name"/>', '<xsl:value-of select="$stereotype"/>', '<xsl:value-of select="$incoming"/>', '<xsl:value-of select="./@xmi:idref"/>');
			</xsl:for-each>
		</xsl:when>
		<xsl:when test="$nodetype='uml:OpaqueAction'">
		</xsl:when>
		<xsl:when test="$nodetype='uml:FinalNode'">
		</xsl:when>
		<xsl:otherwise>
-- Nodetype <xsl:value-of select="$nodetype"/> not known.
		</xsl:otherwise>
	</xsl:choose>
</xsl:for-each>
	</xsl:when>
	<xsl:otherwise>
-- Error: Target database '<xsl:value-of select="$TargetDatabaseType"/>' not support yet.
	</xsl:otherwise>
</xsl:choose>

-- Cleanup unused double types
DELETE FROM "action_types" where "id" NOT IN (SELECT "typ" from "actions") AND "id" NOT IN (SELECT "type" from "action_steps");

</xsl:template>

	<!--<xsl:template match="XMI.content">
	    <xsl:apply-templates/>
	</xsl:template>-->
</xsl:stylesheet>
