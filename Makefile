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
HL2SDK=hl2sdk-tf2
# The path to the Metamod source tree
MMSDK=../metamod-source

# Include Source SDK directories
INCLUDES=-I$(HL2SDK)/public -I$(HL2SDK)/public/tier0 -I$(HL2SDK)/public/tier1 -I$(MMSDK)/core

# Include the folder with the Source SDK libraries
LINKFLAGS=-shared -m32 -L$(HL2SDK)/lib/linux

all: tickrate_enabler.o tickrate_enabler.so

tickrate_enabler.o:
	$(CXX) $(CFLAGS) $(OPTFLAGS) $(INCLUDES) -c tickrate_enabler.cpp

tickrate_enabler.so:
	$(CC) -o tickrate_enabler.so $(LINKFLAGS) tickrate_enabler.o $(MMSDK)/build/core/metamod.2.tf2/linux-x86/sourcehook_sourcehook*.o \
	-l:libtier0_srv.so -l:tier1_i486.a -lm -ldl -lstdc++

clean:
	-rm -f tickrate_enabler.o
	-rm -f tickrate_enabler.so
