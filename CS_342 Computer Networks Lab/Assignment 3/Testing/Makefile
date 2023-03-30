

# Debug malloc support (http://dmalloc.com).  Comment out if you don't
# have dmalloc, but it is highly recommended.
#
#DMALLOC_CFLAGS = -I/usr/local/include -DDMALLOC=1
#DMALLOC_LIBS = -L/usr/local/lib -ldmalloc
#

LIBRT = `test -f /usr/lib/librt.a && printf -- -lrt`

CC = gcc
CFLAGS = -g -Wall $(DMALLOC_CFLAGS)
LIBS = $(DMALLOC_LIBS)

all: ref

.c.o:
	$(CC) $(CFLAGS) -c $<

ref: reliable.o rlib.o
	$(CC) $(CFLAGS) -o $@ reliable.o rlib.o $(LIBS) $(LIBRT)

