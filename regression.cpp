#include<bits/stdc++.h>
using namespace std;

void linearReg(vector<int> x, vector<int> y,int sumx,int sumy,int sumxy,int sumx2,int n)
{
	int num1 = (sumy*sumx2) - (sumx * sumxy);
    int den1 = (n * sumx2) - pow(sumx,2);

    int num2 = (n * sumxy) - (sumx * sumy);
    int den2 = (n * sumx2) - pow(sumx,2);

    float a = (float)num1/(float)den1;
    float b = (float)num2/(float)den2;

    cout<<"Regression line : y = "<<a<<" + "<<b<<"x\n";
   
    vector<float> yval;
    for(int i = 0 ;i < n;i++)
    {
    	float el = a+(b*x[i]);
        yval.push_back(el);
	}
    
    cout<<"\nX \t\t Y \t\t newY\n";
    for(int i = 0 ;i < n;i++)
    	cout<<x[i]<<"\t\t"<<y[i]<<"\t\t"<<yval[i]<<endl;
}

int main()
{
	int n = 10;
	vector<int> x{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> y{1, 3, 2, 5, 7, 8, 8, 9, 10, 12};
    vector<int> xy{};
 
    vector<int> x2;
    for(int i=0;i<n;i++)
    {
    	xy.push_back(x[i]*y[i]);
        x2.push_back(x[i]*x[i]);
	}
    
    int sumx = accumulate(x.begin(),x.end(), 0);
    int sumy =accumulate(y.begin(),y.end(), 0);
    int sumxy = accumulate(xy.begin(),xy.end(), 0);
    int sumx2 = accumulate(x2.begin(),x2.end(), 0);
    linearReg(x, y, sumx, sumy, sumxy, sumx2,n);
    
    return 0;
}


