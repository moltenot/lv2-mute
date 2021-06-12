#include <gtkmm.h>
#include <lv2gui.hpp>


using namespace Gtk;

class MuteGUI : public LV2::GUI<MuteGUI> {
    public: MuteGUI(const std::string& URI) {

    }

    void port_event() {}
};