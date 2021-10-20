#include<iostream>
#include<cstring>
#include<fstream>
#include<string>
using namespace std;

class Transaction{
    int accountNumber_;
    char typeOfTransaction_[10];
    float amount;
    public:
    void showTransactions();
    void addTransactions(int ,char[],float);
};


void Transaction::addTransactions(int accNo,char type[10],float amt){
    this->accountNumber_ = accNo;
    this->amount = amt;
    strcpy(typeOfTransaction_,type);
}

void Transaction::showTransactions(){
    cout<<"Account Number: "<<accountNumber_<<endl;
    cout<<"Type: "<<typeOfTransaction_<<endl;
    cout<<"Amount: "<<amount<<endl;
}