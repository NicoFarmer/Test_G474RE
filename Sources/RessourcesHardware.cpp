/*! \file RessoucesHardware.cpp
	\brief Déclare les ressources hardware du MBED utilisées par le reste du logiciel
*/
#include "RessourcesHardware.h"

// ===================================================
//          LED INTEGREE SUR LA CARTE
// ===================================================

// --------------------------------------------------
void setLedBuiltin(bool state)
{
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, (GPIO_PinState)state);
}

// --------------------------------------------------
void toggleLedBuiltin()
{
    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
}

// ===================================================
//              COMMANDES MOTEURS
// ===================================================

/*!
 * \brief Commande de moteur
 * \param num_moteur numéro du moteur entre 1 et 4
 * \param cde_pourcent valeur signée du PWM
 * PWM = PeriodTimer * (cde_pourcent / 100)
 *      PeriodTimer = 8500 (htim<xxx>.Init.Period = 8500)
 *      PWM = 8500/100 * cde_pourcent
 *      PWM = 85 * cde_pourcent
 *      (valable pour les 3 channels sur timer)
 */
void CdeMoteur(unsigned char num_moteur, float cde_pourcent)
{
    const float COEF_CDE_MOTEUR = 85;
    switch(num_moteur)
    {
    // ___________________________________________
    case 1:
           if (cde_pourcent == 0) {
               HAL_GPIO_WritePin(Mot1_Sens1_GPIO_Port, Mot1_Sens1_Pin, GPIO_PIN_RESET);
               HAL_GPIO_WritePin(Mot1_Sens2_GPIO_Port, Mot1_Sens2_Pin, GPIO_PIN_RESET);
               __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
           }
           else if (cde_pourcent > 0) {
               HAL_GPIO_WritePin(Mot1_Sens1_GPIO_Port, Mot1_Sens1_Pin, GPIO_PIN_SET);
               HAL_GPIO_WritePin(Mot1_Sens2_GPIO_Port, Mot1_Sens2_Pin, GPIO_PIN_RESET);
               __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, COEF_CDE_MOTEUR * cde_pourcent);
           }
           else {
               HAL_GPIO_WritePin(Mot1_Sens1_GPIO_Port, Mot1_Sens1_Pin, GPIO_PIN_RESET);
               HAL_GPIO_WritePin(Mot1_Sens2_GPIO_Port, Mot1_Sens2_Pin, GPIO_PIN_SET);
               __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, COEF_CDE_MOTEUR * (-cde_pourcent));
           }
        break;
    // ___________________________________________
    case 2:
           if (cde_pourcent == 0) {
               HAL_GPIO_WritePin(Mot2_Sens1_GPIO_Port, Mot2_Sens1_Pin, GPIO_PIN_RESET);
               HAL_GPIO_WritePin(Mot2_Sens2_GPIO_Port, Mot2_Sens2_Pin, GPIO_PIN_RESET);
               __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
           }
           else if (cde_pourcent > 0) {
               HAL_GPIO_WritePin(Mot2_Sens1_GPIO_Port, Mot2_Sens1_Pin, GPIO_PIN_RESET);
               HAL_GPIO_WritePin(Mot2_Sens2_GPIO_Port, Mot2_Sens2_Pin, GPIO_PIN_SET);
               __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, COEF_CDE_MOTEUR * cde_pourcent);
           }
           else {
               HAL_GPIO_WritePin(Mot2_Sens1_GPIO_Port, Mot2_Sens1_Pin, GPIO_PIN_SET);
               HAL_GPIO_WritePin(Mot2_Sens2_GPIO_Port, Mot2_Sens2_Pin, GPIO_PIN_RESET);
               __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, COEF_CDE_MOTEUR * (-cde_pourcent));
           }
        break;
    // ___________________________________________
    case 3:
        if (cde_pourcent == 0) {
            HAL_GPIO_WritePin(Mot3_Sens1_GPIO_Port, Mot3_Sens1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(Mot3_Sens2_GPIO_Port, Mot3_Sens2_Pin, GPIO_PIN_RESET);
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);
        }
        else if (cde_pourcent > 0) {
            HAL_GPIO_WritePin(Mot3_Sens1_GPIO_Port, Mot3_Sens1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(Mot3_Sens2_GPIO_Port, Mot3_Sens2_Pin, GPIO_PIN_RESET);
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, COEF_CDE_MOTEUR * cde_pourcent);
        }
        else {
            HAL_GPIO_WritePin(Mot3_Sens1_GPIO_Port, Mot3_Sens1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(Mot3_Sens2_GPIO_Port, Mot3_Sens2_Pin, GPIO_PIN_SET);
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, COEF_CDE_MOTEUR * (-cde_pourcent));
        }
        break;
    // ___________________________________________
    default:
        break;
    }
}







// ===================================================
//                      CODEURS
// ===================================================

signed short getCodeur(int num)
{
    switch(num)
    {
    case 1 : return __HAL_TIM_GET_COUNTER(&htim4);
    case 2 : return __HAL_TIM_GET_COUNTER(&htim8);
    //case 3 : return __HAL_TIM_GET_COUNTER(&htim4); break;
    //case 4 : return __HAL_TIM_GET_COUNTER(&htim8); break;
    default: break;
    }
    return 0;
}

// ===================================================
//              ENTREES ANALOGIQUES
// ===================================================

// --------------------------------------------------
unsigned int readAnalog(int num_eana)
{
    ADC_ChannelConfTypeDef sConfig = {0};
    int adc_channel;
    switch(num_eana)
    {
    case 1: adc_channel = ADC_CHANNEL_1;	break;	// Eana1 : PA0
    case 2: adc_channel = ADC_CHANNEL_5;   	break;  // Eana2 : PB14
    case 3: adc_channel = ADC_CHANNEL_6;    break;  // Eana3 : PC0
    case 4: adc_channel = ADC_CHANNEL_7;   	break;  // Eana4 : PC1
    default :  // entrée Eana inexistante
        return 0;
    }

    sConfig.Channel = adc_channel;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_12CYCLES_5;
    sConfig.SingleDiff = ADC_SINGLE_ENDED;
    //sConfig.OffsetNumber = ADC_OFFSET_NONE;
    //sConfig.Offset = 0;
    //sConfig.OffsetSignedSaturation = DISABLE;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 1000);
    uint32_t analog_value = HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);
    return analog_value;
}

// --------------------------------------------------
#define COEF_ADC_VOLTS (3.3f/4096)
float readAnalogVolt(int channel)
{
    return readAnalog(channel) * COEF_ADC_VOLTS;
}

// ===================================================
//              SERVO MOTEURS
// ===================================================
// _______________________________________________
//!
//! \brief Commande d'un servo moteur
//! \param num_servo numéro du servo moteur (entre 1 et 8)
//! \param pulse_usec largeur d'impulsion souhaitée en [µsec]
//! Pulse = ARR * (largeur d’impulsion voulue  en µsec / 20 000µsec)
//! Pour les 4 servo du TIM2 (32 bits)
//!     Pulse = (3 400 000/20 000) * largeur d’impulsion voulue  en µsec
//!     Pulse = 170 * largeur d’impulsion voulue  en µsec
//!
void CdeServo(unsigned char num_servo, unsigned int pulse_usec)
{
    const float COEF_TIM32bits = 170;

    switch(num_servo)
    {
    case 1 : // Servo1: PB11
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, COEF_TIM32bits*pulse_usec);
        break;
    case 2 : // Servo2: PA15
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, COEF_TIM32bits*pulse_usec);
        break;
    case 3 : // Servo3: PA1
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, COEF_TIM32bits*pulse_usec);
        break;
    case 4 : // Servo4: PB10
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, COEF_TIM32bits*pulse_usec);
        break;
    default :
        break;
    }
}
