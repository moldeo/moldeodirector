AC_INIT([Moldeo Director], [0.9.1.0], [info@moldeointeractive.com.ar], [moldeodirector])

AM_INIT_AUTOMAKE
AC_CONFIG_MACRO_DIR([m4])
AM_CONFIG_HEADER(config.h)

AC_LIBTOOL_CONFIG

AC_PROG_CC
AC_PROG_CC_STDC
AC_C_CONST
AC_PROG_LIBTOOL
AM_PROG_LIBTOOL

AC_PROG_CXX
AC_PROG_CXXCPP
AC_PROG_CXX_C_O


dnl Set install paths.
if test "x$prefix" = "xNONE" ; then
  prefix="/usr/local"
fi
if test "x$exec_prefix" = "xNONE" ; then
  exec_prefix=$prefix
fi

case "$host" in
        *-*-mingw*|*-*-cygwin*)
                AC_DEFINE(PLATFORM_WIN32, 1, [Platform is Win32])
                PLATFORM_STRING="Win32"
                ;;
        x86_64-*linux*)
                with_boost_libdir="/usr/lib/x86_64-linux-gnu"
                PLATFORM_STRING="Linux"
                ;;
        *-*-linux*)
                AC_DEFINE(PLATFORM_LINUX, 1, [Platform is Linux])
                PLATFORM_STRING="Linux"
                ;;
        *-*-darwin*)
		AC_MSG_WARN([Hello])
                AC_DEFINE(PLATFORM_APPLE, 1, [Platform is Apple])
                PLATFORM_STRING="Apple"
                ;;
        *)
                AC_MSG_WARN([*** Please add $host to configure.ac checks!])
                ;;
esac


case "$host" in
        i?86-* | k?-* | athlon-* | pentium*-)
                AC_DEFINE(ARCH_X86, 1, [Architecture is x86])
                ARCH_SPECIFIC_CFLAGS=""
                ARCH_STRING="X86"
                ;;
        x86_64-*)
                AC_DEFINE(ARCH_X86_64, 1, [Architecture is x86-64])
                ARCH_SPECIFIC_CFLAGS="-DUSE_ADDR64"
                ARCH_STRING="X86-64"
                libdir=$prefix"/lib"
                ;;
        ppc-* | powerpc-*)
		AC_MSG_WARN([HI THERE!])
                AC_DEFINE(ARCH_PPC, 1, [Architecture is PowerPC])
                ARCH_SPECIFIC_CFLAGS=""
                ARCH_STRING="PowerPC"
                ;;
        *)
                AC_MSG_ERROR([Unknown Architecture])
                ;;
esac


#dnl check for libmoldeo
PKG_CHECK_MODULES([LIBMOLDEO], [libmoldeo] ,has_libmoldeo=yes)

#dnl check for moldeocontrols
PKG_CHECK_MODULES([MOLDEOCONTROLS], [moldeocontrols] ,has_mnoldeocontrols=yes)

#dnl check for sdl-net
#AC_CHECK_HEADER(SDL/SDL_net.h, , AC_MSG_ERROR([SDL_net header not found.]))
#AC_CHECK_LIB(SDL_net, SDLNet_Init, AC_SUBST([SDL_NET_LIBS], [-lSDL_net]), AC_MSG_ERROR([SDL_net not found.]), [${SDL_LIBS} ${WIN32_LIBS}])

#dnl check for glew
#AC_CHECK_HEADER(GL/glew.h, , AC_MSG_ERROR([glew header not found.]))
#AC_CHECK_LIB(GLEW, glewInit, AC_SUBST([GLEW_LIBS], [-lGLEW]), #AC_MSG_ERROR([glew not found.]), )
PKG_CHECK_MODULES([GLEW], [glew] ,has_glew=yes)

#dnl check for glut
AC_CHECK_HEADER(GL/glut.h, , AC_MSG_ERROR([glut header not found.]))
AC_CHECK_LIB(glut, glutMainLoop, AC_SUBST([GLUT_LIBS], [-lglut]), AC_MSG_ERROR([glut not found.]), )

#dnl check for gle
AC_CHECK_HEADER(GL/gle.h, , AC_MSG_ERROR([gle header not found.]))
AC_CHECK_LIB(gle, gleDestroyGC, AC_SUBST([GLE_LIBS], [-lgle]), AC_MSG_ERROR([gle not found.]), )

#dnl check for ftgl
PKG_CHECK_MODULES([FTGL], [ftgl] ,has_ftgl=yes)

dnl check for freeimage
AC_CHECK_HEADER(FreeImage.h, , AC_MSG_ERROR([FreeImage header not found.]))
AC_CHECK_LIB(freeimage, FreeImage_GetVersion, AC_SUBST([FREEIMAGE_LIBS], [-lfreeimage]), AC_MSG_ERROR([FreeImage not found.]), )

#dnl check for freetype2
AC_CHECK_FT2()

#dnl check boost libraries
AX_BOOST_BASE
AX_BOOST_ASIO
AX_BOOST_THREAD
AX_BOOST_FILESYSTEM

#dnl nvidia-cG-toolkit requires pthread
AC_CHECK_LIB(pthread, pthread_attr_init, LIBS="$LIBS -lpthread")

#dnl check for cg
#AC_LANG_PUSH(C++)dnl
#AC_CHECK_LIB(Cg, cgCreateContext,
#[
	#AC_CHECK_HEADERS(Cg/cg.h,
#	[
		#AC_DEFINE(HAVE_CG, 1, [define if you have libcg])
#		AC_SUBST([CG_LIBS])
		#CG_LIBS="-lCg"
#		have_cg=yes
	#],
#	[
		#AC_MSG_ERROR([cG header file missing or not in Cg/ include subdir])
#	],
	#)
#
#],
#[
	#AC_MSG_ERROR([
#	* nvidia cG toolkit is missing.
	#* You can download it from: http://developer.nvidia.com/object/cg_toolkit.html ])
#],
#)
#
#AC_CHECK_LIB(CgGL, cgGLBindProgram,
#[
	#AC_CHECK_HEADERS(Cg/cgGL.h,
#	[
		#AC_DEFINE(HAVE_CGGL, 1, [define if you have libcg])
#		AC_SUBST([CGGL_LIBS])
		#CGGL_LIBS="-lCgGL -lGL"
#		have_cggl=yes
	#],
#	[
		#AC_MSG_ERROR([cGGL header file missing or not in Cg/ include subdir])
#	])
#
#],
#[
	#AC_MSG_ERROR([
#	* Something's wrong with nvidia cG toolkit
	#* Probably bad installation
#	* You can download it from: http://developer.nvidia.com/object/cg_toolkit.html ])
#
#],
#[ -lGL ]
#)
#AC_LANG_POP(C++)

wxversion=2.8.0

dnl Check wx-Widgets
WX_CONFIG_CHECK([2.8.0], [wxWin=1], [wxWin=0], [html,core,net,gl,aui,adv,propgrid], [--unicode])

CPPFLAGS="$CPPFLAGS $WX_CPPFLAGS"
CXXFLAGS="$CXXFLAGS $WX_CXXFLAGS_ONLY"
CFLAGS="$CFLAGS $WX_CFLAGS_ONLY"
LIBS="$LIBS $WX_LIBS"

AC_SUBST(WX_LIB_GL)
AC_SUBST(CPPFLAGS)
AC_SUBST(CXXFLAGS)
AC_SUBST(CFLAGS)
AC_SUBST(LIBS)

WX_GTK2_CFLAGS=
WX_GTK2_LIBS=

dnl default value is to (silently) do nothing in the makefile
POSTLINK_COMMAND="@true"
MACSETFILE="@true"

AC_MSG_CHECKING(for wxWidgets platform)
WX_BASENAME=`$WX_CONFIG_WITH_ARGS --basename`
case $WX_BASENAME in
    *wx_gtk*)
        AC_MSG_RESULT(wxGTK)
        WX_GTK2_CFLAGS="$GTK2_CFLAGS"
        WX_GTK2_LIBS="$GTK2_LIBS"
    ;;
    *wx_msw*)
        AC_MSG_RESULT(wxMSW)
    ;;
    *wx_mac*)
        AC_MSG_RESULT(wxMac)
        AC_CHECK_PROG(REZ, Rez, Rez, /Developer/Tools/Rez)
        POSTLINK_COMMAND="\$(REZ) -d __DARWIN__ -t APPL Carbon.r -o"
        AC_CHECK_PROG(SETFILE, SetFile, SetFile, /Developer/Tools/SetFile)
        MACSETFILE="\$(SETFILE)"
    ;;
    *)
        AC_MSG_RESULT(other)
    ;;
esac

AC_SUBST(WX_GTK2_CFLAGS)
AC_SUBST(WX_GTK2_LIBS)


dnl check for gstreamer
GST_VERSION_MAJOR=0
GST_VERSION_MINOR=10
GST_VERSION_RELEASE=19
GSTPLUG_VERSION_RELEASE=7

AC_ARG_ENABLE(gstreamer,
[--enable-gstreamer[=gstreamer version] Specify the gstreamer version:
			0.10: Gstreamer version 0.10 [default]
			1.0: Gstreamer version 1.0],
[ if test "x$enableval" = "x1.0" ; then
    GST_VERSION_MAJOR=1
    GST_VERSION_MINOR=0
    GST_VERSION_RELEASE=0
    GSTPLUG_VERSION_RELEASE=0
    host_cflags="$host_cflags -DGSTVERSION"
  fi
])


AC_SUBST([HOSTCFLAGS],$host_cflags)
AC_SUBST([HOSTLDFLAGS],$host_ldflags)
AC_SUBST([OPENGLESV2],$OPENGLESV2)

dnl check for gstreamer
GSTREAMER_REQ=$GST_VERSION_MAJOR.$GST_VERSION_MINOR.$GST_VERSION_RELEASE
GSTPLUGINS_REQ=$GST_VERSION_MAJOR.$GST_VERSION_MINOR.$GSTPLUG_VERSION_RELEASE
GST_MAJORMINOR=$GST_VERSION_MAJOR.$GST_VERSION_MINOR

if test "x$host_name" = "xosx" ; then

AC_SUBST(GST_CFLAGS,"-I/Library/Frameworks/GStreamer.framework/Versions/1.0/Headers")
AC_SUBST(GST_LIBS,"-framework GStreamer")

else

PKG_CHECK_MODULES(GST, gstreamer-$GST_MAJORMINOR >= $GSTREAMER_REQ, 
HAVE_GSTREAMER=yes)
AC_SUBST(GST_CFLAGS)
AC_SUBST(GST_LIBS)

if test "x$GST_VERSION_MAJOR" = "x1" ; then
    librequires="$librequires , gstreamer-1.0, gstreamer-app-1.0"
    PKG_CHECK_MODULES(GST_INTERFACES, gstreamer-app-$GST_MAJORMINOR >= $GSTREAMER_REQ, HAVE_GSTREAMER_INTERFACES=yes)
elif test "x$GST_VERSION_MAJOR" = "x0" ; then
    librequires="$librequires , gstreamer-0.10, gstreamer-interfaces-0.10, gstreamer-app-0.10"   
    PKG_CHECK_MODULES(GST_INTERFACES, gstreamer-interfaces-$GST_MAJORMINOR >= $GSTREAMER_REQ, HAVE_GSTREAMER_INTERFACES=yes)
fi

AC_SUBST(GST_INTERFACES_CFLAGS)
AC_SUBST(GST_INTERFACES_LIBS)

fi


AC_SUBST(POSTLINK_COMMAND)
AC_SUBST(MACSETFILE)

PLUGIN_WX_LIBS=

AC_MSG_CHECKING(if wxWidgets libraries are needed for plugins)
case `uname` in
    Darwin)
        AC_MSG_RESULT(yes)
        PLUGIN_WX_LIBS="$WX_LIBS"
    ;;
    *)
        AC_MSG_RESULT(no)
    ;;
esac

AC_SUBST(PLUGIN_WX_LIBS)

dnl autoscan results
AC_CHECK_FUNCS([floor])
AC_CHECK_FUNCS([getcwd])
AC_CHECK_FUNCS([memmove])
AC_CHECK_FUNCS([memset])
AC_CHECK_FUNCS([pow])
AC_CHECK_FUNCS([rint])
AC_CHECK_FUNCS([sqrt])
AC_CHECK_FUNCS([strchr])
AC_CHECK_FUNCS([strstr])
AC_CHECK_HEADERS([fcntl.h])
AC_CHECK_HEADERS([float.h])
AC_CHECK_HEADERS([limits.h])
AC_CHECK_HEADERS([stddef.h])
AC_CHECK_HEADERS([stdlib.h])
AC_CHECK_HEADERS([string.h])
AC_CHECK_TYPES([ptrdiff_t])
AC_C_INLINE
AC_FUNC_MALLOC
AC_FUNC_MEMCMP
AC_FUNC_VPRINTF
AC_HEADER_STDBOOL
AC_HEADER_STDC
AC_PREREQ
AC_PROG_CPP
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
LT_INIT
AC_STRUCT_TM
AC_TYPE_SIZE_T

AC_ARG_ENABLE(debug,
AS_HELP_STRING([--enable-debug],
               [enable debugging, default: no]),
[case "${enableval}" in
             yes) debug=true ;;
             no)  debug=false ;;
             *)   AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
esac],
[debug=false])

AM_CONDITIONAL(DEBUG, test x"$debug" = x"true")

AC_SUBST([librequires])

echo "PLATFORM_STRING: $PLATFORM_STRING"
echo "ARCH_STRING: $ARCH_STRING"
echo "GLES: $with_gles"
echo "OPENGLESV2: $OPENGLESV2"
echo "GSTREAMER VERSION: $GSTREAMER_REQ"
echo "librequires: $librequires"
echo "HOST NAME: $host_name"
echo "HOST: $host"
echo "HOSTCFLAGS: $host_cflags"
echo "HOSTLDFLAGS: $host_ldflags"
echo "DEBUG: $debug"

dnl Makefile outputs
AC_OUTPUT([
Makefile
moldeodirector/Makefile
data/Makefile
])

