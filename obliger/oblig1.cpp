#include <iostream>
#include <vector>
using namespace std;

struct Oppgave {
  string beskrivelse, // Hva oppgaven er.
      ansvarlig;      // Hvem som skal gjøre den.
  bool erFullfort;    // Om oppgaven er gjort eller ei.
};

vector<Oppgave *> gAntallOppgaver;

void skrivMeny() {
  cout << "Ny oppgave" << endl
       << "Fjern alle oppgaver" << endl
       << "Endre status på oppgave" << endl
       << "Les data på oppgave" << endl
       << "Skriv data på oppgave" << endl
       << "Skriv alle oppgaver" << endl
       << "Skriv meny" << endl;
}

void oppgaveLesData(Oppgave &oppgave) {
  string erFullfortString;
  cout << "\tBeskrivelse:     ";
  getline(cin, oppgave.beskrivelse);
  cout << "\tAnsvarlig:  ";
  getline(cin, oppgave.ansvarlig);
  cout << "Er oppgaven fullført?";
  cin >> erFullfortString;
  if (erFullfortString == "Ja" || erFullfortString == "ja" ||
      erFullfortString == "j") {
    oppgave.erFullfort = true;
  } else {
    oppgave.erFullfort = false;
  }
}

void nyOppgave() {
  Oppgave *nyOppgave = new Oppgave;
  cout << "\nNy oppgave:\n";
  oppgaveLesData(*nyOppgave);
  gAntallOppgaver.push_back(nyOppgave);
  cout << "\n\tNy oppgave innlagt har nr." << gAntallOppgaver.size() << '\n';
}

void fjernAlleOppgaver() {
  for (int i = 0; i < gAntallOppgaver.size();
       i++) // Sletter ALLE bøkene/struct'ene:
    delete gAntallOppgaver[i];
  gAntallOppgaver.clear(); //  Fjerner ALLE PEKERNE i vectoren.
}

int main() {
  skrivMeny();
  nyOppgave();
  return 0;
}
