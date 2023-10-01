@rem This batch will build the wxWidgets library after the installation.

echo dummy > readme.txt

call watcomenv.bat exit

@rem Override WXDIR from this point on. wxWidgets uses Windows backslash for path separators. 
set WXDIR=%DEVLW%\lbDMF\Develop\wxwin\wx
set MINGWBIN=%DEVLW%\%BASE%\Tools\mingw\bin;%DEVLW%\%BASE%\Tools\mingw32\bin

@rem Get an explicite version that always ensures to build the code
set MINGW_STICKON_VERSION=4.7.*
set MINGW_STICKON_WIN32_VERSION=4.0.3-*
@rem set WX_VERSION=2.8.12
@rem https://github.com/wxWidgets/wxWidgets/releases/download/v3.2.2.1/wxMSW-3.2.2.1-Setup.exe
set WX_VERSION=3.2.2.1
set WX_DOWNLOAD=https://github.com/wxWidgets/wxWidgets/releases/download/v%WX_VERSION%/wxMSW-%WX_VERSION%-Setup.exe
set Path=%SystemRoot%\system32

set Path=%Path%;%MINGWBIN%

rem set Path=%Path%;Q:\develop\Tools\Bakefile\src

echo del readme.txt > doBuildWx.bat

echo set DRIVE=%DEVLW% >> doBuildWx.bat
echo set WXDIR=%DEVLW%\lbDMF\Develop\wxwin\wx >> doBuildWx.bat
echo %DEVLW% >> doBuildWx.bat
echo IF NOT EXIST %DEVLW%\lbDMF\Develop\Projects\lbdmf\vendor\libxslt-1.1.34.tar.gz ( >> doBuildWx.bat
echo curl -k -L -o %DEVLW%\lbDMF\Develop\Projects\lbdmf\vendor\libxslt-1.1.34.tar.gz ftp://xmlsoft.org/libxml2/libxslt-1.1.34.tar.gz >> doBuildWx.bat
echo ) >> doBuildWx.bat
echo IF NOT EXIST %DEVLW%\lbDMF\Develop\Tools\mingw32\bin\gcc.exe ( >> doBuildWx.bat
echo call %DEVLW%\lbDMF\installMinGW.bat %MINGW_STICKON_VERSION% %MINGW_STICKON_WIN32_VERSION% >> doBuildWx.bat
rem echo copy /Y %DEVLW%\lbDMF\commctrl-wxWidgets-patch.h Develop\Tools\MinGW\include\commctrl.h >> doBuildWx.bat
rem echo copy /Y %DEVLW%\lbDMF\w32api-Wcpp-patch.h Develop\Tools\MinGW\include\w32api.h >> doBuildWx.bat
echo ) >> doBuildWx.bat
echo IF NOT EXIST %DEVLW%\lbDMF\Develop\Projects\bin\bison.exe ( >> doBuildWx.bat
echo curl -k -L -o lbDMF-BinbuildTools-1.3.3-vc.exe http://sourceforge.net/projects/lbdmf/files/lbdmf/lbDMF-1.3.3/lbDMF-BinbuildTools-1.3.3-vc.exe/download >> doBuildWx.bat
echo lbDMF-BinbuildTools-1.3.3-vc.exe /VERYSILENT /SP- /DIR=%DEVLW%\lbDMF >> doBuildWx.bat
echo ) >> doBuildWx.bat
echo IF NOT EXIST %WXDIR%\build\msw ( >> doBuildWx.bat
echo curl -k -L -o wxMSW-%WX_VERSION%-Setup.exe %WX_DOWNLOAD% >> doBuildWx.bat
echo wxMSW-%WX_VERSION%-Setup.exe /VERYSILENT /SP- /DIR=%WXDIR% >> doBuildWx.bat
echo ) >> doBuildWx.bat
echo cd %WXDIR%\build\msw >> doBuildWx.bat
echo copy /Y %WXDIR%\include\wx\msw\setup.h %WXDIR%\include\wx >> doBuildWx.bat
echo copy /Y %DEVLW%\lbDMF\wxWidgets-config-debug.gcc %WXDIR%\build\msw\config.gcc >> doBuildWx.bat
echo mingw32-make -f makefile.gcc clean >> doBuildWx.bat
echo set Path=%SystemRoot%\system32 >> doBuildWx.bat
echo set MINGWBIN=%DEVLW%\%BASE%\Tools\mingw\bin >> doBuildWx.bat
echo set Path=%Path%;%MINGWBIN% >> doBuildWx.bat
echo mingw32-make -f makefile.gcc all >> doBuildWx.bat
echo copy %WXDIR%\lib\gcc_dll\*.dll %DEVLW%\%BASE%\Projects\dll >> doBuildWx.bat
echo IF NOT EXIST %DEVLW%\lbDMF\XSLT ( >> doBuildWx.bat
echo xcopy %DEVLW%\lbDMF\Develop\Projects\lbdmf\AppDevelopmentDemo\DynamicApp\XSLT_Templates %DEVLW%\lbDMF >> doBuildWx.bat
echo move %DEVLW%\lbDMF\XSLT_Templates %DEVLW%\lbDMF\XSLT >> doBuildWx.bat
echo ) >> doBuildWx.bat
echo IF NOT EXIST %DEVLW%\lbDMF\UMLSamples ( >> doBuildWx.bat
echo xcopy %DEVLW%\lbDMF\Develop\Projects\lbdmf\AppDevelopmentDemo\DynamicApp\UMLSamples %DEVLW%\lbDMF >> doBuildWx.bat
echo ) >> doBuildWx.bat

@rem After installing msys, bunzip2 is available and watcomenv.bat sets up PATH

echo IF EXIST %DEVLW%\lbDMF\GetACE.txt ( call %DEVLW%\lbDMF\InstallACE.bat ) >> doBuildWx.bat
echo IF EXIST %DEVLW%\lbDMF\GetDoUMLBin.txt ( call %DEVLW%\lbDMF\InstallDoUMLBin.bat ) >> doBuildWx.bat
echo IF EXIST %DEVLW%\lbDMF\GetDoUMLSrc.txt ( call %DEVLW%\lbDMF\InstallDoUMLSrc.bat ) >> doBuildWx.bat
echo cd %DEVLW%\lbDMF >> doBuildWx.bat
call watcomenv.bat %DEVLW%\lbDMF\doBuildWx.bat
