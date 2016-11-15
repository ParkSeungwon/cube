#include<iostream>

class Cube {
public:
	Cube();
	int face[6][3][3];
};

std::ostream& operator<<(std::ostream& o, const Cube& r);
	
