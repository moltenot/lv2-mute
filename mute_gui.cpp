#include <gtkmm.h>
#include <lv2gui.hpp>

using namespace Gtk;

class MuteGUI : public LV2::GUI<MuteGUI>
{
public:
    MuteGUI(const std::string &URI)
    {
        mute_button.add_label("mute button");
        mute_button.set_size_request(100,100);

        // would regester a signal handler here

        mute_button.show();
        add(mute_button);
    }

    // void port_event(uint32_t port, uint32_t buffer_size,
    //                 uint32_t format, void const *buffer) {}
protected:
    Gtk::Button mute_button;
};

static int _ = MuteGUI::register_class("https://github.com/moltenot/lv2-mute/wiki");