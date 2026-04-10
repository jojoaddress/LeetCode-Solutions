from typing import List

class Node:
    __slots__ = 'son','end'
    def __init__(self):
        self.son = {}
        self.end = False
        

class Solution:
    def __init__(self):
        self.root = Node()

    def dfs(self, node: Node, path: list, result: list):
        if node.end:
            result.append("".join(path))  # 找到一个完整单词

        for ch, child in node.son.items():
            ch = '/' + ch  # 添加路径分隔符
            path.append(ch)  # 添加当前字符到路径
            self.dfs(child, path, result)  # 递归子节点
            path.pop()  # 回溯

    def removeSubfolders(self, folder: List[str]) -> List[str]:
        self.root = Node() 
        res = []
        folderList = [path.split('/')[1:] for path in folder]
        folderList.sort(key=lambda x: len(x))
        for fold in folderList:
            cur = self.root
            for c in fold:
                if c not in cur.son:
                    cur.son[c] = Node()
                cur = cur.son[c]
                if cur.end == True:
                    break
            cur.end = True
        
        cur = self.root
        path = []
        self.dfs(cur,path,res)
        
        return res
    
    def removeSubfolders2(self, folder: List[str]) -> List[str]:
        folder.sort()
        res = [folder[0]]
        for fold in folder[1:]:
            last = res[-1]
            # 如果当前文件夹 fold 不以 last 为前缀，则肯定不是子文件夹
            # 或者，如果以 last 为前缀，但紧接着 last 后面的字符不是 '/', 也不是子文件夹
            if not fold.startswith(last) or fold[len(last)] != '/':
                res.append(fold)
        return res

    
if __name__ == "__main__":
    s = Solution()
    #print(s.removeSubfolders(["/a","/a/b","/c/d","/c/d/e","/c/f"]))  # 输出 ["/a","/c/d","/c/f"]
    #print(s.removeSubfolders(["/a","/a/b/c","/a/b/d"]))  # 输出 ["/a"]
    print(s.removeSubfolders2(["/ah/al/am","/ah/al"]))  # 输出 ["/ah/al/am","/ah/al"]
        
        
                

