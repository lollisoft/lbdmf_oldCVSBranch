<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:xmi="http://schema.omg.org/spec/XMI/2.1">
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

<!-- Handling of found associations -->

<xsl:template name="Helper.Lookup.Association">
    <xsl:param name="ID"/><!--  -->
    <xsl:param name="ClassID"/><!--  -->
<!--<xsl:value-of select="//UML:AssociationEnd.participant/UML:Class[@xmi.idref=$ClassID]/../../../../@xmi.id"/>-->
<xsl:for-each select="*">
<xsl:value-of select="@xmi.idref"/>
</xsl:for-each>
</xsl:template>

</xsl:stylesheet>
