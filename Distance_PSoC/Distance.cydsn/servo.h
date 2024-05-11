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

/* [] END OF FILE */

void SetServoLimit(unsigned char id, unsigned short int cw_limit, unsigned short int ccw_limit);
void SetServoPosition(unsigned char id, unsigned short int position, unsigned short int velocity);
void SetServoVelocity(unsigned char id, signed short int velocity);

#define WAITING_TIME 2
