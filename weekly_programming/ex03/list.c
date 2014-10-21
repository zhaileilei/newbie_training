/*===========================
 *	Filename:
 *	list.c
 *	Copyright (C) 2014 Wistron
 *	All rights reserved.
 *
 *	Description:
 *		This file will achieve the number of output 1
 *
 *	Author/Create Date:
 *		Myth Zhai, Oct08'14
 *	Modification History:
 *
 *
 *	Note:
 *=================================
 */

/* Include Files */
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct {
	int id;
	char name[20];
	char genda[10];
	int age;
	float salary;
} s_worker;
/* create list */
typedef struct node {
	s_worker worker;
	struct node *p_next;
}node;

/*create a node*/
node *create(){
	node *new = malloc(sizeof( node));
	if (new == NULL) {
		printf("malloc err !\n");
		return NULL;
	}
	new->p_next = NULL;
	return new;
}

/* Insert node */
void insert(node *head){
	node *tmp = head;
	node *new = malloc(sizeof(node));
	int i =0;
	if (new == NULL) {
		printf("malloc err !\n");
		return ;
	}
	while (tmp->p_next) {
		tmp = tmp->p_next;
	}
	tmp->p_next = new;
	new->p_next = NULL;
	printf("please input your id:");
	scanf("%d", &new->worker.id);
	printf("please input your name:");
	scanf("%s", new->worker.name);
	printf("please input your genda:");
	scanf("%s", new->worker.genda);
	printf("please input your age:");
	scanf("%d", &new->worker.age);
	printf("please input your salary:");
	scanf("%f", &new->worker.salary);
}
/* Traversal function */
void traversal(node *head){
	node *tmp = head/*->p_next*/;
	tmp = tmp->p_next;
	while (tmp) {
		printf("id=%d,name=%s,genda=%s,age=%d,salary=%g\n",
				tmp->worker.id, tmp->worker.name, tmp->worker.genda,
				tmp->worker.age, tmp->worker.salary);
		tmp = tmp->p_next;
	}
	printf("traversal over !\n");
}
/* Removing a single node */
void delet_node(node *head, int id){
	node *tmp = head;
	node *this = head;
	int flag = 0;
	while (tmp->p_next) {
		this = tmp;
		tmp = tmp->p_next;
		/* delete node :tmp->worker.id == id*/
		if (tmp->worker.id == id) {
			printf("delete id=%d,name=%s,genda=%s,age=%d,salary=%g\n",
					tmp->worker.id, tmp->worker.name, tmp->worker.genda,
					tmp->worker.age, tmp->worker.salary);
			this->p_next = tmp->p_next;
			free(tmp);
			flag = 1;
			break;
		}
	}
	if (flag == 0) {
		printf("%d not exists, delete none !\n", id);
	}
	
}
/* Delete all nodes */
void free_all(node *head) {
	node *node1 = head;
	node *node2 = head;
	while (node1->p_next) {
		node1 = node2;
		node2 = node2->p_next;
		printf("delete id=%d,name=%s,genda=%s,age=%d,salary=%g\n",
				node2->worker.id, node2->worker.name, node2->worker.genda,
				node2->worker.age, node2->worker.salary);

		node1->p_next = node2->p_next;
		free(node2);
		node2 = node1;
	}

	printf("free all nodes in the linked list !\n");
}
int main (){
	node *head = create();
	int i = 0;
	int x;
	for(i =0; i<3;i++){
		insert(head);
		
	}
	printf("insert over !\n");
	traversal(head);
	printf("please input delete id: ");
	scanf("%d",&x);

	delet_node(head, x);
	traversal(head);
	delet_node(head, 100);

	free_all(head);
	traversal(head);

	return 0;
}
