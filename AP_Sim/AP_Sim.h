#ifndef AP_SIM_H
#define AP_SIM_H

void AP_Sim_Init(void);

void AP_Sim_Update(float roll_command,
                   float dt);

float AP_Sim_GetRoll(void);

float AP_Sim_GetRollRate(void);

#endif
