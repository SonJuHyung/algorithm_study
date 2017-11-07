#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct list_head {
    struct list_head *next, *prev;
};

struct node{
    int x;
    int y;
    int duration;
    struct list_head list_head;
};

struct node_manager{
    int node_num;
    int t_red;
    int t_green;
    int t_rot;

    struct list_head head;
};

static inline void INIT_LIST_HEAD(struct list_head *list)
{
	list->next = list;
	list->prev = list;
}

static inline void __list_add(struct list_head *new,
			      struct list_head *prev,
			      struct list_head *next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}

static inline void __list_del(struct list_head *prev, struct list_head *next)
{
	next->prev = prev;
	prev->next = next;
}

////
static inline int list_empty(const struct list_head *head)
{
	return head->next == head;
}


#define container_of(ptr, type, member) \
	((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)

////
#define list_for_each_entry(pos, head, member)				\
	for (pos = list_entry((head)->next, typeof(*pos), member);	\
	     &pos->member != (head); 	\
	     pos = list_entry(pos->member.next, typeof(*pos), member))

void printarr(int **arr, int m , int n){
    int i,j;
    puts("");
    puts("");
    for(i=0 ; i<n ; i++){
        for(j=0; j<m ;j++){
            printf("%d ",arr[i][j]);
        } 
        printf("\n");
    }
    puts("");
    puts("");

}

void add_node(struct node *node,struct node_manager *manager){
    struct list_head *head = &manager->head;
    manager->node_num++;
    __list_add(&node->list_head,head->prev,head);
}

struct node* del_node(struct node_manager *manager){
    struct list_head *entry = manager->head.next;
    struct node* node = list_entry(entry,struct node,list_head);

    manager->node_num--;
    __list_del(entry->prev,entry->next); 

    return node;
}

void del_list(struct node_manager *manager){
    while(manager->node_num){
        del_node(manager);
    }
}

struct node* new_node(int x,int y,int duration){
    struct node *node = (struct node*)malloc(sizeof(struct node));
    node->x = x;
    node->y = y;
    node->duration = duration;
    return node;
}


int main(int argc, char *argv[]){
    int i,j,n,m,max=0;
    int **box;

    INIT_LIST_HEAD($manager.head);
    scanf("%d %d",&m,&n);

    box = (int**)malloc(sizeof(int*)*n);

    for(i=0; i < n ; i++){
        box[i] = (int*)malloc(sizeof(int)*m);
        for(j=0; j < m ; j++){
            scanf("%d",&box[i][j]);
        }
    }    
}
