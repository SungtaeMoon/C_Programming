#
TARGET  = $(COMP_TARGET)
APOBJS  = $(TARGET).o


ADVCDIR = /private/advc
ADVCINC = $(ADVCDIR)/inc
LIBD    = $(ADVCDIR)/lib
LIBS    = -ladvc -lpthread

CFLAGS  = -O -I$(ADVCINC)

#
.SUFFIXES : .c

.c.o:
	$(CC) $(CFLAGS) -c $< >> err

#
# client compile
#

$(TARGET): $(APOBJS)
	$(CC) $(APOBJS) -L$(LIBD) $(LIBS) -o $(TARGET) >> err

#
clean:
	-rm -f *.o core $(TARGET)
