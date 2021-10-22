/*
Author: Pranay Rishith
Date: 18th Oct

Banking System Management
Design a project to represent a bank account and its relevant operations, where following details
can be maintained:
1. Depositor name,
2. account number(you may define any starting number),
3. type of account,
4. balance amount in the account.

Actions:
1. Add new customers to the bank who become an account holder.
2. Display a list of all the account holders of the bank along with their account numbers and
balance.
3. Delete the information related to the account holder from the customer data file
4. Update the balance after customer has performed a deposit or withdraw transaction
5. display the account number of the last entry
6. check whether an account exists or not
7. retrieve the name of the account holder
8. retrieve the address of the account holder
9. retrieve the balance of the account holder
10. returns the record number from the customer file when an employee of the bank enters
the account number related to an account holder(Transaction details along with the
account information)
11. displays all the information related to an account holder from the customer file on the
basis of specified account number.
12. Calculate the interest to date on the deposit if a particular customer has not withdrawn
for more than a month

*/

/*
Some important points:
fstream is used universally for both reading and writing
ios::binary is used to read in binary
ios::in is used for read operations
ios::out is used for write operations
ios::app is used to append at end of file but append is not used cause the changes are mostly inbetween
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
void getBalance(); //to return balance of the account holder
void allTransactions(); //to show transaction history
void closeAccount(); //to delete account
void getAccount(); //to get details of specific account
void getTransactions(int); //to get transaction for account holder
void getRecordNumber(); //to get record number with transactions details


int main(){
    system("cls");
    int n;
    cout<<"Welcome to the BANK"<<endl;
    do{
        cout<<"\nMAIN MENU\n1.Open An account\n2.Deposit\n3.Withdraw\n4.Check Balance\n5.Get Account Details\n6.All Accounts\n7.Close account\n8.Record Number\n9.All Transactions\n10.Exit"<<endl;
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
            case 9:
                allTransactions();
        }
    }while(n<10);

}

//to open account
void openAccount(){
    fstream outFile1,outFile2;
    char temp[] = "Deposit";
    outFile1.open("accountDetails",ios::binary|ios::in|ios::out|ios::app);
    Transaction t;
    outFile2.open("transactionData",ios::binary|ios::in|ios::out|ios::app);
    Bank b;
    cout<<"\nEnter your Details"<<endl;
    b.openAcc();
    t.addTransactions(b.getAccountNumber(),temp,b.getBalance());
    outFile2.write((char*)&t,sizeof(Transaction));
    outFile1.write((char*)&b,sizeof(Bank));
    outFile1.close();
    outFile2.close();
}

//to get all account details
void allAccounts(){
    fstream inFile;
    inFile.open("accountDetails",ios::binary|ios::in);
    Bank b;
    cout<<"\n\n\t\tACCOUNT HOLDER LIST";
    while(inFile.read((char*)&b,sizeof(Bank))){
        b.showData();
    }
    inFile.close();
}

//to withdraw amount
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
    inFile2.open("transactionData",ios::binary|ios::in|ios::out|ios::app);
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
            inFile2.write((char*)&t,sizeof(Transaction));
            inFile.close();
            inFile2.close();
        }
    } 
}

//to deposit amount
void depositAmount(){
    // open file
    // read file and get objects
    // check the user input account number with the objects acc no
    // if matched then send that object to deposit
    // if not found break and ask to open new account
    // if found change the balance amount and delete the present entry and include new data into the file
    // close the file
    int accNo,flag = 0,pos;
    fstream inFile,outFile;
    Bank b;
    char temp[] = "Deposit";
    Transaction t;
    inFile.open("accountDetails",ios::binary|ios::in|ios::out);
    outFile.open("transactionData",ios::binary|ios::in|ios::out|ios::app);
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

//to get balance
void getBalance(){
    int accNo,flag=0;
    fstream inFile;
    Bank b;
    inFile.open("accountDetails",ios::binary|ios::in);
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

//to get all transactions made in the bank
void allTransactions(){
    fstream inFile;
    inFile.open("transactionData",ios::binary|ios::in);
    Transaction t;
    while(inFile.read((char*)&t,sizeof(Transaction))){
        t.showTransactions();
    }
    inFile.close();
}

//to close an account
void closeAccount(){
    int accno;
    Bank b;
    fstream file1,file2;
    file1.open("accountDetails",ios::binary);
    file2.open("tempFile",ios::binary|ios::in|ios::out);
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

//to get account details
void getAccount(){
    Bank b;
    fstream inFile;
    inFile.open("accountDetails",ios::binary|ios::in);
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

//to get record number
void getRecordNumber(){
    Bank b;
    fstream inFile;
    inFile.open("accountDetails",ios::binary|ios::in);
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
    cout<<"\nRecord Number: "<<count+1<<endl;
    getTransactions(accNo);
    cout<<"\n";
}

//to get transactions details on specific account
void getTransactions(int accno=100000){
    fstream inFile;
    int flag=0;
    inFile.open("transactionData",ios::binary|ios::in);
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