#include "binary_search_tree.h"

BinarySearchTree::BinarySearchTree()
{
	root_ = nullptr;
}

BinarySearchTree::~BinarySearchTree()
{
	empty();
}

bool BinarySearchTree::isEmpty() const
{
	return root_ == nullptr;
}

void BinarySearchTree::empty()
{
	if (!isEmpty())
	{
		search_empty(root_);
	}
}

void BinarySearchTree::display() const
{
	if (!isEmpty())
	{
		search_display(root_);
	}
	else
	{
		cerr << "ERROR: No accounts found." << endl;
	}
}

//Finds an account given an account number.
bool BinarySearchTree::Retrieve(const int& acct_number, Account*& the_account)
{
	Node* current = root_;
	while (current != nullptr)
	{
		if (acct_number == current->account->get_id())
		{
			the_account = current->account;
			return true;
		}
		else if (acct_number < current->account->get_id())
		{
			current = current->left;
		}
		else if (acct_number > current->account->get_id())
		{
			current = current->right;
		}
	}
	return false;
}

//Inserts an account if the account number is valid.
bool BinarySearchTree::Insert(Account* the_account)
{
	if (the_account->get_id() < 1000 || the_account->get_id() > 9999)
	{
		cerr << "ERROR: " << the_account->get_id() << " is not a valid account number. Transaction refused." << endl;
		return false;
	}
	if (isEmpty())
	{
		root_ = new Node;
		root_->account = the_account;
		return true;
	}
	int insert_id = the_account->get_id();
	Node* current = root_;
	while (current != nullptr) {
		if (insert_id < current->account->get_id())
		{
			if (current->left == nullptr)
			{
				current->left = new Node;
				current->left->account = the_account;
				return true;
			}
			else
			{
				current = current->left;
			}
		}
		else if (insert_id > current->account->get_id())
		{
			if (current->right == nullptr)
			{
				current->right = new Node;
				current->right->account = the_account;
				return true;
			}
			else
			{
				current = current->right;
			}
		}
		else if (current->account->get_id() == insert_id)
		{
			cerr << "ERROR: Account " << the_account->get_id() << " is already open. Transaction refused." << endl;
			return false;
		}
	}
	return false;
}

//Recursively empties the list.
void BinarySearchTree::search_empty(Node* current)
{
	if (current == nullptr)
	{
		return;
	}
	search_empty(current->left);
	search_empty(current->right);
	delete current->account;
	current->account = nullptr;
	current->left = nullptr;
	current->right = nullptr;
	delete current;
	current = nullptr;
}

//Recursively displays the list of accounts in order by ID number.
void BinarySearchTree::search_display(Node* current) const
{
	if (current->left != nullptr && current->right != nullptr)
	{
		search_display(current->left);
		cout << *(current->account) << endl;
		search_display(current->right);
	}
	else if (current->left != nullptr)
	{
		search_display(current->left);
		cout << *(current->account) << endl;
	}
	else if (current->right != nullptr)
	{
		cout << *(current->account) << endl;
		search_display(current->right);
	}
	else
	{
		cout << *(current->account) << endl;
	}
}