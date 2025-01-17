/**
 *   Løsning til eksamen i OOProg (i C++), mai 2024, oppgave 1A.
 *
 *   @file     EX_V24_1A.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>
#include <string>     //  'find' skriver evt. startindeksen for tekstmatch
using namespace std;

//  NB: string::npos    betyr "ikke funnet", det samme som en iterators end()

class A  {
  protected:
     string navn, adresse;
  public:
     A()  {  }
     A(const string n, const string a)  {  navn = n;  adresse = a;  }
     virtual void display() const = 0;
     void funk1(const char c)  {    int n;
       while ((n = adresse.find(c, 0)) != string::npos) adresse[n] = 't'; }
     bool funk2()  {  return (navn.substr(1, 5) == adresse.substr(1, 5));  }
};


class B : public A {
  private:
    float hoyde;
  public:
    B(const string n, const string a, const float h) : A(n, a)  { hoyde = h; }
    B(const B & b)       { navn = (b.navn + " Idar");
                           adresse = b.adresse + 'a';  hoyde = b.hoyde;   }
    void display() const { cout << navn << ", " << adresse
                                << " hoyde: " << hoyde << "    "; }
    float funk3(const B b, const float hoyde)
                         {  this->hoyde = (b.hoyde > hoyde) ? hoyde : b.hoyde;
                            return (this->hoyde); }
};


int main() {
  B  nr1("Are", "Aremark", 179.5),
     nr2("Odd", "Odda", 183.5);
  B* nr3 = new B("Morten", "Horten", 184.0);
  nr2.display();    nr1.display();            cout << '\n';
  nr2.funk1('d');   nr2.display();            cout << '\n';
  cout << (!nr3->funk2() ? "Vel" : "Joda")  <<    " ...\n";
  cout << nr1.funk3(*nr3, 183.5)    << '\n';
  B nr4(nr1);  nr4.display();  cout << '\n';

  return 0;
}



//  Utskrift:  Odd, Odda hoyde: 183.5    Are, Aremark hoyde: 179.5
//             Odd, Otta hoyde: 183.5
//             Joda ...
//             183.5
//             Are Idar, Aremarka hoyde: 183.5
