---
tags: Algorithms
---

# Algorithms HW5 Handwritten
#### 2020 Spring | 90899201Y tony20715 黃悟淳

### 1. Turnip Delivery
1. 4 Edges.
2. 圖
    ![](https://i.imgur.com/kgHGmUC.jpg)
3. 設所有邊的集合為 $E$，前述最大生成樹的邊的集合為 $E'$，設所有沒被選到的邊的集合為 $F=E-E'$。根據生成樹定義，$E'$ 必定連結所有節點，任兩節點必有唯一一條路徑 (path)，而根據 Kruskal's Algorithm，可知集合 $F$ 中的所有邊的權 (weight) 必定小於或等於集合 $E'$ 中任一邊的權。由上述可推得，若要找到另一條兩節點間的路徑，則一定要在 $F$ 中找至少一條邊來走，但 $F$ 中的邊的權必定小於或等於最大生成樹的唯一路徑中最小權的邊，使得飛機能載的重量必定小於或等於原本都走在 $E'$ 的邊的路徑，得證經過最大生成樹的路徑必為最佳解之一。

### 2. Lexicographical order AGAIN!
1. 
    - 從 $zyx<yzx<wwww$，我們得到 $z<y<w$ ；從 $yzx<yxv$，得到 $z<x$；從 $yzx<yzy$，得到 $x<y$；從 $wwww<wwvx$，得到 $w<v$。
    - 整理上述結果：
        - $z<y<w$
        - $z<x$
        - $x<y$
        - $w<v$
    - 得到： $z<x<y<w<v$ 。
2. 步驟如下
    1. Left align these strings, sorting by ascending order.
        ```=1
        zyx
        yzx
        yzy
        yxv
        wwwww
        wwvxy
        ```
    2. 從第1欄： 
        ![](https://i.imgur.com/qEiceP7.png)
    3. 從第2欄： 
        ![](https://i.imgur.com/oD6rlbR.png)
    4. 從第3欄：
        ![](https://i.imgur.com/anIeuAN.png)
    5. 從第4欄、第5欄無法獲取更多資訊
    6. Combine all the graphs (relationships): 
        ![](https://i.imgur.com/ZRBcDrY.png)
    7. Perform topological sort to the above graph:
        ![](https://i.imgur.com/QKdQWVP.jpg)
    8. 故解答為 $z<x<y<w<v$。

### 3. Strongly Connected Components

// SCC 也是自充填混凝土喔，有良好的變形性，不須振動搗實就可以在組好的模板裡自由流動，確保完整填滿所有縫隙包裹鋼筋，就可以做出像臺中歌劇院、臺北陶朱隱園那樣自由曲面的牆或樓版喔～～
// ![](https://picsig.playplus.solutions/uploads/photo/file/271/86d5038c-999a-4414-9d14-0a058cbd88de.jpeg) ![](https://picsig.playplus.solutions/uploads/image/file/3803/something.jpg)
// 好了，廢話完畢

1. 圖
    ![](https://i.imgur.com/rACNs4W.jpg)
2. 
    After transposing a graph $G$ resulting in $G^T$, the amount of SCCs in graph $G$ is equivalent to which in graph $G^T$, and the components of each SCC remain the same after the transpose operation, since transposing a graph simply inverts the direction of the edges that strongly connect those components, and those vertices (components) are still strongly connected but in another direction. Also, the vertices that were not able to form a "loop" (thus resulting SCCs) still cannot either form a "loop" or join existing loops by exploiting the inverted edges. 
    
    Since SCCs remain the same before and after the transpose operation, we can view $(G^T)^{SCC}$ as a graph with SCCs shrunk ($G^{SCC}$), and all edges that do not form SCC inverted, which is namely, $(G^{SCC})^T$: shrink all the SCCs first and invert the remaining edges (transpose the graph).