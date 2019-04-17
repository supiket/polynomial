#include <iostream>
#include <math.h>
#include <string>
using namespace std;

class Poly{ 
	public:
		int degree; //the degree of a polynom is the power of the term with the highest power
		double *coeff; //for keeping the coefficients of the polynomial in a dynamic array
		Poly (int size); //the constructor for polynomial class
		~Poly (); //default destructor for polynomial class
		double getCoeff(int power); //a method for getting the coefficient of the term with the given power
		double f(double x); //finds the value of the polynomial function for a given x value
};

Poly::Poly(int size){ //the constructor for polynomial class
	coeff = new double [size];
    for (int i = 0; i < size; i++)
    {
        coeff[i] = 0; //sets the elements equal to zero as default
    }
    degree = size; //sets the degree of the polynomial, as explained inside the class
}

Poly::~Poly(){ //deletes the array after its job is done
    delete[] coeff; 
}

double Poly::getCoeff(int power){
	if (0 <= power) //checks if the term with the given power is non negative
  		return coeff[power]; //returns the coefficient of the term that has the given power
  	else if (power >= degree) //if a term with the given power does not exist, returns 0
  		return 0;
  	else
  		cout << "Index out of range"; //warning for out of range problem
}

double Poly::f(double x){ //finds the value of the polynomial function for a given x value
	double value = 0;
    double coeff = 0;
    for (int i = 0; i < degree; i++){ 
        coeff = getCoeff(i); //gets each coefficient by getCoeff method, in a loop
        value = value + (coeff * pow(x, degree - i - 1)); //adds each term's value to the sum
    }
    return value; //returns the value of the polynomial for the given x value
}

int main(int argc, char** argv) { //main function
	//the size of the polynom is determined by the arguments except the last three
	//which corresponds to argument number minus 4
	int size = argc - 4; 
	//creates thePol polynomial of calculated size via the constructor
	Poly thePol(size);
	
	for(int i = 1; i < argc - 3; i++){ 
		 thePol.coeff[i-1] = atof(argv[i]); //sets each value of coefficient array to given corresponding arguments
	}
	
	double guessx0 = atof(argv[argc-3]); //keeps the smaller guess in variable guessx0
	double guessx1 = atof(argv[argc-2]); //keeps the larger guess in variable guessx1
	double tolerance = atof(argv[argc-1]); //keeps the tolerance value in variable tolerance
	
	//BISECTION METHOD
	//in order not to change the actual guess values, two more variables are defined, having the guess values initially
	double bisecx0 = guessx0;  
	double bisecx1 = guessx1;
	double midpoint; //midpoint is defined
	int biseciteration = 0; //iteration number of bisection method is defined
	
	while((bisecx1 - bisecx0) > tolerance){ //iterates as long as the difference between two end points is larger than tolerance value
		midpoint = bisecx0 + (bisecx1 - bisecx0) / 2; //midpoint variable becomes the midpoint of two end points at each iteration
		//this if statement narrows down the range of the end points at each iteration
		//by comparing the signs of the values of the polynomial function at each end point and midpoint
		//if the function's value at the midpoint equals to one of the end points, that end point shifts to the previous midpoint
		if(thePol.f(bisecx0) * thePol.f(midpoint) > 0){ 
			bisecx0 = midpoint;
		}
		else{
			bisecx1 = midpoint;
		}
		//until the values satisfy the tolerance value
		biseciteration = biseciteration + 1; //iteration number of bisection method increases by 1 at each iteration
	}
	//midpoint variable now represents a value as close as possible to the root of the function

	cout << midpoint << " " << biseciteration << "\n"; //prints out the solution and the number of iteration
	
	//SECANT METHOD
	//in order not to change the actual guess values, two more variables are defined, having the guess values initially
	double secantx0 = guessx0;
	double secantx1 = guessx1;
	double methodvar; //a variable that will be used in the iteration is defined
	int secantiteration = 0; //iteration number of secant method is defined
	//iterates as long as the absolute value of the difference between two end points is larger than tolerance value
	while(fabs(secantx1 - secantx0) > tolerance){ 
		//the method approximates the function by the secant line through the two iterates
		//takes the zero of the resulting linear function to be the next approximate solution
		//for each previous value
		methodvar = secantx1 - (thePol.f(secantx1) * (secantx1 - secantx0)) / (thePol.f(secantx1) - thePol.f(secantx0));
		secantx0 = secantx1;
		secantx1 = methodvar;
		secantiteration = secantiteration + 1; //iteration number of secant method increases by 1 at each iteration
		//until the values satisfy the tolerance value
	}
	//methodvar variable now represents a value as close as possible to the root of the function

	cout << methodvar << " " << secantiteration << "\n"; //prints out the solution and the number of iteration
	
	//HYBRID METHOD
	//in order not to change the actual guess values, two more variables are defined, having the guess values initially
	double hybridx0 = guessx0;
	double hybridx1 = guessx1;
	double hybridvar; //hybrid variable is defined
	int hybriditeration = 0; //the number of iterations for hybrid method is defined
	for(int i = 0; i < 2; i++){ //applies the bisection method for first two iterations, the same way as full bisection method
		if((hybridx1 - hybridx0) > tolerance){
			hybridvar = hybridx0 + (hybridx1 - hybridx0) / 2; 
			if(thePol.f(hybridx0) * thePol.f(hybridvar) > 0){
				hybridx0 = hybridvar;
			}
			else{
				hybridx1 = hybridvar;
			}
			hybriditeration = hybriditeration + 1; //adds one to hybrid iteration number at each iteration, which is two times
		}
	}
	while(fabs(hybridx1 - hybridx0) > tolerance){ //applies the secant method for the rest of the iterations
		hybridvar = hybridx1 - (thePol.f(hybridx1) * (hybridx1 - hybridx0)) / (thePol.f(hybridx1) - thePol.f(hybridx0));
		hybridx0 = hybridx1;
		hybridx1 = hybridvar;
		hybriditeration = hybriditeration + 1; //adds one to hybrid iteration number at each iteration
	}
	cout << hybridvar << " " << hybriditeration << "\n"; //prints out the solution and the number of iteration
	
	return 0; //terminates
}
