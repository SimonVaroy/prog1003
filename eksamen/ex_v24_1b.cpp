/**
 *   Løsning til eksamen i OOProg (i C++), mai 2024, oppgave 1B.
 *
 *   @file     EX_V24_1B.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;


int main() {
  vector <string> txt { "GG", "SS", "KK", "BB", "FF", "TT", "AA", "PP", "EE" };
  list <string> txt2;
  int n;

  for (int i = 1;  i < txt.size();  i+=2)
      cout << txt[i] << ' ';   cout << '\n';

  txt2.push_back(txt[4]);
  for (int i = 4;  i > 0;  i--)  {
      txt2.push_back(txt[4-i]);
      txt2.push_front(txt[4+i]);
  }

  for (const auto & val : txt2)
      cout << val << ' ';      cout << '\n';

  txt2.sort();  txt2.reverse();

  auto it  = txt2.begin();
  auto it2 = txt2.rbegin();
  while (*it != *it2) {
    it++;  it2++;
  }
  cout << *it << ' ' << *it2 << '\n';

  while (txt2.front() != *it)  {
    cout << txt2.front() << ' ';
    txt2.pop_front();
  }
  cout << '\n';

  n = txt2.size();
  for (int i = 1;  i <= n;  i++)
      txt2.push_back(*it++);
  for (const auto & val : txt2)
      cout << val << ' ';      cout << '\n';

  return 0;
}




//  Utskrift:  SS BB TT PP
//             TT AA PP EE FF GG SS KK BB
//             GG GG
//             TT SS PP KK
//             GG FF EE BB AA GG FF EE BB AA
