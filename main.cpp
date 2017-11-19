#include <iostream>
using namespace std;
 
//Класс Очередь головой и хвостом
template<class T>
class xQueue {
	struct node 
	{
		T d;
		node* next;
	};
	private:
	node*  ptr;
	public:
	xQueue(void) : ptr(NULL){}//конструктор по умолчанию
	
//Деструктор
	~xQueue() 
	{
		this->clear();
	}

//Добавление элемента в конец очереди (в хвост)
	public:
	void  push(T d) 
	{
		node* e = new node();
		e->d = d;
		if(! ptr) 
		{
			ptr = e;
			ptr->next = ptr;
		} 
		else 
		{
			e->next = ptr->next;
			ptr = ptr->next = e;
		}
	}

//получить значение первого элемента (на выходе)
	T& front(void) 
	{
		return ptr->next->d;
	}

//Извлечение элемента из начала очереди (из головы)
	void  pop(void) 
	{
		if(ptr == ptr->next) 
		{
			delete ptr;
			ptr = NULL;
			return;
		}
		node* tmp = ptr->next;
		ptr->next = tmp->next;
		delete tmp;
		tmp = NULL;
	}

//Кол-во элементов
	size_t  size(void) const 
	{
		size_t cnt = 0u;
		const node* iter = ptr->next;
		do 
		{
			cnt++;
			iter = iter->next;
		} 
		while(iter != ptr->next);
		return cnt;
	}
 
//Проверка на пустоту очереди
	bool empty(void) const 
	{
		return (! ptr);
	}

//Очистка очереди
	void clear(void) 
	{
		while(! this->empty())
		this->pop();
	}

//Сортировка бинарными вставками
	void sort_bin_insert ()
	{
		T *mas,x;
		int count=size();
		mas=new T[count];
		int i=0;
		while(! empty()) 
		{  // читаем очередь от первого до последнего элемента
			mas[i]=front();
			i++;
			pop();
		}
		int left, right, sred;
		for (int i=1; i<count; i++)
		{
			if (mas[i-1]>mas[i]) 
			{   
				x=mas[i];      // x – включаемый элемент
				left=0;       // левая граница отсортированной части массива
				right=i-1;    // правая граница отсортированной части массива 
				do 
				{
					sred = (left+right)/2;      // sred – новая "середина" последовательности
					if (mas[sred]<x )   left= sred+1;
					else right=sred-1;
				} 
				while (left<=right);     // поиск ведется до тех пор, пока левая граница не окажется правее правой границы
				for (int  j=i-1;   j>=left;   j--) mas[j+1]= mas[j];
				mas[left]= x;
			}
		}
		for (int i=0; i<count; i++)
			push(mas[i]);
	}
};

 //Точка входа
void main() {
	setlocale(LC_ALL,"Rus");
  xQueue<double> q;
  char number;
  do
	{
		system("cls");
		cout<<"1. Добавить элемент"<<endl;
		cout<<"2. Удалить элемент"<<endl;
		cout<<"3. Вывести верхний элемент"<<endl;
		cout<<"4. Узнать размер очереди"<<endl;
		cout<<"5. Отсортировать очередь"<<endl;
		cout<<"6. Вывести на экран все элементы очереди"<<endl;
		cout<<"7. Обнулить очередь"<<endl;
		cout<<"0. Выйти\n\n";
		cout<<"Номер команды > "; cin>>number;
		switch (number)
		{
			case '1':
				double num;
				cout<<"Введите число:";
				cin>>num;
				q.push(num);
			break;
			//-----------------------------------------------
			case '2':
				if (q.empty()) 
				{
					cout<<endl<<"Очередь пуста\n\n";
				}
				else 
				{
					q.pop();
				}
			break;
			//-----------------------------------------------
			case '3':
				if (q.empty()) 
				{
					cout<<endl<<"Очередь пуста\n\n";
				}
				else 
				{
					cout<<q.front()<<"\n";
				}
				system("pause");
			break;
			//-----------------------------------------------
			case '4':
			if (q.empty()) 
				{
					cout<<endl<<"Очередь пуста\n\n";
					system("pause");
				}
				else 
				{
					cout<<q.size()<<"\n";
				}
			system("pause");
			break;
			case '5':
			if (q.empty()) 
				{
					cout<<endl<<"Очередь пуста\n\n";
					system("pause");
				}
				else 
				{
					system("cls");
					q.sort_bin_insert();
				}
			break;
			case '6':
			if (q.empty()) 
				{
					cout<<endl<<"Очередь пуста\n\n";
				}
				else 
				{
					xQueue<double> temp;
					system("cls");
					while (!q.empty())
					{
						cout<<q.front()<<"\n";
						temp.push(q.front());
						q.pop();
					}
					while (!temp.empty())
					{
						q.push(temp.front());
						temp.pop();
					}
				}
				system("pause");
			break;
			case '7':
			if (q.empty()) 
				{
					cout<<endl<<"Очередь уже пуста\n\n";
					system("pause");
				}
				else 
				{
					q.clear();
				}
			break;
			//-----------------------------------------------
			case '0': break;
			default: cout<<endl<<"Команда не определена\n\n";
			break;
		}
	} 
	while(number!='0');
}