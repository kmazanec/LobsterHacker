// Keith Mazanec

//  ||\\        //||      //\\      ========
//  ||  \\    //  ||     //  \\          //
//  ||    \\//    ||    //====\\       //
//  ||            ||   //      \\    //
//  ||            ||  //        \\  ========


# ifndef SHOT_H
# define SHOT_H

//#include "barrier.h"
//#include "enemy.h"

class shot // when the lobster fires
{
public:
	// constructors //
	shot ()
	{
		myX = -1;
		myY = -1;
		myDirection = N;
		ismoving = false;
	}
	shot (int x, int y, direction dir)
	{
		myX = x;
		myY = y;
		myDirection = dir;
		ismoving = true;
	}
	void construct (int x, int y, direction dir) // used when the shot takes place so shot object can be reused
	{
		myX = x;
		myY = y;
		myDirection = dir;
		ismoving = true;
	}
	// moves the shot //
	void move(window &A)
	{
		if (!ismoving) return;

		int c = 0;
		while (c<level)
		{
			switch (c)
			{
			case 0:
				A.SetBrush(BLACK);
				break;
			case 1:
				A.SetBrush(MIDNIGHTBLUE);
				break;
			case 2:
				A.SetBrush(MEDIUMSLATEBLUE);
				break;
			case 3:
				A.SetBrush(LAWNGREEN);
				break;
			case 4:
				A.SetBrush(LIMEGREEN);
				break;
			case 5:
				A.SetBrush(PALEGOLDENROD);
				break;
			case 6:
				A.SetBrush(GOLD);
				break;
			case 7:
				A.SetBrush(DARKORANGE);
				break;
			case 8:
				A.SetBrush(MEDIUMVIOLETRED);
				break;
			case 9:
				A.SetBrush(DARKORCHID);
				break;
			}

			A.DrawCircle(myX, myY, 6+c);
			A.UpdateBuffer();
			
			c++;
		}

		A.SetBrush(WHITE);
		A.DrawCircle(myX, myY, 5+level);
		A.UpdateBuffer();

		// CHANGE HERE //
		if (myDirection == 0) myY -= speed/2;
		if (myDirection == 1) myX += speed/2;
		if (myDirection == 2) myY += speed/2;
		if (myDirection == 3) myX -= speed/2;
		// CHANGE HERE //
		
	}
	bool inrange(window &A) // if shot is in the window
	{
		if ( myX >= 0 && myX < A.GetWidth() && myY >= 0 && myY < A.GetHeight() )
			return true;
		ismoving = false;
		return false;
	}

	// accessors //
	bool ismoving;  //	used to fix the problem where the shot still remains
					//	at the barrier undisplayed and enemy can run into it
	int getmyx() { return myX; }
	int getmyy() { return myY; }

private:
	int myX;
	int myY;
	direction myDirection;

};

# endif