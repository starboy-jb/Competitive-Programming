/*input
1101011011
10011
*/

#include <iostream>
#include <string.h>

using namespace std;

string _xor(string data, string val)
{
    int n = data.length();
    string ans = "";
    bool flag = 0;
    for(int i = 0; i < n; i ++) {
        if(data[i] == val[i]) {
            if(flag) 
            ans += "0";
        }
        else {
            flag |= 1;
            ans += "1";
        }
    }
    return ans;
}

int main()
{
    string data, divs;
    cin >> data >> divs;
    int m = divs.length();

    int i = m - 2;
    while(i >= 0) {
        data += "0";
        i --;
    }
    int n = data.length();

    string res = "";
    i = 0;
    while(i < n) {
        while(data[i] == '0' and i < n and res.length() < m) {
            res += "0";
            i ++;
        }
        if(res.length() == m) {
            res = _xor(res, divs);
        }
        if(i < n and data[i] == '1') {
            while(res.length() < m) {
                if(i >= n) {
                    res += "0";
                }
                else {
                    res += data[i];
                }
                i ++;
            }
            res = _xor(divs, res);
        }
    }
    cout << res;
    return 0;
}
