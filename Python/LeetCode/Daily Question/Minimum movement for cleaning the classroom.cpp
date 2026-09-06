#include <cstring>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
using namespace std;

class Solution
{
public:
    int minMoves(vector<string> &classroom, int energy)
    {
        int m = classroom.size();
        int n = classroom[0].size();
        int dx[4] = {0, 0, 1, -1};
        int dy[4] = {1, -1, 0, 0};

        int start_x = -1;
        int start_y = -1;
        vector<vector<int>> litter_id(m, vector<int>(n, -1));
        vector<pair<int, int>> litter;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (classroom[i][j] == 'S')
                {
                    start_x = i;
                    start_y = j;
                }
                if (classroom[i][j] == 'L')
                {
                    litter_id[i][j] = litter.size();
                    litter.push_back({i, j});
                }
            }
        }
        int k = litter.size();
        if (k == 0)
            return 0;

        int tagertMask = (1 << k) - 1;

        // x,y,energy,mask
        static bool v[20][20][51][1024];
        memset(v, 0, sizeof(v));
        // x,y,energy,mask,step
        queue<tuple<int, int, int, int, int>> q;
        q.push({start_x, start_y, energy, 0, 0});

        while (!q.empty())
        {
            auto [x, y, e, mask, step] = q.front();
            q.pop();
            if (mask == tagertMask)
                return step;
            if (e == 0)
                continue;
            for (int i = 0; i < 4; i++)
            {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx < 0 || nx >= m || ny < 0 || ny >= n)
                    continue;
                char c = classroom[nx][ny];
                if (c == 'X')
                    continue;
                int ne = e - 1;
                if(c == 'R')
                    ne = energy;
                int nMask = mask;
                if(c=='L')
                {
                    int id = litter_id[nx][ny];
                    nMask |= (1 << id);
                }
                if(!v[nx][ny][ne][nMask])
                {
                    v[nx][ny][ne][nMask] = true;
                    q.push({nx, ny, ne, nMask, step + 1});
                }
            }
            
        }
        return -1;
    }
};