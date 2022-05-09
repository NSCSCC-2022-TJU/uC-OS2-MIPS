

LIB	= users.o

OBJS	= user.o

all:	$(LIB)

$(LIB):	$(OBJS) $(SOBJS)
	$(LD) -EL -r -o $@ $(OBJS) $(SOBJS)

#########################################################################

.depend:	Makefile $(OBJS:.o=.c)
		$(CC) -EL -M $(CFLAGS) $(OBJS:.o=.c) > $@

sinclude .depend

#########################################################################
