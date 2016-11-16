#include<random>
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
	for(int i=1; i<7; i++) if(one_face(i)) {
		save_point = trail.size();
		return true;
	}
	return false;
}

bool Cube::first_line(int f)
{
	f--;
	if(face[f][0][0] == f+1 && face[f][0][1] == f+1 && face[f][0][2] == f+1)
		return true;
	return false;
}


bool Cube::second_line(int f)
{
	f--;
	if(face[f][1][0] == f+1 && face[f][1][1] == f+1 && face[f][1][2] == f+1)
		return true;
	return false;
}


void Cube::random_spin() 
{
	static uniform_int_distribution<> df(1, 6);
	static uniform_int_distribution<> dd(1, 3);
	static random_device rd;
	int d1, d2;
	d1 = df(rd);
	d2 = dd(rd);
	trail.push(d1);
	direc.push(d2);
	for(int i=0; i<d2; i++) spin(d1);
}

void Cube::ai() {
	bool step = false;
	int face;
	int dice;
	while(!step) {
		random_spin();
		for(int f=1; f<7; f++) if(first_line(f)) {
			save_point = trail.size();
			face = f;
			step = true;
			cout << *this;
		}
	}
	step = false;
	for(int i=0; !step; i++) {
		random_spin();
		if(first_line(face) && second_line(face)) {
			save_point = trail.size();
			step = true;
			cout << *this;
		} else if(i == 100) {
			i = 0;
			while(trail.size() != save_point) {
				int k = trail.top(); trail.pop();
				int c = direc.top(); direc.pop();
				for(int i=0; i<4-c; i++) spin(k);
			}
		}
	}
	step = false;
	for(int i=0; !step; i++) {
		random_spin();
		if(one_face(face)) {
			save_point = trail.size();
			step = true;
			cout << *this;
		} else if(i == 100) {
			i = 0;
			while(trail.size() != save_point) {
				int k = trail.top(); trail.pop();
				int c = direc.top(); direc.pop();
				for(int i=0; i<4-c; i++) spin(k);
			}
		}
	}
}
