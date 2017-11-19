#pragma once

//Класс Очередь головой и хвостом
template<class T>
class xQueue 
{
	struct node
	{
		T d;
		node* next;
	};

private:
	node*  ptr;

public:
	xQueue(void) : ptr(nullptr) {}//конструктор по умолчанию

							   //Деструктор
	~xQueue()
	{
		this->clear();
	}

public:
	//Добавление элемента в конец очереди (в хвост)
	void  push(T d)
	{
		node* e = new node();
		e->d = d;
		if (!ptr)
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
		if (ptr == ptr->next)
		{
			delete ptr;
			ptr = nullptr;
			return;
		}
		node* tmp = ptr->next;
		ptr->next = tmp->next;
		delete tmp;
		tmp = nullptr;
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
		} while (iter != ptr->next);
		return cnt;
	}

	//Проверка на пустоту очереди
	bool empty(void) const
	{
		return (!ptr);
	}

	//Очистка очереди
	void clear(void)
	{
		while (!this->empty())
			this->pop();
	}
};

