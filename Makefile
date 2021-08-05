CC=gcc
CXX=g++

# Work around hacks in the Source engine
CFLAGS=-m32 -std=gnu++11 -fpermissive -fPIC \
	-Dstrnicmp=strncasecmp -Dstricmp=strcasecmp -D_vsnprintf=vsnprintf \
	-D_alloca=alloca -Dstrcmpi=strcasecmp -DPOSIX -DLINUX -D_LINUX -DCOMPILER_GCC

OPTFLAGS=-O2

# ******************************
# Change these to the proper
# locations for your system.
# ******************************
# The path to the Source SDK to use
HL2SDK=../hl2sdk-csgo
# The path to the Metamod source tree
MMSDK=../metamod-source

# Include Source SDK directories
INCLUDES=-I$(HL2SDK)/public -I$(HL2SDK)/public/tier0 -I$(HL2SDK)/public/tier1 -I$(MMSDK)/core

# Include the folder with the Source SDK libraries
LINKFLAGS=-shared -m32 -L$(HL2SDK)/lib/linux

all: TickrateEnabler.o TickrateEnabler.so

TickrateEnabler.o:
	$(CXX) $(CFLAGS) $(OPTFLAGS) $(INCLUDES) -c TickrateEnabler.cpp

TickrateEnabler.so:
	$(CC) -o TickrateEnabler.so $(LINKFLAGS) TickrateEnabler.o $(MMSDK)/build/core/metamod.2.csgo/linux-x86/sourcehook_sourcehook*.o \
	-l:libtier0.so -l:tier1_i486.a -static-libstdc++ -lm -ldl

clean:
	-rm -f TickrateEnabler.o
	-rm -f TickrateEnabler.so