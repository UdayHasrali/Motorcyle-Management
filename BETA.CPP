#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<iomanip>
using namespace std;
class bike
{ char bno[6];
  char bname[50];
  char mname[20];
  public:
  void create_bike()
  {
   cout<<"\nNEW BOOK ENTRY...\n";
   cout<<"\nEnter The bike no.";
   cin>>bno;
   cout<<"\n\nEnter The Name of The Bike ";
   gets(bname);
   cout<<"\n\nEnter The model's Name ";
   gets(mname);
   cout<<"\n\n\nBike added..";
  }

  void show_bike()
  {
  cout<<"\nBike no. : "<<bno;
  cout<<"\nBike Name : ";
  puts(bname);
  cout<<"model Name : ";
  puts(mname);
  }

  void modify_bike()
  {
   cout<<"\nBook no. : "<<bno;
   cout<<"\nModify Bike Name : ";
   gets(bname);
   cout<<"\nModify Model Name of bike : ";
   gets(mname);
  }

  char* retbno()
  {return bno;}

  void report()
  {cout<<bno<<setw(30)<<bname<<setw(30)<<mname<<endl;}
  };

class rider
{
  char batno[6];
  char name[20];
  char stbno[6];
  int token;
 public:
  void create_rider()
  {
   system("cls");
   cout<<"\nNEW STUDENT ENTRY...\n";
   cout<<"\nEnter The batch no. ";
   cin>>batno;
   cout<<"\n\nEnter The Name of The Rider";
   gets(name);
   token=0;
   stbno[0]='\0';
   cout<<"\n\nRider Record Created..";
  }

  void show_rider()
  {
   cout<<"\nBatch no. : "<<batno;
   cout<<"\nRider Name : ";
   puts(name);
   cout<<"\nNo of BIKES issued : "<<token;
   if(token==1)
   cout<<"\nBIKE No "<<stbno;
  }

  void modify_rider()
  {
   cout<<"\nBatch no. : "<<batno;
   cout<<"\nModify Rider Name : ";
   gets(name);
  }

  char* retbatno()
  {return batno;}

  char* retstbno()
  {return stbno;}

  int rettoken()
  {return token;}

  void addtoken()
  {token=1;}

  void resettoken()
  {token=0;}

  void getstbno(char t[])
  {strcpy(stbno,t);}

  void report()
   {cout<<"\t"<<batno<<setw(20)<<name<<setw(10)<<token<<endl;}

};

fstream fp,fp1;
bike bk;
rider st;

void write_bike()
{
 char ch;
 fp.open("bikes.dat",ios::out|ios::app);
 do
 {
  system("cls");
  bk.create_bike();
  fp.write((char*)&bk,sizeof(bike));
  cout<<"\n\nDo you want to add more record..(y/n?)";
  cin>>ch;
 }while(ch=='y'||ch=='Y');
 fp.close();
}

void write_rider()
{
 char ch;
 fp.open("riders.dat",ios::out|ios::app);
 do
 {
  st.create_rider();
  fp.write((char*)&st,sizeof(rider));
  cout<<"\n\nDo you want to add more record..(y/n?)";
  cin>>ch;
 }while(ch=='y'||ch=='Y');
 fp.close();
}

void display_spb(char n[])
{
 cout<<"\nBIKE DETAILS\n";
 int flag=0;
 fp.open("bikes.dat",ios::in);
 while(fp.read((char*)&bk,sizeof(bike)))
 {
  if(strcmpi(bk.retbno(),n)==0)
  {
   bk.show_bike();
   flag=1;
  }
 }
 fp.close();
 if(flag==0)
  cout<<"\n\nBike does not exist";
 system("pause");
}

void display_sps(char n[])
{
 cout<<"\nRIDER DETAILS\n";
 int flag=0;
 fp.open("riders.dat",ios::in);
 while(fp.read((char*)&st,sizeof(rider)))
 {
  if((strcmpi(st.retbatno(),n)==0))
  {st.show_rider();
   flag=1;
  }
 }
 fp.close();
 if(flag==0)
 cout<<"\n\nRider does not exist";
 system("pause");
}

void modify_bike()
{
 char n[6];
 int found=0;
 system("cls");
 cout<<"\n\n\tMODIFY BIKE RECORD.... ";
 cout<<"\n\n\tEnter The bike no. of The bike";
 cin>>n;
 fp.open("bikes.dat",ios::in|ios::out);
 while(fp.read((char*)&bk,sizeof(bike)) && found==0)
 {if(strcmpi(bk.retbno(),n)==0)
  {
   bk.show_bike();
   cout<<"\nEnter The New Details of bike"<<endl;
   bk.modify_bike();
   int pos=int(-1*sizeof(bk));
   fp.seekp(pos,ios::cur);
   fp.write((char*)&bk,sizeof(bike));
   cout<<"\n\n\t Record Updated";
   found=1;
  }
 }
 fp.close();
 if(found==0)
  cout<<"\n\n Record Not Found ";
 system("pause");
}


void modify_rider()
{
 char n[6];
 int found=0;
 system("cls");
 cout<<"\n\n\tMODIFY RIDER RECORD... ";
 cout<<"\n\n\tEnter The batch no. of The rider";
 cin>>n;
 fp.open("riders.dat",ios::in|ios::out);
 while(fp.read((char*)&st,sizeof(rider)) && found==0)
 {
  if(strcmpi(st.retbatno(),n)==0)
  {
   st.show_rider();
   cout<<"\nEnter The New Details of rider"<<endl;
   st.modify_rider();
   int pos=int(-1*sizeof(st));
   fp.seekp(pos,ios::cur);
   fp.write((char*)&st,sizeof(rider));
   cout<<"\n\n\t Record Updated";
   found=1;
  }
 }
 fp.close();
 if(found==0)
  cout<<"\n\n Record Not Found ";
 system("pause");
}

void delete_rider()
{
 char n[6];
 int flag=0;
 system("cls");
 cout<<"\n\n\n\tDELETE RIDER...";
 cout<<"\n\nEnter The BATCH no. of the RIDER You Want To Delete : ";
 cin>>n;
 fp.open("riders.dat",ios::in|ios::out);
 fstream fp2;
 fp2.open("Temp.dat",ios::out);
 fp.seekg(0,ios::beg);
 while(fp.read((char*)&st,sizeof(rider)))
 {
  if(strcmpi(st.retbatno(),n)!=0)
   fp2.write((char*)&st,sizeof(rider));
  else
   flag=1;
 }
 fp2.close();
 fp.close();
 remove("riders.dat");
 rename("Temp.dat","riders.dat");
 if(flag==1)
  cout<<"\n\n\tRecord Deleted ..";
 else
  cout<<"\n\nRecord not found";
 system("pause");
}


void delete_bike()
{
 char n[6];
 system("cls");
 cout<<"\n\n\n\tDELETE BIKE ...";
 cout<<"\n\nEnter The Bike no. of the Bike You Want To Delete : ";
 cout<<"\n CAUTION!!!!!! DO NOT GIVE THE BIKE NUMBER WHICH HAS BEEN ISSUED :";
 cin>>n;
 fp.open("bike.dat",ios::in|ios::out);
 fstream fp2;
 fp2.open("Temp.dat",ios::out);
 fp.seekg(0,ios::beg);
 while(fp.read((char*)&bk,sizeof(bike)))
 {
  if(strcmpi(bk.retbno(),n)!=0)
   fp2.write((char*)&bk,sizeof(bike));
 }
 fp2.close();
 fp.close();
 remove("bike.dat");
 rename("Temp.dat","bike.dat");
 cout<<"\n\n\tRecord Deleted ..";

 system("pause");
}

void display_alls()
{
system("cls");
 fp.open("riders.dat",ios::in);
 if(!fp)
 {
  cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
  system("pause");
  return;
 }
 cout<<"\n\n\t\tRIDER LIST\n\n";
 cout<<"==================================================================\n";
 cout<<"\tBATCH No."<<setw(10)<<"Name"<<setw(20)<<"Bike Issued\n";
 cout<<"==================================================================\n";
 while(fp.read((char*)&st,sizeof(rider)))
 {st.report();
 }
 fp.close();
 system("pause");
}

void display_allb()
{
 system("cls");
 fp.open("bikes.dat",ios::in);
 if(!fp)
 {
  cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
  system("pause");
  return;
 }
 cout<<"\n\n\t\tBike LIST\n\n";
 cout<<"=========================================================================\n";
 cout<<"Bike Number"<<setw(20)<<"Bike Name"<<setw(25)<<"Model\n";
 cout<<"=========================================================================\n";
 while(fp.read((char*)&bk,sizeof(bike)))
 {
  bk.report();
 }
 fp.close();
	system("pause");
}

void bike_issue()
{
 char sn[6],bn[6];
 int found=0,flag=0;
 system("cls");
 cout<<"\n\nBIKE ISSUE ...";
 cout<<"\n\n\tEnter The rider's batch no. THE CODE MUST BE UNIQUE :";
 cin>>sn;
 fp.open("riders.dat",ios::in|ios::out);
 fp1.open("bikes.dat",ios::in|ios::out);
 while(fp.read((char*)&st,sizeof(rider)) && found==0)
 {
  if(strcmpi(st.retbatno(),sn)==0)
  {
   found=1;
   if(st.rettoken()==0)
   {
    cout<<"\n\n\tEnter the bike no. ";
    cin>>bn;
    while(fp1.read((char*)&bk,sizeof(bike))&& flag==0)
    {
     if(strcmpi(bk.retbno(),bn)==0)
     {
      bk.show_bike();
      flag=1;
      st.addtoken();
      st.getstbno(bk.retbno());
      int pos=int(-1*sizeof(st));
      fp.seekp(pos,ios::cur);
      fp.write((char*)&st,sizeof(rider));
      cout<<"\n\n\t Bike issued successfully\n\nPlease Note: Write the current date 						in backside of your bike and submit within 15 days fine Rs. 100 for each day 							after 15 days period";
     }
    }
    if(flag==0)
     cout<<"Bike no does not exist";
   }
   else
    cout<<"You have not returned the last bike ";
  }
 }
 if(found==0)
  cout<<"Rider record not exist...";
 system("cls");
 fp.close();
 fp1.close();
}

void bike_deposit()
{
 char sn[6],bn[6];
 int found=0,flag=0,day,fine;
 system("cls");
 cout<<"\n\nBOOK DEPOSIT ...";
 cout<<"\n\n\tEnter The rider’s admission no.";
 cin>>sn;
 fp.open("riders.dat",ios::in|ios::out);
 fp1.open("bikes.dat",ios::in|ios::out);
 while(fp.read((char*)&st,sizeof(rider)) && found==0)
 {
  if(strcmpi(st.retbatno(),sn)==0)
  {
   found=1;
   if(st.rettoken()==1)
   {
    while(fp1.read((char*)&bk,sizeof(bike))&& flag==0)
    {
     if(strcmpi(bk.retbno(),st.retstbno())==0)
     {
      bk.show_bike();
      flag=1;
      cout<<"\n\nBook deposited in no. of days";
      cin>>day;
      if(day>15)
      {
       fine=(day-15)*100;
       cout<<"\n\nFine has to deposited Rs. "<<fine;
      }
      st.resettoken();
      int pos=int(-1*sizeof(st));
      fp.seekp(pos,ios::cur);
      fp.write((char*)&st,sizeof(rider));
      cout<<"\n\n\t Bike deposited successfully";
     }
    }
    if(flag==0)
     cout<<"Bike no does not exist";
   }
   else
    cout<<"No bike is issued..please check!!";
  }
 }
 if(found==0)
 cout<<"rider record not exist...";
 system("pause");
 fp.close();
 fp1.close();
}

void intro()
{
 system("cls");
 cout<<"\t\t"<<"STORM RIDERS BIKE RENTING AGENCY"<<endl;
 cout<<"\n\t\t"<<"MADE BY : DINESH KUMAR"<<endl;
 cout<<"\t\t\t  "<<"NITHYA GANESH"<<endl;
 cout<<"\t\t\t  "<<"PRISOJ SURENDRAN"<<endl;
 cout<<"\t\t\t  "<<"SUSHIL KUMAR";
 system("cls");
}

void admin_menu()
{
 system("cls");
 int ch2;
 cout<<"\n\n\n\tADMINISTRATOR MENU";
 cout<<"\n\n\t1.CREATE RIDER RECORD";
 cout<<"\n\n\t2.DISPLAY ALL RIDER RECORD";
 cout<<"\n\n\t3.DISPLAY SPECIFIC RIDER RECORD ";
 cout<<"\n\n\t4.MODIFY RIDER RECORD";
 cout<<"\n\n\t5.DELETE RIDER RECORD";
 cout<<"\n\n\t6.CREATE BIKE ";
 cout<<"\n\n\t7.DISPLAY ALL BIKE ";
 cout<<"\n\n\t8.DISPLAY SPECIFIC BIKE ";
 cout<<"\n\n\t9.MODIFY BIKE ";
 cout<<"\n\n\t10.DELETE BIKE ";
 cout<<"\n\n\t11.BACK TO MAIN MENU";
 cout<<"\n\n\tPlease Enter Your Choice (1-11) ";
 cin>>ch2;
 switch(ch2)
 {
  case 1:system("cls");
	 write_rider();break;
  case 2:display_alls();break;
  case 3:{char num[6];
	  system("cls");
	  cout<<"\n\n\tPlease Enter The Admission No. ";
	  cin>>num;
	  display_sps(num);
	  break;
	 }
  case 4:modify_rider();break;
  case 5:delete_rider();break;
  case 6:system("cls");
	 write_bike();break;
  case 7:display_allb();break;
  case 8:{char num[6];
	  system("cls");
	  cout<<"\n\n\tPlease Enter The book No. ";
	  cin>>num;
	  display_spb(num);
	  break;
	 }
  case 9:modify_bike();break;
  case 10:delete_bike();break;
  case 11:return;
  default:cout<<"\a";
 }
 admin_menu();
}

int main()
{
 int ch;
 intro();
 do
 {
  system("cls");;
  cout<<"\n\n\n\tMAIN MENU";
  cout<<"\n\n\t01. BIKE ISSUE";
  cout<<"\n\n\t02. BIKE DEPOSIT";
  cout<<"\n\n\t03. ADMINISTRATOR MENU";
  cout<<"\n\n\t04. EXIT";
  cout<<"\n\n\tPlease Select Your Option (1-4) ";
  cin>>ch;
  switch(ch)
  {
   case 1:system("cls");
	  bike_issue();
	  break;
   case 2:bike_deposit();
	  break;
   case 3:admin_menu();
	  break;
   case 4:return 0;
   default :cout<<"\a";
  }
  }while(ch!=4);
  main();
}
