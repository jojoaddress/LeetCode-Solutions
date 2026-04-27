from typing import List
from typing import Optional
from collections import defaultdict

class Solution:
    def hasValidPath(self, grid: List[List[int]]) -> bool:
        m,n=len(grid),len(grid[0])
        vis = [[False]*n for _ in range(m)]
        # 0=上(00)，1=右(01)，2=下(10)，3=左(11)
        streets = [None,
                   (1,3),   # 1: 左右
                   (0,2),   # 2: 上下
                   (1,2),   # 3: 右下
                   (2,3),   # 4: 左下
                   (0,1),   # 5: 右上
                   (0,3)]   # 6: 左上
        dxy = [(-1,0), (0,1), (1,0), (0,-1)]
        def dfs(x:int,y:int,preArrow:int)->bool:
            if x>=m or x<0 or y>=n or y<0 or vis[x][y]:
                return False
            if x==m-1 and y==n-1:
                return True
            vis[x][y] = True
            street = streets[grid[x][y]]
            if preArrow == -1:
                for out in street:
                    dx,dy = dxy[out]
                    if(dfs(x+dx, y+dy,(out+2)%4)):
                        return True
            else:
                outArrow = (preArrow+2)%4
                if outArrow not in street:
                    vis[x][y] = False
                    return False
                out = street[0] if street[0]!=outArrow else street[1]
                dx,dy = dxy[out]
                if(dfs(x+dx, y+dy, (out+2)%4)):
                    return True
            vis[x][y] = False
            return False
        return dfs(0,0,-1)

if __name__ == "__main__":
    s = Solution()
    print(s.hasValidPath([[2,4,3],[6,5,2]]))


            





