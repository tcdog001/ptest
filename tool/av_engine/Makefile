
include $(STB_ROOT)/config.mak

LIBOUT = $(STB_ROOT)/lib/slib/libav_engine_if.a
DLIBOUT = $(STB_ROOT)/lib/dlib/libav_engine_if.so

OBJS = av_engine_if.o \
			video_player.o

%.o: %.c
	@$(CC) $(CFLAGS) $(SYS_INCLUDE) $(APP_INCLUDE) -c -o $@ $<

$(LIBOUT): $(OBJS) 
	@echo "Linking $(LIBOUT)......"	
	@$(AR) $(ARFLAGS) -o $(LIBOUT) $(OBJS)
	@echo "Linking Success!"	                                              
clean:
	$(RM) *.o *.bak $(LIBOUT)
