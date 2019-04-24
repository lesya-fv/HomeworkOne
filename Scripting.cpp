// Реализуем классы и функции, объявленные в Scripting.h

#include "Scripting.h"
#include "stdio.h" // для FILENAME_MAX
#include "cstring" // для strlen и других
#include "cstdlib" // для atof
#include <iostream>
#include <string>

using std::string;

string Get_File_Name(const string& s)
{
    char sep = '/';

#ifdef _WIN32
    sep = '\\';
#endif

    size_t i = s.rfind(sep, s.length());
    if (i != string::npos) {
        return(s.substr(i+1, s.length() - i));
    }

    return("");
}

int main(int argc, char** argv) {

    string path = argv[1];

    std::cout << "The file name is \"" << Get_File_Name(path) << "\"\n";
}


// Конструктор 1 класса Variable (готовим переменные для Script)
Variable::Variable(char *name, FILE *file)
{
    v_name = new char[strlen(name) + 1]; // сохраним имя переменной;
                                        // функция strlen() возвращает
                                        // длину строки, оканчивающейся
                                        // нулевым символом, на которую
                                        // указывает str
    strcpy(v_name, name); // копируем name в v_name

    if (file == NULL) // проверим, что указатель на файл существует
        return;

    // Определим тип переменной
    char buffer[FILENAME_MAX]; // выделяем память под макс. длинную строку в файле
    fscanf(file, "%s", buffer); // определяем число аргументов,
                                // которым были присвоены значения
    if (strcmp(buffer, "bool") == 0) // если buffer - это bool
    {
        v_type = VARIABLE_BOOL;

        // Устанавливаем значение переменной
        bool value;
        fscanf(file, "%s", buffer);
        if (strcmp(buffer, "true") == 0)
            value = true;
        else
            value = false;
        v_data = new bool; // ?
        memcpy(v_data, &value, sizeof(bool)); // копируем v_data в &value
    }
    else if (strcmp(buffer, "colour") == 0 )
    {
        v_type = VARIABLE_COLOUR;

        // Устанавливаем переменную цвет
        D3DCOLORVALUE colour;
        fscanf(file, "%s", buffer);
        colour.r = (float)atof(buffer); // преобразуем строку в double
        fscanf(file, "%s", buffer);
        colour.g = (float)atof(buffer);
        fscanf(file, "%s", buffer);
        colour.b = (float)atof(buffer);
        fscanf(file, "%s", buffer);
        colour.a = (float)atof(buffer);
        v_data = new D3DCOLORVALUE;
        memcpy(v_data, &colour, sizeof(D3DCOLORVALUE));
    }
    else if(strcmp(buffer, "float") == 0)
    {
        v_type = VARIABLE_FLOAT;

        // Устанавливаем переменную типа float.
        float value;
        fscanf(file, "%s", buffer);
        value = (float)atof(buffer);
        v_data = new float;
        memcpy(v_data, &value, sizeof(float));
    }
    else if (strcmp(buffer, "number") == 0)
    {
        v_type = VARIABLE_NUMBER;

        // Устанавливаем целочисленную переменную
        long value;
        fscanf(file, "%s", buffer);
        value = atol(buffer); // конвертирует строку
                                // в целое число типа long
        v_data = new long;
        memcpy(v_data, &value, sizeof(long));
    }
    else if (strcmp(buffer, "string") == 0)
    {
        v_type = VARIABLE_STRING;

        // Ищем открывающие обратные слэши (начало блока переменных).
        bool Commas_Found = false;
        buffer[FILENAME_MAX*sizeof(char)] = {0}; // заполняем память
                                                // структуры нулями
        fscanf(file, "%c", buffer);
        while(true)
        {
            if (strcmp(buffer, "\"") == 0)
            {
                Commas_Found = true;
                break;
            }

            if (strcmp(buffer, " ") != 0)
            {
                fpos_t pos; // информация для указания позиции в файле
                fgetpos(file, &pos);
                fsetpos(file, &pos);
                break;
            }

            fscanf(file, "%c", buffer);
        }

        // Устанавливаем переменную string
        char Complete_String[FILENAME_MAX];
        Complete_String[FILENAME_MAX*sizeof(char)] = {0};
        bool Add_Spacing = false;
        do
        {
            fscanf(file, "%s", buffer);
            if (strcmp(&buffer[strlen(buffer) - 1], "\"") == 0)
            {
                buffer[strlen(buffer) - 1] = 0;
                Commas_Found = false;
            }

            if (Add_Spacing == false)
                Add_Spacing = true;
            else
                strcat(Complete_String, " "); // соединяем 2 строки + 0 в конце

            strcat(Complete_String, buffer);
        } while(Commas_Found == true);

        v_data = new char[strlen(Complete_String) + 1];
        strcpy((char*)v_data, Complete_String);
    }
    else if (strcmp(buffer, "vector") == 0)
    {
        v_type = VARIABLE_VECTOR;

        // Устанавливаем переменную vector
        D3DXVECTOR3 vector;
        fscanf(file, "%s", buffer);
        vector.x = (float)atof(buffer);
        fscanf(file, "%s", buffer);
        vector.y = (float)atof(buffer);
        fscanf(file, "%s", buffer);
        vector.z = (float)atof(buffer);
        v_data = new D3DXVECTOR3;
        memcpy(v_data, &vector, sizeof(D3DXVECTOR3));
    }
    else
    {
        v_type = VARIABLE_UNKNOWN;

        fscanf(file, "%s", buffer);
        v_data = new char[strlen(buffer) + 1];
        strcpy((char*)v_data, buffer);
    }
}

// Конструктор 2 класса Variable
Variable::Variable(char *name, char type, void *value)
{
    v_name = new char[strlen(name) + 1];
    strcpy(v_name, name);

    v_type = type;

    // В зависимости от типа переменной установим ее данные
    switch(v_type)
    {
        case VARIABLE_BOOL:
            v_data = new bool;
            memcpy(v_data, (bool*)value, sizeof(bool));
            return;

        case VARIABLE_COLOUR:
            v_data = new D3DCOLORVALUE;
            memcpy(v_data, (D3DCOLORVALUE*)value, sizeof(D3DCOLORVALUE));
            return;

        case VARIABLE_FLOAT:
            v_data = new float;
            memcpy(v_data, (float*)value, sizeof(float));
            return;

        case VARIABLE_NUMBER:
            v_data = new long;
            memcpy(v_data, (long*)value, sizeof(long));
            return;

        case VARIABLE_STRING:
            v_data = new char[strlen((char*)value) + 1];
            strcpy((char*)v_data, (char*)value);
            return;

        case VARIABLE_VECTOR:
            v_data = new D3DXVECTOR3;
            memcpy(v_data, (D3DXVECTOR3*)value, sizeof(D3DXVECTOR3));
            return;

        default:
            v_data = new char[strlen((char*)value) + 1];
            strcpy((char*)v_data, (char*)value);
            return;
    }
}

// Деструктор класса Variable

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) {if(p) {delete (p); (p) = NULL;}}
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) {if(p) {delete[] (p); (p) = NULL;}}
#endif

Variable::~Variable()
{
    SAFE_DELETE_ARRAY(v_name);
    SAFE_DELETE(v_data);
}

// Возращаем тип, имя, данные переменной

char Variable::Get_Type()
{
    return v_type;
}

char *Variable::Get_Name()
{
    return v_name;
}

void *Variable::Get_Data()
{
    switch(v_type)
    {
        case VARIABLE_BOOL:
            return (bool*)v_data;

        case VARIABLE_COLOUR:
            return (D3DCOLORVALUE*)v_data;

        case VARIABLE_FLOAT:
            return (float*)v_data;

        case VARIABLE_NUMBER:
            return (long*)v_data;

        case VARIABLE_STRING:
            return (char*)v_data;

        case VARIABLE_VECTOR:
            return (D3DXVECTOR3*)v_data;

        default:
            return v_data;
    }
}

// Конструктор класса Script
Script::Script(char *name, char *path): Resource <Script>(name, path +)
{
    // Создаём связный список, в котором будут храниться все переменные скрипта
    variables = new Linked_List<Variable>;

    // Открываем скрипт, указываем имя его файла (filename)
    FILE *file = NULL;
    if ((file = fopen(Get_File_Name(path), "r")) == NULL)
        return;

    // Продолжаем чтение файла, пока не достигнем конца
    bool read = false;
    char buffer[FILENAME_MAX];
    fscanf(file, "%s", buffer);
    while(feof(file) == 0) // макросом feof() контролируется указатель положения в файле
    {
        // Проверяем, находится ли индикатор позиции файла между тегами #begin и #end
        // Если да, то читаем данные в связный список переменных
        if (read == true)
        {
            // Останавливаем чтение данных, если встретили #end.
            if (strcmp(buffer, "#end") == 0)
                read = false;
            else
                variables->Add(new Variable(buffer, file));
        }
        else if (strcmp(buffer, "#begin") == 0)
            read = true;

        fscanf(file, "%s", buffer); // читаем следующую строку
    }
    fclose(file); // закрываем файл скрипта
}

// Деструктор скрипта
Script::~Script()
{
    SAFE_DELETE(variables);
}

void Script::Add_Variable(char *name, char type, void *value) // добавляет новую переменную в скрипт
{
    variables->Add(new Variable(name, type, value));
}

void Script::Set_Variable(char *name, void *value) // устанавливает значение существующей переменной в скрипте
{
    // В поисках переменной:
    Variable *variable = NULL;
    variables->Iterate(true);
    while(variables->Iterate() != NULL)
    {
        if (strcmp(variables->GetCurrent()->GetName(), name) == 0)
        {
            variable = variables->GetCurrent();
            break;
        }
    }

    // Вдруг переменная не нашлась:
    if (variable == NULL)
        return;

    char type = variable->Get_Type(); // получаем тип переменной

    variables->Remove(&variable);  // удаляем переменную

    Add_Variable(name, type, value); // добавляем переменную на прежнее место с новым значением
}

// Сохраняет скрипт в файл
void Script::Save_Script(char *filename)
{
    FILE *file = NULL;
    char output[FILENAME_MAX];

    // Открываем указанное имя файла, если таковое имеется, или используем внутреннее имя файла
    if (filename != NULL)
    {
        if ((file = fopen(filename, "w")) == NULL)
            return;
    }
    else
    {
        if ((file = fopen(Get_File_Name(filename), "w")) == NULL)
            return;
    }

    fputs("#begin\n", file); // пишем тег #begin в файл

    // Пишем каждую переменную в файл
    variables->Iterate(true);
    while (variables->Iterate() != NULL)
    {
        switch(variables->GetCurrent()->GetType())
        {
            case VARIABLE_BOOL:
                if (*((bool*)variables->GetCurrent()->GetData()) == true)
                    sprintf(output, "%s bool true", variables->GetCurrent()->GetName()); // вернет число символов, занесенных в массив
                else
                    sprintf(output, "%s bool false", variables->GetCurrent()->GetName());
                fputs(output, file); // записывает строку в поток
                fputs("\n", file);
                continue;

            case VARIABLE_COLOUR:
                sprintf(output, "%s colour %f %f %f %f", variables->GetCurrent()->GetName(),
                        ((D3DCOLORVALUE*)variables->GetCurrent()->GetData())->r,
                        ((D3DCOLORVALUE*)variables->GetCurrent()->GetData())->g,
                        ((D3DCOLORVALUE*)variables->GetCurrent()->GetData())->b,
                        ((D3DCOLORVALUE*)variables->GetCurrent()->GetData())->a);
                fputs(output, file);
                fputs("\n", file);                continue;

            case VARIABLE_FLOAT:
                sprintf(output, "%s float %f", variables->GetCurrent()->GetName(), *(float*)variables->GetCurrent()->GetData());
                fputs(output, file);
                fputs("\n", file);
                continue;

            case VARIABLE_NUMBER:
                sprintf(output, "%s number %d", variables->GetCurrent()->GetName(), *(long*)variables->GetCurrent()->GetData());
                fputs(output, file);
                fputs("\n", file);
                continue;

            case VARIABLE_STRING:
                sprintf( output, "%s string \"%s\"", variables->GetCurrent()->GetName(), (char*)variables->GetCurrent()->GetData() );
                fputs( output, file );
                fputs( "\n", file );
                continue;

            case VARIABLE_VECTOR:
                sprintf(output, "%s vector %f %f %f", variables->GetCurrent()->GetName(),
                        ((D3DXVECTOR3*)variables->GetCurrent()->GetData())->x,
                        ((D3DXVECTOR3*)variables->GetCurrent()->GetData())->y,
                        ((D3DXVECTOR3*)variables->GetCurrent()->GetData())->z);
                fputs(output, file);
                fputs("\n", file);
                continue;

            default:
                sprintf(output, "%s unknown %s", variables->GetCurrent()->GetName(), (char*)variables->GetCurrent()->GetData());
                fputs(output, file);
                fputs("\n", file);
                continue;
        }
    }

    fputs("#end", file); // пишем тег #end в файл
    fclose( file ); // закрываем файл скрипта
}

//-----------------------------------------------------------------------------
// Возвращает данные bool из указанной переменной
bool *Script::Get_Bool_Data(char *variable)
{
    variables->Iterate(true);
    while(variables->Iterate() != NULL)
        if (strcmp(variables->GetCurrent()->GetName(), variable) == 0)
            return (bool*)variables->GetCurrent()->GetData();
    return NULL;
}

// Возвращает данные colour из указанной переменной.
D3DCOLORVALUE *Script::Get_Colour_Data(char *variable)
{
    variables->Iterate(true);
    while (variables->Iterate() != NULL)
        if (strcmp(variables->GetCurrent()->GetName(), variable) == 0)
            return (D3DCOLORVALUE*)variables->GetCurrent()->GetData();
    return NULL;
}

// Возвращает данные типа float из указанной переменной.
float *Script::Get_Float_Data(char *variable)
{
    variables->Iterate(true);
    while (variables->Iterate() != NULL)
        if (strcmp(variables->GetCurrent()->GetName(), variable) == 0)
            return (float*)variables->GetCurrent()->GetData();
    return NULL;
}

// Возвращает данные целочисленного типа из указанной переменной
long *Script::Get_Number_Data(char *variable)
{
    variables->Iterate(true);
    while (variables->Iterate() != NULL)
        if (strcmp(variables->GetCurrent()->GetName(), variable) == 0)
            return (long*)variables->GetCurrent()->GetData();
    return NULL;
}

// Возвращает строку из указанной переменной.
char *Script::Get_String_Data(char *variable)
{
    variables->Iterate(true);
    while (variables->Iterate() != NULL)
        if (strcmp(variables->GetCurrent()->GetName(), variable) == 0)
            return (char*)variables->GetCurrent()->GetData();
    return NULL;
}

// Возвращает данные о цвете из указанной переменной
D3DXVECTOR3 *Script::Get_Vector_Data(char *variable)
{
    variables->Iterate(true);
    while(variables->Iterate() != NULL)
        if (strcmp(variables->GetCurrent()->GetName(), variable) == 0)
            return (D3DXVECTOR3*)variables->GetCurrent()->GetData();
    return NULL;
}

// Возвращает данные неизвестного типа из указанной переменной
void *Script::Get_Unknown_Data(char *variable)
{
    variables->Iterate(true);
    while(variables->Iterate() != NULL)
        if (strcmp(variables->GetCurrent()->GetName(), variable) == 0)
            return variables->GetCurrent()->GetData();
    return NULL;
}
