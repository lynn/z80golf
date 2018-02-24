
TARGET=	z80golf

SRCS=	$(wildcard *.c)
OBJS=	$(subst .c,.o,$(SRCS))

CC= gcc -c
LK= gcc

COPT= -O2 -DNDEBUG

all:	$(TARGET)


$(TARGET):	$(OBJS)
	$(LK) -o$(TARGET) $(OBJS)

clean:
	rm -f $(OBJS)
	rm -f $(TARGET)

.c.o:
	$(CC) $(COPT) $<
