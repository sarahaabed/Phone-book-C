#include <stdio.h>
#include <conio.h>

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

#define ok          111
#define cancel      99
#define backspace   8

void draw_header(void);   //all
void header(char);        //all
void footer(void);       //all
void menu_view(void);    //hala
void menu_file(void);    //taher
void draw_phone_book(void);//char*);  //hala
void phone_book();

void menu_search(void);     //heba
void unshow_search_menu(void);  //heba
void search_by(void);        //heba

void SaveFile(void) ; //sarah

void OpenFile(void) ; //sarah
void EditRecord(void);//sarah this will call CreatLineEditor 3 times
char *LineEditor(int col,int row); //sarah

void OpenFile(int found) ; //sarah
void EditRecord(void); //sarah
void new_file_window(void);//taher
void add_record_window(void);


int main(void)
{
	char key;
	textattr(normal);
	clrscr();

	flushall();
	footer();
	draw_header();
	key=getch();
//Taher
		//add_record_window();
		//getch();
		//return;
//Hala
do{
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
		else if(key==esc){
			terminate=1;
		}

//Heba
	}while(!terminate); //heba

//Sara

//	getch();
	return 0;



}

void draw_header(void)
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

void header(char key)
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
	//hanlde right and left arrows in future

}


void footer(void)
{
	gotoxy(1,25);
	textattr(highlight);
	cprintf("  Alt+f File    Alt+V  View     Alt+s  Search                                  ");
	gotoxy(1,1);
	textattr(normal);
}


//Taher


void menu_file(void)
{
   char key;
   int terminate=0;
   int i = 0;
   int pos=0;        ///    to handle the current position of the cursor.
   char file_menu[4][20]={"   new    " , "   open   " , "   save   " , "   exit   "};
 
                         //////////////////draw the main items in the file menu.///////////
               clrscr();
               textattr(normal);
               footer();
               draw_header();
               gotoxy(1,2);
               ////dy awel marra
               for(i=0;i<4;i++)
                       {
                           if(i==pos)
                                   textbackground(YELLOW);
                           gotoxy(1,i+2);
                           cprintf("%s",file_menu[i]);
                           textattr(highlight);
                       }
                       
               ///////////////initilizing new file name//////////////////////
               do{
                   key = getch();
                   if(key == esc)
                       break;
                   if(key == enter)
                   {
                       switch(pos)
                       {
                           case 0 :                            //// means cursor on new
                           textbackground(BLACK);
                           clrscr();
                           footer();
                           draw_header();
						  // gotoxy(17,7)
						  // cprintf("add new phonebook");
                           OpenFile(0);
						   //new_file_window();
                           break;
						   case 1 :
						   textbackground(BLACK);
                           clrscr();
                           footer();
						   OpenFile(1);
						   draw_phone_book();
                           break;
						   
						   case 2 :
							textbackground(BLACK);
                           clrscr();
                           footer();
                           draw_header();
                           SaveFile();	
						   break;
                       
					   }
                   }
                   else if(key == NULL)
                       {
                           key = getch();
 
                       ///// handle the action
                       //hanlde right and left arrows in future
                       // we are here handling only up and down extended keys and alt_f to exit.
                       // all the key are extended
 
                       switch(key)
                       {
                           case down :
                               pos++;
                               if(pos>3)
                                   pos=0;
 
                           break;
/*                            case alt_v:
                           case right:
                               textattr(normal);
                               clrscr();
                               footer();
                               header(alt_v);
                               break;
   */
                           
                           case up :
                               pos--;
                               if(pos<0)
                                   pos=3;
                           break;
 
                           case alt_f :
                               textattr(normal);
                               clrscr();
                               footer();
                               draw_header();    
                               break;
 
                           default :
                               continue;
                       }
                           window(1,2,11,5);
                           textbackground(WHITE);
 
                           for(i=0;i<4;i++)
                           {
                               if(i==pos)
                                       textbackground(YELLOW);
                               gotoxy(1,i+1);
                               cprintf("%s",file_menu[i]);
                               textattr(highlight);
                           }
 
                       }
           }while(1);
 
}

void new_file_window(void)
{
   int j =0;
   int inner_pos=1;
   int i = 0;
   char key;
   char new_file_name[15];
   char window_buttons[3][15]={"             ","    OK    ","  CANCEL  "};
 
       ///initialize the file name by "           ";
               for(i=0;i<14;i++)
                   new_file_name[i]=' ';
               new_file_name[14]='\0';
           
   
                                   
                               
                               /////////////popup window to get the file name
                               
                               window(15,5,65,15);
                               for(i=1;i<65;i++)
                               {
                                   for(j = 1;j<10; j++)
                                   {
                                       gotoxy(i,j);
                                       textbackground(BLUE);
                                       cprintf("%c" , ' ');
                                   }
                               }
                               gotoxy(20,5);
                               textcolor(BLACK);
                               cprintf("Add new PhoneBook");
 
                               gotoxy(3,7);
                               cprintf("file name: ");
 
                               gotoxy(20,7);
                               textbackground(WHITE);
                               cprintf("%s",window_buttons[0]);    
 
                               gotoxy(15,9);
                               textattr(highlight);
                               cprintf("%s",window_buttons[1]);    
 
                               gotoxy(30,9);
                               textattr(highlight);
                               cprintf("%s",window_buttons[2]);    
                           do
                               {
                                               
                               key=getch();
 
								if(key==enter)
                                   {
                                       break;
                                   }
                               else if(key==esc)
                                   {
                                       break;
                                   }
                               else if (key==tab)
                                   {
                                       inner_pos++;
                                       if(inner_pos>2)
                                           inner_pos=0;
//                                        break;
                                   }
                               else
                                   {
                                       key=getch();
                                       switch(key)
                                           {
                                           case right :
                                                   if(inner_pos==1)
                                                       inner_pos++;
                                                   else if(inner_pos>2)
                                                       inner_pos=1;
                                                   else if(inner_pos==0)
                                                       inner_pos = 0;
                                                   break;
                                                   
                                               case left :
                                                   if(inner_pos==2)
                                                       inner_pos--;
                                                   else if(inner_pos==1)
                                                       inner_pos=1;
                                                   else if(inner_pos==0)
                                                       inner_pos = 0;
                                                   break;
                                               
                                           }
                                   }
                                   
                                   if(inner_pos==0)
                                       {
                                           gotoxy(20,7);
                                           textbackground(WHITE);
                                           cprintf("%s",window_buttons[0]);
                                           
                                           gotoxy(30,9);
                                           textattr(highlight);
                                           cprintf("%s",window_buttons[2]);
                                           gotoxy(15,9);
                                           textattr(highlight);
                                           cprintf("%s",window_buttons[1]);
 
                                           gotoxy(20,7);
                                           scanf("%s",new_file_name);
                                       }
 
                                   if(inner_pos==1)
                                       {
                                           gotoxy(15,9);
                                           textbackground(YELLOW);
                                           textcolor(BLACK);
                                           cprintf("%s",window_buttons[1]);
                                           
                                           gotoxy(30,9);
                                           textattr(highlight);
                                           cprintf("%s",window_buttons[2]);
 
                                       }
 
                                   if(inner_pos==2)
                                       {
 
                                           gotoxy(15,9);
                                           textattr(highlight);
                                           cprintf("%s",window_buttons[1]);
                                           
                                           gotoxy(30,9);
                                           textbackground(YELLOW);
                                           textcolor(BLACK);
                                           cprintf("%s",window_buttons[2]);
                                           
                                       }
                                   
                           }while(1);
}

void add_record_window(void)
{
	char new_info[3][15];

	int i=0;
	int 	j =0;
	char window_buttons[2][20]={"    OK    ","  CANCEL  "};
	for(j =0 ; j<3; j++)
		{
			for(i=0;i<14;i++)
				new_info[j][i]=' ';
			new_info[j][14]='\0';
		}
		
   window(15,5,65,15);
   for(i=1;i<65;i++)
   {
	   for(j = 1;j<10; j++)
	   {
		   gotoxy(i,j);
		   textbackground(BLUE);
		   cprintf("%c" , ' ');
	   }
   }
   
	gotoxy(25,1);
	cprintf("add new record");
	
	gotoxy(3,3);
	cprintf("Name");
	gotoxy(25,3);
	textbackground(WHITE);
	cprintf("%s",new_info[0]);   

	gotoxy(3,5);
	textbackground(BLUE);
	cprintf("Address");	
	gotoxy(25,5);
	textbackground(WHITE);
	cprintf("%s",new_info[1]);    
	
	gotoxy(3,7);
	textbackground(BLUE);
	cprintf("Phone");
	gotoxy(25,7);
	textbackground(WHITE);
	cprintf("%s",new_info[2]);    

	gotoxy(15,9);
	textattr(highlight);
	cprintf("%s",window_buttons[0]);    

	gotoxy(30,9);
	textattr(highlight);
	cprintf("%s",window_buttons[1]);    
	
}

//Hala

void menu_view(void)
{
	char key;
	int pos=0,i, stop=0, size=3;
	char view_menu[3][35]={" Sort by name    ", " Sort by phone   "," Sort by address "};
	flushall();
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
						menu_file();								//// go to the file menu
						break;
					case alt_s:
					case right:
						//call alts func
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
				draw_phone_book();
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
				stop=1;
				break;
		}
	}while(!stop);
}

void draw_phone_book(void)//char* file)
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
	gotoxy(1,25);
	cprintf("  Ins Insert   Del Delete   F2 Edit   Up/Down Move                          ");
	gotoxy(1,3);
	textattr(normal);
	phone_book();
}

void phone_book()
{
	int pos=0, stop=0;
	char key;
	int size;  //number of records in phone book
	do{
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

void menu_search(void){
	char search_menu[2][13]={"  by name   ","  by phone  "};
	int pos=0,i, size=2, page=0;
	char key;
	int terminate;
/* 	window(10,2,19,5);
	textattr(highlight); */
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
					switch(pos){
						case 0:
							unshow_search_menu();
							search_by();
							getch();
							terminate=1;
							break;

						case 1:
							clrscr();
							printf("\n Display Action Down here \n\n press any key to continuo");
							getch();
							break;
						}
					break;

			case esc:
				terminate=1;
				break;

			case tab:
				pos--;
				if(pos<0) pos=2;
				break;

			case NULL:
				key=getch();
				switch(key){

					case up:
						pos--;
						if(pos<0) pos=2;
						break;

					/* case PageUp:
						pos--;
						if(pos<0) pos=2;
						break; */

					case down:
						pos++;
						if(pos>2) pos=0;
						break;

					/* case PageDown:
						pos++;
						if(pos>2) pos=0;
						break ; */

					case home:
						pos=0;
						break;

					case end:
						pos=2;
						break;

					case alt_f:
						//menu_view();
						terminate=1;
						page=1;
						break;

					case alt_v:
						//menu_view();
						terminate=1;
						page=2;
						break;

					case alt_s:
						//menu_view();
						terminate=1;
						page=3;
						break;
				}
				break;

		}
	}while(terminate!=1);
	if(page==1){
		unshow_search_menu();
		menu_file();
	}
	else if(page==2){
		unshow_search_menu();
		menu_view();
	}
	else if(page==3){
		unshow_search_menu();
		menu_search();
	}
}

void unshow_search_menu(void){
	char search_menu[2][13]={"            ","            "};
	int i,size=2;
	flushall();
	textattr(normal);
	gotoxy(21,2);
	cprintf("            ");
	for(i=0;i<size;i++)
	{
			gotoxy(21,i+3);
			cprintf("%s",search_menu[i]);
			textattr(normal);
	}
		gotoxy(21,3+size);
		cprintf("            ");
}

void search_by(void){
		int i ,j;
		char Name[10];

		window(19,11,60,18);
		textbackground(BLUE);
		for(i=1;i<65;i++)
		{
			for(j = 1;j<10; j++){
				gotoxy(i,j);
				textbackground(BROWN);
				cprintf("%c" , ' ');
			}
		}
		gotoxy(16,2);
		textcolor(BLACK);
		printf("Search By Name\n");

		gotoxy(10,4);
		printf("Name: ");


		window(35,14,50,14);
		gotoxy(1,1);
		textbackground(BLUE);
		for(i=0;i<15;i++){
			cprintf("%c" , ' ');
		}
		gotoxy(1,1);
		// getch search word
		
		
}
//Sara
void SaveFile(void)
{
     char SaveOptions[2][10]={" Ok "," Cancel "};
	int i,j,terminate=0,pos=0,step=0 ;
	char SaveSelection ;
	clrscr();
	textattr(highlight);
	gotoxy(35,13);
	printf("Are  You Sure ? \n");

       for(i=0;i<25;i++)
	{
		gotoxy(30+i,12);
		printf("-");
		gotoxy(30+i,17);
		printf("-");

	}

		gotoxy(35,15);

       do{

       step=0;
		for(j=0;j<2;j++)

		{
		       if(j==pos)
				textbackground(BLUE);

			gotoxy(35+step,15) ;

			cprintf("%s",SaveOptions[j]);
			 textattr(highlight2);
		       //	printf("   ") ;

		       step+=8;

		}

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
					printf("\n\n\n ok handling in progress...\n");


				break;
				case 1:
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
				printf("\n\n\n ok handling in progress...\n");
				pos=0;
			break;

			case cancel:
				printf("\n\n\n cancelling...\n");
				pos=1;
				terminate=1;
			break;

			case esc:
				terminate=1;
			break;


		}

       }while(!terminate);


}

void OpenFile(int found)
{
int startcol=20,currentcol=20,endcol=20,term=0,index=0,i;
char key;
char *startptr,*currentptr,*endptr;
char text[21],ch;
int j;
FILE * fp;
currentptr=text;
startptr=text;
endptr=text;

		textattr(normal);
		clrscr();
		window(15,5,65,15);
		for(i=1;i<65;i++)
		{
		for(j = 1;j<10; j++)
		{
			gotoxy(i,j);
			textbackground(BROWN);
			cprintf("%c" , ' ');
		}
		}


		gotoxy(20,7);
		textbackground(BLUE);
		for(i=0;i<20;i++)
			cprintf(" ");

	textattr(normal);
	gotoxy(5,7);
			///////////////////////////////////////
	if(found == 0)
			printf("Create New File");
	
	else if(found == 1)
		printf("Open File : ");
		////////////////////////////////////////////
	gotoxy(30,9);
	textattr(hilight) ;
	cprintf("\n OK ") ;
	
   while(!term){

	 gotoxy(currentcol,7);
	 key=getch();
		if (key==NULL)
			key=getch();

		switch(key){


			case right :
				if(currentcol<41){
					currentcol++;
					currentptr++;
						  }
			break;
			case left:
				if(currentcol>0 && currentcol>startcol)
				{
				currentcol--;
				currentptr--;
				}
			break ;
			case end:
				currentcol=endcol;
				currentptr=endptr;

			break;
			case home:
				currentcol=startcol;
				currentptr=startptr;

			break ;

			case up :
				continue;
			break;

			case down :
				continue;
			break;

			case enter:
				textattr(normal);
				clrscr();
				*endptr='\0';
				fp=fopen(text,"a+");
					//while((ch =fgetc(fp))!=EOF)
						//printf("%c",ch);

				//fclose(fp);
				term=1;
			break ;
			 case esc :
				term=1;
			 break;
			  default:
				gotoxy(currentcol,15);
				*currentptr=key;

			 if(currentcol<41) {
			 currentcol++;
			 currentptr++;
					 }
			 if(endcol<currentcol)
				{
					endcol++;
					endptr++;

				  }
			  textattr(hilight);
			 cprintf("%c",key);



		  }
	 }
	 if(found == 0)
	 {
				textbackground(BLUE);
				textcolor(WHITE);
				printf("file created");
				
				
	}
}


void EditRec (void)

{

int startcol=20,currentcol=20,endcol=20,term=0,index=0,i;
char key;
char *startptr,*currentptr,*endptr;
char EditFeilds[3][16]={"Name","phone","address"},text[21];
int j,step,row=5;
currentptr=text;
startptr=text;
endptr=text;

		textattr(normal);
		clrscr();
		window(15,5,65,15);
		for(i=1;i<65;i++)
		{
		for(j = 1;j<10; j++)
		{
			gotoxy(i,j);
			textbackground(BROWN);
			cprintf("%c" , ' ');
		}
		}

	      for(i=0;i<3;i++)
	      {
		gotoxy(12,5+step);
		puts(EditFeilds[i]);
		gotoxy(20,5+step) ;
		textbackground(BLUE);
		for(j=0;j<22;j++)
			cprintf(" ");
		step+=2;

	       }
	       gotoxy(30,11);
	       textattr(hilight) ;
	       cprintf(" OK ");

   while(!term){


	 gotoxy(currentcol,row);
	 key=getch();
		if (key==NULL)
			key=getch();

		switch(key){


			case right :
				if(currentcol<41){
					currentcol++;
					currentptr++;
						  }
			break;
			case left:
				if(currentcol>0 && currentcol>startcol)
				{
				currentcol--;
				currentptr--;
				}
			break ;
			case end:
				currentcol=endcol;
				currentptr=endptr;

			break;
			case home:
				currentcol=startcol;
				currentptr=startptr;

			break ;

			case up :
				row-=2;
				if(row>5)
				row=9;
			break;

			case down :
				row+=2;
				if(row>11)
				row=5;
			break;

			case enter:
				textattr(normal);
				clrscr();
				*endptr='\0';
		     //		puts(text);   //text hold only last record
				term=1;       //i have to make extra two text arrays
			break ;
			 case esc :
				term=1;
			 break;
			  default:
				gotoxy(currentcol,15);
				*currentptr=key;

			 if(currentcol<41) {
			 currentcol++;
			 currentptr++;
					 }
			 if(endcol<currentcol)
				{
					endcol++;
					endptr++;

				  }
			  textattr(hilight);
			 cprintf("%c",key);



		  }
	 }
}

void EditRecord (void)
{
char EditFeilds[3][16]={"Name","phone","address" };
int j,step1=0,step2=0;
char * result;
int i;
textattr(normal);
		clrscr();
		window(15,5,65,15);
		for(i=1;i<65;i++)
		{
			for(j = 1;j<10; j++)
			{
				gotoxy(i,j);
				textbackground(BROWN);
				cprintf("%c" , ' ');
			}
		}

	      for(i=0;i<3;i++)
	      {
		gotoxy(12,5+step1);
		puts(EditFeilds[i]);
		gotoxy(20,5+step1);
		textbackground(BLUE);
		for(j=0;j<22;j++)
		cprintf(" ");
		step1+=2;
		}

		gotoxy(30,9);
		textattr(hilight) ;
		cprintf("\n OK ") ;

		for(i=0;i<3;i++)
		{
		result=(char *)LineEditor(20,5+step2);
		if(result[0]=='\0')
			break;
		puts(result);
		step2+=2;
	       }

}

char* LineEditor(int col,int r)
{
int startcol=col,currentcol=col,endcol=col,term=0,index=0,i;
char key;
int row=r;
char *startptr,*currentptr,*endptr;
char text[50],ch;
currentptr=text;
startptr=text;
endptr=text;
text[0]='\0';

   while(!term){

	 gotoxy(currentcol,row);

	 key=getch();
	 flushall();
		if (key==NULL)
			key=getch();
			flushall();

		switch(key){


			case right :
				if(currentcol<41){
					currentcol++;
					currentptr++;
						  }
			break;
			case left:
				if(currentcol>0 && currentcol>startcol)
				{
				currentcol--;
				currentptr--;
				}
			break ;
			case end:
				currentcol=endcol;
				currentptr=endptr;

			break;
			case home:
				currentcol=startcol;
				currentptr=startptr;

			break ;


				case up :
				row-=2;
				if(row>5)
				row=9;
			break;

			case down :
				row+=2;
				if(row>11)
				row=5;
			break;

			case enter:
			      //	textattr(normal);
				*endptr='\0';
				term=1;
			break ;
			 case esc :
				term=1;
			 break;
			  default:
				gotoxy(currentcol,15);
				*currentptr=key;

			 if(currentcol<41) {
			 currentcol++;
			 currentptr++;
					 }
			 if(endcol<currentcol)
				{
					endcol++;
					endptr++;

				  }
			  textattr(hilight);
				 cprintf("%c",key);



		  }
	 }
   return text;
	 }
