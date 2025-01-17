/**
 *   Skjelett for eksamen i OOProg (i C++), mai 2024, oppgave 2.
 *
 *   Programmet holder orden p� ulike fotballbaner en person har bes�kt.
 *
 *   Programmet:
 *      - inneholder EN <map> med pekere til 'Bane'-objekter.
 *      - skriver ut ALLE banene, alle i EN by, alle med en viss kapasitet
 //       eller alle bes�kt ETT gitt �r
 *      - legger inn en ny bane eller et nytt bes�k
 *      - frigir alt allokert minne
 *      - leser (og skriver) HELE datastrukturen fra fil
 *
 *   @file     EX_V24_2.TPL
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                //  cout, cin
#include <fstream>                 //  ifstream (ofstream)
#include <string>
#include <vector>
#include <map>
#include <algorithm>               //  sort, for_each
#include "LesData2.h"              //  Verkt�ykasse for lesing av diverse data
using namespace std;


const int MINKAPASITET =   1000;   ///<  Minimum kapasitet p� en bane.
const int MAXKAPASITET = 120000;   ///<  Maksimum kapasitet p� en bane.
const int MINAAR       =   2000;   ///<  F�rste �r for registrering av bes�k.
const int MAXAAR       =   2030;   ///<  Siste �r for registrering av bes�k.


/**
 *  Bane med hjemmelagets navn, hvilken by/sted den ligger, kapasitet
 *  og alle datoer som man har bes�kt banen.
 */
class Bane  {
  private:
    string lag, by;
    vector <int> datoer;                   //  Hver dato er p� formen:  ��MMDD
    int kapasitet;
  public:
    Bane()  {  kapasitet = 0;  }                     //        (ferdiglaget)
    string  hentBy() const         {  return by;  }  //        (ferdiglaget)
    int     hentKapasitet() const  {  return kapasitet;  } //  (ferdiglaget)
    void    lesData();                               //  Oppgave 2B
    void    lesFraFil(ifstream & inn);               //  Oppgave 2G
    void    nyttBesok();                             //  Oppgave 2C
    void    skrivData() const;                       //  Oppgave 2A
};


void frigiAllokertMinne();                           //  Oppgave 2F
void lesFraFil();                                    //  Oppgave 2G
void nyBane();                                       //  Oppgave 2B
void nyttBesok();                                    //  Oppgave 2C
void skrivAlleBaner();                               //  Oppgave 2A
void skrivGittAar();                                 //  Oppgave 2E
void skrivGitteUtvalgte();                           //  Oppgave 2D
void skrivMeny();                                    //     (ferdiglaget)


map <string, Bane*> gBanene;       ///<  Datastrukturen med ALLE banene.


/**
 *  Hovedprogrammet.
 */
int main() {
  char valg;

  lesFraFil();                                       //  Oppgave 2G

  skrivMeny();
  valg = lesChar("\nKommando");

  while (valg != 'Q') {
     switch (valg) {
       case 'S': skrivAlleBaner();       break;      //  Oppgave 2A
       case 'N': nyBane();               break;      //  Oppgave 2B
       case 'B': nyttBesok();            break;      //  Oppgave 2C
       case 'U': skrivGitteUtvalgte();   break;      //  Oppgave 2D
       case 'A': skrivGittAar();         break;      //  Oppgave 2E
       default:  skrivMeny();            break;
     }
     valg = lesChar("\nKommando");
  }

  frigiAllokertMinne();                              //  Oppgave 2F

  cout << "\n\n";
  return 0;
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV KLASSE-FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Oppgave 2B - Leser inn alle data (unntatt bes�k) om en bane.
 */
void Bane::lesData()  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2G - Leser inn ALLE data om EN bane fra fil.
 *
 *  @param    inn  -  Filen det leses inn fra
 */
void Bane::lesFraFil(ifstream & inn)  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2C - Legger inn eN ny dato for bes�k p� banen.
 */
void Bane::nyttBesok()  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2A - Skriver ut p� skjermen ALLE data om banen.
 */
void Bane::skrivData() const  {

	//   LAG INNMATEN
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV ANDRE FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Oppgave 2F - Frigir/sletter ALT allokert minne/memory.
 */
void frigiAllokertMinne()  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2G - Leser ALLE banene inn fra fil.
 */
void lesFraFil()  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2B - Legger inn (om mulig) en ny bane.
 */
void nyBane()  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2C - Legger inn (om mulig) ett nytt bes�k p� en bane.
 */
void nyttBesok()  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2A - Skriver ut p� skjermen ALLE datene om ALLE banene.
 */
void skrivAlleBaner()  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2E - Skriver ut ALLE baner bes�kt et gitt �r.
 */
void skrivGittAar()  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2D - Skriver ut ALLE baner i en gitt by eller med en viss kapasitet.
 */
void skrivGitteUtvalgte()  {

	//   LAG INNMATEN
}


/**
 *  Skriver programmets menyvalg/muligheter p� skjermen.
 */
void skrivMeny()  {
  cout << "\nFolgende kommandoer er tilgjengelige:\n"
       << "   S  - Skriv alle baner\n"
       << "   N  - Ny bane\n"
       << "   B  - nytt besok paa en bane\n"
       << "   U  - skriv gitte Utvalgte byer eller kapasiteter\n"
       << "   A  - skriv alle banebesok ett gitt Aar\n"
       << "   Q  - Quit / avslutt\n";
}
