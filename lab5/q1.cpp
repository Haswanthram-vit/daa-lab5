#include<iostream>
#include<vector>
using namespace std;

int rodCutRecursive(vector<int>&price,int n)
{
    if(n==0)
    {
        return 0;
    }
    int maxRevenue=-10000;
    for(int i=1;i<=n;i++)
    {
        maxRevenue=max(maxRevenue,price[i-1]+rodCutRecursive(price,n-i));
    }
    return maxRevenue;
}

int rodCutMemoHelper(vector<int>&price,int n,vector<int>&memo)
{
    if(n==0)
    {
        return 0;
    }
    if(memo[n]!=-1)
    {
        return memo[n];
    }
    int maxRevenue=-10000;
    for(int i=1;i<=n;i++)
    {
        maxRevenue=max(maxRevenue,price[i-1]+rodCutMemoHelper(price,n-i,memo));
    }
    memo[n]=maxRevenue;
    return maxRevenue;
}

int rodCutMemoized(vector<int>&price,int n)
{
    vector<int>memo(n+1,-1);
    return rodCutMemoHelper(price,n,memo);
}

void rodCutBottomUp(vector<int>&price,int n,int &maxRevenue,vector<int> &cutPieces)
{
    vector<int>dp(n+1,0);
    vector<int>cuts(n+1,0);
    for(int j=1;j<=n;j++)
    {
        int best=-10000;
        for(int i=1;i<=j;i++)
        {
            if(price[i-1]+dp[j-i]>best)
            {
                best=price[i-1]+dp[j-i];
                cuts[j]=i;
            }
        }
        dp[j]=best;
    }
    maxRevenue=dp[n];
    int length=n;
    while(length>0)
    {
        cutPieces.push_back(cuts[length]);
        length-=cuts[length];
    }
}

int main()
{
    int n;
    cout<<"Enter length values:\n";
    cin>>n;
    vector<int>price(n);
    cout<<"\nEnter price values:\n";
    for(int i=0;i<n;i++)
    {
        cin>>price[i];
    }
    int rodLength;
    cout<<"\nEnter rod length:\n";
    cin>>rodLength;
    cout<<"\nOutput:"<<endl;

    cout<<"Recursive (Top-Down) Result: "<<rodCutRecursive(price,rodLength)<<endl;
    cout<<"Memoized (Top-Down with DP) Result: "<<rodCutMemoized(price,rodLength)<<endl;

    int bottomUpRevenue;
    vector<int>cutPieces;
    rodCutBottomUp(price,rodLength,bottomUpRevenue,cutPieces);

    cout<<"Bottom-Up DP Result: "<<bottomUpRevenue<<endl;
    for(int cut:cutPieces)
    {
        cout<<cut<<" ";
    }
    cout<<endl;
}
