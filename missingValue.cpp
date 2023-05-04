#include<bits/stdc++.h>
using namespace std;

void printList(vector<string> yoe,vector<string> sal,int n)
{
    cout<<"Sno. \t\tyoe \t\t sal ";
	cout<<endl;
    for(int i=0; i<n; i++)
        cout<<i+1<<"\t\t"<<setprecision(2)<<yoe[i]<<"\t\t"<<sal[i]<<endl;

}

void ignoreVal(vector<string> yoe,vector<string> sal,int n)
{
	vector<string> newyoe;
    vector<string> newsal;
    int c = 0;
    for(int i=0; i<n; i++)
    {
    	if(sal[i] != "NULL" && yoe[i] != "NULL")
    	{
    		newsal.push_back(sal[i]);
            newyoe.push_back(yoe[i]);
            c = c+1;
		}           
	}
        
    cout<<"Modified data : \n";
    printList(newyoe,newsal,c);
}
    


void manVal(vector<string> yoe,vector<string> sal,int n)
{
    vector<string> newyoe;
    vector<string> newSal;
    string s;
    string y;
    for(int i=0;i<n;i++)
    {
    	if(sal[i] == "NULL" && yoe[i] == "NULL")
        {
			cout<<"\nEnter the year of exp : ";
            cin>>y;
            cout<<"\nEnter the salary: ";
            cin>>s;
            newyoe.push_back(y);
            newSal.push_back(s);
        }
        else if(sal[i] == "NULL" && yoe[i] != "NULL")
        {
        	cout<<"For year of exp : "<<yoe[i];
           	cout<<"\nEnter the salary: ";
           	cin>>s;
            newSal.push_back(s);
            newyoe.push_back(yoe[i]);
		}
        else if(yoe[i] == "NULL" && sal[i] != "NULL")
        {
          	cout<<"For salary : "<<sal[i];
            cout<<"\nEnter the year of exp : ";
            cin>>y;
            newyoe.push_back(y);
            newSal.push_back(sal[i]);
		}
        else
        {
        	newSal.push_back(sal[i]);
            newyoe.push_back(yoe[i]);
		}
            
	}
        
    cout<<"Modified data : \n";
    printList(newyoe,newSal,n);
}

void constVal(vector<string> yoe,vector<string> sal,int n)
{
	vector<string> newSal;
    vector<string> newyoe;
    string s = "10000";
    string y = "2";
    for(int i=0;i<n;i++)
    {
    	if(sal[i] == "NULL" && yoe[i] == "NULL")
        {
        	newyoe.push_back(y);
            newSal.push_back(s);
		}
        else if(sal[i] == "NULL" && yoe[i] != "NULL")
        {
			newSal.push_back(s);
            newyoe.push_back(yoe[i]);
        }
        else if(yoe[i] == "NULL" && sal[i] != "NULL")
        {
        	newyoe.push_back(y);
            newSal.push_back(sal[i]);
		}   
        else
		{
        	newSal.push_back(sal[i]);
            newyoe.push_back(yoe[i]);
		}
            
	}
        
    cout<<"Modified data : \n";
    printList(newyoe, newSal, n);

}
    

void meanData(vector<string> yoe, vector<string> sal, int n)
{
	float s1 = 0;
    float s2 = 0;
    int c1 = 0;
    float c2 = 0;

    for(int i=0;i<n;i++)
    {
    	if(yoe[i] != "NULL")
    	{
    		s1 = s1 + stoi(yoe[i]);
            c1 = c1+1;
		}  
        if(sal[i] != "NULL")
        {
        	s2 = s2 + stoi(sal[i]);
            c2 = c2+1;
		}     
	}
        
    vector<string> newyoe;
    vector<string> newsal;
    float f2 = ceil(s2/c2);
    string m1 = to_string(ceil(s1/c1));
    string m2 = to_string(f2);

    for(int i=0;i<n;i++)
    {
    	if(yoe[i] == "NULL" && sal[i] == "NULL")
        {
        	newyoe.push_back(m1);
            newsal.push_back(m2);
		} 
        else if(yoe[i] == "NULL" && sal[i] != "NULL")
        {
        	newyoe.push_back(m1);
            newsal.push_back(sal[i]);
		}
        else if(sal[i] == "NULL" && yoe[i] != "NULL")
        {
         	newsal.push_back(m2);
            newyoe.push_back(yoe[i]);	
		}  
        else
		{		
            newyoe.push_back(yoe[i]);
            newsal.push_back(sal[i]);
        }
	}
        

    cout<<"Modified data : \n";
    printList(newyoe, newsal, n);

}
    

void groupMean(vector<string> yoe,vector<string> sal,int n)
{
	vector<string> newyoe;
    vector<string> newsal;
    for(int i = 0;i<n;i++)
    {
    	if(yoe[i] == "NULL" && sal[i] == "NULL")
    	{
    		int s1 = 0;
            int s2 = 0;
            int c1 = 0;
            int c2 = 0;

            for(int k=0;k<n;k++)
            {
            	if(yoe[k] != "NULL")
            	{
            		s1 = s1 + stoi(yoe[k]);
                    c1 = c1 + 1;
				}
                if(sal[k] != "NULL")
                {
                	s2 = s2 + stoi(sal[k]);
                    c2 = c2 + 1;
				}
      		}
        	string m1 = to_string(float(s1/c1));
        	string m2 = to_string(float(s2/c2));
        	newyoe.push_back(m1);
        	newsal.push_back(m2);

		}	
    	else if(yoe[i] != "NULL" && sal[i] == "NULL")
    	{
    		float s = 0;
        	float c2 = 0;
        	for(int j=0;j<n;j++)
        	{
        		if(yoe[i] == yoe[j] && sal[j] != "NULL")
            	{
            		s = s + stoi(sal[j]);
                	c2 = c2 + 1;
				}
            	
            }
            newyoe.push_back(yoe[i]);
            newsal.push_back(to_string(s/c2));
		}        
        else
		{
        	newyoe.push_back(yoe[i]);
            newsal.push_back(sal[i]);
		}       
	}
    cout<<"Modified data: \n";
    printList(newyoe,newsal,n);

}
    
int main()
{
	vector<string> yoe{"2","2","4","6","4","2","4","6","2","7","NULL"};
    vector<string> sal{"10000","NULL","12000","25000","14000","8000","14000","26000","9000","30000","NULL"};

    int n = 11;
    printList(yoe,sal,n);
    cout<<"******* MENU *******\n";
    cout<<"1. Ignore the missing value\n";
    cout<<"2. Replace with manually filled value\n";
    cout<<"3. Replace with Const value\n";
    cout<<"4. Replace with Mean value\n";
    cout<<"5. Replace with group Mean \n";
    int ch; 
	cout<<"Enter the choice: ";
	cin>>ch;
	
    if(ch == 1)
        ignoreVal(yoe,sal,n);
    else if(ch == 2)
        manVal(yoe,sal,n);
    else if(ch == 3)
        constVal(yoe, sal, n);
    else if(ch == 4)
        meanData(yoe, sal, n);
    else if(ch == 5)
        groupMean(yoe, sal, n);
    else
    	cout<<"Enter the correct option ";

	return 0;
}

    
