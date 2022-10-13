#include <stdio.h>
#include <stdlib.h>

#include "Header.h"

/*

 ******************
 ----- VZORCE -----
 ******************
 FormulaA - Otacky hnaciho bubnu nB(ot/min)
 FormulaB - Prevodovy pomer prevodovky iP(-)
 FormulaC - Hmotnost nakladu mN(kg)
 FormulaD - Hmotnost pasu mP(kg)
 FormulaE - Celkovy odpor OC(N)
 FormulaF - Vypocet momentu na hnacim bubnu M(N*m)
 FormulaG - Vykon potrebny pro pohyb dopravniku Pc(W)
 FormulaH - Vykon pro rozjezd Pm(W)

 ********************
 ----- FORMULAS -----
 ********************
 FormulaA - RPM of drived pulley nB(ot/min)
 FormulaB - Gear ratio of transmission iP(-)
 FormulaC - Load weight mN(kg)
 FormulaD - Belt weight mP(kg)
 FormulaE - Total resistant force OC(N)
 FormulaF - Drived pulley torque M(N*m)
 FormulaG - Power required to move the conveyor Pc(W)
 FormulaH - Power required for start Pm(W)

*/


// Otacky hnaciho bubnu nB(ot/min)
void FormulaA(float *v, float *d, float *result){

    *result = ((*v)*1000) / ((float)PI * (*d));
}

// Prevodovy pomer prevodovky iP(-)
void FormulaB(float *nm, float *nB, float *result){

    *result = (*nm) / (*nB);
}

// Hmotnost nakladu mN(kg)
void FormulaC(float *mZ, float *L, float *km, float *result){

    *result = (*mZ) * ((*L)/1000) * (*km);
}

// Hmotnost pasu mP(kg)
void FormulaD(float *L, float *S, float *mspec, float *result){

    *result = ((*L)/1000) * ((*S)/1000) * (*mspec);
}

// Celkovy odpor OC(N)
void FormulaE(float *nM, float *mP, float *alpha, float *result){

    if((*alpha) == 90){

            *result = (((float)FRIC * (float)GFORCE * ((*nM) + (*mP))) / (cos((*alpha - 1) * RAD))) * 2;   // Special case for 90deg
    }

    else{
        *result = ((float)FRIC * (float)GFORCE * ((*nM) + (*mP))) / (cos((*alpha) * RAD));
    }


}

// Vypocet momentu na hnacim bubnu M(N*m)
void FormulaF(float *OCr, float *d, float *result){

    *result = (*OCr) * (((*d)/1000)/2);
}

// Vykon potrebny pro pohyb dopravniku Pc(W)
void FormulaG(float *M, float *nB, float *result){

    *result = round((2 * (float)PI * (*M) * (*nB)) / 60);

}

// Vykon pro rozjezd Pm(W)
void FormulaH(float *Pc, float *result){

    *result = (*Pc) * (float)KR;
}


 // ********************
 // ----- MATH FIX -----
 // ********************

 // ROUND APP A
 void RoundAppA(float *OC, float *result){

    *result = (round((*OC) / 100))*100;

    if((*OC) > (*result)){

        *result += 50;
    }
 }

// ROUND APP B
void RoundAppB(float *M, float *result){

    *result = (round((*M) * 10)) / 10;
}
