/* Function MinimumDetour(end_at_base) calculates minimum detour distance for one driver to pick up another driver and drop them off.
   The argument is true if the driver doing the picking is required to end at their own destination at end of drive
*/


#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <sstream>

using namespace std;


struct route{
	/* Vertices are A, B, C, D; longitutes and latitudes are given in degrees */

	string route_name;               /* Each route has 4 vertices; the route_name is in order of the vertex traversed */
	vector<double> longitudes;       /* The order is longitudes of vertex 1, 2, 3, 4 */
	vector<double> latitudes;        /* The order is latitudes of vertex 1, 2, 3, 4 */
	double routeLength;
		
	route(string a){
		route_name = a;
		for (int i = 0; i < 4; i++)
		{
			longitudes.push_back(0.0);
			latitudes.push_back(0.0);
		}
		
		routeLength = 0;		
	}

};

struct vertex{
	string vertex_name;
	double vertex_long;
	double vertex_lat;

	vertex(string m, double r, double q){
		vertex_name = m;
		vertex_long = r;
		vertex_lat =  q;
	}
};

double CalculateRoadDistance(double lng1, double lat1, double lng2, double lat2){
	/* 
	   Roads from point say A to point B in a city would depend on the map on the ground. 
	   But, no matter the curves or bends of the road, it is equal to a straight line of length AB where AB is
	   the total distance covered driving from A to B. I therefore assume that the distance between any two longitude/latitude
	   pair is equal to the length of the earth's arc between this pair of points.
	
	   The radian of an angle in a circle is the length of the corresponding arc on the circle;
	   Thus the difference in the longitude in radians will give the length of the arc, and similarly for 
	   the latitudes, 
	   
	   where Angle in radian = (pi/180)*(angle in degree) so that length of AB = angle in radian * radius of earth

	   This transforms the routes map into the sides of a quadrilateral with vertices A,B,C,D.

	   By my assumptions then, distance between A and B, AB = radius of earth * length of arc between AB
	*/

	double R = 6371.0; /* approximate radius of earth, assuming a perfect sphere */
	double a = ((R*M_PI) / double(180))*(lng1 - lng2);
	double b = ((R*M_PI) / double(180))*(lat1 - lat2);
	a = pow(a, 2.00);
	b = pow(b, 2.00);		
	return sqrt(a + b);  // Euclidean distance between two points

	}

double CalculateRouteLength(vector<double>& longis, vector<double> &lats){
	
	return ( CalculateRoadDistance(longis[0], lats[0], longis[1], lats[1]) + CalculateRoadDistance(longis[1], lats[1], longis[2], lats[2]) + CalculateRoadDistance(longis[2], lats[2], longis[3], lats[3]) );

}


void MinimumDetour(bool end_at_base)
{   
	route ACDB("ACDB"); 
	route ABCD("ABCD");
	route CABD("CABD");
	route CDAB("CDAB");
	
	vector<route> ValidRoutes;
	
	if (end_at_base == true)
	{   /* When it is required that the driver who does the picking ends up at their base or destination at the end of the journey */
		ValidRoutes.push_back(ACDB);
		ValidRoutes.push_back(CABD);
	}
	else
	{   /* When the driver who does the picking is only required to pass through their destination, not necessarily end the journey there */
		ValidRoutes.push_back(ACDB);
		ValidRoutes.push_back(CABD);
		ValidRoutes.push_back(ABCD);
		ValidRoutes.push_back(CDAB);
	}
	
	
	vector<vertex> vertices;
	vector<string> verticesNames = { "A", "B", "C", "D"};

	/* Generate random longitudes and latitudes for testing */
	for (size_t i = 0; i < 4; i++)
	{       
		int inum = (int)(rand() % 360 + (-180) );
		int inum2 = (int)(rand() % 180 + (-90) );
		vertex vect(verticesNames[i], inum, inum2);
		vertices.push_back(vect);
	}

	for (size_t j = 0; j < vertices.size(); j++)
	{
		string vname = vertices[j].vertex_name;
		for (size_t i=0; i <ValidRoutes.size() ; i++)
		{
			string StringAt = ValidRoutes[i].route_name; 

			/* Split a route name into char vector */
			vector<char> VectorOfCharAt(StringAt.begin(),StringAt.end());

			for (size_t k = 0; k < VectorOfCharAt.size(); k++)
			{
				stringstream c;
				string tempst;
				c << VectorOfCharAt[k];
				c >> tempst;
			
				if (tempst == vname)
				{				
					ValidRoutes[i].longitudes[k] = vertices[j].vertex_long;
					ValidRoutes[i].latitudes[k] = vertices[j].vertex_lat;					
				}
			}

		}

	}

	
	for (size_t i = 0; i < ValidRoutes.size(); i++)
	{
		ValidRoutes[i].routeLength = CalculateRouteLength(ValidRoutes[i].longitudes, ValidRoutes[i].latitudes);
	}

	/* Iterate through the valid routes vector container and find the route with the least route length */
	double MinLength = ValidRoutes[0].routeLength;  
	string MinRoute = ValidRoutes[0].route_name;
	for(size_t i = 1; i < ValidRoutes.size(); i++){
		if ( ValidRoutes[i].routeLength < MinLength){
			MinLength = ValidRoutes[i].routeLength;
			MinRoute = ValidRoutes[i].route_name;
			
		}
	}

	cout << "The minimum-length detour route is " << MinRoute << " which is " << MinLength << " km of driving distance."<< endl;
	

}

int main()
{
	srand(time(NULL));

	MinimumDetour(true);

	system("pause");
	return 0;
}