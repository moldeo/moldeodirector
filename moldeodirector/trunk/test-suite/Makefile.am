INCLUDES                    = @CHECK_CFLAGS@
TESTS                       = check_moldeodirector
noinst_PROGRAMS             = $(TESTS)
check_moldeodirector_SOURCES      = check_moldeodirector.cpp
check_moldeodirector_LDADD        = @CHECK_LIBS@ \
	-lmoldeo \
	@MUPARSER_LIBS@ \
	@SDL_LIBS@ \
	@GLE_LIBS@ \
	@FREEIMAGE_LIBS@ \
	@FREEALUT_LIBS@ \
	@GLEW_LIBS@ \
	@CG_LIBS@ \
	@CGGL_LIBS@ \
	@LUA51_LIBS@ \
	@GST_LIBS@ \
	@FT2_LIBS@
CLEANFILES                  = check_moldeodirector.log

