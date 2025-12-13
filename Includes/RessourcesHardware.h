/*! \file RessoucesHardware.h
	\brief Déclare les ressources hardware du MBED utilisées par le reste du logiciel
*/
#ifndef _RESSOURCES_HARDWARE_H_ 
#define _RESSOURCES_HARDWARE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define I2C_HDL_ELECTROBOT hi2c2
#define I2C_DEFAULT_TIMEOUT (100)

#define CODEUR_ROUE (CCodeurs::CODEUR_2)

//#define ANGLE_PAR_PAS_CODEUR (7200./7813.)//(0.92272)
#define ANGLE_PAR_PAS_CODEUR (360./400.)

void setLedBuiltin(bool state);
void toggleLedBuiltin();
void CdeMoteur(unsigned char num_moteur, float cde_pourcent);
void CdeServo(unsigned char num_servo, unsigned int pulse_usec);
signed short getCodeur(int num);
unsigned int readAnalog(int channel);
float readAnalogVolt(int channel);

#ifdef __cplusplus
}
#endif

#endif


