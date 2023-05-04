#include<bits/stdc++.h>
using namespace std;

float dist(int x1,int x2,int y1,int y2)
{
	float d = sqrt(pow((x2-x1),2) + pow((y2-y1),2));
    return d;
}

void printClus(vector<vector<float>> vec)
{
    for (int i = 0; i < vec.size(); i++) {
            cout <<"("<<vec[i][0]<<","<<vec[i][1]<<")\t";
       
    }
}
vector<float> meanCalc(vector<vector<float>> clus)
{
    int l = clus.size();
    float xsum = 0;
    float ysum = 0;

    for(int i =0;i<l;i++)
	{
	
        xsum = xsum + clus[i][0];
        ysum = ysum + clus[i][1];
	}
    return {xsum/l,ysum/l};
}

int main()
{

    int k = 3;
    vector<vector<float>> points {{3,5},{1,4},{1,5},{2,6},{1,5},{6,8},{6,6},{6,7},{5,6},{6,7},{7,1},{8,2},{9,1},{8,2},{9,3},{9,2},{8,3}};
    
    vector<float> prevc1 = points[3];
    vector<float> prevc2 = points[5];
    vector<float> prevc3 = points[9];

	vector<float> newc1(2,0);
    vector<float> newc2(2,0);
    vector<float> newc3(2,0);

    int n = points.size();
    
    vector<vector<float>> clus1;
    vector<vector<float>> clus2;
    vector<vector<float>> clus3;

    int x = 0;

    while(prevc1[0] != newc1[0] && prevc1[1] != newc1[1] && prevc2[0] != newc2[0] && prevc2[1] != newc2[1] && prevc3[0] != newc3[0] && prevc3[1] != newc3[1])
	{
	
        if(x != 0)
        {
			prevc1 = newc1;
            prevc2 = newc2;
            prevc3 = newc3;
            
            clus1.clear();
        	clus2.clear();
        	clus3.clear();
    	}
    	
        
        for(int i=0;i<n;i++)
        {
        	
		    float d1 = dist(points[i][0], prevc1[0], points[i][1], prevc1[1]);
            float d2 = dist(points[i][0], prevc2[0], points[i][1], prevc2[1]);
            float d3 = dist(points[i][0], prevc3[0], points[i][1], prevc3[1]);

            if (d1 < d2 && d1 <= d3)
                clus1.push_back(points[i]);
            if (d2 <= d1 && d2 < d3)
                clus2.push_back(points[i]);
            if (d3 < d1 && d3 <= d2)
                clus3.push_back(points[i]);
		}
				
        newc1 = meanCalc(clus1);
        newc2 = meanCalc(clus2);
        newc3 = meanCalc(clus3);
        
        x++;
      
	}
	   cout<<"Final clusters are  : ";
       cout<<"\n\n Cluster 1: \n";
	   printClus(clus1);
       cout<<"\n\n Cluster 2: \n";
	   printClus(clus2);
       cout<<"\n\n Cluster 3: \n";
	   printClus(clus3);
}

