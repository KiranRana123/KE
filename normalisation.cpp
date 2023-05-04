#include<bits/stdc++.h>
using namespace std;

void printArr(vector<float> marks,int n)
{
	cout<<"Sno \t\t Marks \n";
    for(int i = 0 ; i<n; i++)
        cout<<i<<"\t\t"<<marks[i]<<"\n";
}
  
void printArray(vector<float> marks,int n,vector<float> newMarks)
{
	cout<<"Sno \t\tMarks \t\t New Marks\n";
    for(int i = 0 ; i<n ;i++)
        cout<<i<<"\t\t"<<marks[i]<<"\t\t "<<setprecision(2)<<newMarks[i]<<"\n";

}

void decimalScaling(vector<float> marks,int n)
{

	int maxMarks = -1;
    for(int i = 0 ; i<n ;i++)
	{
        if(marks[i] > maxMarks)
            maxMarks = marks[i];
	}
    int p = 0;
    while(maxMarks > 0)
	{
		maxMarks = maxMarks/10;
        p = p + 1;
	}
  
    float div = pow(10,p);
    vector<float> newMarks;
    
    for(int i =0;i<n;i++)
	{
		float cg = marks[i]/div;
        newMarks.push_back(cg);
	}

    cout<<"\nSno \t\tMarks \t\t New Marks\n";
    for(int i = 0 ; i<n ;i++)
        cout<<i<<"\t\t"<<marks[i]<<"\t\t "<<newMarks[i]<<"\n";
}
void zScore(vector<float> marks,int n)
{
    int sumMarks = 0;
    for(int i = 0 ; i<n ;i++)
		 sumMarks = sumMarks + marks[i];

    float meanMarks = sumMarks / n;

    double s = 0;
    for(int i = 0 ; i<n ;i++)
	  s = s + pow((meanMarks - marks[i]), 2);

    s = s / n;
    double sd = sqrt(s);
    vector<float> newMarks;

    for(int i = 0 ; i<n ;i++)
	{
	 	float z = abs(marks[i] - meanMarks) / sd;
        newMarks.push_back(z);
 	
	 }
    printArray(marks,n, newMarks);
}

void minMax(vector<float> marks,int n)
{
    float newMin;
	cout<<"\nEnter the lower value for new range : ";
	cin>>newMin;
	
    float newMax;
	cout<<"\nEnter the upper value for new range : ";
	cin>>newMax;

    float min = 2000;
    float max = -1;

    for(int i = 0 ; i<n ;i++)
	{
    	if(marks[i] > max)
            max = marks[i];
        if(marks[i] < min)
            min = marks[i];
	}
       

    vector<float> newMarks{};
    for(int i = 0 ; i<n ;i++)
	{
        float l = (marks[i] - min) / (max - min);
        float x = l * (newMax - newMin);
        newMarks.push_back(x);
	}
    printArray(marks,n,newMarks);
}
int main()
{

    int n = 10;
    vector<float> marks{78,56,23,32,89,98,64,85,96,99};

    printArr(marks,n);

    cout<<"\n******* MENU *******\n";
    cout<<"1. Decimal Scaling\n";
    cout<<"2. Z-Score\n";
    cout<<"3. Min-Max \n";
    int ch;
	cout<<"Enter the choice: ";
	cin>>ch;
    if(ch == 1)
       decimalScaling(marks,n);
    else if(ch == 2)
        zScore(marks,n);
    else if(ch == 3)
        minMax(marks,n);
    else
    	cout<<"Enter correct option ";
}

