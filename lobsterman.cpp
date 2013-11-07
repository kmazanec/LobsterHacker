// Keith Mazanec

//  ||\\        //||      //\\      ========
//  ||  \\    //  ||     //  \\          //
//  ||    \\//    ||    //====\\       //
//  ||            ||   //      \\    //
//  ||            ||  //        \\  ========


#include "CMUgraphics.h"
#include <fstream>
#include "randgen.h"

const int speed = 10; // the omnipotent speed variable
int level = 1;
int score = 0; // another very important variable that is used everywhere
enum direction {N, E, S, W}; // used in the direction of images or shots


#include "shot.h"
#include "barrier.h"
#include "enemy.h"


int main()
{
	window A(800,600,0,0);
	A.ChangeTitle("LOBSTER");

	image up("up.jpg", JPEG);
	image down("down.jpg", JPEG);
	image right("right.jpg", JPEG);
	image left("left.jpg", JPEG);

	image prev = up; // default previous image

	direction dir = N; // default direction

	A.SetBuffering(true);
	int x=A.GetWidth()/2, y=A.GetHeight()/2;
	char k;

	int mx, my; // mouse click coords

	shot s1; // shot
	enemy e1(A); // enemy

	bool crashed = false; // if player runs into enemy
	int emc = 90; // enemy move count

// ====>	MULTIPLE BARRIER OBJECTS BELOW //
	barrier first(0,0,800,50,STEELBLUE);
	barrier second(200,500,700,510,STEELBLUE);
	barrier third(690,200,700,400,STEELBLUE);
	barrier fourth(200,200,500,210,STEELBLUE);

	A.SetFont(35,BOLD,ROMAN,NULL);
	A.SetPen(BLACK,60);
	A.DrawString(80,260,"Shoot the bomb!!");
	A.UpdateBuffer();
	A.WaitKeyPress(k);
	A.SetBrush(WHITE);
	A.SetPen(WHITE,1);
	A.DrawRectangle(0,0,800,600);
	A.DrawImage(up,x-up.GetWidth()/2,y-up.GetHeight()/2);


	while (k!=27)
	{

// ====>	MULTIPLE BARRIER OBJECTS BELOW //
		first.draw(A);
		second.draw(A);
		third.draw(A);
		fourth.draw(A);

		A.SetPen(BLACK,1);
		A.SetFont(15,BOLD,ROMAN,NULL);
		A.DrawString(10,20,"Press 'esc' to quit");
		A.SetFont(25,BOLD,ROMAN,NULL);
		A.DrawString(500,15,"Score:");
		A.DrawInteger(600,15,score);
		A.DrawString(300,15,"Level:");
		A.DrawInteger(400,15,level);


		A.SetBrush(WHITE);
		A.SetPen(WHITE);

		A.GetKeyPress(k); // get user's next action

		switch (k)
		{
		case (4): // if left
			A.DrawRectangle(x-prev.GetWidth()/2-1,y-prev.GetHeight()/2-1, 
							x+prev.GetWidth()/2+1, y+prev.GetHeight()/2+1);
			
// ====>		MULTIPLE BARRIER OBJECTS BELOW //
			if (first.inbounds(x-speed,y,left) &&
				second.inbounds(x-speed,y,left) &&
				third.inbounds(x-speed,y,left) &&
				fourth.inbounds(x-speed,y,left))
				x-=speed;
			else // moves up to the barrier exactly
			{
				if(! first.inbounds(x-speed,y,left))
					x -= ((x-right.GetWidth()/2)-first.getx2());
				if(! second.inbounds(x-speed,y,left))
					x -= ((x-right.GetWidth()/2)-second.getx2());
				if(! third.inbounds(x-speed,y,left))
					x -= ((x-right.GetWidth()/2)-third.getx2());
				if(! fourth.inbounds(x-speed,y,left))
					x -= ((x-right.GetWidth()/2)-fourth.getx2());
			}

			
			A.DrawImage(left,x-left.GetWidth()/2,y-left.GetHeight()/2);
			prev = left;
			dir = W;
			A.UpdateBuffer();
			break;
		case (6): // if right
			A.DrawRectangle(x-prev.GetWidth()/2-1,y-prev.GetHeight()/2-1,
							x+prev.GetWidth()/2+1, y+prev.GetHeight()/2+1);

// ====>		MULTIPLE BARRIER OBJECTS BELOW //
			if (first.inbounds(x+speed,y,right) &&
				second.inbounds(x+speed,y,right) &&
				third.inbounds(x+speed,y,right) && 
				fourth.inbounds(x+speed,y,right))
				x+=speed;
			else // moves up to the barrier exactly
			{
				if(! first.inbounds(x+speed,y,right))
					x += (first.getx1()-(x+right.GetWidth()/2));
				if(! second.inbounds(x+speed,y,right))
					x += (second.getx1()-(x+right.GetWidth()/2));
				if(! third.inbounds(x+speed,y,right))
					x += (third.getx1()-(x+right.GetWidth()/2));
				if(! fourth.inbounds(x+speed,y,right))
					x += (fourth.getx1()-(x+right.GetWidth()/2));
			}

			A.DrawImage(right,x-right.GetWidth()/2,y-right.GetHeight()/2);
			prev = right;
			dir = E;
			A.UpdateBuffer();
			break;
		case (8): // if up
			A.DrawRectangle(x-prev.GetWidth()/2-1,y-prev.GetHeight()/2-1,
							x+prev.GetWidth()/2+1, y+prev.GetHeight()/2+1);

// ====>		MULTIPLE BARRIER OBJECTS BELOW //
			if (first.inbounds(x,y-speed,up) &&
				second.inbounds(x,y-speed,up) &&
				third.inbounds(x,y-speed,up) &&
				fourth.inbounds(x,y-speed,up) )
				y-=speed;
			else // moves exactly to the barrier
			{
				if(! first.inbounds(x,y-speed,up))
					y -= ((y-up.GetHeight()/2)-first.gety2());
				if(! second.inbounds(x,y-speed,up))
					y -= ((y-up.GetHeight()/2)-second.gety2());
				if(! third.inbounds(x,y-speed,up))
					y -= ((y-up.GetHeight()/2)-third.gety2());
				if(! fourth.inbounds(x,y-speed,up))
					y -= ((y-up.GetHeight()/2)-fourth.gety2());
			}


			A.DrawImage(up,x-up.GetWidth()/2,y-up.GetHeight()/2);
			prev = up;
			dir = N;
			A.UpdateBuffer();
			break;
		case (2): // if down
			A.DrawRectangle(x-prev.GetWidth()/2-1,y-prev.GetHeight()/2-1,
							x+prev.GetWidth()/2+1, y+prev.GetHeight()/2+1);

// ====>		MULTIPLE BARRIER OBJECTS BELOW //
			if (first.inbounds(x,y+speed,down) &&
				second.inbounds(x,y+speed,down) &&
				third.inbounds(x,y+speed,down) &&
				fourth.inbounds(x,y+speed,down))
				y+=speed;
			else // moves up to the barrier exactly
			{
				if(! first.inbounds(x,y+speed,down))
					y += (first.gety1()-(y+down.GetHeight()/2));
				if(! second.inbounds(x,y+speed,down))
					y += (second.gety1()-(y+down.GetHeight()/2));
				if(! third.inbounds(x,y+speed,down))
					y += (third.gety1()-(y+down.GetHeight()/2));
				if(! fourth.inbounds(x,y+speed,down))
					y += (fourth.gety1()-(y+down.GetHeight()/2));
			}


			A.DrawImage(down,x-down.GetWidth()/2,y-down.GetHeight()/2);
			prev = down;
			dir = S;
			A.UpdateBuffer();
			break;
		case (' '): // if user shoots, create a shot heading in the right direction from the claws
			if (dir == 0) s1.construct(x,y-prev.GetHeight()/2-3,dir);
			if (dir == 1) s1.construct(x+prev.GetWidth()/2+3,y,dir);
			if (dir == 2) s1.construct(x,y+prev.GetHeight()/2+3,dir);
			if (dir == 3) s1.construct(x-prev.GetWidth()/2-3,y,dir);
			A.UpdateBuffer();
			A.FlushKeyQueue();
			break;
		}

// ====>	MULTIPLE BARRIER OBJECTS BELOW //
		if (emc % 90 == 0&&
			s1.inrange(A) &&
			first.inbounds(s1)  &&
			second.inbounds(s1) &&
			third.inbounds(s1) &&
			fourth.inbounds(s1) ) s1.move(A);

		crashed = false;
		// check if user is touching enemy //
		if ( ( (x-prev.GetWidth()/2 > e1.x1() && x-prev.GetWidth()/2 < e1.x2()) || 
			   (x+prev.GetWidth()/2 > e1.x1() && x+prev.GetWidth()/2 < e1.x2()) ) &&
			 ( (y-prev.GetHeight()/2 > e1.y1() && y-prev.GetHeight()/2 < e1.y2()) ||
			   (y+prev.GetHeight()/2 > e1.y1() && y+prev.GetHeight()/2 < e1.y2()) ) )
		{
			crashed = true;
		}

		if (emc%90 == 0 ) // only moves every 90 frames
			if (!e1.move(A,s1,first,second,third,fourth,crashed)) // if enemy has been killed
			{
				A.SetPen(BLACK,1);
				A.SetFont(35,BOLD,ROMAN,NULL);
				A.DrawString(180,260,"Click to continue");
				A.UpdateBuffer();
				A.FlushMouseQueue();
				A.WaitMouseClick(mx,my);
				A.SetBrush(WHITE);
				A.SetPen(WHITE,1);
				A.DrawRectangle(0,0,800,600);
				A.UpdateBuffer();
				A.FlushKeyQueue();
				s1.ismoving = false;
				if (crashed)
					score -= 237;
				else
					score += 801;
			}
		emc++;

		if (emc%27000 == 0) // score diminishes with time
			score -= 13;
		if (emc%270000 == 0 && score < 0)
		{
			A.SetPen(BLACK,1);
			A.SetFont(75,BOLD,ROMAN,NULL);
			A.DrawString(180,260,"YOU LOSE!!!");
			A.UpdateBuffer();
			break;
		}
		if (score > level * 500)
			level ++;

	}
	A.WaitMouseClick(mx,my);
	A.SetWaitClose(false);
	return 0;
}