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

        m_asservissement_position.Traitement();
        m_asservissement_vitesse.Traitement();
    }

    // ______________________________
    cpt20msec++;
    if (cpt20msec >= TEMPO_20msec) {
        cpt20msec = 0;
    }


    // ______________________________
    cpt50msec++;
    if (cpt50msec >= TEMPO_50msec) {
        cpt50msec = 0;
    }

    // ______________________________
    cpt100msec++;
    if (cpt100msec >= TEMPO_100msec) {
        cpt100msec = 0;
    }

    // ______________________________
    cpt200msec++;
    if (cpt200msec >= TEMPO_200msec) {
        cpt200msec = 0;
        //printf("POS: %f / Vit=%f / Codeur=%ld\n\r", m_asservissement_position.getPosition(), m_asservissement_vitesse.getVitesse(), m_codeurs.m_CumulCodeurPosition2);
    }
    // ______________________________
    cpt500msec++;
    if (cpt500msec >= TEMPO_500msec) {
        cpt500msec = 0;

        toggleLedBuiltin();
    }
    // ______________________________
    cpt1sec++;
    if (cpt1sec >= TEMPO_1sec) {
        cpt1sec = 0;

        //printf("+100 pas\n\r");
        //SimuPasCodeurs(100);
        //printf("  > [%d] Codeur=%d\n\r",HAL_GetTick(), getCodeur2());
    }

}



void CGlobale::SimuPasCodeurs(int count)
{
	int _tempo = 100;

	printf("\n\r+%d pas : Compteur avant: %ld\n\r", count*4, m_codeurs.m_CumulCodeurPosition2);
	if (count > 0) {
		for (int i=0; i<count; i++) {
			WRITE_REG(GPIOB->ODR, 0x00);
			for (int t=0; t<=_tempo; t++);
			WRITE_REG(GPIOB->ODR, 0x80);
			for (int t=0; t<=_tempo; t++);
			WRITE_REG(GPIOB->ODR, 0x81);
			for (int t=0; t<=_tempo; t++);
			WRITE_REG(GPIOB->ODR, 0x01);
			for (int t=0; t<=_tempo; t++);
			WRITE_REG(GPIOB->ODR, 0x00);
			for (int t=0; t<=_tempo; t++);
			m_codeurs.Traitement();
		}
	}
	else {
		for (int i=0; i<(-count); i++) {
			WRITE_REG(GPIOB->ODR, 0x00);
			for (int t=0; t<=_tempo; t++);
			WRITE_REG(GPIOB->ODR, 0x01);
			for (int t=0; t<=_tempo; t++);
			WRITE_REG(GPIOB->ODR, 0x81);
			for (int t=0; t<=_tempo; t++);
			WRITE_REG(GPIOB->ODR, 0x80);
			for (int t=0; t<=_tempo; t++);
			WRITE_REG(GPIOB->ODR, 0x00);
			for (int t=0; t<=_tempo; t++);
			m_codeurs.Traitement();
		}

	}
	printf("Après : Counter = %ld\n\r", m_codeurs.m_CumulCodeurPosition2);
}

