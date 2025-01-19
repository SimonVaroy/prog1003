#include <iostream>
using namespace std;

class kodeStil {
public:
  string name;
  bool kjedelig;
  bool moderne;
};

int main() {
  cout << "Dette er ikke et løsningsforslag";
  kodeStil frodeKode;
  frodeKode.name = "FrodeKode";
  frodeKode.kjedelig = true;
  frodeKode.moderne = false;
  if (frodeKode.kjedelig && !frodeKode.moderne) {
    return frodeKode.kjedelig;
  }
  return 0;
}
