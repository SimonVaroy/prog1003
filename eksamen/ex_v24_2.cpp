/**
 *   Løsningsforslag til eksamen i OOProg (i C++), mai 2024, oppgave 2.
 *
 *   Programmet holder orden på ulike fotballbaner en person har besøkt.
 *
 *   Programmet:
 *      - inneholder EN <map> med pekere til 'Bane'-objekter.
 *      - skriver ut ALLE banene, alle i EN by, alle med en viss kapasitet
 *        eller alle besøkt ETT gitt år
 *      - legger inn en ny bane eller et nytt besøk
 *      - frigir alt allokert minne
 *      - leser (og skriver) HELE datastrukturen fra fil
 *
 *   @file     EX_V24_2.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                //  cout, cin
#include <fstream>                 //  ifstream (ofstream)
#include <string>
#include <vector>
#include <map>
#include <algorithm>               //  sort, for_each
#include "LesData2.h"              //  Verktøykasse for lesing av diverse data
using namespace std;


const int MINKAPASITET =   1000;   ///<  Minimum kapasitet på en bane.
const int MAXKAPASITET = 120000;   ///<  Maksimum kapasitet på en bane.
const int MINAAR       =   2000;   ///<  Første år for registrering av besøk.
const int MAXAAR       =   2030;   ///<  Siste år for registrering av besøk.


/**
 *  Bane med hjemmelagets navn, hvilken by/sted den ligger, kapasitet
 *  og alle datoer som man har besøkt banen.
 */
class Bane  {
  private:
    string lag, by;
    vector <int> datoer;                   //  Hver dato er på formen:  ÅÅMMDD
    int kapasitet;
  public:
    Bane()  {  kapasitet = 0;  }                     //        (ferdiglaget)
    bool    besoktAar(const int aar) const;          //  Oppgave 2E
    string  hentBy() const         {  return by;  }  //        (ferdiglaget)
    int     hentKapasitet() const  {  return kapasitet;  } //  (ferdiglaget)
    void    lesData();                               //  Oppgave 2B
    void    lesFraFil(ifstream & inn);               //  Oppgave 2G
    void    nyttBesok();                             //  Oppgave 2C
    void    skrivData() const;                       //  Oppgave 2A
    void    skrivTilFil(ofstream & ut) const;        //  EXTRA
};


void frigiAllokertMinne();                           //  Oppgave 2F
void lesFraFil();                                    //  Oppgave 2G
void nyBane();                                       //  Oppgave 2B
void nyttBesok();                                    //  Oppgave 2C
void skrivAlleBaner();                               //  Oppgave 2A
void skrivGittAar();                                 //  Oppgave 2E
void skrivGitteUtvalgte();                           //  Oppgave 2D
void skrivMeny();                                    //     (ferdiglaget)
void skrivTilFil();                                  //  EXTRA


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

  skrivTilFil();                                     //  EXTRA

  frigiAllokertMinne();                              //  Oppgave 2F

  cout << "\n\n";
  return 0;
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV KLASSE-FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Oppgave 2E - Returnerer (true/false) til om besøkt banen et gitt år.
 *
 *  @param    aar  -  Aktuelt år å sjekke om banen er besøkt
 *  @return   True/false til om banen er besøkt i året 'aar'
 */
bool Bane::besoktAar(const int aar) const  {
  for (const auto & val : datoer)
      if (val/10000 == (aar-MINAAR)) return true;    //  Finner evt. år-match.
  return false;
}


/**
 *  Oppgave 2B - Leser inn alle data (unntatt besøk) om en bane.
 */
void Bane::lesData()  {
  kapasitet = lesInt("\tKapasitet  ", MINKAPASITET, MAXKAPASITET);
  cout << "\tLaget som spiller der:        ";   getline(cin, lag);
  cout << "\tByen/stedet er banen ligger:  ";   getline(cin, by);
}


/**
 *  Oppgave 2G - Leser inn ALLE data om EN bane fra fil.
 *
 *  @param    inn  -  Filen det leses inn fra
 */
void Bane::lesFraFil(ifstream & inn)  {
  int antallDatoer, dato;

  inn >> kapasitet;   inn.ignore();            //  Leser kapasitet, lag og by:
  getline(inn, lag);
  getline(inn, by);

  inn >> antallDatoer;                         //  Leser ALLE besøksdatoer:
  for (int i = 0;  i < antallDatoer;  i++)  {
      inn >> dato;
      datoer.push_back(dato);
  }
  inn.ignore();
}


/**
 *  Oppgave 2C - Legger inn eN ny dato for besøk på banen.
 */
void Bane::nyttBesok()  {
  int dag = lesInt("\tDag      ", 1, 31),                 //  Leser dat, måned
      mnd = lesInt("\tMaaned   ", 1, 12),                 //    og år:
      aar = lesInt("\tAar      ", MINAAR, MAXAAR);
  datoer.push_back((aar-MINAAR)*10000 + mnd*100 + dag);   //  Til rett format.
  sort(datoer.begin(), datoer.end());                     //  Sorterer.
}


/**
 *  Oppgave 2A - Skriver ut på skjermen ALLE data om banen.
 */
void Bane::skrivData() const  {
  cout << ", " << kapasitet << "  " << lag << ", " << by << "\n\t\t";
  if (datoer.size() > 0)                         //  Datoer finnes:
     for (const auto & val : datoer)             //  Dato på formen  DD/MM-ÅÅ:
         cout << val%100 << '/' << (val/100)%100 << '-' << val/10000 << "  ";
  else
     cout << "Ennaa ikke besokt denne banen.";
  cout << '\n';
}


/**
 *  EXTRA - Skriver ut på fil ALLE banens data.
 *
 *  @param    ut  -  Filen det skal skrives til
 */
void Bane::skrivTilFil(ofstream & ut) const  {
  ut << kapasitet << ' ' << lag << '\n' << by << '\n' << datoer.size();

  for (const auto & val : datoer)                //  Skriver ut ALLE datoene.
      ut << ' ' << val;
  ut << '\n';
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV ANDRE FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Oppgave 2F - Frigir/sletter ALT allokert minne/memory.
 */
void frigiAllokertMinne()  {
    for_each(gBanene.begin(), gBanene.end(),     //  Fjerner ALLE de TILPEKTE.
            [] (auto & val) {  delete val.second; } );
//  Alternativ måte når 'for_each' ikke er påkrevd:
//  for (const auto & val : gBanene)
//      delete val.second;
  gBanene.clear();                               //  Fjerner ALLE PEKERNE.
}


/**
 *  Oppgave 2G - Leser ALLE banene inn fra fil.
 *
 *  @see   Bane::lesFraFil(...)
 */
void lesFraFil()  {
  ifstream innfil("EX_V24_BANER.DTA");
  string baneNavn;
  Bane* nyBane = nullptr;

  if (innfil)  {                              //  Filen finnes:
    cout << "\n\tLeser inn fra filen 'EX_V24_BANER.DTA' .....\n\n";

    getline(innfil, baneNavn);                //  Leser evt. en banes navn.
    while (!innfil.eof())  {                  //  Ikke nådd filslutt:
      nyBane = new Bane;                      //  Oppretter ny bane.
      nyBane->lesFraFil(innfil);              //  Den leser resten selv.
      gBanene[baneNavn] = nyBane;             //  Legger inn i datastrukturen.
      getline(innfil, baneNavn);              //  Leser evt. neste banes navn.
    }
    innfil.close();                           //  Lukker filen manuelt.
  } else                                      //  Filen finnes IKKE:
    cout << "\n\n\tFant ikke filen 'EX_V24_BANER.DTA'!\n\n";
}


/**
 *  Oppgave 2B - Legger inn (om mulig) en ny bane.
 *
 *  @see   Bane::lesData()
 */
void nyBane()  {
  string baneNavn;
  Bane* nyBane = nullptr;

  cout << "\tNy banes navn: ";   getline(cin, baneNavn);
  if (gBanene.find(baneNavn) == gBanene.end()) {  //  Ny bane:
     nyBane = new Bane;                       //  Oppretter ny.
     nyBane->lesData();                       //  Får dets data lest inn.
     gBanene[baneNavn] = nyBane;              //  Legger inn i datastrukturen.
     cout << "\n\tNy bane lagt inn i datastrukturen.\n";
  } else
    cout << "\n\tDenne banen finnes fra foer!\n";
}


/**
 *  Oppgave 2C - Legger inn (om mulig) ett nytt besøk på en bane.
 *
 *  @see   Bane::nyttBesok()
 */
void nyttBesok()  {
  string baneNavn;

  if (!gBanene.empty())  {
     cout << "\n\tNytt besok paa banen: ";   getline(cin, baneNavn);
     if (gBanene.find(baneNavn) != gBanene.end())  //  Funn:
        gBanene[baneNavn]->nyttBesok();            //  Nytt besøk registreres.
     else
       cout << "\n\tIngen bane ennaa registrert med dette navnet!\n";
  } else
    cout << "\n\tForelopig ingen registrerte/lagrede baner!\n";
}


/**
 *  Oppgave 2A - Skriver ut på skjermen ALLE datene om ALLE banene.
 *
 *  @see   Bane::skrivData()
 */
void skrivAlleBaner()  {
  if (!gBanene.empty())  {
     cout << "\n\tFolgende " << gBanene.size() << " er registrert:"
          << "\n\t==========================\n";
     for (const auto & val : gBanene)  {
         cout << '\t' << val.first;            //  Skriver banens navn.
         (val.second)->skrivData();            //  Skriver resten av dataene.
     }
//  Alternativt vha. 'for_each':
//     for_each(gBanene.begin(), gBanene.end(), [] (const auto & val)
//              {  cout << '\t' << val.first; (val.second)->skrivData();  } );

//  Alternativt vha. iterator:
//     auto it = gBanene.begin();
//     while (it != gBanene.end())  {
//       cout << '\t' << (*it).first;
//       ((*it++).second)->skrivData();
//     }
  } else
    cout << "\n\tForelopig ingen registrerte/lagrede baner!\n";
}


/**
 *  Oppgave 2E - Skriver ut ALLE baner besøkt et gitt år.
 *
 *  @see   Bane::besoktAar(...)
 */
void skrivGittAar()  {
  int aar;

  if (!gBanene.empty())  {
     aar = lesInt("\tAarstall for baner besokt", MINAAR, MAXAAR);
     cout << "\n\tBaner besokt dette aaret:\n\t=========================\n";
     for (auto it = gBanene.begin();  it != gBanene.end();  it++)
         if (((*it).second)->besoktAar(aar))          //  Matchende år:
            cout << '\t' << (*it).first << '\n';      //  Skriver banens navn.
  } else
    cout << "\n\tForelopig ingen registrerte/lagrede baner!\n";
}


/**
 *  Oppgave 2D - Skriver ut ALLE baner i en gitt by eller med en viss kapasitet.
 *
 *  @see   Bane::hentBy()
 *  @see   Bane::hentKapasitet()
 */
void skrivGitteUtvalgte()  {
  string byNavn;
  int minKapasitet, kapasitet;
  char valg;
  bool funn = false;

  if (!gBanene.empty())  {
     do  {
        valg = lesChar("\tBaner i by (B) eller med en viss kapasitet (K)");
     } while (valg != 'B'  &&  valg != 'K');

     if (valg == 'B')  {    // Valg 'B':
        cout << "\tBaner i byen: ";   getline(cin, byNavn);
        cout << "\n\tBaner i denne byen:\n\t===================\n";
        for (const auto & val : gBanene)
            if ((val.second)->hentBy() == byNavn) {   //  Matchende bynavn.
               funn = true;
               cout << '\t' << val.first << '\n';     //  Skriver banens navn.
            }
     }  else  {             // Valg 'K':
        minKapasitet = lesInt("\tBanens minimumkapasitet", MINKAPASITET, MAXKAPASITET);
        cout << "\n\tBaner med minimum denne kapasiteten:"
             << "\n\t====================================\n";
        for (const auto & val : gBanene) {
            kapasitet = (val.second)->hentKapasitet();
            if (kapasitet >= minKapasitet) {          //  Matchende kapasitet.
               funn = true;              //  Skriver banens navn og kapasitet:
               cout << '\t' << val.first  << ", " << kapasitet << '\n';
            }
        }
     }
     if (!funn)
        cout << "\n\tIngen baner tilfredstilte dette kriteriet!\n";
  } else
    cout << "\n\tForelopig ingen registrerte/lagrede baner!\n";
}


/**
 *  Skriver programmets menyvalg/muligheter på skjermen.
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


/**
 *  EXTRA - Skriver ALLE banene ut til fil.
 *
 *  @see   Bane::skrivTilFil(...)
 */
void skrivTilFil()  {
  ofstream utfil("EX_V24_BANER.DT2");

  cout << "\n\tSkriver alle data til filen 'EX_V24_BANER.DT2' .....\n";

  for (const auto & val : gBanene)  {          //  Hver bane skriver selv:
      utfil << val.first << '\n';
      (val.second)->skrivTilFil(utfil);
  }
  utfil.close();                               //  Lukker filen manuelt.
}
