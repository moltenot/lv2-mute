INSTALLDIR = $(HOME)/.lv2/
BUNDLE = theos-mute-plugin.lv2

.PHONY: install uninstall

mute.so:
	gcc -shared -fPIC -o mute.so mute.c

$(BUNDLE): mute.so mute_gui.so
	mkdir $(BUNDLE)
	cp manifest.ttl mute.so mute.ttl mute_gui.so $(BUNDLE)

mute_gui.so:
	g++ mute_gui.cpp -fPIC -DPIC -shared `pkg-config --cflags --libs lv2-gui` -o mute_gui.so

clean:
	rm -rf $(BUNDLE) mute.so mute_gui.so

install: uninstall $(BUNDLE)
	mkdir -p $(INSTALLDIR)/$(BUNDLE)
	mv $(BUNDLE) $(INSTALLDIR)

uninstall:
	rm -rf $(INSTALLDIR)/$(BUNDLE)