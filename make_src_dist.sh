#!/bin/sh
export DEVROOT=dist/Develop/Projects/CPP

ARCH=`arch`

if [ "$1" == "" ]; then
	echo No version parameter given.
	echo Sample: $0 0.7.1
	exit;
fi

if [ -e "dist" ]; then
	rm -Rf dist;
fi

mkdir dist
cd dist

if [ "$ARCH" == "ppc" ]; then
	mkdir Projects
	cd Projects
fi

# Building HEAD revision
#cvs -d:ext:lollisoft@lbdmf.cvs.sourceforge.net:/cvsroot/lbdmf export -r HEAD CPP

# Building branch revision
cvs -d:ext:lollisoft@lbdmf.cvs.sourceforge.net:/cvsroot/lbdmf export -r Release_1_0_4_stable_rc1_branch CPP

cp ~/develop/Projects/CPP/Plugins/DatabaseReport/repwrt.cpp CPP/Plugins/DatabaseReport/repwrt.cpp
cp ~/develop/Projects/CPP/Plugins/DatabaseReport/repwrt.h CPP/Plugins/DatabaseReport/repwrt.h

# Remove some vendor packages, I do not use yet.

rm -R CPP/vendor/c-goldparser
if [ "$ARCH" == "ppc" ]; then
	cp CPP/configure ..
	/Developer/Applications/Utilities/PackageMaker.app/Contents/MacOS/PackageMaker -build \
		-p ~/Pakete/lbDMF-$1.pkg -f ~/develop/Projects/CPP/dist \
		-i ~/Pakete/Info.plist -d ~/Pakete/Description.plist
	rm -r /Users/lothar/develop/Projects/CPP/bindist/Package_contents/usr
	mkdir /Users/lothar/develop/Projects/CPP/bindist/Package_contents/usr
	mkdir /Users/lothar/develop/Projects/CPP/bindist/Package_contents/usr/local
	mkdir /Users/lothar/develop/Projects/CPP/bindist/Package_contents/usr/local/lib
	cp /usr/local/lib/libwx_macd_Lollisoft-2.6.0.2.0.dylib /Users/lothar/develop/Projects/CPP/bindist/Package_contents/usr/local/lib/libwx_macd_Lollisoft-2.6.0.2.0.dylib
	cd /Users/lothar/develop/Projects/CPP/bindist/Package_contents/usr/local/lib
	ln -s libwx_macd_Lollisoft-2.6.0.2.0.dylib libwx_macd_Lollisoft-2.6.0.dylib
	ln -s libwx_macd_Lollisoft-2.6.0.dylib libwx_macd_Lollisoft-2.6.dylib

	exit;
fi

echo Do Linux stuff
mkdir -p lbdmf-$1/Projects
mv CPP lbdmf-$1/Projects
cp lbdmf-$1/Projects/CPP/configure lbdmf-$1
tar cvzf lbdmf-$1.tgz lbdmf-$1/
cp lbdmf-$1.tgz /usr/src/packages/SOURCES
cd ..

if [ "$2" == "" ]; then
	rpmbuild --nodeps -ba lbdmf.spec
fi

if [ "$2" == "debug" ]; then
	rpmbuild --nodeps -ba lbdmf-debug.spec
fi
