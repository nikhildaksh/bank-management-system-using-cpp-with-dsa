#include<iostream>
#include"classes/menu.cpp"
int main(){    
    menu *obj = new menu;
    obj->main_menu();
    delete obj;
    return 0;
}