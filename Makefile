CC = gcc
CFLAGS = -c

DEPS = gstyoutubebin.h
SOURCES = gstyoutubebin.c

CFLAGS += `pkg-config --cflags gstreamer-1.0 gstreamer-base-1.0 glib-2.0 gio-2.0`

LDFLAGS += `pkg-config --libs gstreamer-1.0 gstreamer-base-1.0 glib-2.0 gio-2.0`
OBJ = $(SOURCES:.c=.o)

%.o : %.c $(DEPS)
	$(CC) -c -fPIC -o $@ $< $(CFLAGS)

libgstyoutubebin.so: $(OBJ)
	$(CC) -shared -o $@ $^ $(LDFLAGS)

clean:
	rm *.o libgstyoutubebin.so
	
