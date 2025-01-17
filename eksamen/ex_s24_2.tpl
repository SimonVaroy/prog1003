/**
 *   Skjelett for eksamen i OOProg (i C++), august 2024, oppgave 2.
 *
 *   Programmet holder orden på ulike biler og bobiler,
 *     og hvilke byer disse har vært i.
 *
 *   Programmet:
 *      - inneholder EN <list> med pekere til 'Bil/Bobil'-objekter.
 *      - skriver ut hoveddatene om ALLE (bo)bilene, ALT om EN (bo)bil
 *      - legger inn en ny (bo)bil eller besøkte byer
 *      - skriver de fem mest besøkte byene
 *      - skriver og leser HELE datastrukturen til/fra fil
 *
 *   @file     EX_S24_2.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                //  cout, cin
#include <fstream>                 //  ifstream, ofstream
#include <string>
#include <vector>
#include <list>
#include <algorithm>               //  find_if
#include "LesData2.h"              //  Verktøykasse for lesing av diverse data
using namespace std;

const int MINPERS  =    2;         ///<  Bil minimum antall personer.
const int MAXPERS  =    8;         ///<  Bil maksimum antall personer.
const int MINLEN   =  4.0;         ///<  Bobils minimumslengde.
const int MAXLEN   = 10.0;         ///<  Bobils maksimumslengde.


/**
 *  Bil med dets registreringsnummer, merke/type (f eks Audi Q4) og
 *    antall personer det er plass til i bo(bilen), samt vector med navnet
 *    på besøkte byer og vector med antall besøk i aktuell by.
 */
class Bil  {
  private:
    string regnr,
           merke;
    int antallPersoner;
    vector <string> bynavn;
    vector <int>    antallBesok;
  public:
    Bil(string rnr)  { regnr = rnr;  antallPersoner = 0; } //    (Ferdiglaget)
    Bil(ifstream & inn);                                   //  Oppgave 2G
    void bybesok();                                        //  Oppgave 2D
    string hentID()    { return  regnr;  }                 //    (Ferdiglaget)
    virtual void lesData();                                //  Oppgave 2C
            void skrivData()   const;                      //  Oppgave 2A
    virtual void skrivData2()  const;                      //  Oppgave 2B
    virtual void skrivTilFil(ofstream & ut) const;         //  Oppgave 2F
            void skrivTilFil2(ofstream & ut) const;        //  Oppgave 2F
};


/**
 *  Avledet klasse 'Bobil' med bobilens lengde og antall sengeplasser.
 */
class Bobil : public Bil  {
  private:
    float lengde;
    int   antallSengeplasser;
  public:                                                  //   (Ferdiglaget):
    Bobil(string rnr) : Bil(rnr)  {  lengde = 0.0;  antallSengeplasser = 0;  }
    Bobil(ifstream & inn);                                 //  Oppgave 2G
    virtual void lesData();                                //  Oppgave 2C
    virtual void skrivData2()  const;                      //  Oppgave 2B
    virtual void skrivTilFil(ofstream & ut) const;         //  Oppgave 2F
};


void byBesok();                                            //  Oppgave 2D
Bil* finnEnGittBil(string regnr);                          //    (Ferdiglaget)
void lesFraFil();                                          //  Oppgave 2G
void nyBil();                                              //  Oppgave 2C
void skrivAlleBiler();                                     //  Oppgave 2A
void skrivEnGittBil();                                     //  Oppgave 2B
void skrivMeny();                                          //    (Ferdiglaget)
void skrivTilFil();                                        //  Oppgave 2F
void skrivTotaltAntallBybesok();                           //  Oppgave 2E


list <Bil*> gBilene;                  ///<  Datastrukturen med ALLE bilene.


/**
 *  Hovedprogrammet.
 */
int main() {
  char valg;

  lesFraFil();                                             //  Oppgave 2G

  skrivMeny();
  valg = lesChar("\nKommando");

  while (valg != 'Q') {
     switch (valg) {
       case 'A': skrivAlleBiler();             break;      //  Oppgave 2A
       case 'G': skrivEnGittBil();             break;      //  Oppgave 2B
       case 'N': nyBil();                      break;      //  Oppgave 2C
       case 'B': byBesok();                    break;      //  Oppgave 2D
       case 'T': skrivTotaltAntallBybesok();   break;      //  Oppgave 2E
       default:  skrivMeny();                  break;
     }
     valg = lesChar("\nKommando");
  }

  skrivTilFil();                                           //  Oppgave 2F

  cout << "\n\n";
  return 0;
}

// ---------------------------------------------------------------------------
//                       DEFINISJON AV KLASSE-FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Oppgave 2G - Leser inn ALLE data om EN bil fra fil.
 *
 *  @param    inn  -  Filen det leses inn fra
 */
Bil::Bil(ifstream & inn)  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2D - Leser inn null eller flere (nye) besøkte byer av bilen..
 *
 *  @see   Bil::skrivData2()
 */
void Bil::bybesok()  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2C - Leser inn ALT om en bil (unntatt besøkte byer).
 */
void Bil::lesData()  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2A - Skriver ut på skjermen noen utvalgte HOVEDdata.
 */
void Bil::skrivData()   const  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2B - Skriver ALT om en bil ut på skjermen.
 */
void Bil::skrivData2()  const  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2F - Skriver ut på fil ALLE bilens data.
 *
 *  @param    ut  -  Filen det skal skrives til
 *  @see      Bil::skrivTilFil(...)
 */
void Bil::skrivTilFil(ofstream & ut) const  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2F - Skriver ut på fil ALLE bilens data.
 *
 *  @param    ut  -  Filen det skal skrives til
 */
void Bil::skrivTilFil2(ofstream & ut) const  {

	//   LAG INNMATEN
}

// ---------------------------------------------------------------------------

/**
 *  Oppgave 2G - Leser inn ALLE data om en bobil fra fil.
 *
 *  @param   inn  -  Filen det leses inn fra
 *  @see     Bil::Bil(...)
 */
Bobil::Bobil(ifstream & inn) : Bil(inn)  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2C - Leser inn ALT om en bobil.
 *
 *  @see     Bil::lesData()
 */
void Bobil::lesData()  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2B - Skriver ALT om en bobil ut på skjermen.
 *
 *  @see     Bil::skrivData2()
 */
void Bobil::skrivData2()  const  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2F - Skriver ut på fil ALLE bobilens data.
 *
 *  @param    ut  -  Filen det skal skrives til
 *  @see      Bil::skrivTilFil(...)
 */
void Bobil::skrivTilFil(ofstream & ut) const  {

	//   LAG INNMATEN
}

// ---------------------------------------------------------------------------
//                       DEFINISJON AV ANDRE FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Oppgave 2D - Legger inn nye bybesøk for en gitt bil.
 *
 *  @see   finnEnGittBil(...)
 *  @see   Bil::bybesok()
 */
void byBesok()  {

	//   LAG INNMATEN
}


/**
 *  Returnerer (om mulig) en peker til bil med ønsket regnr.
 *
 *  @param    regnr  -  Regnr det skal letes/søkes etter
 *  @return   Peker til søkt bil eller 'nullptr'
 *  @see      Bil::hentID()
 */
Bil* finnEnGittBil(string regnr)  {              //  Leter etter en gitt bil:
  auto it = find_if(gBilene.begin(), gBilene.end(),[regnr] (const auto & val)
                                     { return (val->hentID()  == regnr);  } );
  return ((it != gBilene.end()) ? *it : nullptr); //  Returnerer peker til
}                                                 //    bilen eller 'nullptr'.


/**
 *  Oppgave 2G - Leser ALLE bilene inn fra fil.
 *
 *  @see   Bil::Bil(...)
 *  @see   Bobil::Bobil(...)
 */
void lesFraFil()  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2C - Legger (om mulig) inn en ny (bo)bil i datastrukturen.
 *
 *  @see   finnEnGittBil(...)
 *  @see   Bil::Bil(...)
 *  @see   Bobil::Bobil(...)
 */
void nyBil()  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2A - Skriver ut på skjermen hoveddatene om ALLE bilene.
 *
 *  @see   Bil::skrivData()
 */
void skrivAlleBiler()  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2B - Skriver ut på skjermen ALLE data om en GITT bil.
 *
 *  @see   finnEnGittBil(...)
 *  @see   Bil::skrivData2()
 *  @see   Bobil::skrivData2()
 */
void skrivEnGittBil()  {

	//   LAG INNMATEN
}


/**
 *  Skriver programmets menyvalg/muligheter på skjermen.
 */
void skrivMeny()  {
  cout << "\nFolgende kommandoer er tilgjengelige:\n"
       << "   A  - skriv Alle biler\n"
       << "   G  - skriv alt om en Gitt bil\n"
       << "   N  - ny (bo)bil\n"
       << "   B  - (ny) By er besokt\n"
       << "   T  - skriver Totalt antall besok i hver by\n"
       << "   Q  - Quit / avslutt\n";
}


/**
 *  Oppgave 2F - Skriver ALLE bilene ut til fil.
 *
 *  @see   Bil::skrivTilFil(...)
 *  @see   Bobil::skrivTilFil(...)
 */
void skrivTilFil()  {

	//   LAG INNMATEN
}


/**
 *  Oppgave 2E - Skriver ALLE byene og TOTALT antall besøk i hver av dem.
 *
 *  @see   Bil::hentByer(...)
 */
void skrivTotaltAntallBybesok() {

	//   LAG INNMATEN
}
