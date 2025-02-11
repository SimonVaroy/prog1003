#include "LesData2.h"
#include <iostream>
#include <vector>
using namespace std;

// Struct som representerer en oppgave
struct Oppgave {
  string beskrivelse; // Beskrivelse av oppgaven
  string ansvarlig;   // Person som er ansvarlig for oppgaven
  bool erFullfort;    // Om oppgaven er fullført eller ikke
};

// Global vektor som lagrer alle oppgavene
vector<Oppgave *> gAntallOppgaver;

// Funksjonsdeklarasjoner (alfabetisk rekkefølge)
void fjernAlleOppgaver();
void fjernOppgave();
void nyOppgave();
void oppgaveEndreStatus();
void oppgaveEndreStatus(Oppgave &oppgave);
void oppgaveLesData(Oppgave &oppgave);
void oppgaveSkrivData(const Oppgave *oppgave);
void skrivAlleOppgaver();
void skrivMeny();
void skrivOppgave();

/**
 * @brief Fjerner alle oppgaver fra den globale vektoren og frigjør minnet.
 */
void fjernAlleOppgaver() {
  for (int i = 0; i < gAntallOppgaver.size(); i++) {
    delete gAntallOppgaver[i]; // Slett hver oppgave
  }
  gAntallOppgaver.clear(); // Tøm vektoren
}

/**
 * @brief Fjerner en spesifikk oppgave fra den globale vektoren og frigjør
 * minnet.
 * @see lesInt
 */
void fjernOppgave() {
  int nr = lesInt("\tFjerne bok nr", 1,
                  gAntallOppgaver.size()); // Hent oppgavenummer
  delete gAntallOppgaver[nr - 1];          // Slett oppgaven
  gAntallOppgaver[nr - 1] =
      gAntallOppgaver[gAntallOppgaver.size() -
                      1];     // Flytt siste oppgave til denne plassen
  gAntallOppgaver.pop_back(); // Fjern den siste pekeren
}

/**
 * @brief Oppretter en ny oppgave og legger den til i den globale vektoren.
 * @see lesChar
 */
void nyOppgave() {
  Oppgave *nyOppgave = new Oppgave;
  cout << "\nNy oppgave:\n";
  oppgaveLesData(*nyOppgave);           // Les oppgavedata
  gAntallOppgaver.push_back(nyOppgave); // Legg til oppgaven i vektoren
  cout << "\n\tNy oppgave innlagt har nr." << gAntallOppgaver.size() << '\n';
}

/**
 * @brief Endrer fullføringsstatusen til en spesifikk oppgave.
 * @see lesInt
 */
void oppgaveEndreStatus() {
  int nr = lesInt("Endre status på oppgave nr", 1,
                  gAntallOppgaver.size()); // Hent oppgavenummer
  gAntallOppgaver[nr - 1]->erFullfort =
      !gAntallOppgaver[nr - 1]->erFullfort; // Bytt status
}

/**
 * @brief Endrer fullføringsstatusen til en gitt oppgave.
 * @param oppgave Oppgaven som skal endres.
 */
void oppgaveEndreStatus(Oppgave &oppgave) {
  oppgave.erFullfort = !oppgave.erFullfort; // Bytt status
}

/**
 * @brief Leser data for en oppgave fra brukeren.
 * @param oppgave Oppgaven som skal fylles med data.
 * @see lesChar
 */
void oppgaveLesData(Oppgave &oppgave) {
  cout << "\tBeskrivelse: ";
  getline(cin, oppgave.beskrivelse);
  cout << "\tAnsvarlig: ";
  getline(cin, oppgave.ansvarlig);
  char erFullfortChar =
      lesChar("Er oppgaven fullført? (j/n)");   // Les fullføringsstatus
  oppgave.erFullfort = (erFullfortChar == 'J'); // Sett status
}

/**
 * @brief Skriver ut detaljene for en spesifikk oppgave.
 * @param oppgave Oppgaven som skal skrives ut.
 */
void oppgaveSkrivData(const Oppgave *oppgave) {
  cout << "\t\t\"" << oppgave->beskrivelse << "\" av " << oppgave->ansvarlig
       << ((!oppgave->erFullfort) ? " IKKE " : " ") << "fullført\n";
}

/**
 * @brief Skriver ut alle oppgavene i den globale vektoren.
 */
void skrivAlleOppgaver() {
  for (int i = 0; i < gAntallOppgaver.size(); i++) {
    cout << "\tOppgave nr." << setw(2) << i + 1 << ":\n";
    oppgaveSkrivData(gAntallOppgaver[i]); // Skriv ut hver oppgave
  }
}

/**
 * @brief Skriver ut hovedmenyen med tilgjengelige kommandoer.
 */
void skrivMeny() {
  cout << "Ny oppgave (N)" << endl
       << "Skriv alle oppgaver (S)" << endl
       << "Endre status på oppgave (E)" << endl
       << "Avslutt programmet (Q)" << endl;
}

/**
 * @brief Skriver ut en spesifikk oppgave basert på brukerinput.
 * @see lesInt
 */
void skrivOppgave() {
  int nr = lesInt("\tSe oppgave nr", 1,
                  gAntallOppgaver.size());   // Hent oppgavenummer
  oppgaveSkrivData(gAntallOppgaver[nr - 1]); // Skriv ut oppgaven
}

int main() {
  char kommando;

  skrivMeny();
  kommando = lesChar("\nKommando");

  while (kommando != 'Q') {
    switch (kommando) {
    case 'N':
      nyOppgave();
      break;
    case 'S':
      skrivAlleOppgaver();
      break;
    case 'E':
      oppgaveEndreStatus();
      break;
    }
    kommando = lesChar("\nKommando");
  }

  fjernAlleOppgaver(); // Rydd opp i minnet før avslutning
  return 0;
}
