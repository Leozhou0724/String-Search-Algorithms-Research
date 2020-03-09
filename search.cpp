#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#define CLOCKS_PER_SEC 1000
using namespace std;
void naive(string data, string find);
void KMP(string data, string find);
void LPS(string find, int lps[], int m);
void boyer_moore(string data, string find);
void BADCHAR(string find, int badchar[], int m);
int main()
{
    clock_t time1, time2, time3, time4;
    string data = "";
    string tmp;
    ifstream datafile;
    datafile.open("data5.txt");
    while (getline(datafile, tmp))
    {
        data += tmp;
    }
    string find = "algorithm";
    time1 = clock();
    naive(data, find);
    time2 = clock();
    //cout << "naive " << (double)(time2 - time1) / CLOCKS_PER_SEC << " s" << endl;
    cout << (double)(time2 - time1) / CLOCKS_PER_SEC << endl;
    KMP(data, find);

    time3 = clock();
    //cout << "KMP " << (double)(time3 - time2) / CLOCKS_PER_SEC << " s" << endl;
    cout << (double)(time3 - time2) / CLOCKS_PER_SEC << endl;
    boyer_moore(data, find);
    time4 = clock();
    //cout << "boyer_moore " << (double)(time4 - time3) / CLOCKS_PER_SEC << " s" << endl;
    cout << (double)(time4 - time3) / CLOCKS_PER_SEC << endl;
}

void naive(string data, string find)
{
    int n = data.length();
    int m = find.length();
    int count = 0;
    for (int i = 0; i <= n - m; i++)
    {
        int j;
        for (j = 0; j < m; j++)
        {
            if (find[j] != data[i + j])
            {
                break;
            }
        }
        if (j == m)
        {
            count++;
        }
    }
}

void KMP(string data, string find)
{
    int n = data.length();
    int m = find.length();
    int lps[m];
    LPS(find, lps, m);
    int count = 0;
    int i = 0;
    int j = 0;
    while (i < n)
    {
        if (data[i] == find[j])
        {
            i++;
            j++;
        }
        if (j == m)
        {
            count++;
            j = lps[j - 1];
        }
        else if (i < n && data[i] != find[j])
        {
            if (j == 0)
            {
                i++;
            }
            else
            {
                j = lps[j - 1];
            }
        }
    }
}

void LPS(string find, int lps[], int m)
{
    lps[0] = 0;
    for (int i = 1; i < m; i++)
    {
        int len = 0;
        lps[i] = len;
        for (len = 1; len <= i; len++)
        {
            if (find.substr(0, len) == find.substr(i - len + 1, len))
            {
                lps[i] = len;
            }
        }
    }
}

void boyer_moore(string data, string find)
{
    int n = data.length();
    int m = find.length();
    int badchar[256];
    BADCHAR(find, badchar, m);
    int count = 0;
    int i = 0;
    int j;
    while (i <= n - m)
    {
        j = m - 1;
        while (j >= 0 && data[i + j] == find[j])
        {
            j--;
        }
        if (j < 0)
        {
            count++;
            if (i < n - m)
            {
                i = i + m - badchar[int(data[i + m])];
            }
            else
            {
                i++;
            }
        }
        else
        {
            i = i + max(1, j - badchar[int(data[i + j])]);
        }
    }
}

void BADCHAR(string find, int badchar[], int m)
{
    for (int i = 0; i < 256; i++)
    {
        badchar[i] = -1;
    }
    for (int i = 0; i < m; i++)
    {
        badchar[int(find[i])] = i;
    }
}
