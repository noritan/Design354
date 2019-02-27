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

#if !defined(`$INSTANCE_NAME`_H)
#define `$INSTANCE_NAME`_H

#include "project.h"
#include "cy_device_headers.h"
#include "cyfitter.h"

#define `$INSTANCE_NAME`_CMD_SLPIN      (0x10)
#define `$INSTANCE_NAME`_CMD_SLPOUT     (0x11)
#define `$INSTANCE_NAME`_CMD_DISPOFF    (0x28)
#define `$INSTANCE_NAME`_CMD_DISPON     (0x29)
#define `$INSTANCE_NAME`_CMD_CASET      (0x2A)
#define `$INSTANCE_NAME`_CMD_RASET      (0x2B)
#define `$INSTANCE_NAME`_CMD_RAMWR      (0x2C)
#define `$INSTANCE_NAME`_CMD_MADCTL     (0x36)
#define `$INSTANCE_NAME`_CMD_COLMOD     (0x3A)
#define `$INSTANCE_NAME`_CMD_PORCTRL    (0xB2)
#define `$INSTANCE_NAME`_CMD_GCTRL      (0xB7)
#define `$INSTANCE_NAME`_CMD_VCOMS      (0xBB)
#define `$INSTANCE_NAME`_CMD_LCMCTRL    (0xC0)
#define `$INSTANCE_NAME`_CMD_VDVVRHEN   (0xC2)
#define `$INSTANCE_NAME`_CMD_VRHS       (0xC3)
#define `$INSTANCE_NAME`_CMD_VDVS       (0xC4)
#define `$INSTANCE_NAME`_CMD_FRCTRL2    (0xC6)
#define `$INSTANCE_NAME`_CMD_PWCTRL1    (0xD0)
#define `$INSTANCE_NAME`_CMD_PVGAMCTRL  (0xE0)
#define `$INSTANCE_NAME`_CMD_NVGAMCTRL  (0xE1)
    
#define `$INSTANCE_NAME`_FULL_MASK      (0x01)
#define `$INSTANCE_NAME`_BUSY_MASK      (0x02)
#define `$INSTANCE_NAME`_FIFO_REG       (* (reg8 *)  `$INSTANCE_NAME`_B_DP__F0_REG)
#define `$INSTANCE_NAME`_FIFO_PTR       (  (reg8 *)  `$INSTANCE_NAME`_B_DP__F0_REG)

#define `$INSTANCE_NAME`_CONFIG(command, params)  `$INSTANCE_NAME`_Configure((command),(params),sizeof (params));
    
                void `$INSTANCE_NAME`_Start(void);
                void `$INSTANCE_NAME`_Init(void);
                void `$INSTANCE_NAME`_WriteData(uint8_t data);
                void `$INSTANCE_NAME`_WriteCommand(uint8_t command);
                void `$INSTANCE_NAME`_Configure(uint8_t command, const uint8_t *params, uint32_t size);
                void `$INSTANCE_NAME`_ColumnAddressSet(uint32_t start, uint32_t end);
                void `$INSTANCE_NAME`_RowAddressSet(uint32_t start, uint32_t end);
                void `$INSTANCE_NAME`_WriteMemoryFill(uint32_t n, uint32_t color);
                void `$INSTANCE_NAME`_WriteMemoryBlock(uint32_t n, const uint8_t *image);
                void `$INSTANCE_NAME`_WriteMemoryImage(uint32_t width, uint32_t height, const uint8_t *image);

__STATIC_INLINE void `$INSTANCE_NAME`_AssertReset(void);
__STATIC_INLINE void `$INSTANCE_NAME`_NegateReset(void);
__STATIC_INLINE uint8_t `$INSTANCE_NAME`_IsFull(void);
__STATIC_INLINE uint8_t `$INSTANCE_NAME`_IsBusy(void);
__STATIC_INLINE void `$INSTANCE_NAME`_Write(uint8_t d);

__STATIC_INLINE void `$INSTANCE_NAME`_SleepIn(void);
__STATIC_INLINE void `$INSTANCE_NAME`_SleepOut(void);
__STATIC_INLINE void `$INSTANCE_NAME`_DisplayOff(void);
__STATIC_INLINE void `$INSTANCE_NAME`_DisplayOn(void);
__STATIC_INLINE void `$INSTANCE_NAME`_WriteMemory(void);

/***************************************
*    In-line Function Implementation
***************************************/

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_AssertReset
********************************************************************************
* Summary: 
*   Assert the RESETX output
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_AssertReset(void) {
    Cy_GPIO_Clr(`$INSTANCE_NAME`_RESETX_PORT, `$INSTANCE_NAME`_RESETX_NUM);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_NegateReset
********************************************************************************
* Summary: 
*   Negate the RESETX output
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_NegateReset(void) {
    Cy_GPIO_Set(`$INSTANCE_NAME`_RESETX_PORT, `$INSTANCE_NAME`_RESETX_NUM);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DataMode
********************************************************************************
* Summary: 
*   Set the D/C signal to DATA mode.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_DataMode(void) {
    while (`$INSTANCE_NAME`_IsBusy()) ;
    Cy_GPIO_Set(`$INSTANCE_NAME`_D_C_PORT, `$INSTANCE_NAME`_D_C_NUM);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CommandMode
********************************************************************************
* Summary: 
*   Set the D/C signal to COMMAND mode.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_CommandMode(void) {
    while (`$INSTANCE_NAME`_IsBusy()) ;
    Cy_GPIO_Clr(`$INSTANCE_NAME`_D_C_PORT, `$INSTANCE_NAME`_D_C_NUM);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_IsFull
********************************************************************************
* Summary: 
*   Return the FIFO full flag
*
*******************************************************************************/
__STATIC_INLINE uint8_t `$INSTANCE_NAME`_IsFull(void) {
    return (`$INSTANCE_NAME`_SR1_Read() & `$INSTANCE_NAME`_FULL_MASK)?(1):(0);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_IsBusy
********************************************************************************
* Summary: 
*   Return the busy flag
*
*******************************************************************************/
__STATIC_INLINE uint8_t `$INSTANCE_NAME`_IsBusy(void) {
    return (`$INSTANCE_NAME`_SR1_Read() & `$INSTANCE_NAME`_BUSY_MASK)?(1):(0);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Write
********************************************************************************
* Summary: 
*   Write a word in current mode.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Write(uint8 d) {
    while (`$INSTANCE_NAME`_IsFull()) ;
    CY_SET_REG8(`$INSTANCE_NAME`_FIFO_PTR, d);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SleepIn
********************************************************************************
* Summary: 
*   Enter to sleep
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SleepIn(void) {
    `$INSTANCE_NAME`_WriteCommand(`$INSTANCE_NAME`_CMD_SLPIN);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SleepOut
********************************************************************************
* Summary: 
*   Exit from sleep
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SleepOut(void) {
    `$INSTANCE_NAME`_WriteCommand(`$INSTANCE_NAME`_CMD_SLPOUT);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DisplayOff
********************************************************************************
* Summary: 
*   Turn OFF the display
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_DisplayOff(void) {
    `$INSTANCE_NAME`_WriteCommand(`$INSTANCE_NAME`_CMD_DISPOFF);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DisplayOn
********************************************************************************
* Summary: 
*   Turn ON the display
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_DisplayOn(void) {
    `$INSTANCE_NAME`_WriteCommand(`$INSTANCE_NAME`_CMD_DISPON);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_WriteMemory
********************************************************************************
* Summary: 
*   Send Write Memory command
*
*******************************************************************************/
void `$INSTANCE_NAME`_WriteMemory(void) {
    `$INSTANCE_NAME`_WriteCommand(`$INSTANCE_NAME`_CMD_RAMWR);
}

#endif /* `$INSTANCE_NAME`_H */
    
/* [] END OF FILE */
