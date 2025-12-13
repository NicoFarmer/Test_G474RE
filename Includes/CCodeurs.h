/*! \file CCodeurs.h
    \brief Classe codeurs de position
*/
#ifndef _CODEURS_H_
#define _CODEURS_H_

class CCodeurs
{
public :
    CCodeurs();

    typedef enum {
     CODEUR_1 = 1,
     CODEUR_2,
    }eCODEURS_POSITION;

    void Traitement(void);
    void reset(unsigned char num_codeur, signed long val=0);

    signed long m_CumulCodeurPosition1;
    signed long m_CumulCodeurPosition2;

    signed short m_old_codeur1;
    signed short m_old_codeur2;
};
#endif


