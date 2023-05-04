#include<bits/stdc++.h>
using namespace std;



float manDist(int x1,int x2,int y1,int y2)
{
	float dist;
	dist= abs(x2-x1)+abs(y2-y1);
	return dist;
}

int main()
{
	//vector<vector<float>> data = {{3,5},{1,4},{1,5},{2,6},{1,5},{6,8},{6,6},{6,7},{5,6},{6,7},{7,1},{8,2},{9,1},{8,2},{9,3},{9,2},{8,3}};
	vector<vector<float>> data = {{2,6},{3,4},{3,8},{4,7},{6,2},{6,4},{7,3},{7,4},{8,5},{7,6}};

	//vector<float> c1 = data[3];
	//vector<float> c2 = data[5];
	//vector<float> c3 = data[9];
	vector<float> c1 = data[1];
	vector<float> c2 = data[7];
	vector<float> newc1(2,0);
	vector<float> newc2(2,0);
//	vector<float> newc3(2,0);
	int x = 0;
	vector<vector<float>> clus1;
	vector<vector<float>> clus2;
	vector<vector<float>> clus3;
	
	float prevd =100000;
	float newd = 0;
	
	
	srand(time(0));
	while(newd < prevd)
	{
		
		if(x!=0){
			prevd = newd;
			c1= newc1;
			c2 = newc2;
			//c3=newc3;
			clus1.clear();
			clus2.clear();
			//clus3.clear();
		}
		 
		float dis = 0;
		for(int i = 0;i<data.size();i++)
		{
			float dist1 = manDist(c1[0],data[i][0],c1[1],data[i][1]);
			float dist2 = manDist(c2[0],data[i][0],c2[1],data[i][1]);
		/*	float dist3 = manDist(c3[0],data[i][0],c3[1],data[i][1]);
				
			if(dist1<=dist2 && dist1<dist3)
			{
				clus1.push_back(data[i]);
				dis= dis +dist1;
			}
			
			if(dist2<dist1 && dist2<=dist3)
			{
				clus2.push_back(data[i]);
				dis = dis +dist2;
			}
	     	if(dist3<=dist1 && dist3<dist2)
			{
				clus3.push_back(data[i]);
				dis = dis+dist3;
			}	
		}*/
		if(dist1<=dist2)
			{
				clus1.push_back(data[i]);
				dis= dis +dist1;
			}
		else{
			clus2.push_back(data[i]);
				dis = dis +dist2;
			}
		}
		newd = dis;
		
		newc1 =  data[rand()%10];
		newc2 =  data[rand()%10];
	//	newc3 =  data[rand()%16];
		x++;
		
	
}
	cout<<"Final clusters are: ";
	cout<<"\nCluster1: {";
	for(auto i : clus1)
	{
		cout<<"{"<<i[0]<<","<<i[1]<<"} , ";
	}
	cout<<"}";
	
	cout<<"\nCluster2: {";
	for(auto i : clus2)
	{
		cout<<"{"<<i[0]<<","<<i[1]<<"} , ";
	}
	cout<<"}";
	/*
	cout<<"\nCluster3: {";
	for(auto i : clus3)
	{
		cout<<"{"<<i[0]<<","<<i[1]<<"} , ";
	}
	cout<<"}";
	*/
	
}
