#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef pair<int,int> PII;
typedef double ld;
 
#define pb push_back
#define all(c) c.begin(),c.end()
#define allr(c) c.rbegin(),c.rend()
#define MOD 1000000007
#define PI 3.14159265
 
#define MAX 1500
int isBad[26];
 
class Trie {
public:
    bool last;
    unordered_map <char , Trie*> nChar;
};
 
Trie* give() {
    Trie* Node = new Trie;
    Node -> last = true;
    return Node;
}
 
Trie *troot;
 
void build (Trie *root , string str) {
    int n = str.size();
    Trie *temp = root;
    for (int i = 0; i < n; i++) {
        if (temp -> nChar.find(str[i]) == temp -> nChar.end()) {
            temp -> nChar[str[i]] = give();
        }
        temp = temp -> nChar[str[i]];
    }
    temp -> last = true;
}
 
int search(Trie *root , char c) {
    root -> last = false;
    root = root -> nChar[c];
    troot = root;
    if (root -> last == true) {
        root -> last = false;
        return 1;
    }
    else return 0;
}
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
 
    int t;
    cin >> t;
    while (t--) {
        Trie *root = give();
        root -> last = false;
 
        string str;
        cin >> str;
 
        int n = str.size();
        for (int i = 0; i < n; i++) {
            build(root , str.substr(i , n - i));
        }
 
        int ans = 0;
        for (int i = 0; i < n; i++) {
            troot = root;
            for (int j = i; j < n; j++) {
                ans += (int)search(troot , str[j]);
            }
        }
        cout << ans << endl;
    }
 
 
    return 0;
}
