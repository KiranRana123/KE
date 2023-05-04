#include<bits/stdc++.h>
using namespace std;

double calcInfoD(vector<vector<string>> data){
	int yes_count = 0;
	int no_count = 0;
	for(int i =0;i<data.size();i++)
	{
		if(data[i][4] == "Yes")
			yes_count++;
		if(data[i][4] == "No")
			no_count++;	
	}
	
	double p1 = (double)yes_count/(double)data.size();
	double p2 = (double)no_count/(double)data.size();
	double infoD = -1*((double)(p1*(double)(log2(p1))) + (double)((p2)*(double)(log2(p2))));
	return infoD;
}

double calcSplitInfoA(vector<vector<string>> data,int index)
{

	map<string,int> m;
	double SplitinfoA = 0;
	double infoA = 0;
	for(int i = 0 ; i < data.size();i++)
	{
		if(m.find(data[i][index])==m.end())
			m[data[i][index]] =1;
		else
			m[data[i][index]]++;			
	}
	double sinfoA = 0;
	for(auto i:m){
		double sp1 = (double)i.second/data.size();
		double sinfo1 =0 ;
		if(sp1 != 0 && sp1 != 1)
			sinfo1 = -1*(sp1*log2(sp1));
	// cout<<"\n"<<i.first<<": "<<sinfo1	;	
	 sinfoA= (double)(sinfoA+sinfo1);
		
	}
			
	return sinfoA;
	
}


double calcInfoA(vector<vector<string>> data,int index,double infoD,vector<string> &attribute)
{

	map<string,int> m;
	double infoA = 0;
	for(int i = 0 ; i < data.size();i++)
	{
		if(m.find(data[i][index])==m.end())
			m[data[i][index]] =1;
		else
			m[data[i][index]]++;			
	}
	for(auto i:m){
		int y_count = 0;
		int n_count = 0;
		attribute.push_back(i.first);
		for(int j = 0;j<data.size();j++)
		{
			if(i.first == data[j][index] && data[j][4] == "Yes" )
				y_count++;
			if(i.first == data[j][index] && data[j][4] == "No" )
				n_count++;	
		}
		double p1 = (double)y_count/i.second;
		//cout<<i.first<<": "<<y_count<<", "<<n_count;
		double p2 = (double)n_count/i.second;
		double info1 = 0;
		double info2 = 0;
		
		if(p1 != 0 && p1 != 1)
			info1 = -1*(p1*log2(p1));
		if(p2 != 0 && p2 != 1)	
			info2 = -1*(p2*log2(p2));
			
		double info = (double)(i.second*(info1+info2))/(double)data.size();	
		//cout<<"\n info "<<i.first<<" : "<<info;
		infoA = infoA + info;
		
	}
	return (infoD-infoA);
	
}


vector<vector<string> > decisionTree(vector<vector<string>> data,vector<string> features)
{
	double infoD = calcInfoD(data);
	vector<double> gainRatio;
	vector<vector<string>> att;
	for(int i = 0;i<features.size()-1;i++)
	{
		vector<string> attribute;
		double gainA= calcInfoA(data,i,infoD,attribute);
		double splitA =  calcSplitInfoA(data,i);
	
		double rat = (double)gainA/splitA;
		//cout<<"\n\n total : "<<features[i]<< " : "<<gainA<<" , "<<splitA<<" , "<<rat;
		gainRatio.push_back(rat);	
		att.push_back(attribute);
		cout<<"\n Gain Ratio "<<features[i]<<" : "<<gainRatio[i];
		
	}
	vector<vector<string>> tree;
	for(int i =0;i<gainRatio.size();i++)
	{
		double max= -1;
		int ind = -1;
		for(int j = 0; j <gainRatio.size();j++)
		{
				if(max<gainRatio[j])
				{
					max = gainRatio[j];
					ind = j;
				}
				
		}
		vector<string>tmp;
		tmp.push_back(features[ind]);
		for(int k=0;k<att[ind].size();k++)
			tmp.push_back(att[ind][k]);
		tree.push_back(tmp);
		
		gainRatio[ind]=-1;
	}
	
	return tree;
}


int main(){
	
	vector<string> features = {"Weather", "Temperature", "Humidity", "Wind" , "Play?"};
	vector< vector<string>> data = {
		{"Sunny", "Hot", "High", "Weak", "No"},
        {"Cloudy", "Hot", "High", "Weak", "Yes"},
       	{"Sunny", "Mild", "Normal", "Strong", "Yes"},
        {"Cloudy", "Mild", "High", "Strong", "Yes"},
        {"Rainy", "Mild", "High", "Strong", "No"},
        {"Rainy", "Cool", "Normal", "Strong", "No"},
        {"Rainy", "Mild", "High", "Weak", "Yes"},
        {"Sunny", "Hot", "High", "Strong", "No"},
        {"Cloudy", "Hot", "Normal", "Weak", "Yes"},
        {"Rainy", "Mild", "High", "Strong", "No"}
		};

	vector<vector<string> > m = decisionTree(data,features);
	int c= 1;
	for(int i=0;i<m.size();i++)
	{
		cout<<"\n\nFor Level : "<<c;
		cout<<"\nMax attribute: "<<m[i][0];
		cout<<"\n";	
		for(int j=1;j<m[i].size();j++)
			cout<<m[i][j]<<" ' ";
		cout<<"\n";	
		c++;
	}
	
	return 0;
}
