A project for detecting by given points the minimum circle that enclosing all points

the Main is checking if the radius is correct, if all points are checked and if there are "leaks" of points/

I used the welzel algoritem that every recursive iteration, decrease one point and check if it is in the boundery. and add it to vector
if the point is not in the boundery, continue. at the end by the given boundry we will determen :
if the circle is by two points of boundery, the center is the middle between them
if the circle is by three points of boundery, the center is by "circumCenter" equation that say that the center of a circle that "block" triangle is by the equation.
all other points are inside the circle.