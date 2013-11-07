// Keith Mazanec

//  ||\\        //||      //\\      ========
//  ||  \\    //  ||     //  \\          //
//  ||    \\//    ||    //====\\       //
//  ||            ||   //      \\    //
//  ||            ||  //        \\  ========


#include "CMUgraphics.h"
#include <fstream.h>
#include "randgen.h"
#include "barrier.h"
#include "enemy.h"
#include "shot.h"

const int speed = 18; // the omnipotent speed variable

enum direction {N, E, S, W}; // used in the direction of images

class shot // when the lobster fires
{
public:
	// constructors //
	shot ()
	{
		myX = -1;
		myY = -1;
		myDirection = N;
	}
	shot (int x, int y, direction dir)
	{
		myX = x;
		myY = y;
		myDirection = dir;
	}
	void construct (int x, int y, direction dir)
	{
		myX = x;
		myY = y;
		myDirection = dir;
	}
	// moves the shot //
	void move(window &A)
	{
		for (int c=0; c<1; c++)
		{
			A.SetBrush(BLACK);
			A.DrawCircle(myX, myY, 3);
			A.UpdateBuffer();

			A.SetBrush(WHITE);
			A.DrawCircle(myX, myY, 3);
			A.UpdateBuffer();

			// CHANGE HERE //
			if (myDirection == 0) myY -= speed*.15;
			if (myDirection == 1) myX += speed*.15;
			if (myDirection == 2) myY += speed*.15;
			if (myDirection == 3) myX -= speed*.15;
			// CHANGE HERE //
		}
	}
	bool inrange(window &A)
	{
		return ( myX >= 0 && myX < A.GetWidth() && myY >= 0 && myY < A.GetHeight() );
	}

	int getmyx() { return myX; }
	int getmyy() { return myY; }

private:
	int myX;
	int myY;
	direction myDirection;
};

class barrier // used for rectangles that are constantly there
{
public:
	// Constructor //
	barrier(int px1, int py1, int px2, int py2)
	{
		x1 = px1;
		x2 = px2;
		y1 = py1;
		y2 = py2;
	}

	// Accessors //
	int getx1()	{ return x1; }
	int getx2()	{ return x2; }
	int gety1() { return y1; }
	int gety2() { return y2; }

	// Member functions //
	void draw(window & A)
	{
		A.DrawRectangle(x1,y1,x2,y2);
	}
	bool inbounds(int x, int y, image &now)
	{
		return (( x+now.GetWidth()/2<x1 || x-now.GetWidth()/2>x2 ) || ( y+now.GetHeight()/2<y1 || y-now.GetHeight()/2>y2 ));
	}
	bool inbounds(shot & here)
	{
		return (here.getmyx() > x2 || here.getmyx() < x1 || here.getmyy() > y2 || here.getmyy() < y1);
	}

private:
	int x1, x2, y1, y2;

};

class enemy // name says it all
{
public:
	// constructor //
	enemy (window &A)
	{
		RandGen r;
		myX = r.RandInt(A.GetWidth());
		myY = r.RandInt(A.GetHeight());
		bobomb.Open("bobomb.jpg", JPEG);
	}

	// randomly moves and displays enemy //
	void move (window &A)
	{
		RandGen r;

		// CHANGE HERE //
		int x = r.RandInt(-speed/6,speed/6), y = r.RandInt(-speed/6,speed/6);
		// CHANGE HERE //

		A.SetBrush(WHITE);
		A.DrawRectangle(myX,myY,myX+bobomb.GetWidth(),myY+bobomb.GetHeight());
		A.UpdateBuffer();
		if (myX + x > 0 && myX + x < A.GetWidth())	myX += x;
		if (myY + y > 0 && myY + y < A.GetHeight()) myY += y;
		A.DrawImage(bobomb,myX,myY);
		A.UpdateBuffer();
	}

private:
	int myX, myY; // top left corner coords of enemy
	image bobomb;
};


int main()
{
	window A(800,600,0,0);

	image up("up.jpg", JPEG);
	image down("down.jpg", JPEG);
	image right("right.jpg", JPEG);
	image left("left.jpg", JPEG);

	image prev = up; // default previous image

	direction dir = N; // default direction

	A.SetBuffering(true);
	int x=A.GetWidth()/2, y=A.GetHeight()/2;
	char k;

	shot s1; // shot
	enemy e1(A); // enemy

	int emc = 90; // enemy move count

	// list of impassable barriers in this level //
	barrier first(100,0,150,500);
	barrier second(100,500,600,550);

	while (k!=27)
	{
		// Draw the barriers with the correct color //
		A.SetBrush(STEELBLUE);
		A.SetPen(STEELBLUE);
		first.draw(A);
		second.draw(A);

		A.SetBrush(WHITE);
		A.SetPen(WHITE);

		A.GetKeyPress(k);
		switch (k)
		{
		case (4):
			A.DrawRectangle(x-prev.GetWidth()/2-1,y-prev.GetHeight()/2-1, 
							x+prev.GetWidth()/2+1, y+prev.GetHeight()/2+1);
			
			if (first.inbounds(x-speed,y,left) &&
				second.inbounds(x-speed,y,left))
				x-=speed;
			else
			{
				if(! first.inbounds(x-speed,y,left))
					x -= ((x-right.GetWidth()/2)-first.getx2());
				if(! second.inbounds(x-speed,y,left))
					x -= ((x-right.GetWidth()/2)-second.getx2());
			}

			
			A.DrawImage(left,x-left.GetWidth()/2,y-left.GetHeight()/2);
			prev = left;
			dir = W;
			A.UpdateBuffer();
			break;
		case (6): 
			A.DrawRectangle(x-prev.GetWidth()/2-1,y-prev.GetHeight()/2-1,
							x+prev.GetWidth()/2+1, y+prev.GetHeight()/2+1);

			if (first.inbounds(x+speed,y,right) &&
				second.inbounds(x+speed,y,right))
				x+=speed;
			else
			{
				if(! first.inbounds(x+speed,y,right))
					x += (first.getx1()-(x+right.GetWidth()/2));
				if(! second.inbounds(x+speed,y,right))
					x += (second.getx1()-(x+right.GetWidth()/2));
			}

			A.DrawImage(right,x-right.GetWidth()/2,y-right.GetHeight()/2);
			prev = right;
			dir = E;
			A.UpdateBuffer();
			break;
		case (8):
			A.DrawRectangle(x-prev.GetWidth()/2-1,y-prev.GetHeight()/2-1,
							x+prev.GetWidth()/2+1, y+prev.GetHeight()/2+1);

			if (first.inbounds(x,y-speed,up) &&
				second.inbounds(x,y-speed,up))
				y-=speed;
			else // moves exactly to the barrier
			{
				if(! first.inbounds(x,y-speed,up))
					y -= ((y-up.GetHeight()/2)-first.gety2());
				if(! second.inbounds(x,y-speed,up))
					y -= ((y-up.GetHeight()/2)-second.gety2());
			}


			A.DrawImage(up,x-up.GetWidth()/2,y-up.GetHeight()/2);
			prev = up;
			dir = N;
			A.UpdateBuffer();
			break;
		case (2):
			A.DrawRectangle(x-prev.GetWidth()/2-1,y-prev.GetHeight()/2-1,
							x+prev.GetWidth()/2+1, y+prev.GetHeight()/2+1);

			if (first.inbounds(x,y+speed,down) &&
				second.inbounds(x,y+speed,down))
				y+=speed;
			else
			{
				if(! first.inbounds(x,y+speed,down))
					y += (first.gety1()-(y+down.GetHeight()/2));
				if(! second.inbounds(x,y+speed,down))
					y += (second.gety1()-(y+down.GetHeight()/2));
			}


			A.DrawImage(down,x-down.GetWidth()/2,y-down.GetHeight()/2);
			prev = down;
			dir = S;
			A.UpdateBuffer();
			break;
		case (' '):
			if (dir == 0) s1.construct(x,y-prev.GetHeight()/2-3,dir);
			if (dir == 1) s1.construct(x+prev.GetWidth()/2+3,y,dir);
			if (dir == 2) s1.construct(x,y+prev.GetHeight()/2+3,dir);
			if (dir == 3) s1.construct(x-prev.GetWidth()/2-3,y,dir);
			A.UpdateBuffer();
			break;
		}

		if (s1.inrange(A) &&
			first.inbounds(s1) &&
			second.inbounds(s1)) s1.move(A);
		if (emc%90 == 1)
			e1.move(A);
		emc++;

	}
	A.SetWaitClose(false);
	return 0;
}

