######################################################################
# ynop's Modified Makefile: Ripped from Josh who took it form Watson #
#                                                                    #
#  make           -- build the app                                   # 
#                                                                    #
#  make clean     -- remove all object files                         #
#                                                                    #
#  make clobber   -- do make clean, and then get rid of executable   #
#                                                                    #
######################################################################

PROGNAME = prog3


CC       = g++
ARCH	   = $(shell arch)
INCLUDE  =  
CFLAGS   = $(INCLUDE)

COMPILE.cpp: 
	$(CC) $(CFLAGS) -o $(PROGNAME) $(PROGNAME).cpp

clean:	
	rm -f *.o core *.bak *.BAK

clobber: clean
	 rm -f $(PROGNAME)
