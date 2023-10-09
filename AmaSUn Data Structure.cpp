#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct node{
    char id[10];
    char name[101];
    char owner[101];
    char location[101];
    char type[101];
    int height;
    int balance;

    node* left;
    node* right;
}*root=NULL;

int store_count=0;

node* createNew(char name[],char owner[], char location[], char type[])
{
    node* newNode = (node*)malloc(sizeof(node));
    strcpy(newNode->name, name);
    strcpy(newNode->owner, owner);
    strcpy(newNode->location, location);
    strcpy(newNode->type, type);
    sprintf(newNode->id, "ST%03d", store_count);
    store_count++;
    newNode->height = 1;
    newNode->balance = 0;
    newNode->left = newNode->right = NULL;
    return newNode;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int getHeight(node* root)
{
    return (root) ? root->height : 0;
}

int getMaxHeight(node* root)
{
    return max(getHeight(root->left), getHeight(root->right)) + 1;
}

int setBalance(node* root)
{
    return (root) ? getHeight(root->left) - getHeight(root->right) : 0;
}

node* updateHB(node* root)
{
    root->height = getMaxHeight(root);
    root->balance = setBalance(root);
    return root;
}

node* CW(node* root)
{
    node* pivot = root->left;
    node* pivotRightChild = pivot->right;
    pivot->right = root;
    root->left = pivotRightChild;
    root = updateHB(root);
    pivot = updateHB(pivot);
    return pivot;
}

node* CCW(node* root)
{
    node* pivot = root->right;
    node* pivotLeftChild = pivot->left;
    pivot->left = root;
    root->right = pivotLeftChild;
    root = updateHB(root);
    pivot = updateHB(pivot);
    return pivot;
}

node* AVL(node* root)
{
    if(root->balance > 1)
    {
        if(setBalance(root->left) >= 0)
        {
            return CW(root);
        }
        else
        {
            root->left = CCW(root->left);
            return CW(root);
        }
    }
    else if(root->balance < -1)
    {
        if(setBalance(root->right) <= 0)
        {
            return CCW(root);
        }
        else
        {
            root->right = CW(root->right);
            return CCW(root);
        }
    }
    return root;
}

node* insertNew(node* root,node* newItem )
{
    if(root == NULL)
    {
        return newItem;
    }
    if(strcmp(newItem->name, root->name) < 0)
    {
        root->left = insertNew(root->left, newItem);
    }
    else if(strcmp(newItem->name, root->name) > 0)
    {
        root->right = insertNew(root->right, newItem);
    }
    else
    {
        printf("\nKey already exists");
    }
    return AVL(updateHB(root));
}

node* predecessor(node* root)
{
    node *curr = root->left;
    while(curr && curr->right)
    {
        curr = curr->right;
    }
    return curr;
}

node* search(node* root, char id[])
{
    if(root == NULL)
    {
        return NULL;
    }
    if(strcmp(id, root->id) < 0){
        return search(root->left, id);
    }
    else if(strcmp(id, root->id) > 0){
        return search(root->right, id);
    }
    else{
        return root;
    }
}

node* deletenode(node* root, char id[])
{
    if(!root)
     {
        return NULL;
    }
    else if(strcmp (id, root->id) < 0)
    {
        root->left = deletenode(root->left, id);
    }
    else if(strcmp (id, root->id) > 0)
    {
        root->right = deletenode(root->right, id);
    }
    else
    {
      if(!root->left || !root->right)
      {
        node *newRoot = root->left ? root->left : root->right;
        root->left = root->right = NULL;
        free(root);
        root = NULL;
        return newRoot;
      }
      node* inOrderPredecessor = predecessor(root);
      strcpy(root->id, inOrderPredecessor->id);
      strcpy(root->owner, inOrderPredecessor->owner);
      strcpy(root->location, inOrderPredecessor->location);
      strcpy(root->type, inOrderPredecessor->type);
      root->left = deletenode(root->left, inOrderPredecessor->id);
    }
    return AVL(updateHB(root));
}

void inOrder(node* root)
{
    if(root)
    {
      inOrder(root->left);
      printf("|%-10s|%-28s|%-28s|%-25s|%-20s|\n", root->id, root->name, root->owner, root->location, root->type);
      inOrder(root->right);
    }
}

void preOrder(node* root)
{
    if(root)
    {
      printf("|%-10s|%-28s|%-28s|%-25s|%-20s|\n", root->id, root->name, root->owner, root->location, root->type);
      preOrder(root->left);
      preOrder(root->right);
    }
}

void postOrder(node* root)
{
  if(root)
  {
    postOrder(root->left);
    postOrder(root->right);
    printf("|%-10s|%-28s|%-28s|%-25s|%-20s|\n", root->id, root->name, root->owner, root->location, root->type);
  }
}

int checkTree()
{
  if(root == NULL)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

void printHeader()
{
    printf("=====================================================================================================================\n");
    printf("| Store ID | Store Name                 | Store Owner Name           | Store Location        | Store Type           |\n");
    printf("=====================================================================================================================\n");
}

void printAll()
{
  int check = checkTree();
  if(check==0)
  {
    printf("No store yet....\n");
    return;
  }
  else
  {
    printf("+================+\n");
    printf("|    View Menus  |\n");
    printf("+================+\n");
    printf("| 1. Pre-Order   |\n");
    printf("| 2. In-Order    |\n");
    printf("| 3. Post-Order  |\n");
    printf("+================+\n");
    int choice;
    printf(">> ");
    scanf("%d", &choice);getchar();
    system("cls");
    switch(choice)
    {
      case 1:
        printHeader();
        preOrder(root);
        printf("=====================================================================================================================\n");
        break;
      case 2:
        printHeader();
        inOrder(root);
        printf("=====================================================================================================================\n");
        break;
      case 3:
        printHeader();
        postOrder(root);
        printf("=====================================================================================================================\n");
        break;
      default:
        printf("Invalid choice\n");
        break;
      }
  }
}

void deleteStore()
{
  int check = checkTree();
  if(check==0)
  {
    printf("No store yet....\n");
    return;
  }
  else
  {
    char id[8];
    printf("Input store ID: ");
    scanf("%s", id);getchar();
    node* temp = search(root, id);
    if(temp == NULL)
    {
      printf("ID not found\n");
    }
    else
    {
      root = deletenode(root, id);
      printf("Data Succesfully Removed!\n");
    }
  }
}

void deleteAll()
{
    int check = checkTree();
    if(check==0){
        printf("No store yet....\n");
        return;
    }
    else{
        char choose[5];
        printf("All data will be deleted\n");
        do{
            printf("will you like to proceed? [Yes | No]: ");
            scanf("%s", choose);getchar();
        }while(strcmp(choose, "Yes") != 0 && strcmp(choose, "No") != 0);
        if(strcmp(choose, "Yes") == 0){
            root = NULL;
            printf("All data has been deleted\n");
        }
        else{
            return;
        }
    }
}

void insertStore()
{
    char name[101];
    char owner[101];
    char location[101];
    char type[101];
    int len=0;
    int flag=0;

    printf("Menu : Inserty New Store\n");

    do{
       printf("Input store name: ");
       scanf("%[^\n]", name);getchar();
       len = strlen(name);
       if(len<5){
        printf("Store name length must be at least 5 !\n");
       }
    }while(len<5);

    do{
        printf("Input store owner name ['Mr. ' or 'Mrs. ' (case sensitive)]: ");
        scanf("%[^\n]", owner);getchar();
        if(strncmp(owner, "Mr. ",4) != 0 && strncmp(owner, "Mrs. ",5) != 0){
            printf("Owner name must start with either 'Mr. ' or 'Mrs. ' !\n");
        }
    }while(strncmp(owner, "Mr. ",4) != 0 && strncmp(owner, "Mrs. ",5) != 0);

    do{
        printf("Input store location [must end with ' Street' (case sensitive)]: ");
        scanf("%[^\n]", location);getchar();
        len=strlen(location);
        if(location[len-7]!=' ' || location[len-6]!='S' || location[len-5]!='t' || location[len-4]!='r' || location[len-3]!='e' || location[len-2]!='e' || location[len-1]!='t'){
            printf("Store location must end with ' Street' !\n");
            flag=0;
        }
        else{
            flag=1;
        }
    }while(flag==0);
    flag=0;
    do{
        printf("Input store type ['Daily Needs' | 'Clothing' | 'F&B' | 'Electronics' | 'Kitchenware']: ");
        scanf("%[^\n]", type);getchar();
        if(strcmpi(type, "Daily Needs") != 0 && strcmpi(type, "Clothing") != 0 && strcmpi(type, "F&B") != 0 && strcmpi(type, "Electronics") != 0 && strcmpi(type, "Kitchenware") != 0){
            printf("Store type must be between ['Daily Needs' | 'Clothing' | 'F&B' | 'Electronics' | 'Kitchenware'] !\n");
            flag=0;
        }
        else{
        	flag=1;
		}
    }while(flag==0);

    node* newnode = createNew(name, owner, location, type);
    printf("Succesfully inserted %s with ID %s ", name, newnode->id);
    root = insertNew(root, newnode);
}



void printMenu()
{
    printf("<       Amasun       >\n");
    printf("<====================>\n");
    printf("1. View all stores\n");
    printf("2. Insert new store\n");
    printf("3. Delete  a store\n");
    printf("4. Delete all stores\n");
    printf("5. Exit\n");
    printf("<====================>\n");
    printf("Choose >> ");
}


int main()
{
    int choice;
    do{
        system("cls");
        printMenu();
        scanf("%d", &choice);getchar();
        switch(choice){
            case 1:
                system("cls");
                printAll();
                system("pause");
                break;
            case 2:
                system("cls");
                insertStore();
                system("pause");
                break;
            case 3:
                system("cls");
                deleteStore();
                system("pause");
                break;
            case 4:
                system("cls");
                deleteAll();
                system("pause");
                break;
            case 5:
                system("cls");
                printf("Goodbye!\n");
                system("pause");
                break;
            default:
                break;
        }
    }while(choice!=5);
    return 0;
}
