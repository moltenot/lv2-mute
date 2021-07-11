INSTALLDIR = $(HOME)/.lv2/
BUNDLE = theos-mute-plugin.lv2
IMAGE_FOLDER=/usr/share/theos_mute_plugin/

.PHONY: install uninstall reinstall jalv_test

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
	mkdir $(IMAGE_FOLDER)
	cp "images/theos dsp plugins logo image.svg" $(IMAGE_FOLDER)


uninstall:
	rm -rf $(IMAGE_FOLDER)
	rm -rf $(INSTALLDIR)/$(BUNDLE)

reinstall: uninstall clean install

jalv_test:
	jalv.gtkmm https://github.com/moltenot/lv2-mute