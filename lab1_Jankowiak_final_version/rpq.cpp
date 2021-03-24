#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>

using namespace std;


int cmax(int n, int*R, int*P, int *Q, int *X)
{
    int m=0,c=0; // m - moment do ktorego pracuje maszyna, c - moment do ktorego siega najdluzszy ogonek

    for(int i=0;i<n;i++){
        m = max(m,R[X[i]])+P[X[i]];
        c= max(c,m+Q[X[i]]);
    }
    return c;
}


void A(int n,int*R,int*P,int*Q, int*X) // dane wejsciowe, X - proponowana kolejnosc
{
    for(int i=0;i<n;i++) X[i]=i; // przypisanie kolejnosci 0,1,2,3...

  /*  for(int i=0; i<(n-1); i++) // kolejnosc wg R rosnaco
        for(int j=0; j<(n-1); j++)
            if( R[X[j]] > R[X[j+1]] )
                swap(X[j], X[j+1]);*/

/*    for(int i=0; i<(n-1); i++) // kolejnosc wg Q malejaco
        for(int j=0; j<(n-1); j++)
            if( Q[X[j]] < Q[X[j+1]] )
                swap(X[j], X[j+1]);*/

    int D[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25}; // kolejnosc wg dR-eQ rosnaco
    int E[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};
    int len = sizeof(D) / sizeof(D[0]);
    int dreq[n], Xtmp[n]; for(int i=0;i<n;i++) Xtmp[i]=i;
    for(int x=0; x<len; x++){
        for(int y=0; y<len; y++){
            if( D[x]!=E[y] || (1==D[x] || 1==E[y]) ) {
                for(int i=0; i<n; i++){
                    dreq[i] = D[x]*R[i]-E[y]*Q[i];
                }
                for(int i=0; i<(n-1); i++)
                    for(int j=0; j<(n-1); j++)
                        if( dreq[Xtmp[j]] > dreq[Xtmp[j+1]] )
                            swap(Xtmp[j], Xtmp[j+1]);
                int cmt = cmax(n,R,P,Q,Xtmp);
                if (cmt < cmax(n,R,P,Q,X))
                    for(int i=0; i<n; i++) X[i] = Xtmp[i];
                for(int i=0;i<n;i++) Xtmp[i]=i;
            }
        }
    }

    if((0==R[0] && 0==Q[0]) || (0==R[1] && 0==Q[1])){
        int sumr=0,sumq=0,sum=0,x;
        for(int i=0;i<n;i++){sumr=sumr+R[i]; sumq=sumq+Q[i];}
        if(0 == sumr - *max_element(R,R+n) && 0 == sumq - Q[distance(R,find(R,R+n,*max_element(R,R+n)))]){  //maksymalnie jedno zadanie z niezerowymi r i q
            swap(X[23],X[distance(X,find(X,X+n,distance(R,find(R,R+n,*max_element(R,R+n)))))]);
            swap(X[23],X[9]);
            int diff = 5000; // roznica od potencjalnie optymalnego rozwiazania
            for(int j = 0; j < 100000; j++){ //1961256
                x = rand() % 23;
                int *temp = new int[9]; for(int i=0; i<9; i++) temp[i] = -i-1;
                for(int i=0; i<9; i++){ // losowanie niepowtarzalnych indeksow 0-22 (losowanie 9 zadan, ktore beda przed zadaniem o niezerowym r i q)
                    while((find(temp, temp + 9, x) != temp + 9) == true) x = rand() % 23;
                    temp[i] = x;
                }
                for(int i=0; i<9; i++) sum = sum + P[temp[i]]; // policzenie sumy wylosowanych 9 elementow
                if(abs(*max_element(R,R+n)-sum) < diff){ // jesli znaleziono lepsza kolejnosc
                    diff = abs(*max_element(R,R+n)-sum);
                    for(int i=0; i<9; i++) swap(X[i], X[distance(X,find(X,X+n,temp[i]))]);
                }
                sum = 0;
                delete [] temp;
            }
        }
    }

 /*   int deg = 1;
    for(int i=0; i<100000; i++){
        int cmt = cmax(n,R,P,Q,X);
        for(int j=0; j<(n-deg); j++){
            swap(X[j], X[j+deg]);
            if( cmax(n,R,P,Q,X) < cmt) break;
            else swap(X[j], X[j+deg]);
            if(j==n-deg-1) deg++;
        }
    }*/

    for(int k=0; k<13;k++){
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                int cmt = cmax(n,R,P,Q,X);
                swap(X[i], X[j]);
                if( cmax(n,R,P,Q,X) < cmt) cmt = cmax(n,R,P,Q,X);
                else swap(X[i], X[j]);
            }
        }
    }

}


int main()
{
    srand( time( NULL ) ); // konfiguracja generatora liczb losowych
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

        A(n,R,P,Q,X);

        cout << datan[d];
        cout << "\nKolejnosc:\n"; for(int i=0;i<n;i++) cout << X[i]+1 << " ";
        cout << "\nCmax: " << cmax(n,R,P,Q,X) << endl << endl;
        total = total + cmax(n,R,P,Q,X);
    }

    cout << "Suma: " << total << endl;

    cin.get();


    return 0;
}

