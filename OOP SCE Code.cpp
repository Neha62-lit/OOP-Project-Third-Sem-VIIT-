#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;
class Bank
{    //private class
    int accnum;
    char accname[50];
    int deposit;
    char type;
public: //public class
    void newaccount();  //function to get data from user
    void displayaccount() const;  //function to show data on screen
    void modify();  //function to add new data
    void dep(int);  //function to accept amount and add to balance amount
    void withdraw(int); //function to accept amount and subtract from balance amount
    void report() const;    //function to show data in tabular format
    int retacno() const;    //function to return account number
    int retdeposit() const; //function to return balance amount
    char rettype() const;  //function to return type of account
};

void Bank::newaccount()   // define method of class outside using scope resolution operator
{
    cout<<"\n\t\tEnter The account Number         : ";
    cin>>accnum;
    cout<<"\t\tEnter The Name of account Holder : ";
    cin.ignore();
    cin.getline(accname,50);
    cout<<"\t\tEnter Type of The account (C/S)  : ";
    cin>>type;
    type=toupper(type);
    cout<<"\t\tEnter The Initial amount         : ";
    cin>>deposit;
    cout<<"\t\tCongratulations....Your Account Has Been successfully Created!!!!!";
}

void Bank::displayaccount() const
{
    cout<<"\n\t\tAccount No.         : "<<accnum;
    cout<<"\n\t\tAccount Holder Name : "<<accname;
    cout<<"\n\t\tType of Account     : "<<type;
    cout<<"\n\t\tBalance amount      : "<<deposit;
}
void Bank::modify()
{
    cout<<"\n\t\tAccount No. : "<<accnum;
    cout<<"\n\t\tModify Account Holder Name : ";
    cin.ignore();
    cin.getline(accname,50);
    cout<<"\n\t\tModify Type of Account : ";
    cin>>type;
    type=toupper(type);
    cout<<"\n\t\tModify Balance amount : ";
    cin>>deposit;
}
void Bank::dep(int x)
{
    deposit+=x;
}

void Bank::withdraw(int x)
{
    deposit-=x;
}

void Bank::report() const
{
    cout<<accnum<<setw(20)<<" "<<accname<<setw(30)<<" "<<type<<setw(6)<<deposit<<endl;
}

int Bank::retacno() const   //function to return account number
{
    return accnum;
}

int Bank::retdeposit() const //function to return balance amount
{
    return deposit;
}

char Bank::rettype() const //function to return type of account
{
    return type;
}
//function declaration

void write_account();   //function to write record in binary file
void display_sp(int);   //function to display account details given by user
void modify_account(int);   //function to modify record of file
void delete_account(int);   //function to delete record of file
void deposit_withdraw(int, int); // function to desposit/withdraw amount for given account
void intro();   //introductory screen function

//THE MAIN FUNCTION OF PROGRAM
int main()
{
    char ch;
    int number;
    intro();
    do
    {
        cout<<"\n\n\n\t************************MAIN MENU************************";
        cout<<"\n\t01. NEW ACCOUNT";
        cout<<"\n\t02. DEPOSIT AMOUNT";
        cout<<"\n\t03. WITHDRAW AMOUNT";
        cout<<"\n\t04. BALANCE ENQUIRY";
        cout<<"\n\t05. CLOSE AN ACCOUNT";
        cout<<"\n\t06. MODIFY AN ACCOUNT";
        cout<<"\n\t07. QUIT";
        cout<<"\n\tEnter Your Choice :\t";
        cin>>ch;
        switch(ch)
        {
        case '1':
            write_account();
            break;
        case '2':
            cout<<"\n\t\tEnter The account No. : "; cin>>number;
            deposit_withdraw(number, 1);
            break;
        case '3':
            cout<<"\t\tEnter The account No. : "; cin>>number;
            deposit_withdraw(number, 2);
            break;
        case '4':
            cout<<"\t\tEnter The account No. : "; cin>>number;
            display_sp(number);
            break;
        case '5':
            cout<<"\t\tEnter The account No. : "; cin>>number;
            delete_account(number);
            break;
         case '6':
            cout<<"\t\tEnter The account No. : "; cin>>number;
            modify_account(number);
            break;
         case '7':
            cout<<"\n\n\t\tThanks for using Banking Management System!!!!";
            break;
         default :cout<<"\a";
        }
        cin.ignore();
        cin.get();
    }while(ch!='7');
    return 0;
}

//  function to write in file
void write_account()
{
    Bank ac;
    ofstream outFile;
    outFile.open("Bankinginfo.dat",ios::binary|ios::app);
    ac.newaccount();
    outFile.write(reinterpret_cast<char *> (&ac), sizeof(Bank));
    outFile.close();
}

//      function to read specific record from file
void display_sp(int n)
{
    Bank ac;
    bool flag=false;
    ifstream inFile;
    inFile.open("Bankinginfo.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    cout<<"\n\t\t\tBALANCE DETAILS\n\t\t\t";
        while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(Bank)))
    {
      if(ac.retacno()==n)
        {
            ac.displayaccount();
            flag=true;
        }
    }
    inFile.close();
    if(flag==false)
        cout<<"\n\t\tAccount number does not exist";
}

//      function to modify record of file
void modify_account(int n)
{
    bool found=false;
  Bank ac;
    fstream File;
    File.open("Bankinginfo.dat",ios::binary|ios::in|ios::out);
    if(!File)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    while(!File.eof() && found==false)
    {
        File.read(reinterpret_cast<char *> (&ac), sizeof(Bank));
       if(ac.retacno()==n)
        {
            ac.displayaccount();
            cout<<"\n\t\tEnter The New Details of account"<<endl;
            ac.modify();
            int pos=(-1)*static_cast<int>(sizeof(Bank));
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char *> (&ac), sizeof(Bank));
            cout<<"\n\n\t Record Updated";
            found=true;
          }
    }
    File.close();
    if(found==false)
        cout<<"\n\t\t\tRecord Not Found!!!!Please Try Again...";
}


//      function to delete record of file
void delete_account(int n)
{
    Bank ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("Bankinginfo.dat",ios::binary);
    if(!inFile)
    {
        cout<<"\t\tFile could not be open !! Press any Key...";
        return;
    }
    outFile.open("Temp.dat",ios::binary);
    inFile.seekg(0,ios::beg);
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(Bank)))
    {
       if(ac.retacno()!=n)
        {
            outFile.write(reinterpret_cast<char *> (&ac), sizeof(Bank));
        }
    }
    inFile.close();
    outFile.close();
    remove("Bankinginfo.dat");
    rename("Temp.dat","Bankinginfo.dat");
    cout<<"\n\n\tRecord Deleted ..";
}

// function to deposit and withdraw amounts
void deposit_withdraw(int n, int option)
{
    int amt;
    bool found=false;
    Bank ac;
    fstream File;
    File.open("Bankinginfo.dat", ios::binary|ios::in|ios::out);
    if(!File)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    while(!File.eof() && found==false)
    {
        File.read(reinterpret_cast<char *> (&ac), sizeof(Bank));
        if(ac.retacno()==n)
        {
            ac.displayaccount();
            if(option==1)
            {
                cout<<"\n\n\t\tTO DEPOSITE AMOUNT: \t";
                cout<<"\n\t\t\tEnter The amount to be deposited: \t"; cin>>amt;
                ac.dep(amt);
            }
            if(option==2)
            {
                cout<<"\n\n\t\tTO WITHDRAW AMOUNT: \t";
                cout<<"\n\n\t\tEnter The amount to be withdraw: \t"; cin>>amt;
                int bal=ac.retdeposit()-amt;
                if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
                    cout<<"\n\t\tInsufficience balance";
                else
                    ac.withdraw(amt);
              }
            int pos=(-1)*static_cast<int>(sizeof(ac));
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char *> (&ac), sizeof(Bank));
            cout<<"\n\n\t\tRecord Updated...";
            found=true;
           }
         }
    File.close();
    if(found==false)
        cout<<"\n\n\t\tRecord Not Found...";
}
//introduction function
void intro()
{
    cout<<"\n\t\t\t\tBANKING MANAGEMENT SYSTEM";
    cin.get();
}

/*output:

                                BANKING MANAGEMENT SYSTEM



        ************************MAIN MENU************************
        01. NEW ACCOUNT
        02. DEPOSIT AMOUNT
        03. WITHDRAW AMOUNT
        04. BALANCE ENQUIRY
        05. CLOSE AN ACCOUNT
        06. MODIFY AN ACCOUNT
        07. QUIT
        Enter Your Choice :     1

                Enter The account Number         : 123456789
                Enter The Name of account Holder : Neha Musale
                Enter Type of The account (C/S)  : s
                Enter The Initial amount         : 1000
                Congratulations....Your Account Has Been successfully Created!!!!!



        ************************MAIN MENU************************
        01. NEW ACCOUNT
        02. DEPOSIT AMOUNT
        03. WITHDRAW AMOUNT
        04. BALANCE ENQUIRY
        05. CLOSE AN ACCOUNT
        06. MODIFY AN ACCOUNT
        07. QUIT
        Enter Your Choice :     2

                Enter The account No. : 123456789

                Account No.         : 123456789
                Account Holder Name : Neha Musale
                Type of Account     : S
                Balance amount      : 2800

                TO DEPOSITE AMOUNT:
                        Enter The amount to be deposited:       20000


                Record Updated...



        ************************MAIN MENU************************
        01. NEW ACCOUNT
        02. DEPOSIT AMOUNT
        03. WITHDRAW AMOUNT
        04. BALANCE ENQUIRY
        05. CLOSE AN ACCOUNT
        06. MODIFY AN ACCOUNT
        07. QUIT
        Enter Your Choice :     3
                Enter The account No. : 123456789

                Account No.         : 123456789
                Account Holder Name : Neha Musale
                Type of Account     : S
                Balance amount      : 22800

                TO WITHDRAW AMOUNT:

                Enter The amount to be withdraw:        23000

                Insufficience balance

                Record Updated...



        ************************MAIN MENU************************
        01. NEW ACCOUNT
        02. DEPOSIT AMOUNT
        03. WITHDRAW AMOUNT
        04. BALANCE ENQUIRY
        05. CLOSE AN ACCOUNT
        06. MODIFY AN ACCOUNT
        07. QUIT
        Enter Your Choice :     3
                Enter The account No. : 123456789

                Account No.         : 123456789
                Account Holder Name : Neha Musale
                Type of Account     : S
                Balance amount      : 22800

                TO WITHDRAW AMOUNT:

                Enter The amount to be withdraw:        1000


                Record Updated...



        ************************MAIN MENU************************
        01. NEW ACCOUNT
        02. DEPOSIT AMOUNT
        03. WITHDRAW AMOUNT
        04. BALANCE ENQUIRY
        05. CLOSE AN ACCOUNT
        06. MODIFY AN ACCOUNT
        07. QUIT
        Enter Your Choice :     4
                Enter The account No. : 123456789

                        BALANCE DETAILS

                Account No.         : 123456789
                Account Holder Name : Neha Musale
                Type of Account     : S
                Balance amount      : 21800
                Account No.         : 123456789
                Account Holder Name : Neha Musale
                Type of Account     : S
                Balance amount      : 1000
                Account No.         : 123456789
                Account Holder Name : Neha Musale
                Type of Account     : S
                Balance amount      : 1000



        ************************MAIN MENU************************
        01. NEW ACCOUNT
        02. DEPOSIT AMOUNT
        03. WITHDRAW AMOUNT
        04. BALANCE ENQUIRY
        05. CLOSE AN ACCOUNT
        06. MODIFY AN ACCOUNT
        07. QUIT
        Enter Your Choice :     1

                Enter The account Number         : 147258369
                Enter The Name of account Holder : Srushti Khandade
                Enter Type of The account (C/S)  : c
                Enter The Initial amount         : 1000
                Congratulations....Your Account Has Been successfully Created!!!!!



        ************************MAIN MENU************************
        01. NEW ACCOUNT
        02. DEPOSIT AMOUNT
        03. WITHDRAW AMOUNT
        04. BALANCE ENQUIRY
        05. CLOSE AN ACCOUNT
        06. MODIFY AN ACCOUNT
        07. QUIT
        Enter Your Choice :     2

                Enter The account No. : 147258369

                Account No.         : 147258369
                Account Holder Name : Neha Musale
                Type of Account     : S
                Balance amount      : 1000

                TO DEPOSITE AMOUNT:
                        Enter The amount to be deposited:       14000


                Record Updated...



        ************************MAIN MENU************************
        01. NEW ACCOUNT
        02. DEPOSIT AMOUNT
        03. WITHDRAW AMOUNT
        04. BALANCE ENQUIRY
        05. CLOSE AN ACCOUNT
        06. MODIFY AN ACCOUNT
        07. QUIT
        Enter Your Choice :     3
                Enter The account No. : 147258369

                Account No.         : 147258369
                Account Holder Name : Neha Musale
                Type of Account     : S
                Balance amount      : 15000

                TO WITHDRAW AMOUNT:

                Enter The amount to be withdraw:        1000


                Record Updated...



        ************************MAIN MENU************************
        01. NEW ACCOUNT
        02. DEPOSIT AMOUNT
        03. WITHDRAW AMOUNT
        04. BALANCE ENQUIRY
        05. CLOSE AN ACCOUNT
        06. MODIFY AN ACCOUNT
        07. QUIT
        Enter Your Choice :     4
                Enter The account No. : 147258369

                        BALANCE DETAILS

                Account No.         : 147258369
                Account Holder Name : Neha Musale
                Type of Account     : S
                Balance amount      : 14000
                Account No.         : 147258369
                Account Holder Name : Srushti Khandade
                Type of Account     : C
                Balance amount      : 1000



        ************************MAIN MENU************************
        01. NEW ACCOUNT
        02. DEPOSIT AMOUNT
        03. WITHDRAW AMOUNT
        04. BALANCE ENQUIRY
        05. CLOSE AN ACCOUNT
        06. MODIFY AN ACCOUNT
        07. QUIT
        Enter Your Choice :     5
                Enter The account No. : 147254


        Record Deleted ..



        ************************MAIN MENU************************
        01. NEW ACCOUNT
        02. DEPOSIT AMOUNT
        03. WITHDRAW AMOUNT
        04. BALANCE ENQUIRY
        05. CLOSE AN ACCOUNT
        06. MODIFY AN ACCOUNT
        07. QUIT
        Enter Your Choice :     4
                Enter The account No. : 147258369

                        BALANCE DETAILS

                Account No.         : 147258369
                Account Holder Name : Neha Musale
                Type of Account     : S
                Balance amount      : 14000
                Account No.         : 147258369
                Account Holder Name : Srushti Khandade
                Type of Account     : C
                Balance amount      : 1000



        ************************MAIN MENU************************
        01. NEW ACCOUNT
        02. DEPOSIT AMOUNT
        03. WITHDRAW AMOUNT
        04. BALANCE ENQUIRY
        05. CLOSE AN ACCOUNT
        06. MODIFY AN ACCOUNT
        07. QUIT
        Enter Your Choice :     6
                Enter The account No. : 1472536

                        Record Not Found!!!!Please Try Again...



        ************************MAIN MENU************************
        01. NEW ACCOUNT
        02. DEPOSIT AMOUNT
        03. WITHDRAW AMOUNT
        04. BALANCE ENQUIRY
        05. CLOSE AN ACCOUNT
        06. MODIFY AN ACCOUNT
        07. QUIT
        Enter Your Choice :     7


                Thanks for using Banking Management System!!!!

Process returned 0 (0x0)   execution time : 133.393 s
Press any key to continue.

*/
