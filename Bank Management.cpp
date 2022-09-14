/*Bank Management System contains following 
---------------------------------------Classes----------------------------------------
   1 Account--
      Data Members--->name,account_no,typeofaccount_,balance_amt,phone_no,time_t
      Member functions--->get_name,get_account_no,get_typeofamount_,get_balance_amt,get_phone_no,info
      
   2  Transaction--
      Data Members--->acc_no,transaction_id,bal_before,bal_after,time_t
      Member functions--->get_transaction_id,get_bal_before,get_bal_after,startTransaction,deposit,withdraw
	  
   3  Employee--
      Member functions--->create_account,display_list,delete_account,update_balance,display_last_entry,search,
                          retrieveAndUpdateName, retrieveAndUpdateAddress,retrieveBalanceAmt,accAndTrans,
                          displayDetailsAccHolder
	  
   4 Operations--
      Member function--->operate  
	  
---------------------------------------Binary Files------------------------------------
    1 AccFile.dat--->Used to store the objects of Account class
    2 Transaction.dat--->Used to store the objects of Transaction class
    3 New.dat--->Temporary file in this project to store the objects ,further on remamed from New.dat to AccFile.dat
	  */


#include<bits/stdc++.h>
using namespace std;
//Account class---used to store the data of customer details which is entered by employee of the bank
class Account{
	char name[40];
	int  account_no;
	char typeofaccount_[20];
	int balance_amt;
	long long phone_no;
    char address[100];
	public:
		time_t now = time(0);
        tm *ltm = localtime(&now);//for current time
        
        //returns the name of the account holder
		char* get_name(){
			return name;
		}
		
		//returns the account_no of the account holder
		int get_account_no(){
			return account_no;
		}
		
		//returns the type of account of the account holder
		char* get_typeofaccount_(){
			return typeofaccount_;
		}
		
		//returns the balance amt of the account holder
		int get_balance_amt(){
			return balance_amt;
		}
		
		//returns the phone number of the account holder
		long long get_phone_no(){
			return phone_no;
		}
		
		//returns the address of the account holder
		char* get_address(){
		   return address;
		}
		
		//used to set the balance amt on transaction of the account holder
		void set_balance_amt(int amt){
			balance_amt=amt;
		}
		
		//used to set the name
		void set_name(char n[]){
		    strcpy(name,n);
		}
		
		//used to set the address
		void set_address(char add[]){
		    strcpy(address,add);
		}
		
	    //Info--Used to enter all the details of account holder
		void info(){
			cout<<"Please enter your account_no:";
		    cin>>account_no;
		    
			cout<<"Please enter your name:";
			cin.ignore();
			cin.getline(name,20);
			
			cout<<"Please enter the phone number:";
			cin>>phone_no;
			
			cout<<"Please enter type of account:";
	        cin.ignore();
			cin.getline(typeofaccount_,20);
	        
	    	cout<<"Please enter your money to be deposited:";
			cin>>balance_amt;
			
			cout<<"Please enter address:";
			cin.ignore();
			cin.getline(address,100);
		}	
};
  
//Transaction---used to store the details of deposit and withdrawal from the particular account by the employee
class Transaction{
	//Used private acccess specifier for secure transaction
    int acc_no;
    long long transaction_id;
    int bal_before;
    int bal_after;
    
    public:
    time_t now = time(0);
    tm *ltm = localtime(&now);//for current object
    
    //returns transaction_id of the particular transaction
    long long get_transaction_id(){
        return transaction_id;
    }
    
    //returns balance before the transaction of the account holder
    int get_bal_before(){
      return bal_before;  
    }
    
    //returns balance after the transaction of the account holder
    int get_bal_after(){
        return bal_after;
    }
    
    //returns account number of the transaction of the account holder
    int get_acc_no(){
        return acc_no;
    }
    
    //sets the transaction_id using static variable i
    void  startTransaction(){
        static int i=234;
        transaction_id=i;
        i++;
    }
    
     /*Deposit--Gets the value of data member(acc_no) and (bal_before) from Account object ,
	 then sets the value for data member(bal_after)  by adding  amt with bal_before */
    void deposit(Account a,int amt){
        acc_no=a.get_account_no();
        bal_before=a.get_balance_amt();
        int balance=a.get_balance_amt()+amt;
        bal_after=balance;
        
     }
     
     /*Withdraw--Gets the value of data member(acc_no) and (bal_before) from Account object ,
	 then sets the value for data member(bal_after) by subtracting bal_before with amt */
    void withdraw(Account a,int amt){
        acc_no=a.get_account_no();
        bal_before=a.get_balance_amt();
        int balance=a.get_balance_amt()-amt;
        bal_after=balance;
    }
};


//Defines the set of functions which employee of bank can perform and it is kept under protected section
class Employee{

	protected:
		
		//Add new customers to the bank who become an account holder in the Accfile.dat.
		void create_account(){
			
	        ofstream a1("AccFile.dat",ios::binary|ios::app);//Created object of ofstream
			Account a;                                      //Created object of Account class
		    a.info();                                       //Call to member function(info) of account class
			a1.write((char*)&a,sizeof(a));                  //Writing object of class into binary file
			a1.close();                                    //Closing of the file
			cout<<"New account created"<<endl;
		}
	
		//Display a list of all the account holders of the bank along with their account numbers and balance
		void display_list(){
		
			ifstream acc_file;                                  //Created object of ifstream
			Account a;                                         //Created object of Account class
		    acc_file.open("AccFile.dat",ios::binary | ios::in);//Opening of file(AccountFile)
		    if(!acc_file){                                    //if file is unable to open
				cout<<"Unable to open"<<endl;
			}
		    else{
		    	acc_file.read((char *)&a,sizeof(a));          //Reading the object from file
		       while(!acc_file.eof()){ 
		       
		        //Printing the account_no and balance of all account holders
		      	cout<<"Account_no:"<<a.get_account_no()<<endl;
		        cout<<"Balance Amount:"<<a.get_balance_amt()<<endl;
		        cout<<"-------------------"<<endl;
				acc_file.read((char*)&a,sizeof(a));          //Reading the object from file
		     }
		    acc_file.close();                               //Closing the file
	   	}
	}
	//Delete the information related to the account holder from the customer data file
	void delete_account(){
		cout<<"Enter the account_no to be deleted:"<<endl;
		int acc_no;
		cin>>acc_no;                                                //Account no from the employee to be deleted
		fstream acc_file;                                          //Created object of fstream
		ofstream new_file;                                         //Created object of ofstream class
		Account a;                                                //Created object of account class
		acc_file.open("AccFile.dat",ios::binary | ios::in );	    //Opening of AccFile.dat in read mode
		new_file.open("New.dat",ios::binary|ios::out);         	  //Opening of New.dat in writing mode
	   	if(!acc_file){                                          //in case unable to open AccFile.dat
				cout<<"Unable to open"<<endl;
			}
		 else{
		    bool found=false;                                    //to check whether account_no exists or not
			acc_file.read((char *)&a,sizeof(a));                  //Reading of object of account class from file
		     while(!acc_file.eof()){ 
		        if(acc_no!=a.get_account_no())
		        {
		            new_file.write((char*)&a,sizeof(a));        //Writing of the object of account class into the file
				}
				else{
				    found=true;
				    cout<<"Account deleted from bank"<<endl;
				}
				acc_file.read((char*)&a,sizeof(a));           //Reading of object of account class from file
		     }
		     if(!found){
		         cout<<"Account doesn't exists"<<endl;
		     }
		    //Closing both files
		    acc_file.close();                                 
		    new_file.close();                                
		    remove("AccFile.dat");                              //Deleting AccFile.dat  
		    rename("New.dat","AccFile.dat");                     //Renaming the New.dat to AccFile.dat
	   	}
	}
	
	//Update the balance after customer has performed a deposited/withdrawn in the bank
    void update_balance(){
    	cout<<"Enter the acc_no in which account holder wants to deposit/withdraw:";
		int acc_no;
		cin>>acc_no;
		fstream acc_file;                                         //Created object of fstream
		ofstream new_file;                                        //Created object of ofstream
		Account a;                                                //Created object of Account class
		//Opening of AccFile and New files
		acc_file.open("AccFile.dat",ios::binary | ios::in );
		new_file.open("New.dat",ios::binary|ios::out);
		if(!acc_file){
				cout<<"Unable to open"<<endl;
			}
		    else{
		       bool found=false;                                   //to check whether account_no exists or not
		    	acc_file.read((char *)&a,sizeof(a));              //Reading the object of class Account from the file
		       while(!acc_file.eof()){ 
		       //On finding the account,updating the balance amount
		        if(acc_no==a.get_account_no())
		        {
		            found=true;
		            Transaction t;                                    //Created object of transaction class
	             	ofstream trans;                                   //Created object of fstream
	             	trans.open("Transaction.dat",ios::binary|ios::app);//Opened file in append mode
		           	cout<<"Amount to be deposited or withdraw:";
	            	int amt;
	             	cin>>amt;
		            cout<<"Do you want to deposit/withdraw?(d/w)";
		            char ch;
		            cin>>ch;
		            if(ch=='d'){                                   //to deposit money
		               t.startTransaction();                       //call to startTransaction function of transaction class
		               t.deposit(a,amt);                           //call to deposit function of transaction class
		               a.set_balance_amt(t.get_bal_after());        //call to set_balance_amt function of account class
		               trans.write((char*)&t,sizeof(t));            //writing in Transaction.dat file
		               cout<<"Amt deposited"<<endl;
		            }
		            else{
		                if(amt<=a.get_balance_amt()){               //to withdraw money
		                    t.startTransaction();                  //call to startTransaction function of transaction class
		                   t.withdraw(a,amt);                      //call to withdraw function of transaction class
		                   a.set_balance_amt(t.get_bal_after());   //call to set_balance_amt function of account class
		                   trans.write((char*)&t,sizeof(t));        //writing in Transaction.dat file
		                   cout<<"Amt withdrawn"<<endl;
		                }
		                else{
		                    cout<<"You have low balance"<<endl;         //amt to be withdrwan is less than balance 
		                    
		                }
		            }
		            trans.close();                                    //closing the file
				}
				new_file.write((char*)&a,sizeof(a));                 //Writing the object of class Account into the file
				acc_file.read((char*)&a,sizeof(a));                  //Reading the object of class Account from the file
		     }
		      if(!found){                                           //Unable to find amount
		         cout<<"Account doesn't exists"<<endl;
		     }
		    //Closing of both files
		    acc_file.close();
		    new_file.close();
		    remove("AccFile.dat");                                   //Removing AccFile 
		    rename("New.dat","AccFile.dat");                         //Renaming the New.dat to AccFile.dat
	   	}
	}
	
   //Display the account number of the last entry
     void display_last_entry(){
     	    ifstream acc_file;                                       //Created object of ifstream
			Account a;                                               //Created objects of class Account 
			Account pre;                                            //Used to store previous object in the file
		    acc_file.open("AccFile.dat",ios::binary | ios::in);     //Opened the file in read mode
			if(!acc_file){
				cout<<"Unable to open"<<endl;
			}
		    else{
			acc_file.read((char *)&a,sizeof(a));                   //Reading the object from file
		     while(!acc_file.eof()){ 
		      	pre=a;
				acc_file.read((char*)&a,sizeof(a));                //Reading the object from file
		     }
		     cout<<"---------Last entry details--------"<<endl;
		     cout<<"Account_no:"<<pre.get_account_no()<<endl;
		     cout<<"Balance Amount:"<<pre.get_balance_amt()<<endl;
		     cout<<"Name:"<<pre.get_name()<<endl;
		     cout<<"Phone_No:"<<pre.get_phone_no()<<endl;
		     cout<<"Address:"<<pre.get_address()<<endl;
		     cout<<"-------------------"<<endl;
		    acc_file.close();                                      //Closing of the file
	   	}
	 }
	 
	 
	 //Check whether an account exists or not
	 void search(){
			ifstream acc_file;                                  //Created object of ifstream
			Account a;                                          //Created object of class Account
		    acc_file.open("AccFile.dat",ios::binary | ios::in); //Opening the file in read mode
			if(!acc_file){
				cout<<"Unable to open"<<endl;
			}
		    else{
		    int i=0;
		    bool found=false;
		    cout<<"Search the account_no:"<<endl;
		    int acc_no;
		    cin>>acc_no;
			acc_file.read((char *)&a,sizeof(a));                 //Reading the object from file to find the particular account
		     while(!acc_file.eof()){ 
		      	if(a.get_account_no()==acc_no){                  //account_no found
		      		found=true;
		      		break;
				  }
				 acc_file.read((char*)&a,sizeof(a));             //Reading the object from file 
		     }
		     if(found){
		     	cout<<"Account exists"<<endl;
			 }
			 else{
			 	cout<<"Account doesn't exist"<<endl;
			 }
		    acc_file.close();                                  //Closing of the file
	   	}
	}
	
	
	//retrieve/update the name of the account holder
	void retrieveAndUpdateAddress(){
    	cout<<"Enter the acc_no in which account holder wants update name:";
		int acc_no;
		cin>>acc_no;
		fstream acc_file;                                    	//Created object of fstream
		ofstream new_file;                                      //Created object of ofstream
		Account a;                                             //Created object of Account class
		//Opening of AccFile and New files 
		acc_file.open("AccFile.dat",ios::binary | ios::in );
		new_file.open("New.dat",ios::binary|ios::out);
		if(!acc_file){
				cout<<"Unable to open"<<endl;
			}
		    else{
		     bool found=true;
			 acc_file.read((char *)&a,sizeof(a));               //Reading the object of class Account from the file
		     while(!acc_file.eof()){ 
		      //On finding the account,updating the balance amount
		        if(acc_no==a.get_account_no())
		        {
		           cout<<"Account holder address:"<<a.get_address()<<endl;
		           char add[100];
		           cout<<"Enter the account_holder new address:";
		           cin.ignore();
		           cin.getline(add,100);
		           a.set_address(add);
		           cout<<"Address updated"<<endl;
				}
				new_file.write((char*)&a,sizeof(a));          	//Writing the object of class Account into the file
				acc_file.read((char*)&a,sizeof(a));             //Reading the object of class Account from the file
		     }
		      if(!found){
		         cout<<"Account doesn't exists"<<endl;
		     }
		     //Closing of both files
		    acc_file.close();                                   
		    new_file.close();                                   
		    remove("AccFile.dat");                                 //Removing AccFile 
		    rename("New.dat","AccFile.dat");                     //Renaming the New.dat to AccFile.dat
	   	}
	}
	
	
	
	//retrieve/updated the address of the account holder
	void retrieveAndUpdateName(){
    	cout<<"Enter the acc_no in which account holder wants update address:";
		int acc_no;
		cin>>acc_no;
		fstream acc_file;                                       //Created object of fstream
		ofstream new_file;                                      //Created object of ofstream
		Account a;                                              //Created object of Account class
		acc_file.open("AccFile.dat",ios::binary | ios::in );    //Opening of AccFile and New files
		new_file.open("New.dat",ios::binary|ios::out);
		if(!acc_file){
				cout<<"Unable to open"<<endl;
			}
		    else{
		       bool found=false; 
			   acc_file.read((char *)&a,sizeof(a));            //Reading the object of class Account from the file
		       while(!acc_file.eof()){ 
		      //On finding the account,updating the balance amount
		        if(acc_no==a.get_account_no())
		        {  
		           found=true;
		           char n[100];
		           cout<<"Existing Account holder's name:"<<a.get_name()<<endl;
		           cout<<"Enter the account_holder new name:";
		           cin.ignore();
		           cin.getline(n,100);
		           a.set_name(n);
		           cout<<"Name updated"<<endl;
				}
				new_file.write((char*)&a,sizeof(a));              //Writing the object of class Account into the file
				acc_file.read((char*)&a,sizeof(a));               //Reading the object of class Account from the file
		     }
		      if(!found){
		         cout<<"Account doesn't exists"<<endl;
		     }
		     //Closing of both files
		     acc_file.close();
		     new_file.close();
		     remove("AccFile.dat");                                //Removing AccFile 
		     rename("New.dat","AccFile.dat");                       //Renaming the New.dat to AccFile.dat
	   	}
	}
	//retrieve the balance of the account holder
	void retrieveBalanceAmt(){
			ifstream acc_file;                                     //Created object of ifstream
			Account a;                                             //Created object of Account class
		    acc_file.open("AccFile.dat",ios::binary | ios::in);    //Opening of file(AccountFile)
		    cout<<"Enter the acc_no in which account holder wants update address:";
	    	int acc_no;
	    	cin>>acc_no;
			if(!acc_file){                                        //if file is unable to open
				cout<<"Unable to open"<<endl;
			}
		    else{
		       bool found=false;
			   acc_file.read((char *)&a,sizeof(a));              //Reading the object from file
		       while(!acc_file.eof()){                  
		       if(a.get_account_no()==acc_no){
		        cout<<"Balance Amount:"<<a.get_balance_amt()<<endl;
		        found=true;
		        break;
		       }
				acc_file.read((char*)&a,sizeof(a));              //Reading the object from file
		     }
		      if(!found){
		         cout<<"Account doesn't exists"<<endl;
		     }
		    acc_file.close();                                      //Closing the file
	   	} 
	}
	
	
	//Transaction details along with the account information
    void accAndTrans(){
         //Created objects of ifstream
     	    ifstream acc_file;
     	    ifstream trans_file;
			Account a;                                           //Created object of class Account 
			Transaction t;                                        //Created object of class Transaction
			int accNo;
			bool found=false;
		    cout<<"Enter the account_no:";
		    cin>>accNo;
		    //Open files in read mode
		    acc_file.open("AccFile.dat",ios::binary | ios::in);     
		    trans_file.open("Transaction.dat",ios::binary | ios::in);
			if(!acc_file){
				cout<<"Unable to open"<<endl;
			}
		    else{
		     acc_file.read((char *)&a,sizeof(a));                   //Reading the object from file
		     while(!acc_file.eof()){ 
		        if(accNo==a.get_account_no()){                      //when accNo is found
		            found=true;
		            cout<<"Account_no:"<<a.get_account_no()<<endl;
		            cout<<"Balance Amount:"<<a.get_balance_amt()<<endl;
		            cout<<"Name:"<<a.get_name()<<endl;
		            cout<<"Phone_No:"<<a.get_phone_no()<<endl;
		            cout<<"Address:"<<a.get_address()<<endl;
		        }
				acc_file.read((char*)&a,sizeof(a));                 //Reading the file
		     }
		     if(!found){                            
		         cout<<"Account no doesn't exist"<<endl;            
		         return;
		     }
		    acc_file.close();                                       //Closing of the file
	   	} 
	   	if(!trans_file){
				cout<<"Unable to open"<<endl;
			}
		    else{
		    
			 trans_file.read((char *)&t,sizeof(t));               //Reading the object from file
		     while(!trans_file.eof()){ 
		        if(accNo==t.get_acc_no()){                         //account_no found
		            found=true;
		            //Displaying the details of the transaction
		            cout<<"Transaction id:"<<t.get_transaction_id()<<endl;
		            cout<<"Balance Amount Before Transaction:"<<t.get_bal_before()<<endl;
		            cout<<"Balance Amount After Transaction:"<<t.get_bal_after()<<endl;
		            cout <<"Year:" << 1900 + t.ltm->tm_year<<endl;
		            cout <<"Month: "<< 1 + t.ltm->tm_mon<< endl;
                    cout <<"Day: "<< t.ltm->tm_mday << endl;
		            cout<<"Time:"<< t.ltm->tm_hour << ":"<<t.ltm->tm_min<<":"<<t.ltm->tm_sec<<endl;
		            
		        }
				trans_file.read((char*)&t,sizeof(t));              //Reading the file
		     }
		    trans_file.close();                                   //Closing of the file
	   	}
    }
    
    //Displays all the information related to an account holder from the customer file on the basis of specified account number
    void displayDetailsAccHolder(){
     	    ifstream acc_file;                                   //Created object of ifstream
			Account a;                                           //Created objects of class Account 
			int accNo;
			bool found=false;                                    //to check whether the account exist or not
		    cout<<"Enter the account_no:";
		    cin>>accNo;
		    acc_file.open("AccFile.dat",ios::binary | ios::in);      //opening the file in read mode
			if(!acc_file){
				cout<<"Unable to open"<<endl;
			}
		    else{
		   	 acc_file.read((char *)&a,sizeof(a));                   //Reading the object from file
		     while(!acc_file.eof()){ 
		        if(accNo==a.get_account_no()){                     //when account_no found
		            found=true;
		            //Displaying the details of account holder
		            cout<<"Account_no:"<<a.get_account_no()<<endl;
		            cout<<"Balance Amount:"<<a.get_balance_amt()<<endl;
		            cout<<"Name:"<<a.get_name()<<endl;
		            cout<<"Phone_No:"<<a.get_phone_no()<<endl;
		            cout<<"Address:"<<a.get_address()<<endl;
		        }
				acc_file.read((char*)&a,sizeof(a));           //Reading the object from file
		     }
		     if(!found){                                      //account no not found
		         cout<<"Account no doesn't exist"<<endl;
		         return;
		     }
		    acc_file.close();                                 //Closing of the file
	   	}
    }
    
}; 

/*Operations class contains member function(operate) to ask the employee which operation has to perform.
This class inherit Employee class and makes Employee's function as private so that other class can't inherit it*/
class Operations:private Employee{
    public:
     void operate(){
     	//Set of functions
         cout<<"-----------------Menu----------------------"<<endl;
         cout<<"1 Add new customers to the bank who become an account holder"<<endl;
         cout<<"2 Display a list of all the account holders of the bank along with their account numbers and balance"<<endl;
         cout<<"3 Delete the information related to the account holder from the customer data file"<<endl;
         cout<<"4 Update the balance after customer has performed a deposit or withdraw transaction"<<endl;
         cout<<"5 Display the account number of the last entry"<<endl;
         cout<<"6 Check whether an account exists or not"<<endl;
         cout<<"7 Retrieve/updated the name of the account holder"<<endl;
         cout<<"8 Retrieve/updated the address of the account holder"<<endl;
         cout<<"9 Retrieve the balance of the account holder"<<endl;
         cout<<"10 Transaction details along with the account information"<<endl;
         cout<<"11 Displays all the information related to an account holder from the customer file on the basis of specified account number"<<endl;
         cout<<"12 Exit"<<endl;
		 cout<<"----------------------------------------------"<<endl;
         int option;
         do{
             
             cout<<"Enter your choice:";
             cin>>option;
             switch(option){
               case 1:
                     create_account();
                     cout<<"-----------------"<<endl;
                     break;
               case 2:
                     display_list();      
                     cout<<"-----------------"<<endl;
                     break;
               case 3:
                    delete_account();
                    cout<<"-----------------"<<endl;
                    break;
               case 4:
                    update_balance();
                    cout<<"-----------------"<<endl;
                     break;
               case 5:
                   display_last_entry();
                   cout<<"-----------------"<<endl;
                     break;
               case 6:
                   search();
                   cout<<"-----------------"<<endl;
                     break;
               case 7:
                   retrieveAndUpdateName();
                   cout<<"-----------------"<<endl;
                     break;
               case  8:
                   retrieveAndUpdateAddress();
                   cout<<"-----------------"<<endl;
                  break;
               case  9:
                   retrieveBalanceAmt();
                   cout<<"-----------------"<<endl;
                     break;
               case 10:
                    accAndTrans();
                    cout<<"-----------------"<<endl;
                    break;
               case 11:
                    displayDetailsAccHolder();
                    cout<<"-----------------"<<endl;
                    break;
               case 12:
                  exit(0);

             }
             
         }
         while(option);

     }
};

int main(){
        Operations o;
        o.operate();
		return 0;
}
