/*! \file CAsservissementVitesse.h
    \brief Classe de gestion de l'asservissement de l'AD
*/
#ifndef _ASSERVISSEMENT_VITESSE_H_
#define _ASSERVISSEMENT_VITESSE_H_

class CAsservissementVitesse
{
private :
    static const float Te;

    bool m_asservissement_en_cours;
    int m_codeur_old;
    float m_consigne_vitesse;
    float m_vitesse;

    float m_erreur_vitesse;
    float m_erreur_position;
    float m_cumul_erreur_vitesse;

    float m_zone_morte_moteur;

    float m_vitesse_coef_p;
    float m_vitesse_coef_i;
    float m_vitesse_coef_d;

    bool m_debug;

    void _asservissement_vitesse();
    void _calcul_vitesse();
    void _reset();

public :
    CAsservissementVitesse();

    void Traitement(void);

    void setPIDCoef(float p, float i, float d=0);
    void setZoneMorteMoteur(float zone_morte_pourcent);
    void CommandeManuelle(float pourcent);
    void CommandeVitesse(float consigne_vitesse);
    float getVitesse();
    void activeDebug(bool active=true);
};
#endif


