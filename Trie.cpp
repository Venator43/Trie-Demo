#include <iostream>
#include <unordered_map>
#include <string>
#include <cstring>	
#include <windows.h>

using namespace std;

struct trie
{
	unordered_map<char,trie*> child;
	bool word =false;
};

trie* predict(trie*root,string key)
{
	char str_char[key.length()+1];
	strcpy(str_char, key.c_str());
	trie* n = root;
	bool done = false;
	for(int i = 0;i<key.length();i++)
	{
		if (n->child.find(str_char[i]) == n->child.end())
		{
			continue; 
		}
    	else
    	{
    		cout<<str_char[i];
    	    n=n->child[str_char[i]];
    	}
	}
	while(done != true)
	{
		unordered_map<char,trie*>:: iterator p; 
    	for (p = n->child.begin(); p != n->child.end(); p++) 
    	{
    		//cout << p->first << " " << p->second << " " << p->second->word << endl;
    		cout << p->first;
    		if(p->second->word == true or p->second == NULL)
    		{
    			done = true;
    			break;
       		}
       		else
       		{
       			n = p->second;
       			break;
       		}
    	}
	}
	return n;
}

void insert_tree(trie* root, string key)
{
	char str_char[key.length()+1];
	strcpy(str_char, key.c_str());
	trie* n = root;
	char prev;
	for(int i = 0;i<key.length();i++)
	{
		if (n->child.find(str_char[i]) == n->child.end())
		{
			//cout << str_char[i];
			n->child[str_char[i]] = NULL;
			trie* tmp = new trie();
			n->child[str_char[i]] = tmp;
			if(i+1 == key.length())
			{
				tmp->word = true;
			}
			n = n->child[str_char[i]];
			//cout << endl;
		}
		else
		{
			n=n->child[str_char[i]];
		}
	}
	//cout << endl;
}

void print_tree(trie* root)
{
	if(root != NULL)
	{
		unordered_map<char,trie*>:: iterator p; 
    	for (p = root->child.begin(); p != root->child.end(); p++) 
    	{
    		cout << root << " " << p->first << " " << p->second<< " " << root->word <<endl;
    		print_tree(p->second);
    	}

	}
}

int main()
{
	trie* root = new trie();
	insert_tree(root, "CARS");
	insert_tree(root, "CASH");
	insert_tree(root, "AIR");

	int g;
	int exit = 0;
	while(exit != 1)
	{
		string input;
		int con;
		system("cls");
		cout << " _____________________" << endl;
		cout << "|  Autocomplete Text  |" << endl;
		cout << "|---------------------|" << endl;
		cout << "|[1]Tambah Data Baru  |" << endl;
		cout << "|[2]Autocomplete text |" << endl;
		cout << "|[3]Print Trie        |" << endl;
		cout << "|                     |" << endl;
		cout << "|[9]Exit              |" << endl;
		cout << "|_____________________|" << endl;
		cout << "Pilih Menu: ";
		cin >> g;
		switch (g)
		{
			case 1:
				cout << "\nInput Data Yang Akan Di Masukan :";
				cin >> input;
				insert_tree(root,input);
				break;
			case 2:
				cout << "\nMasukan Kata:";
				cin >> input;
				predict(root,input);
				cout << "\n[9]Exit...";
				cin >> con;
				break;
			case 3:
				print_tree(root);
				cout << "[9]Exit...";
				cin >> con;
				break;
			case 9:
				exit = 1;
				break;
		}
	}
}