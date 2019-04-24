// Реализуем систему скриптов

#ifndef SCRIPTING_H
#define SCRIPTING_H
#include "cstdio" // для FILE
#include <iostream>
#include <list>
#include "Linked_List.h"

// Объявляем перечисление (набор именованных констант - список перечислителей)
enum Variable_list {VARIABLE_BOOL, VARIABLE_FLOAT, VARIABLE_NUMBER, VARIABLE_STRING,
        VARIABLE_VECTOR, VARIABLE_UNKNOWN, VARIABLE_COLOUR};

struct D3DCOLORVALUE
{
    float r;
    float g;
    float b;
    float a;
};

typedef struct D3DXVECTOR3
{
    float x;
    float y;
    float z;
} D3DXVECTOR3;

class Variable
{
public:
    Variable(char *name, FILE *file); //конструктор, в котором FILE *file -
    // указатель на экземпляр структуры, которая содержит данные для открытого файла
    // вызывается при извлечении скриптовых переменных из текстового файла скрипта
    Variable(char *name, char type, void *value); // когда файл скрипта создается с нуля
    virtual ~Variable(); // деструктор

    // Для доступа к переменным, хранящих тип, имя и данные переменной
    char Get_Type();
    char *Get_Name();
    void *Get_Data();

private:
    char v_type; // тип данных, которые хранятся в переменной
    char *v_name; // имя переменной
    void *v_data; // данные, которые хранятся в переменной.
};

class Script: public Resource <Script> // наследование?
{
public:
    Script(char *name, char *path = "./"); // скрипты будут искаться в каталоге игры по дефолту
    virtual ~Script();

    void Add_Variable(char *name, char type, void *value);
    void Set_Variable(char *name, void *value);

    void Save_Script(char *filename = NULL);

    bool *Get_Bool_Data(char *variable);
    D3DCOLORVALUE *Get_Colour_Data(char *variable);
    float *Get_Float_Data(char *variable);
    long *Get_Number_Data(char *variable);
    char *Get_String_Data(char *variable);
    D3DXVECTOR3 *Get_Vector_Data(char *variable); // ? надо что-то включить
    void *Get_Unknown_Data(char *variable);

private:
    Linked_List <Variable> *variables; // cвязный список переменных в скрипте (!!!)
};

#endif
