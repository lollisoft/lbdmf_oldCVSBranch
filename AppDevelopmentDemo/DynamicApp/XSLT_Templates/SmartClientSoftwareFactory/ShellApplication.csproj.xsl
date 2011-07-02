<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="exsl.xsl"/>

<xsl:template name="ShellApplication.csproj">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/>&lt;Project DefaultTargets="Build" xmlns="http://schemas.microsoft.com/developer/msbuild/2003" ToolsVersion="3.5"&gt;
  &lt;PropertyGroup&gt;
    &lt;Configuration Condition=" '$(Configuration)' == '' "&gt;Debug&lt;/Configuration&gt;
    &lt;Platform Condition=" '$(Platform)' == '' "&gt;AnyCPU&lt;/Platform&gt;
    &lt;ProductVersion&gt;9.0.30729&lt;/ProductVersion&gt;
    &lt;SchemaVersion&gt;2.0&lt;/SchemaVersion&gt;
    &lt;ProjectGuid&gt;{27939947-5B62-4C4C-99FF-898BF0C71D07}&lt;/ProjectGuid&gt;
    &lt;OutputType&gt;WinExe&lt;/OutputType&gt;
    &lt;AppDesignerFolder&gt;Properties&lt;/AppDesignerFolder&gt;
    &lt;RootNamespace&gt;ShellApplication&lt;/RootNamespace&gt;
    &lt;AssemblyName&gt;ShellApplication&lt;/AssemblyName&gt;
    &lt;FileUpgradeFlags&gt;
    &lt;/FileUpgradeFlags&gt;
    &lt;OldToolsVersion&gt;2.0&lt;/OldToolsVersion&gt;
    &lt;UpgradeBackupLocation&gt;
    &lt;/UpgradeBackupLocation&gt;
    &lt;TargetFrameworkVersion&gt;v3.5&lt;/TargetFrameworkVersion&gt;
    &lt;PublishUrl&gt;publish\&lt;/PublishUrl&gt;
    &lt;Install&gt;true&lt;/Install&gt;
    &lt;InstallFrom&gt;Disk&lt;/InstallFrom&gt;
    &lt;UpdateEnabled&gt;false&lt;/UpdateEnabled&gt;
    &lt;UpdateMode&gt;Foreground&lt;/UpdateMode&gt;
    &lt;UpdateInterval&gt;7&lt;/UpdateInterval&gt;
    &lt;UpdateIntervalUnits&gt;Days&lt;/UpdateIntervalUnits&gt;
    &lt;UpdatePeriodically&gt;false&lt;/UpdatePeriodically&gt;
    &lt;UpdateRequired&gt;false&lt;/UpdateRequired&gt;
    &lt;MapFileExtensions&gt;true&lt;/MapFileExtensions&gt;
    &lt;ApplicationRevision&gt;0&lt;/ApplicationRevision&gt;
    &lt;ApplicationVersion&gt;1.0.0.%2a&lt;/ApplicationVersion&gt;
    &lt;IsWebBootstrapper&gt;false&lt;/IsWebBootstrapper&gt;
    &lt;UseApplicationTrust&gt;false&lt;/UseApplicationTrust&gt;
    &lt;BootstrapperEnabled&gt;true&lt;/BootstrapperEnabled&gt;
  &lt;/PropertyGroup&gt;
  &lt;PropertyGroup Condition=" '$(Configuration)|$(Platform)' == 'Debug|AnyCPU' "&gt;
    &lt;DebugSymbols&gt;true&lt;/DebugSymbols&gt;
    &lt;DebugType&gt;full&lt;/DebugType&gt;
    &lt;Optimize&gt;false&lt;/Optimize&gt;
    &lt;OutputPath&gt;bin\Debug\&lt;/OutputPath&gt;
    &lt;DefineConstants&gt;DEBUG;TRACE&lt;/DefineConstants&gt;
    &lt;ErrorReport&gt;prompt&lt;/ErrorReport&gt;
    &lt;WarningLevel&gt;4&lt;/WarningLevel&gt;
  &lt;/PropertyGroup&gt;
  &lt;PropertyGroup Condition=" '$(Configuration)|$(Platform)' == 'Release|AnyCPU' "&gt;
    &lt;DebugType&gt;pdbonly&lt;/DebugType&gt;
    &lt;Optimize&gt;true&lt;/Optimize&gt;
    &lt;OutputPath&gt;bin\Release\&lt;/OutputPath&gt;
    &lt;DefineConstants&gt;TRACE&lt;/DefineConstants&gt;
    &lt;ErrorReport&gt;prompt&lt;/ErrorReport&gt;
    &lt;WarningLevel&gt;4&lt;/WarningLevel&gt;
  &lt;/PropertyGroup&gt;
  &lt;ItemGroup&gt;
    &lt;Reference Include="Microsoft.Practices.ObjectBuilder, Version=1.0.51206.0, Culture=neutral, PublicKeyToken=b03f5f7f11d50a3a, processorArchitecture=MSIL"&gt;
      &lt;SpecificVersion&gt;False&lt;/SpecificVersion&gt;
      &lt;HintPath&gt;..\..\Lib\Microsoft.Practices.ObjectBuilder.dll&lt;/HintPath&gt;
    &lt;/Reference&gt;
    &lt;Reference Include="System" /&gt;
    &lt;Reference Include="System.Core"&gt;
      &lt;RequiredTargetFramework&gt;3.5&lt;/RequiredTargetFramework&gt;
    &lt;/Reference&gt;
    &lt;Reference Include="System.Data" /&gt;
    &lt;Reference Include="System.Deployment" /&gt;
    &lt;Reference Include="System.Drawing" /&gt;
    &lt;Reference Include="System.Windows.Forms" /&gt;
    &lt;Reference Include="System.Xml" /&gt;
  &lt;/ItemGroup&gt;
  &lt;ItemGroup&gt;
    &lt;Compile Include="CommandMap.cs"&gt;
      &lt;DependentUpon&gt;CommandMap.xsd&lt;/DependentUpon&gt;
    &lt;/Compile&gt;
    &lt;Compile Include="MainController.cs" /&gt;
    &lt;Compile Include="ShellApplication.cs" /&gt;
    &lt;Compile Include="ShellForm.cs"&gt;
      &lt;SubType&gt;Form&lt;/SubType&gt;
    &lt;/Compile&gt;
    &lt;Compile Include="ShellForm.Designer.cs"&gt;
      &lt;DependentUpon&gt;ShellForm.cs&lt;/DependentUpon&gt;
    &lt;/Compile&gt;
    &lt;Compile Include="Properties\AssemblyInfo.cs" /&gt;
    &lt;EmbeddedResource Include="Properties\Resources.resx"&gt;
      &lt;Generator&gt;ResXFileCodeGenerator&lt;/Generator&gt;
      &lt;LastGenOutput&gt;Resources.Designer.cs&lt;/LastGenOutput&gt;
      &lt;SubType&gt;Designer&lt;/SubType&gt;
    &lt;/EmbeddedResource&gt;
    &lt;EmbeddedResource Include="ShellForm.resx"&gt;
      &lt;SubType&gt;Designer&lt;/SubType&gt;
      &lt;DependentUpon&gt;ShellForm.cs&lt;/DependentUpon&gt;
    &lt;/EmbeddedResource&gt;
    &lt;Compile Include="Properties\Resources.Designer.cs"&gt;
      &lt;AutoGen&gt;True&lt;/AutoGen&gt;
      &lt;DependentUpon&gt;Resources.resx&lt;/DependentUpon&gt;
      &lt;DesignTime&gt;True&lt;/DesignTime&gt;
    &lt;/Compile&gt;
    &lt;None Include="CommandMap.xsd" /&gt;
    &lt;None Include="CommandMap.xsx"&gt;
      &lt;DependentUpon&gt;CommandMap.xsd&lt;/DependentUpon&gt;
    &lt;/None&gt;
    &lt;None Include="Properties\Settings.settings"&gt;
      &lt;Generator&gt;SettingsSingleFileGenerator&lt;/Generator&gt;
      &lt;LastGenOutput&gt;Settings.Designer.cs&lt;/LastGenOutput&gt;
    &lt;/None&gt;
    &lt;Compile Include="Properties\Settings.Designer.cs"&gt;
      &lt;AutoGen&gt;True&lt;/AutoGen&gt;
      &lt;DependentUpon&gt;Settings.settings&lt;/DependentUpon&gt;
      &lt;DesignTimeSharedInput&gt;True&lt;/DesignTimeSharedInput&gt;
    &lt;/Compile&gt;
    &lt;Compile Include="ShellWorkItem.cs"&gt;
    &lt;/Compile&gt;
    &lt;Content Include="ProfileCatalog.xml"&gt;
      &lt;CopyToOutputDirectory&gt;Always&lt;/CopyToOutputDirectory&gt;
    &lt;/Content&gt;
  &lt;/ItemGroup&gt;
  &lt;ItemGroup&gt;
    &lt;ProjectReference Include="..\..\Blocks\CAB\CS\Source\CompositeUI\CompositeUI.csproj"&gt;
      &lt;Project&gt;{C478E40B-A05E-4C69-9AB3-7A3BB374243F}&lt;/Project&gt;
      &lt;Name&gt;CompositeUI&lt;/Name&gt;
    &lt;/ProjectReference&gt;
    &lt;ProjectReference Include="..\..\Blocks\CAB\CS\Source\CompositeUI.WinForms\CompositeUI.WinForms.csproj"&gt;
      &lt;Project&gt;{073BCD60-F2FB-4DB9-92FB-403C8F9E8DD0}&lt;/Project&gt;
      &lt;Name&gt;CompositeUI.WinForms&lt;/Name&gt;
    &lt;/ProjectReference&gt;
  &lt;/ItemGroup&gt;
  &lt;ItemGroup&gt;
    &lt;BootstrapperPackage Include="Microsoft.Net.Framework.2.0"&gt;
      &lt;Visible&gt;False&lt;/Visible&gt;
      &lt;ProductName&gt;.NET Framework 2.0 %28x86%29&lt;/ProductName&gt;
      &lt;Install&gt;true&lt;/Install&gt;
    &lt;/BootstrapperPackage&gt;
    &lt;BootstrapperPackage Include="Microsoft.Net.Framework.3.0"&gt;
      &lt;Visible&gt;False&lt;/Visible&gt;
      &lt;ProductName&gt;.NET Framework 3.0 %28x86%29&lt;/ProductName&gt;
      &lt;Install&gt;false&lt;/Install&gt;
    &lt;/BootstrapperPackage&gt;
    &lt;BootstrapperPackage Include="Microsoft.Net.Framework.3.5"&gt;
      &lt;Visible&gt;False&lt;/Visible&gt;
      &lt;ProductName&gt;.NET Framework 3.5&lt;/ProductName&gt;
      &lt;Install&gt;false&lt;/Install&gt;
    &lt;/BootstrapperPackage&gt;
  &lt;/ItemGroup&gt;
  &lt;Import Project="$(MSBuildBinPath)\Microsoft.CSharp.targets" /&gt;
  &lt;!-- To modify your build process, add your task inside one of the targets below and uncomment it. 
       Other similar extension points exist, see Microsoft.Common.targets.
  &lt;Target Name="BeforeBuild"&gt;
  &lt;/Target&gt;
  &lt;Target Name="AfterBuild"&gt;
  &lt;/Target&gt;
  --&gt;
&lt;/Project&gt;
</xsl:template>
</xsl:stylesheet>