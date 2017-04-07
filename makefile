backlight_mod : main.c
	gcc -o backlight_mod main.c

install : backlight_mod
	chown root:root backlight_mod
	chmod +s backlight_mod
	cp backlight_mod /usr/bin
