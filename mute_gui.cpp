#include <gtkmm.h>
#include <lv2gui.hpp>

using namespace Gtk;

// http://ll-plugins.nongnu.org/dox/lv2-c++-tools/1.0.5/classLV2_1_1GUI.html
class MuteGUI : public LV2::GUI<MuteGUI>
{
public:
    MuteGUI(const std::string &URI)
    {
        set_border_width(10);

        mute_button.add_label("mute");
        mute_button.set_size_request(100,50);

        sigc::slot<void> slot = 
                sigc::compose(
                    sigc::bind(
                        mem_fun(*this, &MuteGUI::write_control), 0),                        ),
                        mem_fun(*mute_button,)
                    )
                );

        mute_button->on_button_press_event().connect(sigc::mem_fun(*this, &MuteGUI::write_control))
        // toggle button reference:
        // https://developer.gnome.org/gtkmm/stable/classGtk_1_1ToggleButton.html

        // How the nongnu guy does it
        // http://ll-plugins.nongnu.org/lv2pftci/#A_GUI

        mute_button.show();
        add(mute_button);
    }

    // void port_event(uint32_t port, uint32_t buffer_size,
    //                 uint32_t format, void const *buffer) {}
protected:
    Gtk::ToggleButton mute_button;
};

static int _ = MuteGUI::register_class("https://github.com/moltenot/lv2-mute/wiki");