#ifndef LINKED_LIST_H
#define LINKED_LIST_H

template< class Type > class Linked_List
{
public:
struct Element
{
Type *data; //  указатель на данные, содержащиеся в элементе
Element *next; // указатель на следующий элемент в списке
Element *prev; // указатель на предыдущий элемент в списке

// Конструктор структуры элемент
Element(Type *element)
{
data = element;
next = prev = NULL;
}

// Деструктор структуры элемент
~Element()
{
SAFE_DELETE(data);

if (next)
next->prev = prev;
if (prev)
prev->next = next;
}
};

// Конструктор класса Linked_List
Linked_List()
{
e_first = e_last = e_iterate = e_temp = NULL;
total_elements = 0;
}

// Деструктор класса Linked_List
~Linked_List()
{
Empty();
}

// Добавляет данный элемент в конец списка
Type *Add(Type *element)
{
if (element == NULL)
return NULL;

if (e_first == NULL)
{
e_first = new Element(element);
e_last = e_first;
}
else
{
e_last->next = new Element(element);
e_last->next->prev = e_last;
e_last = e_last->next;
}

total_elements++;

return v_last->data;
}

// Вставляет данный элемент в связный список сразу перед next_element
Type *InsertBefore(Type *element, Element *next_element)
{
e_temp = next_element->prev;

total_elements++;

if (e_temp == NULL)
{
e_first = new Element(element);
e_first->next = next_element;
next_element->prev = e_first;

return e_first->data;
}
else
{
e_temp->next = new Element(element);
e_temp->next->prev = e_temp;
e_temp->next->next = next_element;
next_element->prev = e_temp->next;

return e_temp->next->data;
}
}

// Удаляет данный элемент из списка и уничтожает его данные
void Remove(Type **element)
{
e_temp = e_first;
while (e_temp != NULL)
{
if (e_temp->data == *element)
{
if (e_temp == e_first)
{
e_first = e_first->next;
if (e_first)
e_first->prev = NULL;
}
if (e_temp == e_last)
{
e_last = e_last->prev;
if (e_last)
e_last->next = NULL;
}

SAFE_DELETE(e_temp);
*element = NULL;
total_elements--;
return;
}
e_temp = e_temp->next;
}
}

// Удаляет все элементы связного списка вместе с их данными
void Empty()
{
while (e_last != NULL)
{
e_temp = e_last;
e_last = e_last->prev;
SAFE_DELETE(e_temp);
}
e_first = e_last = e_iterate = e_temp = NULL;
total_elements = 0;
}

// Убирает все элементы связного списка вместе с указателями
// (не уничтожает данные, содержащиеся в элементах)
void ClearPointers()
{
while (e_last != NULL)
{
e_temp = e_last;
e_temp->data = NULL;
e_last = e_last->prev;
SAFE_DELETE(e_temp);
}
e_first = e_last = e_iterate = e_temp = NULL;
total_elements = 0;
}

// Удаляет данный элемент списка и очищает указатель на него
// (не уничтожает данные, содержащиеся в данном элементе)
void ClearPointer(Type **element)
{
e_temp = e_first;
while(e_temp != NULL)
{
if (e_temp->data == *element)
{
if (e_temp == e_first)
{
e_first = e_first->next;
if (e_first)
e_first->prev = NULL;
}
if (e_temp == e_last)
{
e_last = e_last->prev;
if (e_last)
e_last->next = NULL;
}
e_temp->data = NULL;
SAFE_DELETE(e_temp);
*element = NULL;
total_elements--;
return;
}
e_temp = e_temp->next;
}
}

// Итерация (сканирование) каждого элемента в списке
Type *Iterate(bool restart = false)
{
if (restart)
e_iterate = NULL;
else
{
if (e_iterate == NULL)
e_iterate = e_first;
else
e_iterate = e_iterate->next;
}

if (e_iterate == NULL)
return NULL;
else
return e_iterate->data;
}

// Возвращает элемент связного списка, итерируемый в данный момент
Type *GetCurrent()
{
if (e_iterate)
return e_iterate->data;
else
return NULL;
}

// Возвращает первый элемент связного списка
Type *GetFirst()
{
if (e_first)
return e_first->data;
else
return NULL;
}

// Возвращает последний элемент связного списка
Type *GetLast()
{
if (e_last)
return e_last->data;
else
return NULL;
}

// Возвращает элемент связного списка, следующий за данным
Type *GetNext(Type *element)
{
e_temp = e_first;
while (e_temp != NULL)
{
if (e_temp->data == element)
{
if (e_temp->next == NULL)
return NULL;
else
return e_temp->next->data;
}

e_temp = e_temp->next;
}
return NULL;
}

// Возвращает случайный элемент связного списка
Type *GetRandom()
{
if (total_elements == 0)
return NULL;
else if (total_elements == 1)
return e_first->data;
unsigned long element = rand()*total_elements/RAND_MAX;
e_temp = e_first;
for (unsigned long e = 0; e < element; e++)
e_temp = e_temp->next;
return metemp->data;
}

// Возвращает полный элемент списка
Element *GetCompleteElement(Type *element)
{
e_temp = e_first;
while (e_temp != NULL)
{
if (e_temp->data == element)
return e_temp;
e_temp = e_temp->next;
}
return NULL;
}

// Возвращает число элементов в связном списке
unsigned long GetTotalElements()
{
return total_elements;
}

private:
Element *e_first; // первый элемент связного списка
Element *e_last; // последний элемент связного списка
Element *e_iterate; // используется для итерации связного списка
Element *e_temp; // используется как временное хранилище при различных операциях

unsigned long total_elements; // общее количество элементов в связном списке
};

#endif
#ifndef LINKED_LIST_H
#endif
