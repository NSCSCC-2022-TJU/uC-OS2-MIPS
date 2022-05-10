
# CFLAGS += -DET_DEBUG -DDEBUG

LIB	= ucos2.o

OBJS	=   os_core.o \
			os_cpu_c.o \
			os_dbg_r.o \
			os_flag.o \
			os_mbox.o \
			os_mem.o \
			os_mutex.o \
			os_q.o \
			os_sem.o \
			os_task.o \
			os_time.o \
			os_tmr.o 

SOBJS	= os_cpu_a.o \
			entry.o
			
all: $(LIB)

$(LIB):	$(OBJS) $(SOBJS)
	$(LD) -EL -r -o $@ $(OBJS) $(SOBJS)



.depend: Makefile $(OBJS:.o=.c) $(SOBJS:.o=.S)
		$(CC) -EL -M $(CFLAGS) $(OBJS:.o=.c) $(SOBJS:.o=.S) > $@


sinclude .depend

