#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

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

#define ok               111
#define cancel           99
#define backspace   8

struct contact{
	char name[15];
	int phone;
	char address[20];
	struct contact * prev;
	struct contact * next;

};  //heba

//global variable
struct contact * head , * tail; 					// heba

//functions prototypes
void draw_header(void);   							//all
void header(char);        							//all
void footer(void);       							//all
void menu_view(void);    							//hala
void menu_file(void);    							//taher
void menu_search(void);     						//heba
void open_file_window(int); 						//taher
char* line_editor(int,int,char, char*); 			//hala
void draw_phone_book(void);//char*);  				//hala
void phone_book(char*);								//hala



int ReadFile(char* szInputfile); 					//heba
struct contact * createNode(void); 					//heba
void append (struct contact *ele); 					//heba
void display(int,int);								//hala

void delete_contact(struct contact * temp); 		//heba

/*

//void unshow_search_menu(void);  //heba
void deleteChar(char *pt,int pos,int size, int button); // heba
void NotFound(void); //heba
void search_by_name(void);       //heba
void search_by_phone(void);       //heba
void hide_search_by(void); //heba
void search_result(char Name[10],int Number); //heba
void search_result_screen(struct contact * temp);//heba;
void hide_search_result(void); //heba

void SaveFile(void) ; //sarah


void EditRecord(void);//sarah this will call CreatLineEditor 3 times
//char *LineEditor(int col,int row); //sarah

void OpenFile(int found) ; //sarah
void EditRecord(void); //sarah

void add_record_window(void);
*/

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

	} while(!terminate); 

//Sara

//	getch();
	return 0;
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
   	int pos=0,i, stop=0, size=4;
   	char file_menu[4][20]={"   New    " , "   Open   " , "   Save   " , "   Exit   "};
	flushall();
	
	textattr(normal);
	clrscr();
	footer();
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
						menu_view();
						stop=1;
						break;
					case alt_s:
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
						open_file_window(0);
						//phone_book(file_name);
						//ReadFile(file_name);
						stop=1;
						break;
					case 2 :
						textbackground(BLACK);
						clrscr();
						footer();
						draw_header();
						//SaveFile();
						stop=1;
						break;
					case 3:
						exit(0);
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

void open_file_window(int create)   //done
{
	int size=2,stop=0;
   	int pos=-1;
   	int i = 0;
   	char key;
   	char* file_name;
   	char window_buttons[2][15]={"   OK    ","  CANCEL  "};         
   	FILE* fb;
                                               
	// new_file_name = "test file name";
	 ////////   
	file_name=(char*)malloc(21*sizeof(char));
	     
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
					line_editor(15,6,key,file_name);
					pos++;
				} 
		}
	}while(!stop);
	//free(file_name);
}

//Hala

void menu_view(void)   						  	//done
{
	char key;
	int pos=0,i, stop=0, size=3;
	char view_menu[3][35]={" Sort by name    ", " Sort by phone   "," Sort by address "};
	flushall();
	
	textattr(normal);
	clrscr();
	footer();
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
						menu_file();
						stop=1;								//// go to the file menu
						break;
					case alt_s:
					case right:
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
				getch();
				stop=1;

				//read from file func
				//pos cases
				switch (pos)
				{

					case 0:
						//sort by name func
						break;
					case 1:
						//sort by phone func
						break;
					case 2:
						//sort by address func
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

void phone_book(char* file_name)								//done
{
	int pos=0, stop=0, i=0;
	char key;
	int size;  //number of records in phone book
	struct contact* curr_contact;
	
	curr_contact=head;

	size=ReadFile(file_name);

	do{
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
						break;
					//Operations on records
					case insert:
						// add record func
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
							while(i<=pos)
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
}

//Heba

void menu_search(void)    //done
{
	char search_menu[2][13]={"  by name   ","  by phone  "};
	
	int pos=0,i, size=2;
	char key;
	int terminate=0;
	
	textattr(normal);
	clrscr();
	footer();
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
							
							//search_by_name();
							terminate=1;
							break;

						case 1:
				
							//search_by_phone();
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
						if(pos>2) pos=0;
						break;

					case home:
						pos=0;
						break;

					case end:
						pos=2;
						break;

					case alt_f:
						menu_file();
						terminate=1;
						break;

					case alt_v:
					case left:
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

//create new node
struct contact * createNode(void)
{
   return (struct contact *)malloc(sizeof(struct contact));
}
 
// add struct 
void append (struct contact *ele)
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
}                  
 
// read from file
int ReadFile(char* szInputfile)
{
 
   	FILE *pfile_input;
   	char szBuffer[100];
	int  records_num=0;
   	char * pTemp;
 
 	//open_file_window(0);
/* if( argc != 2 )
{
 
printf("No database file specify");
exit(0);
 
}
else
{
sprintf( szInputfile, "%s", argv[1] );
 
}  */
 
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
       strcpy( num, pTemp );
       record->phone=atoi(num);
       
       pTemp = strtok( NULL, "," );
       strcpy( record->address, pTemp ); 
       
       append(record);
       records_num++;
   }  
   return records_num;
}

void display(int records_num, int pos)
{
	struct contact *temp;
    int x=4,y=4, i=0;
    temp=head;
    
    while(temp!=NULL && i<records_num)
	{
		if (i==pos)
			textattr(highlight2);
		gotoxy(x,y);
       	cprintf("%s",temp->name);   
		gotoxy(x+25,y);
       	cprintf("%d",temp->phone);          
	   	gotoxy(x+50,y);
       	cprintf("%s",temp->address); 
       	textattr(normal);
			
		y++;
		i++;
        temp=temp->next; 
    } 
}

void delete_contact(struct contact * temp)
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
		else if (head!=tail && temp!=tail && temp!=head){
			temp->prev->next=temp->next;
			temp->next->prev=temp->prev;
			free(temp);
		}

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

//hala

char* line_editor(int col,int row, char key, char* arr)  //almost done
{
	//char arr[21];//, key;
	char *p_current=arr, *p_last=arr, *p_start=arr;
	int strt_column=col, cur_column=col, end_column=col,counter=0,stop=0;
	int max_chars_num=20;
	//clrscr();

	gotoxy(strt_column,10);
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
				}
				flushall();
				key=getch();
				break;
			
			case tab:
			case esc:
				*p_last='\0';
				 //return arr;
				 stop=1;
				 break;
			/*case enter:
				*(p_last)='\0';
				//p_last=p_start+20;
				gotoxy(strt_column,12);
				puts(arr);
				stop=1;
				break;*/
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
