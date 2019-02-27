/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"

#define TFT_WIDTH       (320)
#define TFT_HEIGHT      (240)

static const uint8_t defaultMAD[1] = {
    0xA0
}; //MADCTL: memory data access control
static const uint8_t defaultCOLMOD[1] = {
    0x66
}; //COLMOD: Interface Pixel format
static const uint8_t defaultPOR[5] = {
    0x0C, 0x0C, 0x00, 0x33, 0x33
}; //PORCTRL: Porch setting
static const uint8_t defaultGATE[1] = {
    0x35
}; //GCTRL: Gate Control
static const uint8_t defaultVCOM[1] = {
    0x2B
}; //VCOMS: VCOM setting
static const uint8_t defaultLCM[1] = {
    0x2C
}; //LCMCTRL: LCM Control
static const uint8_t defaultVDVVRHEN[2] = {
    0x01, 0xFF
}; //VDVVRHEN: VDV and VRH Command Enable
static const uint8_t defaultVRH[1] = {
    0x11
}; //VRHS: VRH Set
static const uint8_t defaultVDV[1] = {
    0x20
}; //VDVS: VDV Set
static const uint8_t defaultFR2[1] = {
    0x0F
}; //FRCTRL2: Frame Rate control in normal mode
static const uint8_t defaultPWR1[2] = {
    0xA4, 0xA1
}; //PWCTRL1: Power Control 1
static const uint8_t defaultPVGAM[14] = {
    0xD0, 0x00, 0x05, 0x0E, 0x15, 0x0D, 0x37,
    0x43, 0x47, 0x09, 0x15, 0x12, 0x16, 0x19
}; // PVGAMCTRL
static const uint8_t defaultNVGAM[14] = {
    0xD0, 0x00, 0x05, 0x0D, 0x0C, 0x06, 0x2D,
    0x44, 0x40, 0x0E, 0x1C, 0x18, 0x16, 0x19
}; // NVGAMCTRL

void initialize(void) {
    Cy_SysLib_Delay(20);
    GLCD_AssertReset();
    Cy_SysLib_Delay(75);
    GLCD_NegateReset();
    Cy_SysLib_Delay(200);
    
    GLCD_DisplayOff();
    GLCD_SleepOut();
    Cy_SysLib_Delay(100);

    GLCD_CONFIG(GLCD_CMD_MADCTL, defaultMAD); // MADCTL
    GLCD_CONFIG(GLCD_CMD_COLMOD, defaultCOLMOD); // COLMOD
    GLCD_CONFIG(GLCD_CMD_PORCTRL, defaultPOR); // PORCTRL
    GLCD_CONFIG(GLCD_CMD_GCTRL, defaultGATE); // GCTRL
    GLCD_CONFIG(GLCD_CMD_VCOMS, defaultVCOM); // VCOMS
    GLCD_CONFIG(GLCD_CMD_LCMCTRL, defaultLCM); // LCMCTRL
    GLCD_CONFIG(GLCD_CMD_VDVVRHEN, defaultVDVVRHEN); // VDVVRHEN
    GLCD_CONFIG(GLCD_CMD_VRHS, defaultVRH); // VRHS
    GLCD_CONFIG(GLCD_CMD_VDVS, defaultVDV); // VDVS
    GLCD_CONFIG(GLCD_CMD_FRCTRL2, defaultFR2); // FRCTRL2
    GLCD_CONFIG(GLCD_CMD_PWCTRL1, defaultPWR1); // PWCTRL1
    GLCD_CONFIG(GLCD_CMD_PVGAMCTRL, defaultPVGAM); // PVGAMCTRL
    GLCD_CONFIG(GLCD_CMD_NVGAMCTRL, defaultNVGAM); // NVGAMCTRL

    GLCD_RowAddressSet(0, TFT_HEIGHT-1);
    GLCD_ColumnAddressSet(0, TFT_WIDTH-1);
    Cy_SysLib_Delay(10);
}

int main(void)
{
    uint32_t color = 0xAA0000;
    const uint32_t xc = TFT_WIDTH / 2;
    const uint32_t yc = TFT_HEIGHT / 2;
    uint32_t w = 0;
    uint32_t h = 0;
    uint32_t step = 10;
    __enable_irq(); /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    GLCD_Start();
    initialize();
    GLCD_DisplayOn();
    GLCD_WriteMemoryFill(TFT_WIDTH * TFT_HEIGHT, 0x00000);

    for(;;)
    {
        /* Place your application code here. */
//        GLCD_DisplayOff();
        w = TFT_WIDTH / 2;
        h = TFT_HEIGHT / 2;
        while ((w >= step) && (h >= step)) {
            color = (color << 8) | ((color >> 16) & 0xFF);
            GLCD_RowAddressSet(yc - h, yc + h - 1);
            GLCD_ColumnAddressSet(xc - w, xc + w - 1);
            GLCD_WriteMemoryFill(w * h * 4, color);
            w -= step;
            h -= step;
        }
//        GLCD_DisplayOn();
        Cy_SysLib_Delay(200);
    }
}

/* [] END OF FILE */
