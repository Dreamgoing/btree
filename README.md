# B-tree

## 简介

+ 平衡二叉树：最坏情况复杂度，height ＝ O(log(n)) 
+ 被设计为可以直接访问辅助存储设备的数据结构
+ 和红黑树类似，但是对于在磁盘硬盘的读取I/O操作上面表现的好
+ B树，还有类似的B+树，B*树被广泛的运用于数据库系统中

## 动机

计算机的存储空间广义上说由两部分构成：

+ 主存（primary memory）:使用RAM
+ 辅存（secondary storage）:通常为磁盘

为了尽可能多的高效率的在硬盘上面读取数据，B-树因此诞生。

## 定义&性质

### 定义

B-tree T是一个有根树,其根节点为root[T]

对于B-tree 的每一个节点node x，包含了如下4条内容：

+ n[x],x节点存储了当前有多少个索引(key)。
+ 对于当前节点的所有索引key值(n[x]),都按非递减序存储。
+ bool变量：leaf，标识了当前节点是叶节点还是中间节点
+ n[x]+1个指针，指向当前节点的子节点
+ B树的阶为（每个节点包含的最多的儿子数）：即最多包含子节点的个数
+ B树的阶数为m，则根节点中的关键字个数为1~m-1,非根结点的关键字个数为[m/2]-1~m-1

### 性质
x为当前节点的标志符

+ 存储在当前节点中的key[x][i]，在其子树中分割了不同的范围：

```
k1<=key[x][1]<=k2<=key[x][2]<=...key[x][n]<=kn+1
```

+ 所有的叶节点都拥有相同的高度，即树高
+ 一个节点包含的key(索引值)有上界和下界，因此使用度来标记衡量B-tree的上界和下界
	- 下界：每一个节点（除了根节点）至少包含t－1个key（索引），即至少有t个子节点
	- 上界：每一个节点最多包含2t－1个key（索引），即每个节点最多有2t个子节点


## B-tree的基本操作

### 查找(search)

``` c++

template <class T>
pair<BtreeNode<T>*, T> Btree<T>::BtreeSearch(BtreeNode<T> *now, const T &k) {
    if(now== nullptr){
        ///not found
        return make_pair(nullptr,-1);
    }
    ///can use b_search
    int pos = 0;
    while (pos<now->children.size()&&k>now->children[pos].first){
        pos++;
    }
    if(pos<now->children.size()&&k==now->children[pos].first){
        ///found
        return now->children[pos];
    }

    if(now->leaf){
        ///not found
        return make_pair(nullptr,-1);
    } else{
        ///first Disk-read(now->children[pos])
        return BtreeSearch(now->children[pos],k);
    }


}
```

### 插入(insert)

+ 在B树上插入一个节点，要比在二叉树上面插入节点要复杂
+ 在插入的过程中会进行分割这一基础操作即，把一个满的节点即包含（2t－1）个索引的节点在插入时期，分成两个节点
+ 从中间元素分开分成两部分，中间元素向上传递到父节点
+ 如果是进行分割的节点为根节点，则使得树的高度加1

## Reference
[b-tree](http://www.di.ufpb.br/lucidio/Btrees.pdf)


