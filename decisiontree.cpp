#include<bits/stdc++.h>
using namespace std;

double calcEntropy(vector<vector<string>> data){
    int n = data.size(), m = data[0].size();
    int yes = 0, no = 0;
    for(int i=0; i<n; i++){
        if(data[i][m-1] == "Yes") yes++;
        else no++;
    }
    double p = (double)yes/(yes+no);
    double q = (double)no/(yes+no);
    if(p == 0 || q == 0) return 0;
    double entropy = -1*p*log2(p) - q*log2(q);
    return entropy;
}

double calcFeatureEntropy(vector<vector<string>> data, int col){
    int n = data.size(), m = data[0].size();
    unordered_map<string, int> mp;
    vector<string> temp;
    for(int i=0; i<n; i++){
        mp[data[i][col]]++;
    }
    double featureEntropy = 0;
    for(auto it=mp.begin(); it!=mp.end(); it++){
        int yes = 0, no = 0;
        for(int i=0; i<n; i++){
            if(data[i][col] == it->first){
                if(data[i][m-1] == "Yes") yes++;
                else no++;
            }
        }
        double p = (double)yes/(yes+no);
        double q = (double)no/(yes+no);
        if(p == 0 || q == 0) continue;
        double entropy = -1*p*log2(p) - q*log2(q);
        cout<<"\n"<<it->first<<": "<<(double)(it->second)*entropy/n;
        featureEntropy += (double)(it->second)*entropy/n;
    }
    return featureEntropy;
}

/*
void displayTree(vector<vector<string>> data, vector<string> features){
    int n = data.size(), m = data[0].size();
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cout << data[i][j] << "\t";
        }
        cout << endl;
    }
}
*/
void displayData(vector<string> head, vector<vector<string>> data){
    cout<< "**************************************************************" << endl;
    for(int i=0; i<head.size(); i++){
        cout << head[i] << "\t";
        if(head[i].size() < 8) cout << "\t";
    }
    cout << endl<< endl;
    for(int i=0; i<data.size(); i++){
        for(int j=0; j<data[i].size(); j++){
            cout << data[i][j] << "\t";
            if(data[i][j].size() < 8) cout << "\t";
        }
        cout << endl;
    }
    cout << "*************************************************************" << endl;
}


void decisionTree(vector<vector<string>> data, vector<string> features,vector<string>& paths,string s){
    int n = data.size(), m = data[0].size();
    double entropy = calcEntropy(data);
    if(entropy == 0){
        paths.push_back(s+data[0][m-1]);
        cout<< "Decision: " << data[0][m-1] << endl;
        cout<< endl <<endl;
        return;
    }
    cout<< "Entropy: " << entropy << endl;
    double maxGain = INT_MIN;
    int maxGainCol = -1;
    for(int i=0; i<m-1; i++){
        double featureEntropy = calcFeatureEntropy(data, i);
        double gain = entropy - featureEntropy;
        cout<< "Gain for " << features[i] << ": " << gain << endl;
        if(gain > maxGain){
            maxGain = gain;
            maxGainCol = i;
        }
    }
    cout<< "Max Gain: " << maxGain << endl;
    cout<< "Max Gain Column: " << features[maxGainCol] << endl;
    s+=features[maxGainCol]+"--";
    unordered_map<string, int> mp;
    vector<string> temp;
    for(int i=0; i<n; i++){
        if(mp.find(data[i][maxGainCol]) == mp.end()){
            mp[data[i][maxGainCol]] = 1;
            temp.push_back(data[i][maxGainCol]);
        }
    }
    vector<vector<vector<string>>> newData;
    for(int i=0; i<temp.size(); i++){
        vector<vector<string>> tempData;
        for(int j=0; j<n; j++){
            if(data[j][maxGainCol] == temp[i]){
                vector<string> tempRow;
                for(int k=0; k<m; k++){
                    if(k != maxGainCol) tempRow.push_back(data[j][k]);
                }
                tempData.push_back(tempRow);
            }
        }
        newData.push_back(tempData);
    }
    
    cout << "\n*************************************************************" << endl;
    for( int i=0; i<newData.size(); i++){
        string t=s;
        t+=temp[i]+"-->";
        cout << "For " << features[maxGainCol] << " = " << temp[i] << endl;
        if(calcEntropy(newData[i]) == 0){
            paths.push_back(t+newData[i][0][newData[i][0].size()-1]);
            cout << "Decision: " << newData[i][0][newData[i][0].size()-1] << endl;
        }
        else{
            vector<string> newfeatures;
            for(int j=0; j<features.size(); j++){
                if(j != maxGainCol) newfeatures.push_back(features[j]);
            }
            displayData(newfeatures, newData[i]);
            decisionTree(newData[i], newfeatures, paths, t);
        }
    }
    cout<<"*************************************************************\n\n";

}

int main()
{

    vector<string> features = {"Weather", "Temperature", "Humidity", "Wind" , "Play?"};
    vector<vector<string>> data ={
        {"Sunny", "Hot", "High", "Weak", "No"},
        {"Cloudy", "Hot", "High", "Weak", "Yes"},
       	{"Sunny", "Mild", "Normal", "Strong", "Yes"},
        {"Cloudy", "Mild", "High", "Strong", "Yes"},
        {"Rainy", "Mild", "High", "Strong", "No"},
        {"Rainy", "Cool", "Normal", "Strong", "No"},
        {"Rainy", "Mild", "High", "Weak", "Yes"},
        {"Sunny", "Hot", "High", "Strong", "No"},
        {"Cloudy", "Hot", "Normal", "Weak", "Yes"},
        {"Rainy", "Mild", "High", "Strong", "No"},
    };
    /*
    vector<string> features = {"age","income","student","credit rating","buys computer"};
    vector<vector<string>> data ={ 
	{"<=30","high","no","fair","no"},
    {"<=30","high","no","excellent","no"},
    {"31-40","high","no","fair","yes"},
    {">40","medium","no","fair","yes"},
    {">40","low","yes","fair","yes"},
    {">40","low","yes","excellent","no"},
    {"31-40","low","yes","excellent","yes"},
    {"<=30","medium","no","fair","no"},
    {"<=30","low","yes","fair","yes"},
    {">40","medium","yes","fair","yes"},
    {"<=30","medium","yes","excellent","yes"},
    {"31-40","medium","no","excellent","yes"},
    {"31-40","high","yes","fair","yes"},
    {">40","medium","no","excellent","no"}
};	*/
    cout<< "\n*********** Decision Tree Classification Method ***********" << endl;
    displayData(features, data);
    vector<string> paths;
    decisionTree(data, features ,paths , "");

    cout<< "The Paths of the decision tree are: " << endl;
    for(int i=0; i<paths.size(); i++){
        cout<< paths[i] << endl;
    }
    return 0;
}

