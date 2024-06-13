enum class LogType {
  BankingSystemCreation,
  BankCreation,
  AccountCreation,
  AccountDeposit,
  AccountWithdraw,
  Transaction,
  Error
};

class Log {
  private:
    int logId;
    LogType logType;
    string logMessage;
    time_t timestamp;

  public:
    Log(int id, LogType type, string message="") : logId(id), logType(type), logMessage(message) {
      timestamp = time(nullptr);
    }

    void print() const {
      cout << "[" << ctime(&timestamp) << "] ";
      cout<< "Log ID: " << logId << ", ";
      cout<< "Log Type: ";
      switch (logType) {
        case LogType::BankingSystemCreation:
          cout << "BankingSystemCreation";
          break;
        case LogType::BankCreation:
          cout << "Bank Creation";
          break;
        case LogType::AccountCreation:
          cout << "Account Creation";
          break;
        case LogType::AccountDeposit:
          cout << "Account Deposit";
          break;
        case LogType::AccountWithdraw:
          cout << "Account Withdraw";
          break;
        case LogType::Transaction:
          cout << "Transaction";
          break;
        case LogType::Error:
          cout << "Error";
          break;
      }
      if(!logMessage.empty())
        cout <<", Log Message -> "<< logMessage;
      cout<<endl;// New Line
    }
};