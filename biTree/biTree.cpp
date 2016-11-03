//二叉树相关
/*
二叉树的遍历
*/

#include <iostream>
using namespace std;

typedef struct BiTNode {
	char data;
	struct BiTNode *lchild, *rchild;
}BiTNide, *BiTree;

//------------------------------栈--------------------
typedef struct StackNode {
	BiTree data;
	struct StackNode *next;
}StackNode, *LinkStack;

//初始化链栈
void initStack(LinkStack &S)
{
	S = NULL;
}
//入栈，将元素e入栈,采用头插法，将栈顶插入到链头
int push(LinkStack &S,BiTree e)
{
	LinkStack p;
	p = new StackNode;
	if (!p)	return -1;  //开辟空间失败
	p->data = e;
	p->next = S;//将p插入到链表头
	S = p;//头结点指向p
	return 1;
}
//出栈，将栈顶元素赋给e，然后删除栈顶元素
int pop(LinkStack &S,BiTree &e)
{
	LinkStack p;
	p = S;//p指向栈顶元素
	e = p->data;//将栈顶元素的值赋给e
	S = p->next;//S头结点指向第二个结点，即新的栈顶结点
	delete p;//释放栈顶结点
	return 1;
}
//取栈顶元素
BiTree getTop(LinkStack S)
{
	if (!S) return 0;//栈空
	return S->data;
}
//判断栈是否为空
bool stackEmpty(LinkStack S)
{
	if (S)	return false;
	return true;
}
//-------------------------------栈---------------------

//先序创建二叉树
void createBiTree(BiTree &T)
{
	char ch;
	cin >> ch;
	if (ch == '#')//以'#'代表空
	{
		T = NULL;
	}
	else
	{
		T = new BiTNode;
		T->data = ch;//将ch赋到结点数据域
		createBiTree(T->lchild);//递归创建左子树
		createBiTree(T->rchild);//递归创建右子树
	}

}

//复制二叉树，将二叉树T复制给NewT
void copyTree(BiTree T, BiTree &NewT)
{
	if (T == NULL)
	{
		NewT = NULL;
	}
	else
	{
		NewT = new BiTNide;
		NewT->data = T->data;//数据域复制
		copyTree(T->lchild, NewT->lchild);//递归复制左子树
		copyTree(T->rchild, NewT->rchild);//递归复制右子树

	}
}

//先序遍历二叉树
void preOrderTraverse(BiTree T)
{
	if (T)//T不是空树
	{
		cout << T->data<<"   ";
		preOrderTraverse(T->lchild);//递归先序遍历左子树
		preOrderTraverse(T->rchild);//递归先序遍历右子树
	}
}
//中序遍历二叉树
void inOrderTraverse(BiTree T)
{
	if (T)//T不是空树
	{
		inOrderTraverse(T->lchild);//递归中序遍历左子树
		cout << T->data << "   ";
		inOrderTraverse(T->rchild);//递归中序遍历右子树
	}
}

//后序遍历二叉树
void postOrderTraverse(BiTree T)
{
	if (T)//T不是空树
	{
		postOrderTraverse(T->lchild);//递归后序遍历左子树
		postOrderTraverse(T->rchild);//递归后序遍历右子树
		cout << T->data << "   ";
	}
}

//非递归先序遍历二叉树
void feiDiGuiPreOrderTraverse(BiTree T)
{
	LinkStack S;
	initStack(S);
	BiTree p = T,q;
	q = new BiTNode;
	while (p || !stackEmpty(S))
	{
		if (p)//p非空
		{
			cout << p->data << "   ";
			push(S, p);
			p = p->lchild;
		}
		else
		{
			pop(S, p);
			p = p->rchild;
		}

	}
}

//非递归中序遍历二叉树
void feiDiGuiInOrderTraverse(BiTree T)
{
	LinkStack S;
	initStack(S);
	BiTree q;
	q = new BiTNode;
	BiTree p = T;
	while (p || !stackEmpty(S))
	{
		if (p)//p不空
		{
			push(S, p);//p入栈
			p = p->lchild;
		}
		else
		{
			pop(S, q);
			cout << q->data << "   ";
			p = q->rchild;
		}
	}
}
//非递归后序遍历二叉树

void feiDiGuiPostOrderTraverse(BiTree T)
{
	LinkStack S;
	initStack(S);
	BiTree p = T,q;
	q = NULL;
	while (p || !stackEmpty(S))
	{
		if (p)
		{
			push(S,p);
			p = p->lchild;
		}
		else
		{
			p = getTop(S);
			if (q != p->rchild)
			{
				p = p->rchild;
				q = p;
			}
			else
			{
				pop(S, p);
				cout << p->data << "   ";
				pop(S, p);
				cout << p->data << "   ";
				p = p->rchild;
			}
		}


		/*
		if (p)//p非空
		{
			push(S, p);
			p = p->lchild;
		}
		else
		{//p空
			p = getTop(S);
			if (p != q)
			{
				q = p;
				p = p->rchild;
			}
			else
			{
				cout << p->data << "   ";
				pop(S, p);
				p = getTop(S);
				p = p->rchild;
			}
		}*/
	}

}


//计算二叉树的深度
int depth(BiTree T)
{
	if (!T)
	{
		return 0;
	}
	else
	{
		int m = depth(T->lchild);
		int n = depth(T->rchild);
		return (m > n ? m : n) + 1;
	}
}
//统计二叉树的结点的个数
int nodeCount(BiTree T)
{
	if (!T)
		return 0;
	else
		return nodeCount(T->lchild) + nodeCount(T->rchild) + 1;
}

//统计二叉树中度为1的结点的个数
int duYiNodeCount(BiTree T)
{
	if (T)
	{
		int n = 0;
		if ( (T->lchild && !T->rchild) || (!T->lchild && T->rchild) )
		{
			n = 1;
		}
		return duYiNodeCount(T->lchild) + duYiNodeCount(T->rchild) + n;
	}
	return 0;
}

//统计二叉树中度为1的结点的个数
int duErNodeCount(BiTree T)
{
	if (T)
	{
		int n = 0;
		if (T->lchild && T->rchild)
		{
			n = 1;
		}
		return duErNodeCount(T->lchild) + duErNodeCount(T->rchild) + n;
	}
	return 0;
}

//统计二叉树的叶结点的个数
int leafNodeCount(BiTree T)
{
	if (T)
	{
		if (!T->lchild && !T->rchild)
			return 1;
		return leafNodeCount(T->lchild) + leafNodeCount(T->rchild);
	}
	return 0;
}

//交换二叉树每个结点的左孩子和右孩子
void swapChild(BiTree &T)
{
	if (T)
	{
		swapChild(T->lchild);//交换左子树
		swapChild(T->rchild);//交换右子树
		//交换左右孩子
		BiTree p;
		p = T->lchild;
		T->lchild = T->rchild;
		T->rchild = p;
	}
}


void main()
{
	BiTree T;
	createBiTree(T);
	cout << "先序遍历：  ";
	preOrderTraverse(T);
	cout <<endl<< "中序遍历：  ";
	inOrderTraverse(T);
	cout <<endl<< "后序遍历：  ";
	postOrderTraverse(T);
	BiTree newT;
	copyTree(T, newT);
	cout <<endl<< "T的复制二叉树的中序遍历:  ";
	inOrderTraverse(newT);
	cout << "结点个数：" << nodeCount(T)<<endl;
	cout << "度为1的结点个数：" << duYiNodeCount(T) << endl;
	cout << "度为2的结点个数：" << duErNodeCount(T) << endl;
	cout << "叶结点个数：" << leafNodeCount(T) << endl;
	cout << "交换左右孩子后：" << endl;
	swapChild(T);
	cout << "先序遍历：  ";
	preOrderTraverse(T);
	cout << endl << "中序遍历：  ";
	inOrderTraverse(T);
	cout << endl << "后序遍历：  ";
	postOrderTraverse(T);
	copyTree(T, newT);
	cout << endl << "T的复制二叉树的中序遍历:  ";
	inOrderTraverse(newT);
	cout << "结点个数：" << nodeCount(T) << endl;
	cout << "度为1的结点个数：" << duYiNodeCount(T) << endl;
	cout << "度为2的结点个数：" << duErNodeCount(T) << endl;
	cout << "叶结点个数：" << leafNodeCount(T) << endl;
}