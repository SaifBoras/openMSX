# $Id$
#
# Configuration for MinGW on x86 machines.

# Does platform support symlinks?
USE_SYMLINK:=false

# Default compiler.
OPENMSX_CXX?=g++

# File name extension of executables.
EXEEXT:=.exe

# Compiler flags.
COMPILE_FLAGS+= \
	-mthreads -mconsole -mms-bitfields \
	-I/mingw/include -I/mingw/include/w32api\
	`if test -d /usr/local/include; then echo '-I/usr/local/include -I/usr/local/include/directx'; fi` \
	-D__GTHREAD_HIDE_WIN32API \
	-DFS_CASEINSENSE

# Linker flags.
LINK_FLAGS:=-L/mingw/lib -L/mingw/lib/w32api -lwsock32 -lwinmm -ldsound \
	`if test -d /usr/local/lib; then echo '-L/usr/local/lib'; fi` \
	$(LINK_FLAGS)


# Probe Overrides
# ===============

GL_LDFLAGS:=-lopengl32

GLEW_LDFLAGS_SYS_DYN:=-lglew32
GLEW_LDFLAGS_3RD_STA:=$(3RDPARTY_INSTALL_DIR)/lib/libglew32.dll.a

SDL_LDFLAGS_SYS_DYN:=`sdl-config --libs | sed -e 's/-mwindows/-mconsole/' 2>> $(LOG)`
SDL_LDFLAGS_3RD_STA:=`$(3RDPARTY_INSTALL_DIR)/bin/sdl-config --static-libs | sed -e \"s/-L[^ ]*//g\" -e 's/-mwindows/-mconsole/' 2>> $(LOG)`
