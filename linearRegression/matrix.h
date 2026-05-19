#include<cmath>
#include<vector>

struct Matrix{
	int r;
	int c;
	vector<<vector<float>> M;

	Matrix(int r, int c): r{r}, c{c} {
		M.resize(r,vector<float>(c));
	}

	Matrix& operator+(const Matrix& other){

