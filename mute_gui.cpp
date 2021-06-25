#include <iostream>
#include <gtkmm.h>
#include <lv2gui.hpp>

using namespace Gtk;
using namespace sigc;

// http://ll-plugins.nongnu.org/dox/lv2-c++-tools/1.0.5/classLV2_1_1GUI.html
class MuteGUI : public LV2::GUI<MuteGUI>
{
public:
    MuteGUI(const std::string &URI)
    {
        set_border_width(10);

        mute_button.add_label("mute");
        mute_button.set_size_request(100, 50);

        slot<void> slot = compose(bind(mem_fun(*this, &MuteGUI::write_control), 0),
                                  compose(mem_fun(*this, &MuteGUI::callback),
                                          mem_fun(mute_button, &ToggleButton::get_active)));
        mute_button.signal_toggled().connect(slot);
        // toggle button reference:
        // https://developer.gnome.org/gtkmm/stable/classGtk_1_1ToggleButton.html

        // How the nongnu guy does it
        // http://ll-plugins.nongnu.org/lv2pftci/#A_GUI

        mute_button.show();
        add(mute_button);
    }

    void port_event(uint32_t port, uint32_t buffer_size,
                    uint32_t format, void const *buffer)
    {
        printf("por:%d buf size:%d format:%d buffer: %s\n", port, buffer_size, format, &buffer);
    }

protected:
    Gtk::ToggleButton mute_button;

    bool callback(bool state)
    {
        std::cout << state << std::endl;
        return static_cast<float>(state);
    }
};

static int _ = MuteGUI::register_class("https://github.com/moltenot/lv2-mute/wiki");