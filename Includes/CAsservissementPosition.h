/*! \file CAsservissementPosition.h
    \brief Classe de gestion de l'asservissement de l'AD
*/
#ifndef _ASSERVISSEMENT_POSITION_H_
#define _ASSERVISSEMENT_POSITION_H_

class CAsservissementPosition
{
private :
    static const float DEFAULT_SPEED;
    static const float SEUIL_CONVERGENCE_ANGLE;
    static const float Te;

    bool m_asservissement_en_cours;
    int m_codeur_old;
    float m_consigne_position;
    float m_consigne_vitesse;
    float m_position;
    bool m_maintien_position;   //! force le maintien en position après convergence ou relâchement dès que la consigne a été atteinte

    bool m_new_consigne;

    float m_erreur;
    float m_cumul_erreur;

    bool m_convergence;

    float m_coef_p;
    float m_coef_i;
    float m_coef_d;

    float m_rampe_vitesse_start;

    bool m_debug;

    void _asservissement();
    void _calcul_position();
    void _reset();
    float modulo180M180(float degre);
    float diff_angles(float angle1, float angle2);
    float diff_angles_abs(float angle1, float angle2);

public :
    CAsservissementPosition();

    void Traitement(void);

    void setPIDCoef(float p, float i, float d=0);
    void Stop();
    void CommandeVitesse(float consigne_vitesse);
    void CommandePosition(float consigne_position, float consigne_vitesse = DEFAULT_SPEED, bool maintien_position=false);
    float getPosition();
    void resetPosition(float position=0.);
    bool isConvergence();
    void activeDebug(bool active=true);

};
#endif


