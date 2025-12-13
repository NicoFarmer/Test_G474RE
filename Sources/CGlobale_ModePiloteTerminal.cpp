/*! \file CGlobale_ModePiloteTerminal.cpp
    \brief Classe qui contient toute l'application pour le mode de fonctionnement pilote via Anaconbot
*/
#include "CGlobale.h"
#include "stdio.h"

//___________________________________________________________________________
/*!
   \brief Gestion du mode piloté via Anaconbot

   \param --
   \return --
*/
void CGlobale::ModePiloteTerminal(void)
{
    while(1) {
        if (tick) {
            tick = 0;
            SequenceurModePiloteTerminal();
        }
    }
}

// _____________________________________________________________
void CGlobale::ReceiveRS232_ModePiloteTerminal(void)
{
    char rxData;
    //rxData = _rs232_pc_rx.getc();
}


//___________________________________________________________________________
/*!
   \brief Sequenceur de taches en mode autonome

   \param --
   \return --
*/
void CGlobale::SequenceurModePiloteTerminal(void)
{
    static unsigned int cpt1msec = 0;
    static unsigned int cpt10msec = 0;
    static unsigned int cpt20msec = 0;
    static unsigned int cpt50msec = 0;
    static unsigned int cpt100msec = 0;
    static unsigned int cpt200msec = 0;
    static unsigned int cpt500msec = 0;
    static unsigned int cpt1sec = 0;

    static unsigned char compteur=1;
    static unsigned char toggle=0;
    static float cde_mot1 = 0.;
    static int signe_cde_mot = +1;

    // ______________________________
    cpt1msec++;
    if (cpt1msec >= TEMPO_1msec) {
        cpt1msec = 0;

        m_codeurs.Traitement();
    }

    // ______________________________
    cpt10msec++;
    if (cpt10msec >= TEMPO_10msec) {
        cpt10msec = 0;
        unsigned char rxdata[2], txdata[2]= {0xF0, 0x69};
        HAL_SPI_TransmitReceive(&hspi2, txdata, rxdata, 2, 100);
    }

    // ______________________________
    cpt20msec++;
    if (cpt20msec >= TEMPO_20msec) {
        cpt20msec = 0;

        HAL_GPIO_WritePin(Mot1_Sens1_GPIO_Port, Mot1_Sens1_Pin, (GPIO_PinState)test_Mot1_Sens1);
        HAL_GPIO_WritePin(Mot1_Sens2_GPIO_Port, Mot1_Sens2_Pin, (GPIO_PinState)test_Mot1_Sens2);
        HAL_GPIO_WritePin(Mot2_Sens1_GPIO_Port, Mot2_Sens1_Pin, (GPIO_PinState)test_Mot2_Sens1);
        HAL_GPIO_WritePin(Mot2_Sens2_GPIO_Port, Mot2_Sens2_Pin, (GPIO_PinState)test_Mot2_Sens2);
        HAL_GPIO_WritePin(Mot3_Sens1_GPIO_Port, Mot3_Sens1_Pin, (GPIO_PinState)test_Mot3_Sens1);
        HAL_GPIO_WritePin(Mot3_Sens2_GPIO_Port, Mot3_Sens2_Pin, (GPIO_PinState)test_Mot3_Sens2);

        HAL_GPIO_WritePin(Led1_GPIO_Port, Led1_Pin, (GPIO_PinState)test_Led1);
        HAL_GPIO_WritePin(Led2_GPIO_Port, Led2_Pin, (GPIO_PinState)test_Led2);
        HAL_GPIO_WritePin(Cde_Mosfet_GPIO_Port, Cde_Mosfet_Pin, (GPIO_PinState)test_CdeMosfet);

        test_Etor1 = HAL_GPIO_ReadPin(Etor1_GPIO_Port, Etor1_Pin);
        test_Etor2 = HAL_GPIO_ReadPin(Etor2_GPIO_Port, Etor2_Pin);
        test_Etor3 = HAL_GPIO_ReadPin(Etor3_GPIO_Port, Etor3_Pin);

    }


    // ______________________________
    cpt50msec++;
    if (cpt50msec >= TEMPO_50msec) {
        cpt50msec = 0;
        toggleLedBuiltin();
        //printf("%d\n\r", HAL_GetTick());
    }

    // ______________________________
    cpt100msec++;
    if (cpt100msec >= TEMPO_100msec) {
        cpt100msec = 0;
/*
        unsigned char c='4';
        unsigned char r='0';

        HAL_UART_Transmit(&huart4, &c, 1, 100);
        if (HAL_UART_Receive(&huart4, &r, 1, 100) == HAL_OK) {
        	printf("[%d] UART4: %c\n\r", HAL_GetTick(), r);
        }
*/
    }

    // ______________________________
    cpt200msec++;
    if (cpt200msec >= TEMPO_200msec) {
        cpt200msec = 0;
/*
        unsigned char c='5';
        unsigned char r='0';
        HAL_UART_Transmit(&huart5, &c, 1, 100);
        if (HAL_UART_Receive(&huart5, &r, 1, 100) == HAL_OK) {
        	printf("[%d] UART5: %c\n\r", HAL_GetTick(), r);
        }
*/
    }
    // ______________________________
    cpt500msec++;
    if (cpt500msec >= TEMPO_500msec) {
        cpt500msec = 0;
    }
    // ______________________________
    cpt1sec++;
    if (cpt1sec >= TEMPO_1sec) {
        cpt1sec = 0;
    }

}
