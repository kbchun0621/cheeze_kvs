#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct _node{
	char  key[4096];
	char  value[4096];
	struct _node  *left;
	struct _node  *right;
}Node;

Node *root=NULL;

Node *mknode(){
	Node *new=malloc(sizeof(Node));
	new->left=NULL;
	new->right=NULL;
	return new;
}
Node *Insert(Node *standard,char* key, char *value){
	if(standard==NULL){//case of a root
		Node *new;
		new=mknode();
		standard=new;
		strcpy(standard->key,key);
		strcpy(standard->value,value);
		return standard;
	}
	else if(strcmp(key,standard->key)<0 && standard-> left==NULL){//add it on the left
		Node * new;
		new=mknode();
		strcpy(new->key,key);
		strcpy(new->value,value);
		standard->left=new;
		return standard;
	}
	else if(strcmp(key,standard->key)<0&& standard->left!=NULL){//have to go deeper left
		standard->left=Insert(standard->left,key,value);
		return standard;
	}
	else if(strcmp(key,standard->key)>0 && standard->right==NULL){//add it on the right
		Node * new;
                new=mknode();
                strcpy(new->key,key);
		strcpy(new->value, value);
                standard->right=new;
                return standard;
	}
	else {//add have to go deeper
		standard->right=Insert(standard->right,key,value);
		return standard;
	}
}

Node *Delete(Node *standard,char * key){
//반복문으로 먼저 찾아 들어가자! 그때마다 parent 바꿔주자.
	Node *parent=NULL;
	Node *look=standard;
	while(1){
		if(strcmp(look->key,key)!=0){
			break;
		}
		else if(strcmp(look->key,key)<0){
			parent=look;
			look=look->right;
		}
		else if(strcmp(look->key,key)>0){
			parent=look;
			look=look->left;
			}
		if(look->right==NULL&&look->left==NULL)
		{
			printf("%s","It doesn't exist");
			return NULL;
		}
	
	//root인 경우
        if(parent==NULL){
            //nochild
            if(look->left==NULL && look->right==NULL){
                free(look);
		root=NULL;
                return NULL;
            }
            // one child
            else if(look->left==NULL|| look->right==NULL){
		Node* replace;
                if(look->left==NULL){
                        replace=look->right;
                }
                else{
                        replace=look->left;
                }
		root=replace;
		free(look);
		return NULL;
	    }
	    //two child;
	    else{
		    Node *replace=look->right;
		    Node *pr=NULL;
		    while(replace !=NULL && replace->left!=NULL){
			    pr=replace;
			    replace=replace->left;
		    }
		    strcpy(root->key,replace->key);
		    if(pr->left==replace){
			pr->left=NULL;
		}
		    else{
			    pr->right=NULL;
		}
		    free(replace);
		    return NULL;
	    }

       	}
	//non root
	//non child
	if(look->left==NULL && look->right==NULL){
		if(parent->left==look){
			Node *temp=NULL;
			free(look);
			parent->left=NULL;
			return temp;
		}
		else{
			Node *temp=NULL;
			free(look);
			parent->right=NULL;
			return temp;
		}

	}
	//one child
	else if(look->left==NULL|| look->right==NULL){
		Node*replace;
		if(look->left==NULL){
			replace=look->right;
		}
		else{
			replace=look->left;
		}
		if(parent->right==look){
			parent->right=replace;
			free(look);
			return replace;}
		else{
			parent->left=replace;
			free(look);
			return replace;
		}
	}
	//two child
	else{
		Node *replace=look->right;
		Node *pr=NULL;
		while(replace!=NULL && replace->left!=NULL){
			pr=replace;
			replace=replace->left;
		}
		strcpy(look->key,replace->key);
		if(pr->left==replace){
			pr->left=NULL;
		}
		else{
			pr->right=NULL;
		}
		free(replace);
	return pr;}
	}
	}
Node * Print(Node *standard){
	if(standard!=NULL){
		Print(standard->left);
		printf("The key is %s \n", standard->key);
		printf("The value is %s \n", standard->value);
		Print(standard->right);
	}
}


int main(void){
	while(1){
		int enter=0;
		printf("Choose a number :\n1.Insert\n2.Delete\n3.Print\n4.Exit\n");
		scanf("%d",&enter);
		if(enter==1){
			while(true){
				char key[4096];
				char value[4096];
				printf("%s","enter a key");
				scanf("%s",key);
				if(strcmp(key,"-1")==0){
					break;}
				else{
					printf("%s","enter a value");
					scanf("%s",value);
					Node * standard;
					standard=Insert(root,key,value);
					if (root == NULL){
					       	root = standard;
					}
				}
			}
		}
		else if(enter==2){
			while(true){
				char key[4096];
				printf("%s","enter a key");
				scanf("%s", key);
				if(strcmp(key,"-1")==0){
					break;
				}
				else{
					Node *standard;
					standard=Delete(root,key);
				}
			}
		}
		else if(enter==3){
			Print(root);

		}
		else{
			break;
		}
	}
}
