#include<iostream>
#include"cube.h"
using namespace std;

ostream& operator<<(ostream& o, const int r[6][3][3]) 
{
	for(int j=0; j<3; j++) {
		cout << "   ";
		for(int i=0; i<3; i++) cout << r[0][j][i];
		cout << endl;
	}

	for(int k=0; k<3; k++) {
		 for(int j=1; j<5; j++) for(int i=0; i<3; i++) cout << r[j][k][i];
		cout << endl;
	}

	for(int j=0; j<3; j++) {
		cout << "   ";
		for(int i=0; i<3; i++) cout << r[5][j][i];
		cout << endl;
	}
}
int face[6][3][3];

int main() 
{
	for(int i=1; i<7; i++) for(int j=0; j<3; j++) for(int k=0; k<3; k++) 
		face[i-1][j][k] = i;
	cout << face;
}
