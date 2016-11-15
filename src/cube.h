#include<iostream>

class Cube {
public:
	Cube();
	int face[6][3][3];
	int spin(int face);
	bool is_made();
	bool one_face(int f);
	bool any_face();
	
private:
};

std::ostream& operator<<(std::ostream& o, const Cube& r);
	
