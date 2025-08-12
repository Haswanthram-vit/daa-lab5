#include<iostream>
#include<vector>
using namespace std;

int rodCutRecursiveCost(vector<int>&price,int n,int cost)
{
    if(n==0)
    {
        return 0;
    }
    int maxRevenue=price[n-1];
    for(int i=1;i<n;i++)
    {
        int revenue=price[i-1]+rodCutRecursiveCost(price,n-i,cost)-cost;
        if(revenue>maxRevenue)
        {
            maxRevenue=revenue;
        }
    }
    return maxRevenue;
}

int rodCutMemoHelperCost(vector<int>&price,int n,vector<int>&memo,int cost)
{
    if(n==0)
    {
        return 0;
    }
    if(memo[n]!=-1)
    {
        return memo[n];
    }
    int maxRevenue=price[n-1];
    for(int i=1;i<n;i++)
    {
        int revenue=price[i-1]+rodCutMemoHelperCost(price,n-i,memo,cost)-cost;
        if(revenue>maxRevenue)
        {
            maxRevenue=revenue;
        }
    }
    memo[n]=maxRevenue;
    return maxRevenue;
}

int rodCutMemoizedCost(vector<int>&price,int n,int cost)
{
    vector<int>memo(n+1,-1);
    return rodCutMemoHelperCost(price,n,memo,cost);
}

void rodCutBottomUpCost(vector<int>&price,int n,int cost,int &maxRevenue,vector<int> &cutPieces)
{
    vector<int>dp(n+1,0);
    vector<int>cuts(n+1,0);
    for(int j=1;j<=n;j++)
    {
        int best=price[j-1];
        int bestCut=j;
        for(int i=1;i<j;i++)
        {
            int revenue=price[i-1]+dp[j-i]-cost;
            if(revenue>best)
            {
                best=revenue;
                bestCut=i;
            }
        }
        dp[j]=best;
        cuts[j]=bestCut;
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
    int rodLength,cost;
    cout<<"\nEnter rod length:\n";
    cin>>rodLength;
    cout<<"\nEnter cutting cost:\n";
    cin>>cost;

    cout<<"\nOutput:"<<endl;
    cout<<"Recursive Approach Revenue: "<<rodCutRecursiveCost(price,rodLength,cost)<<endl;
    cout<<"Memoized Approach Revenue: "<<rodCutMemoizedCost(price,rodLength,cost)<<endl;

    int bottomUpRevenue;
    vector<int>cutPieces;
    rodCutBottomUpCost(price,rodLength,cost,bottomUpRevenue,cutPieces);

    cout<<"Bottom-Up Approach Revenue: "<<bottomUpRevenue<<endl;
    for(int cut:cutPieces)
    {
        cout<<cut<<" ";
    }
    cout<<endl;
}
