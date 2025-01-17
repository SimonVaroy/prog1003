/**
 *   Løsning til eksamen i OOProg (i C++), august 2024, oppgave 1A.
 *
 *   @file     EX_S24_1A.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>
#include <string>
#include <algorithm>
using namespace std;


class A  {
  protected:
    string aa;
  public:
    A(string s)  {  aa = s;  }
    virtual void display() = 0;
};


class B : public A  {
  private:
    int bb;
  public:
    B(string s, int b) : A(s)  {  bb = b;  }
    void display()  {  cout << aa << ' ' << bb;  }
    void funk1(string s)  {  aa += (' ' + s);  }
    int  funk2(string s, string t)
              {  aa.insert(aa.size(),s);  return (aa.find_first_of(t));  }
};


class C : public A  {
  private:
    char cc;
  public:
    C(string s, char c) : A(s)  {  cc = c;  }
    void display()  {  cout << aa << ' ' << cc;   }
    string funk1()  {  return (aa.substr(3, 3));  }
    void funk2(string s)  { for (int i = 73; i < 77;  i++) aa += s;   }
    bool funk2(char c)  { return (count(aa.begin(), aa.end(), c) > 4); }
};


int main() {
  B  bObj("Brokke", 1708);
  C* cObj = new C("Hovden", 'T');
  A* obj = new C("Revesand", 'E');
  bObj.display();  cout << ' ';  cObj->display(); cout << ' ';
  obj->display();  cout << '\n';
  bObj.funk1("hytte");  bObj.display();  cout << '\n';
  cout << cObj->funk1() + "ne" << '\n';
  cout << bObj.funk2("felt", "t") << '\n';
  cObj->funk2("AT");  cObj->display();  cout << ' ' << cObj->funk2('T') << '\n';

  return 0;
}



//  Utskrift:  Brokke 1708 Hovden T Revesand E
//             Brokke hytte 1708
//             denne
//             9
//             HovdenATATATAT T 0
