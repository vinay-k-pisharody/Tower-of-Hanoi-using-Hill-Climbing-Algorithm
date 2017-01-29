#include<conio.h>
#include<iostream>
#include<stack>
#include<math.h>

using namespace std;

int index;
stack<int> ** calmoves(stack<int> peg[],int count)
{
    stack<int> ** solutions = 0;
    stack<int> ogpeg[count];
    for(int i=0;i<count;i++)
    {
        ogpeg[i]=peg[i];
    }
    solutions = new stack<int>*[10];
    index=0;
    for(int i=0;i<count;i++)
    {
        for(int j=0;j<count;j++)
        {
            if(i!=j)
            {
                if(!peg[i].empty())
                {
                    int temp=peg[i].top();
                    if(peg[j].empty())
                    {
                        peg[j].push(temp);
                        peg[i].pop();
                        solutions[index]=new stack<int>[count];
                        for(int m=0;m<count;m++)
                        {
                            solutions[index][m]=peg[m];
                            peg[m]=ogpeg[m];
                        }
                        index++;
                    }
                    else
                    {
                        if(peg[i].top()<peg[j].top())
                        {
                            peg[j].push(temp);
                            peg[i].pop();
                            solutions[index]=new stack<int>[count];
                            for(int m=0;m<count;m++)
                            {
                                solutions[index][m]=peg[m];
                                peg[m]=ogpeg[m];
                            }
                            index++;
                        }
                    }
                }
            }

        }
    }
    return solutions;
}

int main()
{
    int r,p;
    cout<<"\nEnter number of rings : ";
    cin>>r;
    cout<<"\nEnter number of pegs : ";
    cin>>p;

    stack<int> **pointer;
    stack<int> peg[p];
    for(int i=r;i>0;i--)
    {
        peg[0].push(i);
    }
    int prev=0,pp=0;
    repeat:
    stack<int> solution[10][p];
    stack<int> temp[p];
    cout<<"\n\n";
    for(int i=0;i<p;i++)
    {
        temp[i]=peg[i];
        while(!temp[i].empty())
        {
            int temp1=temp[i].top();
            cout<<temp1<<" ";
            temp[i].pop();
        }
        cout<<"\n";
    }
    getch();
    pointer=calmoves(peg,p);
    for(int j=0;j<index;j++)
    {
        for(int i=0;i<p;i++)
        {
            solution[j][i]=pointer[j][i];
        }
    }

    for(int j=0;j<index;j++)
    {
        cout<<"\nIndex : "<<j<<endl;
        for(int i=0;i<p;i++)
        {
            while(!pointer[j][i].empty())
            {
                cout<<pointer[j][i].top()<<" ";
                pointer[j][i].pop();
            }
            cout<<"\n";
        }
        cout<<endl;
    }
    int h[index];
    float resl;
    for(int j=0;j<index;j++)
    {
        resl=0;
        for(int i=0;i<p;i++)
        {
            int temp=solution[j][i].size();
            temp=p-temp;
            int temp1=pow(10,(p-1-i));
            resl=resl+temp*pow(10,(p-1-i));
        }
        h[j]=resl;
    }
    int max=0;
    int mindex;
    for(int i=0;i<index;i++)
    {
        if(h[i]>max&&h[i]!=pp)
        {
            max=h[i];
            mindex=i;
        }
    }
    if(max==330)
    {
        goto skip;
    }
    else
    {
        for(int i=0;i<p;i++)
        {
            peg[i]=solution[mindex][i];
        }
        pp=prev;
        prev=max;
        goto repeat;
    }

skip:
    cout<<"\n";
    for(int i=0;i<p;i++)
    {
        peg[i]=solution[mindex][i];
        while(!peg[i].empty())
        {
            int temp=peg[i].top();
            cout<<temp<<" ";
            peg[i].pop();
        }
        cout<<"\n";
    }
    return 0;
}
