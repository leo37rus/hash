#pragma once
#include <iostream>
#include <string>
#include"sha1.h"

typedef unsigned int uint;
//#define SIZE 10
#define LOGINLENGTH 10
typedef char LoginName[LOGINLENGTH]; 

class HashTable { 
public:

    HashTable();
    ~HashTable();
    void add(LoginName _login, uint* pass_sha1_hash);

    void del(LoginName _login);
    int find(LoginName _login);
    void reg(char _login[LOGINLENGTH], char _pass[], int pass_length);
    bool login(char _login[LOGINLENGTH], char _pass[], int pass_length);
    void resize();
    void show();

private:

    enum enPairStatus {
        free,
        engaged,
        deleted
    };

    struct Pair { 

        Pair() :
            login(""),
            pass_sha1_hash(0),
            status(enPairStatus::free)
        {}
        Pair(LoginName _login, uint* sh1) :
            pass_sha1_hash(sh1),
            status(enPairStatus::engaged) {
            memcpy(login, _login, LOGINLENGTH);
        }
        Pair& operator = (const Pair& other) {
            pass_sha1_hash = other.pass_sha1_hash;
            memcpy(login, other.login, LOGINLENGTH);
            status = other.status;

            return *this;
        }

        bool operator == (const Pair& other) {
            return  status == other.status &&
                (status != enPairStatus::engaged || (pass_sha1_hash == other.pass_sha1_hash && !strcmp(login, other.login)));
        }
                
        char login[LOGINLENGTH];
        uint* pass_sha1_hash;
        enPairStatus status;
    };

    int hash_func(LoginName fr_name, int offset);

    Pair* array;
    int mem_size;
    int count;
};
