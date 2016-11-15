#include<iostream>
#include<random>
#include"cube.h"
using namespace std;

int main(int ac, char** v) 
{
	uniform_int_distribution<> di{1,6};
	random_device rd;
	Cube c;
	cout << c;
	//c.spin(atoi(v[1]));
	for(int i=0; i<10; i++)  {
		int n = di(rd);
		c.spin(n);
		cout << "회전 : " << n << endl << c;
	}

	while(!c.any_face()) {
		int n = di(rd);
		c.spin(n);
		cout << "회전 : " << n << endl << c;
	}
}
