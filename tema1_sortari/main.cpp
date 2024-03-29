#include <iostream>
#include <fstream>
#include <time.h>
#include <chrono>
#include <algorithm>
#include <vector>
using namespace std;
using namespace std::chrono;

ifstream f("teste.in");
ofstream g("timp.out");

int *v = new int[100000000];
int *vaux = new int[100000000];
int n,mx=0;

bool test_sort(int v[],int n);

int maxim(int v[],int n)
{
    int maxi=v[0];
    for (int i=1; i<n; i++)
        if(v[i]>maxi)
            maxi=v[i];
    return maxi;
}

void sortcifre(int v[],int n,int exp)
{
    int v2[n],fr[10]= {0};

    for(int i=0; i<n; i++)
        fr[(v[i]/exp)%10]++;//calculam frecvente fiecarei cifre

    for(int i=1; i<10; i++)
        fr[i]=fr[i]+fr[i-1];//calculam pozițiile finale ale fiecărei cifre

    for(int i=n-1; i>=0; i--)
    {
        v2[fr[(v[i]/exp)%10]-1]=v[i];
        fr[(v[i]/exp)%10]--;//punem elementele în vectorul nou în ordinea corectă
    }

    for(int i=0; i<n; i++)
        v[i]=v2[i];

}

void radixSort(int v[],int n)
{
    int maxi=maxim(v,n);
    for(int exp=1; maxi/exp>0; exp=exp*10)
        sortcifre(v,n,exp);
}

void merge(int v[], int stg, int mij, int dr)
{
    int n1=mij-stg + 1;
    int n2=dr-mij;

    //Crearea subvectorilor temporari pt stanga si dreapta
    int vs[n1], vd[n2];

    //copiem datele în subvectorii temporari
    for (int i=0; i<n1; i++)
    {
        vs[i]=v[stg+i];
    }
    for (int j=0; j<n2; j++)
    {
        vd[j]=v[mij+1+j];
    }

    //interclasarea subvectorilor temporari înapoi în vectorul principal
    int i=0, j=0, k=stg;
    while (i<n1 && j<n2)
    {
        if (vs[i] <= vd[j])
        {
            v[k]=vs[i];
            i++;
        }
        else
        {
            v[k]=vd[j];
            j++;
        }
        k++;
    }

    //copierea elementelor rămase din vs (dacă există)
    while (i<n1)
    {
        v[k]=vs[i];
        i++;
        k++;
    }

    //copierea elementelor rămase din vd (dacă există)
    while (j<n2)
    {
        v[k] =vd[j];
        j++;
        k++;
    }
}
void mergeSort(int v[], int stg, int dr)
{
    if (stg >= dr)
    {
        //vectorul are cel mult un element, deci este deja sortat
        return;
    }

    int mij=stg+(dr-stg)/2;
    mergeSort(v,stg,mij);   //sortarea primei jumătăți a vectorului
    mergeSort(v,mij+1,dr);  //sortarea celei de-a doua jumătăți a vectorului
    merge(v,stg,mij,dr); //interclasarea celor două jumătăți sortate
}
void shellSort(int v[], int n)
{
    for (int k=n/2; k>0; k=k/2)
    {
        for (int i=k; i<n; i=i+1)
        {
            int aux=v[i];
            int j;
            for (j=i; j>=k && v[j-k]>aux; j=j-k)
                v[j]=v[j-k];
            v[j]=aux;
        }
    }
}
void bubbleSort(int v[], int n)
{
    for (int i=0; i<n-1; i++)
    {
        for (int j=0; j<n-i-1; j++)
        {
            if (v[j]>v[j+1])
            {
                int aux = v[j];
                v[j]=v[j+1];
                v[j+1]=aux;
            }
        }
    }
}
void countSort(int v[], int n)
{
    int maxi=v[0];
    for (int i=1; i<n; i++)
        if (v[i]>maxi)
            maxi=v[i];

    int *vcount=new int[maxi+1];

    for(int i=0; i<maxi+1; i++)
        vcount[i]=0;


    for (int i=0; i<n; i++)
        vcount[v[i]]++;

    for (int i=1; i<=maxi; i++)
        vcount[i]=vcount[i]+vcount[i-1];

    int sortedv[n];
    for (int i=n-1; i>=0; i--)
    {
        sortedv[vcount[v[i]]-1]=v[i];
        vcount[v[i]]--;
    }

    for (int i=0; i<n; i++)
        v[i] = sortedv[i];

    delete[] vcount;
}

int partition(int v[], int low, int high) {
    int pivot = v[high];
    int i = (low - 1); // indexul elementului mai mic

    for (int j = low; j <= high - 1; j++) {
        if (v[j] < pivot) {
            i++; // Incrementam indexul elem mai mare
            swap(v[i], v[j]);
        }
    }
    swap(v[i + 1], v[high]);
    return (i + 1);
}

void quickSort(int v[], int low, int high) {
    if (low < high) {
        int pi = partition(v, low, high);

        // Sorteaza separate inainte si dupa partitie
        quickSort(v, low, pi - 1);
        quickSort(v, pi + 1, high);
    }
}


bool test_sort(int v[],int n)
{
    if(n==0 || n==1) return true;
    for(int i=1; i<n; i++)
        if(v[i] < v[i-1]) return false;
    return true;
}


int main()
{
    int nrteste,maxi;
    f>>nrteste;
    for(int k=1; k<=nrteste; k++)
    {
        f>>n>>maxi;
        for(int i=0; i<n; i++)
        {
            v[i]=rand()%maxi;
            cout<<v[i]<<" ";
        }
    g<<endl<<"Timpii pentru testul "<<k<<endl;
    // copiati elemente v[i] in vaux[i]
    for(int i=0; i<n; i++)
        vaux[i]=v[i];

    cout<<endl;
    auto start = high_resolution_clock::now();
    bubbleSort(vaux,n);
    if(test_sort(vaux,n))
    {
        cout<<"Bubblesort: ";
        for (int i=0; i<n; i++)
            cout<<vaux[i]<< " ";
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        g<<"Timpul pentru BubbleSort este: "<<duration.count()<<" nanosecunde"<<endl;
    }


    for(int i=0; i<n; i++)
        vaux[i]=v[i];

    cout<<endl;
    auto start1 = high_resolution_clock::now();
    mergeSort(vaux,0,n-1);

    if(test_sort(vaux,n))
    {
        cout<<"MergeSort: ";
        for (int i=0; i<n; i++)
            cout<<vaux[i]<< " ";
        auto stop1 = high_resolution_clock::now();
        auto duration1 = duration_cast<nanoseconds>(stop1 - start1);
        g<<"Timpul pentru MergeSort este: "<<duration1.count()<<" nanosecunde"<<endl;
    }
    cout<<endl;
    for(int i=0; i<n; i++)
        vaux[i]=v[i];

    auto start2 = std::chrono::high_resolution_clock::now();
    shellSort(vaux,n);

    if(test_sort(vaux,n))
    {
        cout<<"Shellsort: ";
        for (int i=0; i<n; i++)
            cout<<vaux[i]<< " ";
        auto stop2 = high_resolution_clock::now();
        auto duration2 = duration_cast<nanoseconds>(stop2 - start2);
        g<<"Timpul pentru ShellSort este: "<<duration2.count()<<" nanosecunde"<<endl;
    }
    cout<<endl;

    for(int i=0; i<n; i++)
        vaux[i]=v[i];

    auto start3 = high_resolution_clock::now();
    countSort(vaux,n);
    if(test_sort(vaux,n))
    {

        cout<<"Countsort: ";
        for (int i=0; i<n; i++)
            cout<<vaux[i]<< " ";
        auto stop3 = high_resolution_clock::now();
        auto duration3 = duration_cast<nanoseconds>(stop3 - start3);
        g<<"Timpul pentru CountSort este: "<<duration3.count()<<" nanosecunde"<<endl;
    }
    cout<<endl;

    for(int i=0; i<n; i++)
        vaux[i]=v[i];

    auto start4 = high_resolution_clock::now();
    radixSort(vaux,n);

    if(test_sort(vaux,n))
    {

        cout<<"Radixsort: ";
        for (int i=0; i<n; i++)
            cout<<vaux[i]<< " ";
        auto stop4 = high_resolution_clock::now();
        auto duration4 = duration_cast<nanoseconds>(stop4 - start4);
        g<<"Timpul pentru RadixSort este: "<<duration4.count()<<" nanosecunde"<<endl;
    }
    cout<<endl;

    for(int i=0; i<n; i++)
        vaux[i]=v[i];

    auto start5 = high_resolution_clock::now();

    quickSort(vaux,0,n-1);
    if(test_sort(vaux,n))
    {

        cout<<"Quick sort: ";
        for (int i=0; i<n; i++)
            cout<<vaux[i]<< " ";
        auto stop5 = high_resolution_clock::now();
        auto duration5 = duration_cast<nanoseconds>(stop5 - start5);
        g<<"Timpul pentru QuickSort este: "<<duration5.count()<<" nanosecunde"<<endl;
    }
    cout<<endl;

    for(int i=0; i<n; i++)
        vaux[i]=v[i];
    auto start6 = high_resolution_clock::now();

    sort(vaux,vaux+n);
    if(test_sort(vaux,n))
    {

        cout<<"Sortarea nativa: ";
        for (int i=0; i<n; i++)
            cout<<vaux[i]<< " ";
        auto stop6 = high_resolution_clock::now();
        auto duration6 = duration_cast<nanoseconds>(stop6 - start6);
        g<<"Timpul pentru Sortarea nativa este: "<<duration6.count()<<" nanosecunde"<<endl;
    }
    cout<<endl;

    }

    if(v!=NULL)
    {
        delete[] v;
        v = NULL;
    }
    if(vaux!=NULL)
    {
        delete[] vaux;
        vaux = NULL;
    }
    return 0;
}
