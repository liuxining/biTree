//���������
/*
�������ı���
*/

#include <iostream>
using namespace std;

typedef struct BiTNode {
	char data;
	struct BiTNode *lchild, *rchild;
}BiTNide, *BiTree;

//------------------------------ջ--------------------
typedef struct StackNode {
	BiTree data;
	struct StackNode *next;
}StackNode, *LinkStack;

//��ʼ����ջ
void initStack(LinkStack &S)
{
	S = NULL;
}
//��ջ����Ԫ��e��ջ,����ͷ�巨����ջ�����뵽��ͷ
int push(LinkStack &S,BiTree e)
{
	LinkStack p;
	p = new StackNode;
	if (!p)	return -1;  //���ٿռ�ʧ��
	p->data = e;
	p->next = S;//��p���뵽����ͷ
	S = p;//ͷ���ָ��p
	return 1;
}
//��ջ����ջ��Ԫ�ظ���e��Ȼ��ɾ��ջ��Ԫ��
int pop(LinkStack &S,BiTree &e)
{
	LinkStack p;
	p = S;//pָ��ջ��Ԫ��
	e = p->data;//��ջ��Ԫ�ص�ֵ����e
	S = p->next;//Sͷ���ָ��ڶ�����㣬���µ�ջ�����
	delete p;//�ͷ�ջ�����
	return 1;
}
//ȡջ��Ԫ��
BiTree getTop(LinkStack S)
{
	if (!S) return 0;//ջ��
	return S->data;
}
//�ж�ջ�Ƿ�Ϊ��
bool stackEmpty(LinkStack S)
{
	if (S)	return false;
	return true;
}
//-------------------------------ջ---------------------

//���򴴽�������
void createBiTree(BiTree &T)
{
	char ch;
	cin >> ch;
	if (ch == '#')//��'#'�����
	{
		T = NULL;
	}
	else
	{
		T = new BiTNode;
		T->data = ch;//��ch�������������
		createBiTree(T->lchild);//�ݹ鴴��������
		createBiTree(T->rchild);//�ݹ鴴��������
	}

}

//���ƶ���������������T���Ƹ�NewT
void copyTree(BiTree T, BiTree &NewT)
{
	if (T == NULL)
	{
		NewT = NULL;
	}
	else
	{
		NewT = new BiTNide;
		NewT->data = T->data;//��������
		copyTree(T->lchild, NewT->lchild);//�ݹ鸴��������
		copyTree(T->rchild, NewT->rchild);//�ݹ鸴��������

	}
}

//�������������
void preOrderTraverse(BiTree T)
{
	if (T)//T���ǿ���
	{
		cout << T->data<<"   ";
		preOrderTraverse(T->lchild);//�ݹ��������������
		preOrderTraverse(T->rchild);//�ݹ��������������
	}
}
//�������������
void inOrderTraverse(BiTree T)
{
	if (T)//T���ǿ���
	{
		inOrderTraverse(T->lchild);//�ݹ��������������
		cout << T->data << "   ";
		inOrderTraverse(T->rchild);//�ݹ��������������
	}
}

//�������������
void postOrderTraverse(BiTree T)
{
	if (T)//T���ǿ���
	{
		postOrderTraverse(T->lchild);//�ݹ�������������
		postOrderTraverse(T->rchild);//�ݹ�������������
		cout << T->data << "   ";
	}
}

//�ǵݹ��������������
void feiDiGuiPreOrderTraverse(BiTree T)
{
	LinkStack S;
	initStack(S);
	BiTree p = T,q;
	q = new BiTNode;
	while (p || !stackEmpty(S))
	{
		if (p)//p�ǿ�
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

//�ǵݹ��������������
void feiDiGuiInOrderTraverse(BiTree T)
{
	LinkStack S;
	initStack(S);
	BiTree q;
	q = new BiTNode;
	BiTree p = T;
	while (p || !stackEmpty(S))
	{
		if (p)//p����
		{
			push(S, p);//p��ջ
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
//�ǵݹ�������������

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
		if (p)//p�ǿ�
		{
			push(S, p);
			p = p->lchild;
		}
		else
		{//p��
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


//��������������
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
//ͳ�ƶ������Ľ��ĸ���
int nodeCount(BiTree T)
{
	if (!T)
		return 0;
	else
		return nodeCount(T->lchild) + nodeCount(T->rchild) + 1;
}

//ͳ�ƶ������ж�Ϊ1�Ľ��ĸ���
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

//ͳ�ƶ������ж�Ϊ1�Ľ��ĸ���
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

//ͳ�ƶ�������Ҷ���ĸ���
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

//����������ÿ���������Ӻ��Һ���
void swapChild(BiTree &T)
{
	if (T)
	{
		swapChild(T->lchild);//����������
		swapChild(T->rchild);//����������
		//�������Һ���
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
	cout << "���������  ";
	preOrderTraverse(T);
	cout <<endl<< "���������  ";
	inOrderTraverse(T);
	cout <<endl<< "���������  ";
	postOrderTraverse(T);
	BiTree newT;
	copyTree(T, newT);
	cout <<endl<< "T�ĸ��ƶ��������������:  ";
	inOrderTraverse(newT);
	cout << "��������" << nodeCount(T)<<endl;
	cout << "��Ϊ1�Ľ�������" << duYiNodeCount(T) << endl;
	cout << "��Ϊ2�Ľ�������" << duErNodeCount(T) << endl;
	cout << "Ҷ��������" << leafNodeCount(T) << endl;
	cout << "�������Һ��Ӻ�" << endl;
	swapChild(T);
	cout << "���������  ";
	preOrderTraverse(T);
	cout << endl << "���������  ";
	inOrderTraverse(T);
	cout << endl << "���������  ";
	postOrderTraverse(T);
	copyTree(T, newT);
	cout << endl << "T�ĸ��ƶ��������������:  ";
	inOrderTraverse(newT);
	cout << "��������" << nodeCount(T) << endl;
	cout << "��Ϊ1�Ľ�������" << duYiNodeCount(T) << endl;
	cout << "��Ϊ2�Ľ�������" << duErNodeCount(T) << endl;
	cout << "Ҷ��������" << leafNodeCount(T) << endl;
}