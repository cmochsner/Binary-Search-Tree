//Program by Christina Ochsner
//PS#: 1166214

#include <iostream>
using namespace std;

struct node
{
	int data;
	node* left=NULL;
	node* right=NULL;
};
class tree
{
	private:
		node* root;

		int tLength(struct node* curr)
		{
			if (curr == NULL)
				return 0;

			int l = tLength(curr->left);
			int r = tLength(curr->right);

			if (l > r)
			{
				return(l + 1);
			}
			else 
			{
				return(r + 1);
			}
		}
	public:
		tree()
		{
			root = NULL;
		}
		bool isEmpty()
		{
			if (root == NULL)
			{
				return true;
			}
			return false;
		}
		void insert(int key)
		{
			node* newnode = new node;
			newnode->data = key;

			if (root == NULL)
			{
				root = newnode;
				return;
			}

			node* current=root;
			node* prev=root;

			while (current != NULL)
			{
				prev = current;
				if (key < current->data)
				{
					current = current->left;
					if (current == NULL)
					{
						current = newnode;
						prev->left = current;
						return;
					}
				}
				else if (key > current->data)
				{
					current = current->right;
					if (current == NULL)
					{
						current = newnode;
						prev->right = current;
						return;
					}
				}	
				else
				{
					cout << "No duplicates allowed!" << endl;
					return;
				}
			}
		}
		void inorder(node* newroot)
		{
			if (newroot != NULL)	
			{
				inorder(newroot->left);
				cout << newroot->data << " ";
				inorder(newroot->right);
			}
		}
		void preorder(node* newroot)
		{
			if (newroot != NULL)
			{
				cout << newroot->data << " ";
				preorder(newroot->left);
				preorder(newroot->right);
			}
		}
		void postorder(node* newroot)
		{
			if (newroot != NULL)
			{
				postorder(newroot->left);
				postorder(newroot->right);
				cout << newroot->data << " ";
			}
		}
		int min()
		{
			node *current = root;
			if (current == NULL)
			{
				cout << "Empty tree. No minimum." << endl;
				return -99;
			}
			while (current->left != NULL)
			{
				current = current->left;
			}
			return current->data;
		}
		int max()
		{
			node *current = root;
			if (current == NULL)
			{
				cout << "Empty tree. No maximum." << endl;
				return -99;
			}
			while (current->right != NULL)
			{
				current = current->right;
			}
			return current->data;
		}
		node* search(int key)
		{
			node* current = root;

			while (current != NULL && current->data != key)
			{
				if (current->data < key)
				{
					current = current->right;
				}
				else if (current->data > key)
				{
					current = current->left;
				}
			}
			if (current == NULL)
			{
				return NULL;
			}
			else
			{
				return current;
			}
		}
		int depth(int key)
		{
			node* current = root;
			int level = 0;

			while (current != NULL && current->data != key)
			{
				if (current->data < key)
				{
					current = current->right;
				}
				else if (current->data > key)
				{
					current = current->left;
				}
				level++;
			}
			if (current == NULL)
			{
				//-99 means tree is empty
				return -99;
			}
			else
			{
				return level;
			}
		}
		int height()
		{
			return tLength(root);
		}
		void remove(int key)
		{
			node* curr = root;
			node* succ = NULL;
			node* keyNode = NULL;
			
			while (curr != NULL)
			{
				if (key == root->data)
				{
					keyNode = curr;
					break;
				}
				if (curr->left!=NULL && curr->left->data == key)
				{
					succ = curr;
					keyNode = curr->left;

					break;
				}
				else if (curr->right!=NULL && curr->right->data == key)
				{
					succ = curr;
					keyNode = curr->right;

					break;
				}
				if (curr->data < key)
				{
					curr = curr->right;
				}
				else if (curr->data > key)
				{
					curr = curr->left;
				}
			}
			if (keyNode == NULL)
			{
				return;
			}
			else if (keyNode->right == NULL && keyNode->left == NULL)
			{
				if (succ == NULL)
				{
					root = NULL;
				}
				else if (key > succ->data)
				{
					succ->right = NULL;
				}
				else if (key < succ->data)
				{
					succ->left = NULL;
				}

				free(keyNode);
			}
			else if (keyNode->right == NULL)
			{
				node* temp = keyNode->left;

				keyNode->data = temp->data;
				keyNode->left = temp->left;
				keyNode->right= temp->right;

				free(temp);

			}
			else if (keyNode->left == NULL)
			{
				node* temp = keyNode->right;

				keyNode->data = keyNode->right->data;
				keyNode->left = keyNode->right->left;
				keyNode->right = keyNode->right->right;

				free(temp);
			}
			else
			{
				node *sLRS = keyNode;
				node *LRS = keyNode->right;
				
				while (LRS->left != NULL)
				{
					sLRS = LRS;
					LRS = LRS->left;
				}

				keyNode->data = LRS->data;

				if (LRS->right != NULL)
				{
					node *temp = LRS->right;

					LRS->data = temp->data;
					LRS->left =temp->left;
					LRS->right= temp->right;

					free(temp);
				}
				else
				{
					if (sLRS->data == LRS->left->data)
					{
						sLRS->left = NULL;
					}
					else
					{
						sLRS->right = NULL;
					}

					free(LRS);
				}
			}
		}
		void print(int type)
		{
			switch (type)
			{
				case 1:
					preorder(root);
					cout << endl;
					break;
				case 2:
					inorder(root);
					cout << endl;
					break;
				case 3:
					postorder(root);
					cout << endl;
					break;
			}
		}
};

int main()
{
	tree t;
	int choice=0;
	int num=-99;

	cout << "Hey! Welcome to the Binary Search Tree program!" << endl;
	cout << "Type in a number from the menu below to perform operations on your tree." << endl;

	while (choice != 9)
	{
		cout << "\n1. Insert a number into your tree. No duplicates allowed." << endl;
		cout << "2. Search for a number in your tree." << endl;
		cout << "3. Delete a number from your tree." << endl;
		cout << "4. Print your tree." << endl;
		cout << "5. Find the minimum value of your tree." << endl;
		cout << "6. Find the maximum value of your tree." << endl;
		cout << "7. Find the height of the tree." << endl;
		cout << "8. Find the depth of a certain node." << endl;
		cout << "9. Exit" << endl;
		cin >> choice;

		switch (choice)
		{
			case 1:
			{
				cout << "Enter the number you'd like to enter: ";
				cin >> num;
				t.insert(num);
				cout << endl;
			}
			break;
			case 2:
			{
				cout << "Enter the number you'd like to search for: ";
				cin >> num;
				if (t.search(num) == NULL)
				{
					cout << "\nNumber is not in tree!" << endl;
				}
				else
				{
					cout << "\nNumber is in tree!" << endl;
				}
			}
			break;
			case 3:
			{
				cout << "Enter the number you'd like to delete from the tree: ";
				cin >> num;
				t.remove(num);
				cout << endl;
			}
			break;
			case 4:
			{
				cout << "Enter the type of traversal you'd like to use when printing your tree." << endl;
				cout << "1 for Preorder, 2 for Inorder, or 3 for Postorder." << endl;
				cin >> num;
				t.print(num);
			}
			break;
			case 5:
			{
				int min = t.min();
				if (min != -99)
				{
					cout << "The minimum of the tree is " << min << endl;
				}
			}
			break;
			case 6:
			{
				int max = t.max();
				if (max != -99)
				{
					cout << "The maximum of the tree is " << max << endl;
				}
			}
			break;
			case 7:
			{
				cout << "The height of the tree is " << t.height() << endl;
			}
			break;
			case 8:
			{
				cout << "Enter the number for which you want to see the depth: ";
				cin >> num;
				int deep = t.depth(num);
				if (deep != -99)
				{
					cout << "\nThe depth of " << num << " is " << deep << endl;
				}
				else
				{
					cout << "\nThe number you entered does not exist in the tree." << endl;
				}
			}
			break;
			case 9:
				break;
			default:
			{
				cout << "Invalid input. Try again." << endl;
			}
			break;
		}
	}

	//system("pause");
	return 0;
}