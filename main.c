#include <stdint.h>

#include "external/gsKit/include/gsKit.h"
#include "external/gsKit/include/dmaKit.h"

GSGLOBAL* settings = NULL;
const uint64_t CLEAR_COLOR = GS_SETREG_RGBAQ(0x00, 0x00, 0x00, 0x80, 0x00);

void InitScreenSettings() {
    settings = gsKit_init_global();
    settings->PrimAlphaEnable = GS_SETTING_ON;

    dmaKit_init(D_CTRL_RELE_OFF, D_CTRL_MFD_OFF, D_CTRL_STS_UNSPEC,
                D_CTRL_STD_OFF, D_CTRL_RCYC_8, 1 << DMA_CHANNEL_GIF);
    dmaKit_chan_init(DMA_CHANNEL_GIF);

    gsKit_set_primalpha(settings, GS_SETREG_ALPHA(0, 1, 0, 1, 0), 0);

    gsKit_set_clamp(settings, GS_CMODE_REPEAT);
    gsKit_vram_clear(settings);
    gsKit_init_screen(settings);
    gsKit_mode_switch(settings, GS_ONESHOT);
}

void flipScreen(GSGLOBAL* gsGlobal)
{
    gsKit_queue_exec(gsGlobal);
    gsKit_sync_flip(gsGlobal);
}

int main(void)
{
    //Initializes GsKit and DmaKit.
    InitScreenSettings();

    // Main gameplay loop.
    while(1) {
        gsKit_clear(settings, CLEAR_COLOR);
        //drawing code goes here.
        flipScreen(settings);
    }

    return 0;
}
