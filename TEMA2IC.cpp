// TEMA2IC.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "NTL/ZZ.h"
#include <cmath>
using namespace std;
using namespace NTL;

ofstream fout("outBBS.txt");
ofstream rout("outJacobi.txt");

long witness(const ZZ& n, const ZZ& x)
{
    ZZ m, y, z;
    long j, k;

    if (x == 0) return 0;

    // compute m, k such that n-1 = 2^k * m, m odd:

    k = 1;
    m = n / 2;
    while (m % 2 == 0) {
        k++;
        m /= 2;
    }

    z = PowerMod(x, m, n); // z = x^m % n
    if (z == 1) return 0;

    j = 0;
    do {
        y = z;
        z = (y * y) % n;
        j++;
    } while (j < k && z != 1);

    return z != 1 || y != n - 1;
}


long PrimeTest(const ZZ& n, long t=0)
{
    if (n <= 1) return 0;

    // first, perform trial division by primes up to 2000

    PrimeSeq s;  // a class for quickly generating primes in sequence
    long p;

    p = s.next();  // first prime is always 2
    while (p && p < 2000) {
        if ((n % p) == 0) return (n == p);
        p = s.next();
    }

    // second, perform t Miller-Rabin tests

    ZZ x;
    long i;

    for (i = 0; i < t; i++) {
        x = RandomBnd(n); // random number between 0 and n-1

        if (witness(n, x))
            return 0;
    }

    return 1;
}
ZZ next_usable_prime(const ZZ& n)
{
    if (PrimeTest(n) == 1 && n % 4 == 3)
        return n;
    else return next_usable_prime(n + 1);
}
int numberof0(string a)
{
    int count = 0;
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] == '0') count++;
    }
    return count;
}
ZZ SymbolJacobi(const ZZ& a, const ZZ& n)
{
    ZZ ca, cn;
    ca = a % n;
    cn = n;
    ZZ t,r;
    t = 1;
    while (ca != 0) {
        while (ca % 2 == 0) {
            ca = ca / 2;
            
            r= cn % 8;
            if (r == 3 || r == 5)
                t = -t;
        }
        swap(ca, cn);
        if (ca % 4 == 3 && cn % 4 == 3)
            t = -t;
        ca =ca % cn;
    }
    if (cn == 1) return t;
    else return ZZ{ 0 };
}
int numberofzero(string s)
{
    int k = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '0') k++;
    }
    return k;
}
string LSFR(string seed, int cycles)
{

    string s = seed;
    string ret;
    int copie = cycles;
    int count = 0;
    while (copie!=0)
    {   // 32, 28 , 27 ,1
        // 1, 2, 4 , 15
        int k1 = s[1] - '0';
        int k2 = s[2] - '0';  // the max length polynom for 16 bits
        int k3 = s[4] - '0';
        int k4 = s[15] - '0';
        int x = k1 ^ k2 ^ k3 ^ k4;
        if (s[s.length() - 1] == '0')
        {
            ret = ret + "0";
        }
        else ret = ret + "1";
        string aux;
        if (x == 0)
        {
            aux = aux + "0";
        }
        else aux = aux + "1";
        aux = aux + s.substr(0, s.length() - 1);
        s = "";
        s = aux;
        aux = "";
        copie--;
    }
    return ret;
}
int main()
{  /*
    ZZ a, b, c, result, M, N, seed;
    long t;
    int bit;
    RandomLen(a, 512);
    RandomLen(b, 512);
    cout << "Primul numar pentru BBS de la tastatura este:"<<a<< endl;
    
    cout << "Al doilea numar pentru BBS de la tastatura este :"<<b<<endl;
    
    //result=PowerMod(a,b,c);
    //cout << result<<" "<< PrimeTest(a);;
    a = next_usable_prime(a);
    b = next_usable_prime(b);
    //cout << a<<" "<<b<<" "<<numberof0("00100");
    
    M = a * b;
    cout << "Produsul lor este : " << M<<endl;
    //N = pow(2, 20);
    cout << "Numarul de biti generati:"<<endl;
    cin >> N;
    //cout << endl;
    //cout << N;
    //cout << endl;
    string output = "";
    /* for (int i = 0; i < N; i++)
     {

     }
    do {
        seed = RandomBnd(pow(2,20));
    } while (GCD(seed, M) != 1);
    cout << "Seed ul este: " << seed<<endl;
    for (int i = 0; i < N; i++)
    {
        //seed = seed * seed % M;
        seed = PowerMod(seed, 2, M);
        bit = seed % 2;
        if (bit == 0) output = output + "0";
        else output = output + "1";
    }
    //cout << "BBS:"<<output<<endl;
    fout << output;
    cout << "NUMBER OF 0:" << (float)(numberof0(output) * 100) / output.size() << endl;
    cout << "NUMBER OF 1:" << (float)(output.size() - numberof0(output))*100/output.size() << endl;

    ZZ n1, n2;
    RandomLen(n1, 512);
    cout << "Primul numar pentru Jacobi generat random este: " << n1 << endl;
   
    RandomLen(n2,512);
    cout << "Al doilea numar pentru Jacobi generat random este: " << n2 << endl;
    n1 = next_usable_prime(n1);
    n2 = next_usable_prime(n2);

    M = n1 * n2;
    ZZ seedJacobi,NUM;
    RandomLen(seedJacobi, 512);
    seedJacobi = seedJacobi % M;
    cout << "Seed-ul pentru Jacobi este : " << seedJacobi << endl;
    string outputJacobi = "";
    cout << "Numarul de biti generati pentru Jacobi: " << endl;
    cin >> NUM;
   
    ZZ contor;
    for (int i = 0; i < NUM; i++)
    {
        contor = SymbolJacobi(seedJacobi + i, M);
        if (contor == -1) outputJacobi = outputJacobi + "0";
        else outputJacobi = outputJacobi + "1";
    }
    //cout << "Jacobi:" << outputJacobi << endl;
    rout << outputJacobi;
    cout << "NUMBER OF 0:" << (float)numberof0(outputJacobi)*100/outputJacobi.size() << endl;
    cout << "NUMBER OF 1:" << (float)(outputJacobi.size() - numberof0(outputJacobi))*100/outputJacobi.size() << endl;
        //cout << "Jacobi's symbol for :" << n1 << " and " << n2 << " este: " << SymbolJacobi(n1, n2)<<endl;
        //cout << "Jacobi's symbol for :" << n1 << " and " << n2 << " este (cu functie) : " <<Jacobi(n1, n2);
     */
    string seed = "0001000110010101";
    int nbofbits = 65535;
    cout << LSFR(seed, nbofbits) << endl;
    cout << "Numarul de 0 : " << numberofzero(LSFR(seed, nbofbits)) * 1.0 / nbofbits * 100 << endl;
    cout << "Numarul de 1 : " << 100.0 - numberofzero(LSFR(seed, nbofbits)) * 1.0 / nbofbits * 100;


}

