/**
 *   Løsningsforslag til eksamen i OOProg (i C++), august 2024, oppgave 2.
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
#include <iomanip>                 //  setw, left, right
#include <fstream>                 //  ifstream, ofstream
#include <string>
#include <vector>
#include <list>
#include <algorithm>               //  for_each, find_if, sort, unique, count
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
    void hentByer(vector <string> & byer) const;           //  Oppgave 2E
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
  string txt;
  int antall, ant;
  inn >> antallPersoner >> regnr;  inn.ignore();   //  Leser tre første
  getline(inn, merke);                             //    datamedlemmer.
  inn >> antall;                               //  Leser antall som nå kommer.
  for (int i = 0;  i < antall;  i++)  {        //  Leser bynavnene og antall
      inn >> txt >> ant;                       //    besøk i hver av dem:
      bynavn.push_back(txt);                   //  Legger alt dette inn i de
      antallBesok.push_back(ant);              //    to vectorene.
  }
  inn.ignore();
}


/**
 *  Oppgave 2D - Leser inn null eller flere (nye) besøkte byer av bilen..
 *
 *  @see   Bil::skrivData2()
 */
void Bil::bybesok()  {
  string navn;
  int i;

  skrivData2();                               //  Skriver initiell status.
  cout << "\n\tBesokt byen (kun ENTER = slutt): ";  getline(cin, navn);
  while (navn.length() > 0)  {                //  Ennå ikke kun 'ENTER':
    for (i = 0;  i < bynavn.size();  i++)     //  Leter etter navnet:
        if (bynavn[i] == navn) break;         //  Funn!
    if (i < bynavn.size()) antallBesok[i]++;  //  Finnes:  Øker kun antallet.
    else {                                    //  Ny:
       bynavn.push_back(navn);                //  Legger både navn og antall
       antallBesok.push_back(1);              //    ganger bakerst i hver
    }                                         //    sin vector.
    cout << "\tBesokt byen (kun ENTER = slutt): ";  getline(cin, navn);
  }
  skrivData2();                               //  Skriver avsluttende status.
}


/**
 *  Oppgave 2E - Oppdaterer medsendt vector med ALLE byene som er besøkt
 **              av bilen  Bynavnene blir duplisert ut fra antall besøk.
 *
 *  @param   byer  -  Referanseoverført vector med ALLE bybesøkene for bilen
 */
void Bil::hentByer(vector <string> & byer) const  {
  for (int i = 0;  i < bynavn.size();  i++)      // Går igjennom ALLE byene:
      for (int j = 0;  j < antallBesok[i];  j++) // Hver dupliseres (og legges)
          byer.push_back(bynavn[i]);             //  bakerst det antall ganger
}                                                //  den er besøkt.


/**
 *  Oppgave 2C - Leser inn ALT om en bil (unntatt besøkte byer).
 */
void Bil::lesData()  {
  cout << "\tMerke:\t\t\t";  getline(cin, merke);
  antallPersoner = lesInt("\tSitteplasser ", MINPERS, MAXPERS);
}


/**
 *  Oppgave 2A - Skriver ut på skjermen noen utvalgte HOVEDdata.
 */
void Bil::skrivData()   const  {
  cout << '\t' << regnr << ", " << left << setw(25) << merke << right
       << "Antall ulike byer besokt: " << bynavn.size() << " stk\n";
}


/**
 *  Oppgave 2B - Skriver ALT om en bil ut på skjermen.
 */
void Bil::skrivData2()  const  {
  cout << "\n\tMerke: " << merke
       << "    Antall sitteplasser: " << antallPersoner << "\n\n\t";
  if (!bynavn.empty())  {
     cout << "Har besokt folgende " << bynavn.size() << " byer:\n";
     for (int i = 0;  i < bynavn.size();  i++)    //  Skriver alle bybesøkene:
         cout << "\t\t" << left << setw(20) << bynavn[i] << right
              << setw(5) << antallBesok[i] << " gang(er)\n";
  } else
     cout << "Har ennaa ikke besokt noen byer.\n";
}


/**
 *  Oppgave 2F - Skriver ut på fil ALLE bilens data.
 *
 *  @param    ut  -  Filen det skal skrives til
 *  @see      Bil::skrivTilFil(...)
 */
void Bil::skrivTilFil(ofstream & ut) const  {
  ut << "I ";                                 //  Skriver at er BIL.
  skrivTilFil2(ut);                           //  Skriver resten av egne data.
}


/**
 *  Oppgave 2F - Skriver ut på fil ALLE bilens data.
 *
 *  @param    ut  -  Filen det skal skrives til
 */
void Bil::skrivTilFil2(ofstream & ut) const  {
 ut << antallPersoner << ' ' << regnr << '\n'  //  Skriver første tre data:
    << merke << '\n' << bynavn.size();
 for (int i = 0;  i < bynavn.size();  i++)     //  Skriver alle byer og antall
     ut << ' ' << bynavn[i] << ' ' << antallBesok[i]; //  besøk i hver av dem.
 ut << '\n';
}

// ---------------------------------------------------------------------------

/**
 *  Oppgave 2G - Leser inn ALLE data om en bobil fra fil.
 *
 *  @param   inn  -  Filen det leses inn fra
 *  @see     Bil::Bil(...)
 */
Bobil::Bobil(ifstream & inn) : Bil(inn)  {
  inn >> lengde >> antallSengeplasser;  inn.ignore();
}


/**
 *  Oppgave 2C - Leser inn ALT om en bobil.
 *
 *  @see     Bil::lesData()
 */
void Bobil::lesData()  {
  Bil::lesData();
  lengde = lesFloat("\tLengde", MINLEN, MAXLEN);
  antallSengeplasser = lesInt("\tSengeplasser ", MINPERS, MAXPERS);
}


/**
 *  Oppgave 2B - Skriver ALT om en bobil ut på skjermen.
 *
 *  @see     Bil::skrivData2()
 */
void Bobil::skrivData2()  const  {
  cout << "\n\tBOBIL:\n" << "\t\tLengde: " << lengde
       << "    sengeplasser: " << antallSengeplasser << '\n';
  Bil::skrivData2();
}


/**
 *  Oppgave 2F - Skriver ut på fil ALLE bobilens data.
 *
 *  @param    ut  -  Filen det skal skrives til
 *  @see      Bil::skrivTilFil(...)
 */
void Bobil::skrivTilFil(ofstream & ut) const  {
  ut << "O ";                                      //  Skriver at er BOBIL.
  skrivTilFil2(ut);                                //  Alle mors data skrives.
  ut << lengde << ' ' << antallSengeplasser << '\n';  //  Skriver egne data.
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
  Bil* bil = nullptr;
  string regnr;
  if (!gBilene.empty())  {                   //  Biler er registrert:
     cout << "\tRegnr som har besokt by(er):  ";  getline(cin, regnr);
     bil = finnEnGittBil(regnr);             //  Aktuell bil finnes:
     if (bil)
        bil->bybesok();                      //  Bybesøk registreres.
     else
       cout << "\n\tIngen (bo)biler med dette registreringsnummeret!\n";
  } else
    cout << "\n\tForelopig ingen registrerte/lagrede biler!\n";
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
  ifstream innfil("EX_S24_BILER.DTA");
  char type;
  int antallBiler;

  if (innfil)  {                                  //  Filen finnes:
    cout << "\n\tLeser inn fra filen 'EX_S24_BILER.DTA' .....\n\n";
    innfil >> antallBiler;   innfil.ignore();
    for (int i = 0;  i < antallBiler;  i++)  {
        innfil >> type;   innfil.ignore();        //  Leser objekt-type.
        switch (type)  {                          //  Oprretter og legger inn:
          case 'I':  gBilene.push_back(new Bil(innfil));     break;
          case 'O':  gBilene.push_back(new Bobil(innfil));   break;
          default:   cout << "\n\tUkjent objekt-type!\n";    break;
        }
    }
    innfil.close();                               //  Lukker filen manuelt.
  } else                                          //  Filen finnes IKKE:
    cout << "\n\n\tFant ikke filen 'EX_S24_BILER.DTA'!\n\n";
}


/**
 *  Oppgave 2C - Legger (om mulig) inn en ny (bo)bil i datastrukturen.
 *
 *  @see   finnEnGittBil(...)
 *  @see   Bil::Bil(...)
 *  @see   Bobil::Bobil(...)
 */
void nyBil()  {
  Bil* nyBil = nullptr;
  char type;
  string regnr;

  cout << "\tNY bil sitt regnr:  ";    getline(cin, regnr);
  if (!finnEnGittBil(regnr))  {              //  Biler er IKKE registrert:
     do  {                                   //  Leser ønsket objekt-type:
       type = lesChar("\tBil eller bobil ('I'/'O')");
     } while (type != 'I'  &&  type != 'O');

     switch (type)  {                        //  Oppretter aktuelt objekt:
       case 'I':  nyBil = new Bil(regnr);     break;
       case 'O':  nyBil = new Bobil(regnr);   break;
     }
     nyBil->lesData();                       //  Leser inn dets datamedlemmer.
     gBilene.push_back(nyBil);               //  Legger inn i datastrukturen.
     gBilene.sort([] (const auto & b1, const auto & b2)   //  Sorterer på nr.
                     {  return (b1->hentID() < b2->hentID()); } );
  } else
     cout << "\n\tFinnes allerede en bil med dette registreringsnummeret!\n";
}


/**
 *  Oppgave 2A - Skriver ut på skjermen hoveddatene om ALLE bilene.
 *
 *  @see   Bil::skrivData()
 */
void skrivAlleBiler()  {
  if (!gBilene.empty())  {                   //  Biler er registrert:
     cout << "\n\tFolgende " << gBilene.size() << " biler er registrert:"
          << "\n\t===============================\n";
     for (const auto & val : gBilene)
         val->skrivData();      //  Skriver bilenes HOVEDdata.

//  Alternativt vha. 'for_each':
//     for_each(gBilene.begin(), gBilene.end(),
//                      [] (const auto & val) {  val->skrivData();  } );

//  Alternativt vha. iterator:
//     auto it = gBilene.begin();
//     while (it != gBilene.end())
//       (*it++)->skrivData();
  } else
    cout << "\n\tForelopig ingen registrerte/lagrede biler!\n";
}


/**
 *  Oppgave 2B - Skriver ut på skjermen ALLE data om en GITT bil.
 *
 *  @see   finnEnGittBil(...)
 *  @see   Bil::skrivData2()
 *  @see   Bobil::skrivData2()
 */
void skrivEnGittBil()  {
  Bil* bil = nullptr;
  string regnr;
  if (!gBilene.empty())  {                   //  Biler er registrert:
     cout << "\tALT om regnr:  ";    getline(cin, regnr);
     bil = finnEnGittBil(regnr);             //  Prøver å finne bil med regnr.
     if (bil)                                //  Funn:
        bil->skrivData2();                   //  Får dets data skrevet.
     else
       cout << "\n\tIngen (bo)biler med dette registreringsnummeret!\n";
  } else
    cout << "\n\tForelopig ingen registrerte/lagrede biler!\n";
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
  ofstream utfil("EX_S24_BILER.DT2");

  cout << "\n\tSkriver alle data til filen 'EX_S24_BILER.DT2' .....\n";
  utfil << gBilene.size() << '\n';
  for (const auto & val : gBilene)
      val->skrivTilFil(utfil);              //  Hver (bo)bil skriver seg selv.

//  Alternativt vha. iterator:
//     auto it = gBilene.begin();
//     while (it != gBilene.end())
//       (*it++)->skrivTilFil(utfil);
  utfil.close();                            //  Lukker filen manuelt.
}


/**
 *  Oppgave 2E - Skriver ALLE byene og TOTALT antall besøk i hver av dem.
 *
 *  @see   Bil::hentByer(...)
 */
void skrivTotaltAntallBybesok() {
  vector <string> byene;    //  Vector med ALLE byene, også dupliserte navn.
  vector <string> kopi;     //  Initielt kopi av den ovenfor, før den sorteres
                            //    og gjøres 'unique' (INGEN dupliserte byer).
  for (const auto & val : gBilene)   //  Samler inn ALLE byene fra bilene,
      val->hentByer(byene);          //    også MASSE dupliserte bynavn.

  kopi = byene;                                //  Tar kopi av det innsamlede,
  sort(kopi.begin(), kopi.end());              //    sorterer det, og lager
  auto it = unique(kopi.begin(), kopi.end());  //    alle bynavnene unike.
                                     //  'it' er 'end' i den unike mengden!
  cout << "\n\tTOTALT antall besok i hver av byene:\n";
  auto it2 = kopi.begin();           //  Går igjennom alle de UNIKE bynavnene:
  while (it2 != it)  {               //  Skriver bynavn og ANTALLET av hver:
    cout << "\t\t" << left << setw(20) << *it2 << ':' << right
         << setw(5) << count(byene.begin(), byene.end(), *it2) << " stk\n";
    it2++;
  }
}
