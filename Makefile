PREFIX = $(HOME)/.lv2
NAME = theos-mute-plugin
DESTDIR=$(PREFIX)/$(NAME)

.PHONY: install

mute.so:
	gcc -shared -fPIC -o mute.so mute.c

install: mute.so
	install -d $(DESTDIR)
	install mute.so mute.ttl manifest.ttl $(DESTDIR)
