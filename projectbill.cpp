#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<iomanip>
#include<process.h>
#include<fstream>
#include<windows.h>
//HEADER FILES USED
using namespace std;
void admin_menu();
void menu();
class book 			//*****CLASS STARTS*****//
{
	int pno;
	char name[50];
	float price,qty,tax,dis;
	public:
	book()
	{
		price=qty=tax=dis=0;
	}
void create_book() 	 
//****FUNCTION TO CREATE BOOK RECORDS****//
{
	system("CLS");
	cout<<"\nPlease Enter The book No. of The book:- ";
	cin>>pno;
	cout<<"\n\nPlease Enter The Name of The book:- ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nPlease Enter The Price of The book:- ";
	cin>>price;
	cout<<"\nPlease Enter The Discount (%):- ";
	cin>>dis;	}
   	void show_book()     
 		//****FUNCTION TO SHOW BOOK RECORD****//
	{
		system("CLS");
		cout<<"\nThe book No. of The book:- "<<pno;
		cout<<"\nThe Name of The book:- ";
	 	puts(name);
		cout<<"\nThe Price of The book:-"<<price;
    		cout<<"\nDiscount:-"<<dis;
        }
    int retpno()
		{return pno;}
	  int retqty()
		{return qty;}
    	 float retprice()
		{return price;}
	char* retname()
	    {return name;}
	int retdis()
	    {return dis;}
void add_qty(int n)
{
	qty+=n;
}
int red_qty(int n)
{
	qty-=n;
 }
};   
      //****CLASS ENDS HERE****//
void gotoxy(int x,int y)  			//****GOTOXY FUNCTION****//
{
	COORD coord;
	coord.X=x;
	coord.Y=y;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void splash()  			//****MAIN PAGE****//
{
     	system("COLOR fc");
gotoxy(10,8);
	 cout<<"\t\t    MAMS BOOK DEPOT\n";
     	Sleep(500);
	cout<<"\t\t\t\tBILLING\n";
     	Sleep(500);
	 cout<<"\t\t\tCOMPUTER SCIENCE PROJECT\n";
	 Sleep(500);
	 cout<<"\t\t\tMade by :- \n\t\t\t->PRIYANKA DARYANI(25)\n\t\t\t->DEEPANSHI GUPTA(10)";
    	 Sleep(500);
	 cout<<"\n\t\t\tMAHARAJA AGRASEN MODEL SCHOOL\n";
     	getch();
}
struct pur_book{  //****STRUCTURE STARTS****//
	int bcode;
	char bname[40];
   	 int qty_reqd;
	int bprice;
	float bdis;
	float bamt;
};
//****STRUCTURE ENDS****//
void get_values(pur_book &b) 		 
//****FUNCTION TO PURCHASE BOOKS****//
{
    fstream fp;
    book pr;
    fp.open("Shop.dat",ios::in|ios::out|ios::binary);
    fp.seekg(0);
    int flag=0;
    while(fp.read((char*)&pr,sizeof(book)))
	{
		if(pr.retpno()!=b.bcode)
  		{
		flag=-1;
		}
		 else
          if(pr.retqty()<b.qty_reqd)
		{
			cout<<"Invalid Quantity";
			return;
		}
		else
		{  
if((pr.retpno()==b.bcode)&&(pr.retqty()>=b.qty_reqd))
	{
                     strcpy(b.bname,pr.retname());
                	b.bprice=pr.retprice();
		b.bdis=pr.retdis();
		b.bamt=pr.retprice()*b.qty_reqd;
		b.bamt= b.bamt- (b.bamt*float(b.bdis/100));
		pr.red_qty(b.qty_reqd);
		int p=fp.tellg();
		fp.seekg(p-sizeof(pr));
		fp.write((char*)&pr,sizeof(pr));
	 }
		}
			}
}
int validate_code(int code)		
//FUNCTION TO VALIDATE BOOK CODE
{
    fstream fp;
    book pr;
    fp.open("Shop.dat",ios::in|ios::binary);
    while(fp.read((char*)&pr,sizeof(book)))
    {
if(pr.retpno()==code)
	return 1;
      }
	return 0;
}
void place_order() 		 //****FUNCTION TO PLACE ORDER****//
{
	/*
	1.LIST ALL THE BOOKS
	2. ASK THE BOOK CODE
	3. VALIDATE THE CODE
	3. ASK FOR QUANTITY AND IT SHOULD BE LESS THAN 
THE AVAILABLE QUANTITY
	4. REDUCE THE BOOK QUANTITY
	5. DISPLAY TOTAL BILL
	*/
	pur_book b[50];
	int c=0;
	float totamt=0;
	char ch='y';
	while(ch=='y')
	{
        menu();
    	cout<<"Enter Book code"; cin>>b[c].bcode;
    	if(validate_code(b[c].bcode))
    	{
            cout<<"Enter Book Quantity"; cin>>b[c].qty_reqd;
    		get_values(b[c]);
			c++;
		}
		else
		{
			cout<<"invalid Code"; getch();
		}
    	cout<<"Purchase More ";cin>>ch;
    }
    system("cls");
	cout<<"\n\t\t\t\t BILLING SECTION\n\n\n";
	cout<<"=============================================================\n";
	cout<<"Book   Qty  Price(Rs)  Discount(%)  Net(Rs)\n";
	for(int i=0;i<c;i++)
	{
		cout<<setw(2)<<b[i].bname<<"\t"<<b[i].qty_reqd<<"\t"<<b[i].bprice<<"	\t"<<b[i].bdis<<"\t    "<<b[i].bamt<<"\n";
		cout<<"==============================================	===============\n";
		totamt+=b[i].bamt;
	}
	cout<<"\n\n\n Total Amount to pay \t: "<<totamt;
    	getch();
}
void write_book() 	
 //****FUNCTION TO WRITE BOOK RECORDS****//
{
    system("CLS");
    fstream fp;
    book pr;
    char ch='y';
    fp.open("Shop.dat",ios::out|ios::app|ios::binary);
    while(ch=='y'||ch=='Y')
    {
        pr.create_book();
	  	fp.write((char*)&pr,sizeof(book));
	  	cout<<"\n\nThe book Has Been Created.";
	  	cout<<"\n\n Add more records (y/n)";
		cin>>ch;
		}
	fp.close();
}
void display_all()  	
//****FUNCTION TO DISPLAY ALL RECORDS****//
{
	fstream fp;
    book pr;
	system("CLS");
	cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
	fp.open("Shop.dat",ios::in|ios::binary);
	while(fp.read((char*)&pr,sizeof(book)))
	{
		pr.show_book();
		cout<<"\n\n====================================\n";
		getch();
	 	}
	fp.close();
}
void display_sp(int n)		
//TO DISPLAY SPECIFIC BOOK RECORD
{
    system("CLS");
     int flag=0;
    fstream fp;
    book pr;
	fp.open("Shop.dat",ios::in|ios::binary);
	while(fp.read((char*)&pr,sizeof(book)))
	{
	 	if(pr.retpno()==n)
  		{
			pr.show_book();
		 	flag=1;
		}
	}
	  	fp.close();
	  	if(flag==0)
	  	cout<<"\n\nrecord not exist";
       	getch();
}
void modify_book()  
 //****FUCTION TO MODIFY THE RECORDS****// 
{
	system("CLS");
	int no,found=0;
	fstream fp;
    	book pr;
	cout<<"\n\n\tTo Modify ";
	cout<<"\n\n\tPlease Enter The book No. of The book:-";
	cin>>no;
	fp.open("Shop.dat",ios::in|ios::out|ios::binary);
	while(fp.read((char*)&pr,sizeof(book)) && found==0)
	{
		if(pr.retpno()==no)
		{
			pr.show_book();
			cout<<"\nPlease Enter The New Details of book:-"<<endl;
			pr.create_book();
			int pos=-1*sizeof(pr);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&pr,sizeof(book));
			cout<<"\n\n\t Record Updated";
			 		found=1;
				}
		  	}
	  		fp.close();
	 		if(found==0)
	  		cout<<"\n\n Record Not Found ";
	  		getch();
}
void delete_book()		
//****FUNCTION TO DELETE THE RECORD****//
{
    system("CLS");
	int no;
	fstream fp;
    	book pr;
	cout<<"\n\n\n\tDelete Record";
	cout<<"\n\nPlease Enter The book no. of The book You Want To 	Delete:-";
	cin>>no;
	fp.open("Shop.dat",ios::in|ios::binary);
	fstream fp2;
	fp2.open("Temp.dat",ios::out|ios::binary);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&pr,sizeof(book)))
	{
	 	if(pr.retpno()!=no)
		{
		 	fp2.write((char*)&pr,sizeof(book));
		}
	}
	fp2.close();
	fp.close();
	remove("Shop.dat");
	rename("Temp.dat","Shop.dat");
	cout<<"\n\n\tRecord Deleted ..";
	getch();
}
void menu()  	//****FUCTION TO DISPLAY BOOK  MENU****//
{
    	system("CLS");
	  	fstream fp;
       	book pr;
	  	fp.open("Shop.dat",ios::in|ios::binary);
	  	if(!fp)
	  	{
	  		cout<<"ERROR!!! FILE COULD NOT BE OPEN\n\n Go To Admin Menu to create File";
	  		cout<<"\n\n\n Program is closing ....";
	  		getch();
		 	return;
	  	}
			cout<<"\n\n\t\tBOOK MENU\n\t\tThese are available books.\nTo add more books go to the administrative section\n\n";
			cout<<"==============================================	======\n";
	cout<<"P.NO.\tNAME\tPRICE\tQuantity\n";
			cout<<"==============================================	======\n";
		while(fp.read((char*)&pr,sizeof(book)))
		{
			cout<<pr.retpno()<<"\t"<<pr.retname()<<"\t"<<pr.retprice()<<"\t"
			<<pr.retqty()<<endl;
		}
	  		fp.close(); getch();
}
void book_pur()		
{
		system("CLS");
	  	fstream fp;
       	book pr;
	  	fp.open("Shop.dat",ios::in|ios::out|ios::binary);
	  	if(!fp)
	  	{
	  		cout<<"ERROR!!! FILE COULD NOT BE OPEN\n\n Go 			To Admin Menu to create File";
	  		cout<<"\n\n\n Program is closing ....";
	  		getch();
		 	return;
	  	}
	  	int bcode,bqty=0;
	  	cout<<"Enter Book code";
	  	cin>>bcode;
	  	int f=0;
	  	while(fp.read((char*)&pr,sizeof(pr)))
	  	{
			if(pr.retpno()==bcode)
				{
					cout<<"Enter Book Quantity";
					cin>>bqty;
					pr.add_qty(bqty);
					int pos=fp.tellg();
					fp.seekg(pos-sizeof(pr));
					fp.write((char*)&pr,sizeof(pr));
					f=1;
					break;
				}
	  	}
	  	fp.close();
	  	if(f==0)
	  	{
			cout<<"record not found";
			getch();
		}

}
void admin_menu()  	//TO DISPLAY THE ADMIN MENU
{       
	int ch2;
	do{
        system("CLS");
	  	cout<<"\n\n\n\tADMIN MENU";
     		cout<<"\n\n\t1.CREATE book record";
	    	cout<<"\n\n\t2.DISPLAY NAME OF ALL BOOKS";
	    	cout<<"\n\n\t3.SERACH BY OOK  NUMBER ";
	    	cout<<"\n\n\t4.CHANGE BOOK RECORD";
	    	cout<<"\n\n\t5.DELETE BOOK RECORD";
	  	cout<<"\n\n\t6.VIEW BOOK LIST";
	  	cout<<"\n\n\t7.ADD QUANTITY TO A BOOK ";
	  	cout<<"\n\n\t0.BACK TO MAIN MENU";
	  	cout<<"\n\n\tPlease Enter Your Choice (1-7) ";
		cin>>ch2;
	  	switch(ch2)
	  	{
	 		case 1 :write_book(); 			break;
	 		case 2: display_all();break;
	 		case 3:int num; system("CLS");
				 cout<<"\n\n\tPlease Enter The book No. ";
				cin>>num;
			display_sp(num);
			 break;
			case 4: modify_book();break;
			case 5: delete_book();break;
			case 6: menu(); break;
            		case 7: book_pur(); break;
			case 0: return;
	  		default:cout<<"\a Invalid Choice";
		}
	}while(ch2!=0);

}
void main_menu()		//FOR MAIN MENU
{
    int ch;
    do
	 {
		system("CLS");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t1. CUSTOMER";
		cout<<"\n\n\t2. ADMINISTRATOR";
		cout<<"\n\n\t0. EXIT";
		cout<<"\n\n\tPlease Select Your Option (1-3) ";
		cin>>ch;
		switch(ch)
		{
		case 1:	place_order();system("CLS");
				break;
    		case 2: admin_menu(); system("CLS");
				break;
     		case 0:exit(0);
	 		default :cout<<"\aInvalid choice "; 
getch();
		}
	}while(ch!=0);

}
void heading()		//TO DISPLAY THE MAIN HEADING
{
	system("COLOR F1");
	cout<<"\n\n\n\n\n\n\n\n";
	cout<<"\n\t     ***   ****  ****  *   *    ***    ****  ***   ****  ***** ";
	Sleep(250);
	cout<<"\n\t     *  *  *  *  *  *  * *      *   *  *     *  *  *  *    *   ";
	Sleep(250);
	cout<<"\n\t     ***   *  *  *  *  **       *   *  ***   ***   *  *    *   ";
	Sleep(250);
	cout<<"\n\t     *  *  *  *  *  *  * *      *   *  *     *     *  *    *   ";
	Sleep(250);
	cout<<"\n\t     ***   ****  ****  *   *    ***    ****  *     ****    *   ";
	getch();
}
void box(int r1,int r2,int c1,int c2,char ch)		//FOR CREATING BOX
{
	for(int c=c1;c<=c2;c++)
	{
		gotoxy(c,r1);
		cout<<ch;
		
		gotoxy(c,r2);
		cout<<ch;
	}
	for(int r=r1;r<=r2;r++)
	{
		gotoxy(c1,r);
		cout<<ch;
		gotoxy(c2,r);
		cout<<ch;
	
	}
}



int main()
{
	heading();
	box(3,20,5,75,'@');
	getch();
	system("CLS");
	splash();
	box(3,20,5,70,'#');
	getch();
	main_menu();
	return 0;
}



