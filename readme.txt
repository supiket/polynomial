This program takes a given polynomial and finds its roots using first the bisection method, then 
the secant method, and lastly a hybrid method composed of bisection method for first two iterations and 
secant method for the rest. Prints out the result and the number of iterations for each method.

FOR THIS PROGRAM TO WORK PROPERLY: 
Please enter 
1) The coefficients of the polynomial in descending power order  
2) The guess values for the root, the smaller one coming first 
3) And finally the tolerance value which determines the precision of the solution.

Bisection Method takes the two guess values and looks for a very short interval 
in which the function has a change in sign, it implies there is a root in the interval
if the function is continuous. The method begins with the given values for the interval and 
reduces the distance between them until a solution as accurately as the given tolerance is found.
At each iteration, the function's value is calculated at the midpoint of the current interval. 
And the half of the interval which does not have the sign of the value of midpoint is discarded.
When the iteration ends, the midpoint becomes the result.

Secant Method approximates the function by the secant line of the given points which are 
reasonably close to the exact root, then takes the zero of it as the next approximate solution. 
The line is refound in each iteration. Although it is complex, this process requires less 
iterations than the others.

Hybrid Method uses both methods, the bisection method for first two iterations and secant method 
for the rest of the iterations. It is in between the two methods by means of efficiency.
