AC_INIT([Moldeo Director], [0.7.9.6], [info@moldeointeractive.com.ar], [moldeodirector])

AM_INIT_AUTOMAKE
AC_CONFIG_MACRO_DIR([m4])
AM_CONFIG_HEADER(config.h)

AC_LIBTOOL_CONFIG

AC_PROG_CC
AC_PROG_CC_STDC
AC_C_CONST
AC_PROG_LIBTOOL

AC_PROG_CXX
AC_PROG_CXXCPP
AC_PROG_CXX_C_O

#dnl check for libmoldeo
PKG_CHECK_MODULES([LIBMOLDEO], [libmoldeo] ,has_libmoldeo=yes)

#dnl check for moldeocontrols
PKG_CHECK_MODULES([MOLDEOCONTROLS], [moldeocontrols] ,has_mnoldeocontrols=yes)

#dnl check for sdl-net
AC_CHECK_HEADER(SDL/SDL_net.h, , AC_MSG_ERROR([SDL_net header not found.]))
AC_CHECK_LIB(SDL_net, SDLNet_Init, AC_SUBST([SDL_NET_LIBS], [-lSDL_net]), AC_MSG_ERROR([SDL_net not found.]), [${SDL_LIBS} ${WIN32_LIBS}])

#dnl check for glew
AC_CHECK_HEADER(GL/glew.h, , AC_MSG_ERROR([glew header not found.]))
AC_CHECK_LIB(GLEW, glewInit, AC_SUBST([GLEW_LIBS], [-lGLEW]), AC_MSG_ERROR([glew not found.]), )

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
AC_LANG_PUSH(C++)dnl
AC_CHECK_LIB(Cg, cgCreateContext,
[
	AC_CHECK_HEADERS(Cg/cg.h,
	[
		AC_DEFINE(HAVE_CG, 1, [define if you have libcg])
		AC_SUBST([CG_LIBS])
		CG_LIBS="-lCg"
		have_cg=yes
	],
	[
		AC_MSG_ERROR([cG header file missing or not in Cg/ include subdir])
	],
	)

],
[
	AC_MSG_ERROR([
	* nvidia cG toolkit is missing.
	* You can download it from: http://developer.nvidia.com/object/cg_toolkit.html ])
],
)

AC_CHECK_LIB(CgGL, cgGLBindProgram,
[
	AC_CHECK_HEADERS(Cg/cgGL.h,
	[
		AC_DEFINE(HAVE_CGGL, 1, [define if you have libcg])
		AC_SUBST([CGGL_LIBS])
		CGGL_LIBS="-lCgGL -lGL"
		have_cggl=yes
	],
	[
		AC_MSG_ERROR([cGGL header file missing or not in Cg/ include subdir])
	])

],
[
	AC_MSG_ERROR([
	* Something's wrong with nvidia cG toolkit
	* Probably bad installation
	* You can download it from: http://developer.nvidia.com/object/cg_toolkit.html ])

],
[ -lGL ]
)
AC_LANG_POP(C++)

dnl Check wx-Widgets
AC_ARG_ENABLE([unicode],[AC_HELP_STRING([--disable-unicode],[internally use ansi])], 
	[AS_IF([test "x$enableval" = "xno"],[wx_config_args="--unicode=no"])
	AS_IF([test "x$enableval" = "xyes"],[wx_config_args="--unicode=yes"])],
	[wx_config_args="--unicode=no"]
)
AM_OPTIONS_WXCONFIG
AM_PATH_WXCONFIG(2.8.0, wxWin=1)
        if test "$wxWin" != 1; then
        AC_MSG_ERROR([
                wxWidgets must be installed on your system.

                Please check that wx-config is in path, the directory
                where wxWidgets libraries are installed (returned by
                'wx-config --libs' or 'wx-config --static --libs' command)
                is in LD_LIBRARY_PATH or equivalent variable and
                wxWindows version is 2.8.0 or above.
                ])
        fi

CPPFLAGS="$CPPFLAGS $WX_CPPFLAGS"
CXXFLAGS="$CXXFLAGS $WX_CXXFLAGS_ONLY"
CFLAGS="$CFLAGS $WX_CFLAGS_ONLY"
LIBS="$LIBS $WX_LIBS"

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

dnl Makefile outputs
AC_OUTPUT([
Makefile
moldeodirector/Makefile
data/Makefile
])

