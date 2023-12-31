﻿<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="../exsl.xsl"/>

<xsl:template name="Resources.resx">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/>&lt;?xml version="1.0" encoding="utf-8"?&gt;
&lt;root&gt;
  &lt;!-- 
    Microsoft ResX Schema 
    
    Version 2.0
    
    The primary goals of this format is to allow a simple XML format 
    that is mostly human readable. The generation and parsing of the 
    various data types are done through the TypeConverter classes 
    associated with the data types.
    
    Example:
    
    ... ado.net/XML headers &amp; schema ...
    &lt;resheader name="resmimetype"&gt;text/microsoft-resx&lt;/resheader&gt;
    &lt;resheader name="version"&gt;2.0&lt;/resheader&gt;
    &lt;resheader name="reader"&gt;System.Resources.ResXResourceReader, System.Windows.Forms, ...&lt;/resheader&gt;
    &lt;resheader name="writer"&gt;System.Resources.ResXResourceWriter, System.Windows.Forms, ...&lt;/resheader&gt;
    &lt;data name="Name1"&gt;&lt;value&gt;this is my long string&lt;/value&gt;&lt;comment&gt;this is a comment&lt;/comment&gt;&lt;/data&gt;
    &lt;data name="Color1" type="System.Drawing.Color, System.Drawing"&gt;Blue&lt;/data&gt;
    &lt;data name="Bitmap1" mimetype="application/x-microsoft.net.object.binary.base64"&gt;
        &lt;value&gt;[base64 mime encoded serialized .NET Framework object]&lt;/value&gt;
    &lt;/data&gt;
    &lt;data name="Icon1" type="System.Drawing.Icon, System.Drawing" mimetype="application/x-microsoft.net.object.bytearray.base64"&gt;
        &lt;value&gt;[base64 mime encoded string representing a byte array form of the .NET Framework object]&lt;/value&gt;
        &lt;comment&gt;This is a comment&lt;/comment&gt;
    &lt;/data&gt;
                
    There are any number of "resheader" rows that contain simple 
    name/value pairs.
    
    Each data row contains a name, and value. The row also contains a 
    type or mimetype. Type corresponds to a .NET class that support 
    text/value conversion through the TypeConverter architecture. 
    Classes that don't support this are serialized and stored with the 
    mimetype set.
    
    The mimetype is used for serialized objects, and tells the 
    ResXResourceReader how to depersist the object. This is currently not 
    extensible. For a given mimetype the value must be set accordingly:
    
    Note - application/x-microsoft.net.object.binary.base64 is the format 
    that the ResXResourceWriter will generate, however the reader can 
    read any of the formats listed below.
    
    mimetype: application/x-microsoft.net.object.binary.base64
    value   : The object must be serialized with 
            : System.Serialization.Formatters.Binary.BinaryFormatter
            : and then encoded with base64 encoding.
    
    mimetype: application/x-microsoft.net.object.soap.base64
    value   : The object must be serialized with 
            : System.Runtime.Serialization.Formatters.Soap.SoapFormatter
            : and then encoded with base64 encoding.

    mimetype: application/x-microsoft.net.object.bytearray.base64
    value   : The object must be serialized into a byte array 
            : using a System.ComponentModel.TypeConverter
            : and then encoded with base64 encoding.
    --&gt;
  &lt;xsd:schema id="root" xmlns="" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:msdata="urn:schemas-microsoft-com:xml-msdata"&gt;
    &lt;xsd:element name="root" msdata:IsDataSet="true"&gt;
      &lt;xsd:complexType&gt;
        &lt;xsd:choice maxOccurs="unbounded"&gt;
          &lt;xsd:element name="metadata"&gt;
            &lt;xsd:complexType&gt;
              &lt;xsd:sequence&gt;
                &lt;xsd:element name="value" type="xsd:string" minOccurs="0" /&gt;
              &lt;/xsd:sequence&gt;
              &lt;xsd:attribute name="name" type="xsd:string" /&gt;
              &lt;xsd:attribute name="type" type="xsd:string" /&gt;
              &lt;xsd:attribute name="mimetype" type="xsd:string" /&gt;
            &lt;/xsd:complexType&gt;
          &lt;/xsd:element&gt;
          &lt;xsd:element name="assembly"&gt;
            &lt;xsd:complexType&gt;
              &lt;xsd:attribute name="alias" type="xsd:string" /&gt;
              &lt;xsd:attribute name="name" type="xsd:string" /&gt;
            &lt;/xsd:complexType&gt;
          &lt;/xsd:element&gt;
          &lt;xsd:element name="data"&gt;
            &lt;xsd:complexType&gt;
              &lt;xsd:sequence&gt;
                &lt;xsd:element name="value" type="xsd:string" minOccurs="0" msdata:Ordinal="1" /&gt;
                &lt;xsd:element name="comment" type="xsd:string" minOccurs="0" msdata:Ordinal="2" /&gt;
              &lt;/xsd:sequence&gt;
              &lt;xsd:attribute name="name" type="xsd:string" msdata:Ordinal="1" /&gt;
              &lt;xsd:attribute name="type" type="xsd:string" msdata:Ordinal="3" /&gt;
              &lt;xsd:attribute name="mimetype" type="xsd:string" msdata:Ordinal="4" /&gt;
            &lt;/xsd:complexType&gt;
          &lt;/xsd:element&gt;
          &lt;xsd:element name="resheader"&gt;
            &lt;xsd:complexType&gt;
              &lt;xsd:sequence&gt;
                &lt;xsd:element name="value" type="xsd:string" minOccurs="0" msdata:Ordinal="1" /&gt;
              &lt;/xsd:sequence&gt;
              &lt;xsd:attribute name="name" type="xsd:string" use="required" /&gt;
            &lt;/xsd:complexType&gt;
          &lt;/xsd:element&gt;
        &lt;/xsd:choice&gt;
      &lt;/xsd:complexType&gt;
    &lt;/xsd:element&gt;
  &lt;/xsd:schema&gt;
  &lt;resheader name="resmimetype"&gt;
    &lt;value&gt;text/microsoft-resx&lt;/value&gt;
  &lt;/resheader&gt;
  &lt;resheader name="version"&gt;
    &lt;value&gt;2.0&lt;/value&gt;
  &lt;/resheader&gt;
  &lt;resheader name="reader"&gt;
    &lt;value&gt;System.Resources.ResXResourceReader, System.Windows.Forms, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089&lt;/value&gt;
  &lt;/resheader&gt;
  &lt;resheader name="writer"&gt;
    &lt;value&gt;System.Resources.ResXResourceWriter, System.Windows.Forms, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089&lt;/value&gt;
  &lt;/resheader&gt;
&lt;/root&gt;
</xsl:template>
</xsl:stylesheet>