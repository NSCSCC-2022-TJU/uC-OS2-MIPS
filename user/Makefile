LIB	= users.o

OBJS = user.o

all:	$(LIB)

$(LIB):	$(OBJS)
	$(LD) -EL -r -o $@ $(OBJS)


.depend:	Makefile $(OBJS:.o=.c)
		$(CC) -c -mips1  $(CFLAGS) $(OBJS:.o=.c) > $@

sinclude .depend

