

CONFIG_SHELL	:= $(shell if [ -x "$$BASH" ]; then echo $$BASH; \
		    else if [ -x /bin/bash ]; then echo /bin/bash; \
		    else echo sh; fi ; fi)

HOSTCC		= cc
HOSTCFLAGS	= -Wall -Wstrict-prototypes -O2 -fomit-frame-pointer

ON_FPGA = n

ifeq  ($(ON_FPGA), y)
FPGA_LD_FLAGS += -S
MACH_DEF := -DMACH_FPGA
else
MACH_DEF := -DMACH_QEMU
endif



#
# Include the make variables (CC, etc...)
#
AS	= $(CROSS_COMPILE)as
LD	= $(CROSS_COMPILE)ld
CC	= $(CROSS_COMPILE)gcc
AR	= $(CROSS_COMPILE)ar
NM	= $(CROSS_COMPILE)nm
STRIP	= $(CROSS_COMPILE)strip
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump
RANLIB	= $(CROSS_COMPILE)ranlib

CFLAGS += -DMACH_QEMU -I$(TOPDIR)/include -I$(TOPDIR)/include/user -I$(TOPDIR)/src -I$(TOPDIR)/user -mips1 -G0  -EL# -Wall -Wstrict-prototypes -Werror-implicit-function-declaration -fomit-frame-pointer -fno-strength-reduce -O2 -g -pipe -fno-builtin -nostdlib
# CFLAGS += -I$(TOPDIR)/include -I$(TOPDIR)/include/init -I$(TOPDIR)/src -I$(TOPDIR)/user -mips1 -G0 -O2 -EL# -Wall -Wstrict-prototypes -Werror-implicit-function-declaration -fomit-frame-pointer -fno-strength-reduce -O2 -g -pipe -fno-builtin -nostdlib

ASFLAGS += $(CFLAGS) -EL

LDFLAGS += -EL -nostdlib -n -G 0 -static



export	CONFIG_SHELL HOSTCC HOSTCFLAGS CROSS_COMPILE \
	AS LD CC AR NM STRIP OBJCOPY OBJDUMP \
	MAKE CFLAGS ASFLAGS



%.o:	%.S
	$(CC) $(CFLAGS) -c -o $@ $<
%.o:	%.c
	$(CC) $(CFLAGS) -c -o $@ $<


