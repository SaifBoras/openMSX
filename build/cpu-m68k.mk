# $Id$
#
# Configuration for the Motorola 860x0 family. EXPERIMENTAL AND UNTESTED

# Big or little endian?
BIG_ENDIAN:=true

# Default build flavour.
OPENMSX_FLAVOUR?=opt

# overrule optimization level for m68k
CXXFLAGS:=-O1 -DNDEBUG
