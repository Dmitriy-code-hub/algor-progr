#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* run this program using the console pauser or add your own getch,
system("pause") or input loop
using namespace std; */

struct TreeNode
{
	double data; // ключ/данные
	struct  TreeNode* left; // указатель на левого потомка
	struct TreeNode* right; // указатель на правого потомка
};

struct QueueNode //для вывода по уровням
{
	struct TreeNode* node;
	struct QueueNode* next;
} *headq = NULL, * q = NULL, * tailq = NULL, * for_del = NULL;


void from_file(char* file_name, int** x, int* n) {
	FILE* input = NULL;

	//input = fopen(file_name, "r");
	fopen_s(&input, file_name, "r"); //безопасный вариант требуют некоторые компиляторы
	if (input == NULL) {
		printf("Error opening file");
		getch();
		exit(3);
	}

	//Подсчитать среднее значение ключей узлов правого узла

	int k;
	fscanf_s(input, "%d\n", &k);
	*n = k;
	*x = (int*)malloc(k * sizeof(int));
	for (int i = 0; i < k; i++)
	{
		fscanf_s(input, "%d\n", *x + i); // &((*x)[i]));
	}
	fclose(input);
}




void AddNode(struct TreeNode* node)
{
	q = (struct QueueNode*)malloc(sizeof(struct QueueNode));
	q->node = node; //почему подчеркивает? что может значить еще раз 
	q->next = NULL;
	if (!headq)	headq = q;
	else tailq->next = q;
	tailq = q;
}
//moyi funkzii
double summa_elementov(struct TreeNode* root)
{
	if (root == NULL)   // Базовый случай
	{
		return 0;
	}
	double rezult = root->data;
	rezult += summa_elementov(root->right);  //рекурсивный вызов правого поддерева
	rezult += summa_elementov(root->left);   //рекурсивный вызов левого поддерева
	return rezult;
}



double kolichestvo_elementov(struct TreeNode* root)
{
	if (root == NULL)   // Базовый случай
	{
		return 0;
	}
	double rezult = 1;
	rezult += kolichestvo_elementov(root->right);  //рекурсивный вызов правого поддерева
	rezult += kolichestvo_elementov(root->left);   //рекурсивный вызов левого поддерева
	return rezult;
}

double sredneye(struct TreeNode* root)
{
	if (root == NULL)   // Базовый случай
	{
		return 0;
	}
	if (root->right == NULL)   // Базовый случай
	{
		return 0;
	}
	double s = 0;
	s = summa_elementov(root->right);
	int k = kolichestvo_elementov(root->right);
	if (k > 0)
	{
		s /= (double)k;
	}
	return s;
}
//konez moyich
void levelOrderPrint(struct TreeNode* root) {
	if (root == NULL)
	{
		return;
	}
	AddNode(root);

	while (headq) // пока очередь не пуста
	{
		//TreeNode* temp = headq->node; // Берем первый элемент в очереди
		printf("%.0lf ", headq->node->data);
		//cout << headq->node->data << " "; // Печатаем значение первого элемента в очереди
		//printf("%lf, %lf  ", p->key.x, p->key.y);
		if (headq->node->left != NULL)
			AddNode(headq->node->left);  // Вставляем  в очередь левого потомка
		if (headq->node->right != NULL)
			AddNode(headq->node->right);  // Вставляем  в очередь правого потомка
		for_del = headq;
		headq = headq->next;
		free(for_del);
		//delete for_del;
	}
}

void preorderPrint(struct TreeNode* root)
{
	if (root == NULL)   // Базовый случай
	{
		return;
	}
	printf("%.0lf ", root->data);
	//cout << root->data << " ";
	preorderPrint(root->left);   //рекурсивный вызов левого поддерева
	preorderPrint(root->right);  //рекурсивный вызов правого поддерева
}
// Функция печатает значения бинарного дерева поиска в прямом порядке.
// Вместо печати первой инструкцией функции может быть любое действие
// с данным узлом

void inorderPrint(struct TreeNode* root)
{
	if (root == NULL)   // Базовый случай
	{
		return;
	}
	inorderPrint(root->left);   //рекурсивный вызов левого поддерева
	printf("%lf ", root->data);
	//cout << root->data << " ";
	inorderPrint(root->right);  //рекурсивный вызов правого поддерева
}
// Функция печатает значения бинарного дерева поиска в симметричном порядке.
// То есть в отсортированном порядке

void postorderPrint(struct TreeNode* root)
{
	if (root == NULL)   // Базовый случай
	{
		return;
	}
	postorderPrint(root->left);   //рекурсивный вызов левого поддерева
	postorderPrint(root->right);  //рекурсивный вызов правого поддерева
	printf("%lf ", root->data);	  //cout << root->data << " ";
}
// Функция печатает значения бинарного дерева поиска в обратном порядке.
// Не путайте обратный и обратноотсортированный (обратный симметричный).

void reverseInorderPrint(struct TreeNode* root)
{
	if (root == NULL)   // Базовый случай
	{
		return;
	}
	reverseInorderPrint(root->right);  //рекурсивный вызов правого поддерева
	printf("%lf ", root->data);
	//cout << root->data << " ";
	reverseInorderPrint(root->left);   //рекурсивный вызов левого поддерева
}
// Функция печатает значения бинарного дерева поиска в обратном симметричном порядке.
// То есть в обратном отсортированном порядке

void likeTree(struct TreeNode* root)
{
	static int level = 0;
	if (!root)
	{
		level--;
		return;
	}
	level++;
	likeTree(root->right);
	for (int i = 0; i < level; i++)
		printf("\t");
	//cout << "\t";
	printf("%.0lf\n", root->data);
	//cout << root->data << endl;
	level++;
	likeTree(root->left);
	level--;
}

int main(int argc, char** argv) {
	int N, i;
	struct TreeNode* head = NULL, * cur = NULL, * tmp = NULL;
	//srand ((int)time(NULL));
//	printf("Vvedite kolichestvo elementov dereva\n");
	//scanf_s("%d", &N);//chitayu zeloe i kuda polozhit
	//cin >> N;
	//printf("\n");
	//cout << endl;
	printf("0:");
	//cout << "0: ";

	int* a;
	from_file("Dano.txt", &a, &N);

	for (i = 0; i < N; i++)
	{
		struct TreeNode* tmp;
		tmp = (struct TreeNode*)malloc(sizeof(struct TreeNode));
		tmp->data = a[i];

		//rand() % 10 - rand() % 10;

		printf("%lf ", tmp->data);
		//cout << tmp->data << " ";
		tmp->left = NULL;
		tmp->right = NULL;
		if (!head)
		{
			head = tmp;
			cur = tmp;
		}
		else
		{
			cur = head;
			while (cur)
			{
				if (tmp->data >= cur->data)
				{
					if (cur->right) cur = cur->right;
					else
					{
						cur->right = tmp;
						break;
					}
				}
				else
				{
					if (cur->left) cur = cur->left;
					else
					{
						cur->left = tmp;
						break;
					}
				}
			}
		}
	}
	printf("\n"); //cout << endl;
	printf("\n"); //cout << endl;
	printf("1:");  //cout << "1: ";
	preorderPrint(head);
	printf("\n"); //cout << endl;
	printf("\n"); //cout << endl;
	printf("2:"); //cout << "2: ";
	inorderPrint(head);
	printf("\n");//cout << endl;
	printf("\n"); //cout << endl;
	printf("3:"); //cout << "3: ";
	postorderPrint(head);
	printf("\n"); //cout << endl;
	printf("\n"); //cout << endl;
	printf("4:"); //cout << "4: ";
	reverseInorderPrint(head);
	printf("\n"); //cout << endl;
	printf("\n"); //cout << endl;
	printf("5:"); //cout << "5: ";
	levelOrderPrint(head);
	printf("\n"); //cout << endl;
	printf("\n"); //cout << endl;
	likeTree(head);

	//moya
	printf("\n"); //cout << endl;
	printf("\n"); //cout << endl;
	double s = sredneye(head);
	printf("s= %lf\n", s);



	return 0;
}
