在这里放一下整个Dictionary_pure的实现逻辑

Node用来定义BST里的一个节点，里面存放了key, value, 和指向两个子节点的shared_ptr left和right，以及对应的constructor
字典所有的内容都存在Node里，Dictionary是拿着访问这些Node的指针

Dictionary自己存的成员是root，表示树的根节点
此外还有一个explicit constructor

Dictionary需要实现的功能是：
- constructor（包括创建空树和复制已有的树），
- 查找是否包含某个key（返回bool），
- 查找某个key的具体value（返回int），
- 向BST添加节点（返回新的Dictionary）

BST：左边的子节点都小于自己，右边的子节点都大于自己
按照这个逻辑进行contains和lookup查找

由于这是一个pure functional BST，因此不可以直接改动已有的节点，但是由于shared_ptr的特性，我们可以让多个数共用同一个节点
因此add的逻辑是，在找到插入的位置的同时，把经过的节点都复制一份，没经过的可以复用
因为recursive的逻辑好写一些，所以这里用到了一个add_node作为add的helper
此外这个add还能顺手完成update的功能