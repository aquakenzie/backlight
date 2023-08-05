default: compile

compile:
	cc backlight.c -o backlight -Wall

install:
	install -m 4755 -o root -g root backlight /usr/bin/backlight

uninstall:
	rm /usr/bin/backlight

clean:
	rm backlight backlight.c~ Makefile~ 2>/dev/null; true
