// Keith Mazanec

//  ||\\        //||      //\\      ========
//  ||  \\    //  ||     //  \\          //
//  ||    \\//    ||    //====\\       //
//  ||            ||   //      \\    //
//  ||            ||  //        \\  ========


# ifndef BARRIER_H
# define BARRIER_H

//#include "shot.h"
//#include "enemy.h"

class barrier // used for rectangles that are constantly there
{
public:
	// Constructor //
	barrier(int px1, int py1, int px2, int py2, color col)
	{
		x1 = px1;
		x2 = px2;
		y1 = py1;
		y2 = py2;
		myColor = col;
	}

	// Accessors //
	int getx1()	{ return x1; }
	int getx2()	{ return x2; }
	int gety1() { return y1; }
	int gety2() { return y2; }

	// Member functions //
	void draw(window & A) // draws the barrier using unique color
	{
		A.SetBrush(myColor);
		A.DrawRectangle(x1,y1,x2,y2);
	}
	bool inbounds(int x, int y, image &now) // if player bumps barrier
	{
		return (( x+now.GetWidth()/2<x1 || x-now.GetWidth()/2>x2 ) || ( y+now.GetHeight()/2<y1 || y-now.GetHeight()/2>y2 ));
	}
	bool inbounds(int bbx1, int bby1, int bbx2, int bby2) // if enemy hits barrier
	{
		return (( bbx2<x1 || bbx1>x2 ) || ( bby2<y1 || bby1>y2 ));
	}
	bool inbounds(shot & here) // if shot hits barrier
	{
		if (here.getmyx() > x2 || here.getmyx() < x1 || here.getmyy() > y2 || here.getmyy() < y1)
		{
			return true;
		}
		here.ismoving = false;
		return false;
	}

private:
	int x1; // left edge
	int x2; // right edge
	int y1; // top edge
	int y2; // bottom edge
	color myColor; // each barrier stores its own unique color

};


# endif