@rem ACE Delete Problem: del /Q /S \\?\C:\lbDMF

@rem This batch will flag the installation and building of ACE.

if NOT EXIST C:\lbDMF\Develop\Projects\CPP\vendor\ACE+TAO+CIAO-6.1.0.tar (
	cd C:\lbDMF\Develop\Projects\CPP\vendor
	C:\lbDMF\wget http://download.dre.vanderbilt.edu/previous_versions/ACE+TAO+CIAO-6.1.0.tar.bz2
	C:\lbDMF\Develop\Tools\MinGW\msys\1.0\bin\bunzip2 ACE+TAO+CIAO-6.1.0.tar.bz2
	C:\lbDMF\Develop\Tools\MinGW\msys\1.0\bin\tar xvf ACE+TAO+CIAO-6.1.0.tar
)

@SET DEVLW=C:
@SET ACE_ROOT=%DEVLW%\lbDMF\Develop\Projects\CPP\vendor\ACE_wrappers

@rem Post prepare
@rem Use mingw32-make to compile (multiple targets error will be shown by make)

@echo #include "ace/config-win32.h"> %DEVLW%\lbDMF\Develop\Projects\CPP\vendor\ACE_wrappers\ace\config.h
@echo include $(ACE_ROOT)/include/makeinclude/platform_mingw32.GNU> %DEVLW%\lbDMF\Develop\Projects\CPP\vendor\ACE_wrappers\include\makeinclude\platform_macros.GNU

@rem Fixing ACE and TAO issues in version 6.1.0

@rem Override SHLIBBUILD build rule as it does not work using dlltool
@echo SHLIBBUILD = $(CXX) -fPIC -shared -Wl,--enable-auto-import -Wl,--subsystem,windows -mthreads -mwindows -Wl,--out-implib=$(ACE_ROOT)/lib/$@.a -o $@ -L $(ACE_ROOT)/lib $(LDFLAGS) $(VSHOBJS) $(ACE_SHLIBS) $(LIBS)>> %DEVLW%\lbDMF\Develop\Projects\CPP\vendor\ACE_wrappers\include\makeinclude\platform_macros.GNU

@rem Add building 32Bit platform code only
@echo OCFLAGS    += -m32>> %DEVLW%\lbDMF\Develop\Projects\CPP\vendor\ACE_wrappers\include\makeinclude\platform_macros.GNU
@echo OCCFLAGS   += -m32>> %DEVLW%\lbDMF\Develop\Projects\CPP\vendor\ACE_wrappers\include\makeinclude\platform_macros.GNU

@rem TAO AV project needs QoS, but it is not built, thus fix it here
copy %DEVLW%\lbDMF\TAO.orbsvcs.orbsvcs.GNUmakefile %DEVLW%\lbDMF\Develop\Projects\CPP\vendor\ACE_wrappers\TAO\orbsvcs\orbsvcs\GNUmakefile
copy %DEVLW%\lbDMF\TAO.GNUmakefile %DEVLW%\lbDMF\Develop\Projects\CPP\vendor\ACE_wrappers\TAO\GNUmakefile

@rem Important order for the build process. If not correct, created executables were not executable due to broken ACL's of the files (too less rights)
@rem I run into this problem on Windows7 64Bit only if I remember correctly with my own code.
set PATH=%DEVLW%\lbDMF\Develop\Tools\MinGW\msys\1.0\bin;%DEVLW%\lbDMF\Develop\Tools\MinGW\bin;%DEVLW%\lbDMF\Develop\Projects\bin;%ACE_ROOT%\bin;%ACE_ROOT%\lib

cd %DEVLW%\lbDMF\Develop\Projects\CPP\vendor\ACE_wrappers\
mingw32-make
mingw32-make -C TAO
pause