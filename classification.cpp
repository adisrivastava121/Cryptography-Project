#include<bits/stdc++.h>
using namespace std;

vector<string> numbers(int n, int len)
{
    vector<string> ans;
    for(int i=0; i<pow(2,len); i++)
    {
        string s = bitset<32> (i).to_string();
        string str = s.substr(32-len, len);
        ans.push_back(str);
    }
    return ans;
}

void Erase(string &str, int len)
{
    while(len>0)
    {
        str.pop_back();
        len--;
    }
    return;
}

void general(int n, int k, vector<vector<string>> &mat, vector<string> &perms, vector<string> &I, int rno)
{
    if(rno==k)
    {
        mat.push_back(I);
        return;
    }
    
    for(int j=0; j<perms.size(); j++)
    {
        I[rno].append(perms[j]);
        general(n,k,mat,perms,I,rno+1);
        Erase(I[rno],n-k);
    }
}

vector<vector<string>> solve(int n, int k)
{
    vector<string> I;
    
    for(int i=0; i<k; i++)
    {
        string s(k,'0');
        s[i]='1';
        I.push_back(s);
    }
    
    vector<string> perms = numbers(n,n-k);
    
    vector<vector<string>> mat;
    
    general(n,k,mat,perms,I,0);
    
    return mat;
}

void print(vector<string> &mat)
{
    for(int i=0; i<mat.size(); i++)
    {
        cout << mat[i] << "\n";
    }
}

bool checkSingleDeletion(vector<string> &s, int n)
{
    unordered_map<string,int> stringmap;
    vector<set<string>> Dset(n);
    
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

int countDiff(string &a, string &b)
{
    int count=0;
    for(int i=0; i<a.length(); i++)
    {
        if(a[i]!=b[i])
            count++;
    }
    return count;
}

int minHammingDistance(vector<string> &codewords)
{
    int dist=INT_MAX;
    
    for(int i=0; i<codewords.size(); i++)
    {
        for(int j=i+1; j<codewords.size(); j++)
        {
            dist = min(dist,countDiff(codewords[i], codewords[j]));
        }
    }
    
    return dist;
}

vector<vector<string>> findCodeWords(int n, int k, vector<vector<string>> &matrix)
{   
    vector<vector<string>> codeWords;
    
    for(int i=0;i<matrix.size();i++)
    {
        vector<string> basis=matrix[i];
        vector<string> res;
        unordered_set<string> uset;
        
        string zeros(n,'0');
        uset.insert(zeros);
        res.push_back(zeros);
        
        for(int l=0; l<basis.size(); l++)
        {
            if(uset.find(basis[l])==uset.end())
            {
                res.push_back(basis[l]);
                uset.insert(basis[l]);
            }
            
            string codei=basis[l];
            
            for(int m=l+1;m<basis.size();m++)
            {
                string codej=basis[m];
                string code;
                for(int x=0; x<n; x++)
                {
                    char ch = '0'+(codei[x]-'0'+codej[x]-'0')%2;
                    code.push_back(ch);
                }
                
                if(uset.find(code)==uset.end())
                {
                    res.push_back(code);
                    uset.insert(code);
                }
            }
        }
        
        codeWords.push_back(res);
    }
    
    return codeWords;
}
int main()
{
    int n;
    cin >> n;

        for(int k=1; k<n; k++)
        {   
            vector<vector<string>> matrix = solve(n,k);
            vector<vector<string>> codeWords = findCodeWords(n,k,matrix);
            
            for(int i=0; i<codeWords.size(); i++)
            {
                int minh = minHammingDistance(codeWords[i]);
                cout << "Code " << " ";
                cout << "n: " << n << " k: " << k << " d: " << minh << " ";
                
                if(checkSingleDeletion(codeWords[i],n)==true)
                    cout << "YES\n";
                else
                    cout << "NO\n";

                cout << "Matrix " << "\n";
                print(matrix[i]);
                cout << "CodeWords " << "\n";
                print(codeWords[i]);
            }
        
        }
    return 0;
}