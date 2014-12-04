#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define esc 		27
#define enter 		13
#define up 			72
#define down 		80
#define home 		71
#define end 		79
#define normal 		0x07
#define highlight 	0x70
#define hilight     0x70
#define highlight2  0x3f
#define tab 		9
#define alt_f 		33
#define alt_s 		31
#define alt_v	 	47
#define insert 		82
#define del 		83
#define f2    		60
#define right 		77
#define left 		75

#define ok              111
#define cancel          99
#define backspace   	8

struct contact{
	char name[15];
	char phone[15];
	char address[20];
	struct contact * prev;
	struct contact * next;

};  //heba

//global variable
struct contact * head , * tail; 					// heba
char* file_name;
int records_num=0;

//functions prototypes
void draw_header(void);   							
void header(char);        							
void footer(void);       							
void menu_view(void);    							
void menu_file(void);    							
void menu_search(void);     						
void open_file_window(int); 						
char* line_editor(int,int,char, char*); 			
void draw_phone_book(void);//char*);  				
void phone_book(char*);								

void save_file(char *);
int are_you_sure(void);

int ReadFile(char* szInputfile); 					
struct contact * createNode(void); 					
void append (struct contact *ele); 					
void display(int,int);								
void delete_contact(struct contact * temp); 		
void search_by(int search_type);                   
void NotFound(void);                               
void search_result(char Name[21],char Number[21]);      
void search_result_screen(struct contact * );   
void deleteChar(char *pt,int pos,int size,int col,int row ,int button);

void sort (struct contact * ,struct contact * ,int );
void swap (struct contact * ,struct contact *);

void Editing (struct contact *);
/*

void EditRecord(void);//sarah this will call CreatLineEditor 3 times
//char *LineEditor(int col,int row); //sarah
void EditRecord(void); //sarah */
void add_record_window(void);


int main(void)
{
	char key;
	int terminate=0;
	textattr(normal);
	clrscr();

	flushall();
	footer();
	draw_header();
	
//Taher
		//add_record_window();
		//getch();
		//return;
//Hala
	do
	{
		key=getch();
		if (key == NULL)  //to make header active all the time
		{
			key=getch();
			switch(key)
			{
				case alt_f:
				case alt_v:
				case alt_s:
					header(key);
					break;
			}
		}
//Heba
		else if(key==esc)
		{
			textattr(normal);
			clrscr();
			footer();
			draw_header();
			terminate=1;
		}
		else
		{
			textattr(normal);
			clrscr();
			footer();
			draw_header();
		}

	} while(!terminate); 

//Sara

//	getch();
	return 0;
}

int are_you_sure(void)
{
    char SaveOptions[2][10]={" Ok "," Cancel "};
	int i,j,terminate=0,pos=0, sure;
	char SaveSelection ;
	clrscr();
	footer();
	draw_header();
	//textattr(highlight2);
	
	window(15,7,65,17);
	gotoxy(1,1);
	textattr(highlight2);
	for (i=0; i<11; i++)
		cprintf("                                                       ");

	
	gotoxy(20,3);
    textcolor(WHITE);
	cprintf("Are  You Sure ? \n");
	gotoxy(2,8);
	cprintf("----------------------------------------------");
       do{
       	for(j=0;j<2;j++)

		{
		       if(j==pos)
				textbackground(YELLOW);
			gotoxy(10+j*15,9);

			cprintf("%s",SaveOptions[j]);
			 textattr(highlight);
		}
		textattr(highlight2);
		gotoxy(2,10);
		cprintf("-----------------------------------------------");

		flushall();
		SaveSelection=getch();
		switch(SaveSelection)
		{
			case NULL:
				SaveSelection=getch();
				switch(SaveSelection)
				{
					case left:
					pos--;
					if(pos<0)
						pos=1;
					break;

					case right:
					pos++;
					if(pos>1)
						pos=0;
					break;

				}

			break;
		case enter :
			switch(pos)
			{
				case 0:
					sure=0;
					terminate=1;
				break;
				case 1:
					sure=1;
					terminate=1;
				break;
			}
		break;
			case tab:
					pos++;
					if(pos>1)
						pos=0;
			break;

			case ok:
			       //	getch()
				 sure=1;
				//printf("\n\n\n ok handling in progress...\n");
				terminate=1;
				pos=0;
			break;
			case cancel:
				sure=0;
				//printf("\n\n\n cancelling...\n");
				pos=1;
				terminate=1;
			break;

			case esc:
				terminate=1;
			break;
		}

       }while(!terminate);
		return sure;
}

void draw_header(void)    //done
{
	int pos,i;
	char menu[3][11]={" File     ", "View      ","Search    "};
	textattr(normal);
	//clrscr();
	gotoxy(1,1);
	textattr(highlight);
	for(i=0; i<3; i++)
		cprintf("%s", menu[i]);
	cprintf("                                                  ");
	textattr(normal);
}

void header(char key)     //done
{
	// Handle Alt+f, Alt+v, Alt+s
	switch(key)
	{
				case alt_f:
					menu_file();
					break;
				case alt_s:
					menu_search();
					break;
				case alt_v:
					menu_view();
					break;
	}
}

void footer(void)        //done
{
	gotoxy(1,25);
	textattr(highlight);
	cprintf("  Alt+f File    Alt+V  View     Alt+s  Search                                  ");
	gotoxy(1,1);
	textattr(normal);
}

//Taher

void menu_file(void)      //done
{
	char key;
   	int pos=0,i, stop=0, size=4, sure=0;
   	char file_menu[4][20]={"   New    " , "   Open   " , "   Save   " , "   Exit   "};
	flushall();
	
	//file_name=(char*)malloc(21*sizeof(char));
	
	textattr(normal);
	//clrscr();
	//footer();
	draw_header();
	
	textattr(highlight);
	gotoxy(1,2);
	cprintf("----------");
	do{
		//window(1,20,4,30);
		textbackground(WHITE);
		for(i=0;i<size;i++)
		{
			if(i==pos)
				textbackground(YELLOW);
			gotoxy(1,i+3);
			cprintf("%s",file_menu[i]);
			textattr(highlight);
		}
		gotoxy(1,3+size);
		cprintf("----------");
		
		flushall();
		key=getch();
		switch (key)
		{
			case NULL:
				key=getch();
				switch (key)
				{
					case up:
						pos--;
						if (pos<0)
							pos=size-1;
						break;
					case down:
						pos++;
						if (pos >size-1)
							pos=0;
						break;
					case alt_v:
					case right:
						textattr(normal);
						clrscr();
						footer();
						menu_view();
						stop=1;
						break;
					case alt_s:
						textattr(normal);
						clrscr();
						footer();
						menu_search();
						stop=1;
						break;
					case alt_f:
						textattr(normal);
						clrscr();
						footer();
						draw_header();
						stop=1;
						break;
				}
				break;
			case tab:
				pos++;
				if (pos >size-1)
					pos=0;
				break;

			case enter:
				switch(pos)
				{
					case 0 :                            //// means cursor on new
						textbackground(BLACK);
						clrscr();
						footer();
						draw_header();
						open_file_window(1);
						stop=1;
						break;
					case 1 :							//// means cursor on open
						textbackground(BLACK);
						clrscr();
						footer();
						draw_header();
						head=tail=NULL;
						open_file_window(0);
						//clrscr();
						//printf("ba3d open %s",file_name);
						//getch();
						//phone_book(file_name);
						//ReadFile(file_name);
						stop=1;
						break;
					case 2 :
						textbackground(BLACK);
						clrscr();
						footer();
						draw_header();
						sure=are_you_sure();
						if (sure==0)
						{
							window(1,1,80,24);
							clrscr();
							textbackground(BLACK);
							clrscr();
							footer();
							draw_header();
							save_file(file_name);
						}
						else
						{
							window(1,1,80,24);
							textbackground(BLACK);
							clrscr();
							footer();
							draw_header();
						}
						stop=1;
						break;
					case 3:
						textbackground(BLACK);
						clrscr();
						footer();
						draw_header();
						sure=are_you_sure();
						if (sure == 0)
						{	
							exit(0);
						}
						else
						{
							window(1,1,80,24);
							textbackground(BLACK);
							clrscr();
							footer();
							draw_header();
						}
						stop=1;
						break;
				}
				break;		
			case esc:
				textattr(normal);
				clrscr();
				footer();
				draw_header();
				stop=1;
				break;
		}
	}while(!stop);
}

void save_file(char * file_name)		//done
{
	struct contact * temp;
	FILE * pfile_out;
	temp = head;
	
	//clrscr();
	//printf("gowa save %s",file_name);
	//getch();
	if ((pfile_out = fopen( file_name, "w" )) == NULL )
   {
       printf("Error, cannot open %s\n", file_name);
		getch();
	   exit(1);
   }
	else
	{
		//fflush(pfile_out);
		while(temp != NULL)
		{
			fprintf(pfile_out,"%s,%s,%s", temp->name , temp->phone,temp->address);
			temp=temp->next;
		}
		fclose(pfile_out);
	}
}

void open_file_window(int create)   //done
{
	int size=2,stop=0;
   	int pos=-1;
   	int i = 0;
   	char key;
   
   	char window_buttons[2][15]={"   OK    ","  CANCEL  "};         
   	FILE* fb;
                                               
	// new_file_name = "test file name";
	 ////////   
	     
	textattr(normal);
	clrscr();
	footer();         
	draw_header();
	
	flushall();
	window(15,7,65,17);
	gotoxy(1,1);
	textattr(highlight2);
	for (i=0; i<11; i++)
		cprintf("                                                       ");
	
	gotoxy(20,3);
    textcolor(WHITE);
    if (create)
    	cprintf("Add New PhoneBook");
    else
    	cprintf("Open a PhoneBook");
 
    gotoxy(3,6);
    cprintf("file name: ");
	
	
	gotoxy(2,8);
	cprintf("----------------------------------------------");
	
	do{
		//window(1,20,4,30);
		gotoxy(10,9);
		textattr(highlight);
		for(i=0;i<size;i++)
		{
			if(i==pos)
				textbackground(YELLOW);
			gotoxy(10+i*15,9);
			cprintf("%s",window_buttons[i]);
			textattr(highlight);
		}
		textattr(highlight2);
		gotoxy(2,10);
		cprintf("-----------------------------------------------");
		
		gotoxy(15,6);
		//new_file_name=line_editor(15,6);
		
		flushall();
		key=getch();
		switch (key)
		{
			case NULL:
				key=getch();
				switch (key)
				{
					case right:
						pos++;
						if (pos >size-1)
							pos=0;
						break;
					case left:
						pos--;
						if (pos <0 )
							pos=size-1;
						break;
				}
				break;
			case tab:
				pos++;
				if (pos >size-1)
					pos=0;
				break;

				case enter:
				switch(pos)
				{
					case 0 :         //ok
						if (create)        //it was the create new file window               
						{	
							if( access( file_name, 06 ) != -1 ) 
    						{	// file exists
    							gotoxy(15,7);
								printf("This file already exists.");
							}
							else 
							{
    							// file doesn't exist
								fopen(file_name, "a+");
								window(1,1,80,24);
								textattr(normal);
								clrscr();
								draw_header();
								//ReadFile(file_name);
								phone_book(file_name);
								stop=1;							
							}
						}
						
						if (!create)        //it was the open file window               
						{	
							if( access( file_name, 06 ) != -1 ) 
    						{	// file exists
    							fopen(file_name, "a+");
								window(1,1,80,24);
								textattr(normal);
								clrscr();
								draw_header();
								phone_book(file_name);
								stop=1;			
							
							}
							else 
							{
    							// file doesn't exist
								gotoxy(15,7);
								printf("This file doesn't exist.");			
							}
						}
						break;
					case 1 :     			//cancel
						window(1,1,80,24);
						textattr(normal);
						clrscr();
						footer();
						draw_header();
						stop=1;
						break;
				}
				break;		
			case esc:
				window(1,1,80,24);
				textattr(normal);
				clrscr();
				footer();
				draw_header();
				stop=1;
				break;
			default:
				if (isprint(key))
				{
					file_name=line_editor(15,6,key,file_name);
					pos++;
				} 
		}
	}while(!stop);
	//free(file_name);
	//clrscr();
	//printf("return   %s",file_name);
	//getch();
	//return file_name;
}

//Hala

void menu_view(void)   						  	//done
{
	char key;
	int pos=0,i, stop=0, size=3;
	char view_menu[3][35]={" Sort by name    ", " Sort by phone   "," Sort by address "};
	flushall();
	
	textattr(normal);
	//clrscr();
	//footer();
	draw_header();
	
	textattr(highlight);
	gotoxy(10,2);
	cprintf("-----------------");
	do{
		//window(1,20,4,30);
		textbackground(WHITE);
		for(i=0;i<size;i++)
		{
			if(i==pos)
				textbackground(YELLOW);
			gotoxy(10,i+3);
			cprintf("%s",view_menu[i]);
			textattr(highlight);
		}
		gotoxy(10,3+size);
		cprintf("-----------------");

		flushall();
		key=getch();
		switch (key)
		{
			case NULL:
				key=getch();
				switch (key)
				{
					case up:
						pos--;
						if (pos<0)
							pos=size-1;
						break;
					case down:
						pos++;
						if (pos >size-1)
							pos=0;
						break;
					case alt_f:
					case left:
						textattr(normal);
						clrscr();
						footer();
						menu_file();
						stop=1;								//// go to the file menu
						break;
					case alt_s:
					case right:
						textattr(normal);
						clrscr();
						footer();
						menu_search();
						stop=1;
						break;
					case alt_v:
						textattr(normal);
						clrscr();
						footer();
						draw_header();
						stop=1;
						break;
				}
				break;
			case tab:
				pos++;
				if (pos >size-1)
					pos=0;
				break;

			case enter:
				textattr(normal);
				clrscr();
				footer();
				draw_header();
			//	draw_phone_book();
				//getch();
				stop=1;

				//read from file func
				//pos cases
				switch (pos)
				{

					case 0:
						sort(head,head,0);
						draw_header();
						draw_phone_book();
						display(records_num,0);
						//sort by name func
						stop=1;
						break;
					case 1:
						sort(head,head,1);
						draw_header();
						draw_phone_book();
						display(records_num,0);
						//sort by phone func
						stop=1;
						break;
					case 2:
						sort(head,head,2);
						draw_header();
						draw_phone_book();
						display(records_num,0);
						//sort by address func
						stop=1;
						break;
				}
				break;
			case esc:
				textattr(normal);
				clrscr();
				footer();
				draw_header();
				stop=1;
				break;
		}
	}while(!stop);
}

void draw_phone_book(void)//char* file)       	//done
{
	gotoxy(1,2);
	textattr(0x17);
	cprintf("   Name              ");
	textattr(normal);
	cprintf("  ");
	textattr(0x17);
	cprintf("   Phone              ");
	textattr(normal);
	cprintf("  ");
	textattr(0x17);
	cprintf("   Address                       \n");
	textattr(highlight);
	gotoxy(1,24);
	cprintf("  Ins Insert   Del Delete   F2 Edit   Up/Down Move                             ");
	gotoxy(1,2);
	textattr(normal);
}

void phone_book(char* file_name)				//done
{
	int pos=0, stop=0, i=0;
	char key;
	int size;  //number of records in phone book
	struct contact* curr_contact;
	
	size=ReadFile(file_name);

	do{
		curr_contact=head;
		clrscr();
		footer();
		draw_header();
		draw_phone_book();
		display(size,pos);
		flushall();
		key=getch();
		switch (key)
		{
			case NULL:
				key=getch();
				switch (key)
				{
					case up:
						pos--;
						if (pos<0)
							pos=size-1;
					
						break;
					case down:
						pos++;
						if (pos >size-1)
							pos=0;
						break;
					case alt_f:
					case alt_s:
					case alt_v:
						header(key);
						stop=1;
						break;
					//Operations on records
					case insert:
						// add record func
						add_record_window();
						window(1,1,80,24);
						textattr(normal);
						clrscr();
						footer();
						draw_header();
						break;
					case del:
						//sure?? func
						//delete_reco func
						i=0;
						if (pos==0)
							curr_contact=head;
	 					else if (pos == size-1)
							curr_contact=tail;
	 					else
						{
							while(i<pos)
							{
								curr_contact=curr_contact->next;
								i++;
							}		
						}
						delete_contact(curr_contact);
						size--;
						break;
					case f2:
						//edit func			/sarah
						// update button
				
							//if(curr_contact==NULL) Editing(tail);
							 //Editing(curr_contact);
						
					
					
						break;
				}
				break;
			case tab:
				pos++;
				if (pos >size-1)
					pos=0;
				break;

			case enter:
				//show record
				break;
			case esc:
				stop=1;
				break;
		}		
	}while(!stop);
	//return file_name;
}
void add_record_window(void)
{
	int size=2,stop=0;
   	int pos=-3;
   	int i = 0, field=0;
   	char key;
	struct contact* con;
	
	
	char* name;
	char* address;
	char* phone;
   	char window_buttons[2][15]={"   OK    ","  CANCEL  "};         
	
	textattr(normal);
	clrscr();
	footer();         
	draw_header();
	
	flushall();
	window(15,7,65,17);
	gotoxy(1,1);
	textattr(highlight2);
	for (i=0; i<11; i++)
		cprintf("                                                       ");
	
	gotoxy(20,3);
    textcolor(WHITE);
  	cprintf("Add New record");

    gotoxy(3,6);
    cprintf("Name: ");
	gotoxy(3,7);
    cprintf("Phone: ");
	gotoxy(3,8);
    cprintf("Address: ");
	
	gotoxy(2,9);
	cprintf("----------------------------------------------");

	do{
		//window(1,20,4,30);
		gotoxy(10,10);
		textattr(highlight);
		for(i=0;i<size;i++)
		{
			if(i==pos)
				textbackground(YELLOW);
			gotoxy(10+i*15,10);
			cprintf("%s",window_buttons[i]);
			textattr(highlight);
		}
		textattr(highlight2);
		gotoxy(2,11);
		cprintf("-----------------------------------------------");
					
		flushall();
		key=getch();
		//new_file_name=line_editor(15,6);
		gotoxy(15,6);
		switch (key)
		{
			case NULL:
				key=getch();
				switch (key)
				{
					case right:
						pos++;
						if (pos >size-1)
							pos=0;
						break;
					case left:
						pos--;
						if (pos < 0)
							pos=size-1;
						break;
					case down:
						pos++;
						if (pos > -1)
							pos=-1;
						break;
					case up:
						pos--;
						if (pos <-3)
							pos=-3;
						break;
				}
				break;
			case tab:
				pos++;
				if (pos > size-1)
					pos=-3;
				break;

			case enter:
				switch(pos)
				{
					case 0 :         //ok
						//name=strtok( ",",name );
						//name=strtok( name, "," );
						//phone=strtok( phone, "," );
						//address=strtok( address, "," );
						strcpy( con->name, name );
						strcpy( con->phone, phone );
						strcpy( con->address, address );
						
						//if(are_you_sure() == 0)
							append(con);
						clrscr();
					printf("fel con	%s",tail->name);
					printf("fel con	%s",tail->phone);
					printf("fel con	%s",tail->address);
					getch();
						stop=1;
						break;
					case 1 :     			//cancel
						window(1,1,80,24);
						textattr(normal);
						clrscr();
						footer();
						draw_header();
						stop=1;
						break;
				}
				break;		
			case esc:
				window(1,1,80,24);
				textattr(normal);
				clrscr();
				footer();
				draw_header();
				stop=1;
				break;
			default:
				if (isprint(key))
				{
					if (pos==-3)
					{gotoxy(15,6);
					name=line_editor(15,6,key,name);
					}
					else if (pos==-2)
					{gotoxy(15,7);
					phone=line_editor(15,7,key,phone);
					gotoxy(15,8);
					}
					else if (pos==-1)
					{gotoxy(15,8);
					address=line_editor(15,8,key,address);
					}
					pos++;
				}
				//stop=1;
		}
	
	}while(!stop);
}

//Heba

void menu_search(void) {   						//done
	char search_menu[2][13]={"  by name   ","  by phone  "};
	
	int pos=0,i, size=2;
	char key;
	int terminate=0;
	
	textattr(normal);
	//clrscr();
	//footer();
	draw_header();

	textattr(highlight);
	flushall();
	gotoxy(21,2);
	cprintf("------------");
	do{
		//window(1,20,4,30);
		textbackground(WHITE);
		for(i=0;i<size;i++)
		{ 
			if(i==pos)
			textbackground(YELLOW);
			gotoxy(21,i+3);
			cprintf("%s",search_menu[i]);
			textattr(highlight);
		}
		gotoxy(21,3+size);
		cprintf("------------");

		flushall();
		key=getch();
		switch(key){
			case enter:
					switch(pos)
					{
						case 0:
							
							//search by name 
							textattr(normal);
							clrscr();
							footer();
							draw_header();
							search_by(1);
							terminate=1;
							break;

						case 1:
				
							//search by phone
							textattr(normal);
							clrscr();
							footer();
							draw_header();
							search_by(2);
							terminate=1;
							break;
					}
					break;

			case tab:
				pos--;
				if(pos<0) pos=2;
				break;

			case NULL:
				key=getch();
				switch(key)
				{
					case up:
						pos--;
						if(pos<0) pos=2;
						break;

					case down:
						pos++;
						if(pos>1) pos=0;
						break;

					case home:
						pos=0;
						break;

					case end:
						pos=2;
						break;

					case alt_f:
						textattr(normal);
						clrscr();
						footer();
						menu_file();
						terminate=1;
						break;

					case alt_v:
					case left:
						textattr(normal);
						clrscr();
						footer();
						menu_view();
						terminate=1;
						break;

					case alt_s:
						textattr(normal);
						clrscr();
						footer();
						draw_header();
						terminate=1;
						break;
				}
				break;
			
			case esc:
				textattr(normal);
				clrscr();
				footer();
				draw_header();
				terminate=1;
				break;

		}
	}while(!terminate);
	
}

// not found Screen
void NotFound(void){							//done
		int i,j;
		for(i=23;i<60;i++){
			for(j = 9;j<16; j++){
				gotoxy(i,j);
				textattr(highlight2);
				cprintf("%c" , ' ');
			}
		}
		gotoxy(32,12);
		textcolor(BLACK);
		printf("Contact is Not Found\n");

		// draw button
		gotoxy(38,14);
		printf("Cancel");
		textcolor(BLACK);

		gotoxy(38,14);
		getch();
		
		//hide screen
		for(i=23;i<60;i++){
			for(j = 9;j<16; j++){
				gotoxy(i,j);
				textbackground(highlight);
				cprintf("%c" , ' ');
			}
		}
}

//create new node
struct contact * createNode(void)				//done
{
   return (struct contact *)malloc(sizeof(struct contact));
}
 
// add struct 
void append (struct contact *ele)					//done
{
   if(head==NULL){
       head=tail=ele;
       ele->prev=NULL;
       ele->next=NULL;
   }
   else{
       ele->prev=tail;
       tail->next=ele;
       tail=ele;
       ele->next=NULL;
   }
   records_num++;
}                  
 
// read from file
int ReadFile(char* szInputfile)						//done
{
 
   	FILE *pfile_input;
   	char szBuffer[100];
	char * pTemp;
	
	//records_num=0;
   	
 
   /*************************************...
   open inputfile for reading
   **************************************... */
 
   if ((pfile_input = fopen( szInputfile, "r" )) == NULL )
   {
       printf("Error, cannot open %s for reading\n", szInputfile);
       exit(1);
   }
 
   /*************************************...
   Read the data from the inputfile
   **************************************... */
 
   while( ( fgets( szBuffer, sizeof(szBuffer), pfile_input )) != NULL )
   {
 
       struct contact * record= createNode();
       //append();
       char num [15];
       pTemp = strtok( szBuffer, "," );
       strcpy( record->name, pTemp ); 
 
       pTemp = strtok( NULL, "," ); 
       //strcpy( num, pTemp );
	   strcpy( record->phone, pTemp ); 
       
       pTemp = strtok( NULL, "," );
       strcpy( record->address, pTemp ); 
       
       append(record);
   }  
   
	fclose(pfile_input);
   return records_num;
}

void display(int records_num, int pos)				//done
{
	struct contact *temp;
    int x=4,y=4, i=0;
    temp=head;
    //records_num=25;
    while(temp!=NULL && i<records_num)
	{
		if (i==pos)
			textattr(highlight2);
		gotoxy(x,y);
       	cprintf("%s",temp->name);   
		gotoxy(x+25,y);
       	cprintf("%s",temp->phone);          
	   	gotoxy(x+50,y);
       	cprintf("%s",temp->address); 
       	textattr(normal);
			
		y++;
		i++;
        temp=temp->next; 
    } 
}

void delete_contact(struct contact * temp)			//done
{
		//struct contact *ee;
		if (temp==head && head==tail){
			head=tail=NULL;
			free(temp);
		}
		else if (temp==head && head!=tail){
			head=head->next;
			head->prev=NULL;
			free(temp);
		}
		else if (temp==tail && head!=tail){
			tail=tail->prev;
			tail->next=NULL;
			free(temp);
		}
		else {
			temp->prev->next=temp->next;
			temp->next->prev=temp->prev;
			free(temp);
		}
		tail->next=NULL;
		records_num--;

		/* ee=head;
		do{
		printf("\n%s\t\t%d\t\t%s\n",ee->name,ee->phone,ee->address);
		if(ee->next!=NULL){
			ee=ee->next;
		}
		else{
			ee=NULL;
		}
		}
		while(ee!=NULL); */
}

// search result screen
void search_result_screen(struct contact * temp){		//done
		int i,j , pos , terminate;
		char key;
		for(i=19;i<65;i++){
			for(j=7;j<20; j++){
				gotoxy(i,j);
				textattr(highlight2);
				cprintf("%c" , ' ');
			}
		}
		gotoxy(36,8);
		textcolor(WHITE);
		cprintf("Search Result\n");

	    gotoxy(20,10);
		cprintf("Name: ");
		gotoxy(35,10);
		cprintf("%s",temp->name);
		
		gotoxy(20,12);
		cprintf("Phone: ");
		gotoxy(35,12);
		cprintf("%s",temp->phone);
		
		gotoxy(20,14);
		cprintf("Address: ");
		gotoxy(37,14);
		cprintf("%s",temp->address);
		
		textcolor(WHITE);
		gotoxy(20,16);
		cprintf("------------------------------------------");
		
		// draw button
		textcolor(BLACK);
		gotoxy(28,17);
	    cprintf("Edit");
	
		gotoxy(38,17);
	    cprintf("Remove");
		
		
		gotoxy(50,17);
	    cprintf("Next");
		textcolor(WHITE);
		
		gotoxy(20,18);
		cprintf("-----------------------------------------");
		gotoxy(50,17);
		textattr(normal);
}

void Editing (struct contact * temp)
{
	char EditFeilds[3][16]={"Name","phone","address" };
	int j,i,step1=0,checkPrint,stopLoop=0 , pos=0 , End=0;
	char name[15] , address[21] ,phone[15],key , search_word;
	char * ptrName , * ptrAdd ,* ptrPhone;
	ptrName=name;
	ptrPhone=phone;
	ptrAdd=address;
	
	textattr(normal);
	clrscr();
	gotoxy(25,2);
	printf("Name: %s",temp->name);
	gotoxy(25,3);
	printf("Phone: %s",temp->phone);
	gotoxy(25,4);
	printf("Address:%s",temp->address);
	window(15,5,65,16);
	textattr(highlight2);
	for(i=1;i<11;i++)
		cprintf("                                                                   ");
	    for(i=0;i<3;i++){
			gotoxy(12,5+step1);
			puts(EditFeilds[i]);
			gotoxy(20,5+step1);
			textbackground(BLUE);
			for(j=0;j<22;j++)	cprintf(" ");
			step1+=2;
		}

		gotoxy(30,10);
		textattr(highlight) ;
		cprintf("\n OK ") ;
		
		step1=0;
		gotoxy(20,5+step1);

		do{
				flushall();
				key=getch();
				switch(key){
					case enter:
						if(step1==6){
							window(1,1,80,24);
							textattr(normal);
							clrscr();
							footer();
							draw_header();
							if(are_you_sure()==0){
								window(1,1,80,24);
								strcpy(temp->name,name);
								strcpy(temp->phone,phone);
								strcpy(temp->address,address);
							}
							stopLoop=1;
						}
					break;
					case esc:
						window(1,1,80,24);
						textattr(normal);
						clrscr();
						footer();
						draw_header();
						stopLoop=1;
						break;
						
					case backspace:
						if(step1!=6){
							pos--;
							if(pos<0) pos=0;
							else{
								if(step1==0) deleteChar(ptrName,pos,End,20,5+step1,backspace);
								else if(step1==2) deleteChar(ptrPhone,pos,End,20,5+step1,backspace);
								else if(step1==4) deleteChar(ptrAdd,pos,End,20,5+step1,backspace);
								End=End-1;
									if(End<0) {
										End=0;
										pos=0;
									}
									
							}
						}
						break;
						
					case NULL:
						key=getch();
						switch(key){
							case del:
								if(step1!=6){
									if(step1==0) deleteChar(ptrName,pos,End,20,5+step1,del);
									else if(step1==2) deleteChar(ptrPhone,pos,End,20,5+step1,del);
									else if(step1==4) deleteChar(ptrAdd,pos,End,20,5+step1,del);
									//pos=pos-1;
									//if(pos<0) pos=0;
									//if(pos<End) pos=0;
									End=End-1;
									if(End<0) {
										End=0;
										pos=0;
									}
								}								
								break;
								
							case up:
									// set terminate character
									if(step1==0) {
										for(i=End-1;i<15;i++){
											name[End]='\0';
										}
									}
									else if(step1==2){
										for(i=End-1;i<15;i++){
											phone[End]='\0';
										}
									}
									else if(step1==4){
										for(i=End-1;i<21;i++){
											address[End]='\0';
										}
									}
									step1-=2;
									if(step1<0) step1=6;
									if(step1==6) gotoxy(30,10);
									else gotoxy(20,5+step1);
									pos=0;
									End=0;
									stopLoop=0;
									break;

							case down:
									// set terminate character
									if(step1==0) {
										for(i=End-1;i<15;i++){
											name[End]='\0';
										}
									}
									else if(step1==2){
										for(i=End-1;i<15;i++){
											phone[End]='\0';
										}
									}
									else if(step1==4){
										for(i=End-1;i<21;i++){
											address[End]='\0';
										}
									}
									step1+=2;
									if(step1>6) step1=0;
									if(step1==6) gotoxy(30,10);
									else gotoxy(20,5+step1);
									pos=0;
									End=0;
									stopLoop=0;
									break;
									
							case right:
								if(step1!=6){
									pos++;
									if(pos>=End) {
										pos=End;
										gotoxy(20+pos-1,5+step1);
									}
									else gotoxy(20+pos,5+step1);
								}
								stopLoop=0;
								break;

							case left:
								if(step1!=6){
									//printf("\n\n%d",pos);
									pos--;
									//printf("\n\n%d",pos);
									if(pos<=0){
										pos=0;
										gotoxy(20+pos,5+step1);
									}
									else gotoxy(20+pos-1 ,5+step1);
								}
								stopLoop=0;
								break;
						}
						break;
						
					default:
						if(step1!=6){
							checkPrint=isprint(key);
							if(step1==0 || step1==4){
								if(checkPrint && End<=15 && (step1==0 || step1==4)){
									if(step1==0)  *(ptrName+pos)=key;
									else if (step1==4) *(ptrAdd+pos)=key;
									
									if(pos!=0){
										gotoxy(20+pos,5+step1);
									}
									cprintf("%c",key);
									gotoxy(20+pos,5+step1);
									pos++;
									End++;
								}
								/* else{
									if(pos==End){
										End=End+1;
										pos=pos+1;
									} */
									stopLoop=0;
									break;
								}
							else{
									if(checkPrint && End<=15 && isdigit(key)){
										*(ptrPhone+pos)=key;
										if(pos!=0){
											gotoxy(20+pos,5+step1);
										}
										cprintf("%c",key);
										gotoxy(20+pos,5+step1);
										pos++;
										End++;
									}
								/* else if (checkPrint){
									if(pos==End){
										End=End+1;
										pos=pos+1;
									} */
									stopLoop=0;
								}
							}
						}

		}while(stopLoop==0);

}

//hala

char* line_editor(int col,int row, char key, char* arr)  //almost done
{
	//char arr[21];//, key;
	char *p_current=arr, *p_last=arr, *p_start=arr;
	int strt_column=col, cur_column=col, end_column=col,counter=0,stop=0;
	int max_chars_num=20;
	//clrscr();

	gotoxy(strt_column,row);
	do
	{	//flushall();
		//key= getch();
		switch (key)
		{
			case NULL:
				key=getch();
				switch (key)
				{
					case end:
						p_current=p_last;
						cur_column=end_column;
						gotoxy(cur_column,row);
						break;
					case home:
						p_current=p_start;
						cur_column=strt_column;
						gotoxy(cur_column,row);
						break;
					case right:
						p_current++;
						if (p_current > p_last)
						{
							p_current=p_last;
							cur_column=end_column;
						}
						else
							cur_column++;

						gotoxy(cur_column,row);
						break;
					case left:
						p_current--;
						if(p_current < p_start)
						{
							p_current = p_start;
							cur_column=strt_column;
						}
						else
							cur_column--;
						gotoxy(cur_column,row);
						break;
					/*case up:
					case down:
						*p_last='\0';
						//return arr;
						stop=1;
						break;*/
				}
				flushall();
				key=getch();
				break;
			case tab:
			case esc:
			case enter:			
				*p_last='\0';
				 //return arr;
				 stop=1;
				 break;
			default:
				if (counter == max_chars_num && cur_column>=end_column)
					 {p_current=p_last;}
				else
				{
					if(isprint(key))
					{
						gotoxy(cur_column,row);
						cprintf("%c",key);
						*p_current = key;
						cur_column++;
						p_current++;
						if(p_current > p_last && end_column<=strt_column+max_chars_num)
						{       end_column++;
							p_last++;
							counter++;
						}
					}
				}
				flushall();
				key=getch();
				break;
		}
	}while(!stop);
	return arr;
}


void sort (struct contact * temp1,struct contact * temp2,int sort_type)
{
	temp1=temp1;
	while(temp2 != NULL )
	{
		if(sort_type==0)
		{
		if(strcmpi(temp1->name,temp2->name)>0)
			swap(temp1,temp2);
		}
		else if (sort_type==2)
		{
		if(strcmpi(temp1->address,temp2->address)>0)
			swap(temp1,temp2);
		}
		else
		{
		if(strcmpi(temp1->phone,temp2->phone)>0)
			swap(temp1,temp2);
		}
		temp2=temp2->next;
	}
	temp2=temp1->next;
	temp1=temp1->next;
	if(temp1 != NULL)
	{
		sort(temp1,temp2,sort_type);
	}
}
/*  
void swap (struct contact * t1,struct contact * t2)
{   
	struct contact* temp;//,*temp2;;
	temp=t2;
	//temp2=t2;
	printf("%s   ",t1->name);
	printf("%s   ",t2->name);
	//printf("%s   ",temp->name);
	getch();
	if (t1==head && t2!= tail)
	{	
	t2->next->prev=NULL;//t2->prev;
	t2->prev->next=t1;//t1->prev;
	
	t2->next=t1->next;
	t2->prev=NULL;
	head = t2;
	}
	else if(t1!=head && t2== tail)
	{
	//t2->next->prev=t1;//t2->prev;
	t2->prev->next=t1;//t1->prev;
	
	//temp->next=t2->next;
	//temp->prev=t2->prev;
	
	t2->next=t1->next;
	t2->prev=t1->prev;
	tail=t1;
	}
	else if (t1==head && t2== tail)
	{
	//t1->prev->next=t2;//t1->next;
	t1->next->prev=t2;	
	
	//t2->next->prev=t1;//t2->prev;
	t2->prev->next=t1;//t1->prev;
	
	//t1->next=NULL;
	//t1->prev=t2->prev;
	
	t2->next=t1->next;
	t2->prev=NULL;
	head=t2;
	tail=t1;
	}
	else
	{
	//temp->prev->next=t2;//t1->next;
	//temp->next->prev=t2;	
	
	t2->next->prev=t1;//t2->prev;
	t2->prev->next=t1;//t1->prev;
	
	//temp->next=t2->next;
	//temp->prev=t2->prev;
	
	t2->next=t1->next;
	t2->prev=t1->prev;
	}
	t2=t1;
	t1=temp;
	//
//	t2->prev=temp->prev;
//	t2->next=temp->next;
	
	
	printf("\n%s    ",t1->name);
	printf("%s   ",t2->name);
	//printf("%s   ",temp->name);
	getch();
	printf("\n");
	display(records_num,0);
	
	
	
} */

void swap (struct contact * t1,struct contact * t2)
{       
	//struct contact* temp1=createNode();
	//struct contact* temp2=createNode();
	//temp1=t1;
	//temp2=t2;
	char name[21];
	char phone[21];
	char address[21];
	
	strcpy(name,t1->name);
	strcpy(phone,t1->phone);
	strcpy(address,t1->address);
	
	strcpy(t1->name,t2->name);
	strcpy(t1->phone,t2->phone);
	strcpy(t1->address,t2->address);
	
	strcpy(t2->name,name);
	strcpy(t2->phone,phone);
	strcpy(t2->address,address);
	
	/*if (t1==head)
		head=t2;
	if (t2==tail)
		tail=t2;
	t1->prev->next=t1->next;
	t2->next->prev=t2->prev;
	t2->next->prev=t2->prev;
	t2->prev=t1->prev;
	t1->next=t2->next;
	t1->prev=t2;
	t2->next=t1;*/
}

void search_by(int search_type){				//done
		
		int i,j,checkPrint,stop;
		int pos=0,terminate=0,End=0,page=0;
		char name[15],key , search_word;
		char * ptr;
		ptr=name;

		for(i=19;i<65;i++){
			for(j = 7;j<16; j++){
				gotoxy(i,j);
				textattr(highlight2);
				cprintf("%c" , ' ');
			}
		}
		gotoxy(35,8);
		textcolor(BLACK);
		
		if(search_type==1){
			printf("Search By Name\n");
			gotoxy(28,10);
			printf("Name: ");
		}
		else if(search_type==2){
			printf("Search By Phone\n");
			gotoxy(28,10);
			printf("Phone: ");
		}
		
		// draw button
		gotoxy(35,13);
	    printf("Search");
		textcolor(BLACK);
		
		gotoxy(45,13);
	    printf("Cancel");
		textcolor(WHITE);
	
	
		gotoxy(35,10);
		textbackground(BLUE);
		for(i=35;i<51;i++){
			cprintf("%c" , ' ');
			gotoxy(i+1,10);
		}
			
		gotoxy(35,10);
		//***************** Enter Search Word (Phone , Name)*************************//
	   do{
			key=getch();
			stop=key;
			switch(stop){

				case backspace:
					if(page==0){
						pos--;
						if(pos<0) pos=0;
						else{
							deleteChar(ptr,pos-1,End,35,10,backspace);
							End=End-1;
						}
					}
					break;
				
				case esc :
					terminate=1;
					break;
					
				case enter:
					if(page==2){
						// read from file
					   //	display();
						if(head==NULL){
							textattr(normal);
							clrscr();
							footer();
							draw_header();
							NotFound();
						}
						else{
							textattr(normal);
							clrscr();
							footer();
							draw_header();
							for(i=End;i<15;i++){
								name[End]='\0';
							}
							// search by name
							if(search_type==1){
								search_result(name," ");	
							}
							// search by phone
							else if(search_type==2){
								search_result(" ",name);	
							}					
						}
						terminate=1;
					}
					else if (page==1){
						textattr(normal);
						clrscr();
						footer();
						draw_header();
						terminate=1;
					}
					break;

				case NULL:
					stop=getch();
					switch(stop){
						case esc:
							terminate=1;
							break;

						case home:
						   if(page==0){
								pos=0;
								gotoxy(35+pos,10);	
							}
							break;

						case end:
							if(page==0){
								pos=end;
								gotoxy(35+pos,10);
							}
							break;
							
						case left:
							if(page==0){
								pos--;
								if(pos<=0){
									pos=0;
									gotoxy(35,10);
								}
								else{
									gotoxy(35+pos-1,10);
								}
							}
							else{
							// draw button
								if(page==1){
									page=2;
									gotoxy(35,13);
									printf("Search");
									
								}
								
								else{
								    page=1;
									gotoxy(45,13);
									printf("Cancel");
								}
							}
							
							break;

						case right:
							if(page==0){
								pos++;
								if(pos>=End) {
									pos=End;
									gotoxy(35+pos-1,10);
								}
								else gotoxy(35+pos,10);
							}
							else{
								// draw button
								if(page==1){
									gotoxy(35,13);
									printf("Search");
									page=2;
								}
								
								else{
									page=1;
									gotoxy(45,13);
									printf("Cancel");
								}
							}
								break;

						case del:
						    if(page==0){
								deleteChar(ptr,pos,End,35,10,del);
								pos=pos-1;
								if(pos<0) pos=0;
								End=End-1;
								if(End<0) End=0;
							}								
						    break;
								
						case up:
								page=0;
								gotoxy(35+pos,10);
								break;

					    case down:
								page=2;
						        gotoxy(35,13);
								textattr(highlight);
								printf("Search");  
						        break;
					}
					break;
				default:
					if(page==0){
						checkPrint=isprint(key);
						if(search_type==1){
							if(checkPrint && End<=15){
								*(ptr+pos)=key;
								if(pos!=0){
									gotoxy(35+pos,10);
								}
								cprintf("%c",key);
								gotoxy(35+pos,10);
								pos++;
								End++;
							}
							else{
								if(pos==End){
									End=End+1;
									pos=pos+1;
								}
								terminate=1;
								break;
							}
						}
						else if(search_type==2){
							if(checkPrint && End<=15 &&  isdigit(key)){
								*(ptr+pos)=key;
								if(pos!=0){
									gotoxy(35+pos,10);
								}
								cprintf("%c",key);
								gotoxy(35+pos,10);
								pos++;
								End++;
							}
							else{
								if(pos==End){
									End=End+1;
									pos=pos+1;
								}
								terminate=1;
								break;
							}
						}

					}
				}
		flushall();
	}while(!terminate);

}

// search processing
void search_result(char Name[21],char Number[21]){		//done

	struct contact * temp=head;
	struct contact * LastNode ;
	int pos=3 , stopLoop=0;
	char key;
	int i;
		if(strcmp(" ",Number)){
			while(temp!=NULL && strcmp(temp->phone,Number)){
				temp=temp->next;
			}
		}
		else{
			while((temp!=NULL && strcmp(temp->name,Name))){
				temp=temp->next;
			}
		}
		if(temp==NULL){
			textattr(normal);
			clrscr();
			footer();
			draw_header();
			NotFound();
		}
		
		else{
			search_result_screen(temp);
			temp=temp->next;
			do{
				flushall();
				key=getch();
				switch(key){
					case enter:
					// next button
					if(pos==3){
						if(strcmp(" ",Number)){
							while(temp!=NULL && strcmp(temp->phone,Number)){
								temp=temp->next;
							}
						}
						else{
							while((temp!=NULL && strcmp(temp->name,Name))){
								temp=temp->next;
							}
						}

						if(temp!=NULL){
							search_result_screen(temp);
							temp=temp->next;
						}
						else{
							textattr(normal);
							clrscr();
							footer();
							draw_header();
							stopLoop=1;
						}
					}
					// remove button
					else if(pos==2){
							if(temp==NULL) delete_contact(tail);
							else delete_contact(temp->prev);
							stopLoop=1;
					}
					
					// update button
					else if(pos==1){
							if(temp==NULL) Editing(tail);
							else Editing(temp->prev);
							stopLoop=1;
					}
					
					break;
				case esc:
					textattr(normal);
					clrscr();
					footer();
					draw_header();
					stopLoop=1;
					break;

				case right:
					pos++;
					if(pos>3) pos=1;
					if(pos==3) gotoxy(50,17);
					else if (pos==2) gotoxy(38,17);
					else if (pos==1) gotoxy(28,17);
					stopLoop=0;
					break;

				case left:
					pos--;
					if(pos<1) pos=3;
					if(pos==3) gotoxy(50,17);
					else if (pos==2) gotoxy(38,17);
					else if (pos==1) gotoxy(28,17);
					stopLoop=0;
					break;

			}
			}while(stopLoop==0);
			flushall();
			getch();
			textattr(normal);
			clrscr();
			footer();
			draw_header();
			
		}
	}
	
// line editor	
void deleteChar(char *pt,int pos,int size,int col,int row ,int button){			//done
		int i;
		//printf("\n%d,%d",pos,size);
		//printf("\n\n%d,%d,%d",col,pos,row);
		if(pos>0){
		if(button==del){
				if(pos==size){
					*(pt+pos)='\0' ;
					*(pt+pos+1)='\0' ;
					gotoxy(col+pos-1,row);
					cprintf("%c",'\0');
				    gotoxy(col+pos-2,row);
					if(pos-1<=0)  gotoxy(col-1,row);
				}
				else{
				for(i=pos-1;i<=size;i++) {
					*(pt+i)=*(pt+i+1);
					*(pt+i+1)='\0';
					gotoxy(col+i,row);
					cprintf("%c",*(pt+i));
					gotoxy(col+i+1,row);
					cprintf("%c",' ');
					if(i==0) gotoxy(col+pos,row);
					gotoxy(col+pos-1,row);
				}
				}
		}
		else{
			for(i=pos;i<=size-1;i++) {
				//printf("\n\n\n\n%d,%d",i,size-1);
				*(pt+i)=*(pt+i+1) ;
				gotoxy(col+i,row);
				cprintf("%c",*(pt+i));
				gotoxy(col+i+1,row);
				cprintf("%c",' ');
				gotoxy(col+i-1,row);
			}
		}
		}
}
