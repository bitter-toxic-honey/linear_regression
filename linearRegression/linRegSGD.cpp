#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>

#define alpha 0.01
#define EPOCHS 6

void deviations(const std::vector<float>&T,const std::vector<float> X, std::vector<float> &devs){
	float y=T[0];
	float y_act= X[X.size()-1];
	for(int i=0; i<X.size()-1; i++){
		y+=T[i+1]*X[i];
	}
	devs[0]=y-y_act;
	for(int i=1; i<devs.size(); i++){
		devs[i]= (y-y_act)*X[i-1];
	}
}
	
void optimum_para(const std::vector<std::vector<float>>&data,std::vector<float>& T){
	std::vector<float> devs(T.size());;	
	for(const auto& X: data){
		deviations(T,X,devs);
		int i=0;
		for(auto& t: T){
			t = t - alpha*(devs[i++]);
		}
	}
}

float cost(std::vector<float> T, std::vector<std::vector<float>> data){
	float c=0;
	float temp;
	for(const auto &X:data){
		temp=T[0];
		for(int i=0; i<X.size()-1; i++){
			temp += X[i]*T[i+1];
		}
		c+= (temp-X[X.size()-1])*(temp-X[X.size()-1]);
	}
	return c;
}





int main(){

	int n;
	std::string line;
	std::vector<std::vector<float>>data;
	std::vector<float> t;

	std::ifstream file("SGD.txt");

	if(!file){
		std::cerr<<"error while opening file\n";
		return 1;
	}

	std::getline(file,line);
	n=std::stoi(line);

	t.resize(n+1);
	for(int i=0; i<=n; i++) t[i]=0;

	while(std::getline(file,line)){
		std::vector<float>X(n+1);

		std::stringstream str(line);
		for(int i=0; i<=n; i++){
			str>>X[i];
		}
	
		data.push_back(X);
	}

	for(int i=0; i<EPOCHS; i++) optimum_para(data,t);
	
	for(auto x: t) std::cout<<x<<' ';
	std::cout<<'\n';
	std::cout<<cost(t,data)<<'\n';

	return 0;
}


