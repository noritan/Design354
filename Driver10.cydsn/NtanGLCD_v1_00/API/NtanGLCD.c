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

#include "`$INSTANCE_NAME`.h"

/** `$INSTANCE_NAME`_initVar indicates whether the `$INSTANCE_NAME` 
*  component has been initialized. The variable is initialized to 0 
*  and set to 1 the first time `$INSTANCE_NAME`_Start() is called. This allows 
*  the component to restart without reinitialization after the first 
*  call to the `$INSTANCE_NAME`_Start() routine.
*
*  If re-initialization of the component is required, then the 
*  `$INSTANCE_NAME`_Init() function can be called before the 
*  `$INSTANCE_NAME`_Start() function.
*/
uint8 `$INSTANCE_NAME`_initVar = 0u;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
****************************************************************************//**
*
* Start and initialize the GLCD
*  
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void) {
    if (!`$INSTANCE_NAME`_initVar) {
        `$INSTANCE_NAME`_Init();
        `$INSTANCE_NAME`_initVar = 1u;
    }
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
****************************************************************************//**
*
* Initialize the component.
*  
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void) {
    `$INSTANCE_NAME`_DMA_WRITE_Init();
    `$INSTANCE_NAME`_DMA_WRITE_initVar = 1u;  // Set initialization flag explicitly
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_WriteData
********************************************************************************
* Summary:
*   This function writes data to the TFT display interface.
*
* Parameters:
*   data: Data to be sent to the TFT display
*
*******************************************************************************/
void `$INSTANCE_NAME`_WriteData(uint8_t data) {
    `$INSTANCE_NAME`_DataMode();
    `$INSTANCE_NAME`_Write(data);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_WriteCommand
********************************************************************************
* Summary:
*   This function writes a command to the TFT display interface.
*
* Parameters:
*   command: Command to be sent to the TFT display
*
*******************************************************************************/
void `$INSTANCE_NAME`_WriteCommand(uint8_t command) {
    `$INSTANCE_NAME`_CommandMode();
    `$INSTANCE_NAME`_Write(command);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Configure
********************************************************************************
* Summary:
*   This function writes a command following parameters.
*
* Parameters:
*   command: Command to be sent
*   params: An array of parameters for the command
*   size: The size of the parameter array
*
*******************************************************************************/
void `$INSTANCE_NAME`_Configure(uint8_t command, const uint8_t *params, uint32_t size) {
    uint32_t i;
    `$INSTANCE_NAME`_WriteCommand(command);
    `$INSTANCE_NAME`_DataMode();
    for (i = 0; i < size; i++) {
        `$INSTANCE_NAME`_Write(params[i]);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ColumnAddressSet
********************************************************************************
* Summary: 
*   Set the column address
*
*******************************************************************************/
void `$INSTANCE_NAME`_ColumnAddressSet(uint32_t start, uint32_t end) {
    `$INSTANCE_NAME`_WriteCommand(`$INSTANCE_NAME`_CMD_CASET);
    `$INSTANCE_NAME`_DataMode();
    `$INSTANCE_NAME`_Write(CY_HI8(start));
    `$INSTANCE_NAME`_Write(CY_LO8(start));
    `$INSTANCE_NAME`_Write(CY_HI8(end));
    `$INSTANCE_NAME`_Write(CY_LO8(end));//X address set
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ColumnAddressSet
********************************************************************************
* Summary: 
*   Set the Row address
*
*******************************************************************************/
void `$INSTANCE_NAME`_RowAddressSet(uint32_t start, uint32_t end) {
    `$INSTANCE_NAME`_WriteCommand(`$INSTANCE_NAME`_CMD_RASET);
    `$INSTANCE_NAME`_DataMode();
    `$INSTANCE_NAME`_Write(CY_HI8(start));
    `$INSTANCE_NAME`_Write(CY_LO8(start));
    `$INSTANCE_NAME`_Write(CY_HI8(end));
    `$INSTANCE_NAME`_Write(CY_LO8(end));//Y address set
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_WriteMemoryFill
********************************************************************************
* Summary: 
*   Fill the memory area with a color
*
*******************************************************************************/
void `$INSTANCE_NAME`_WriteMemoryFill(uint32_t n, uint32_t color) {
    uint32_t i;
    uint8_t r = (uint8_t)(color >> 16);
    uint8_t g = (uint8_t)(color >> 8);
    uint8_t b = (uint8_t)(color >> 0);
    
    `$INSTANCE_NAME`_WriteCommand(`$INSTANCE_NAME`_CMD_RAMWR);
    `$INSTANCE_NAME`_DataMode();
    for (i = 0; i < n; i++) {
        `$INSTANCE_NAME`_Write(r);
        `$INSTANCE_NAME`_Write(g);
        `$INSTANCE_NAME`_Write(b);
    } 
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_WriteMemoryBlock
********************************************************************************
* Summary: 
*   Fill a memory area with an image
*
*******************************************************************************/
void `$INSTANCE_NAME`_WriteMemoryBlock(uint32_t n, const uint8_t *image) {
    uint32_t i;
    
    `$INSTANCE_NAME`_WriteCommand(`$INSTANCE_NAME`_CMD_RAMWR);
    `$INSTANCE_NAME`_DataMode();
    for (i = 0; i < n; i++) {
        `$INSTANCE_NAME`_Write(*image++);
        `$INSTANCE_NAME`_Write(*image++);
        `$INSTANCE_NAME`_Write(*image++);
    }
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_WriteMemoryImage
********************************************************************************
* Summary: 
*   Fill a memory area with an image
*
*******************************************************************************/
void `$INSTANCE_NAME`_WriteMemoryImage(uint32_t width, uint32_t height, const uint8_t *image) {
    CY_ASSERT_L2(width <= 256 / 3);
    CY_ASSERT_L2(height <= 256);
    `$INSTANCE_NAME`_WriteCommand(`$INSTANCE_NAME`_CMD_RAMWR);
    `$INSTANCE_NAME`_DataMode();
    `$INSTANCE_NAME`_DMA_WRITE_Init();
    `$INSTANCE_NAME`_DMA_WRITE_SetXloopDataCount(&`$INSTANCE_NAME`_DMA_WRITE_BlockXfer, width * 3);
    `$INSTANCE_NAME`_DMA_WRITE_SetXloopSrcIncrement(&`$INSTANCE_NAME`_DMA_WRITE_BlockXfer, 1);
    `$INSTANCE_NAME`_DMA_WRITE_SetYloopDataCount(&`$INSTANCE_NAME`_DMA_WRITE_BlockXfer, height);
    `$INSTANCE_NAME`_DMA_WRITE_SetYloopSrcIncrement(&`$INSTANCE_NAME`_DMA_WRITE_BlockXfer, width * 3);
    `$INSTANCE_NAME`_DMA_WRITE_Start(image, (const void *)`$INSTANCE_NAME`_FIFO_PTR);
    while (!`$INSTANCE_NAME`_DMA_WRITE_GetInterruptStatus()) ;
    `$INSTANCE_NAME`_DMA_WRITE_Stop();
    `$INSTANCE_NAME`_DMA_WRITE_ClearInterrupt();
}

/* [] END OF FILE */
