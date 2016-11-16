#include<iostream>
#include<stack>
class Cube {
public:
	Cube();
	int face[6][3][3];
	int spin(int face);
	bool is_made();
	bool one_face(int f);
	bool any_face();
	void ai();

protected:
	bool first_line(int f);
	bool second_line(int f);
	
private:
	std::stack<int> trail;
	std::stack<int> direc;
	int save_point;
	void random_spin();
};

std::ostream& operator<<(std::ostream& o, const Cube& r);
	
