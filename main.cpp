#include <bits/stdc++.h>
using namespace std;
#include "BankingSystem.hpp"
BankingSystem India;
#include "functions.hpp"



int main() {

  FILE* file = freopen("output.txt", "w", stdout);
  if (file == nullptr) {
      std::cerr << "Failed to open file." << std::endl;
      return 1;
  }

  addBank("SBI");
  addBank("SBI");
  addBank("ICICI");
  addBank("HDFC");

  addAccount( "SBI", 101, "Ram", 10000);
  addAccount( "SBI", 102, "Shyam");
  addAccount( "ICICI", 201, "Ram", 20000);
  addAccount( "HDFC", 301, "Ram", 30000);
  addAccount( "SBI", 301, "Ram", 30000);
  addAccount( "SBI", 301, "Ram", 10000);
  addAccount( "SBI", 301, "Ghyam");

  getAccountBalance("SBI", 101);
  getAccountBalance("SBI", 102);
  getAccountBalance("SBI", 103);
  getAccountBalance("FakeBank", 104);
  getAccountBalance("ICICI", 201);
  getAccountBalance("HDFC", 301);
  getAccountBalance("HDFC", 302);

  deposit("SBI", 101, 1000);
  getAccountBalance("SBI", 101);
  deposit("SBI", 102, 1000);
  getAccountBalance("SBI", 102);
  deposit("ICICI", 201, 1000);
  getAccountBalance("ICICI", 201);
  deposit("HDFC", 301, 1000);
  getAccountBalance("HDFC", 301);
  deposit("FakeBank", 301, 1000);
  getAccountBalance("FakeBank", 301);

  withdraw("SBI", 101, 1000);
  getAccountBalance("SBI", 101);
  withdraw("SBI", 102, 1000);
  getAccountBalance("SBI", 102);
  withdraw("FaKiBank", 301, 1000);
  withdraw("SBI", 101, 100000);
  getAccountBalance("SBI", 101);

  cout<<"\n\n";
  
  getAccountBalance("SBI", 101);
  getAccountBalance("ICICI", 2001);
  transaction( "SBI", 101, "ICICI", 2001, 1000);
  getAccountBalance("SBI", 101);
  getAccountBalance("ICICI", 2001);

  for(int i=0;i<50000;i++){
    transaction( "SBI", 101, "ICICI", 201, 1);
  }

  cout<<"\n\n";

  // Printing Logs

  India.printLogs();

  return 0;
}