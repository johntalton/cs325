######################################################################
# John's Modified Makefile:                                          # 
#                                                                    #
#  make           -- build the app                                   # 
#                                                                    #
#  make clean     -- remove all object files                         #
#                                                                    #
#  make clobber   -- do make clean, and then get rid of executable   #
#                                                                    #
######################################################################

CC       = g++
ARCH	   = $(shell arch)
INCLUDE  =  
CFLAGS   =  $(INCLUDE)


prog2:	
	rm -f prog2
	$(CC) $(CFLAGS) -o prog2	prog2.cpp


clean:	
	rm -f *.o core *.bak *.BAK

clobber: clean
	 rm -f prog2
