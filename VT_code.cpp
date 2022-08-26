// VT Code Single Deletion Checker

#include <bits/stdc++.h>
using namespace std;

//  Constraints:  n -> []
//                l -> []
//                q -> []
//                a -> []

//  Generate n length strings such that VT equation is satisfied.
//  vector<string> s holds all the valid strings that satisfies VT equation.
void generateAllKLengthRec(vector<char> &ch, string prefix, int q, int n,vector<string> &s,int num,int l,int a,int N)
{
    if (n == 0)
    {
        if(num%(N+1)==a)
        {
            //cout<<num<<" "<<N+1<<" "<<prefix<<endl;
            s.push_back(prefix);
        }
        return;
    }
 
    for (int i = 0; i < q; i++)
    {
        string newPrefix;
        newPrefix = prefix + ch[i];
        int tmp=pow((prefix.length()+1),l)*(ch[i]-'0');
        generateAllKLengthRec(ch, newPrefix, q, n - 1,s,num+tmp,l,a,N);
    }
 
}

void generateAllKLength(vector<char> &ch, int n,int q,vector<string> &s,int num,int l,int a,int N)
{
    generateAllKLengthRec(ch, "", q, n,s,num,l,a,N);
}

// Generate field for q <- {1,2,3,5};

void generateFeildElements(int q,vector<char> &ch)
{
    // q value should be less than 5 and greater than 1;
    
    if(q>5||q<=1)
        return;
    
    ch.push_back('0');
    ch.push_back('1');
    if(q==3)
        ch.push_back('2');
    else if(q==4)
        ch.push_back('a'),ch.push_back('b');  // b=a^2
    else
    {
        ch.push_back('2');
        ch.push_back('3');
        ch.push_back('4');
    }
}

// Funtions that check the intersection of pair of Dset generated after deleting single character from s.
bool checkSingleDeletion(vector<set<string>> &Dset, vector<string> &s, int n)
{
    unordered_map<string,int> stringmap;
    
    for(int i=0; i<s.size(); i++)
    {
        for(int j=0; j<n; j++)
        {
            string temp = s[i];
            temp.erase(j,1);
            Dset[i].insert(temp);
            
            // Comment from here till line 84 to print Dset.
            if(stringmap.find(temp)==stringmap.end())
                stringmap[temp]=i;
            else
            {
                if(stringmap[temp]!=i)
                    return false;
            }
            // Comment till here.
        }
    }
    return true;
    
        // Uncomment to print Dset
    
//     for(int i=0; i<s.size(); i++)
//     {
//         cout << "For " << s[i] << ": ";
//         for(auto itr=Dset[i].begin(); itr!=Dset[i].end(); itr++)
//         {
//             cout << *itr << " ";
//         }
//         cout << "\n";
//     }
    
    
//     return true;
}

int main()
{
        int n,q,l,a;
    
        cin>>n>>q>>l>>a;
        vector<char> ch;
    
        generateFeildElements(q,ch);
    
        if(q>5)
            cout<<"Entered feild is not valid.";
        else
        {
            vector<string> s;
            
            generateAllKLength(ch, n, q,s,0,l,a,n);
            
//          Print all the possible strings
//            
//                 for(int i=0;i<s.size();i++)
//                      cout<<s[i]<<endl;
            
            int num_of_strings = s.size();
            vector<set<string>> Dset(num_of_strings);
            
            if(checkSingleDeletion(Dset,s,n))
                cout << ":) Can handle single deletion\n";
            else
                cout << ":( Cannot handle single deletion\n";
            

            
            // Print the size of possible generated strings
            //cout<<s.size()<<endl;
        }
}