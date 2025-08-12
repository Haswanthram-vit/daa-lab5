#include<iostream>
#include<vector>
using namespace std;

int main()
{
    int m=4, n=10; 
    vector<vector<int>> price = 
    {
        {0,0,0,0,0,0,0,0,0,0,0},
        {0,1,5,8,9,10,17,17,20,24,30},
        {0,5,6,18,22,31,35,37,39,40,45},
        {0,8,18,22,34,37,39,42,43,45,48},
        {0,9,22,34,40,44,47,48,50,52,53}
    };

    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));

    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            dp[i][j] = price[i][j];

            for(int cut=1;cut<i;cut++)
            {
                dp[i][j] = max(dp[i][j], dp[cut][j] + dp[i-cut][j]);
            }
            for(int cut=1;cut<j;cut++)
            {
                dp[i][j] = max(dp[i][j], dp[i][cut] + dp[i][j-cut]);
            }
        }
    }

    cout<<"Maximum Revenue for "<<m<<"x"<<n<<" chocolate: "<<dp[m][n]<<endl;
}
