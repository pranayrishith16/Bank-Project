/*
Author: Pranay Rishith
Date: 18th Oct
*/

/*

3. Delete the information related to the account holder from the customer data file
5. display the account number of the last entry
8. retrieve the address of the account holder(Not possible with present data)
10. returns the record number from the customer file when an employee of the bank enters
the account number related to an account holder(Transaction details along with the
account information)
11. displays all the information related to an account holder from the customer file on the
basis of specified account number.
12. Calculate the interest to date on the deposit if a particular customer has not withdrawn
for more than a month
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



int main(){
    // openAccount();
    // allAccounts();
    // depositAmount();
    // withdrawAmount();
    allTransactions();
}

void openAccount(){
    ofstream outFile;
    outFile.open("accountDetails.dat",ios::binary|ios::app);
    Bank b;
    cout<<"Enter your Details"<<endl;
    b.openAcc();
    outFile.write((char*)&b,sizeof(Bank));
    outFile.close();
}


void allAccounts(){
    ifstream inFile;
    inFile.open("accountDetails.dat",ios::binary);
    Bank b;
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
    inFile.open("accountDetails.dat",ios::binary|ios::in|ios::out);
    inFile2.open("transactionData.dat",ios::binary|ios::in|ios::out);
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
    inFile.open("accountDetails.dat",ios::binary|ios::in|ios::out);
    outFile.open("transactionData.dat",ios::binary|ios::app);
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
    allAccounts();
}

void getName(){
    int accNo,flag=0;
    fstream inFile;
    Bank b;
    inFile.open("accountDetails.dat",ios::binary|ios::in|ios::out);
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
    inFile.open("accountDetails.dat",ios::binary|ios::in|ios::out);
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
    cout<<b.getBalance();
}

void allTransactions(){
    ifstream inFile;
    inFile.open("transactionData.dat",ios::binary);
    Transaction t;
    while(inFile.read((char*)&t,sizeof(Transaction))){
        t.showTransactions();
    }
    inFile.close();
}