#!/bin/bash

CVS_RSH=ssh
MODULELIB=lbModule.so
LBXMLFUNCTOR=getlbDOMConfigInstance
LBMODULEFUNCTOR=getlb_ModuleInstance
DEVROOT=~/develop
LD_LIBRARY_PATH=~/lib:/Users/lothar/develop/Projects/CPP/vendor/ACE_wrappers/lib:/Users/lothar/develop/Projects/CPP/vendor/ACE_wrappers/TAO/tao:
PLUGIN_DIR=~/plugins
OSTYPE=osx
OSVERSION=`uname -r`
OSPLATFORM=`uname -p`
PATH="/sw/bin:/sw/sbin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/X11R6/bin:~/bin:/usr/local/bin:/Users/lothar/develop/Projects/CPP/vendor/ACE_wrappers/lib:/Users/lothar/develop/Projects/CPP/vendor/ACE_wrappers/TAO/tao:"

export CVS_RSH
export MODULELIB
export LBXMLFUNCTOR
export LBMODULEFUNCTOR
export DEVROOT
export LD_LIBRARY_PATH
export PLUGIN_DIR 
export OSTYPE
export OSVERSION
export OSPLATFORM
export PATH
