CC = clang
CFLAGS = -fPIC -Wall -Wextra -O2
LDFLAGS = -shared -lGL -lglfw -lm
SRCS = yacore.c yamath.c yashapes.c yatexture.c yatext.c yacamera.c
OBJS = $(SRCS:.c=.o)
TARGET = libyagl.so

all: $(TARGET)
	sudo cp libyagl.so /usr/lib
	sudo cp yagl.h /usr/include

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

install: $(TARGET)
	cp $(TARGET) /usr/local/lib/
	ldconfig

uninstall:
	rm -f /usr/local/lib/$(TARGET)
	ldconfig

.PHONY: all clean install uninstall
