#include<iostream>
#include<fstream>
#include<iomanip>
class admin_login{
    std::string username;
    std::string password;
    bool login_check(std::string username,std::string password){
        if(username=="admin" && password =="root"){
            return true;
        }
        return false;
    }
    public:
    bool login(std::string username, std::string password){        
        if(login_check(username,password)){
            return true;
        }
        return false;
    }
};
class admin_function:private admin_login{
        typedef struct account_details{
            std::string password;
            std::string name;
            std::string contact_no;
            int total_money;
            std::string id;
        }account_details;
            // linked list functionality
        typedef struct node{
            std::string password;
            std::string name;
            std::string contact_no;
            int total_money;
            struct node *next;
            std::string id;
        }node;
        node *head;
        int node_index;
        bool is_admin_login_sucessfully;
        public:
        bool admin_login_fun(){            
            std::string username,password;
            std::cout<<"----- Admin Login ---- "<<std::endl;
            std::cout<<" Username: ";std::cin>>username;
            std::cout<<" Password: ";std::cin>>password;
            if(login(username, password)){
                is_admin_login_sucessfully = true;
                std::cout<<"Sucessfully login "<<std::endl;
                return true;              
            }else{
                is_admin_login_sucessfully = false;
                std::cout<<"Login Failed! "<<std::endl;
                return false;                
            }
            // return false;
        }
        admin_function(){
            is_admin_login_sucessfully = false;
            // admin_login_fun(); remove from constructor
            node_index = 0;         
            head = new node;
            head->next = NULL;
            std::fstream obj("Database/data.text",std::ios::in);
            if(obj.is_open()){
                account_details *s = new account_details;
                while(!obj.eof()){                    
                    obj>>s->id;
                    obj>>s->password;
                    obj>>s->name;
                    obj>>s->contact_no;
                    obj>>s->total_money;                    
                    create_node(s);
                }                
                delete s;
            }
            obj.close();
        }
        ~admin_function(){
            node *h = head;
            if(h->next==NULL){

            }else{
                std::fstream obj("Database/data.text",std::ios::out);
                int flag=0;
                while(h->next!=NULL){
                    if(flag==0){                                                
                        h = h->next;
                        obj<<h->id<<std::endl;
                        obj<<h->password<<std::endl;
                        obj<<h->name<<std::endl;
                        obj<<h->contact_no<<std::endl;
                        obj<<h->total_money;
                        flag=1;
                    }else{
                        h = h->next;
                        obj<<std::endl;
                        obj<<h->id<<std::endl;
                        obj<<h->password<<std::endl;
                        obj<<h->name<<std::endl;
                        obj<<h->contact_no<<std::endl;
                        obj<<h->total_money;
                    }
                }                
                obj.close();
                // free all memory
                delete h;
                delete head;
            }
        }

        bool create_node(account_details *s){
            node *h = head;
            node *temp = new node;
            temp->id = s->id;
            temp->password = s->password;
            temp->name = s->name;            
            temp->contact_no = s->contact_no;
            temp->total_money = s->total_money;
            temp->next = NULL;
            if(h->next==NULL){
                h->next = temp;
                node_index++;
                return true;
            }else{
                while(h->next!=NULL){
                    h = h->next;
                }
                h->next = temp;                
                node_index++;
                return true;
            }
            return false;
        }
        bool delete_node(account_details *s){
            node *h = head;
            int f = 0;
            if(h->next==NULL){
                std::cout<<" Empty List "<<std::endl;
                return false;
            }else{
                node *n = h->next;                
                while(n!=NULL){                    
                    if(n->id==s->id){
                        f = 1;
                        break;
                    }
                    n = n->next;
                    h = h->next;          
                }
                if(f==1){
                    h->next = n->next;
                    delete n;                    
                    return true;
                }
                return false;
            }
            delete h;
        }
        bool update_node(account_details *s){
            node *h = head;
            if(h->next==NULL){
                std::cout<<" Empty List "<<std::endl;                
                return false;
            }else{
                while(h->next!=NULL){
                    h = h->next;
                    if(h->id==s->id){
                        std::cout<<"\n Details are founded. "<<std::endl;
                        std::cout<<"Name : "<<h->name<<" | Number: "<<h->contact_no<<std::endl;
                        std::cout<<"--------------------------------------------------"<<std::endl;
                        std::cout<<"Update Account Details: "<<std::endl;
                        std::cout<<"Enter Name: ";std::cin>>h->name;
                        std::cout<<"Enter Contact No: ";std::cin>>h->contact_no;
                        return true;
                    }                       
                }
                return false;
            }            
        }
        // direct used function
        bool is_id_exist(std::string id){
            node *h = head;
            if(h->next==NULL){
                return false;
            }else{
                while(h->next!=NULL){
                    h = h->next;
                    if(h->id==id){
                        return true;
                    }
                }
            }
            return false;
        }
        void create_new_account(){
            if(is_admin_login_sucessfully){
                account_details *s;
                s = new account_details;
                std::cout<<"\n--- Create New Account -----"<<std::endl;
                start:            
                std::cout<<"Enter ID (Unique): ";std::cin>>s->id;
                if(is_id_exist(s->id)){
                    std::cout<<"ID Already Exist"<<std::endl;
                    goto start;
                }
                std::cout<<"Enter Password: ";std::cin>>s->password;
                std::cout<<"Enter Name: ";std::cin>>s->name;
                std::cout<<"Enter Contact No: "; std::cin>>s->contact_no;            
                std::cout<<"Total Money: "; std::cin>>s->total_money;
                if(create_node(s)){
                    std::cout<<"Account Added Sucessfully. "<<std::endl;
                }else{
                    std::cout<<"Failed! Account not created. "<<std::endl;
                }
            }else{
                std::cout<<" Please Login ! First . "<<std::endl;
                admin_login_fun();
            }          
        }        
        void close_existing_account(){
            if(is_admin_login_sucessfully){
                account_details *temp = new account_details;
                std::cout<<"\n---- Close Account ------"<<std::endl;            
                std::cout<<" Enter ID to Close Account: ";std::cin>>temp->id;
                if(delete_node(temp)){
                    std::cout<<"\nDeleted Sucessfully. "<<std::endl;
                }else{
                    std::cout<<"\nSorry Account Not founded."<<std::endl;                
                }
                delete temp;
            }else{
                std::cout<<" Please Login ! First . "<<std::endl;
                admin_login_fun();
            }  
        }
        void update_existing_account(){
            if(is_admin_login_sucessfully){
                account_details *temp = new account_details;
                std::cout<<"\n---- Update Account ------"<<std::endl;            
                std::cout<<" Enter ID to Update Account: ";std::cin>>temp->id;
                if(update_node(temp)){
                    std::cout<<"\n Updated Sucessfully. "<<std::endl;
                }else{
                    std::cout<<"\nSorry Account Not founded."<<std::endl;                
                }
                delete temp;
            }else{
                std::cout<<" Please Login ! First . "<<std::endl;
                admin_login_fun();
            }
        }
        void display_all_account(){          
            if(is_admin_login_sucessfully){         
                node *h = head;
                if(h->next==NULL){
                    std::cout<<"\n Empty List"<<std::endl;
                }else{                         
                    std::cout<<"\n All Account Details are: "<<std::endl;                
                    std::cout<<"------------------------------------------------------------------------------------------------------------"<<std::endl;
                    std::cout <<std::left<<std::setw(10)<< " | "<< std::setw(10) << " id "<< std::setw(10) << " | "<<std::setw(10)<< "Name" << std::setw(15) <<" | "<<std::setw(20) << "contact no" <<std::setw(15)<<" | "<<std::setw(15)<< "total money" <<std::setw(10)<<" | "<<std::endl;
                    std::cout<<"------------------------------------------------------------------------------------------------------------"<<std::endl;

                    while(h->next!=NULL){
                        h = h->next;
                        // std::cout<<"Name : "<<h->name<<" | Number: "<<h->contact_no<<" | Total Money: "<<h->total_money<<std::endl;                                        
                        std::cout <<std::left<<std::setw(10)<< " | "<< std::setw(10) << h->id<< std::setw(10) << " | "<<std::setw(10)<< h->name << std::setw(15) <<" | "<<std::setw(20) << h->contact_no <<std::setw(15)<<" | "<<std::setw(15)<<h->total_money <<std::setw(10)<<" | "<<std::endl;
                    }
                    std::cout<<"------------------------------------------------------------------------------------------------------------"<<std::endl;
                    std::cout<<"Total Number of Accounts are: "<<node_index<<std::endl;
                }
            }else{
                std::cout<<" Please Login ! First . "<<std::endl;
                admin_login_fun();
            }
        }
        void withdrawal_from_total_money(){
            if(is_admin_login_sucessfully){
                node *h = head;
                if(h->next == NULL){
                    std::cout<<"\n Sorry, no any account founded."<<std::endl;
                }else{
                    std::string tempid;
                    int withdrawmoney;
                    tempstart:
                    std::cout<<"-------------------------------------------------------"<<std::endl;
                    std::cout<<"Enter ID to withdaw money: "; std::cin>>tempid;                
                    if(is_id_exist(tempid)){
                        balance_enquiry(tempid);
                        std::cout<<"Enter How Many Money Withdraw: ";std::cin>>withdrawmoney;
                        while(h->next!=NULL){
                            h = h->next;
                            if(h->id==tempid){
                                if(h->total_money>=withdrawmoney){
                                    h->total_money = h->total_money - withdrawmoney;
                                    std::cout<<"withdral sucessfully: "<<withdrawmoney<<std::endl;
                                    std::cout<<"Remaining Balance: "<<h->total_money<<std::endl;
                                }else{
                                    std::cout<<"Insufficent Balance!"<<std::endl;                                                                
                                }
                                break;
                            }
                        }
                    }else{
                        std::cout<<"\nSorry Account Not founded."<<std::endl;
                        goto tempstart;
                    }                
                }
            }else{
                std::cout<<" Please Login ! First . "<<std::endl;
                admin_login_fun();
            }
        }
        void deposit_money(){
            if(is_admin_login_sucessfully){
                node *h = head;
                if(h->next == NULL){
                    std::cout<<"\n Sorry, no any account founded."<<std::endl;
                }else{
                    std::string tempid;
                    int tempmoney;
                    tempstart:
                    std::cout<<"-------------------------------------------------------"<<std::endl;
                    std::cout<<"Enter ID to add money: "; std::cin>>tempid;
                    if(is_id_exist(tempid)){
                        std::cout<<"How many ammount deposit: ";std::cin>>tempmoney;
                        while(h->next!=NULL){
                            h=h->next;
                            if(h->id==tempid){
                                h->total_money += tempmoney;
                                std::cout<<"\n"<<tempmoney<<" deposit sucessfully.";
                                break;
                            }
                        }
                    }else{
                        std::cout<<"\nSorry Account Not founded."<<std::endl;
                        goto tempstart;
                    }
                }
            }else{
                std::cout<<" Please Login ! First . "<<std::endl;
                admin_login_fun();
            }
        }

        void balance_enquiry(std::string defaultid="empty"){
            if(is_admin_login_sucessfully){
                node *h = head;
                if(h->next == NULL){
                    std::cout<<"\n Sorry, no any account founded."<<std::endl;
                }else{
                    std::string tempid;
                    int checkbalance;
                    if(defaultid=="empty"){
                        tempstart:
                        std::cout<<"-------------------------------------------------------"<<std::endl;
                        std::cout<<"Enter ID to check balance: "; std::cin>>tempid;                
                        if(is_id_exist(tempid)){
                            while(h->next!=NULL){
                                h = h->next;
                                if(h->id==tempid){                            
                                    checkbalance = h->total_money;
                                    std::cout<<"\n Id : "<<tempid<<" Total Balance: "<<checkbalance<<std::endl;
                                    break;
                                }
                            }
                        }else{
                            std::cout<<"\nSorry Account Not founded."<<std::endl;
                            goto tempstart;
                        }    
                    }else{
                        if(is_id_exist(defaultid)){
                            while(h->next!=NULL){
                                h = h->next;
                                if(h->id==defaultid){                            
                                    checkbalance = h->total_money;
                                    std::cout<<"\n Id : "<<defaultid<<" Total Balance: "<<checkbalance<<std::endl;
                                    break;
                                }
                            }
                        }else{
                            std::cout<<"\nSorry Account Not founded."<<std::endl;
                            goto tempstart;
                        }                        
                    }                    
                }
            }else{
                std::cout<<" Please Login ! First . "<<std::endl;
                admin_login_fun();
            }
        }
        void changed_user_password(){
            if(is_admin_login_sucessfully){
               node *h = head;
               std::string tempid, temppassword;
               start:
               int flag = 0;
               std::cout<<" ------- User Password Change ------- "<<std::endl;
               std::cout<<" Enter Id to change user Account Password: ";std::cin>>tempid;
               if(is_id_exist(tempid)){
                    std::cout<<" Account Id: "<<tempid<<std::endl;
                    std::cout<<" Enter New Password: ";std::cin>>temppassword;
                    while(h->next!=NULL){
                        h =h->next;
                        if(h->id==tempid){
                            h->password =temppassword;
                            std::cout<<" Password Changed Sucessfully. "<<std::endl;
                            std::cout<<" New Password: "<<h->password<<std::endl;
                            flag = 1;
                        }
                    }
               }else{
                    std::cout<<"  Sorry This id not founed. try again. "<<std::endl;
                    goto start;
                }
                if(flag==0){
                    std::cout<<" Failed to Changed Password! "<<std::endl;
                }
            }else{
                std::cout<<" Please Login ! First . "<<std::endl;
                admin_login_fun();
            }
        }
        void setting(){
            std::cout<<" setting function "<<std::endl;
        }
};