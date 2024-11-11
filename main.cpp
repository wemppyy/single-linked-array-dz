#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct BOOK {
private:
	string name;
	string author;
	struct date {
		int month;
		int year;
	} date;
	int cost;

	void set_default() {
		name = "Unknown";
		author = "Unknown";
		date.month = 0;
		date.year = 0;
		cost = 0;
		next = nullptr;
	}
public:
	BOOK* next;
	BOOK() {
		set_default();
	}
	BOOK(string name, string author, int month, int year, int cost) {
		this->name = name;
		this->author = author;
		this->date.month = month;
		this->date.year = year;
		this->cost = cost;
		next = nullptr;
	}

	string get_name() { return name; }
	string get_author() { return author; }
	int get_month() { return date.month; }
	int get_year() { return date.year; }
	int get_cost() { return cost; }

	~BOOK() {
		delete next;
	}
};

void push_back(BOOK* head, string name, string author, int month, int year, int cost) {
	BOOK* current = head;
	while (current->next != nullptr) {
		current = current->next;
	}
	current->next = new BOOK(name, author, month, year, cost);
}

void push_front(BOOK* head, string name, string author, int month, int year, int cost) {
	BOOK* new_head = new BOOK(name, author, month, year, cost);
	new_head->next = head->next;
	head->next = new_head;
}

void insert(BOOK* head, int index, string name, string author, int month, int year, int cost) {
	BOOK* current = head;
	for (int i = 0; i < index; i++) {
		if (current->next == nullptr) {
			cout << "Index out of range" << endl;
			return;
		}
		current = current->next;
	}
	BOOK* new_book = new BOOK(name, author, month, year, cost);
	new_book->next = current->next;
	current->next = new_book;
}

void remove(BOOK* head, int index) {
	BOOK* current = head;
	for (int i = 0; i < index; i++) {
		if (current->next == nullptr) {
			cout << "Index out of range" << endl;
			return;
		}
		current = current->next;
	}
	BOOK* temp = current->next;
	current->next = current->next->next;
	delete temp;
}

void remove_all(BOOK* head) {
	BOOK* current = head->next;
	while (current != nullptr) {
		BOOK* temp = current;
		current = current->next;
		delete temp;
	}
	head->next = nullptr;
}

void write_to_file(BOOK* head) {
	ofstream file("SHOP.dat");
	BOOK* current = head->next;
	while (current != nullptr) {
		file << current->get_name() << 
		 " " << current->get_author() << 
		 " " << current->get_month() << 
		 " " << current->get_year() << 
		 " " << current->get_cost() << endl;
		current = current->next;
	}
	file.close();
}

void read_file(BOOK* head) {
	ifstream file("SHOP.dat");
	remove_all(head);
	while (!file.eof()) {
		string name;
		string author;
		int month;
		int year;
		int cost;
		file >> name >> author >> month >> year >> cost;
		push_back(head, name, author, month, year, cost);
	}
}

void print(BOOK* head) {
	BOOK* current = head->next;
	while (current != nullptr) {
		cout << current->get_name() << " " << current->get_author() << " " << current->get_month() << " " << current->get_year() << " " << current->get_cost() << endl;
		current = current->next;
	}
}

void menu(BOOK* head) {
	while (true) {
		int choice;

		system("cls");
		cout << "1. Add book" << endl;
		cout << "2. Add book to the beginning" << endl;
		cout << "3. Insert book" << endl;
		cout << "4. Remove book" << endl;
		cout << "5. Remove all books" << endl;
		cout << "6. Write to file" << endl;
		cout << "7. Read from file" << endl;
		cout << "8. Print" << endl;
		cout << "9. Exit" << endl;

		cin >> choice;
		
		switch (choice)
		{
		case 1:
		{
			string name;
			string author;
			int month;
			int year;
			int cost;
			cout << "Enter name: ";
			cin >> name;
			cout << "Enter author: ";
			cin >> author;
			cout << "Enter month: ";
			cin >> month;
			cout << "Enter year: ";
			cin >> year;
			cout << "Enter cost: ";
			cin >> cost;
			push_back(head, name, author, month, year, cost);
			break;
		}
		case 2:
		{
			string name;
			string author;
			int month;
			int year;
			int cost;
			cout << "Enter name: ";
			cin >> name;
			cout << "Enter author: ";
			cin >> author;
			cout << "Enter month: ";
			cin >> month;
			cout << "Enter year: ";
			cin >> year;
			cout << "Enter cost: ";
			cin >> cost;
			push_front(head, name, author, month, year, cost);
			break;
		}
		case 3:
		{
			int index;
			string name;
			string author;
			int month;
			int year;
			int cost;
			cout << "Enter index: ";
			cin >> index;
			cout << "Enter name: ";
			cin >> name;
			cout << "Enter author: ";
			cin >> author;
			cout << "Enter month: ";
			cin >> month;
			cout << "Enter year: ";
			cin >> year;
			cout << "Enter cost: ";
			cin >> cost;
			insert(head, index, name, author, month, year, cost);
			break;
		}
		case 4:
		{
			int index;
			cout << "Enter index: ";
			cin >> index;
			remove(head, index);
			break;
		}
		case 5:
		{
			remove_all(head);
			system("pause");
			break;
		}
		case 6:
		{
			write_to_file(head);
			system("pause");
			break;
		}
		case 7:
		{
			read_file(head);
			system("pause");
			break;
		}
		case 8:
		{
			print(head);
			system("pause");
			break;
		}
		case 9:
		{
			delete head;
			return;
		}
		default:
			break;
		}
	}
}


int main() {
	BOOK* head = new BOOK();
	menu(head);

	return 0;
}
