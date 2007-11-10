<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<!-- Helper to create multible files. -->
<xsl:import href="../include/exsl.xsl"/>

<xsl:import href="../include/lbDMFBaseTemplates.xsl"/>

<!-- Template to create base class file for fixed database forms -->
<xsl:import href="wxARGFixedFormBaseclass.xsl"/>

<!-- Template to create formular implementation code per formular definition -->
<xsl:import href="wxARGFixedFormImplementation.xsl"/>

<!-- Template to create application main module -->
<xsl:import href="wxARGApplicationModul.xsl"/>

<xsl:output method="text" indent="no"/>

<xsl:template match="lbDMF">
Export application code to <xsl:value-of select="$basedir"/>


<!-- Create the base class file and it's header file -->
<xsl:call-template name="CreateFixedFormBaseclass"/>

<xsl:call-template name="createMakeFileModule_ApplicationModule">
<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
</xsl:call-template>

<xsl:call-template name="createMakeFileModule_FormularModul">
<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
</xsl:call-template>

<xsl:call-template name="createApplicationHeader">
<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
</xsl:call-template>

<xsl:call-template name="createApplicationModule">
<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
</xsl:call-template>


<xsl:variable name="ApplicationID" select="//lbDMF/@applicationid"/>
<xsl:variable name="OrginalApplicationName" select="//lbDMF/applications/application[@ID=$ApplicationID]/@name"/>
<xsl:variable name="ApplicationName" select="concat(substring-before($OrginalApplicationName, ' '), substring-after($OrginalApplicationName, ' '))"/>


<!-- === Formular specific template ====================================================================== -->

<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID]">
<xsl:variable name="tempFormularName" select="@name"/>
<xsl:variable name="FormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularName"/>
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

<xsl:call-template name="CreateFixedFormImplementation">
<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
<xsl:with-param name="FormularID" select="@ID"/>
<xsl:with-param name="FormName" select="$FormularName"/>
</xsl:call-template>
</xsl:for-each>
</xsl:template>

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
</xsl:stylesheet>