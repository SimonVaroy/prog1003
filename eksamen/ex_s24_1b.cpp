/**
 *   Løsning til eksamen i OOProg (i C++), august 2024, oppgave 1B.
 *
 *   @file     EX_S24_1B.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;


void skriv(map <int, string> & m)  {
  for (const auto & val : m)
      cout << val.first << ':' << val.second << "  ";    cout << '\n';
}


int main() {
  vector <string> txt { "AA", "LL", "NN", "SS", "RR", "EE", "AA" };
  map <int, string> mapen;

  for (int i = txt.size()-1;  i >= 0;   i--)
      mapen[i*3] = txt[i];

  skriv(mapen);

  auto it = mapen.begin();
  mapen.erase(++it);
  skriv(mapen);

  auto it2 = mapen.rbegin();
  for (int i = 0;  i < 4;  i++)  it2++;
  while (it2 != mapen.rend()) cout << (it2++)->first << ' ';   cout << '\n';


  it  = mapen.lower_bound(6);
  auto it3 = mapen.upper_bound(15);

  cout << it3->first << '\n';

  for (  ;  it != it3;  )
      cout << (it++)->first << ' ';   cout << '\n';


  return 0;
}




//  Utskrift:  0:AA  3:LL  6:NN  9:SS  12:RR  15:EE  18:AA
//             0:AA  6:NN  9:SS  12:RR  15:EE  18:AA
//             6 0
//             18
//             6 9 12 15
