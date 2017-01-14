#include <iostream>
#include <cmath>

#define smalldist 0.001
#define smalldistp2 0.000001

struct intersection
{
	int itype;
		//endpoints intersect=1
		//line segments are the same=2
	//?: How many endpoints are within smalldist of the other's line segment?
		//line segments overlap but have 1 or 2 diffent endpoints
		//one line segment terminates in the
		// middle range of another line segment
	//Then, if no endpoints in range of other's line, test this;
		//line segments intersect at a point but share no endpoints
		//line segments do not intersect. (parallel or not).
	double xi,yi;
};

intersection FindIntersection(double ax1, double ay1,
				 double ax2, double ay2,
				double bx1, double by1,
				double bx2, double by2);

int main ()
{
	cout << "ThrottleEstimate1_10_2004.\n";

	double throttle;
	double throttles[4];
	int i;
	//double px[4] = {-1100, 100, 1000, -100};
	//double py[4] = {-100, -100, 100, 100};
	double px[4] = { 100 ,1000, -100,-1100};
	double py[4] = {-100,100,100,-100};
	
	
	double lendiag1 = sqrt(pow((px[0]-px[2]),2)+pow((py[0]-py[2]),2));
	double lendiag2 = sqrt(pow((px[1]-px[3]),2)+pow((py[1]-py[3]),2));
	cout << "diagonal lengths: "<<endl;cout << lendiag1 <<endl;cout <<lendiag2<<endl;	
//uble angle1 =	// a dot b = |a|*|b|*cos(theta)
	double theta1= 180.0-180/3.1415926*acos (
		 ( (px[0]-px[3])*(px[1]-px[0])
		+(py[0]-py[3])*(py[1]-py[0]) )
		/ sqrt((px[0]-px[3])*(px[0]-px[3])+(py[0]-py[3])*(py[0]-py[3]) )
		/ sqrt((px[1]-px[0])*(px[1]-px[0])+(py[1]-py[0])*(py[1]-py[0]) )
		);
	cout << "angle 1 is "<< theta1 << endl;

	double theta2= 180.0-180/3.1415926*acos (
		 ( (px[1]-px[0])*(px[2]-px[1])
		+(py[1]-py[0])*(py[2]-py[1]) )
		/ sqrt((px[1]-px[0])*(px[1]-px[0])+(py[1]-py[0])*(py[1]-py[0]) )
		/ sqrt((px[2]-px[1])*(px[2]-px[1])+(py[2]-py[1])*(py[2]-py[1]) )
		);
	cout << "angle 2 is "<< theta2 << endl;

	double theta3= 180.0-180/3.1415926*acos (
		 ( (px[2]-px[1])*(px[3]-px[2])
		+(py[2]-py[1])*(py[3]-py[2]) )
		/ sqrt((px[2]-px[1])*(px[2]-px[1])+(py[2]-py[1])*(py[2]-py[1]) )
		/ sqrt((px[3]-px[2])*(px[3]-px[2])+(py[3]-py[2])*(py[3]-py[2]) )
		);
	cout << "angle 3 is "<< theta3 << endl;
	
	double theta4= 180.0-180/3.1415926*acos (
		 ( (px[3]-px[2])*(px[0]-px[3])
		+(py[3]-py[2])*(py[0]-py[3]) )
		/ sqrt((px[3]-px[2])*(px[3]-px[2])+(py[3]-py[2])*(py[3]-py[2]) )
		/ sqrt((px[0]-px[3])*(px[0]-px[3])+(py[0]-py[3])*(py[0]-py[3]) )
		);
	cout << "angle 4 is "<< theta4 << endl;

        //estimate inefficiency:
	//Use a unit involving the two legs touching the angle.
	//Just need to calculate the bounding rect and the fraction of area
	// covered by a parallelogram decided by the two legs and the angle.

	double xmin=px[0];
	double xmax=px[0];
	double ymin=py[0];
	double ymax=py[0];
	for (i=1;i<4;i++)
	{
		if (px[i]<xmin)
			xmin=px[i];
		if (py[i]<ymin)
			ymin=py[i];
		if (px[i]>xmax)
			xmax=px[i];
		if (py[i]>ymax)
			ymax=py[i];
	}
	cout << "x " << xmin << " to " << xmax << ", y " << ymin << " to " << ymax << endl;
	double ABound = (xmax-xmin)*(ymax-ymin);
	cout << ABound << "->ABound1" << endl;	




	double AParallelogram1=	sin(theta1*3.1415927/180.0)
			*sqrt((px[0]-px[3])*(px[0]-px[3])+(py[0]-py[3])*(py[0]-py[3]))
			*sqrt((px[1]-px[0])*(px[1]-px[0])+(py[1]-py[0])*(py[1]-py[0]));
	cout << AParallelogram1 << "->Aparallelogram1" << endl;

	throttles[0] = 1/ (ABound/AParallelogram1);
	cout << throttles[0] << "->repothrottle1" << endl;

	double AParallelogram2=	sin(theta1*3.1415927/180.0)
			*sqrt((px[1]-px[0])*(px[1]-px[0])+(py[1]-py[0])*(py[1]-py[0]))
			*sqrt((px[2]-px[1])*(px[2]-px[1])+(py[2]-py[1])*(py[2]-py[1]));
	cout << AParallelogram2 << "->Aparallelogram2" << endl;

	throttles[1] = 1/ (ABound/AParallelogram2);
	cout << throttles[1] << "->repothrottle2" << endl;

	double AParallelogram3=	sin(theta1*3.1415927/180.0)
			*sqrt((px[2]-px[1])*(px[2]-px[1])+(py[2]-py[1])*(py[2]-py[1]))
			*sqrt((px[3]-px[2])*(px[3]-px[2])+(py[3]-py[2])*(py[3]-py[2]));
	cout << AParallelogram3 << "->Aparallelogram3" << endl;

	throttles[2] = 1/ (ABound/AParallelogram3);
	cout << throttles[2] << "->repothrottle2" << endl;

	double AParallelogram4=	sin(theta1*3.1415927/180.0)
			*sqrt((px[3]-px[2])*(px[3]-px[2])+(py[3]-py[2])*(py[3]-py[2]))
			*sqrt((px[0]-px[3])*(px[0]-px[3])+(py[0]-py[3])*(py[0]-py[3]));
	cout << AParallelogram4 << "->Aparallelogram4" << endl;

	throttles[3] = 1/ (ABound/AParallelogram4);
	cout << throttles[3] << "->repothrottle4" << endl;

	throttle = throttles[0];
	for (i=1;i<4;i++)
	{
		if (throttles[i] < throttle)
			throttle=throttles[i];
	}
	cout << "repothrottle chosen is " << throttle << endl;


//  Now for an area calc using px[] and py[]:
	double areat1, areat2;
	double areaquad;
	
	/*
double px[4] = {-1100, 100, 1000, -100};
	double py[4] = {-100, -100, 100, 100};
*/
	//uses ymin from above.	
	
	areat1=abs( 
		  (0.5*((py[0]-ymin)+(py[1]-ymin))*( px[1]-px[0] ))
		- (0.5*((py[0]-ymin)+(py[3]-ymin))*( px[3]-px[0] ))
		- (0.5*((py[1]-ymin)+(py[3]-ymin))*( px[1]-px[3] ))
		);
	areat2= abs(
		  (0.5*((py[3]-ymin)+(py[1]-ymin))*( px[1]-px[3] ))
		- (0.5*((py[3]-ymin)+(py[2]-ymin))*( px[2]-px[3] ))
		- (0.5*((py[1]-ymin)+(py[2]-ymin))*( px[1]-px[2] ))
		);

	
	areaquad=areat1+areat2;

	cout << "area t1 = " << areat1 << ",  areat2 = " << areat2 << endl;
	cout << "area total = " << areaquad << endl;
	cout << "abs? " << abs(-1.5) << endl;

	return 0;

/*
	//float num = pow(3.0, 3);
	//std::cout << num << endl;
	
	//counters:
	int i;
	//set up the viewing area's 4 corners:
	//
	double vx1[4], vy1[4], vx2[4], vy2[4];
	double cx[4] = {0, 720, 720, 0};
	double cy[4] = {0, 0, 486, 486};
	for (i=0;i<4;i++)
	{
		vx1[i]=cx[i%4]; vy1[i]=cy[i%4];
		vx2[i]=cx[(i+1)%4]; vy2[i]=cy[(i+1)%4];
	}
	struct intersection myintersect=
		FindIntersection(720,0,15,15, 720,0,15,15);
	if (myintersect.itype==1)
	{
		cout << myintersect.xi << " " << myintersect.yi << endl;
				
	}
	if (myintersect.itype==2)
	{
		cout << "lines match endpoints." << endl;
	}
	return (0);
*/
}

intersection FindIntersection(double ax1, double ay1,
				 double ax2, double ay2,
				double bx1, double by1,
				double bx2, double by2)
{
	//Note: this function will return the x,y position from
	//  line a's endpoints if a and b share an endpoint within
	//  radius smalldist.

	struct intersection returnPoint;
	returnPoint.itype=-1;

	//check endpoints, check endpoints intersecting, then
	// check intersection.

	int done = 0;
	int donea1b1 = 0;
	int donea1b2 = 0;
	int donea2b1 = 0;
	int donea2b2 = 0;

	double distance2;
	distance2 = (bx1-ax1)*(bx1-ax1)+(by1-ay1)*(by1-ay1);
	if (distance2<smalldistp2)
	{
		donea1b1=1;
		done=1;
	}
	distance2 = (bx2-ax1)*(bx2-ax1)+(by2-ay1)*(by2-ay1);
	if (distance2<smalldistp2)
	{
		donea1b2=1;
		done=1;
	}
	distance2 = (bx1-ax2)*(bx1-ax2)+(by1-ay2)*(by1-ay2);
	if (distance2<smalldistp2)
	{
		donea2b1=1;
		done=1;
	}
	distance2 = (bx2-ax2)*(bx2-ax2)+(by2-ay2)*(by2-ay2);
	if (distance2<smalldistp2)
	{
		donea2b2=1;
		done=1;
	}
	/*cout << "found " << donea1b1 << " " <<
		donea1b2 << " " << donea2b1 << " " 
		<< donea2b2 << endl;
	*/

	if (done==1)
	{
		int cornermatchcount=
			donea1b1+donea1b2+donea2b1+donea2b2;
		if (cornermatchcount== 2)
		{
			returnPoint.itype=2;//line segments
				// share the same endpoints.
			return returnPoint;
		}
		if  (cornermatchcount== 1)
		{
			returnPoint.itype=1;
			if (donea1b1==1 || donea1b2==1)
			{
				returnPoint.xi=ax1;
				returnPoint.yi=ay1;
			}
			if (donea2b1==1 || donea2b2==1)
			{
				returnPoint.xi=ax2;
				returnPoint.yi=ay2;
			}
			return returnPoint;
		}
	}


	//find endpoints of b that are on line a:
	

	return returnPoint;

}