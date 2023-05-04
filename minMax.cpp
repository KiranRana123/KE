#include <bits/stdc++.h>
using namespace std;

int main()
{
	
	int n;
	cout<<"Enter number of values to be entered : ";
	cin>>n;
	
	vector<float> marks;
	for(int i= 0;i<n;i++)
	{
   		int m;
    	cout<<"Enter marks for student "<<i<<" : ";
        cin>>m;
   		marks.push_back(m);	
	}
    

newMin = cout<<"Enter the lower value for(new range : "))
newMax = cout<<"Enter the upper value for(new range : "))

min = 2000
max = -1

for(i in range(n):
    if(marks[i] > max:
        max = marks[i]
    if(marks[i] < min:
        min = marks[i]

newMarks = []
for(i in range(0,n):
    l = float((marks[i] - min)/(max - min))
    x = float(l*(newMax - newMin))
    newMarks.append(x)

cout<<"Sno ", "\t", "Marks ","\t", "New Marks")

for(i in range(n):
    cout<<i, "\t\t", marks[i], "\t\t\t",newMarks[i])
    cout<<"\n")	

}




