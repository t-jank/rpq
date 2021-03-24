#include <iostream>
#include <fstream>

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
    for(int i=0;i<n;i++) X[i]=i; // przypisanie kolejnosci 1,2,3...

  /*  for(int i=0; i<(n-1); i++) // kolejnosc wg R rosnaco
        for(int j=0; j<(n-1); j++)
            if( R[X[j]] > R[X[j+1]] )
                swap(X[j], X[j+1]);*/

/*    for(int i=0; i<(n-1); i++) // kolejnosc wg Q malejaco
        for(int j=0; j<(n-1); j++)
            if( Q[X[j]] < Q[X[j+1]] )
                swap(X[j], X[j+1]);*/

    int D[]={1,3,4,8,11,12,21,23}; // kolejnosc wg dR-eQ rozsnaco
    int E[]={1,3,4,8,11,12,21,23};
    int len = sizeof(D) / sizeof(D[0]);
    int dreq[n], Xtmp[n]; for(int i=0;i<n;i++) Xtmp[i]=i;
    for(int x=0; x<len; x++){
        for(int y=0; y<len; y++){
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

            /*cout << "Wartosci:\n";
            cout.width(7); cout << left << "nr";
            cout.width(7); cout << left << "R";
            cout.width(6); cout << left << "P";
            cout.width(6); cout << left << "Q" << endl;
            for(int i = 0; i < n; i++){
                cout.width(7); cout << left;
                cout << X[i]+1;
                cout.width(7); cout << left;
                cout << R[X[i]];
                cout.width(6); cout << left;
                cout << P[X[i]];
                cout.width(6); cout << left;
                cout << Q[X[i]] << endl;
            }*/

    }

    cout << "Suma: " << total << endl;

    cin.get();


    return 0;
}

