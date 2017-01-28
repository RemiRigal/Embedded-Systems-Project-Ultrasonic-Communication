##
## Makefile for Miosix embedded OS
##
MAKEFILE_VERSION := 1.07
## Path to kernel directory (edited by init_project_out_of_git_repo.pl)
KPATH := miosix-kernel/miosix
## Path to config directory (edited by init_project_out_of_git_repo.pl)
CONFPATH := .
include $(CONFPATH)/config/Makefile.inc
## Path to UltraSound (US) sources
USPATH := Utilities

##
## List here subdirectories which contains makefiles
##
SUBDIRS := $(KPATH)

##
## List here your source files (both .s, .c and .cpp)
##
RSRC :=                                  \
main_receiver.cpp $(USPATH)/Serial.cpp $(USPATH)/Decoder.cpp $(USPATH)/USReceiver.cpp

TSRC :=                                  \
main_transmitter.cpp $(USPATH)/Serial.cpp $(USPATH)/Encoder.cpp $(USPATH)/USTransmitter.cpp 

##
## List here additional static libraries with relative path
##
LIBS :=					\

##
## List here additional include directories (in the form -Iinclude_dir)
##
INCLUDE_DIRS :=				\
    -I./$(USPATH)

##############################################################################
## You should not need to modify anything below                             ##
##############################################################################

ifeq ("$(VERBOSE)","1")
Q := 
ECHO := @true
else
Q := @
ECHO := @echo
endif

## Replaces both "foo.cpp"-->"foo.o" and "foo.c"-->"foo.o"
ROBJ := $(addsuffix .o, $(basename $(RSRC)))
TOBJ := $(addsuffix .o, $(basename $(TSRC)))
OBJ := $(ROBJ) $(TOBJ)

## Includes the miosix base directory for C/C++
## Always include CONFPATH first, as it overrides the config file location
CXXFLAGS := $(CXXFLAGS_BASE) -I$(CONFPATH) -I$(CONFPATH)/config/$(BOARD_INC)  \
            -I. -I$(KPATH) -I$(KPATH)/arch/common -I$(KPATH)/$(ARCH_INC)      \
            -I$(KPATH)/$(BOARD_INC) $(INCLUDE_DIRS)
CFLAGS   := $(CFLAGS_BASE)   -I$(CONFPATH) -I$(CONFPATH)/config/$(BOARD_INC)  \
            -I. -I$(KPATH) -I$(KPATH)/arch/common -I$(KPATH)/$(ARCH_INC)      \
            -I$(KPATH)/$(BOARD_INC) $(INCLUDE_DIRS)
AFLAGS   := $(AFLAGS_BASE)
LFLAGS   := $(LFLAGS_BASE)
DFLAGS   := -MMD -MP

LINK_LIBS := $(LIBS) -L$(KPATH) -Wl,--start-group -lmiosix -lstdc++ -lc \
             -lm -lgcc -Wl,--end-group

all: all-recursive main_receiver main_transmitter

clean: clean-recursive clean-topdir

program:
	$(PROGRAM_CMDLINE)

all-recursive:
	$(foreach i,$(SUBDIRS),$(MAKE) -C $(i)                               \
	  KPATH=$(shell perl $(KPATH)/_tools/relpath.pl $(i) $(KPATH))       \
	  CONFPATH=$(shell perl $(KPATH)/_tools/relpath.pl $(i) $(CONFPATH)) \
	  || exit 1;)

clean-recursive:
	$(foreach i,$(SUBDIRS),$(MAKE) -C $(i)                               \
	  KPATH=$(shell perl $(KPATH)/_tools/relpath.pl $(i) $(KPATH))       \
	  CONFPATH=$(shell perl $(KPATH)/_tools/relpath.pl $(i) $(CONFPATH)) \
	  clean || exit 1;)

clean-topdir:
	-rm -f $(OBJ) $(OBJ:.o=.d) \
		main_receiver.elf main_receiver.hex main_receiver.bin main_receiver.map \
		main_transmitter.elf main_transmitter.hex main_transmitter.bin main_transmitter.map

main_receiver: main_receiver.elf
	$(ECHO) "[CP  ] main_receiver.hex"
	$(Q)$(CP) -O ihex   main_receiver.elf main_receiver.hex
	$(ECHO) "[CP  ] main_receiver.bin"
	$(Q)$(CP) -O binary main_receiver.elf main_receiver.bin
	$(Q)$(SZ) main_receiver.elf

main_receiver.elf: $(ROBJ) all-recursive
	$(ECHO) "[LD  ] main_receiver.elf"
	$(Q)$(CXX) $(LFLAGS) -o main_receiver.elf $(ROBJ) $(KPATH)/$(BOOT_FILE) $(LINK_LIBS)

main_transmitter: main_transmitter.elf
	$(ECHO) "[CP  ] main_transmitter.hex"
	$(Q)$(CP) -O ihex   main_transmitter.elf main_transmitter.hex
	$(ECHO) "[CP  ] main_transmitter.bin"
	$(Q)$(CP) -O binary main_transmitter.elf main_transmitter.bin
	$(Q)$(SZ) main_transmitter.elf

main_transmitter.elf: $(TOBJ) all-recursive
	$(ECHO) "[LD  ] main_transmitter.elf"
	$(Q)$(CXX) $(LFLAGS) -o main_transmitter.elf $(TOBJ) $(KPATH)/$(BOOT_FILE) $(LINK_LIBS)

%.o: %.s
%.o: %.s
	$(ECHO) "[AS  ] $<"
	$(Q)$(AS)  $(AFLAGS) $< -o $@

%.o : %.c
	$(ECHO) "[CC  ] $<"
	$(Q)$(CC)  $(DFLAGS) $(CFLAGS) $< -o $@

%.o : %.cpp
	$(ECHO) "[CXX ] $<"
	$(Q)$(CXX) $(DFLAGS) $(CXXFLAGS) $< -o $@

#pull in dependecy info for existing .o files
-include $(OBJ:.o=.d)

