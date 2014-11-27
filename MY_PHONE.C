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
#define tab 		9
#define alt_f 		33
#define alt_s 		31
#define alt_v	 	47
#define insert 		82
#define del 		83
#define f2    		60
#define right 		77
#define left 		75

void draw_header(void);      //all
void header(char);       //all
void footer(void);       //all
void menu_view(void);    //hala
void menu_file(void);   // taher
void draw_phone_book(void);//char*);  //hala
void phone_book();


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

//Hala
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
					printf("keda s");
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

//Sara
