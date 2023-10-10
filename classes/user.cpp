#include<iostream>
#include<fstream>
#include<iomanip>
class user_login{
    // std::string username;
    // std::string password;
    public:
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
    account_details login_details;
    bool is_login_sucessfully;
    private:    
    bool login_check(std::string id,std::string password){    
        std::fstream obj("Database/data.text",std::ios::in);
        account_details *s = new account_details;
        if(obj.is_open()){
            while(!obj.eof()){
                    obj>>s->id;
                    obj>>s->password;
                    obj>>s->name;
                    obj>>s->contact_no;
                    obj>>s->total_money;    
                if(id == s->id && password == s->password){
                    login_details.id = s->id;
                    login_details.password = s->password;
                    login_details.name = s->name;
                    login_details.contact_no = s->contact_no;
                    login_details.total_money = s->total_money;
                    is_login_sucessfully = true;
                    delete s;
                    obj.close();
                    return true;
                }
            }
        }   
        delete s;     
        obj.close();       
        return false;
    }
    public:
    bool login(std::string id,std::string password){
        if(login_check(id,password)){
            return true;
        }
        return false;
    }
};
class user_function:private user_login{
        public:
        // account_details t;
        node *head;
        bool user_login(){              
            account_details *t = new account_details;
            std::cout<<" ------- USER Login --------- "<<std::endl;
            std::cout<<"ID: ";std::cin>>t->id;
            std::cout<<"Password: ";std::cin>>t->password;
            if(login(t->id,t->password)){
                head = new node;
                head->next = NULL;
                std::cout<<"\n login sucessfully. "<<std::endl;                
                return true;
            }else{
                std::cout<<"\n login failed. "<<std::endl;
                return false;
            }            
        }
                     //  create linked list
        bool create_node(account_details *data){
            node *h = head;
            if(h->next==NULL){
                node *temp = new node;
                temp->next = NULL;
                temp->id = data->id;
                temp->name = data->name;
                temp->contact_no = data->contact_no;
                temp->password = data->password;
                temp->total_money = data->total_money;
                h->next = temp;
                // delete temp;                
                return true;
            }else{
                while(h->next!=NULL){
                    h = h->next;
                }
                node *temp = new node;
                temp->next = NULL;
                temp->id = data->id;
                temp->name = data->name;
                temp->contact_no = data->contact_no;
                temp->password = data->password;
                temp->total_money = data->total_money;
                h->next = temp;
                // delete temp;
                return true;                
            }            
            return false;
        }
        void fetch_data_from_file(){            
            if(is_login_sucessfully){
                std::fstream obj("Database/data.text",std::ios::in);
                // account_details *data = new account_details;
                account_details *t = new account_details;
                if(obj.is_open()){
                    while(!obj.eof()){
                            obj>>t->id;
                            obj>>t->password;
                            obj>>t->name;
                            obj>>t->contact_no;
                            obj>>t->total_money;
                        create_node(t);
                    }
                    delete t;                            
                }else{
                    std::cout<<"error, file not open sucessfully."<<std::endl;
                }               
                obj.close();
            }else{
                std::cout<<"login please... "<<std::endl;
                user_login();
            }
        }

        void send_data_to_file(){
            if(is_login_sucessfully){
                int flag=0;
                node *h = head;                
                std::fstream obj("Database/data.text",std::ios::out);
                while(h->next!=NULL){
                    h=h->next;
                    if(flag==0){                        
                        obj<<h->id<<std::endl;
                        obj<<h->password<<std::endl;
                        obj<<h->name<<std::endl;
                        obj<<h->contact_no<<std::endl;
                        obj<<h->total_money;
                        flag=1;
                    }else{                        
                        obj<<std::endl;
                        obj<<h->id<<std::endl;
                        obj<<h->password<<std::endl;
                        obj<<h->name<<std::endl;
                        obj<<h->contact_no<<std::endl;
                        obj<<h->total_money;
                    }
                }                
                obj.close();
            }else{
                std::cout<<"login please... "<<std::endl;
                user_login();
            }
        }   

        bool update_money(std::string targetid , int money){
            if(is_login_sucessfully){                
                node *h = head;
                int flag1 =0, flag2=0;
                while(h->next!=NULL){
                    h = h->next;
                    if(h->id==login_details.id){
                        if(h->total_money>=money){
                            h->total_money =  h->total_money - money;
                            login_details.total_money = h->total_money;
                            flag1=1;
                        }
                    }
                    if(h->id==targetid){                                                
                        h->total_money =  h->total_money + money;
                            flag2=1;
                    }
                }    
                if(flag1==1 && flag2==1){                    
                    send_data_to_file(); 
                    return true;
                }
            }
            return false;
        }
        
        bool withdrawal_money(int withdrawalmoney){
            if(is_login_sucessfully){
                fetch_data_from_file();
                int flag = 0;
                node *h = head;
                while(h->next!=NULL){
                    h = h->next;
                    if(h->id==login_details.id){
                        if(h->total_money>=withdrawalmoney){
                            h->total_money = h->total_money - withdrawalmoney;                            
                            login_details.total_money = h->total_money;
                            flag = 1;                            
                        }                    
                    }
                }
                if(flag==1){                    
                    send_data_to_file();
                    return true;
                }
            }
            return false;
        }
        bool is_id_exist(std::string targetid){            
            if(is_login_sucessfully){
                node *h = head;
                while(h->next!=NULL){
                    h = h->next;
                    if(h->id==targetid){
                        return true;                        
                    }
                }
            }
            return false;
        }

        // end linked list
        void accountdetails(){
            if(is_login_sucessfully){
                std::cout<<"\n Account Details are: "<<std::endl;                
                std::cout<<"------------------------------------------------------------------------------------------------------------"<<std::endl;
                std::cout <<std::left<<std::setw(10)<< " | "<< std::setw(10) << " id "<< std::setw(10) << " | "<<std::setw(10)<< "Name" << std::setw(15) <<" | "<<std::setw(20) << "contact no" <<std::setw(15)<<" | "<<std::setw(15)<< "total money" <<std::setw(10)<<" | "<<std::endl;
                std::cout<<"------------------------------------------------------------------------------------------------------------"<<std::endl;                
                std::cout <<std::left<<std::setw(10)<< " | "<< std::setw(10) << login_details.id<< std::setw(10) << " | "<<std::setw(10)<< login_details.name << std::setw(15) <<" | "<<std::setw(20) << login_details.contact_no <<std::setw(15)<<" | "<<std::setw(15)<<login_details.total_money <<std::setw(10)<<" | "<<std::endl;
            }else{
                std::cout<<"login please... "<<std::endl;
                user_login();
            }
        }
        void send_money_to_another(){        
            if(is_login_sucessfully){
                std::cout<<" Current Balance: "<<login_details.total_money<<std::endl;
                fetch_data_from_file();                        
                int tempmoney;
                std::string tempid;
                std::cout<<"send money to another"<<std::endl;
                start:
                std::cout<<" Enter ID to send money: "; std::cin>>tempid;
                if(tempid==login_details.id){
                    std::cout<<" This is your account id. please enter another id."<<std::endl;
                    goto start;
                }
                if(!is_id_exist(tempid)){
                    std::cout<<" ID Not Found. "<<std::endl;
                    goto start;
                }                
                std::cout<<" How many money to send: "; std::cin>>tempmoney;
                if(tempmoney>login_details.total_money){
                    std::cout<<" Insufficent Balance " <<std::endl;
                    std::cout<<" Current Balance: "<<login_details.total_money<<std::endl;
                }
                if(update_money(tempid,tempmoney)){
                    send_data_to_file();                    
                    std::cout<<" Money Transfer Sucessfully "<<std::endl;
                }                
            }else{
                std::cout<<"login please... "<<std::endl;
                user_login();
            }

        }
        void withdrawal_from_total_money(){
            if(is_login_sucessfully){
                int tempmoney;
                std::cout<<" ------------- withdrawal Money ------------ "<<std::endl;
                start:
                std::cout<<" Current Balance: "<<login_details.total_money<<std::endl;
                std::cout<<"Enter how many money wintdrawl: "; std::cin>>tempmoney;
                if(!(login_details.total_money>=tempmoney)){
                    std::cout<<" Insufficent Balance "<<std::endl;
                    goto start;
                }
                if(withdrawal_money(tempmoney)){
                    std::cout<<"sucessfully withdrawal."<<std::endl;
                }
            }else{
                std::cout<<"login please... "<<std::endl;
                user_login();
            }
        }
        void balance_enquiry(){        
            if(is_login_sucessfully){
                std::cout<<" ------------ Balance Enquiry ----------- "<<std::endl;
                std::cout<<" Current Balance: "<<login_details.total_money<<std::endl;
            }else{
                std::cout<<"login please... "<<std::endl;
                user_login();
            }
        }
        void change_password(){
            if(is_login_sucessfully){
                fetch_data_from_file();
                int flag = 0;
                std::string newpassword;
                node *h = head;
                std::cout<<" ------ Change Password ------ "<<std::endl;
                std::cout<<" Your Old Password: "<<login_details.password<<std::endl;
                std::cout<<" Enter Your New Password: "; std::cin>>newpassword;
                while(h->next!=NULL){
                    h = h->next;
                    if(h->password==login_details.password){
                        h->password = newpassword;
                        login_details.password = newpassword;
                        flag = 1;
                    }
                }
                if(flag==1){
                    std::cout<<" Password Changed Sucessfully. "<<std::endl;
                    std::cout<<" New Password:  "<<login_details.password<<std::endl;
                    // send_data_to_file();
                    // return true;
                }else{
                    std::cout<<" sorry! Password not changed ";
                }
            }else{
                std::cout<<"login please... "<<std::endl;
                user_login();
            }
        }
        void setting(){
            // setting
        }
};