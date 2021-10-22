#include<iostream>
#include<cstring>
#include<fstream>
#include<string>
using namespace std;

class Transaction{
    int accountNumber_;
    char typeOfTransaction_[10];
    float amount_;
    public:
    void showTransactions();
    void addTransactions(int ,char[],float);
    int getAccountNumber();
};

// to add transactions
void Transaction::addTransactions(int accNo,char type[10],float amt){
    this->accountNumber_ = accNo;
    this->amount_ = amt;
    strcpy(typeOfTransaction_,type);
}

//to show transactions
void Transaction::showTransactions(){
    cout<<"\nAccount Number: "<<accountNumber_<<"\tType: "<<typeOfTransaction_<<"\tAmount: "<<amount_<<endl;
}

//to get account number
int Transaction::getAccountNumber(){
    return this->accountNumber_;
}