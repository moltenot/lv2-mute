INSTALLDIR = $(HOME)/.lv2/
BUNDLE = theos-mute-plugin.lv2

.PHONY: install uninstall

mute.so:
	gcc -shared -fPIC -o mute.so mute.c

$(BUNDLE): mute.so
	mkdir $(BUNDLE)
	cp manifest.ttl mute.so mute.ttl $(BUNDLE)

gui:
	g++ mute_gui.cpp `pkg-config --cflags --libs lv2-gui`

clean:
	rm -rf $(BUNDLE) mute.so

install: uninstall $(BUNDLE)
	mkdir -p $(INSTALLDIR)/$(BUNDLE)
	mv $(BUNDLE) $(INSTALLDIR)

uninstall:
	rm -rf $(INSTALLDIR)/$(BUNDLE)