ifndef CROSS_COMPILE
CROSS_COMPILE = mips-sde-elf-
endif

export	CROSS_COMPILE

#########################################################################

TOPDIR	:= $(shell if [ "$$PWD" != "" ]; then echo $$PWD; else pwd; fi)
export	TOPDIR

include $(TOPDIR)/config.mk

# order is important here:
SUBDIRS	= User Source Port
LIBS  =	User/user.o Source/source.o Port/port.o
OBJDIR = ./obj

#########################################################################

all: ucosii.om ucosii.bin ucosii.asm ucosii.bin ucosii.bin
	mkdir -p $(OBJDIR)
	mv ucosii.om  $(OBJDIR)/.
	mv ucosii.asm   $(OBJDIR)/.
	mv ucosii.bin  $(OBJDIR)/.
	
ucosii.om: depend subdirs $(LIBS) Makefile
	$(CC) -Tdefault.ld -o $@ $(LIBS) -nostdlib $(LDFLAGS)

ucosii.bin: ucosii.om
	mips-sde-elf-objcopy -O binary $< $@

ucosii.asm: ucosii.om
	mips-sde-elf-objdump -D $< > $@

#########################################################################

depend dep:
	@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir .depend ; done

subdirs:
	@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir || exit 1 ; done

clean:
	find . -type f \
		\( -name 'core' -o -name '*.bak' -o -name '*~' \
		-o -name '*.o'  -o -name '*.tmp' -o -name '*.hex' \
		-o -name 'OS.bin' -o -name 'ucosii.bin' -o -name '*.srec' \
		-o -name '*.mem' -o -name '*.img' -o -name '*.out' \
		-o -name '*.aux' -o -name '*.log' -o -name '*.data' \) -print \
		| xargs rm -f
	rm -f System.map
	rm -f *.asm *.om *.bin
	find . -name ".depend" | xargs rm -f
	rm -rf obj/

distclean: clean
	find . -type f \
		\( -name .depend -o -name '*.srec' -o -name '*.bin' \
		-o -name '*.pdf' \) \
		-print | xargs rm -f
	rm -f $(OBJS) *.bak tags TAGS
	rm -fr *.*~

#########################################################################
