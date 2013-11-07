// Keith Mazanec

//  ||\\        //||      //\\      ========
//  ||  \\    //  ||     //  \\          //
//  ||    \\//    ||    //====\\       //
//  ||            ||   //      \\    //
//  ||            ||  //        \\  ========


# ifndef ENEMY_H
# define ENEMY_H

//#include "barrier.h"
//#include "shot.h"

class enemy // name says it all
{
public:
	// constructor //
	enemy (window &A)
	{
		bobomb.Open("bobomb.jpg", JPEG);
		RandGen r;
		myX = r.RandInt(A.GetWidth()-bobomb.GetWidth());
		myY = r.RandInt(A.GetHeight()-bobomb.GetHeight());
	}

	int x1 () { return myX; }
	int x2 () { return myX + bobomb.GetWidth(); }
	int y1 () { return myY; }
	int y2 () { return myY + bobomb.GetHeight(); }

	// randomly moves and displays enemy //
	bool move (window &A, shot &s, barrier &first, barrier &second, barrier &third, barrier &fourth, bool crashed)
	{
		// covers old enemy //
		A.SetBrush(WHITE);
		A.DrawRectangle(myX,myY,myX+bobomb.GetWidth(),myY+bobomb.GetHeight());
		A.UpdateBuffer();
		RandGen r;

		while ( ! ( first.inbounds(myX,myY,myX+bobomb.GetWidth(),myY+bobomb.GetHeight()) &&
					second.inbounds(myX,myY,myX+bobomb.GetWidth(),myY+bobomb.GetHeight()) &&
					third.inbounds(myX,myY,myX+bobomb.GetWidth(),myY+bobomb.GetHeight()) &&
					fourth.inbounds(myX,myY,myX+bobomb.GetWidth(),myY+bobomb.GetHeight()) ) )
		{
			myX = r.RandInt(A.GetWidth()-bobomb.GetWidth());
			myY = r.RandInt(A.GetHeight()-bobomb.GetHeight());
		}		

		// CHANGE HERE //
		int x = r.RandInt(-speed/2*level,speed/2*level), y = r.RandInt(-speed/2*level,speed/2*level);
//		int x = r.RandInt(-speed*level,speed*level), y = r.RandInt(-speed*level,speed*level);
		// CHANGE HERE //

		// keeps enemy within window
		if (myX + x > 0 && myX + x < A.GetWidth() - bobomb.GetWidth()) myX += x;
		if (myY + y > 0 && myY + y < A.GetHeight() - bobomb.GetHeight()) myY += y;
		if (first.inbounds(myX,myY,myX+bobomb.GetWidth(),myY+bobomb.GetHeight()) && 
			second.inbounds(myX,myY,myX+bobomb.GetWidth(),myY+bobomb.GetHeight()) &&
			third.inbounds(myX,myY,myX+bobomb.GetWidth(),myY+bobomb.GetHeight()) &&
			fourth.inbounds(myX,myY,myX+bobomb.GetWidth(),myY+bobomb.GetHeight()) )
		{
			A.DrawImage(bobomb,myX,myY);
			A.UpdateBuffer();
		}
		else // if the chosen new location is inside a barrier, don't move this turn
		{
			myX -= x;
			myY -= y;
		}

		// if enemy is hit by shot //
		if ( (s.ismoving &&
			s.getmyx() >= myX && s.getmyx() <= myX+bobomb.GetWidth() &&
			s.getmyy() >= myY && s.getmyy() <= myY+bobomb.GetHeight()) ||
			crashed )
		{
			image bomb("bomb.jpg",JPEG);
			A.DrawImage(bomb,myX-12,myY-12);
			A.UpdateBuffer();

			// reset enemy to new random position
			RandGen r;
			myX = r.RandInt(A.GetWidth()-bobomb.GetWidth());
			myY = r.RandInt(A.GetHeight()-bobomb.GetHeight());

			return false; // enemy is killed, returns false
		}
		return true; // returns true if enemy has moved without dying
	}

private:
	int myX, myY; // top left corner coords of enemy
	image bobomb;
};


# endif