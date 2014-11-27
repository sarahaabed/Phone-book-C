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
#define tab 		9
#define alt_f 		33
#define alt_s 		31
#define alt_v	 	47
#define insert 		82
#define del 		83
#define f2    		60

void header(char);
void footer(void);

int main(void)
{
	char key;
	int pos,i;
	char menu[3][11]={" File     ", "View      ","Search    "};
	textattr(normal);
	clrscr();
	footer();

	gotoxy(1,1);
	textattr(highlight);
	for(i=0; i<3; i++)
		cprintf("%s", menu[i]);
	cprintf("                                                  ");
	key=getch();
	if (key == NULL)
		key=getch();
	

	header(key);
//Taher

//Hala

//Heba

//Sara




	getch();
	return 0;
}


void header(char key)
{

	char file_menu[4]][10]={"open      " , "new       " , "save      " , "exit      "};
	// Handle Alt+f, Alt+v, Alt+s
	gotoxy(12,12);
	switch(key)
	{
			case alt_f:
					printf("kede f");
					window(10,10,40,11);
					textcolor(BLACK);
					textbackground(WHITE);
					gotoxy(10,12);
					//textcolor(WHITE);
					//textattr(highlight);
					cprintf("%s"file_menu[0]);
					gotoxy(2,1);
					textattr(highlight);
					cprintf("%s"file_menu[1]);
					gotoxy(3,1);
					textattr(highlight);
					cprintf("%s"file_menu[2]);
					gotoxy(4,1);
					textattr(highlight);
					cprintf("%s"file_menu[3]);
					getch();
					
					break;
				case alt_s:
					printf("keda s");
					break;
				case alt_v:
					printf("keda v");
					break;
	}


		//hanlde right and left arrows in future


}

void footer(void)
{
	gotoxy(1,25);
	textattr(highlight);
	cprintf("  Alt+f File    Alt+V  View     Alt+s  Search                                  ");
	textattr(normal);
}


//Taher

//Hala

//Heba

//Sara
