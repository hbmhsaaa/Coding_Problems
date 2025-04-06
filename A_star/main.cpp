#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include<math.h>

using namespace std;
//自己定义比较的类
class Compare{
public:
    bool operator()(const pair<int,pair<int,int>> &x,const pair<int,pair<int,int>> &y){
        return x.first>y.first;
    }
};

int transfer[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
//A*算法
//曼哈顿距离，启发式函数
int manDis(int x1,int y1,int x2,int y2){
    return abs(x1-x2)+ abs(y1-y2);
}

// 待实现函数：计算从 (sx, sy) 到 (tx, ty) 的最小路径总代价
int minCostPath(const vector<vector<int>>& grid, int sx, int sy, int tx, int ty) {
    //建立访问数组
    //g_x
    vector<vector<int>> g_x(grid.size(),vector<int>(grid[0].size(),INT_MAX));
    //判断该点是否访问过
    vector<vector<bool>> visited(grid.size(),vector<bool>(grid[0].size(), false));
    //定义优先级队列
    priority_queue<pair<int,pair<int,int>>,vector<pair<int,pair<int,int>>>,Compare> que;
    //定义起点的g_x
    g_x[sx][sy]=grid[sx][sy];
    //push进优先级队列
    int f_x = g_x[sx][sy]+ manDis(sx,sy,sx,sy);
    que.push({f_x,{sx, sy}});
    while (!que.empty()){
        //取队列里的点
        auto [curDis,cur]=que.top();que.pop();
        int curX = cur.first;
        int curY = cur.second;
        if(curX==tx&&curY==ty){
            return g_x[curX][curY];
        }
        if(visited[curX][curY])
            continue;
        visited[curX][curY]= true;
        for(int i=0;i<4;i++){
            int nextX = curX+ transfer[i][0];
            int nextY = curY+transfer[i][1];
            if(nextX<0||nextX>=grid.size()||nextY<0||nextY>=grid[0].size()||visited[nextX][nextY])
                continue;
            int g_new = g_x[curX][curY]+grid[nextX][nextY];
            if(g_new<g_x[nextX][nextY]){
                g_x[nextX][nextY]=g_new;
                f_x = manDis(tx,ty,nextX,nextY)+g_new;
                que.push({f_x,{nextX,nextY}});

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