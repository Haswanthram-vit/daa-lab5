#include<iostream>
#include<vector>
#include<climits>
using namespace std;

int rodCutRecursive(const vector<int>&price,int n)
{
    if(n==0) return 0;
    int maxVal=INT_MIN;
    for(int i=1;i<=n;i++)
        maxVal=max(maxVal,price[i]+rodCutRecursive(price,n-i));
    return maxVal;
}

int rodCutMemoUtil(const vector<int>&price,int n,vector<int>&memo)
{
    if(memo[n]>=0) return memo[n];
    int maxVal;
    if(n==0) maxVal=0;
    else
    {
        maxVal=INT_MIN;
        for(int i=1;i<=n;i++)
            maxVal=max(maxVal,price[i]+rodCutMemoUtil(price,n-i,memo));
    }
    memo[n]=maxVal;
    return maxVal;
}

int rodCutMemo(const vector<int>&price,int n)
{
    vector<int>memo(n+1,-1);
    return rodCutMemoUtil(price,n,memo);
}

void rodCutBottomUp(const vector<int>&price,int n,int &maxRevenue,vector<int>&cuts)
{
    vector<int>dp(n+1,0);
    vector<int>cutPos(n+1,0);
    for(int len=1;len<=n;len++)
    {
        int best=price[len];
        int bestCut=len;
        for(int i=1;i<len;i++)
        {
            if(price[i]+dp[len-i]>best)
            {
                best=price[i]+dp[len-i];
                bestCut=i;
            }
        }
        dp[len]=best;
        cutPos[len]=bestCut;
    }
    maxRevenue=dp[n];
    int length=n;
    while(length>0)
    {
        cuts.push_back(cutPos[length]);
        length-=cutPos[length];
    }
}

int main()
{
    int n;
    cout<<"Enter maximum rod length: ";
    cin>>n;
    vector<int>price(n+1);
    cout<<"Enter prices for lengths 1 to "<<n<<":\n";
    for(int i=1;i<=n;i++)
        cin>>price[i];

    int m;
    cout<<"Enter number of rods: ";
    cin>>m;
    vector<int>rods(m);
    cout<<"Enter lengths of rods:\n";
    for(int i=0;i<m;i++)
        cin>>rods[i];

    int totalRevenueRecursive=0,totalRevenueMemo=0,totalRevenueBottomUp=0;

    for(int r=0;r<m;r++)
    {
        int len=rods[r];
        cout<<"\nRod "<<r+1<<" ("<<len<<" inches):\n";

        int revRec=rodCutRecursive(price,len);
        totalRevenueRecursive+=revRec;
        cout<<"  Recursive: Max Revenue = "<<revRec<<"\n";

        int revMemo=rodCutMemo(price,len);
        totalRevenueMemo+=revMemo;
        cout<<"  Memoized: Max Revenue = "<<revMemo<<"\n";

        int revBottom;
        vector<int>cuts;
        rodCutBottomUp(price,len,revBottom,cuts);
        totalRevenueBottomUp+=revBottom;
        cout<<"  Bottom-Up: Max Revenue = "<<revBottom<<", Cuts = [";
        for(int i=0;i<cuts.size();i++)
        {
            cout<<cuts[i];
            if(i+1<cuts.size()) cout<<", ";
        }
        cout<<"]\n";
    }

    cout<<"\nTotal Maximum Revenue (Recursive) = "<<totalRevenueRecursive<<"\n";
    cout<<"Total Maximum Revenue (Memoized) = "<<totalRevenueMemo<<"\n";
    cout<<"Total Maximum Revenue (Bottom-Up) = "<<totalRevenueBottomUp<<"\n";
}
