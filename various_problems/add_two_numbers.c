#include <stdlib.h>

//  * Definition for singly-linked list.
  struct ListNode {
    int val;
     struct ListNode *next;
 };

void	lst_add_back(struct ListNode **l, struct ListNode *new)
{
	if(*l==NULL)
	{
		*l = new;
		return ;
	}
	struct ListNode *tmp = *l;
	while(tmp->next!=NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}

int size_list(struct ListNode* l)
{
	int res =0;
	while(l)
	{
		res++;
		l=l->next;
	}
	return res;
}

void	reverse(char *s, int n)
{
	for(int i=0; i<n/2; i++)
	{
		int tmp=s[i];
		s[i] = s[n-1-i];
		s[n-1-i] = tmp;
	}
}
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2)
{
	struct ListNode *head = NULL;
	struct ListNode *tmp1=l1;
	char *s1 = malloc(size_list(l1) +1);
	int i1=0;
	while(tmp1)
	{
		s1[i1++]=tmp1->val+'0';
		tmp1=tmp1->next;
	}
	s1[i1]=0;
	struct ListNode *tmp2=l2;
	char *s2 = malloc(size_list(l2) +1);
	int i2=0;
	while(tmp2)
	{
		s2[i2++]=tmp2->val+'0';
		tmp2=tmp2->next;
	}
	s2[i2]=0;
	i1=strlen(s1)-1, i2=strlen(s2)-1;
	reverse(s1, i1+1);
	reverse(s2, i2+1);
	int p=0;
	while(i1>=0 && i2>=0)
	{
		struct ListNode *tmp = malloc(sizeof(struct ListNode));
		int value = s1[i1--]-'0' + s2[i2--]-'0' + p;
		p = value/10;
		tmp->val = value%10;
		tmp->next = NULL;
		lst_add_back(&head, tmp);
	}
	while(i1>=0)
	{
		struct ListNode *tmp = malloc(sizeof(struct ListNode));
		int value = s1[i1--]-'0' + p;
		p = value/10;
		tmp->val = value%10;
		tmp->next = NULL;
		lst_add_back(&head, tmp);
	}
	while(i2>=0)
	{
		struct ListNode *tmp = malloc(sizeof(struct ListNode));
		int value = s2[i2--]-'0' + p;
		p = value/10;
		tmp->val = value%10;
		tmp->next = NULL;
		lst_add_back(&head, tmp);
	}
	if(p)
	{
		struct ListNode *tmp = malloc(sizeof(struct ListNode));
		tmp->val = p;
		tmp->next = NULL;
		lst_add_back(&head, tmp);
	}
	return head;
}
