#include <iostream>
#include <gtkmm.h>
#include <lv2gui.hpp>
#include <gtkmm/table.h>
#include <gtkmm/image.h>

using namespace Gtk;
using namespace sigc;

// http://ll-plugins.nongnu.org/dox/lv2-c++-tools/1.0.5/classLV2_1_1GUI.html
class MuteGUI : public LV2::GUI<MuteGUI>
{
public:
    MuteGUI(const std::string &URI)
    {
        set_border_width(10);

        // add button
        mute_button.add_label("mute");
        mute_button.set_size_request(50, 30);

        slot<void> slot = compose(bind<0>(mem_fun(*this, &MuteGUI::write_control), 0),
                                  mem_fun(mute_button, &ToggleButton::get_active));

        mute_button.signal_toggled().connect(slot);

        logo.set("/usr/share/theos_mute_plugin/theos dsp plugins logo image.svg");
        // add widgets to the table
        table.attach(mute_button, 1, 2, 0, 1);
        table.attach(logo, 0, 1, 0, 1);

        add(table);
        table.show_all();
    }

    void port_event(uint32_t port, uint32_t buffer_size,
                    uint32_t format, void const *buffer)
    {
        const float *bufvalue = static_cast<const float *>(buffer);
        bool value = static_cast<bool>(*bufvalue); // cast to a boolean
        mute_button.set_active(value);
        printf("PORT EVENT\n");
        printf("port:%d buf size:%d format:%d buffer pointer: %#x\n value: %d\n",
               port, buffer_size, format, buffer, value);
        printf("\n");
    }

protected:
    Gtk::ToggleButton mute_button;
    Gtk::Image logo;
    Gtk::Table table;
};

static int _ = MuteGUI::register_class("https://github.com/moltenot/lv2-mute/wiki");