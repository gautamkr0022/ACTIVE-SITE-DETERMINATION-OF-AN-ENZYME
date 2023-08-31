#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;


//conver string to integer
int stringtoint(const string& s) {
    int n = s.size();
    int sum = 0;
    for (int i = 0; i < n; i++) {
        if (!isspace(s[i]))
            sum = sum * 10 + (s[i] - '0');
    }
    return sum;
}



//function that will take input .pdb file and output the desired active residue .pdb file
bool searchKeyword(vector<int>& res, const string& keyword,int size) {
    ifstream inputFile("fileName.pdb");
    ofstream activeSite("activeSite.pdb");
    
      //in case there is some error in input file
    if (!inputFile || !activeSite ) {
        cerr << "Failed to open the file." << endl;
        return false;
    }

  //add a active residue line from input file to new file
    string line;
    while (getline(inputFile, line)) {
        if (line.compare(0, 4, keyword) == 0) {
            int n = stringtoint(line.substr(23, 4));
            if (n > res[size-1])
                return true;

            for(int i=0;i<size;i++){
                if (stringtoint(line.substr(23,4))==res[i]){
                    activeSite<<line<<endl;
                }
            }           
        }
    }

    inputFile.close();
    activeSite.close();
   
    return true;
}

int main() {
    
    //create a vector that contains active residue numbers
    int size;
    cout<<"ENTER THE NUMBER OF ACTIVE RESIDUES"<<endl;
    cin>>size;
    vector<int> res;



    //input file format
    cout<<"please save your input file as filename.pdb"<<endl;



    //taking input of residue numbers
    cout<<"enter your residue number in increasing order"<<endl;
    for(int i=0;i<size;i++){
        int temp;
        cin>>temp;
        res.push_back(temp);
    }



    bool found = searchKeyword(res, "ATOM" , size);
    if (found)
        cout << "Active site files created successfully." << endl;

    return 0;
}
