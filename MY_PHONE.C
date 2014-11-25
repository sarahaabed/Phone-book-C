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

	// Handle Alt+f, Alt+v, Alt+s
	gotoxy(12,12);
	switch(key)
	{
			case alt_f:
					printf("kede f");
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
