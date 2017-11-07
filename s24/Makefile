CC=gcc
INC= -I$(CURDIR)/include/
DEBUG=-g
WARNING=-w

OBJS_CH24=s24_03.o
SRCS_CH24=$(OBJS_CH24:.o=.c)

TARGET_CH24 = s24

.c.o:
	@echo "Compiling $<"
	@$(CC) -c $(CFLAGS) $<

$(TARGET_CH24) : $(OBJS_CH24)
	@$(CC) -o $(TARGET_CH24) $(OBJS_CH24) $(LDFLAGS)

all : $(TARGET_CH24)

dep :
	gccmaedep $(INC) $(SRCS)

clean : 
	@echo "Cleaning ..."
	@rm -rf $(OBJS_CH24) $(TARGET_CH24)
