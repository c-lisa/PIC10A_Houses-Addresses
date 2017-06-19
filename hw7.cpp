/***************
Lisa Chiang
304-255-524
HW#7 11/14/2016
Houses Graphics
***************/

#include"ccc_win.h"
#include <time.h>
using namespace std;

class House {
public:
	House(); //default constructor
	House(int new_house, Point new_location); //constructor
	void draw_house() const; 
	Point get_location(); //return location
	int get_num() const; //return house number
private:
	int house_number; //house number
	Point location; //location of house as a POINT
};

//returning location of house - POINT (x,y)
Point House::get_location()
{
	return location; 
}
//returning number of address - INT #
int House::get_num() const
{
	return house_number;
}
//default constructor
House::House()
{
	house_number = 1;
	location = Point(0, 0);
}
//constructor for House (house number, location)
House::House(int new_house_number, Point new_location)
{
	house_number = new_house_number;
	location = new_location;
}
//drawing the actual house
void House::draw_house() const //o = location 
{
	double x, y;
	x = location.get_x();
	y = location.get_y();
	double r; //ratio of increase or decrease
	r = 2;

	//drawing window
	Point w1(x - 1 * r, y), w2(x + 1 * r, y), w3(x - 1 * r, y - 2 * r), w4(x + 1 * r, y - 2 * r),
		w5(x, y), w6(x, y - 2 * r), w7(x - 1 * r, y - 1 * r), w8(x + 1 * r, y - 1 * r);
	Line wi1(w1, w2), wi2(w1, w3), wi3(w2, w4), wi4(w3, w4), wi5(w5, w6), wi6(w7, w8);
	cwin << wi1 << wi2 << wi3 << wi4 << wi5 << wi6;

	//drawing ground
	Point g1(x - 5 * r, y - 3 * r), g2(x + 5 * r, y - 3 * r);
	Line gr1(g1, g2);
	cwin << gr1;

	//drawing house outline
	Point h1(x - 4 * r, y + 1 * r), h2(x + 2 * r, y + 1 * r), h3(x - 4 * r, y - 3 * r), h4(x + 2 * r, y - 3 * r);
	Line ho1(h1, h2), ho2(h2, h4), ho3(h3, h4), ho4(h3, h1);
	cwin << ho1 << ho2 << ho3 << ho4;

	//drawing roof
	Point r1(x - 3 * r, y + 3 * r), r2(x + 1 * r, y + 3 * r);
	Line ro1(r1, r2), ro2(h1, r1), ro3(r2, h2);
	cwin << ro1 << ro2 << ro3;

	//drawing door
	Point d1(x - 3 * r, y - 1 * r), d2(x - 2 * r, y - 1 * r), d3(x - 3 * r, y - 3 * r), d4(x - 2 * r, y - 3 * r);
	Line do1(d1, d2), do2(d2, d4), do3(d1, d3);
	cwin << do1 << do2 << do3;

	//drawing doorknob
	Point dk1(x - 2.25*r, y - 2 * r);
	Circle dk(dk1, 0.1*r);
	cwin << dk;

	//drawing the chimney
	Point c1(x, y + 4 * r), c2(x, y + 3 * r), c3(x + 1 * r, y + 4 * r);
	Line ch1(c1, c2), ch2(c1, c3), ch3(c3, r2);
	cwin << ch1 << ch2 << ch3;

	//drawing the tree
	Point t1(x + 3.5*r, y), t2(x + 3 * r, y - 1 * r), t3(x + 4 * r, y - 1 * r), t4(x + 3 * r, y - 3 * r), t5(x + 4 * r, y - 3 * r);
	Circle tree(t1, 1 * r);
	Line tr1(t2, t4), tr2(t3, t5);
	cwin << tree << tr1 << tr2;

	//writing house number
	Point M(x - 1.3*r, y + 2 * r);
	Message number(M, house_number);
	cwin << number;
}
//calculating the house number - return a NUMBER
int calc_house_num(House first, House last, int num_houses, int index)
{
	int house_num = first.get_num();
	house_num += double(index*(last.get_num() - first.get_num())) / (num_houses - 1); 
	return house_num; 
}

//calculating the house location - return a HOUSE (aka POINT)
Point calc_house_location(House first, House last, int num_houses, int index)
{
	Point first_location = first.get_location(); 
	Point last_location = last.get_location(); 

	double current_x = first_location.get_x(); 
	double current_y = first_location.get_y(); 
	double last_x = last_location.get_x(); 
	double last_y = last_location.get_y(); 

	current_x += index*(last_x - current_x) / (num_houses - 1); 
	current_y += index*(last_y - current_y)/ (num_houses -1); 

	Point current_location(current_x, current_y); 
	return current_location; 

}

class Street {
public:
	Street(House new_first, House new_last, int num_houses);
	void plot();
private:
	House first;
	House last;
	int num_houses;
};
//constructor
Street::Street(House new_first, House new_last, int new_num_houses)
{
	first = new_first;
	last = new_last;
	num_houses = new_num_houses;
}
//plotting the street w/ houses
void Street::plot()
{
	for (int i = 0; i < num_houses; i++)
	{
		Point current_location = calc_house_location(first, last, num_houses, i); 
		int current_num = calc_house_num(first, last, num_houses, i); 
		
		House current_house(current_num, current_location); 
		current_house.draw_house(); 
	}
}

int ccc_win_main()
{
	//playing field
	cwin.coord(-50, 50, 50, -50);

	srand((int)time(0));

	//getting two points
	Point location_1 = cwin.get_mouse("Click somewhere as your starting location.");
	Point location_2 = cwin.get_mouse("Click again for your ending location."); 

	//asking for first and last hosue address number
	int first_num = cwin.get_int("Please enter the first house number.");
	int second_num = cwin.get_int("Please enter the last house number."); 

	//establishign first and last house 
	House first (first_num, location_1);
	House last (second_num, location_2);

	int num_houses = cwin.get_int("How many houses are on this street?"); 

	//plotting street
	Street one (first, last, num_houses); 
	one.plot(); 

	return 0;
}