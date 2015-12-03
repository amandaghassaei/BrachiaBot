#ifndef JSON_h
#define JSON_h

#include "mbed.h"

class JSON {
    
    public:
    
        JSON(Serial* pc){
            _pc = pc;
        }
        
        void open(){
            _pc->printf("{");
        }
        
        void close(){
            _pc->printf("}\n");
        }
        
        void sepItem(){
            _pc->printf(",");
        }
    
        void print(char *key, float value){
            _pc->printf("\"");
            _pc->printf(key);
            _pc->printf("\": \"");
            _pc->printf("%f", value);
            _pc->printf("\"");
        }
        
        void print(char *key, int value){
            _pc->printf("\"");
            _pc->printf(key);
            _pc->printf("\": \"");
            _pc->printf("%i", value);
            _pc->printf("\"");
        }
        
        void print(char *key, char *value){
            _pc->printf("\"");
            _pc->printf(key);
            _pc->printf("\": \"");
            _pc->printf(value);
            _pc->printf("\"");
        }
    
    private:
        
        Serial *_pc;
    
    
};

#endif