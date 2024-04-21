/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

// ���Ḯ��Ʈ ����ü
typedef struct Node {
	int key;
	struct Node* link;
} listNode;

// ���Ḯ��Ʈ headNode ����ü
typedef struct Head {
	struct Node* first;
} headNode;


/* �Լ� ����Ʈ */
headNode* initialize(headNode* h);		// ���Ḯ��Ʈ �ʱ�ȭ
int freeList(headNode* h);				// ���Ḯ��Ʈ �޸� �Ҵ� ����

int insertFirst(headNode* h, int key);	// ��带 ���Ḯ��Ʈ ���� �տ� �߰�
int insertNode(headNode* h, int key);	// ���Ḯ��Ʈ�� key�� ���� ū �� �տ� ��� ����
int insertLast(headNode* h, int key);	// ���Ḯ��Ʈ�� �������� ��� �߰�

int deleteFirst(headNode* h);			// ���Ḯ��Ʈ ���� �� �κ� ��� ����
int deleteNode(headNode* h, int key);	// ���Ḯ��Ʈ key���� ã�� ����
int deleteLast(headNode* h);			// ���Ḯ��Ʈ ���� �� �κ� ��� ����
int invertList(headNode* h);			// ���Ḯ��Ʈ ������

void printList(headNode* h);			// ���Ḯ��Ʈ ���

int main()
{	// ���α׷� ���۽� �й��� �̸��� ���
	printf("[----- [Kim Yejun]  [2020025051] -----]\n\n");


	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {
	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(h != NULL)
		freeList(h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
	 */
	listNode* p = h->first;
	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	// Ű ���� ��ũ�� ��忡 ����
	node->link = h->first;
	h->first = node;

	return 0;
}


/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {

	listNode* node= (listNode*)malloc(sizeof(listNode));
    node->key= key;

    listNode* current= h->first; // Ž���� ���� ���
    listNode* prev= NULL;		 // Ž���� ���� ���

    // ����Ʈ�� ���� �� ������ Ű ������ ū �� ���� ����Ʈ �˻��ϴ� ������� Ž��
    while (current!= NULL && current->key< key) {
        prev= current;
        current= current->link;
    }

    if (prev == NULL) {
        // Ű ���� ���� ���� ���
        node->link= h->first;
        h->first= node;
    } else {
		// �׿��� ���
        prev->link= node;
        node->link= current;
    }

    return 0;
}

/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {
	listNode* node= (listNode*)malloc(sizeof(listNode));
    node->key= key;

    if (h->first == NULL) {
        // ����Ʈ�� ������� ���
        h->first= node;
		node->link= NULL;
    } else {
        listNode* current= h->first;
        while (current->link != NULL) {
		// ������ ������ ���Ḯ��Ʈ Ž���ϱ�
            current= current->link;
        }
		// �������� �� ����
        current->link= node;
		node->link= NULL;
    }

    return 0;
}


/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {
	if (h->first != NULL) {
	// ����Ʈ�� ù��° �� ���� �ּҷ� �������ְ� �޸� �Ҵ� ����
		listNode* temp= h->first;
		h->first= h->first->link;
		free(temp);
	}
	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {

    listNode* current= h->first; // Ž���� ���� ���
    listNode* prev= NULL;		 // Ž���� ���� ���

    // �Է¹��� Ű ���� ������ ��� ã��
    while (current != NULL && current->key != key) {
        prev= current;
        current= current->link;
    }

    if (current == NULL) {
        // �Է¹��� Ű���� ���� ��尡 ���� ���
        printf("given key is not in list!\n");
        return 0;
    }

    // ���� �κ�
    if (prev == NULL) {
        // ù ��° ��带 �����ؾ��ϴ� ���
        h->first= current->link;
    } else {
        // �� ���� ��带 �����ϴ� ���
        prev->link= current->link;
    }

    free(current); // ������ ��� �޸� �Ҵ� ����
    return 0;
}

/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {

	// ��尡 ����ִ� ���
    if (h->first == NULL) {
        printf("list already empty!\n");
        return 0;
    }

    listNode* current= h->first; // Ž���� ����� ���� ��ġ
    listNode* prev= NULL;		 // Ž���� ����� ���� ��ġ

    // ������ ������ Ž��
    while (current->link != NULL) {
        prev= current;
        current= current->link;
    }

    // ������ ��� ����
    if (prev == NULL) {
        // ����Ʈ�� ��尡 �ϳ��� ���� ���
        h->first= NULL;
    } else {
		// �� ���� ���
        prev->link= NULL;
    }

    free(current); // ������ ��� �޸� �Ҵ� ����

    return 0;
}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {

    listNode* prev= NULL;
    listNode* current= h->first;
    listNode* next= NULL;

	// �� ĭ�� �̵��ϸ鼭 ���� ���� ���� ����� ��ũ�� �ݴ�� �ٲ���
    while (current != NULL) {
        next= current->link;
        current->link= prev;
        prev= current;
        current= next;
    }

    h->first= prev; // ���������� ��尡 ���� ������ ��带 ����Ű���� 

    return 0;
}


void printList(headNode* h) {
	int i= 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p= h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p= p->link;
		i++;
	}

	printf("  items = %d\n", i);
}