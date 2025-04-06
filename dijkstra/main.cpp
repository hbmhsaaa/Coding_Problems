#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;
//自己定义比较的类
struct Compare {
public:
    bool operator()(const pair<int, pair<int, int>>& a, const pair<int, pair<int, int>>& b) {
        return a.first > b.first;
    }
};

int transfer[4][2]={{1,0},{-1,0},{0,1},{0,-1}};

// 待实现函数：计算从 (sx, sy) 到 (tx, ty) 的最小路径总代价
int minCostPath(const vector<vector<int>>& grid, int sx, int sy, int tx, int ty) {
    //建立访问数组
    vector<vector<bool>> visited(grid.size(),vector<bool>(grid[0].size(), false));
    vector<vector<int>> minDist(grid.size(),vector<int>(grid[0].size(),INT_MAX));
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, Compare> que;
    minDist[sx][sy]=grid[sx][sy];
    que.push({minDist[sx][sy], {sx,sy}});


    while (!que.empty()){
        auto [curDist,cur] = que.top();que.pop();
        int curX = cur.first;
        int curY = cur.second;
        if(curX==tx&&curY==ty){
            return curDist;
        }
        if(visited[curX][curY]){
            continue;
        }
        visited[curX][curY]= true;
        for(int i=0;i<4;i++){
            int nextX = curX+transfer[i][0];
            int nextY = curY+transfer[i][1];
            if(nextX>=grid.size()||nextX<0||nextY>=grid[0].size()||nextY<0||visited[nextX][nextY])
                continue;
            int newDist = curDist+grid[nextX][nextY];
            if(newDist<minDist[nextX][nextY]){
                minDist[nextX][nextY] = newDist;
                que.push({newDist,{nextX,nextY}});
            }
        }
    }

    return -1; // 占位返回值
}

int main() {
    int m, n;
    cin >> m >> n;

    vector<vector<int>> grid(m, vector<int>(n));
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            cin >> grid[i][j];

    int sx, sy, tx, ty;
    cin >> sx >> sy >> tx >> ty;

    int result = minCostPath(grid, sx, sy, tx, ty);
    cout << result << endl;

    return 0;
}
/*
1 2 3
4 5 6

 */
在现有Dijsktra算法的基础上实现A*算法

