#include "BankingSystemLogs.hpp"
#include "Log.hpp"

class BankingSystem{
  private:
    vector<Log> logs; //Log related stuff
    int nextLogId;

  public:
    void printLogs() const {
      for(auto log : logs)
        log.print();
    }
  
    void addLog(LogType logType,string message=""){
      logs.push_back(Log(nextLogId++, logType, message));
    }

  public:
    class Bank{
      private:
        string name;

      public:
        Bank(string name){
          this->name = name;
        }

        class Account{
          private:
            int accountNumber;
            string accountHolderName;
            long long accountBalance;
            // Vector of transactions,deposits,withdrawals

          public:
            Account(int accountNumber,string accountHolderName,long long accountBalance=0){
              this->accountNumber = accountNumber;
              this->accountHolderName = accountHolderName;
              this->accountBalance = accountBalance;
            }

            int getAccountNumber(){
              return accountNumber;
            }

            string getAccountHolderName(){
              return accountHolderName;
            }

           long long getAccountBalance(){
              return accountBalance;
            }

            bool deposit(long long amount){
              if(amount<0)
                return 0;
              accountBalance += amount;
              return 1;
            }

            bool withdraw(long long amount){
              if(amount<0)
                return 0;
              if(accountBalance<amount)
                return 0;
              accountBalance -= amount;
              return 1;
            }
        };

      private:
        map<int,shared_ptr<Account>> accounts;

      public:
        bool addAccount(int accountNumber,string accountHolderName,long long accountBalance=0){
          if(accounts.find(accountNumber)!=accounts.end())
            return 0;
          if(accountBalance<0)
              return 0;
          accounts[accountNumber] = make_shared<Account>(accountNumber,accountHolderName,accountBalance);
          return 1;
        }

        shared_ptr<Bank::Account> getAccount(int accountNumber){
          if(accounts.find(accountNumber)==accounts.end())
            return NULL;
          return accounts[accountNumber];
        }

        bool deposit(int accountNumber,long long amount){
          shared_ptr<Account> account = getAccount(accountNumber);
          if(account==NULL)
            return 0;
          return account->deposit(amount);
        }

        bool withdraw(int accountNumber,long long amount){
          shared_ptr<Account> account = getAccount(accountNumber);
          if(account==NULL)
            return 0;
          return account->withdraw(amount);
        }

        bool transaction(int senderAccountNumber,int recieverAccountNumber,long long amount){
          shared_ptr<Account> senderAccount = getAccount(senderAccountNumber);
          shared_ptr<Account> recieverAccount = getAccount(recieverAccountNumber);
          if(senderAccount==NULL || recieverAccount==NULL)
            return 0;
          if(senderAccount==recieverAccount) // Transaction to same account
            return 0;
          if(amount<0)
            return 0;

          if(senderAccount->withdraw(amount))
          {
            if(recieverAccount->deposit(amount)){
              // Successful Reciever Deposit
              return 1;
            }
            else{
              // Unsuccessful Reciever Deposit
              // Revert Sender Withdraw
              senderAccount->deposit(amount);
              return 0;
            }
          }
          else
          {
            // Unsuccessful Sender Withdraw
            return 0;
          }
        }
    };

  private: 
    map<string,shared_ptr<Bank>> banks;

  public:
    BankingSystem(){
      nextLogId = 1;
      addLog(LogType::BankingSystemCreation);
    }

    bool addBank(string name){
      if(banks.find(name)!=banks.end()){
        addLog(LogType::Error,"Bank already exists");
        return 0;
      }
      
      banks[name] = make_shared<Bank>(name);
      addLog(LogType::BankCreation,name);
      return 1;
    }

    shared_ptr<Bank> getBank(string name){
      if(banks.find(name)==banks.end()){
        addLog(LogType::Error,"Bank" + name + "does not exist");
        return NULL;
      }
      return banks[name];
    }

    bool addAccount(string bankName,int accountNumber,string accountHolderName,long long accountBalance){
      shared_ptr<Bank> bank = getBank(bankName);
      if(bank==NULL){
        addLog(LogType::Error,"Account cannot be created as Bank" + bankName + "does not exist");
        return 0;
      }
      addLog(LogType::AccountCreation,bankName + " " + to_string(accountNumber));
      return bank->addAccount(accountNumber,accountHolderName,accountBalance);
    }

    shared_ptr<BankingSystem::Bank::Account> getAccount(string bankName,int accountNumber){
      shared_ptr<Bank> bank = getBank(bankName);
      if(bank==NULL){
        addLog(LogType::Error,"Account cannot be queried as Bank" + bankName + "does not exist");
        return NULL;
      }
      return bank->getAccount(accountNumber);
    }

    bool deposit(string bankName,int accountNumber,long long amount){
      shared_ptr<Bank::Account> account = getAccount(bankName,accountNumber);
      if(account==NULL){
        addLog(LogType::Error,"Account cannot be deposited as Bank" + bankName + "does not exist");
        return 0;
      }

      bool successfulDeposit=account->deposit(amount);

      if(successfulDeposit){
        addLog(LogType::AccountDeposit,bankName + " " + to_string(accountNumber) + " " + to_string(amount));
        return 1;
      }
      else{
        addLog(LogType::Error,"Failed to deposit " + to_string(amount) + " to Account "+ to_string(accountNumber) + " in Bank " + bankName);
        return 0;
      }
    }

    bool withdraw(string bankName,int accountNumber,long long amount){
      shared_ptr<Bank::Account> account = getAccount(bankName,accountNumber);
      if(account==NULL){
        addLog(LogType::Error,"Account cannot be withdrawn as Bank" + bankName + "does not exist");
        return 0;
      }

      bool successfulWithdraw=account->withdraw(amount);

      if(successfulWithdraw){
        addLog(LogType::AccountWithdraw,bankName + " " + to_string(accountNumber) + " " + to_string(amount));
        return 1;
      }
      else{
        addLog(LogType::Error,"Failed to withdraw " + to_string(amount) + " from Account " + to_string(accountNumber) + " in Bank " + bankName);
        return 0;
      }
    }

    bool transaction(string senderBankName,int senderAccountNumber,string recieverBankName,int
recieverAccountNumber,long long amount){
      shared_ptr<Bank> senderBank = getBank(senderBankName);
      shared_ptr<Bank> recieverBank = getBank(recieverBankName);
      if(senderBank==NULL || recieverBank==NULL){
        addLog(LogType::Error,"Transaction cannot be performed as Bank " + senderBankName + " or Bank " +
          recieverBankName + " does not exist");
        return 0;
      }
      if(senderBank==recieverBank){ // Same Bank Transaction
        bool successfulTransaction = senderBank
        ->transaction(senderAccountNumber,recieverAccountNumber,amount);
        
        if(successfulTransaction){
          addLog(LogType::Transaction,"Sender: " + senderBankName + " " + to_string(senderAccountNumber) + " Reciever: " + recieverBankName + " " + to_string(recieverAccountNumber) + " Amount: " +
            to_string(amount));
          return 1;
        }
        else{
          addLog(LogType::Error,"Failed to perform same bank transaction");
          return 0;
        }
      }

      // Different Bank Transaction
      if(withdraw(senderBankName,senderAccountNumber,amount)){
        if(deposit(recieverBankName,recieverAccountNumber,amount)){
          // Successful Reciever Deposit
          addLog(LogType::Transaction,"Sender: " + senderBankName + " " + to_string(senderAccountNumber) + " Reciever: " + recieverBankName + " " + to_string(recieverAccountNumber) + " Amount: " +
            to_string(amount));
          return 1;
        }
        else{
          // Unsuccessful Reciever Deposit
          // Revert Sender Withdraw
          deposit(senderBankName,senderAccountNumber,amount);
          addLog(LogType::Error,"Failed to perform transaction due to unsuccessful Reciever Deposit");
          return 0;
        }
      }
      else{
        // Unsuccessful Sender Withdraw
        addLog(LogType::Error,"Failed to perform transaction due to unsuccessful Sender Withdraw");
        return 0;
      }
    }
};