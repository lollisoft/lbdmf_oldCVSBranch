; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
AppName=lbDMF Development Environment
AppVerName=lbDMF Development Environment 1.0.4-stable-rc3
OutputBaseFilename=lbDMF-Source-1.0.4-stable-rc3
AppPublisher=Lothar Behrens
AppPublisherURL=http://www.lollisoft.de
AppSupportURL=http://www.sourceforge.net/projects/lbdmf
AppUpdatesURL=http://www.sourceforge.net/projects/lbdmf
DefaultDirName={sd}\lbDMF
DefaultGroupName=lbDMF
LicenseFile=license.txt
; uncomment the following line if you want your installation to run on NT 3.51 too.
; MinVersion=4,3.51

[Tasks]
Name: "desktopicon"; Description: "Create a &desktop icon"; GroupDescription: "Additional icons:"; MinVersion: 4,4

[Files]
; WGet tool
Source: "Q:\develop\Tools\WGet\bin\*.*"; DestDir: "{app}"; CopyMode: alwaysoverwrite;

; MinGW Get tool
Source: "Q:\develop\Tools\MinGW_Get\*.*"; DestDir: "{app}\Develop\Tools\MinGW"; CopyMode: alwaysoverwrite; Flags: recursesubdirs;

; wxWidgets configuration update
Source: "Q:\Develop\Projects\CPP\wxWidgets-config.gcc"; DestDir: "{app}"; CopyMode: alwaysoverwrite;

;Source: "c:\log\*.*"; DestDir: "c:\log"; CopyMode: alwaysoverwrite
Source: "Q:\Develop\Projects\CPP\Database\*.*"; DestDir: "{app}\Database"; CopyMode: alwaysoverwrite; Flags: recursesubdirs;
Source: "Q:\Develop\Projects\CPP\watcomenv.bat"; DestDir: "{app}"; CopyMode: alwaysoverwrite
Source: "Q:\Develop\Projects\CPP\dist\*.*"; DestDir: "{app}"; CopyMode: alwaysoverwrite; Flags: recursesubdirs;
Source: "Q:\Develop\Projects\dll\psqlodbc.dll"; DestDir: "{app}\Develop\Projects\dll"; CopyMode: alwaysoverwrite;
Source: "Q:\Develop\Projects\CPP\buildwxWidgets_MinGW.bat"; DestDir: "{app}"; CopyMode: alwaysoverwrite;
Source: "Q:\Develop\Projects\CPP\installODBC.bat"; DestDir: "{app}"; CopyMode: alwaysoverwrite;
Source: "Q:\Develop\Projects\CPP\installMinGW.bat"; DestDir: "{app}"; CopyMode: alwaysoverwrite;
Source: "Q:\Develop\Projects\CPP\Test\GUI\wxWrapper\splash.png"; DestDir: "{app}\Develop\Projects\CPP\BaseDevelopment"; CopyMode: alwaysoverwrite;
Source: "Q:\Develop\Projects\CPP\Test\GUI\wxWrapper\toolbarimages\*.*"; DestDir: "{app}\Develop\Projects\CPP\BaseDevelopment\toolbarimages"; CopyMode: alwaysoverwrite;



[Icons]
Name: "{group}\lbDMF Develop"; Filename: "{app}\watcomenv.bat"; WorkingDir: "{app}\develop\projects\cpp\BaseDevelopment"
Name: "{userdesktop}\lbDMF Develop"; Filename: "{app}\watcomenv.bat"; MinVersion: 4,4; Tasks: desktopicon; WorkingDir: "{app}\develop\projects\cpp\BaseDevelopment"
;Name: "{userdesktop}\lbDMF Help"; Filename: "{app}\develop\projects\cpp\Doc\html\index.html"; MinVersion: 4,4; Tasks: desktopicon; WorkingDir: "{app}\develop\projects\cpp\BaseDevelopment"

[Run]
;Filename: "{app}\watcomenv.bat"; Description: "Launch My Program"; Flags: shellexec postinstall skipifsilent
Filename: "{app}\installODBC.bat"; Description: "Install ODBC driver settings"; Flags: shellexec postinstall
Filename: "{app}\buildwxWidgets_MinGW.bat"; Description: "Start building wxWidgets library (will be downloaded)"; Flags: shellexec postinstall
