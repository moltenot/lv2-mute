#include "lv2/core/lv2.h"

#include <math.h>
#include <stdint.h>
#include <stdlib.h>

typedef enum
{
    CONTROL = 0,
    INPUT = 1,
    OUTPUT = 2
} PortIndex;

typedef struct
{
    const float *mute;
    const float *input;
    float *output;
} Mute;

static LV2_Handle instantiate(
    const LV2_Descriptor *descriptor,
    double rate,
    const char *bundle_path,
    const LV2_Feature *const *features)
{
    Mute *mute = (Mute *)calloc(1, sizeof(Mute));
    return (LV2_Handle)mute;
}

static void connect_port(LV2_Handle instance, uint32_t port, void *data)
{
    Mute *mute = (Mute *)instance;

    switch ((PortIndex)port))
        {
        case CONTROL:
            mute->mute = (const float *)data;
            break;
        case INPUT:
            mute->input = (const float *)data;
            break;
        case OUTPUT:
            mute->output = (float *)data;
            break;
        }
}

const LV2_SYMBOL_EXPORT LV2_Descriptor *lv2_descriptor(uint32_t index)
{
}