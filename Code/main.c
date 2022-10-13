#include <stdio.h>
#include <stdlib.h>

#include "Header.h"

    /*
    ---------------------
    -------Legenda-------
    ---------------------
    L     - Osova vzdalenost bubnu (mm)
    S     - Sirka pasu (mm)
    alpha - Sklon dopravniku (°)
    mZ    - Max. hmotnost nakladu (kg/m)
    km    - Koeficient pretizeni (-)
    v     - Rychlost posuvu (m/min)
    d     - Prumer bubnu (mm)
    ------------------------------------

    ---------------------
    -------Vystupy-------
    ---------------------
    nB     - Otacky bubnu (1/min)
    iP     - Prevodovy pomer (-)
    nM     - Hmotnost nakladu (kg)
    mP     - Hmotnost pasu (kg)
    OC     - Celkovy odpor (N)
    OCr    - Celkovy odpor (zaokrouhlene) (N)
    M      - Vypocet momentu na hnacim bubnu (N*m)
    M      - Vypocet momentu na hnacim bubnu (zaokrouhlene) (N*m)
    Pc     - Vykon potrebny pro pohyb dopravniku (W)
    Pm     - Vykon pro rozjezd (W)

    ------------------------------------
    */

//---------------
// Variables
//---------------
float L, S, alpha, mZ, km, v, d, mspec, nm; // Inputs
float nB, iP, mN, mP, OC, OCr, M, Mr, Pc, Pm; // Outputs

//---------------
// Tech Variables
//---------------
//char MON;
int MENIC;

//---------------
// MAIN
//---------------
int main()
{


    #ifdef ZADAVACI

    float cargo[7];

    EnterValue(cargo, &MENIC);

    L = cargo[0];
    S = cargo[1];
    alpha = cargo[2];
    mZ = cargo[3];
    km = cargo[4];
    v = cargo[5];
    d = cargo[6];
    mspec = cargo[7];
    nm = cargo[8];

    #endif // ZADAVACI

    #ifdef TESTOVACI

    L = 3500;
    S = 1100;
    alpha = 90;
    mZ = 5;
    km = 1.5;
    v = 8;
    d = 63;
    mspec = 5;
    nm = 1400;

    #endif // TESTOVACI


    #ifdef LANG_CZ
    printf("APLIKACE NA VYPOCET PASOVEHO DOPRAVNIKU \n");
    printf("Autor: Jaromir Baca \n");
    #endif // LANG_CZ

    #ifdef LANG_EN
    printf("APPLICATION FOR CALCULATING BELT CONVEYOR \n");
    printf("Author: Jaromir Baca \n");
    #endif // LANG_EN

    printf("BRNO 2022 \n");
    printf("Git Link: https://github.com/StingrayCZ\n");

    JUMP
    printf("************************************\n");
    JUMP

    #ifdef LANG_CZ
    printf("************************************\n");
    printf("********** ZADANE HODNOTY **********\n");
    printf("************************************\n");
    #endif // LANG_CZ

    #ifdef LANG_EN
    printf("************************************\n");
    printf("********** ENTERED VALUES **********\n");
    printf("************************************\n");
    #endif // LANG_EN


    printf("Osova vzdalenost bubnu, L = %.2f mm \n", L);
    printf("Sirka pasu, S = %.2f mm \n", S);

    // SKLON DOPRAVNIKU
    if(alpha == 0){
        #ifdef LANG_CZ
        printf("Dopravnik je v rovinne poloze. Nulovy uhel sklonu. \n");
        #endif // LANG_CZ

        #ifdef LANG_EN
        printf("The conveyor is in a flat position. Zero tilt angle. \n");
        #endif // LANG_EN

    }

    else if(alpha == 90){
        #ifdef LANG_CZ
        printf("Dopravnik miri stremhlav, sklon dopravniku je 90%c. \n", DEGREE);
        #endif // LANG_CZ

        #ifdef LANG_EN
        printf("The conveyor is straight forward, the inclination of the conveyor is 90%c. \n", DEGREE);
        #endif // LANG_EN

    }

    else{
        #ifdef LANG_CZ
        printf("Sklon dopravniku, alfa = %.0f%c \n", alpha, DEGREE);
        #endif // LANG_CZ

        #ifdef LANG_EN
        printf("Conveyor inclination, alpha = %.0f%c \n", alpha, DEGREE);
        #endif // LANG_EN

    }


    #ifdef LANG_CZ
    printf("Max. hmotnost nakladu, mZ = %.2f kg/m \n", mZ);
    printf("Koeficient pretizeni, km = %.2f \n", km);
    printf("Rychlost posuvu, v = %.2f m/min (%.2f m/s) \n", v, (v / 60));
    printf("Prumer bubnu, d = %.2f mm \n", d);
    printf("Merna hmotnost pasu, mspec = %.2f kg/m2 \n", mspec);
    #endif // LANG_CZ

    #ifdef LANG_EN
    printf("Max. load weight, mZ = %.2f kg/m \n", mZ);
    printf("Coefficient of overload, km = %.2f \n", km);
    printf("Feed rate, v = %.2f m/min (%.2f m/s) \n", v, (v / 60));
    printf("Pulley diameter, d = %.2f mm \n", d);
    printf("Belt specific weight, mspec = %.2f kg/m2 \n", mspec);
    #endif // LANG_EN

    if(MENIC == 1){

        #ifdef LANG_CZ
        printf("Otacky elektromotoru bez menice, nm = %.0f ot/min \n", nm);
        #endif // LANG_CZ

        #ifdef LANG_EN
        printf("Electric motor speed without frequency changer, nm = %.0f rev/min \n", nm);
        #endif // LANG_EN

    }


    else if(MENIC == 2){

            #ifdef LANG_CZ
            printf("Otacky elektromotoru (zadane), %.0f ot/min \n", nm*2);
            printf("Menicem redukovane otacky elektromotoru, nm = %.0f rev/min \n", nm);
            #endif // LANG_CZ

            #ifdef LANG_EN
            printf("Electric motor speed (entered), %.0f ot/min \n", nm*2);
            printf("Electric motor speed reduced by a frequency changer, nm = %.0f ot/min \n", nm);
            #endif // LANG_EN

    }


    JUMP

    #ifdef LANG_CZ
    printf("Doplnujici hodnoty (pevne zadane): \n");
    printf("Gravitacni zrychleni, g = %.2f (m/s) \n", (float)GFORCE);
    printf("Soucinitel treni [pas/kluzna deska], f = %.1f (-) \n", (float)FRIC);
    printf("Koeficient pro rozjezd, kr = %.1f (-) \n", (float)KR);
    #endif // LANG_CZ

    #ifdef LANG_EN
    printf("Additional values (fixed value): \n");
    printf("Gravitational acceleration, g = %.2f (m/s) \n", (float)GFORCE);
    printf("Friction coefficient [belt/sliding plate], f = %.1f (-) \n", (float)FRIC);
    printf("Starting coefficient, kr = %.1f (-) \n", (float)KR);
    #endif // LANG_EN


    JUMP

    // VYPOCET
    FormulaA(&v, &d, &nB);

    FormulaB(&nm, &nB, &iP);

    FormulaC(&mZ, &L, &km, &mN);

    FormulaD(&L, &S, &mspec, &mP);

    FormulaE(&mN, &mP, &alpha, &OC);

    RoundAppA(&OC, &OCr);

    FormulaF(&OCr, &d, &M);

    RoundAppB(&M, &Mr);

    FormulaG(&Mr, &nB, &Pc);

    FormulaH(&Pc, &Pm);


    // VYSLEDKY (RESULTS)
    JUMP

    #ifdef LANG_CZ
    printf("************************************\n");
    printf("********* VYSLEDNE HODNOTY *********\n");
    printf("************************************\n");

    printf("Otacky hnaciho bubnu nB = %.1f ot/min \n", nB);
    printf("Prevodovy pomer prevodovky iP = %.1f (-) \n", iP);
    printf("Hmotnost nakladu mN = %.2f kg \n", mN);
    printf("Hmotnost pasu mP = %.2f kg \n", mP);
    printf("Celkovy odpor OC = %.2f = %.0f N \n",OC, OCr);
    printf("Moment na hnacim bubnu M = %.2f = %.1f N*m \n", M, Mr);
    printf("Vykon potrebny pro pohyb dopravniku Pc = %.0f W \n", Pc);
    printf("Vykon  pro rozjezd Pm = %.0f W \n", Pm);
    #endif // LANG_CZ

    #ifdef LANG_EN
    printf("************************************\n");
    printf("**********  RESULT VALUES **********\n");
    printf("************************************\n");

    printf("RPM of drived pulley nB = %.1f rev/min \n", nB);
    printf("Gear ratio of transmission iP = %.1f (-) \n", iP);
    printf("Load weight mN = %.2f kg \n", mN);
    printf("Belt weight mP = %.2f kg \n", mP);
    printf("Total resistant force OC = %.2f = %.0f N \n",OC, OCr);
    printf("Drived pulley torque M = %.2f = %.1f N*m \n", M, Mr);
    printf("Power required to move the conveyor Pc = %.0f W \n", Pc);
    printf("Power required for start Pm = %.0f W \n", Pm);
    #endif // LANG_EN


    JUMP
    JUMP

//    Month(&MON);
//
//    printf("Mesic je %s \n", MON);

    // Make a file

    FILE * fPointer;

    #ifdef LANG_CZ
    fPointer = fopen("Report - Belt Conveyor (CZ lang).txt", "w");

    fprintf(fPointer, "APLIKACE NA VYPOCET PASOVEHO DOPRAVNIKU\n");
    fprintf(fPointer, "Autor: Jaromir Baca \n");
    fprintf(fPointer, "BRNO 2022 \n");
    fprintf(fPointer, "Git Link: https://github.com/StingrayCZ\n");


    fprintf(fPointer, "\n");
    fprintf(fPointer, "************************************\n");
    fprintf(fPointer, "\n");

    fprintf(fPointer, "************************************\n");
    fprintf(fPointer, "********** ZADANE HODNOTY *********\n");
    fprintf(fPointer, "************************************\n");

    fprintf(fPointer, "\n");
    fprintf(fPointer, "Osova vzdalenost bubnu, L = %.2f mm \n", L);
    fprintf(fPointer, "Sirka pasu, S = %.2f mm \n", S);
    #endif // LANG_CZ

    #ifdef LANG_EN
    fPointer = fopen("Report - Belt Conveyor (EN lang).txt", "w");

    fprintf(fPointer, "APPLICATION FOR CALCULATING BELT CONVEYOR\n");
    fprintf(fPointer, "Author: Jaromir Baca \n");
    fprintf(fPointer, "BRNO 2022 \n");
    fprintf(fPointer, "Git Link: https://github.com/StingrayCZ\n");


    fprintf(fPointer, "\n");
    fprintf(fPointer, "************************************\n");
    fprintf(fPointer, "\n");

    fprintf(fPointer, "************************************\n");
    fprintf(fPointer, "********** ENTERED VALUES **********\n");
    fprintf(fPointer, "************************************\n");

    fprintf(fPointer, "\n");
    fprintf(fPointer, "Pulleys axial distance, L = %.2f mm \n", L);
    fprintf(fPointer, "Belt width, S = %.2f mm \n", S);
    #endif // LANG_EN



    // SKLON DOPRAVNIKU
    if(alpha == 0){
        #ifdef LANG_CZ
        fprintf(fPointer, "Dopravnik je v rovinne poloze. Nulovy uhel sklonu. \n");
        #endif // LANG_CZ

        #ifdef LANG_EN
        fprintf(fPointer, "The conveyor is in a flat position. Zero tilt angle. \n");
        #endif // LANG_EN
    }

    else if(alpha == 90){

        #ifdef LANG_CZ
        fprintf(fPointer, "Dopravnik miri stremhlav, sklon dopravniku je 90%c. \n", DEGREE);
        #endif // LANG_CZ

        #ifdef LANG_EN
        fprintf(fPointer, "The conveyor is heading headlong, angle is 90%c. \n", DEGREE);
        #endif // LANG_EN

    }

    else{
        #ifdef LANG_CZ
        fprintf(fPointer, "Sklon dopravniku, alfa = %.0f° \n", alpha);
        #endif // LANG_CZ

        #ifdef LANG_EN
        fprintf(fPointer, "Conveyor slope, alfa = %.0f° \n", alpha);
        #endif // LANG_EN
    }

    #ifdef LANG_CZ
    fprintf(fPointer, "Max. hmotnost nakladu, mZ = %.2f kg/m \n", mZ);
    fprintf(fPointer, "Koeficient pretizeni, km = %.2f \n", km);
    fprintf(fPointer, "Rychlost posuvu, v = %.2f m/min (%.2f m/s) \n", v, (v / 60));
    fprintf(fPointer, "Prumer bubnu, d = %.2f mm \n", d);
    fprintf(fPointer, "Merna hmotnost pasu, mspec = %.2f kg/m2 \n", mspec);
    #endif // LANG_CZ

    #ifdef LANG_EN
    fprintf(fPointer, "Max. hmotnost nakladu, mZ = %.2f kg/m \n", mZ);
    fprintf(fPointer, "Koeficient pretizeni, km = %.2f \n", km);
    fprintf(fPointer, "Rychlost posuvu, v = %.2f m/min (%.2f m/s) \n", v, (v / 60));
    fprintf(fPointer, "Prumer bubnu, d = %.2f mm \n", d);
    fprintf(fPointer, "Merna hmotnost pasu, mspec = %.2f kg/m2 \n", mspec);
    #endif // LANG_EN


    if(MENIC == 1){

        #ifdef LANG_CZ
        fprintf(fPointer, "Otacky elektromotoru bez menice, nm = %.0f ot/min \n", nm);
        #endif // LANG_CZ

        #ifdef LANG_EN
        fprintf(fPointer, "Electric motor speed without frequency changer, nm = %.0f ot/min \n", nm);
        #endif // LANG_EN

    }


    else{

        #ifdef LANG_CZ
        fprintf(fPointer, "Otacky elektromotoru (zadane), %.0f ot/min \n", nm*2);
        fprintf(fPointer, "Menicem redukovane otacky elektromotoru, nm = %.0f ot/min \n", nm);
        #endif // LANG_CZ

        #ifdef LANG_EN
        fprintf(fPointer, "Electric motor speed (entered), %.0f ot/min \n", nm*2);
        fprintf(fPointer, "Electric motor speed reduced by a frequency changer, nm = %.0f ot/min \n", nm);
        #endif // LANG_EN

    }

    #ifdef LANG_CZ
    fprintf(fPointer, "\n");
    fprintf(fPointer, "Doplnujici hodnoty (pevne zadane): \n");
    fprintf(fPointer, "Gravitacni zrychleni, g = %.2f (m/s) \n", (float)GFORCE);
    fprintf(fPointer, "Soucinitel treni [pas/kluzna deska], f = %.1f (-) \n", (float)FRIC);
    fprintf(fPointer, "Koeficient pro rozjezd, kr = %.1f (-) \n", (float)KR);

    fprintf(fPointer, "\n");
    fprintf(fPointer, "\n");

    fprintf(fPointer, "************************************\n");
    fprintf(fPointer, "********* VYSLEDNE HODNOTY *********\n");
    fprintf(fPointer, "************************************\n");

    fprintf(fPointer, "\n");
    fprintf(fPointer, "Otacky hnaciho bubnu nB = %.1f ot/min \n", nB);
    fprintf(fPointer, "Prevodovy pomer prevodovky iP = %.1f (-) \n", iP);
    fprintf(fPointer, "Hmotnost nakladu mN = %.2f kg \n", mN);
    fprintf(fPointer, "Hmotnost pasu mP = %.2f kg \n", mP);
    fprintf(fPointer, "Celkovy odpor OC = %.2f = %.0f N \n",OC, OCr);
    fprintf(fPointer, "Moment na hnacim bubnu M = %.2f = %.1f N*m \n", M, Mr);
    fprintf(fPointer, "Vykon potrebny pro pohyb dopravniku P' = %.0f W \n", Pc);
    fprintf(fPointer, "Vykon  pro rozjezd P = %.0f W \n", Pm);
    #endif // LANG_CZ

    #ifdef LANG_EN
    fprintf(fPointer, "\n");
    fprintf(fPointer, "Additional values (fixed value): \n");
    fprintf(fPointer, "Gravitational acceleration, g = %.2f (m/s) \n", (float)GFORCE);
    fprintf(fPointer, "Friction coefficient [belt/sliding plate], f = %.1f (-) \n", (float)FRIC);
    fprintf(fPointer, "Starting coefficient, kr = %.1f (-) \n", (float)KR);

    fprintf(fPointer, "\n");
    fprintf(fPointer, "\n");

    fprintf(fPointer, "************************************\n");
    fprintf(fPointer, "**********  RESULT VALUES **********\n");
    fprintf(fPointer, "************************************\n");

    fprintf(fPointer, "\n");
    fprintf(fPointer, "RPM of drived pulley nB = %.1f rev/min \n", nB);
    fprintf(fPointer, "Gear ratio of transmission iP = %.1f (-) \n", iP);
    fprintf(fPointer, "Load weight mN = %.2f kg \n", mN);
    fprintf(fPointer, "Belt weight mP = %.2f kg \n", mP);
    fprintf(fPointer, "Total resistant force OC = %.2f = %.0f N \n",OC, OCr);
    fprintf(fPointer, "Drived pulley torque M = %.2f = %.1f N*m \n", M, Mr);
    fprintf(fPointer, "Power required to move the conveyor P' = %.0f W \n", Pc);
    fprintf(fPointer, "Power required for start P = %.0f W \n", Pm);
    #endif // LANG_EN


    fclose(fPointer);

    system("pause");


    return 0;
}
