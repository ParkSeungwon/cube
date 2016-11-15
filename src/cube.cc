#include"cube.h"
using namespace std;

ostream& operator<<(ostream& o, const Cube& r) 
{
	for(int j=0; j<3; j++) {
		cout << "   ";
		for(int i=0; i<3; i++) cout << r.face[0][j][i];
		cout << endl;
	}

	for(int k=0; k<3; k++) {
		for(int j=1; j<5; j++) for(int i=0; i<3; i++) cout << r.face[j][k][i];
		cout << endl;
	}

	for(int j=0; j<3; j++) {
		cout << "   ";
		for(int i=0; i<3; i++) cout << r.face[5][j][i];
		cout << endl;
	}
}

Cube::Cube()
{
	for(int i=1; i<7; i++) for(int j=0; j<3; j++) for(int k=0; k<3; k++) 
		face[i-1][j][k] = i;
}

static const int cube_order[6][12][3] = {
	4,0,2, 4,0,1, 4,0,0, 3,0,2, 3,0,1, 3,0,0, 2,0,2, 2,0,1, 2,0,0, 1,0,2, 1,0,1, 1,0,0,
	0,0,0, 0,1,0, 0,2,0, 2,0,0, 2,1,0, 2,2,0, 5,0,0, 5,1,0, 5,2,0, 4,2,2, 4,1,2, 4,0,2,
	0,2,0, 0,2,1, 0,2,2, 3,0,0, 3,1,0, 3,2,0, 5,0,2, 5,0,1, 5,0,0, 1,2,2, 1,1,2, 1,0,2,
	0,2,2, 0,1,2, 0,0,2, 4,0,0, 4,1,0, 4,2,0, 5,2,2, 5,1,2, 5,0,2, 2,2,2, 2,1,2, 2,0,2,
	0,0,2, 0,0,1, 0,0,0, 1,0,0, 1,1,0, 1,2,0, 5,2,0, 5,2,1, 5,2,2, 3,2,2, 3,1,2, 3,0,2,
	2,2,0, 2,2,1, 2,2,2, 4,2,0, 4,2,1, 4,2,2, 5,2,0, 5,2,1, 5,2,2, 1,2,0, 1,2,1, 1,2,2
};

int Cube::spin(int f)
{
	f--;
	int k[12], n = 0;
	for(int i=0; i<3; i++) for(int j=0; j<3; j++) k[n++] = face[f][i][j];
	face[f][0][2] = k[0];
	face[f][1][2] = k[1];
	face[f][2][2] = k[2];
	face[f][0][1] = k[3];
	face[f][2][1] = k[5];
	face[f][0][0] = k[6];
	face[f][1][0] = k[7];
	face[f][2][0] = k[8];

	n = 0;
	const int *p = &cube_order[0][0][0];
	p += 36 * f;
	for(int i=0; i<12; i++) k[i] = face[*p++][*p++][*p++];
	p = &cube_order[0][0][0];
	p += 36 * f;
	for(int i=0; i<12; i++) face[*p++][*p++][*p++] = k[(i+9)%12];
	return 0;
}

bool Cube::is_made() 
{
	for(int i=0; i<6; i++) for(int y=0; y<3; y++) for(int x=0; x<3; x++) 
		if(face[i][y][x] != i+1) return false;
	return true;
}
		
bool Cube::one_face(int f)
{
	f--;
	for(int y=0; y<3; y++) for(int x=0; x<3; x++) 
		if(face[f][y][x] != f+1) return false;
	return true;
}

bool Cube::any_face()
{
	for(int i=1; i<7; i++) if(one_face(i)) return true;
	return false;
}





