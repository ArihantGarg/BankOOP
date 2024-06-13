// Based on Banking System "India"

void addBank(string bankName){
  if(India.addBank(bankName)){
    cout<<"Bank "<<bankName<<" created successfully"<<endl;
  }
  else{
    cout<<"Bank "<<bankName<<" already exists"<<endl;
  }
}

void addAccount(string bankName, int accountNumber, string accountHolderName,int initialBalance=0){
  if(India.addAccount(bankName, accountNumber, accountHolderName, initialBalance)){
    cout<<"Account "<<accountNumber<<" created in Bank "<<bankName<<" with initial balance "<<initialBalance<<endl;
  }
  else{
    cout<<"Error in account creation"<<endl;
  }
}

void getAccountBalance(string bankName, int accountNumber){
  shared_ptr<BankingSystem::Bank::Account> account (India.getAccount(bankName,accountNumber));
  if(account==NULL){
    cout<<"Account does not exist"<<endl;
  }
  else{
    cout<<"Account "<<accountNumber<<" in Bank "<<bankName<<" has balance "<<account->getAccountBalance()<<endl;
  }
}

void deposit(string bankName, int accountNumber, int amount){
  if(India.deposit(bankName, accountNumber, amount)){
    cout<<"Deposited "<<amount<<" in account "<<accountNumber<<" of Bank "<<bankName<<endl;
  }
  else{
    cout<<"Error in deposit"<<endl;
  }
}

void withdraw(string bankName, int accountNumber, int amount){
  if(India.withdraw(bankName, accountNumber, amount)){
    cout<<"Withdrew "<<amount<<" from account "<<accountNumber<<" of Bank "<<bankName<<endl;
  }
  else{
    cout<<"Error in withdraw"<<endl;
  }
}

void transaction(string senderBankName,int senderAccountNumber,string recieverBankName,int recieverAccountNumber,long long amount){
  if(India.transaction(senderBankName, senderAccountNumber, recieverBankName, recieverAccountNumber, amount)){
    cout<<"Transaction successful"<<endl;
  }
  else{
    cout<<"Error in transaction"<<endl;
  }
}