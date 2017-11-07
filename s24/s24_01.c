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

int _do_calc(int **box,struct node_manager *manager, int m,int n,int *max){
    struct node *node = NULL;
    int x,y,duration;    
      
    if(manager->node_num){
        node = del_node(manager);
        x = node->x;
        y = node->y;
        duration = node->duration;

        if(*max < duration)
            *max = duration;

        if(x >= 0 && x < m && y >=0 && y < n){
            if(x-1>=0 && !box[y][x-1]){
                manager->t_green--;
                manager->t_red++;
                box[y][x-1]=1;
                add_node(new_node(x-1,y,duration+1),manager);
            }
            if(y-1>=0 && !box[y-1][x]){
                manager->t_green--;
                manager->t_red++;
                box[y-1][x]=1;
                add_node(new_node(x,y-1,duration+1),manager);
            }
            if(x+1<m && !box[y][x+1]){
                manager->t_green--;
                manager->t_red++;
                box[y][x+1]=1;
                add_node(new_node(x+1,y,duration+1),manager);
            }
            if(y+1<n && !box[y+1][x]){
                manager->t_green--;
                manager->t_red++;
                box[y+1][x]=1;
                add_node(new_node(x,y+1,duration+1),manager);
            }
            _do_calc(box,manager,m,n,max);
        }

    }else{
        return 0;
    }
}


int do_calc(int **box,struct node_manager *manager, int m ,int n){
    struct node *node=NULL;    
    int max=0;
   
    _do_calc(box,manager,m,n,&max);
    return max;
}


int main(int argc, char *argv[]){
    
    int i,j,n,m,max=0;
    int **box;
    struct list_head *list=NULL;
    struct node *node=NULL;
    struct node_manager manager = {0,};

    INIT_LIST_HEAD(&manager.head);
    scanf("%d %d",&m,&n);

    box = (int**)malloc(sizeof(int*)*n);

    for(i=0; i < n ; i++){
        box[i] = (int*)malloc(sizeof(int)*m);
        for(j=0; j < m ; j++){
            scanf("%d",&box[i][j]);
            switch(box[i][j]){
                case 1 :
                    node = (struct node*)malloc(sizeof(struct node));
                    node->x=j;
                    node->y=i;
                    node->duration=0;
                    add_node(node,&manager);
                    manager.t_red++;
                    break;
                case 0 :
                    manager.t_green++;
                    break;
                case -1 :
                    manager.t_rot++;
                    break;
            }
        }
    }

    if(manager.t_red != m*n){
        max=do_calc(box,&manager,m,n);
        if(manager.t_green)
            max = -1;
    }else
        max = 0;
/*
    puts("");
    printarr(box,m,n);
    puts("");
    printf("t_green : %d \n",manager.t_green);
    printf("t_red : %d \n",manager.t_red);
    printf("t_rot : %d \n",manager.t_rot);
    printf("status : %d \n",max);
*/
    printf("%d",max);
    del_list(&manager);

    for(i=0; i<n;i++)
        free(box[i]);
    free(box);
}
