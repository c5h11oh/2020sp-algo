#include <iostream>
using namespace std;
const int INF = 1e8;

int main()
{
    int N, M, ui, vi, wi;
    cin >> N >> M;
    int fw[2][N][N];
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            fw[0][i][j] = INF;
    for (int i = 0; i < M; ++i)
    {
        cin >> ui >> vi >> wi;
        if (fw[0][ui - 1][vi - 1] > wi)
            fw[0][ui - 1][vi - 1] = wi;
        //-1因為題目節點是從1開始，實作陣列是從0開始
    }
    int result = INF;
    for (int i = 0; i < N; ++i)
    {
        if (fw[0][i][i] < result)
            result = fw[0][i][i];
        fw[0][i][i] = 0;
    }
    for (int k = 1; k < N + 1; ++k)
    {
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                fw[k % 2][i][j] = min(fw[(k % 2 ? 0 : 1)][i][j], fw[(k % 2 ? 0 : 1)][i][k - 1] + fw[(k % 2 ? 0 : 1)][k - 1][j]);
            }
        }
    }

    for (int i = 0; i < N; ++i)
    {
        for (int j = i + 1; j < N; ++j)
        {
            result = min(result, fw[(N % 2)][i][j] + fw[(N % 2)][j][i]);
        }
    }
    if (result < INF)
        cout << result;
    else
        cout << -1;

    return 0;
}