// ID1 : 206336794 

#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_

#include <iostream>
#include <cmath>
#include <vector>
#include <assert.h> 

using namespace std;

// ------------ DO NOT CHANGE -----------
class Point{
public:
	float x,y;
	Point(float x,float y):x(x),y(y){}
};

class Circle{
public:
	Point center;
	float radius;
	Circle(Point c,float r):center(c),radius(r){}
};
// --------------------------------------

// implement

// A function for distance between 2 points
float distance(const Point& a, const Point& b){ 
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)); 
}

// A method to check if the point is inside the circle or in the boundery.
bool PointInCircle(const Circle& c, const Point& p){ 
    //if the dist between center and point greater then the raduis, the p is outside
    return distance(c.center, p) <= c.radius; 
} 
// A method to get the circumcircle by 4 values 
Point getCenter(float bx, float by, float cx, float cy){ 
    //by the circumCircle equation:
    float B = bx * bx + by * by; 
    float C = cx * cx + cy * cy; 
    float D = bx * cy - by * cx; 
    float X = (cy * B - by * C) / (2 * D);
    float Y = (bx * C - cx * B) / (2 * D);
    return Point(X,Y);
} 
// Get circle by 2 points (the middle is the center and radius)
Circle CircleBy2Points(const Point& A, const Point& B){
    // Set the center to be the midpoint of A and B 
    Point C = { (A.x + B.x) / 2, (A.y + B.y) / 2 }; 
    // Set the radius to be half the distance AB 
    float raduis =  distance(A, B) / 2;
    return Circle(C, raduis);
}
// Get circle by 3 points (by circumcircle equation)
Circle CircleBy3Points(const Point& A, const Point& B,const Point& C){ 
    // get center by the circumcenter equation (method)
    Point Center = getCenter(B.x - A.x, B.y - A.y, C.x - A.x, C.y - A.y); 
    Center.x += A.x; 
    Center.y += A.y; 
    float radius = distance(Center, A);
    return Circle(Center, radius);
} 

//check  whether the points lie inside the circle or not  

bool CircleCheck(const Circle& c, const vector<Point>& Bdr){ 
    for (const Point& p : Bdr) 
        if (!PointInCircle(c, p)){
            return false; 
        }
        return true; 
}

// check after the recursion if the boundery is 1\2\3 points.
Circle trivialCircle(vector<Point>& Bdr) 
{  

     assert(Bdr.size() <= 3);
    if (Bdr.empty()) { 
        return Circle(Point(0,0),0); 
    } 
    else if (Bdr.size() == 1) { 
        return Circle(Point(Bdr[0].x,Bdr[0].y),0); 
    } 
    else if (Bdr.size() == 2) { 
        return CircleBy2Points(Bdr[0], Bdr[1]); 
    } 
    // To 
    //check if the smalles circle determined by 2 points  
    for (int i = 0; i < 3; i++) { 
        for (int j = i + 1; j < 3; j++) { 
            Circle c = CircleBy2Points(Bdr[i], Bdr[j]); 
            if (CircleCheck(c, Bdr)){
                return c;
            }
        } 
    }
    return CircleBy3Points(Bdr[0], Bdr[1], Bdr[2]); 
}

// main welzl's algoritem - check every recursive prograss if the point
// is in the boundery or inside the circle, at the end go to the trivialCircle method
Circle welzlAlg(Point** p, vector<Point> Bdr, int n){ 

    // Base case when all points processed or |R| = 3 
    if (n == 0 || Bdr.size() == 3) { 
        return trivialCircle(Bdr); 
    } 
    // a random point for efficient
     int idx = rand() % n; 
    swap(p[idx], p[n - 1]); 
    // set of points by dicrease point p from the P array -  P - {p} 
    Circle d = welzlAlg(p, Bdr, n - 1); 
    if (PointInCircle(d, *p[idx])){ 
        return d; 
    } 
    // Otherwise, must be on the boundary of the MEC 
    Bdr.push_back(*p[idx]); 
    // Return the MEC for P - {p} and R U {p} 
    return welzlAlg(p, Bdr, n - 1); 
}

Circle findMinCircle(Point** points,size_t size){
    vector<Point> Boundery = {};
    return welzlAlg(points, Boundery, size); 
}

       

#endif /* MINCIRCLE_H_ */
