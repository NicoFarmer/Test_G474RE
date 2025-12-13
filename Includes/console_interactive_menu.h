/*! \file CGlobale.h
        \brief Classe qui contient toute l'application
*/
#ifndef _CONSOLE_INTERACTIVE_MENU_H_
#define _CONSOLE_INTERACTIVE_MENU_H_

#include "console_interaction.h"
#include "CAsservissement.h"

class CMenuApp : public ConsoleInteraction
{
public:
    CMenuApp();
    //CAsservissement m_asservissement = CAsservissement();

    void send_to_console(char msg[]);  // méthode virtuelle pure ré-implémentée

    void page1();
    void page_capteurs();
    void page_asservissement();

    // ___________________________________
    // Les moteurs
    void page_cde_moteurs();

    bool arret_moteurs();
    bool cde_mot_G_M1();
    bool cde_mot_G_M2();
    bool cde_mot_G_M3();
    bool cde_mot_G_P1();
    bool cde_mot_G_P2();
    bool cde_mot_G_P3();

    bool cde_mot_D_M1();
    bool cde_mot_D_M2();
    bool cde_mot_D_M3();
    bool cde_mot_D_P1();
    bool cde_mot_D_P2();
    bool cde_mot_D_P3();

    bool cde_mot_M3_M1();
    bool cde_mot_M3_M2();
    bool cde_mot_M3_M3();
    bool cde_mot_M3_P1();
    bool cde_mot_M3_P2();
    bool cde_mot_M3_P3();



    bool simu_codeur();

    void page_set_param_1();
    void page_set_param_2();

    bool action_set_param1(double val);
    bool action_read_param1();

    bool action_set_param2(int val);
    bool action_read_param2();

    bool action_read_params();


    bool action_asserv_vitesse_1_plus();
    bool action_asserv_vitesse_1_moins();
    bool action_asserv_vitesse_2_plus();
    bool action_asserv_vitesse_2_moins();
    bool action_active_debug_asserv();
    bool action_stop_debug_asserv();


    bool read_codeurs();
    bool read_analog_inputs();
    bool read_telemetre();

    // ___________________________________
    // Servomoteurs
    void page_servos();

    bool page_servo1_1200();
    bool page_servo1_1500();
    bool page_servo1_1700();
    bool page_servo1_2000();

    bool page_servo2_1200();
    bool page_servo2_1500();
    bool page_servo2_1700();
    bool page_servo2_2000();

    bool page_servo3_1200();
    bool page_servo3_1500();
    bool page_servo3_1700();
    bool page_servo3_2000();

    bool page_servo4_1200();
    bool page_servo4_1500();
    bool page_servo4_1700();
    bool page_servo4_2000();


    bool asser_stop();
    bool asser_resetPos();

    bool asser_avant10();
    bool asser_avant50();
    bool asser_avant100();

    bool asser_arriere10();
    bool asser_arriere50();
    bool asser_arriere100();

    bool get_xy_asser();

    // _____________________________
    // Page I2C
    void page_i2c();
    bool i2c_action_scan();

    double m_param1;
    int m_param2;

};
#endif 



