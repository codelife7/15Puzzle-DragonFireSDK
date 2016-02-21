//===============================================
//      ******Header Files******
//===============================================
#include "DragonFireSDK.h"
#include <stdio.h>
#include <time.h>

//===============================================
//      ******ProtoType-s******
//===============================================
void Menu();
void LoadBase();
void LoadBoxPos();
void AssignIDxImageNumber();
bool CheckBoxes();
void LoadImages();
int Ontouch(int,int,int,int);
int MenuTouch(int,int,int,int);
void SwapBoxes(int,int);
void Shuffle(int[]);
void OnTimer();
//===============================================
//   ******Grid /Linear/ :D ??******
//===============================================
#define BOX 16
#define DATA 5

const int posx		  = 0;  //postions x
const int posy		  = 1;	//postion y
const int imagenumber = 2;	//image number , that changes
const int View		  = 3;  //image view handle
const int id		  = 4;  //static number/ box's postion

int Boxes[BOX][DATA]  = { 0 };
int idarray[16];
int temp[1][4];
int MIH;
int MVH;
int fonthandle;
int texthandle[4];
//===============================================
//			******Background******
//===============================================
struct BG
{
	int Posx;
	int Posy;
	int Image;
	int View;
}		Base;
//===============================================
//			 ******Functions******
//===============================================
//      ******Loading Background******
//===============================================

void LoadBase()
{
	Base.Posx  = 0;
	Base.Posy  = 0;
	Base.Image = ImageAdd("Assets/BG FL.png");
	Base.View  = ViewAdd(Base.Image, Base.Posx, Base.Posy);

	int GameText = FontAdd("Arial14Bold - FontMedium");
	TextAdd(75,85,"--",GameText);
	TextAdd(220,85,"93",GameText);

}
//===============================================
//	   ******Pre-Loading postion X****** 
//===============================================
void Callibrate()
{
	for(int cal = 0; cal < BOX; cal++)
	{
		Boxes[cal][posx] = 20; //posx all to 20
	}
}
//===============================================
//		 ******Positioning Boxes******
//===============================================
void LoadBoxPos()
{	
	Callibrate();
	int increment = 70; // 70 is the image length/width
	int box;
	for(box = 0; box < BOX; box++)
	{
		if (box <= 3)
		{
			if (box == 0)
			{
				Boxes[box][posx] = Boxes[box][posx] ; // 20 in box is at 1,5,9,13
			}
			else 
			{
				Boxes[box][posx] = Boxes[box][posx] + (increment * box) ;
			}
		
			Boxes[box][posy] = 130 ;
		}
		else if (box > 3 && box <= 7)
		{
			if (box == 4)
			{
				Boxes[box][posx] = Boxes[box][posx] ;

			} 
			else 
			{
				Boxes[box][posx] = Boxes[box][posx] + (increment * (box - 4)  );
			}
			Boxes[box][posy] = 202 ;
		}
		else if (box > 7 && box <= 11)
		{
			if (box == 8)
			{
				Boxes[box][posx] = Boxes[box][posx] ;
			} 
			else 
			{
				Boxes[box][posx] = Boxes[box][posx] + (increment * (box - 8)  );
			}
			 
			Boxes[box][posy] = 272 ; 
		}

		else if (box > 11 && box <= 15)
		{
			if (box == 12)
			{
				Boxes[box][posx] = Boxes[box][posx] ;
			} 
			else 
			{
				Boxes[box][posx] = Boxes[box][posx] + (increment * (box - 12)  ); //to stay in the limit 1-3
			}
			
			Boxes[box][posy] = 342 ;
		}
	}
}
//===============================================
//	******shuffling IDs and Images******
//After you call shuffle() on the array, its contents will be randomly sorted numbers from 0-15.
//===============================================
void shuffle(int items[16])
{
	int i;
	int rand1;
	int rand2;
	int temp;

	RandomSetSeed(time(NULL));
	for (i = 0; i < BOX; i++)
		items[i]=i;

	for (i = 0; i < 2000; ++i)
	{
		rand1 = Random(16);
		rand2 = Random(16);

		temp = items[rand1];
		items[rand1] = items[rand2];
		items[rand2] = temp;
	}
}
//===============================================
//   ******ID Implantation into core array******
//	    ******Image implantaion too ******
//===============================================
void AssignIDxImageNumber()
{
    for (int box = 0; box < BOX; box++)
    {	
		Boxes[box][imagenumber] = idarray[box];
		Boxes[box][id]		    = box; 
	}
}
//===============================================
//		     ******Check Boxes******
//===============================================
bool CheckBoxes()
{
	int chk =15;
	if(Boxes[chk][imagenumber] == chk)
	{
		chk = chk-5;
		if(Boxes[chk][imagenumber] == chk && Boxes[chk+1][imagenumber] == chk+1 && Boxes[chk+4][imagenumber] == chk+4  )
		{
			chk = chk-5;
			if(Boxes[chk][imagenumber] == chk && Boxes[chk+1][imagenumber] == chk+1 && Boxes[chk+2][imagenumber] == chk+2 && Boxes[chk+4][imagenumber] == chk+4 && Boxes[chk+8][imagenumber] == chk+8)
			{
				chk =chk-5;
				if(Boxes[chk][imagenumber] == chk && Boxes[chk+1][imagenumber] == chk+1 && Boxes[chk+2][imagenumber] == chk+2 && Boxes[chk+3][imagenumber] == chk+3 && Boxes[chk+4][imagenumber] == chk+4 && Boxes[chk+8][imagenumber] == chk+8 && Boxes[chk+12][imagenumber] == chk+12 )
				{
					return true;
				}
			}
		}
	}



	return false;

	/*
	if (array[15] == 0) {

		for (i=11; i > 0; i = i - 5) {

			cout << "Checking - " << i << endl;

			if (array[i-1] == i) {

				if (array[i-1] == 11) end = 12;
				else if (array[i-1] == 6) end = 8;
				else end = 4;

				// check in right horizontal direction
				for (j=i+1; j <= end; j++) {
					cout << "Checking - " << j << endl;
					if (array[j-1] != j) {
						found = false; break;
					}
				}

				// check in downward vertical direction
				for (j=i+4; j < 16; j = j + 4) {
					cout << "Checking - " << j << endl;
					if (array[j-1] != j) {
						found = false; break;
					}
				}
		
			}
			else found = false;

			if (found == false) break;
		
		}
	}
	else {
		found = false;
	}
	*/
}
//===============================================
//		     ******Swap Boxes******
//===============================================
void SwapBoxes(int box, int positionfactor)
{

	temp[0][0] = Boxes[box][imagenumber];
	Boxes[box][2] = Boxes[box + positionfactor][imagenumber];
	Boxes[box + positionfactor][imagenumber] = temp[0][0];


	if(positionfactor == 1)
	{
		ViewSetxy(Boxes[box][View], Boxes[box + 1][posx], Boxes[box + 1][posy]);
	}
	if(positionfactor == 4)
	{
		ViewSetxy(Boxes[box][View], Boxes[box + 4][posx], Boxes[box + 4][posy]);
	}
	if(positionfactor == -1)
	{
		ViewSetxy(Boxes[box][View], Boxes[box - 1][posx], Boxes[box - 1][posy]);
	}
	if(positionfactor == -4)
	{
		ViewSetxy(Boxes[box][View], Boxes[box - 4][posx], Boxes[box - 4][posy]);
	}

}

//===============================================
//		     ******On Touch******
//===============================================
int OnTouch(int box ,int event,int x,int y)
{ 
	int posfactor;

	if( Boxes[box + 1][imagenumber] == 15 )
	{
		posfactor = 1;
		SwapBoxes(box, posfactor);
	}
	if( Boxes[box - 1][imagenumber] == 15 )
	{
		posfactor = -1;
		SwapBoxes(box, posfactor);
	}
	if( Boxes[box + 4][imagenumber] == 15 )
	{
		posfactor = 4;
		SwapBoxes(box, posfactor);
	}
	if( Boxes[box - 4][imagenumber] == 15 )
	{
		posfactor = -4;
		SwapBoxes(box, posfactor);
	}	
	if (CheckBoxes()) 
	{
		fonthandle = FontAdd("Arial12Bold - FontSmall");
		texthandle[0] = TextAdd(120,300,"Solved :D",fonthandle);
	}
	return 0;
}
//===============================================
//		******Loading Images******
//===============================================
void LoadImages()
{
	char string[16];
	for( int box = 0; box < BOX ; box++ )
	{
		sprintf_s(string,"Assets/%02d.png",idarray[box]);
		Boxes[box][View] = ViewAdd(string, Boxes[box][posx], Boxes[box][posy],OnTouch, box );		
	}	
}
//===============================================
//		******MenuTouch Function******
//===============================================

int MenuTouch(int id, int event, int x, int y)
{
	if(id == 0)
	{
		LoadBase();
		LoadBoxPos();
		shuffle(idarray);
		AssignIDxImageNumber();
		LoadImages();
	}
	if(id == 1)
	{
		MIH = ImageAdd("Assets/Scores.png");
		ViewSetImage(MVH, MIH);

		fonthandle = FontAdd("Arial12Bold - FontSmall");
		texthandle[0] = TextAdd(100,490,"No Record Found",fonthandle);
	}
	if(id == 2)
	{
		MIH = ImageAdd("Assets/Instructions.png");
		ViewSetImage(MVH, MIH);
	}
	if(id == 3)
	{
		Menu();
	}

	if(id == 4)
	{
		MIH = ImageAdd("Assets/Facebook.png");
		ViewSetImage(MVH,MIH);

		fonthandle = FontAdd("Arial12Bold - FontSmall");
		texthandle[0] = TextAdd(120,490,"Subscribe",fonthandle);
		texthandle[1] =	TextAdd(80,510,"fb.com/Umair.Hasnain",fonthandle);
		texthandle[2] =	TextAdd(90,530,"fb.com/Sair.Samim",fonthandle);
		texthandle[3] =	TextAdd(98,550,"fb.com/hjgondal",fonthandle);
		OnTimer();
		

	}

	if(id == 5)
	{
		MIH = ImageAdd("Assets/i.png");
		ViewSetImage(MVH,MIH);
		//tell about project
	}
	return 0;
}

//===============================================
//		******Menu Function******
//===============================================
void Menu()
{
	MVH = ViewAdd("Assets/Menu.png",0,0);
	TouchAdd(70, 120, 180, 50, MenuTouch, 0);
	TouchAdd(70, 310, 180, 50, MenuTouch, 1);
	TouchAdd(70, 375, 180, 50, MenuTouch, 2);
	TouchAdd(20, 105,  40, 40, MenuTouch, 3);
	TouchAdd( 0, 450,  30, 30, MenuTouch, 3);
	TouchAdd(30, 440,  50, 40, MenuTouch, 4);
	TouchAdd(235,440,  50, 40, MenuTouch, 5);

}
//===============================================
//		******The MAIN Function******
//===============================================
void AppMain()
{
	Menu();
	
}
//===============================================
//      ******30 Fps Function******
//===============================================
void OnTimer()
{
	TextSetxy(texthandle[0],TextGetx(texthandle[0]), TextGety(texthandle[0]) - 2);
	TextSetxy(texthandle[1],TextGetx(texthandle[1]), TextGety(texthandle[1]) - 2);
	TextSetxy(texthandle[2],TextGetx(texthandle[2]), TextGety(texthandle[2]) - 2);
	TextSetxy(texthandle[3],TextGetx(texthandle[3]), TextGety(texthandle[3]) - 2);

}
//===============================================
//		    ******On Exit******
//===============================================
void AppExit()
{
 //RE-start may be 
}
//===============================================