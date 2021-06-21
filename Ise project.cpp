#include<iostream>
#include<iostream>
#include<fstream>
using namespace std;

class Helper{
public:
	static int StringLength(char* str){
		int str_length = 0;
		for(int i=0 ; str[i]!='\0' ; i++)
			str_length++;
		return str_length;
	}

	static char* GetStringFromBuffer(char* str){
		char* Name = 0;
		int Name_Len = StringLength(str);
		if(Name_Len > 0){
			Name = new char[Name_Len + 1];
			char* tempDest = Name;
			for(char* tempSrc = str; *tempSrc != '\0'; tempSrc++, tempDest++)
				*tempDest = *tempSrc;
			*tempDest = '\0';
		}
		return Name;
	}

};


class Book{
private:
	int Type;
	char* Name;
	char* Author;
	int Availability;
	
public:
	Book(){
		Type = 0;
		Name = 0;
		Author = 0;
		Availability=0;
	}

	void LoadBooks(ifstream& fin){
				Availability=1;
				fin >> Type;
				char name[30];
				fin.ignore();
				fin.getline(name,30);
				Name = Helper::GetStringFromBuffer(name);
				char author[30];
				fin.getline(author,30);
				Author = Helper::GetStringFromBuffer(author);
		
		}

	void InputBooks(){
		cout << "\nEnter type of a book (any integer):\t";
		cin >> Type;
		cin.ignore();
		cout << "\nEnter name of a book:\t";
		char name1[30];
		cin.getline(name1,30);
		Name = Helper::GetStringFromBuffer(name1);
		cout<<"\nEnter author of a book:\t";
		char author1[30];
		cin.getline( author1,30 );
		Author = Helper::GetStringFromBuffer(author1);
	}

	void Print(){
		cout<<"\n"<<Type<<"\t"<<Name<<"\t"<<Author;
	}

	int GetType(){
		return Type;
	}

	int GetAvailabilty()
	{
		return Availability;
	}

	void SetAvailabilty(int a)
	{
		Availability =a;
	}

};


class Librarian{
private:
	char* Name;
	char* password;
	Book** BookList;
	static int TotalBooks;
	static int Q;
	Book** IssuedBooks;
public:
	int login(){
		char fixname[5] = "user";
		char _name[10];
		cout<<"Enter UserName:\t";
		cin >> _name ;
		Name = Helper::GetStringFromBuffer(_name);
		for(int i=0 ; Name[i]!='\0' ; i++){
			if(Name[i] != fixname[i]){
				cout<< "No user found\n";
				return 0;
			}
			else 
				continue;
		}

		cout<< "Enter password:\t";
		char fixPassword[7] ="1234";
		char _password[10];
		cin >> _password;
		password = Helper::GetStringFromBuffer(_password);
		for(int i=0 ; password[i]!='\0' ; i++){
			if(password[i] != fixPassword[i]){
				cout<< "Wrong Password\n";
				return 0;
			}
		}
		cout<<"\n\n\t\tACCOUNT SUCCESSFULLY LOGED IN\n";
		return 1;
	}

	void LoadBookList(){
		ifstream fin("Books.txt");
		fin>>TotalBooks;
		BookList = new Book*[50];
		for(int i=0 ; i<50 ;i++)
			BookList[i] = new Book;
		IssuedBooks= new Book*[50];
		for(int i=0 ; i<50 ;i++)
			IssuedBooks[i] = new Book;
		for(int i=0 ; i<TotalBooks ;i++){
			BookList[i] -> LoadBooks(fin);
		}
	}

	void PrintAll(){
		for(int i=0 ; i<TotalBooks ;i++){
				BookList[i] -> Print();
		}
	}

	void PrintIssuedBooks(){
		for(int i=0 ; i<Q ;i++){
			IssuedBooks[i] -> Print();
		}
	}

	void Remove(){
		int type;
		cout<<"Enter type of a book which you wants to remove:\t";
		cin >> type;
		for(int i=0 ; i<TotalBooks ;i++){
			if(type == BookList[i] -> GetType()){
				BookList[i]--;
				while(i!=TotalBooks){
					BookList[i] = BookList[i+1];
					i++;
				}
				TotalBooks--;
				break;
			}
		}
		cout<<"\n\n\t\tSUCCESSFULLY REMOVED \n";
	}

	void Add(){
		cout << "How many books you wants to stock in:\t";
		int num;
		cin >> num;
		num = num + TotalBooks;
		for(int i=TotalBooks ; i<num ;i++){
			BookList[i] -> InputBooks();
			TotalBooks++;
		}
		cout<<"\n\t\tSUCCESSFULLY ADDED\n";
	}

	void Edit(){
		cout<<"Enter type of a book which you wants to edit:\t";
		int type;
		cin >> type;
		for(int i=0 ; i<TotalBooks ;i++){
			if(type == BookList[i] -> GetType()){
				cout << "Edit the book\n";
				BookList[i] -> InputBooks();
			}
		}
	}
	
	void SetIssuedBook(Book* book)
	{
		IssuedBooks[Q]=book;
		Q++;
	}

	void SetIssuedBookreturn(int type)
	{
		for(int i=0 ; i<Q ;i++){
			if(IssuedBooks[i]->GetType()==type)
			{
				IssuedBooks[i]--;
				while(i!=Q){
					BookList[i] = BookList[i+1];
					i++;
				}
				Q--;
			}
		}
	}
};
int Librarian::TotalBooks = 0;
int Librarian::Q = 0;


class User{
private:
	char* Name;
	char* password;
	Book** BookList;
	static int TotalBooks;
public:
	int login(){
		char fixname[5] = "user";
		char _name[10];
		cout<<"Enter UserName:\t";
		cin >> _name ;
		Name = Helper::GetStringFromBuffer(_name);
		for(int i=0 ; Name[i]!='\0' ; i++){
			if(Name[i] != fixname[i]){
				cout<< "No user found\n";
				return 0;
			}
			else 
				continue;
		}

		cout<< "Enter password:\t";
		char fixPassword[7] ="1234";
		char _password[10];
		cin >> _password;
		password = Helper::GetStringFromBuffer(_password);
		for(int i=0 ; password[i]!='\0' ; i++){
			if(password[i] != fixPassword[i]){
				cout<< "Wrong Password\n";
				return 0;
			}
		}
		cout<<"\n\n\t\tACCOUNT SUCCESSFULLY LOGED IN\n";
		return 1;
	}
	
	void SignUp(){
		cout << "\nUser Name:\t";
		char _name[10];
		cin >> _name ;
		Name = Helper::GetStringFromBuffer(_name);
		cout << "\nPassword:\t";
		char _password[10];
		cin >> _password;
		password = Helper::GetStringFromBuffer(_password);
		cout<<"\n\n\t\tACCOUNT SUCCESSFULLY SIGNED UP\n";
	}

	void LoadBookList(){
		ifstream fin("Books.txt");
		fin>>TotalBooks;
		BookList = new Book*[50];
		for(int i=0 ; i<50 ;i++)
			BookList[i] = new Book;
		for(int i=0 ; i<TotalBooks ;i++){
			BookList[i] -> LoadBooks(fin);
		}
	}

	void PrintAll(){
		for(int i=0 ; i<TotalBooks ;i++){
				BookList[i] -> Print();
		}
	}
	
	Book* issue(){
		int type;
		int check;
		cout<<"\nEnter type of a book which you wants to issue:\t";
		cin >> type;
		for(int i=0 ; i<TotalBooks ;i++){
			if(type == BookList[i] -> GetType()){
				if(1==BookList[i] ->GetAvailabilty())
				{
					BookList[i] ->SetAvailabilty(2);
					cout << "\nBOOK IS SUCCESSFULLY ISSUED\n";
					return BookList[i];

				}
				else
				{
					cout << "\nBOOK IS NOT AVAILALBLE\n";
				}
				break;
			}
			if(i==TotalBooks-1)
				cout<<"\nSORRY NO BOOK WITH SUCH TYPE\n";
		}
	}
	
	int returned(){
		int type;
		cout<<"\nEnter type of a book which you wants to return:\t";
		cin >> type;
		for(int i=0 ; i<TotalBooks ;i++){
			if(type == BookList[i] -> GetType()){
				if(2==BookList[i] ->GetAvailabilty())
				{
					BookList[i] ->SetAvailabilty(1);
					cout << "\nBOOK IS SUCCESSFULLY RETURNED\n";
					return BookList[i]->GetType();
				}
				else
				{
					cout << "\nBOOK WAS NOT ISSUED CANNOT BE RETURNED\n";
				}
				break;
			}
			if(i==TotalBooks-1)
				cout<<"\nSORRY NO BOOK WITH SUCH TYPE\n";
		}
	}
};
int User::TotalBooks = 0;





void main(){

		int choose=0;
		Librarian l;
		User u;
		Book* book;
		Book* book1;
		u.LoadBookList();
		l.LoadBookList();
		for(int U=0; choose!=3; U++)
		{
			cout << "Enter 1 for Librarian and 2 for User and 3 to Exit\n";
			cin >> choose;
			if(choose == 1 ){
				cout << "Hey Librarian please log in your account\n";
				int a = l.login();
				if(a == 0 )
					system("pause");
				else{
					cout<<"Book List:\n";
					l.PrintAll();
					int choose2;
					do{
						cout<<"\nEnter 1 to Add Book in the system\nEnter 2 to Remove Book from the system\nEnter 3 to edit the books\nEnter 4 to view issued books\nEnter 5 to Exit\n";
						cin>>choose2;
						if(choose2 == 1){
							l.Add();
							cout<<"Book List:\n";
							l.PrintAll();
						}
						else if(choose2 == 2){
							l.Remove();
							cout<<"Book List:\n";
							l.PrintAll();
						}
						else if(choose2 == 3){
							l.Edit();
							cout<<"Book List:\n";
							l.PrintAll();
						}
						else if(choose2 == 4){
							cout<<"Issued Book List:\n";
							l.PrintIssuedBooks();
						}
					}while(choose2!=5);
				}
			}
			if(choose == 2){
				cout << "Enter 1 to SIGN UP\nEnter 2 to LOG IN\n";
				int choose3;
				cin >> choose3;
				if(choose3 == 1){
					u.SignUp();
					cout << "Enter I to issue a book\nEnter R to return a book\n";
					char abc;
					cin >> abc;
					cout<<"Book List:\n";
					u.PrintAll();
					if(abc == 'I'){
						book=u.issue();
						l.SetIssuedBook(book);

					}
					else if(abc == 'R'){
						int type=u.returned();
						l.SetIssuedBookreturn(type);
					}
				}
				if(choose3 == 2){
					int b = u.login();
					if(b == 0 )
						system("pause");
					else{
						cout<<"Book List:\n";
						cout << "Enter I to issue a book\nEnter R to return a book\n";
						char abc;
						cin >> abc;
						cout<<"Book List:\n";
						u.PrintAll();
						if(abc == 'I'){
							book=u.issue();
							l.SetIssuedBook(book);
						}
						else if(abc == 'R'){
							int type=u.returned();
							l.SetIssuedBookreturn(type);
						}
					}
				}
			}
		}
		cout<<"The Libarary is closed now"<<endl;

		system("pause");
}
