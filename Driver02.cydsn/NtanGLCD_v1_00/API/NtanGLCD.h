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

extern void `$INSTANCE_NAME`_Start(void);
extern void `$INSTANCE_NAME`_WriteData(uint8_t data);
extern void `$INSTANCE_NAME`_WriteCommand(uint8_t command);

#endif /* `$INSTANCE_NAME`_H */
    
/* [] END OF FILE */
