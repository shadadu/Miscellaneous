
//

#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <vector>


using namespace std;


struct node{
	int data;
	node * next;
	node(int x){ data = x; next = NULL; }
	node(const node & a){ data = a.data; next = a.next; }
};

struct node *pushon(struct node * head_ref, int new_data)
{
	
	struct node * curr=head_ref;
	struct node * prev = NULL;
	while (curr != NULL){
		prev = curr;
		curr = curr->next;
	}
	
	curr = new struct node(new_data);
	prev->next = curr;

	
	return head_ref;
}


struct node *init_list(vector<int> vec){
	int s = vec.size();
	struct node * head = new struct node(vec[0]);
	struct node * prev = head;
	
	for (int i = 1; i < s; i++){
		struct node * curr = new struct node(vec[i]);
		prev->next = curr;
		prev = curr;
		
	}
	
	return head;

}


int print_list(struct node *head){
	
	if(head == NULL) return 0;
	struct node * curr = head;
	while (curr != NULL){
		cout << curr->data << endl;
		curr = curr->next;
		
	}

	return 0;
}

struct node * reverseList(struct node * head){
	if (head == NULL) return NULL;
	node * fore = head->next;
	head->next = NULL;
	node * prev = NULL;
	
	while (fore != NULL){
		prev = head;
		head = fore;		
		fore = fore->next;	
		head->next = prev;	
	}
	return head;
}

struct node * delete_list(node * head){

	if (head == NULL) return NULL;
	node * fore = head->next;
	while (fore != NULL){
		head = fore;
		fore = fore->next;
		delete head;
	}

	return NULL;
	 
}


void main(){

	
	vector<int> vect;

	vect.push_back(7);
	vect.push_back(9);
	vect.push_back(4);
	vect.push_back(5);
	vect.push_back(10);

	node *head = init_list(vect);
	cout << "printing initial list \n";
	print_list(head);
	pushon(head, 20);
	pushon(head, 15);
	cout << "print list after push on: " << endl;
	print_list(head);
	node * header = reverseList(head);
	cout <<" Printing reversed linked list" << endl;
	print_list(header);
	
	system("pause");

}