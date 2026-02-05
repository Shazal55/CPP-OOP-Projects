#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
using namespace std;
const int MAX_ROOM = 30;
class Room{
private:
    int roomNumber;
    string guestName;
    char roomType;
    double pricePerNight;
    int phoneNumber;
    bool isBooked;
public:
    
    Room(){
        roomNumber = 0;
        guestName = " ";
        roomType = ' ';
        pricePerNight = 0;
        isBooked = false;
        phoneNumber = 000000000000;
    }
    Room(int n, string o, char t, double p, bool b,int ph){
        roomNumber = n;
        guestName = o;
        roomType = t;
        pricePerNight = p;
        isBooked = b;
        phoneNumber = ph;
    }
    void setNumber(int n){
        roomNumber = n;
    }
    int getNumber(){
        return roomNumber;
    }
    void setGuest(string o){
        guestName = o;
    }
    string getGuest(){
        return guestName;
    }
    void setType(char a){
        roomType = a;
    }
    char getType(){
        return roomType;
    }
    void setPrice(double p){
        pricePerNight = p;
    }
    double getPrice(){
        return pricePerNight;
    }
    bool Booked(){
        return isBooked;
    }
    int getPhone() {
        return phoneNumber;
    }

    void checkoutRoom(){
        guestName = " ";
        isBooked = false;
        phoneNumber = 00000000;
    }

    void showDetails(){
        cout<<setw(12)<<"Room Number"<<setw(12)<<"Guest Name"<<setw(11)<<"Room Type"<<setw(15)<<"PricePerNight"<<setw(12)<<"Booking"<<setw(13)<<"Phone No."<<endl;
        cout<<setw(8)<<roomNumber<<setw(13)<<guestName<<setw(11)<<roomType<<setw(13)<<pricePerNight<<setw(13)<<Booked()<<setw(15)<<phoneNumber<<endl;
    }
};
class Hotel{
protected:
    Room room[MAX_ROOM];
    double total_revenue = 0;
    int Total_room = 0;
public:
    Hotel(){
        loadFromFile();
        if(Total_room == 0){
        room[0] = Room(1,  "Chris",  'B', 45, true,123432);
        room[1] =Room(2,  "",   'A', 60, false,0);
        room[2] =Room(3,  "Hamza",  'C', 30, true,6786787);
        room[3] =Room(4,  "Leo",    'B', 45, true,4637847);
        room[4] =Room(5,  "", 'A', 60, false,0);
        room[5] =Room(6,  "", 'C', 30, false,0);
        room[6] =Room(7,  "",    'B', 45, false,0);
        room[7] =Room(8,  "",  'C', 30, false,0);
        room[8] =Room(9,  "",  'A', 60, false,0);
        room[9] =Room(10, "",   'B', 45, false,0);
        room[10] =Room(11, "Yasir",  'A', 60, true,543345654);
        room[11] =Room(12, "Kevin",  'C', 30, true,45543234);
        room[12] =Room(13, "Ali",    'B', 45, true,2345654);
        room[13] =Room(14, "Noah",   'C', 30, true,23456543);
        room[14] =Room(15, "",   'A', 60, false,0);
        room[15] =Room(16, "",   'B', 45, false,0);
        room[16] =Room(17, "",   'C', 30, false,0);
        room[17] =Room(18, "",   'A', 60, false,0);
        room[18] =Room(19, "",   'B', 45, false,0);
        room[19] =Room(20, "",   'C', 30, false,0);
        room[20] =Room(21, "",   'A', 60, false,0);
        room[21] =Room(22, "",   'B', 45, false,0);
        room[22] =Room(23, "",   'C', 30, false,0);
        room[23] =Room(24, "",   'A', 60, false,0);
        room[24] =Room(25, "",   'B', 45, false,0);
        
        total_revenue = 0;
        Total_room = 25;
        }
    }
    bool again() {
        char x;
        while (true) {
            cout << "Do you want to continue again?? (y/n) : ";
            cin >> x;
            if (x == 'y' || x == 'Y')
                return true;
            if (x == 'n' || x == 'N')
                return false;
            cout << "Invalid input! Please enter y or n.\n";
            }
    }

    void openingWindow(){
        int choice;
        do {
            cout<<"------Customer Menu------\n"
                <<"1. Book a Room.\n"
                <<"2. Checkout your Room.\n"
                <<"3. View Hotel Rooms.\n"
                <<"4. View my Booking.\n"
                <<"5.Exit Program.\n";
            cin>>choice;
            switch(choice){
                case 1: 
                    bookRoom(); 
                    break;
                case 2: 
                    deleteRoom(); 
                    break;
                case 3: 
                    showHotelRooms(); 
                    break;
                case 4: 
                    viewMyBooking(); 
                    break;
                case 5:
                    return;
                default:
                cout<<"Invalid Choice Entered."<<endl;
            }

        } 
        while(again());
    }
                    
    void showHotelRooms(){
        cout<<endl;
        cout<<"-------------Room Details------------"<<endl;
        cout<<setw(12)<<"roomNumber"<<setw(12)<<"Guest Name"<<setw(11)<<"roomType"<<setw(15)<<"pricePerNight"<<setw(12)<<"isBooked"<<endl;
        for(int i = 0; i< Total_room; i++){
            cout<<setw(12)<<room[i].getNumber()<<setw(12)<<room[i].getGuest()<<setw(11)<<room[i].getType()<<setw(15)<<room[i].getPrice()<<setw(12)<<room[i].Booked()<<endl;
        }
    }

    void viewMyBooking(){
        int num;
        cout<<"Enter your Room Number : ";
        cin>>num;
        if(num < 1 || num > MAX_ROOM){
            cout << "Invalid room number!\n";
        }
        else{
            if(room[num-1].Booked()){
                room[num-1].showDetails();
            }
            else{
                cout<<"There is no booking for this Room."<<endl;
            }
        }

    }
    void deleteRoom(){
        int num;
        cout<<"Enter your Room Number : ";
        cin>>num;
        if(num < 1 || num > MAX_ROOM){
            cout << "Invalid room number!\n";
        }
        else{
            room[num-1].showDetails();
            if(!room[num-1].Booked()){
                cout<<"Room is already vacant."<<endl;
            }
            else{
                room[num-1].checkoutRoom();
                cout<<"Room "<<num<<" CheckedOut Successfully."<<endl;
            }
        }
    }

    void bookRoom(){
        int num,phone,day, price;
        string name;
        char type;
        double bill;
        viewAvailableRooms();
        cout<<"Enter Room Number(1-30) : ";
        cin>>num;
        if(num < 1 || num > Total_room){
            cout << "Invalid room number!\n";
        }
        else if(room[num - 1].Booked()){
            cout << "Room already booked!\n";
        }
        else{
            cout<<"Enter Name for Registeration : ";
            cin>>name;
            type = room[num-1].getType();
            price = room[num-1].getPrice();
            cout<<"How many days are you going to stay : ";
            cin>>day;
            cout<<"Enter Phone number : ";
            cin>>phone;
            bill = price * day;
            room[num-1].setNumber(num);
            room[num-1].setGuest(name);
            room[num-1].setPrice(price);
            room[num-1].setType(type);
            room[num-1] = Room(num,name,type,price,true,phone);

            total_revenue += bill;
            cout<<"Room Booked Successfully"<<endl;
            room[num-1].showDetails();
            cout<<"Total Bill : "<<bill<<" $"<<endl;
            }
    }

    void viewAvailableRooms(){
        cout<<"-------------Available Rooms---------------"<<endl;
        cout<<"-------------------------------------------"<<endl;
        cout<<setw(12)<<"Room Number"<<setw(12)<<"Room Type"<<setw(17)<<"Price per Night"<<endl;
        cout<<"-------------------------------------------"<<endl;
        for(int i = 0; i<Total_room; i++){
            if(!room[i].Booked()){
                cout<<setw(10)<<room[i].getNumber()<<setw(12)<<room[i].getType()<<setw(15)<<room[i].getPrice()<<endl;
            }
        }
    }
    
    void saveToFile() {
        ofstream file("rooms.csv");

        if (!file) {
            cout << "Error saving data!\n";
            return;
        }

        file << "TotalRooms," << Total_room << endl;
        file << "RoomNumber,GuestName,RoomType,Price,Booked,Phone" << endl;

        for (int i = 0; i < Total_room; i++) {
            file << room[i].getNumber() << ","
                << room[i].getGuest() << ","
                << room[i].getType() << ","
                << room[i].getPrice() << ","
                << room[i].Booked() << ","
                << room[i].getPhone() << endl;
        }

        file.close();
    }

    void loadFromFile() {
        ifstream file("rooms.csv");

        if (!file) return;

        string line;
        getline(file, line);   // TotalRooms line
        Total_room = stoi(line.substr(line.find(",") + 1));

        getline(file, line);   // header line

        for (int i = 0; i < Total_room; i++) {
            int num, booked, phone;
            char type;
            double price;
            string name;

            getline(file, line);
            stringstream ss(line);

            string temp;
            getline(ss, temp, ','); num = stoi(temp);
            getline(ss, name, ',');
            getline(ss, temp, ','); type = temp[0];
            getline(ss, temp, ','); price = stod(temp);
            getline(ss, temp, ','); booked = stoi(temp);
            getline(ss, temp, ','); phone = stoi(temp);

            room[i] = Room(num, name, type, price, booked, phone);
        }

        file.close();
    }




};
class Admin : public Hotel{
private:
    const string password = "shazal123";
    bool is_logged = false;
public:
    void login(){
        string passkey;
        while(!is_logged){
            cout<<"Enter Admin's Password : ";
            cin>>passkey;
            if(password == passkey){
                cout<<"Login Successfully!\n"<<endl;
                cout<<"---Welcome to Admin Menu---"<<endl;
                is_logged = true;
                admin_menu();
            }
        }
    }
    void admin_menu() {
        int choice;
        do {
            cout<<"------Admin Menu------\n"
                <<"\n1.View all Rooms"
                <<"\n2.View all bookings"
                <<"\n3.Add new Room"
                <<"\n4.Remove Room"
                <<"\n5.Update Room Price"
                <<"\n6.View Total Revenue"
                <<"\n7.Exit\n";
            cout<<"What do you wanna do?? : ";
            cin>>choice;
            switch(choice) {
                case 1: 
                    Hotel::showHotelRooms(); 
                    break;
                case 2: 
                    BookedRooms(); 
                    break;
                case 3: 
                    addRoom();  
                    break;
                case 4:     
                    delRoom(); 
                    break;
                case 5: 
                    updatePrice(); 
                    break;
                case 6: 
                    showRevenue(); 
                    break;
                case 7:
                    return;
                    break;
                default: 
                    cout<<"Invalid Choice!\n";
            }

        } while(again());
    }


    void BookedRooms(){
        cout<<setw(12)<<"roomNumber"<<setw(12)<<"Guest Name"<<setw(11)<<"roomType"<<setw(15)<<"pricePerNight"<<setw(12)<<"isBooked"<<endl;
        for(int i = 0;i<MAX_ROOM;i++){
            if(room[i].Booked()){
                cout<<setw(12)<<room[i].getNumber()<<setw(12)<<room[i].getGuest()<<setw(11)<<room[i].getType()<<setw(15)<<room[i].getPrice()<<setw(12)<<room[i].Booked()<<endl;
            }
        }
    }

    void addRoom(){
        int num,phone;
        double price;
        char type;
        string name;
        bool booked;
        num = Total_room+1;
        name = "";
        phone = 0000000;
        booked = false;
        cout<<"Enter Room Type : ";
        cin>>type;
        if(type == 'A'){
            price = 60;
        }
        else if(type == 'B'){
            price = 45;
        }
        else  if(type == 'C'){
            price = 30;
        }
        else{
            cout<<"Invalid Type entered!"<<endl;
        }
        Total_room++;
        room[num-1] = Room(num,name,type,price,booked,phone);
        cout<<"Room Added Successfully!"<<endl;
        Hotel::showHotelRooms();
    }

    void delRoom(){
        int num;
        cout<<"Enter room number you want to delete : ";
        cin>>num;
        if(num<0 || num >MAX_ROOM){
            cout<<"Invalid Room number entered!"<<endl;
            return;
        }
        if(!room[num-1].Booked()){
            cout<<"The Room "<<num<<" is already vacant."<<endl;
            return;
        }
        room[num-1].checkoutRoom();
        cout<<"Room removed successfully."<<endl;
        Hotel::showHotelRooms();
    }

    void updatePrice(){
        char type;
        double price;
        cout<<"Which room type price you want to change? Enter Type : ";
        cin>>type;
        if(type == 'A'){
            price = 60;
        }
        else if(type == 'B'){
            price = 45;
        }
        else  if(type == 'C'){
            price = 30;
        }
        else{
            cout<<"Invalid Type entered!"<<endl;
            return;
        }
        cout<<"Enter new Price : ";
        cin>>price;
        for(int i = 0;i<Total_room;i++){
            if(room[i].getType() == type){
                room[i].setPrice(price);
            }
        }
        cout<<"Price updated Successfully."<<endl;
        Hotel::showHotelRooms();
    }

    void showRevenue() {
        double revenue = 0;
        for(int i = 0; i < Total_room; i++){
            if(room[i].Booked()){
                revenue += room[i].getPrice();
            }
        }
        cout << "Total revenue generated : " << revenue << "$" << endl;
    }

};
int main() {
    cout<<"Welcome to the Sky view Hotel."<<endl;
    char choice;
    Admin ad;

    cout<<"Press c to continue as User or Press a for Admin Login : ";
    cin>>choice;

    if(choice == 'c'){
        ad.openingWindow();
        ad.saveToFile();
    }
    else if(choice == 'a'){
        ad.login();
        ad.saveToFile();
    }
    else{
        cout<<"Invalid Choice entered!!"<<endl;
        return 1;
    }

    cout<<"Thanks for Coming."<<endl;
    return 0;
}
