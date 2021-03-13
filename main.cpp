#include <iostream>
#include <fstream>

using namespace std;


int cmax(int n, int*R, int*P, int *Q, int *X)
{
    int m=0,c=0; // m - moment do ktorego pracuje maszyna, c - moment do ktorego siega najdluzszy ogonek

    for(int i;i<n;i++)
    {
        m = max(m,R[X[i]])+P[X[i]];
        c= max(c,m+Q[X[i]]);
    }
    return c;
}


void A(int n,int*R,int*P,int*Q, int*X) // dane wejsciowe, X - proponowana kolejnosc
{
    for(int i=0;i<n;i++) X[i]=i;
    //cmax(n,R,P,Q,X);
}


int main()
{
    int n,R[100],P[100],Q[100],X[100];

    ifstream plik("data.txt");
    string s; while(s!="data.1") plik>>s;

    plik >> n;
    for(int i=0;i<n;i++)
        plik >> R[i] >> P[i] >> Q[i];
    plik.close();

    A(n,R,P,Q,X);

    for(int i=0;i<n;i++)
        cout << i << ") "<<R[i]<<" "<<P[i]<<" "<<Q[i]<<endl;


    cout<<"\nKolejnosc:\n"; for(int i=0;i<n;i++) cout<<X[i]<<" ";
    cout<<"\nCmax: " << cmax(n,R,P,Q,X)<<endl;

    cin.get();

    return 0;
}
