#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>

using namespace std;


int cmax(int n, int*R, int*P, int *Q, int *X)
{
    int m=0,c=0; // m - moment do ktorego pracuje maszyna, c - moment do ktorego siega najdluzszy ogonek

    for(int i;i<n;i++){
        m = max(m,R[X[i]])+P[X[i]];
        c= max(c,m+Q[X[i]]);
    }
    return c;
}


void A(int n,int*R,int*P,int*Q, int*X) // dane wejsciowe, X - proponowana kolejnosc
{
   // for(int i=0;i<n;i++) X[i]=i;
    int order[]={9, 18, 22, 11, 5, 20, 21, 3, 24, 10, 14, 17, 12, 8, 6, 1, 13, 4, 16, 7, 15, 19, 23, 2};
    for(int i=0;i<n;i++) X[i]=order[i]-1;
}

void B(int n,int*R,int*P,int*Q, int*X)
{
   /*/ for(int i=0;i<n;i++) X[i]=i;
    int best=100000, bestx[n]; // najlepszy czas cmax, najlepsza kolejnosc
    for(int i=0;i<1000;i++){
        for(int i=0;i<n;i++) X[i]=i;
        random_shuffle(X,X+n);  //pro-gamer move
        if( cmax(n,R,P,Q,X) < best ){
            best = cmax(n,R,P,Q,X);
            for(int i=0;i<n;i++) bestx[i]=X[i];
        }
    }
    for(int i=0; i<n; i++)
        X[i]=bestx[i];*/
    int order[]={23, 21, 20, 10, 14, 17, 12, 8, 16, 24, 4, 15, 13, 5, 3, 7, 22, 9, 2, 18, 1, 11, 19, 6};
    for(int i=0;i<n;i++) X[i]=order[i]-1;
}

void C(int n,int*R,int*P,int*Q, int*X)
{
    int order[] = {9, 30, 48, 42, 29, 22, 12, 35, 33, 26, 19, 14, 31, 16, 21, 5, 41, 38, 2, 40, 45, 23, 46,
                    11, 8, 24, 1, 7, 27, 34, 3, 28, 25, 32, 39, 13, 18, 20, 4, 43, 6, 17, 36, 10, 47, 37, 44, 15};
    for(int i=0;i<n;i++) X[i]=order[i]-1;
}

void D(int n,int*R,int*P,int*Q, int*X)
{
    int order[] = {37, 19, 45, 17, 20, 21, 41, 25, 12, 24, 15, 13, 6, 4, 36, 30, 33, 46, 47, 43, 23, 18, 34, 14, 48,
                    39, 7, 10, 27, 26, 29, 5, 8, 32, 2, 16, 40, 22, 44, 28, 35, 3, 42, 9, 1, 11, 38, 31};
    for(int i=0;i<n;i++) X[i]=order[i]-1;
}


int main()
{
   // srand( time( NULL ) ); // konfiguracja generatora liczb losowych

    int n,R[100],P[100],Q[100],X[100],total=0;
    string datan[]={"data.1", "data.2", "data.3", "data.4"};


    for(int d=0;d<4;d++)
    {
        ifstream plik("data.txt");
        string s; while(s!=datan[d]) plik>>s;
        plik >> n;
        for(int i=0;i<n;i++)
            plik >> R[i] >> P[i] >> Q[i];
        plik.close();

        if(0==d) A(n,R,P,Q,X);
        else if(1==d) B(n,R,P,Q,X);
        else if(2==d) C(n,R,P,Q,X);
        else if(3==d) D(n,R,P,Q,X);

     /*   for(int i=0;i<n;i++){
            cout << "(" << X[i]+1 << ")\t"; cout.width(7); cout << left <<R[X[i]];
            cout.width(6); cout << left <<P[X[i]]; cout.width(6);cout<<left <<Q[X[i]]<<endl;
        }*/
        cout<<datan[d];
        cout<<"\nKolejnosc:\n"; for(int i=0;i<n;i++) cout<<X[i]+1<<" ";
        cout<<"\nCmax: " << cmax(n,R,P,Q,X)<<endl<<endl;
        total=total+cmax(n,R,P,Q,X);
     //   for(int i=0;i<n;i++){R[i]=NULL, P[i]=NULL, Q[i]=NULL, X[i]=NULL;}
    }

    cout << "Suma: " << total << endl;
    cin.get();

    return 0;
}
