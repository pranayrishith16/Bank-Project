/*
Author: Pranay Rishith
Date: 18th Oct
*/


#include<iostream>
#include<cstring>
#include<fstream>
#include<string>
#include"Bank.h" //bank class as a header file
#include"Transaction.h" //Transaction class as a header file
using namespace std;

void openAccount(); //To open an account
void getDetails(); //to get details of the account holder
void allAccounts(); //to display all the accounts in the bank
void withdrawAmount(); //to withdraw amount
void depositAmount(); //to deposit amount
void getName(); //to return name of the account holder
void getBalance(); //to return balance of the account holder
void allTransactions(); //to show transaction history
void closeAccount(); //to delete account
void getAccount(); //to get details of specific account
void getTransactions(int); //to get transaction for account holder
void getRecordNumber(); 


int main(){
    system("cls");
    int n;
    cout<<"Welcome to the BANK"<<endl;
    do{
        cout<<"\nMAIN MENU\n1.Open An account\n2.Deposit\n3.Withdraw\n4.Check Balance\n5.Get Account Details\n6.All Accounts\n7.Close account\n8.Record Number\n9.Exit"<<endl;
        cout<<"Enter Choice: ";
        cin>>n;
        switch(n){
            case 1:
                openAccount();
                break;
            case 2:
                depositAmount();
                break;
            case 3:
                withdrawAmount();
                break;
            case 4:
                getBalance();
                break;
            case 5:
                getAccount();
                break;
            case 6:
                allAccounts();
                break;
            case 7:
                closeAccount();
                break;
            case 8:
                getRecordNumber();
                break;
        }
    }while(n<9);

}


void openAccount(){
    ofstream outFile;
    outFile.open("accountDetails",ios::binary|ios::app);
    Bank b;
    cout<<"\nEnter your Details"<<endl;
    b.openAcc();
    outFile.write((char*)&b,sizeof(Bank));
    outFile.close();
}


void allAccounts(){
    ifstream inFile;
    inFile.open("accountDetails",ios::binary);
    Bank b;
    cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"AccNo.      NAME      Type        Balance\n";
	cout<<"====================================================\n";
    while(inFile.read((char*)&b,sizeof(Bank))){
        b.showData();
    }
    inFile.close();
}

void withdrawAmount(){
    // open file
    // read file and get objects
    // check the user input account number with the objects acc no
    // if matched then send that object to withdraw
    // if not found break and ask to open new account
    // if found change the balance amount and delete the present entry and include new data into the file
    // close the file
    int accNo,flag = 0,pos;
    fstream inFile,inFile2;
    Bank b;
    char temp[] = "Withdraw";
    Transaction t;
    inFile.open("accountDetails",ios::binary|ios::in|ios::out);
    inFile2.open("transactionData",ios::binary|ios::in|ios::out);
    cout<<"Enter your account number: ";
    cin>>accNo;
    while(inFile.read((char*)&b,sizeof(Bank))){
        if(b.getAccountNumber() == accNo){
			flag = 1;
            break;
        }
    }
    if (flag == 0){
        cout<<"There is no account with this account Number"<<endl;
        return;
    }
    else{
        int amt = b.withdraw();
    if(amt != 0){
        pos = (-1)*sizeof(Bank); //the pointer is on end of the object to to get back multiplying with -1 to get current object location
        inFile.seekp(pos,ios::cur);
        inFile.write((char*)&b,sizeof(Bank));
        t.addTransactions(b.getAccountNumber(),temp,amt);
        inFile.write((char*)&t,sizeof(Transaction));
        inFile.close();
        inFile2.close();
        }
    }
}

void depositAmount(){
    // open file
    // read file and get objects
    // check the user input account number with the objects acc no
    // if matched then send that object to deposit
    // if not found break and ask to open new account
    // if found change the balance amount and delete the present entry and include new data into the file
    // close the file
    int accNo,flag = 0,pos;
    fstream inFile;
    ofstream outFile;
    Bank b;
    char temp[] = "Deposit";
    Transaction t;
    inFile.open("accountDetails",ios::binary|ios::in|ios::out);
    outFile.open("transactionData",ios::binary|ios::app);
    cout<<"Enter your account number: ";
    cin>>accNo;
    while(inFile.read((char*)&b,sizeof(Bank))){
        if(b.getAccountNumber() == accNo){
			flag = 1;
            break;
        }
    }
    if (flag == 0){
        cout<<"There is no account with this account Number"<<endl;
        return;
    }
    int amt = b.deposit();
    pos = (-1)*sizeof(Bank); //the pointer is on end of the object to to get back multiplying with -1 to get current object location
    inFile.seekp(pos,ios::cur);
    inFile.write((char*)&b,sizeof(Bank));
    t.addTransactions(b.getAccountNumber(),temp,amt);
    outFile.write((char*)&t,sizeof(Transaction));
    inFile.close();
    outFile.close();
}

void getName(){
    int accNo,flag=0;
    fstream inFile;
    Bank b;
    inFile.open("accountDetails",ios::binary|ios::in|ios::out);
    cout<<"Enter your account number: ";
    cin>>accNo;
    while(inFile.read((char*)&b,sizeof(Bank))){
        if(b.getAccountNumber() == accNo){
			flag = 1;
            break;
        }
    }
    if (flag == 0){
        cout<<"There is no account with this account Number"<<endl;
        return;
    }
    cout<<b.getDepositorName();
}

void getBalance(){
    int accNo,flag=0;
    fstream inFile;
    Bank b;
    inFile.open("accountDetails",ios::binary|ios::in|ios::out);
    cout<<"Enter your account number: ";
    cin>>accNo;
    while(inFile.read((char*)&b,sizeof(Bank))){
        if(b.getAccountNumber() == accNo){
			flag = 1;
            break;
        }
    }
    if (flag == 0){
        cout<<"There is no account with this account Number"<<endl;
        return;
    }
    cout<<"\nBalance: "<<b.getBalance()<<"\n";
}

void allTransactions(){
    ifstream inFile;
    inFile.open("transactionData",ios::binary);
    Transaction t;
    while(inFile.read((char*)&t,sizeof(Transaction))){
        t.showTransactions();
    }
    inFile.close();
}

void closeAccount(){
    int accno;
    Bank b;
    fstream file1,file2;
    file1.open("accountDetails",ios::binary);
    file2.open("tempFile",ios::binary);
    cout<<"Enter your account Number: ";
    cin>>accno;
    while(file1.read((char*)&b,sizeof(Bank))){
        if(b.getAccountNumber()!=accno){
            file2.write((char*)&b,sizeof(Bank));
        }
    }
    file1.close();
    file2.close();
    remove("accountDetails");
    rename("tempFile","accountDetails");
    cout<<"\nAccount Deleted";
}

void getAccount(){
    Bank b;
    fstream inFile;
    inFile.open("accountDetails",ios::binary);
    int accNo,flag=0;
    cout<<"Enter account Number: ";
    cin>>accNo;
    while(inFile.read((char*)&b,sizeof(Bank))){
        if(b.getAccountNumber() == accNo){
			flag = 1;
            break;
        }
    }
    if (flag == 0){
        cout<<"There is no account with this account Number"<<endl;
        return;
    }
    b.showData();
}

void getRecordNumber(){
    Bank b;
    fstream inFile;
    inFile.open("accountDetails",ios::binary);
    int accNo,flag=0,count = 0;
    cout<<"Enter account Number: ";
    cin>>accNo;
    while(inFile.read((char*)&b,sizeof(Bank))){
        if(b.getAccountNumber() != accNo){
			count ++;
        }
        else if (b.getAccountNumber() ==accNo){
            flag = 1;
            break;
        }
    }
    if (flag == 0){
        cout<<"There is no account with this account Number"<<endl;
        return;
    }
    cout<<"Record Number: "<<count+1<<endl;
    getTransactions(accNo);
}

void getTransactions(int accno=100000){
    ifstream inFile;
    int flag=0;
    inFile.open("transactionData",ios::binary);
    if (accno == 100000){
        cout<<"Enter your account Number: ";
        cin>>accno;
    }
    Transaction t;
    while(inFile.read((char*)&t,sizeof(Transaction))){
        if (t.getAccountNumber() == accno){
            t.showTransactions();
            flag = 1;
        }
    }
    if (flag == 0){
        cout<<"No Transactions Found"<<endl;
    }
    inFile.close();
}