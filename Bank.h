#include<iostream>
#include<cstring>
#include<fstream>
#include<string>
using namespace std;

//class bank
class Bank{
    char depositorName_[50]; //depositor name
    int accountNumber_; //account number
    char accountType_[8]; //type of account either savings or current
    float balanceAmount_ = 0; //balance

    public:
    string getDepositorName(){
        return this->depositorName_;
    }
    
    int getAccountNumber(){
        return this->accountNumber_;
    }
    
    string getAccountType(){
        return this->accountType_;
    }
    
    float getBalance(){
        return this->balanceAmount_;
    }

    void openAcc();
    void showData();
    int withdraw();
    int deposit();
};

//to open account
void Bank::openAcc(){
    int n;
    cout<<"Name:";
    cin.ignore();
    cin.getline(depositorName_,50);
    cout<<"Enter your desired Account Number: ";
    cin>>accountNumber_;
    while(1){
        cout<<"Type of account: \n1.Savings\n2.Current\nChoice: ";
        cin>>n;
        if(n == 1 || n == 2){
            if (n == 1){
                strcpy(accountType_,"SAVINGS");
            }
            else{
                strcpy(accountType_,"CURRENT");
            }
            break;
        }
        else{
            cout<<"Wrong option Select again"<<endl;
        }
    }
    cout<<"Enter initial Deposit: ";
    cin>>balanceAmount_;
    cout<<"\nCreated Account"<<endl;
    this->showData();
}

//to get details
void Bank::showData(){
    cout<<"\n";
    cout<<"Account Number: "<<accountNumber_<<"\tName: "<<depositorName_<<"\tAccount Type: "<<accountType_<<"\tBalance: "<<balanceAmount_<<endl;
}

//for withdraw
int Bank::withdraw(){
    // check if the balance is greater than withdrawl amount
    // mofify the amount
    // send back the control
    float withdraw;
    cout<<"Enter amount you want to withdraw: ";
    cin>>withdraw;
    if(this->getBalance() < withdraw){
        cout<<"Insufficient Funds"<<endl;
        return 0;
    }
    else{
        this->balanceAmount_ -= withdraw;
        cout<<"Successful Withdraw\nDetails\n\n";
        this->showData();
        cout<<"\n";
        return withdraw;
    }
}

//for deposit
int Bank::deposit(){
    int amount;
    cout<<"Enter amount to deposit";
    cin>>amount;
    this->balanceAmount_ += amount;
    cout<<"Successful Withdraw\nDetails\n\n";
    this->showData();
    cout<<"\n";
    return amount;
}
