#include <bits/stdc++.h>
using namespace std;


void printArray(vector<float> marks,int n,vector<float> newMarks)
{
	cout<<"\nSno \t\tMarks \t\tNew Marks \n";
    for(int i=0; i<n ; i++)
    {
        cout<<i+1<<"\t\t"<<marks[i]<<"\t\t"<<newMarks[i]<<"\n";
	}
}    


void printArr(vector<float> marks,int n)
{
    cout<<"\nSno \t\t Marks \n";
    for(int i=0;i<n;i++)
        cout<<i+1<<"\t\t"<<marks[i]<<"\n";
}   


void boundaryBin(vector<float> marks, int n,int binSize)
{
    vector<float> newMarks{};
    
    for(int i=0; i<n-3; i=i+binSize)
    {
        int min = i;
        int max = i + 3;

        for(int j=0;j<binSize;j++) 
          {
             if((j+i - min) <= (max - j-i))
                newMarks.push_back(marks[min]);
            else
                newMarks.push_back(marks[max]);
          } 
    }
    printArray(marks, n, newMarks);

    
}   

void meanBin(vector<float> marks,int n,int binSize)
{
    vector<float> newMarks;
    vector<float> binMean;

    for(int i=0; i<n-2;i=i+binSize)
    {
        float s=0;
        for(int j = 0; j<binSize; j++)
            s = s + marks[j+i];
            
        float m = s/float(binSize);
        binMean.push_back(m);
    }
    int k = 0;
    for(int i = 0; i<n-2; i= i+binSize)
    {
        for(int j = 0; j<binSize; j++)
            newMarks.push_back(binMean[k]);
        k = k+1;
    }    
    printArray(marks,n,newMarks);
}   

int main()
{
	int n = 12;
    int binSize = 3;
    vector<float> marks{78, 56, 23, 32, 89, 98, 64, 85, 96, 56, 67, 99};
    sort(marks.begin(), marks.end());
    cout<<endl;
    printArr(marks,n);
   
    cout<<"\n******* MENU *******\n";
    cout<<"\n1. Replace elements with bin mean\n";
    cout<<"\n2. Replace elements with boundary values\n";
    cout<<"\nEnter the choice: ";
    int ch;
    cin>>ch;
    if(ch == 1)
        meanBin(marks, n,binSize);
    else if(ch == 2)
        boundaryBin(marks, n,binSize);
    else
        cout<<"\nEnter either 1 or 2";

    return 0;
}
   

