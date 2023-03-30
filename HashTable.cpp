#include "HashTable.h"

HashTable::HashTable() {
    count = 0;
    mem_size = 8;
    array = new Pair[mem_size];
}
HashTable::~HashTable() {
    delete[] array;
}
void HashTable::add(LoginName _login, uint* pass_sha1_hash) 
{
    int index = -1, i = 0;
    
    for (; i < mem_size; i++) {
        index = hash_func(_login, i);
        if (array[index].status == enPairStatus::free) 
        {
            break;
        }
    }
    if (i >= mem_size) 
    {
        resize(); 
        add(_login, pass_sha1_hash);
    }
    
    else
    {
        array[index] = Pair(_login, pass_sha1_hash);
        count++;
    }
}

int HashTable::hash_func(LoginName _login, int offset) 
{
    int sum = 0, i = 0;
    for (; i < LOGINLENGTH; i++) 
    {
        sum += _login[i];
    }
    int hash = (int(mem_size * (sum * 0.168) - int(sum * 0.168)) + offset * offset) % mem_size;
    return hash;
}

void HashTable::del(LoginName _login) 
{
    int index = -1;
    for (int i = 0; i < mem_size; i++) 
    {
        index = hash_func(_login, i);
        if (!strcmp(array[index].login, _login) && array[index].status == engaged)
        {
            array[index].status = deleted;
            count--;
            return;
        }
    }
}

int HashTable::find(LoginName _login) 
{
    int index = -1, i = 0;
    
    for (; i < mem_size; i++) 
    {
        index = hash_func(_login, i);
        if (array[index].status == free) 
        {
            return 0;
        }
        if (!strcmp(array[index].login, _login) && array[index].status == engaged)
            return index;
    }
    return 0;
}

void HashTable::reg(char _login[LOGINLENGTH], char _pass[], int pass_length) 
{
     uint* sh1 = sha1(_pass, pass_length);
     add(_login, sh1);
}

bool HashTable::login(char _login[LOGINLENGTH], char _pass[], int pass_length) 
{
    uint* sh1 = sha1(_pass, pass_length);
    
    if (find(_login))
    {
        int index = find(_login);
        for (int j = 0; j < 5; j++)
        {
            if (array[index].pass_sha1_hash[j] != sh1[j])
                return false;
        }
        return true;
    }
    return false;
}

void HashTable::resize() 
{
    Pair* save_array = array;
    int oldSize = mem_size;

    mem_size *= 2;  
    count = 0; 
    array = new Pair[mem_size]; 

    for (int i = 0; i < oldSize; i++) 
    {
        Pair current = save_array[i]; 
        if (current.status == engaged)
            add(current.login, current.pass_sha1_hash);
    }

    delete[] save_array;
}

void HashTable::show()
{
    for (int i = 0; i < mem_size; i++)
    {
        if (array[i].status == engaged)
        {
            std::cout << " INDEX  " << i << "  " << array[i].login 
                /*<< '\t' << array[i].pass_sha1_hash << '\t' << array[i].status << std::endl*/;
            std::cout << " -  " << "HASH  ";
            for (int j = 0; j < 5; j++)
            {
                if (array[i].status == engaged)
                    std::cout << "/" << array[i].pass_sha1_hash[j];
            }
            std::cout << std::endl;
        }
    }
}