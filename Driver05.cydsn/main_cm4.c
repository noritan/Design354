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

    Cy_SysLib_Delay(10);
}

void pset(uint32_t x, uint32_t y, uint32_t color) {
    GLCD_RowAddressSet(y, y);
    GLCD_ColumnAddressSet(x, x);
    GLCD_WriteMemoryFill(1, color);
}

void line(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color) {
    int32_t dx;
    int32_t dy;
    uint32_t i;
    
    dx = x2 - x1;
    dy = y2 - y1;
    
    if ((dx == 0) || (dy == 0)) {
        if (dy < 0) {
            y2 = y1;
            y1 += dy;
            dy = -dy;
        }
        if (dx < 0) {
            x2 = x1;
            x1 += dx;
            dx = -dx;
        }
        GLCD_RowAddressSet(y1, y2);
        GLCD_ColumnAddressSet(x1, x2);
        GLCD_WriteMemoryFill((dx + 1)*(dy + 1), color);
    } else if ((dx == dy) || (dx = -dy)) {
        i = (dx > 0)?(dx):(-dx);
        dx = (dx > 0)?(1):(-1);
        dy = (dy > 0)?(1):(-1);
        for (; i > 0; i--) {
            pset(x1, y1, color);
            y1 += dy;
            x1 += dx;
        }
    } else {
        // not supported
    }
}

struct Turtle {
    uint32_t x;
    uint32_t y;
    uint32_t direction;
    uint32_t step;
    uint32_t color;
}   turtle;

const uint32_t turtleMove[8][2] = {
    { 0, -1},
    { 1, -1},
    { 1,  0},
    { 1,  1},
    { 0,  1},
    {-1,  1},
    {-1,  0},
    {-1, -1}
};

void turtleSetPosition(uint32_t x, uint32_t y) {
    turtle.x = x;
    turtle.y = y;
}

void turtleSetDirection(uint32_t direction) {
    turtle.direction = direction;
}

void turtleSetStep(uint32_t step) {
    turtle.step = step;
}

void turtleSetColor(uint32_t color) {
    turtle.color = color;
}

void turtleInit(void) {
}

void turtleForward(void) {
    uint32_t x0 = turtle.x;
    uint32_t y0 = turtle.y;
    
    turtle.x = x0 + turtleMove[turtle.direction][0] * turtle.step;
    turtle.y = y0 + turtleMove[turtle.direction][1] * turtle.step;
    line(x0, y0, turtle.x, turtle.y, turtle.color);
}

void turtleRight(void) {
    turtle.direction = (turtle.direction + 1) % 8;
}    

void turtleLeft(void) {
    turtle.direction = (turtle.direction + 7) % 8;
}

void s(uint32_t n) {
    if (n == 0) return;
    s(n-1);
    turtleRight();
    turtleForward();
    turtleRight();
    s(n-1);
    turtleLeft();
    turtleLeft();
    turtleForward();
    turtleLeft();
    turtleLeft();
    s(n-1);
    turtleRight();
    turtleForward();
    turtleRight();
    s(n-1);
}

int main(void)
{
    uint32_t color = 0xAA0000;
    const uint32_t xc = TFT_WIDTH / 2;
    const uint32_t yc = TFT_HEIGHT / 2;
    const uint32_t dimension = 4;
    uint32_t w;
    uint32_t step = 4;
    __enable_irq(); /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    GLCD_Start();
    initialize();
    GLCD_DisplayOn();
    GLCD_RowAddressSet(0, TFT_HEIGHT-1);
    GLCD_ColumnAddressSet(0, TFT_WIDTH-1);
    GLCD_WriteMemoryFill(TFT_WIDTH * TFT_HEIGHT, 0x00000);

    w = 3;
    for (uint32_t i = 0; i < dimension; i++) {
        w *= 2;
    }
    turtleInit();
    turtleSetStep(step);
    turtleSetPosition((TFT_WIDTH - w * step) / 2, (TFT_HEIGHT - w * step) / 2);
    turtleSetDirection(2);
    turtleSetColor(0xAAAAAA);
    
    for (uint32_t i = 0; i < 4; i++) {
        s(dimension);
        turtleRight();
        turtleForward();
        turtleRight();
    }

    for(;;)
    {
        /* Place your application code here. */
//        GLCD_DisplayOff();
//        color = (color << 8) | ((color >> 16) & 0xFF);
//        line(x, 0, x, TFT_HEIGHT - 1, color);
//        x += step;
//        if (x >= TFT_WIDTH) {
//            x -= TFT_WIDTH;
//        }
//        line(0, y, TFT_WIDTH - 1, y, color);
//        y += step;
//        if (y >= TFT_HEIGHT) {
//            y -= TFT_HEIGHT;
//        }
////        GLCD_DisplayOn();
//        Cy_SysLib_Delay(100);
    }
}

/* [] END OF FILE */
