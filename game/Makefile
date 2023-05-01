# To be able to play with the Dummy:
#
# 1) Copy one of the objects:
#
# AIDummy.o.Linux64      (Linux   64 bits)
# AIDummy.o.MacOS        (Mac)
# AIDummy.o.MacOS.ARM64  (Mac ARM64)
#
# to AIDummy.o
#
# That is, if you use Linux64: cp AIDummy.o.Linux64 AIDummy.o
#
# 2) Copy one of the objects:
#
# Board.o.Linux64     (Linux   64 bits)
# Board.o.MacOS       (Mac)
# Board.o.MacOS.ARM64 (Mac ARM64)
#
# to Board.o
#
# That is, if you use Linux64: cp Board.o.Linux64 Board.o
#

 DUMMY_OBJ = AIDummy.o
 BOARD_OBJ = Board.o

# Add here any extra .o player files you want to link to the executable
EXTRA_OBJS =

# For debugging matches
# 1) make clean
# 2) Set the following flags
# OPTIMIZE = 0, DEBUG = 1
# 3) cp Board.o.Linux64.Debug Board.o     [or another file depending on your machine]
# 4) cp AIDummy.o.Linux64.Debug AIDummy.o [or another file depending on your machine]
# 5) make all


# Config
OPTIMIZE = 2 # Optimization level (0 to 3)
DEBUG    = 0 # Compile for debugging (0 or 1)
PROFILE  = 0 # Compile for profile (0 or 1)

# Do not edit past this line
############################

# Flags
ifeq ($(strip $(PROFILE)),1)
	PROFILEFLAGS=-pg
endif

ifeq ($(strip $(DEBUG)),1)
	DEBUGFLAGS=-g -O0 -fno-inline -D_GLIBCXX_DEBUG 
endif

# The following two lines will detect all your players (files matching "AI*.cc")

PLAYERS_SRC = $(wildcard AI*.cc)
PLAYERS_OBJ = $(patsubst %.cc, %.o, $(PLAYERS_SRC)) $(EXTRA_OBJS) $(DUMMY_OBJ)

# Flags

CXXFLAGS = -std=c++11 -Wall -Wno-unused-variable  $(ARCHFLAGS) $(PROFILEFLAGS) $(DEBUGFLAGS) -O$(strip $(OPTIMIZE)) -fPIC

LDFLAGS  = -std=c++11 -lm $(ARCHFLAGS) $(PROFILEFLAGS) $(DEBUGFLAGS) -O$(strip $(OPTIMIZE))

# Rules

all: Game 

clean:
	rm -rf Game SecGame *.o *.exe Makefile.deps

# Order of objects is important here to deactivate standard sleep function.

Game: Structs.o Settings.o State.o Info.o Random.o Board.o Action.o Player.o Registry.o Game.o Main.o $(PLAYERS_OBJ) $(BOARD_OBJ) Utils.o 
	$(CXX) $^ -o $@ $(LDFLAGS)

SecGame: Structs.o Settings.o State.o Info.o Random.o Board.o Action.o Player.o Registry.o SecGame.o SecMain.o Utils.o 
	$(CXX) $^ -o $@ $(LDFLAGS) -lrt

%.exe: %.o Structs.o Settings.o State.o Info.o Random.o Board.o Action.o Player.o Registry.o SecGame.o SecMain.o Utils.o
	$(CXX) $^ -o $@ $(LDFLAGS) -lrt

Makefile.deps: *.cc
	$(CXX) $(CXXFLAGS) -MM *.cc > Makefile.deps

include Makefile.deps
