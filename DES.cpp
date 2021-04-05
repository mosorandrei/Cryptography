// DES.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <set>
#include <cstdlib>
#include <sstream>
using namespace std;
string hexa_in_binar(string s)
{
    map<char, string> dictionar;
dictionar.insert(pair<char,string>('0',"0000"));
dictionar.insert(pair<char, string>('1', "0001"));
dictionar.insert(pair<char, string>('2', "0010"));
dictionar.insert(pair<char, string>('3', "0011"));
dictionar.insert(pair<char, string>('4', "0100"));
dictionar.insert(pair<char, string>('5', "0101"));
dictionar.insert(pair<char, string>('6', "0110"));
dictionar.insert(pair<char, string>('7', "0111"));
dictionar.insert(pair<char, string>('8', "1000"));
dictionar.insert(pair<char, string>('9', "1001"));
dictionar.insert(pair<char, string>('A', "1010"));
dictionar.insert(pair<char, string>('B', "1011"));
dictionar.insert(pair<char, string>('C', "1100"));
dictionar.insert(pair<char, string>('D', "1101"));
dictionar.insert(pair<char, string>('E', "1110"));
dictionar.insert(pair<char, string>('F', "1111"));
    string bin = "";
    for (int i = 0; i < s.size(); i++) {
        bin += dictionar[s[i]];
    }
    return bin;
}
string binar_in_hexa(string s)
{
    map<string, char> dictionar;
    dictionar.insert(pair<string,char>("0000",'0'));
    dictionar.insert(pair<string,char>("0001",'1'));
    dictionar.insert(pair<string,char>("0010",'2'));
    dictionar.insert(pair<string,char>("0011",'3'));
    dictionar.insert(pair<string,char>("0100",'4'));
    dictionar.insert(pair<string,char>("0101",'5'));
    dictionar.insert(pair<string,char>("0110",'6'));
    dictionar.insert(pair<string,char>("0111",'7'));
    dictionar.insert(pair<string,char>("1000",'8'));
    dictionar.insert(pair<string,char>("1001",'9'));
    dictionar.insert(pair<string,char>("1010",'A'));
    dictionar.insert(pair<string,char>("1011",'B'));
    dictionar.insert(pair<string,char>("1100",'C'));
    dictionar.insert(pair<string,char>("1101",'D'));
    dictionar.insert(pair<string,char>("1110",'E'));
    dictionar.insert(pair<string,char>("1111",'F'));
    string bin = "";
    for (int i = 0; i < s.length(); i += 4) {
        string ch = "";
        ch += s[i];
        ch += s[i + 1];
        ch += s[i + 2];
        ch += s[i + 3];
        bin += dictionar[ch];
    }
    return bin;
}

string permutare(string k, int* sir, int n)
{
    string IP = "";
    for (int i = 0; i < n; i++) {
        IP += k[sir[i] - 1];
    }
    return IP;
}
string shiftare_stanga(string k, int shifts)
{
    string s = "";
    for (int i = 0; i < shifts; i++) {
        for (int j = 1; j < 28; j++) {
            s += k[j];
        }
        s += k[0];
        k = s;
        s = "";
    }
    return k;
}
string xor_function(string a, string b)
{
    string ret = "";
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == b[i]) {
            ret += "0";
        }
        else {
            ret += "1";
        }
    }
    return ret;
}
string encrypt(string plaintext, vector<string> rkb, vector<string> rkh)
{
   
    plaintext = hexa_in_binar(plaintext);

  
    int initial_perm[64] = { 58, 50, 42, 34, 26, 18, 10, 2,
                             60, 52, 44, 36, 28, 20, 12, 4,
                             62, 54, 46, 38, 30, 22, 14, 6,
                             64, 56, 48, 40, 32, 24, 16, 8,
                             57, 49, 41, 33, 25, 17, 9, 1,
                             59, 51, 43, 35, 27, 19, 11, 3,
                             61, 53, 45, 37, 29, 21, 13, 5,
                             63, 55, 47, 39, 31, 23, 15, 7 };
    
    plaintext = permutare(plaintext, initial_perm, 64);
   // cout << "Dupa permutarea initiala: " << binar_in_hexa(plaintext) << endl;

   
    string left = plaintext.substr(0, 32);
    string right = plaintext.substr(32, 32);
   // cout << "Dupa injumatatire: L0=" << binar_in_hexa(left)
     //   << " R0=" << binar_in_hexa(right) << endl;

    
    int exp_d[48] = { 32, 1, 2, 3, 4, 5, 4, 5,
                      6, 7, 8, 9, 8, 9, 10, 11,
                      12, 13, 12, 13, 14, 15, 16, 17,
                      16, 17, 18, 19, 20, 21, 20, 21,
                      22, 23, 24, 25, 24, 25, 26, 27,
                      28, 29, 28, 29, 30, 31, 32, 1 };

  
    int s[8][4][16] = { { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
                          0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
                          4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
                          15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 },
                        { 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
                          3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
                          0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
                          13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 },

                        { 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
                          13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
                          13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
                          1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 },
                        { 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
                          13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
                          10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
                          3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 },
                        { 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
                          14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
                          4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
                          11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 },
                        { 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
                          10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
                          9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
                          4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 },
                        { 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
                          13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
                          1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
                          6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 },
                        { 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
                          1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
                          7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
                          2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 } };

   
    int per[32] = { 16, 7, 20, 21,
                    29, 12, 28, 17,
                    1, 15, 23, 26,
                    5, 18, 31, 10,
                    2, 8, 24, 14,
                    32, 27, 3, 9,
                    19, 13, 30, 6,
                    22, 11, 4, 25 };

    cout << endl;
    for (int i = 0; i < 16; i++) {
        
        string right_expanded = permutare(right, exp_d, 48);

        
        string x = xor_function(rkb[i], right_expanded);

        
        string op = "";
        for (int i = 0; i < 8; i++) {
            int row = 2 * int(x[i * 6] - '0') + int(x[i * 6 + 5] - '0');
            int col = 8 * int(x[i * 6 + 1] - '0') + 4 * int(x[i * 6 + 2] - '0') + 2 * int(x[i * 6 + 3] - '0') + int(x[i * 6 + 4] - '0');
            int val = s[i][row][col];
            op += char(val / 8 + '0');
            val = val % 8;
            op += char(val / 4 + '0');
            val = val % 4;
            op += char(val / 2 + '0');
            val = val % 2;
            op += char(val + '0');
        }
        
        op = permutare(op, per, 32);

       
        x = xor_function(op, left);

        left = x;

        
        if (i != 15) {
            swap(left, right);
        }
      //  cout << "Pasul : " << i + 1 << " " << binar_in_hexa(left) << " "
       //     << binar_in_hexa(right) << " " << rkh[i] << endl;
    }

   
    string combine = left + right;

   
    int final_perm[64] = { 40, 8, 48, 16, 56, 24, 64, 32,
                           39, 7, 47, 15, 55, 23, 63, 31,
                           38, 6, 46, 14, 54, 22, 62, 30,
                           37, 5, 45, 13, 53, 21, 61, 29,
                           36, 4, 44, 12, 52, 20, 60, 28,
                           35, 3, 43, 11, 51, 19, 59, 27,
                           34, 2, 42, 10, 50, 18, 58, 26,
                           33, 1, 41, 9, 49, 17, 57, 25 };

   
    string cipher = binar_in_hexa(permutare(combine, final_perm, 64));
    return cipher;
}
string DES_enc(string plaintext,string cheie)
{
    cout << endl;
    cout << "DES ALGORITHM FOR PLAINTEXT : " << plaintext << " AND KEY : " << cheie << endl;
    cheie = hexa_in_binar(cheie);
    //cout << cheie;
    int keyp[56] = { 57, 49, 41, 33, 25, 17, 9,
                     1, 58, 50, 42, 34, 26, 18,
                     10, 2, 59, 51, 43, 35, 27,
                     19, 11, 3, 60, 52, 44, 36,
                     63, 55, 47, 39, 31, 23, 15,
                     7, 62, 54, 46, 38, 30, 22,
                     14, 6, 61, 53, 45, 37, 29,
                     21, 13, 5, 28, 20, 12, 4 };

    cheie = permutare(cheie, keyp, 56);
    int shift_table[16] = { 1, 1, 2, 2,
                           2, 2, 2, 2,
                           1, 2, 2, 2,
                           2, 2, 2, 1 };

    int key_comp[48] = { 14, 17, 11, 24, 1, 5,
                         3, 28, 15, 6, 21, 10,
                         23, 19, 12, 4, 26, 8,
                         16, 7, 27, 20, 13, 2,
                         41, 52, 31, 37, 47, 55,
                         30, 40, 51, 45, 33, 48,
                         44, 49, 39, 56, 34, 53,
                         46, 42, 50, 36, 29, 32 };
    
    string left = cheie.substr(0, 28);
    string right = cheie.substr(28, 28);

    vector<string> rk_binar; 
    vector<string> rk_hexa; 
    for (int i = 0; i < 16; i++) {
        
        left = shiftare_stanga(left, shift_table[i]);
        right = shiftare_stanga(right, shift_table[i]);

        // Combining
        string combine = left + right;

        // Key Compression
        string RoundKey = permutare(combine, key_comp, 48);

        rk_binar.push_back(RoundKey);
        rk_hexa.push_back(binar_in_hexa(RoundKey));
    }

    cout << "\nEncryption:\n\n";
    string cipher = encrypt(plaintext, rk_binar, rk_hexa);
    cout << "\nCipher Text: " << cipher << endl;
    string copie_return = cipher;
    cout << "\nDecryption:\n\n";
    reverse(rk_binar.begin(), rk_binar.end());
    reverse(rk_hexa.begin(), rk_hexa.end());
    string text = encrypt(cipher, rk_binar, rk_hexa);
    cout << "\nPlain Text: " << text << endl;
    cout << endl;
    cout << "---------------------END------------------------" << endl<<endl;

    return copie_return;
} 
string DES_dec(string cipher,string cheie)
{
    cout << endl;
    cout << "DES ALGORITHM FOR CYPHER : " << cipher<< " AND KEY : " << cheie << endl;
    cheie = hexa_in_binar(cheie);
    //cout << cheie;
    int keyp[56] = { 57, 49, 41, 33, 25, 17, 9,
                     1, 58, 50, 42, 34, 26, 18,
                     10, 2, 59, 51, 43, 35, 27,
                     19, 11, 3, 60, 52, 44, 36,
                     63, 55, 47, 39, 31, 23, 15,
                     7, 62, 54, 46, 38, 30, 22,
                     14, 6, 61, 53, 45, 37, 29,
                     21, 13, 5, 28, 20, 12, 4 };

    cheie = permutare(cheie, keyp, 56);
    int shift_table[16] = { 1, 1, 2, 2,
                           2, 2, 2, 2,
                           1, 2, 2, 2,
                           2, 2, 2, 1 };

    int key_comp[48] = { 14, 17, 11, 24, 1, 5,
                         3, 28, 15, 6, 21, 10,
                         23, 19, 12, 4, 26, 8,
                         16, 7, 27, 20, 13, 2,
                         41, 52, 31, 37, 47, 55,
                         30, 40, 51, 45, 33, 48,
                         44, 49, 39, 56, 34, 53,
                         46, 42, 50, 36, 29, 32 };

    string left = cheie.substr(0, 28);
    string right = cheie.substr(28, 28);

    vector<string> rk_binar;
    vector<string> rk_hexa;
    for (int i = 0; i < 16; i++) {

        left = shiftare_stanga(left, shift_table[i]);
        right = shiftare_stanga(right, shift_table[i]);

        // Combining
        string combine = left + right;

        // Key Compression
        string RoundKey = permutare(combine, key_comp, 48);

        rk_binar.push_back(RoundKey);
        rk_hexa.push_back(binar_in_hexa(RoundKey));
    }

    cout << "\nEncryption:\n\n";
    cout << "\nCipher Text: " << cipher << endl;
    
    cout << "\nDecryption:\n\n";
    reverse(rk_binar.begin(), rk_binar.end());
    reverse(rk_hexa.begin(), rk_hexa.end());
    string text = encrypt(cipher, rk_binar, rk_hexa);
    cout << "\nPlain Text: " << text << endl;
    cout << endl;
    cout << "---------------------END------------------------" << endl << endl;
    
    return text;
}

string dec_to_hexa(int num)
{
    string d = "0123456789ABCDEF";

    
    string res;
    int contor = 64;
    while (contor != 0)
    {


        while (num > 0)
        {
            res = d[num % 16] + res;
            num /= 16;
            contor--;
        }
        contor--;
        res.insert(0, "0");
    }
    return res;
}
string meet_in_the_middle(string plaintext, string cipher)
{
    set<string, greater<string>> s2;
    do
    {
        string x = "";
        for (int i = 0; i < 8; i++)
        {
            if (rand() % 2 == 0)
                x = x + "0";
            else x = x + "1";
        }
        string ceva = x;
        for (int i = 0; i < 7; i++)
        {
            x = x + ceva;
        }
        s2.insert(x);
    } while (s2.size() != 256);
    set<string>::iterator itr2;
    set<string>::iterator itr3;
    vector<string> v;
    vector<string> v2;
    int ok = 0;
    for (itr2 = s2.begin(); itr2 != s2.end(); itr2++)
    {
        string ceva = *itr2;
        string l = DES_enc(plaintext, binar_in_hexa(ceva));

        /*for (itr3 = s2.begin(); itr3 != s2.end(); itr3++)
        {
            string ceva2 = *itr3;
            string r = DES_dec(cipher, binar_in_hexa(ceva2));
            if (l == r) {
                cout << "Am gasit o pereche : " << ceva << " " << ceva2;
                return;
            }
        }*/
        v.push_back(l);
    }
    for (itr3 = s2.begin(); itr3 != s2.end(); itr3++)
    {
        string ceva2 = *itr3;
        string l = DES_dec(cipher, binar_in_hexa(ceva2));

        /*for (itr3 = s2.begin(); itr3 != s2.end(); itr3++)
        {
            string ceva2 = *itr3;
            string r = DES_dec(cipher, binar_in_hexa(ceva2));
            if (l == r) {
                cout << "Am gasit o pereche : " << ceva << " " << ceva2;
                return;
            }
        }*/
        v2.push_back(l);
    }
    vector<string>::iterator it;
    vector<string>::iterator it2;
    vector<string>::iterator it3;
    string p;
    for (it = v.begin(); it != v.end() && ok ==0; it++)
    {
        string x = *it;
        for (it2 = v2.begin(); it2 != v2.end() && ok==0; it2++)
        {
            
            string y = *it2;
            it3 = find(v.begin(),v.end(), y);
             p = *it3;
            if (it3 != v.end())
            {
                ok++;
                
            }
            
            /*if (x == y) {
                ok++;
                cout << endl;
                cout << x << "s-a terminat--------------------------------------------------------------------------------------------------------------" << endl; 

                return x;
            }
            else cout << "hei" << endl;*/
        }
    }
   
   p= *it3;
   string res="";
   for (itr2 = s2.begin(); itr2 != s2.end(); itr2++)
   {
       string ceva = *itr2;
       string l = DES_enc(plaintext, binar_in_hexa(ceva));
       if (l == p) { res = res + ceva; }
   }
   for (itr3 = s2.begin(); itr3 != s2.end(); itr3++)
   {
       string ceva2 = *itr3;
       string l2 = DES_dec(cipher, binar_in_hexa(ceva2));
       if (l2 == p) { res = res + ceva2; }
   }
   return res;
}
string and_function(string a, string b)
{
    string ret = "";
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == b[i] && a[i]=='1' ) {
            ret += "1";
        }
        else {
            ret += "0";
        }
    }
    return ret;
}
int addOne(int x)
{
    int m = 1;

    // Flip all the set bits
    // until we find a 0
    while (x & m)
    {
        x = x ^ m;
        m <<= 1;
    }

    // flip the rightmost 0 bit
    x = x ^ m;
    return x;
}

int main()
{
    string plaintext, cheie_unu,cheie_doi;
    plaintext = "543216ABCD123456";
    cheie_unu = "0000000000000000";
    cheie_doi = "FFFFFFFFFFFFFFFF";
    
    cout << "citesc1";
    string cipher_ceva = DES_enc(plaintext, cheie_unu);
    string cifru = DES_enc(DES_enc(plaintext, cheie_unu),cheie_doi);
    cout <<cipher_ceva << endl;
    cout << "citesc2";
    cout  <<DES_dec(cifru, cheie_unu) << endl;
 
    //cout << meet_in_the_middle(plaintext,cifru);
    cout << "am inceput meet"<<endl;
    string res= meet_in_the_middle(plaintext, cifru);
    
    for (int i = 0; i < res.length() / 2; i=i+64)
    {
        cout << "cheia unu poate fi  : " << res.substr(i, 64) << endl; //<< " cheia 2 este : " << res.substr(32, 32) << endl;
    }
    for (int i = res.length() / 2; i < res.length(); i = i + 64)
    {
        cout << "cheia doi poate fi  : " << res.substr(i, 64) << endl; //<< " cheia 2 este : " << res.substr(32, 32) << endl;
    }
    cout << "am terminat";
    /*set<string, greater<string>> s2;
    do
    {
        string x = "";
        for (int i = 0; i < 8; i++)
        {
            if (rand() % 2 == 0)
                x = x + "0";
            else x = x + "1";
        }
        string ceva = x;
        for (int i = 0; i < 8; i++)
        {
            x = x + ceva;
        }
        s2.insert(x);
    } while (s2.size() != 256);
    set<string>::iterator itr2;
    set<string>::iterator itr3;
    for (itr2 = s2.begin(); itr2 != s2.end(); itr2++)
    {
        string ceva = *itr2;
        string l = DES_enc(plaintext, binar_in_hexa(ceva));
        if (l == res) { cout << "cheia unu este : " << l << endl; }
    }
    for (itr3 = s2.begin(); itr3 != s2.end(); itr3++)
    {
        string ceva2 = *itr3;
        string l2 = DES_dec(cifru, binar_in_hexa(ceva2));
        if (l2 == res) { cout << "cheia doi este : " << l2 << endl; }
    }
    */
    

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

