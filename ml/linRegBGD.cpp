#include<iostream>
#include<fstream>
#include<sstream>
#include<unordered_map>
#include<vector>

#define alpha 0.06

float cost(float t0, float t1, const std::unordered_map<float,float>&data ){
	float c=0;
	for(const auto&[x,y]:data){
		c+=(t0+ t1*x - y)*(t0+ t1*x - y);
	}
	c*=0.5;
	return c;
}

std::vector<float> grad(const std::unordered_map<float,float>&data, float t0, float t1){
	std::vector<float> vec={0,0};
	for(const auto &[i,j]:data){
		vec[0]+= t0 + (t1*i)-j;
		vec[1]+= i*( t0 + (t1*i)-j);
	}

	return vec;
}

int main(){
	std::string line;
	float x,y;
	float t0=0,t1=0;
	std::vector<float> gradVec;
	std::unordered_map<float,float> data;
	
	std::ifstream file("input.txt");
	if(!file){
		std::cerr<<"error while opening\n";
		return 1;
	}

	while(getline(file,line)){
		std::stringstream str(line);
		str>>x>>y;
		data.insert({x,y});

	}

	for(int i=0; i<200;i++){
		gradVec=grad(data,t0,t1);
		t0=t0- alpha*gradVec[0];
		t1=t1- alpha*gradVec[1];
	}
	std::cout<< t0 <<" " <<t1<<'\n';
	std::cout<< cost(t0,t1,data)<<'\n';
	return 0;

}
