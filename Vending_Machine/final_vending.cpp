#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
void clearInput() {
        cin.clear();
        cin.ignore(1000, '\n');
}
const int MAX_PRODUCTS = 20;
//-------Product Class--------
class Products{
//Encapsulation
private:
    int id;
    string name;
    double price;
    int stock;
    int unit_solds;
public:
    //Default Constructor
    Products(){
        id = 0; 
        name = "unknown";
        price = 0;
        stock = 0;
        unit_solds = 0;
    }
    //Parameterized Constructor
    Products(int i,string n,double p,int s){
        id = i;
        name = n;
        price = p;
        stock = s;
        unit_solds = 0;
    }
    void setId(int s){
        id = s;
    }
    int getId(){
        return id;
    }
    void setName(string s){
        name = s;
    }
    string getName(){
        return name;
    }
    void setPrice(double newPrice){
        price = newPrice;
    }
    double getPrice(){
        return price;
    }
    void setStock(int s){
        stock = s;
    }
    int getStock(){
        return stock;
    }
    bool isAvailable(){
        if(stock > 0){
            return true;
        }
        else{
            return false;
        }
    }
    void reduceStock(){
        if(stock>0){
            stock--;
        }
    }
    void addSale(){
        unit_solds++;
    }
    int getUnitSale(){
        return unit_solds;
    }
    void input(){
        cout<<"Enter product ID : ";
        cin>>id;
        cout<<"Enter product name : ";
        cin>>name;
        cout<<"Enter price : ";
        cin>>price;
        cout<<"Enter Stock : ";
        cin>>stock;
    }
    void display(){
        cout<<setw(5)<<id<<setw(15)<<name<<fixed<<setw(7)<<setprecision(2)<<price<<setw(6)<<stock<<endl;
    }
};
//---------VendingMachine Class--------------
class VendingMachine {//Abstract Class
protected:
    Products inventory[MAX_PRODUCTS];
    double total_revenue;
    int total_sold;
    int productCount;
public:
    //Constructor to initialize the inventory
    VendingMachine() {
            inventory[0]  = Products(1,  "Coke",        10.0, 15);
            inventory[1]  = Products(2,  "Pepsi",       11.5, 13);
            inventory[2]  = Products(3,  "BigApple",     9.0, 10);
            inventory[3]  = Products(4,  "BigLeeche",    9.5, 10);
            inventory[4]  = Products(5,  "Shezan",       5.0, 11);
            inventory[5]  = Products(6,  "Sprite",       9.0, 12);
            inventory[6]  = Products(7,  "Fanta",        9.0, 12);
            inventory[7]  = Products(8,  "MountainDew", 11.0, 10);
            inventory[8]  = Products(9,  "7Up",          9.0, 14);
            inventory[9]  = Products(10, "RedBull",     18.0,  8);
            inventory[10] = Products(11, "Sting",       12.0,  9);
            inventory[11] = Products(12, "Pakola",       8.0, 13);
        total_revenue = 50.0;
        total_sold = 0; 
        productCount = 12;
    }
    virtual void displayInventory() = 0;
    
    void buyProduct(){
        int id;
        double money;
        double price;
        cout<<"Enter Product ID : ";
        if(!(cin >> id) || id <= 0){
            cout<<"Invalid ID input!"<<endl;
            clearInput();
            return;
        }
        bool found = false;
        for(int i=0;i<productCount;i++){
            if(id == inventory[i].getId()){
                found = true;
                if(inventory[i].isAvailable()){
                    price = inventory[i].getPrice();
                    cout<<"Enter your Money : ";
                    if(!(cin >> money) || money < 0){
                        cout<<"Invalid money input!"<<endl;
                        clearInput();
                        return;
                    }
                    if(money>=price){
                        cout<<"Transaction Successfull. Enjoy your drink!"<<endl;
                        cout<<"Change : "<<money-price<<"$"<<endl;
                        inventory[i].reduceStock();
                        total_revenue +=price;
                        total_sold++;
                        inventory[i].addSale();
                        logTransaction(inventory[i].getName(),price,money,money-price);
                        saveInventory();
                    }
                    else{
                        cout<<"Not enough Money. Transaction Cancelled."<<endl;
                    }
                }
                else{
                    cout<<"Sorry! Out of Stock.";
                }
            }
        }
        if(!found){
            cout<<"Invalid ID entered.";
        }
    }
    void saveInventory() {
        ofstream file("vending_data.txt");
        if (!file) return;
        file << productCount << endl;
        for (int i = 0; i < productCount; i++) {
            file << inventory[i].getId() << " "
                << inventory[i].getName() << " "
                << inventory[i].getPrice() << " "
                << inventory[i].getStock() << " "
                << inventory[i].getUnitSale() << endl;
        }
        file << total_revenue << "\n" << total_sold << endl;
        file.close();
    }
    void loadInventory() {
        ifstream file("vending_data.txt");
        if (!file) {
            saveInventory();
            return;
        }   
        file >> productCount;
        if (productCount <= 0 || productCount > MAX_PRODUCTS) {
            return;
        }  
        for (int i = 0; i < productCount; i++) {
            int id, stock, sold;
            double price;
            string name;      
            file >> id >> name >> price >> stock >> sold;     
            inventory[i] = Products(id, name, price, stock);
            for (int j = 0; j < sold; j++) {
                inventory[i].addSale();
            }
        }
        file >> total_revenue >> total_sold;
        file.close();
    }
    void logTransaction(string name, double price, double paid, double change) {
        ofstream file("transactions.txt", ios::app);
        file << left
            << setw(15) << name
            << "Price: $"  << setw(6) << fixed << setprecision(2) << price
            << " Paid: $"  << setw(6) << paid
            << " Change: $" << change
            << endl;
        file.close();
    }

};
//----------Admin Class------------
class Admin : public VendingMachine{//Inheritence
private:
    const string password = "shazal123";
    bool logged_In = false;
    int total_stock = 0;
public:
    string passkey;
    int choice;
    bool found = false;
    void continue_again(){
        char x;
        cout<<"Do you wanna continue again(c) or exit(e)? : ";
        cin>>x;
        if(x=='c'){
            login();
        }
    }
    void login(){
        if(!logged_In){
            cout<<"Enter Password : ";
            cin>>passkey;
            if(passkey == password){
                cout<<"Correct Password."<<endl;
                logged_In = true;
            }
            else{
                cout<<"Incorrect Password. Access Deied"<<endl;
                return;
            }
        }
        displayInventory();
        cout<<"What do you want to do? \n1.Change Products Price \n2.Restock Products\n3.View details\n4.Add New Product\n";
        cout<<"--------------------------------------------"<<endl;
        cin>>choice;
        if(choice ==1){
            changePrice();
            }
            else if(choice==2){
                restockProduct();
            }
            else if(choice == 3){
                cout<<"Total Revenue : "<<total_revenue<<endl;
                cout<<"Total Sold Drinks : "<<total_sold<<endl;
                int max = inventory[0].getUnitSale();
                string popularDrink = inventory[0].getName();
                for(int i = 0;i<productCount;i++){
                    if(inventory[i].getUnitSale()>max){
                        max = inventory[i].getUnitSale();
                        popularDrink = inventory[i].getName();
                    }
                }
                cout<<"Most Popular Drink : "<<popularDrink<<endl;
            }
            else if(choice==4){
                addProduct();
            }
            continue_again();
    }
    //Overriding
    void displayInventory() override{
        cout<<left<<setw(5)<<"ID"<<setw(15)<<"Name"<<setw(7)<<"Price"<<setw(6)<<"Stock"<<endl;
        for(int i = 0; i<productCount;i++){
            inventory[i].display();
        }
    }
    void changePrice(){
        int change_id;
        double change_price;
        bool found = false;
        cout<<"Enter the product ID which you want to change : ";
        cin>>change_id;
        cout<<"Entered the changed price : ";
        if(!(cin >> change_price) || change_price < 0){
            cout<<"Invalid price entered!"<<endl;
            clearInput();
            return;
        }
        for(int i=0; i<productCount;i++){
            if(change_id == inventory[i].getId()){
                inventory[i].setPrice(change_price);
                found = true;
                break;
            }
        }
        if(!found){
            cout<<"Invalid ID entered!!"<<endl;
        }
        else{
            cout<<"Price Updated Successfully."<<endl;
        }
        displayInventory();
    }
    void restockProduct(){
        int change_id;
        double add_stock;
        double cost;
        cout<<"Enter the product ID which you want to change : ";
        cin>>change_id;
        cout<<"Entered the stock amount : ";
        if(!(cin >> add_stock) || add_stock < 0){
            cout<<"Invalid stock amount!"<<endl;
            clearInput();
            return;
        }
        for(int i=0; i<productCount;i++){
            if(change_id == inventory[i].getId()){
                cost = add_stock * inventory[i].getPrice();
                if(cost>total_revenue){
                    cout<<"Not enough revenue!"<<endl;
                    break;
                }
                else{
                    total_revenue -= cost;
                }
                inventory[i].setStock(inventory[i].getStock() + add_stock);
                found = true;
                cout<<"Revenue deducted by $"<<cost<<" for new stock"<<endl;
            }
        }
        if(!found){
                cout<<"Invalid ID"<<endl;
            }
        else{
            cout<<"Products Updated Successfully."<<endl;
        }
        displayInventory();
    }
    void addProduct() {
        if (productCount >= MAX_PRODUCTS) {
            cout << "Inventory Full! Cannot add more products." << endl;
            return;
        }
        int id, stock;
        string name;
        double price;
        cout << "Enter new product ID: ";
        cin >> id;
        cout << "Enter product name: ";
        cin >> name;
        cout << "Enter price: ";
        cin >> price;
        cout << "Enter stock: ";
        cin >> stock;
        if (price <= 0 || stock <= 0) {
            cout << "Invalid price or stock." << endl;
            return;
        }
        double cost = price * stock;
        if (total_revenue >= cost) {
            inventory[productCount++] = Products(id, name, price, stock);
            total_revenue -= cost;
            cout << "Product added successfully!" << endl;
            saveInventory();
        }
        else{
            cout << "Not enough revenue to add this product." << endl;
            return;
        }
    }
};
//------------Main Function-----------
int main(){
    cout<<"---Vending Machine---"<<endl;
    Admin machine;
    VendingMachine* vm = &machine ;
    char again;
    char admin_login;
    bool login= false;
    machine.loadInventory();
    do{
        cout<<"Press any key to continue or Press k for Admin Login : ";
        cin>>admin_login;
        if(admin_login=='k'){
            cout<<"---Welcome to admin panel---"<<endl;
            machine.login();
            machine.saveInventory();
            cout<<"Do you want to continue again?(y/n) : ";
            cin>>again;
        }
        else{
            vm ->displayInventory();
            machine.buyProduct();
            cout<<"Do you want to buy another drink?(y/n) : ";
            cin>>again;
        }
    }
    while(again=='y' || again == 'Y');
    cout<<"Thanks for using the Vending Machine.";
}