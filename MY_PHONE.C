#include <stdio.h>
#include <conio.h>

#define esc 		27
#define enter 		13
#define up 		72
#define down 		80
#define home 		71
#define end 		79
#define normal 		0x07
#define highlight 	0x70
#define hilight         0x70
#define highlight2    	0x3f
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
	char name[10];
	int phone;
	char address[20];
	struct contact * prev;
	struct contact * next;

};  //heba

//global variable
struct contact * head , * tail; // heba

void draw_header(void);      //all
void header(char);       //all
void footer(void);       //all
void menu_view(void);    //hala
void menu_file(void);   // taher
void draw_phone_book(void);//char*);  //hala
void phone_book();

void menu_search(void);     //heba
void unshow_search_menu(void);  //heba
void search_by(int by_type);       //heba
void deleteChar(char *pt,int pos,int size, int button); // heba

void SaveFile(void) ; //sarah
void OpenFile(void) ; //sarah

int main(void)
{
	char key;
	int terminate=0; // heba
	textattr(normal);
	clrscr();

	flushall();
	footer();
	draw_header();
//Taher

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
	char new_file_name[15];
	int terminate=0;
	int j = 0 ;
	int i = 0;
	int pos=0;					///	to handle the current position of the cursor.
	char file_menu[4][10]={" new    " , " open   " , " save   " , " exit   "};

						//////////////////draw the main items in the file menu.///////////
				///initialize the file name by "           ";
				for(i=0;i<14;i++)
					new_file_name[i]=' ';
				new_file_name[14]='\0';
				gotoxy(1,2);
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
							case 0 :					//// means cursor on new
								textbackground(BLACK);
								clrscr();

								window(15,5,65,15);
								textbackground(BLUE);
								for(i=1;i<65;i++)
								{
									for(j = 1;j<10; j++)
									{
										gotoxy(i,j);
										textbackground(BROWN);
										cprintf("%c" , ' ');
									}
								}
								gotoxy(20,5);
								textcolor(BLACK);
								cprintf("Add new PhoneBook");

								gotoxy(3,7);
								cprintf("file name: ");


								window(30,12,50,12);
								gotoxy(1,1);
								textbackground(BLUE);
								for(i=0;i<sizeof(new_file_name);i++)
									cprintf("%c" , new_file_name[i]);

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
/*							case alt_v:
							case right:
								textattr(normal);
								clrscr();
								footer();
								header(alt_v);
	*/
							break;
							case up :
								pos--;
								if(pos<0)
									pos=3;
							break;

							case alt_f :

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
						break;
					case f2:
						//edit func
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
	
	int pos=0,i, size=2 , page;
	char key;
	int terminate=0;

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
							search_by(1);
							terminate=1;
							page=0;
							break;

						case 1:
							unshow_search_menu();
							search_by(2);
							terminate=1;
							page=0;
							break;
						}
					break;

			case esc:
				unshow_search_menu();
				terminate=0;
				page=0;
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
						terminate=1;
						page=1;
						break;

					case alt_v:
						terminate=1;
						page=2;
						break;

					case alt_s:
						terminate=1;
						page=3;
						break;
				}
				break;

		}
	}while(!terminate);
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

void search_by(int by_type){
		
		int i,j,checkPrint,stop;
		int pos=0,terminate=0,End=0,page=0;
		char name[10];
		char key;
		char * ptr;
		ptr=name;
		//window(19,11,60,18);
		//textbackground(BLUE);
		for(i=19;i<65;i++){
			for(j = 7;j<16; j++){
				gotoxy(i,j);
				textbackground(BROWN);
				cprintf("%c" , ' ');
			}
		}
		gotoxy(35,8);
		textcolor(BLACK);
		printf("Search By Name\n");

		if(by_type==1){
			gotoxy(28,10);
			printf("Name: ");
		}
		else{
			gotoxy(28,10);
			printf("Phone: ");
		}

		
		// draw button
		gotoxy(35,13);
	    printf("Search");
		textcolor(BLACK);
		
		gotoxy(45,13);
	    printf("Cancel");
		textcolor(BLACK);
	
	
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
							deleteChar(ptr,pos-1,End,backspace);
							End=End-1;
						}
					}
					break;
				
				case esc :
					terminate=1;
					break;
					
				case enter:
					if(page==2){
						
					}
					else if (page==1){
						for(i=19;i<65;i++){
							for(j = 7;j<16; j++){
								gotoxy(i,j);
								textbackground(highlight);
								cprintf("%c" , ' ');
							}
						}
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
								deleteChar(ptr,pos,End,del);
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
								page=1;
						        gotoxy(35,13);
								textattr(highlight);
								printf("Search");  
						        break;
					}
					break;
				default:
					if(page==0){
						checkPrint=isprint(key);
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
				}
		if(End>15) {
		    stop=enter;
			//getch();
		}
		/* else{
			gotoxy(1+pos-1,1) ;
		} */
		flushall();
	}while(!terminate);

}

void deleteChar(char *pt,int pos,int size, int button){
		int i;
		printf("\n%d,%d",pos,size);
		if(pos>0){
		if(button==del){
				if(pos==size){
					*(pt+pos)='\0' ;
					*(pt+pos+1)='\0' ;
					gotoxy(35+pos-1,10);
					cprintf("%c",'\0');
				    gotoxy(35+pos-2,10);
				}
				else{
				for(i=pos-1;i<size;i++) {
					*(pt+i)=*(pt+i+1);
					*(pt+i+1)='\0';
					gotoxy(35+i,10);
					cprintf("%c",*(pt+i));
					//if(i==0) gotoxy(1,1);
					//else gotoxy(1+i-1,1);
					
				}
				}
		}
		else{
			for(i=pos;i<size-1;i++) {
				//printf("\n%d,%d",i,size-1);
				*(pt+i)=*(pt+i+1) ;
				gotoxy(35+i,10);
				cprintf("%c",*(pt+i));
				gotoxy(35+i+1,10);
				cprintf("%c",' ');
			}
		}
		}
}

//create new node
struct contact * createNode(void){
	return (struct contact *)malloc(sizeof(struct contact));
}

// add struct 
void append (struct contact *ele){
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
void ReadFile(char szInputfile[25]){

	FILE *pfile_input;
	char szBuffer[100];

	char * pTemp;


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
		pTemp = strtok( szBuffer, "," );
		strcpy( record->name, pTemp ); 

		pTemp = strtok( NULL, "," ); 
		strcpy( record->phone, pTemp );

		pTemp = strtok( NULL, "," );
		strcpy( record->address, pTemp ); 
		
		append(record);
	} 

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
void OpenFile(void)
{
int startcol=17,currentcol=17,endcol=17,term=0,index=0,i;
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
	printf("Open File : ");
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
				fp=fopen(text,"r");
					while((ch =fgetc(fp))!=EOF)
						printf("%c",ch);

				fclose(fp);


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
}