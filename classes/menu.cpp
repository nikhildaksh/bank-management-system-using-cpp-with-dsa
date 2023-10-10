// all programs menu are here
#include<iostream>
#include"admin.cpp"
#include"user.cpp"
class admin_menu{  
    public:  
    void f_admin(){        
        admin_function  *obj = new admin_function;
            int slt = 1;
            if(!(obj->admin_login_fun())){
                slt = 0;
            }
            while(slt!=0){
                std::cout<<" ---------------- Admin Menu --------------------- "<<std::endl;
                std::cout<<" 0. Go Back .. "<<std::endl;
                std::cout<<" 1. Exit .. "<<std::endl;
                // std::cout<<" ******* Account Related ******* "<<std::endl;
                std::cout<<" 2. Create New Account .. "<<std::endl;
                std::cout<<" 3. Close Existing Account .. "<<std::endl;
                std::cout<<" 4. Update Existing Account .. "<<std::endl;
                std::cout<<" 5. Display All Account .. "<<std::endl;
                // std::cout<<" ******* Account Basic Task ******* "<<std::endl;
                std::cout<<" 6. Withdraw Money from Total Money .. "<<std::endl;
                std::cout<<" 7. Despoit Money .. "<<std::endl;
                std::cout<<" 8. Balance Enquiry .. "<<std::endl;
                // std::cout<<" ******* Account Setting  ******* "<<std::endl;
                std::cout<<" 9. User Password Change .. "<<std::endl;
                std::cout<<" 10. Setting .. "<<std::endl;
                std::cout<<" -------------------------------------------------- "<<std::endl;
                std::cout<<" Enter Your Choice :  "; std::cin>>slt;
                switch(slt){
                    case 0: delete obj; break;
                    case 1: delete obj; exit(0);
                    case 2: obj->create_new_account(); break;
                    case 3: obj->close_existing_account(); break;
                    case 4: obj->update_existing_account(); break;
                    case 5: obj->display_all_account(); break;
                    case 6: obj->withdrawal_from_total_money(); break;
                    case 7: obj->deposit_money(); break;
                    case 8: obj->balance_enquiry(); break;
                    case 9: obj->changed_user_password(); break;
                    case 10: obj->setting(); break;
                    default: std::cout<<"\n !Invalid Choice, try again "<<std::endl;
                }
            }            
            // delete obj;           
    }    
};
class user_menu{
    public:
    void f_user(){
        user_function *obj = new user_function;
        int slt=1;
        if(!(obj->user_login())){
            slt = 0;
        }
        while(slt!=0){
            std::cout<<" ---------- User Menu ----------- "<<std::endl;
            std::cout<<" 0. Go Back "<<std::endl;
            std::cout<<" 1. Exit "<<std::endl;
            std::cout<<" 2. Withdraw Money "<<std::endl;
            std::cout<<" 3. Check Balance "<<std::endl;
            std::cout<<" 4. Send Money to another "<<std::endl;
            std::cout<<" 5. Change Password "<<std::endl;
            std::cout<<" 6. My Account Details "<<std::endl;
            std::cout<<" -------------------------------- "<<std::endl;
            std::cout<<" Enter Your Choice : "; std::cin>>slt;
            switch(slt){
                case 0: break;
                case 1: exit(0);
                case 2: obj->withdrawal_from_total_money(); break;
                case 3: obj->balance_enquiry(); break;
                case 4: obj->send_money_to_another(); break;
                case 5: obj->change_password(); break;
                case 6: obj->accountdetails(); break;
            }
        }
    }
};
class menu: private user_menu, private admin_menu{
    public:
    void main_menu(){                
        int slt;        
        while(1){
            std::cout<<" ------------ Welcome Bank Management System ------------- "<<std::endl;
            std::cout<<" 0. Exit "<<std::endl;
            std::cout<<" 1. Admin Login "<<std::endl;
            std::cout<<" 2. User Login "<<std::endl;
            std::cout<<" Enter Choice :  "; std::cin>>slt;
            switch(slt){
                case 0: exit(0);
                case 1: f_admin(); break;
                case 2: f_user(); break;
                default : std::cout<<" Invalid Choice ! try again "<<std::endl;
            }
        }
    }    
};

