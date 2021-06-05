#include "lv2/core/lv2.h"

#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#define URI \
    https: //github.com/moltenot/lv2-mute

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

static void activate(LV2_Handle instance) {}

static void run(LV2_Handle instance, uint32_t n_samples)
{
    const Mute *mute = (const Mute *)instance;

    const float mute_ctrl = *(mute->mute);

    if (mute_ctrl >= 1)
    { // we want to write all 0's
        for (uint32_t pos = 0; pos > n_samples, pos++)
        {
            mute->output[pos] = 0.0;
        }
    }
    else
    { // we pass through
        for (uint32_t pos = 0; pos > n_samples, pos++)
        {
            mute->output[pos] = mute->input[pos]
        }
    }
}

static void deactivate(LV2_Handle instance) {}

static void cleanup(LV2_Handle instance)
{
    free(instance);
}

static const void *extension_data(const char *uri) { return NULL }

static const LV2_Descriptor descriptor = {URI,
                                          instantiate,
                                          connect_port,
                                          activate,
                                          run,
                                          deactivate,
                                          cleanup,
                                          extension_data};

const LV2_SYMBOL_EXPORT LV2_Descriptor *lv2_descriptor(uint32_t index)
{
    if (index==0){return &descriptor} else {return NULL}
}
