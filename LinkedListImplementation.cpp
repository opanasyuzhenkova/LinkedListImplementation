#include <iostream>
#include <string>
using namespace std;

class member { 
	string name;
	string surname;
	string city;
	member* next; 
	member* prev;

public:
	member(string name_ = "", string surname_ ="", string city_ = "")
	{
		name = name_; 
		surname = surname_;
		city = city_;
		next = nullptr;
		prev = nullptr;
	}
	void set_next(member* next_) { next = next_; } 
	void set_prev(member* prev_) { prev = prev_; } 
	member* get_next() { return next; } 
	member* get_prev() { return prev; } 
	void set_name(string name_) { name = name_; }
	void set_surname(string surname_) { surname = surname_; }
	void set_city(string city_) { city = city_; }
	string get_name() { return name; }
	string get_surname() { return surname; }
	string get_city() { return city; }
	~member() { cout << "elem with name " << name << " deleted\n"; }
};

class group 
{
public:
	member* head; 
	member* tail;
	int count; 
	group() { head = nullptr; tail = nullptr; count = 0; } 
	~group() 
	{
		member* cur_elem = head; 
		while (cur_elem != nullptr) 
		{
			member* del_elem = cur_elem; 
			cur_elem = cur_elem->get_next(); 
			delete del_elem; 
		}
	}

	void print() 
	{
		member* cur_elem = head; 
		while (cur_elem != nullptr) 
		{
			cout << cur_elem->get_name() << " " << cur_elem->get_surname() << " " << cur_elem->get_city()<<" \n"; 
			cur_elem = cur_elem->get_next();  
		}
	}

	void inverted_print() 
	{
		member* cur_elem = tail; 
		while (cur_elem != nullptr) 
		{
			cout << cur_elem->get_name() << " " << cur_elem->get_surname() << " " << cur_elem->get_city() << "\n"; 
			cur_elem = cur_elem->get_prev(); 
		}
	}

	void push_back(member* last)
	{
		member* add = new member(last->get_name(),last->get_surname(),last->get_city()); 
		if (head == nullptr)
		{
			head = add; 
			tail = add; 
			count++; 
			return;
		}
		member* cur_elem = tail; 
		cur_elem->set_next(add);
		add->set_prev(tail);
		tail = add;
		count++;
	}

	void push_front(member* front) 
	{
		member* add = new member(front->get_name(), front->get_surname(),front->get_city()); 
		if (head == nullptr) 
		{
			head = add; 
			tail = add; 
			count++; 
			return;
		}
		add->set_next(head); 
		head->set_prev(add); 
		head = add; 
		count++;
	}

	void insert(int place, member* new_elem)
	{
		if (head == nullptr) 
			return;
		if (place > count) 
		{
			cout << "Error! Not enough elements in list!\n";
			return;
		}
		else if (place == count) 
			push_back(new_elem);
		else
		{
			member* add = new member(new_elem->get_name(),new_elem->get_surname(),new_elem->get_city()); 
			int k = 1; 
			member* cur_elem = head; 
			while (k < place) 
			{
				cur_elem = cur_elem->get_next(); 
				if (cur_elem == nullptr) 
					break;
				k++;
			}
			add->set_next(cur_elem->get_next()); 
			add->set_prev(cur_elem);
			cur_elem->get_next()->set_prev(add); 
			cur_elem->set_next(add);
			count++; 
		}
	}

	void insert(member after, member* new_elem) 
	{
		if (head == nullptr) 
			return;
		if (after.get_name() == tail->get_name() && after.get_surname()==tail->get_surname() && after.get_city()==tail->get_city()) 
			push_back(new_elem);
		else
		{
			member* add = new member(new_elem->get_name(), new_elem->get_surname(),new_elem->get_city()); 
			member* cur_elem = head; 
			while (cur_elem != nullptr && cur_elem->get_name() != after.get_name() && 
				cur_elem->get_surname()!=after.get_surname() && cur_elem->get_city()!=after.get_city())
				cur_elem = cur_elem->get_next(); 
			if (cur_elem == nullptr) 
			{
				cout << "Element with required name is not found\n";
				return;
			}
			add->set_next(cur_elem->get_next()); 
			add->set_prev(cur_elem);
			cur_elem->get_next()->set_prev(add);
			cur_elem->set_next(add);
			count++;
		}
	}

	void delete_first()
	{
		member* del = head; 
		if (head == nullptr) 
			return;
		head = head->get_next(); 
		if (count==1)
		{
			cout << "We removed the last element\n";
		} 
		delete del; 
		count--;
	}
	
	void delete_last()
	{
		member* del = tail; 
		if (tail == nullptr)
			return;
		if (head==tail)
			cout << "1 element left! \n"; 
		else {
			tail = tail->get_prev();
			tail->set_next(nullptr);
			delete del; 
			count--;
		}
	}

	void delete_elem(member del)
	{
		if (head == nullptr) 
			return;
		if (del.get_name() == tail->get_name() && del.get_surname() == tail->get_surname() 
			&& del.get_city() == tail->get_city()) 
			delete_last();
		else
		{
			member* cur_elem = head; 
			while (cur_elem != nullptr && cur_elem->get_name() != del.get_name() 
				&& cur_elem->get_surname() != del.get_surname() && cur_elem->get_city() != del.get_city())
				cur_elem = cur_elem->get_next(); 
			member* delem = cur_elem; 
			if (cur_elem == nullptr) 
			{
				cout << "Element with required name is not found\n";
				return;
			}
			cur_elem->get_prev()->set_next(cur_elem->get_next()); 
			cur_elem->get_next()->set_prev(cur_elem->get_prev());
			delete delem;
			count--;
		}
	}

	void delete_elem_ind(int place) 
	{
		if (head == nullptr) 
			return;
		if (place > count) 
		{
			cout << "Error! Not enough elements in list!\n";
			return;
		}
		else if (place == count) 
			delete_last();
		else if (place == 1)
			delete_first();
		else
		{
			int k = 1;
			member* cur_elem = head; 
			while (k < place) 
			{
				cur_elem = cur_elem->get_next(); 
				if (cur_elem == nullptr) 
					break;
				k++;
			}
			member* delem = cur_elem; 
			if (cur_elem == nullptr) 
			{
				cout << "Element with required name is not found\n";
				return;
			}
			cur_elem->get_prev()->set_next(cur_elem->get_next());
			cur_elem->get_next()->set_prev(cur_elem->get_prev());
			delete delem;
			count--;
		}
	}

	void count_elems() 
	{
		cout << "There are "<<count<< " elements in the list \n \n";
	}

	void find_element(member new_element) 
	{
		member* cur_elem = head; 
		if (head == nullptr) 
			return;

		while (cur_elem != nullptr && cur_elem->get_name() != new_element.get_name() 
			&& cur_elem->get_surname() != new_element.get_surname() && cur_elem->get_city() != new_element.get_city()) 
			cur_elem = cur_elem->get_next(); 
		if (cur_elem == nullptr) 
		{
			cout << "Element was not found! \n";
			return;
		}
		cout << "Element was found! \n";
		return;
	}

	void swap_elem(int ind_1, int ind_2) 
										
	{
		member* p1, * p2; 
		member* prev_p1 = head;
		member* prev_p2 = head;
		member* next_p1, * next_p2;

		int k = 1; int k2 = 1;

		member* cur_elem = head; 
		if (ind_1 == 1) {
			prev_p1 = NULL; next_p1 = head->get_next(); p1 = head;
		}
		else {
			while (k < ind_1) 
			{
				cur_elem = cur_elem->get_next(); 
				if (cur_elem == nullptr) 
					break;
				k++;
			}

			p1 = cur_elem; 
			prev_p1 = cur_elem->get_prev(); 
			next_p1 = cur_elem->get_next(); 
		}


		member* cur_elem_2 = head; 

		if (ind_2 == 1) { 
			prev_p2 = NULL; next_p2 = head->get_next(); p2 = head;
		}
		else {
			while (k2 < ind_2) 
			{
				cur_elem_2 = cur_elem_2->get_next(); 
				if (cur_elem_2 == nullptr) 
					break;
				k2++;
			}
			p2 = cur_elem_2; 
			prev_p2 = cur_elem_2->get_prev(); 
			next_p2 = cur_elem_2->get_next();

		}

		if (p1->get_next() == p2 && p1 != head) { 

			p1->set_next(next_p2);
			p1->set_prev(p2);
			prev_p1->set_next(p2);
			p2->set_next(p1);
			p2->set_prev(prev_p1);
			next_p2->set_prev(p1);
		}

		else if (p2->get_next() == p1 && p2 != head) { 
			p2->set_next(p1->get_next());
			p2->set_prev(p1);
			prev_p2->set_next(p1);
			p1->set_next(p2);
			p1->set_prev(prev_p2);
			next_p1->set_prev(p2);
		}

		else if (p1 != head) { 
			p1->set_next(next_p2);
			next_p2->set_prev(p1);
			p1->set_prev(prev_p2);
			prev_p2->set_next(p1);


			p2->set_next(next_p1);
			next_p1->set_prev(p2);
			p2->set_prev(prev_p1);
			prev_p1->set_next(p2);
		}
		else if (p2 != head) { 
			p1->set_next(next_p2);
			next_p2->set_prev(p1);
			p1->set_prev(prev_p2);
			prev_p2->set_next(p1);


			p2->set_next(next_p1);
			next_p1->set_prev(p2);
			p2->set_prev(prev_p1);
			prev_p1->set_next(p2);
		}
	}

	void move_elem(int ind_1, int ind_2) 
	{
		if (head == nullptr)
			return;
		int k = 1; int k2=1;
		member* cur_elem = head; 
		while (k < ind_1) 
		{
			cur_elem = cur_elem->get_next(); 
			if (cur_elem == nullptr) 
				break;
			k++;
		}

		member* p1 = cur_elem; 
		member* prev_p1 = cur_elem->get_prev();
		member* next_p1 = cur_elem->get_next();
		
		
		if (ind_2 > count) 
		{
			cout << "Error! Not enough elements in list!\n";
			return;
		}
		

		member* cur_elem_2 = head; 
		while (k2 < ind_2) 
		{
			cur_elem_2 = cur_elem_2->get_next(); 
			if (cur_elem_2 == nullptr) 
				break;
			k2++;
		}

		member* p2 = cur_elem_2; 
		member* next_p2 = cur_elem_2->get_next();

		if (p1 != head) {
			p1->set_next(next_p2); 
			next_p1->set_prev(prev_p1);
			prev_p1->set_next(next_p1);
			p1->set_prev(p2);
			p2->set_next(p1);
			next_p2->set_prev(p1);
		}
	}

};

int main()
{
	group my_group;
	int elem_num;
	cout << "Input amount of members:";
	cin >> elem_num;

	member new_elem;
	for (int i = 0; i < elem_num; i++)
	{
		string name, surname, city;
		string after_name, after_surname, after_city;
		int index, index2;
		int operation = 0;

		cout << "Now we have " << my_group.count << " members\n";

		cout << "Insert name:" << endl;
		cin >> name;
		new_elem.set_name(name);
		cout << "Insert surname:" << endl;
		cin >> surname;
		new_elem.set_surname(surname);
		cout << "Insert city:" << endl;
		cin >> city;
		new_elem.set_city(city);

		cout << "Choose operation: \n\
1 - push_front\n\
2 - push_back\n\
3 - insert after index\n\
4 - insert after element\n\
5 - print\n\
6 - inverted print\n\
7 - delete first \n\
8 - delete last \n\
9 - count \n\
10 - delete element \n\
11 - delete element with index \n\
12 - find element \n\
13 - swap 2 elements\n\
14 - move element \n" ;
		cin >> operation;

		if (operation <= 0 || operation > 14)
		{
			cout << "Error! wrong operation! Insert 1-14 \n";
			i--;
			continue;
		}

		if (operation == 1) 
		{
			cout << "Operation --PUSH_FRONT-- IS CALLED:\n";
		}

		else if (operation == 2)
		{
			cout << "Operation --PUSH_BACK-- IS CALLED:\n";
		}

		else if (operation == 3)
		{
			cout << "Insert index:\n";
			cin >> index;
			cout << "Operation --INSERT TO PLACE-- IS CALLED:\n";
		}
		else if (operation == 4)
		{
			cout << "Insert after name:\n";
			cin >> after_name;
			cout << "Insert after  surname:\n";
			cin >> after_surname;
			cout << "Insert  after city:\n";
			cin >> after_city;
			cout << "Operation --INSERT AFTER ELEMENT-- IS CALLED:\n";
		}

		else if (operation == 5)
		{
			cout << "Operation --PRINT-- IS CALLES:\n";
		}

		else if (operation == 6)
		{
			cout << "Operation --INVERTED_PRINT-- IS CALLED:\n";
		}

		else if (operation == 7)
		{
			cout << "Operation --DELETE_FIRST-- IS CALLED:\n";
		}

		else if (operation == 8)
		{
			cout << "Operation --DELETE_LAST-- IS CALLED:\n";
		}

		else if (operation == 9)
		{
			cout << "Operation --COUNT_ELEMENTS-- IS CALLED:\n";
		}

		else if (operation == 10)
		{
			cout << "Insert name:\n";
			cin >> name;
			cout << "Insert surname:\n";
			cin >> surname;
			cout << "Insert city:\n";
			cin >> city;
		}

		else if (operation == 11)
		{
			cout << "Insert index: \n";
			cin >> index;
			cout << "Operation --DELETE_ELEMENT_WITH_INDEX-- IS CALLED:\n";
		}

		else if (operation == 12)
		{
			cout << "Operation --FIND_ELEMENT-- IS CALLED:\n";
		}
		
		else if (operation == 13)
		{
			cout << "Insert 1st index: \n";
			cin >> index;
			cout << "Insert 2nd index: \n";
			cin >> index2;
			cout << "Operation --SWAP 2 elems-- IS CALLED:\n";
		}

		else if (operation == 14)
		{
			cout << "Insert index: \n";
			cin >> index;
			cout << "Insert 2nd index: \n";
			cin >> index2;
		}


		if (operation == 1) {
			
			my_group.push_front(&new_elem);
			cout << "Member " << new_elem.get_name() << " " << new_elem.get_surname() << 
				" " << new_elem.get_city() << " in the list\n";
		}

		else if (operation == 2) {
			my_group.push_back(&new_elem);
			cout << "Member " << new_elem.get_name() << " " << new_elem.get_surname() << " "
				<< new_elem.get_city() << " in the list\n";
		}

		else if (operation == 3) {
			my_group.insert(index, &new_elem);
			cout << "Group after insert operation:\n";
			my_group.print(); }

		else if (operation == 4)
		{
			member after_elem;
			after_elem.set_name(after_name); 
			after_elem.set_surname(after_surname);
			after_elem.set_city(after_city);

			my_group.insert(after_elem, &new_elem); 
			cout << "Group after insert operation:\n";
			my_group.print();
		}

		else if (operation == 5)
		{
			my_group.print();
		}
		else if (operation == 6)
		{
			my_group.inverted_print();
		}

		else if (operation == 7)
		{
			my_group.delete_first();
			cout << "Group after delete operation:\n";
			my_group.print();
		}

		else if (operation == 8)
		{
			my_group.delete_last();
			cout << "Group after delete operation:\n";
			my_group.print();
		}

		else if (operation == 9)
		{
			my_group.count_elems();
		}

		else if (operation == 10)
		{
			member del_elem;
			del_elem.set_name(name);
			del_elem.set_surname(surname);
			del_elem.set_city(city);
			
			my_group.delete_elem(del_elem);

			cout << "Group after delete operation:\n";
			my_group.print();

		}
		else if (operation == 11)
		{
			my_group.delete_elem_ind(index);
			cout << "Group after insert operation:\n";
			my_group.print();

		}

		else if (operation == 12)
		{
			my_group.find_element(new_elem);
		}

		else if (operation == 13)
		{
			my_group.swap_elem(index, index2);
			cout << "Group after swap operation:\n";
			my_group.print();
		}

		else if (operation == 14)
		{
			my_group.move_elem(index, index2);
			cout << "Group after move operation:\n";
			my_group.print();
		}
	}
	
	my_group.print();
	return 0;
}