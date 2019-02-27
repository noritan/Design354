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

#define TFT_WIDTH       320
#define TFT_HEIGHT      240    

/*******************************************************************************
* Function Name: TFT_WriteData
********************************************************************************
* Summary:
*   This function writes data to the TFT display interface.
*
* Parameters:
*   data: Data to be sent to the TFT display
*
*******************************************************************************/
void TFT_WriteData(uint8_t data)
{
    GLCD_Write8(1, data);
}

/*******************************************************************************
* Function Name: TFT_WriteCommand
********************************************************************************
* Summary:
*   This function writes a command to the TFT display interface.
*
* Parameters:
*   command: Command to be sent to the TFT display
*
*******************************************************************************/
void TFT_WriteCommand(uint8_t command)
{
    GLCD_Write8(0, command);
}

/*******************************************************************************
* Function Name: TFT_DisplayOff
********************************************************************************
* Summary: 
*   Turn OFF the display
*
*******************************************************************************/
void TFT_DisplayOf(void) {
    TFT_WriteCommand(0x28);
}

/*******************************************************************************
* Function Name: TFT_DisplayOn
********************************************************************************
* Summary: 
*   Turn ON the display
*
*******************************************************************************/
void TFT_DisplayOn(void) {
    TFT_WriteCommand(0x29);
}

/*******************************************************************************
* Function Name: TFT_ColumnAddressSet
********************************************************************************
* Summary: 
*   Set the column address
*
*******************************************************************************/
void TFT_ColumnAddressSet(uint32_t start, uint32_t end) {
    TFT_WriteCommand(0x2A);
    TFT_WriteData(CY_HI8(start));
    TFT_WriteData(CY_LO8(start));
    TFT_WriteData(CY_HI8(end));
    TFT_WriteData(CY_LO8(end));//X address set
}

/*******************************************************************************
* Function Name: TFT_RowAddressSet
********************************************************************************
* Summary: 
*   Set the row address
*
*******************************************************************************/
void TFT_RowAddressSet(uint32_t start, uint32_t end) {
    TFT_WriteCommand(0x2B);
    TFT_WriteData(CY_HI8(start));
    TFT_WriteData(CY_LO8(start));
    TFT_WriteData(CY_HI8(end));
    TFT_WriteData(CY_LO8(end));//Y address set
}

/*******************************************************************************
* Function Name: TFT_WriteMemory
********************************************************************************
* Summary: 
*   Send Write Memory command
*
*******************************************************************************/
void TFT_WriteMemory(void) {
    TFT_WriteCommand(0x2C);
}

/*******************************************************************************
* Function Name: TFT_WriteMemoryFill
********************************************************************************
* Summary: 
*   Set the row address
*
*******************************************************************************/
void TFT_WriteMemoryFill(uint32_t n, uint32_t color) {
    uint32_t i;
    uint8_t r = (uint8_t)(color >> 16);
    uint8_t g = (uint8_t)(color >> 8);
    uint8_t b = (uint8_t)(color >> 0);
    
    TFT_WriteMemory();
    for (i = 0; i < n; i++) {
        TFT_WriteData(r);
        TFT_WriteData(g);
        TFT_WriteData(b);
    } 
}

/*******************************************************************************
* Function Name: TFT_Init
********************************************************************************
* Summary: 
*   This function updates the display based on events that occur.
*
*******************************************************************************/
void TFT_Init(void)
{
    /* Start the GraphicLCD component */
    GLCD_Start();
    
    Cy_SysLib_Delay(20);
    Cy_GPIO_Clr(Pin_nreset_PORT, Pin_nreset_NUM);
    Cy_SysLib_Delay(75);
    Cy_GPIO_Set(Pin_nreset_PORT, Pin_nreset_NUM);
    Cy_SysLib_Delay(200);
    
    TFT_WriteCommand(0x28);
    TFT_WriteCommand(0x11); //Exit Sleep mode
    Cy_SysLib_Delay(100);
    
    TFT_WriteCommand(0x36);
    TFT_WriteData(0xA0);//MADCTL: memory data access control
    TFT_WriteCommand(0x3A);
    TFT_WriteData(0x66);//COLMOD: Interface Pixel format
    TFT_WriteCommand(0xB2);
    TFT_WriteData(0x0C);
    TFT_WriteData(0x0C);
    TFT_WriteData(0x00);
    TFT_WriteData(0x33);
    TFT_WriteData(0x33);//PORCTRK: Porch setting
    TFT_WriteCommand(0xB7);
    TFT_WriteData(0x35);//GCTRL: Gate Control
    TFT_WriteCommand(0xBB);
    TFT_WriteData(0x2B);//VCOMS: VCOM setting
    TFT_WriteCommand(0xC0);
    TFT_WriteData(0x2C);//LCMCTRL: LCM Control
    TFT_WriteCommand(0xC2);
    TFT_WriteData(0x01);
    TFT_WriteData(0xFF);//VDVVRHEN: VDV and VRH Command Enable
    TFT_WriteCommand(0xC3);
    TFT_WriteData(0x11);//VRHS: VRH Set
    TFT_WriteCommand(0xC4);    
    TFT_WriteData(0x20);//VDVS: VDV Set
    TFT_WriteCommand(0xC6);
    TFT_WriteData(0x0F);//FRCTRL2: Frame Rate control in normal mode
    TFT_WriteCommand(0xD0);
    TFT_WriteData(0xA4);
    TFT_WriteData(0xA1);//PWCTRL1: Power Control 1
    TFT_WriteCommand(0xE0);
    TFT_WriteData(0xD0);
    TFT_WriteData(0x00);
    TFT_WriteData(0x05);
    TFT_WriteData(0x0E);
    TFT_WriteData(0x15);
    TFT_WriteData(0x0D);
    TFT_WriteData(0x37);
    TFT_WriteData(0x43);
    TFT_WriteData(0x47);
    TFT_WriteData(0x09);
    TFT_WriteData(0x15);
    TFT_WriteData(0x12);
    TFT_WriteData(0x16);
    TFT_WriteData(0x19);//PVGAMCTRL: Positive Voltage Gamma control
    TFT_WriteCommand(0xE1);
    TFT_WriteData(0xD0);
    TFT_WriteData(0x00);
    TFT_WriteData(0x05);
    TFT_WriteData(0x0D);
    TFT_WriteData(0x0C);
    TFT_WriteData(0x06);
    TFT_WriteData(0x2D);
    TFT_WriteData(0x44);
    TFT_WriteData(0x40);
    TFT_WriteData(0x0E);
    TFT_WriteData(0x1C);
    TFT_WriteData(0x18);
    TFT_WriteData(0x16);
    TFT_WriteData(0x19);//NVGAMCTRL: Negative Voltage Gamma control
    TFT_RowAddressSet(0, TFT_HEIGHT-1);
//    TFT_WriteCommand(0x2B);
//    TFT_WriteData(0x00);
//    TFT_WriteData(0x00);
//    TFT_WriteData(0x00);
//    TFT_WriteData(0xEF);//Y address set
    TFT_ColumnAddressSet(0, TFT_WIDTH-1);
//    TFT_WriteCommand(0x2A);
//    TFT_WriteData(0x00);
//    TFT_WriteData(0x00);
//    TFT_WriteData(0x01);
//    TFT_WriteData(0x3F);//X address set
    Cy_SysLib_Delay(10);
    TFT_DisplayOn();
//    TFT_WriteCommand(0x29);
    TFT_WriteMemoryFill(TFT_WIDTH * TFT_HEIGHT, 0x00000);
    
//    uint16 row, column;
//    TFT_WriteCommand(0x2C);
//    for(row = 0; row < TFT_WIDTH; row++)
//    {
//        for(column = 0; column < TFT_HEIGHT; column++)
//        {
//            {
//                TFT_WriteData(0x00); //Red
//                TFT_WriteData(0x00); //Green
//                TFT_WriteData(0x00); //Blue
//            }
//        }
//    }
}

int main(void)
{
    uint32_t color = 0xAA0000;
    
    __enable_irq(); /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    TFT_Init();

    for(;;)
    {
        /* Place your application code here. */
        color = (color << 8) | ((color >> 16) & 0xFF);
        TFT_RowAddressSet(0, TFT_HEIGHT-1);
        TFT_ColumnAddressSet(0, TFT_WIDTH-1);
        TFT_WriteMemoryFill(TFT_WIDTH * TFT_HEIGHT, color);
    }
}

/* [] END OF FILE */
