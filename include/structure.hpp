#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <string>
#include <fstream>
#include <iostream>
#define N 20
#define M 100
#define INT_MAX 2147483647

using namespace std;

class map{
    public:
        map(); //done
        void insert(int u, int v, int length); //done
        int get_length(int u, int v); //done
        int numofStation;
        int graph[N][N];
        void floydWarshall(void);  
};

class station{

    public:
        int numofElectric;
        int numofLady;
        int numofRoad;
        int ElectricToAdd;
        int LadyToAdd;
        int RoadToAdd;
        station(); //done
        void setId(int n); //done
        void setElectric(int num); //done
        void setLady(int num); //done
        void setRoad(int num); //done
        void addBike(int kind, int bikeId); //done
        int rentBike(int kind); //done
        void generateBikeId(void); //done
        int* getSorted(int kind);
        //~station(); //done
    private:
        int* Electric;
        int* Lady;
        int* Road;
        int stationId;        
        void heapify(int arr[], int n, int i); //done
        void buildheap(int arr[], int n); //done        
};


class feePolicy{
    public:
        int electricDiscountedRate;
        int electricRegularRate;
        int ladyDiscountedRate;
        int ladyRegularRate;
        int roadDiscountedRate;
        int roadRegularRate;
        int RateOfWaitingFee;
        double ReducedRateForSwitch;
        int RateOfTransferingFee;
};

class user{
    public:
        int userId;
        int occupiedBikeKind;
        int occupiedBikeId;
        int stationIdRent;
        int rentTime;
        bool switched;
        int wait;
};

class System{
    public:
        string Rent(int stationIdRent, string bikeType, int userid, int timeRent); //done
        void Return(int staionIdReturn, int userid, int timeReturn); //done
        string Print(void); //done
        System();//done
        //~System(); //done
    private:

        map Map;
        user* Users;
        double Revenue;
        feePolicy Discount;
        station* Stations;
        void readMap(void); //done
        void readStation(void); //done
        void setPolicy(void); //done
};


class pseudoRentTestCase{
    public:
        int stationId;
        string bikeType;
        int userId;
        int timeRent;
};

class pseudoReturnTestCase{
    public:
        public:
        int stationId;
        int userId;
        int timeReturn;
};


class System2{
    public:
        string Rent(int stationIdRent, string bikeType, int userid, int timeRent); //done
        void Return(int staionIdReturn, int userid, int timeReturn); //done
        string Print(void); //done
        
        int pRentTCsnum;
        int pReturnTCsnum; 
        pseudoRentTestCase* pRentTCs;
        pseudoReturnTestCase* pReturnTCs;
        void checkless(int arr[3]); //done
        void generatePseudoRentTestCase(int stationIdRent, int bikeType, int userId, int timeRent); //done
        void generatePseudoReturnTestCase(int stationIdReturn, int bikeType, int userId, int timeReturn); //done
        int calculator(bool electricIsAllowed, bool ladyIsAllowed, bool roadIsAllowed, int stationId, string bikeType, int timeRent);
        bool timer(int situation, int time); //done
        void heapify(pseudoReturnTestCase arr[], int n, int i); //done
        void buildheap(pseudoReturnTestCase arr[], int n); //done
        void heapify(pseudoRentTestCase arr[], int n, int i); //done
        void buildheap(pseudoRentTestCase arr[], int n); //done
        

        System2();//done
        //~System2(); //done        
        map Map; 
        user* Users;
        double Revenue;
        feePolicy Discount;
        station* Stations;
        void readMap(void); //done
        void readStation(void); //done
        void setPolicy(void); //done
};


map::map(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++)
            graph[i][j] = INT_MAX;
        graph[i][i] = 0;
    }
}

void map::insert(int u, int v, int length){
    graph[u][v] = length;
    graph[v][u] = length;
}

int map::get_length(int u, int v){
    return graph[u][v];
}

void map::floydWarshall()
{
    for (int k = 1; k < numofStation; k++) {
        for (int i = 1; i < numofStation; i++) {
            for (int j = 1; j < numofStation; j++) {
                 if (graph[i][j] > (graph[i][k] + graph[k][j]) && (graph[k][j] != INT_MAX && graph[i][k] != INT_MAX))
                    graph[i][j] = graph[i][k] + graph[k][j];
            }
        }
    }
}

station::station(){
    numofElectric = 0;
    numofLady = 0;
    numofRoad = 0;
    ElectricToAdd = 0;
    LadyToAdd = 0;
    RoadToAdd = 0;
    int* Electric = new int[M];
    int* Lady = new int[M];
    int* Road = new int[M];
    for(int k = 0; k < M; k++){
        Electric[k] = 0;
        Lady[k] = 0;
        Road[k] = 0;
    }
}

void station::setId(int n){
    stationId = n;
}

void station::setElectric(int num){
    Electric = new int[num];
    for(int i = 0; i < num; i++){
        Electric[i] = 0;
    }
}
void station::setLady(int num){
    Lady = new int[num];
    for(int i = 0; i < num; i++){
        Lady[i] = 0;
    }
}
void station::setRoad(int num){
    Road = new int[num];
    for(int i = 0; i < num; i++){
        Road[i] = 0;
    }
}

void station::heapify(int arr[], int n, int i){
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] < arr[smallest])
        smallest = l;
    
    if (r < n && arr[r] < arr[smallest])
        smallest = r;
    
    if(smallest != i){
        int tmp = arr[i];
        arr[i] = arr[smallest];
        arr[smallest] = tmp;
        heapify(arr,n,smallest);
    }
}

void station::buildheap(int arr[], int n){
    int startIdx = (n/2)-1;

    for (int i = startIdx; i >= 0; i--){
        heapify(arr,n,i);
    }
}

void station::addBike(int kind, int bikeId){
    if(bikeId != 0){
        if (kind == 0){
            //cout << bikeId << endl;
            Electric[numofElectric++] = bikeId;
            buildheap(Electric, numofElectric);            
        }
        else if (kind == 1){
            Lady[numofLady++] = bikeId;
            buildheap(Lady, numofLady);
        }
        else if (kind == 2){
            Road[numofRoad++] = bikeId;
            buildheap(Road, numofRoad);
        }
    }
}

int station::rentBike(int kind){
    if (kind == 0){
        if(numofElectric == 0)
            return -1;
        int bikeId = Electric[0];
        Electric[0] = Electric[--numofElectric];
        Electric[numofElectric] = 0;
        buildheap(Electric, numofElectric);
        return bikeId;
    }
    else if (kind == 1){
        if(numofLady == 0)
            return -1;
        int bikeId = Lady[0];
        Lady[0] = Lady[--numofLady];
        Lady[numofLady] = 0;
        buildheap(Lady, numofLady);
        return bikeId;
    }
    else if (kind == 2){
        if(numofRoad == 0)
            return -1;      
        int bikeId = Road[0];
        Road[0] = Road[--numofRoad];
        Road[numofRoad] = 0;
        buildheap(Road, numofRoad);
        return bikeId;
    }

    return -1;
}

void station::generateBikeId(void){
    for(int i = 0; i < numofElectric; i++)
        Electric[i] = stationId * 100 + i;
    for(int i = 0; i < numofLady; i++)
        Lady[i] = stationId * 100 + i;
    for(int i = 0; i < numofRoad; i++)
        Road[i] = stationId * 100 + i;
}

int* station::getSorted(int kind){
    int *arr1;
    int *arr2;
    int length;
    int index;

    if(kind == 0){
        length = numofElectric;    
        arr1 = new int[numofElectric];
        arr2 = new int[numofElectric];
        for(int i = 0; i < numofElectric; i++)
            arr1[i] = Electric[i];
    }
    else if (kind == 1){
        length = numofLady;    
        arr1 = new int[numofLady];
        arr2 = new int[numofLady];
        for(int i = 0; i < numofLady; i++)
            arr1[i] = Lady[i];
    }
    else if (kind == 2){
        length = numofRoad;    
        arr1 = new int[numofRoad];
        arr2 = new int[numofRoad];
        for(int i = 0; i < numofRoad; i++)
            arr1[i] = Road[i];
    }
    index = length;

    for(int i = 0; i < length; i++){
        arr2[i] = arr1[0];
    
        arr1[0] = arr1[--index];
        heapify(arr1, index, 0);
    }

    return arr2;
}
/*
station::~station(){
    delete Electric;
    delete Lady;
    delete Road;
}
*/

System::System(){

    Revenue = 0;
    readMap();
    readStation();
    setPolicy();
    Users = new user[100010];

}

void System::readMap(void){
    ifstream mp;
    mp.open("test_case/map.txt");
    int u, v, length;
    int max = -1;
    while(mp >> u){
        mp >> v >> length;
        if(u > max || v > max){
            if (u > v)
                max = u;
            else
                max = v;
        }
        Map.insert(u,v,length);
    }
    Map.numofStation = max+1;

    //cout << Map.numofStation << endl;
    /*
    for(int i = 1; i < Map.numofStation; i++){
        for(int j = 1; j < Map.numofStation; j++)
            cout << Map.graph[i][j] << " ";
        cout << endl;
    }

    cout << " " << endl;
    */
    Map.floydWarshall();
    /*
    for(int i = 1; i < Map.numofStation; i++){
        for(int j = 1; j < Map.numofStation; j++)
            cout << Map.graph[i][j] << " ";
        cout << endl;
    }
    */

}

void System::readStation(void){
    ifstream st;
    st.open("test_case/station.txt");
    Stations = new station[Map.numofStation];
    int Id;
    while(st >> Id){
        Stations[Id].setId(Id);
        st >> Stations[Id].numofElectric >> Stations[Id].numofLady >> Stations[Id].numofRoad;
        Stations[Id].setElectric(100);
        Stations[Id].setLady(100);
        Stations[Id].setRoad(100);
        Stations[Id].generateBikeId();
    }
}

void System::setPolicy(void){
    ifstream fee;
    fee.open("test_case/fee.txt");
    string cmd;

    for(int i = 0; i < 3; i++){
        fee >> cmd;
        if(cmd == "electric")
            fee >> Discount.electricDiscountedRate >> Discount.electricRegularRate;
        else if(cmd == "lady")
            fee >> Discount.ladyDiscountedRate >> Discount.ladyRegularRate;
        else if(cmd == "road")
            fee >> Discount.roadDiscountedRate >> Discount.roadRegularRate;
    }

    fee >> Discount.RateOfWaitingFee >> Discount.ReducedRateForSwitch >> Discount.RateOfTransferingFee;
}


string System::Rent(int stationIdRent, string bikeType, int userid, int timeRent){
    Users[userid].userId = userid;
    int bikeId = -1;
    if (bikeType == "electric")
        bikeId = Stations[stationIdRent].rentBike(0);
    else if (bikeType == "lady")
        bikeId = Stations[stationIdRent].rentBike(1);
    else if (bikeType == "road")
        bikeId = Stations[stationIdRent].rentBike(2);

    if (bikeId == -1)
        return "reject";

    if (bikeType == "electric")
        Users[userid].occupiedBikeKind = 0;
    else if (bikeType == "lady")
        Users[userid].occupiedBikeKind = 1;
    else if (bikeType == "road")
        Users[userid].occupiedBikeKind = 2;
    
    Users[userid].rentTime = timeRent;
    Users[userid].occupiedBikeId = bikeId;
    Users[userid].stationIdRent = stationIdRent;
    
    return "accept";    
}

void System::Return(int stationIdReturn, int userid, int timeReturn){
    if (Users[userid].occupiedBikeId != 0){
        Stations[stationIdReturn].addBike(Users[userid].occupiedBikeKind, Users[userid].occupiedBikeId);
        int delta = timeReturn - Users[userid].rentTime;
        if (Users[userid].occupiedBikeKind == 0){
            if (delta <= Map.graph[Users[userid].stationIdRent][stationIdReturn])
                Revenue += delta * Discount.electricDiscountedRate;
            else
                Revenue += delta * Discount.electricRegularRate;
        }
        else if (Users[userid].occupiedBikeKind == 1){
            if (delta <= Map.graph[Users[userid].stationIdRent][stationIdReturn])
                Revenue += delta * Discount.ladyDiscountedRate;
            else
                Revenue += delta * Discount.ladyRegularRate;
        }
        else if (Users[userid].occupiedBikeKind == 2){
            if (delta <= Map.graph[Users[userid].stationIdRent][stationIdReturn])
                Revenue += delta * Discount.roadDiscountedRate;
            else
                Revenue += delta * Discount.roadRegularRate;
        } 
        //cout << delta << endl;
    }
}

string System::Print(void){
    string ans = "";
    for(int i = 1; i < Map.numofStation; i++){
        ans += to_string(i) + ":\n";

        //cout << ans << endl;
        ans += "electric:";
        int* arr = Stations[i].getSorted(0);
        for(int j = 0; j < Stations[i].numofElectric; j++)
            ans += " " + to_string(arr[j]);
        ans += "\n";

        ans += "lady:";
        arr = Stations[i].getSorted(1);
        for(int j = 0; j < Stations[i].numofLady; j++)
            ans += " " + to_string(arr[j]);
        ans += "\n";

        ans += "road:";
        arr = Stations[i].getSorted(2);
        for(int j = 0; j < Stations[i].numofRoad; j++)
            ans += " " + to_string(arr[j]);
        ans += "\n";
    }
    ans += to_string((int)Revenue);

    return ans;
}

/*

System::~System(void){
    delete Users;
    delete Stations;
}
*/

System2::System2(){

    Revenue = 0;
    readMap();
    readStation();
    setPolicy();
    Users = new user[350000];
    for(int i = 0; i < 350000; i++){
        Users[i].wait = 0;
    }
    pRentTCsnum = 0;
    pReturnTCsnum = 0; 
    pRentTCs = new pseudoRentTestCase[500];
    pReturnTCs = new pseudoReturnTestCase[500];

}

void System2::readMap(void){
    ifstream mp;
    mp.open("test_case/map.txt");
    int u, v, length;
    int max = -1;
    while(mp >> u){
        mp >> v >> length;
        if(u > max || v > max){
            if (u > v)
                max = u;
            else
                max = v;
        }
        Map.insert(u,v,length);
    }
    Map.numofStation = max+1;

    //cout << Map.numofStation << endl;
/*
    for(int i = 1; i < Map.numofStation; i++){
        for(int j = 1; j < Map.numofStation; j++)
            cout << Map.graph[i][j] << " ";
        cout << endl;
    }

    cout << " " << endl;
*/
    Map.floydWarshall();
/*    
    for(int i = 1; i < Map.numofStation; i++){
        for(int j = 1; j < Map.numofStation; j++)
            cout << Map.graph[i][j] << " ";
        cout << endl;
    }
*/

}

void System2::readStation(void){
    ifstream st;
    st.open("test_case/station.txt");
    Stations = new station[Map.numofStation];
    int Id;
    while(st >> Id){
        Stations[Id].setId(Id);
        st >> Stations[Id].numofElectric >> Stations[Id].numofLady >> Stations[Id].numofRoad;
        Stations[Id].setElectric(100);
        Stations[Id].setLady(100);
        Stations[Id].setRoad(100);
        Stations[Id].generateBikeId();
        Stations[Id].ElectricToAdd = 0;
        Stations[Id].LadyToAdd = 0;
        Stations[Id].RoadToAdd = 0;
    }
}

void System2::setPolicy(void){
    ifstream fee;
    fee.open("test_case/fee.txt");
    string cmd;

    for(int i = 0; i < 3; i++){
        fee >> cmd;
        if(cmd == "electric")
            fee >> Discount.electricDiscountedRate >> Discount.electricRegularRate;
        else if(cmd == "lady")
            fee >> Discount.ladyDiscountedRate >> Discount.ladyRegularRate;
        else if(cmd == "road")
            fee >> Discount.roadDiscountedRate >> Discount.roadRegularRate;
    }

    fee >> Discount.RateOfWaitingFee >> Discount.ReducedRateForSwitch >> Discount.RateOfTransferingFee;
}


string System2::Rent(int stationIdRent, string bikeType, int userid, int timeRent){
    Users[userid].userId = userid;
    Users[userid].switched = false;
    int bikeId = -1;

    // if the user is by company
    if(userid > 99999){
        if (bikeType == "electric")
            bikeId = Stations[stationIdRent].ElectricToAdd--;
        else if (bikeType == "lady")
            bikeId = Stations[stationIdRent].LadyToAdd--;
        else if (bikeType == "road")
            bikeId = Stations[stationIdRent].RoadToAdd--;
    }


    // rent normally
    if (bikeType == "electric")
        bikeId = Stations[stationIdRent].rentBike(0);
    else if (bikeType == "lady")
        bikeId = Stations[stationIdRent].rentBike(1);
    else if (bikeType == "road")
        bikeId = Stations[stationIdRent].rentBike(2);

    // if no bike is allowed
    bool flag = true;
    bool electricIsAllowed = true;
    bool ladyIsAllowed = true;
    bool roadIsAllowed = true;
    string tmp = "";
    while (bikeId == -1 && flag){
        int judge = calculator(electricIsAllowed, ladyIsAllowed, roadIsAllowed, stationIdRent, bikeType, timeRent);
        if(judge == 0){
            bikeId = Stations[stationIdRent].rentBike(0);
            if(bikeId == -1)
                electricIsAllowed = false;
            else{    
                Users[userid].switched = true;
                flag = false;
                tmp = "discount electric";
            }
        }
        else if(judge == 1){
            bikeId = Stations[stationIdRent].rentBike(1);
            if(bikeId == -1)
                ladyIsAllowed = false;
            else{   
                Users[userid].switched = true; 
                flag = false;
                tmp = "discount lady";
            }
        }
        else if(judge == 2){
            bikeId = Stations[stationIdRent].rentBike(2);
            if(bikeId == -1)
                roadIsAllowed = false;
            else{ 
                Users[userid].switched = true;   
                flag = false;
                tmp = "discount road";
            }
        }
        else if(judge == 3){
            if (bikeType == "electric"){
                generatePseudoRentTestCase(stationIdRent, 0, userid, timeRent+1);
            }
            else if (bikeType == "lady"){
                generatePseudoRentTestCase(stationIdRent, 1, userid, timeRent+1);
            }
            else if (bikeType == "road"){
                generatePseudoRentTestCase(stationIdRent, 2, userid, timeRent+1);
            }
            Revenue -= Discount.RateOfWaitingFee;
            Users[userid].wait += 1;
            flag = false;
            tmp = "wait";
        }
        else if(judge == 4){
            flag = false;
            tmp = "reject";
        }
    }

    if(flag){
        if (bikeType == "electric")
            Users[userid].occupiedBikeKind = 0;
        else if (bikeType == "lady")
            Users[userid].occupiedBikeKind = 1;
        else if (bikeType == "road")
            Users[userid].occupiedBikeKind = 2;
    
        Users[userid].rentTime = timeRent;
        Users[userid].occupiedBikeId = bikeId;
        Users[userid].stationIdRent = stationIdRent;
        return "accept"; 
    }
    else if (tmp == "discount electric"){
        Users[userid].occupiedBikeKind = 0;  
        Users[userid].rentTime = timeRent;
        Users[userid].occupiedBikeId = bikeId;
        Users[userid].stationIdRent = stationIdRent;
        return tmp;
    }
    else if (tmp == "discount lady"){
        Users[userid].occupiedBikeKind = 1;  
        Users[userid].rentTime = timeRent;
        Users[userid].occupiedBikeId = bikeId;
        Users[userid].stationIdRent = stationIdRent;
        return tmp;
    }
    else if (tmp == "discount road"){
        Users[userid].occupiedBikeKind = 2;  
        Users[userid].rentTime = timeRent;
        Users[userid].occupiedBikeId = bikeId;
        Users[userid].stationIdRent = stationIdRent;
        return tmp;
    }

    return tmp;       
}

void System2::Return(int stationIdReturn, int userid, int timeReturn){
    if (Users[userid].occupiedBikeId != 0){  
        if (userid > 99999){
                                 //if user is from company
            Stations[stationIdReturn].addBike(Users[userid].occupiedBikeKind, Users[userid].occupiedBikeId);
            
            int delta = timeReturn - Users[userid].rentTime + Users[userid].wait;
            if (Users[userid].occupiedBikeKind == 0){
                if (delta <= Map.graph[Users[userid].stationIdRent][stationIdReturn])
                    Revenue -= delta * Discount.RateOfTransferingFee /7;
                else
                    Revenue -= delta * Discount.RateOfTransferingFee /7;
            }
            else if (Users[userid].occupiedBikeKind == 1){
                if (delta <= Map.graph[Users[userid].stationIdRent][stationIdReturn])
                    Revenue -= delta * Discount.RateOfTransferingFee /7;
                else
                    Revenue -= delta * Discount.RateOfTransferingFee /7;
            }
            else if (Users[userid].occupiedBikeKind == 2){
                if (delta <= Map.graph[Users[userid].stationIdRent][stationIdReturn])
                    Revenue -= delta * Discount.RateOfTransferingFee /7;
                else
                    Revenue -= delta * Discount.RateOfTransferingFee /7; 
            }
            
        } 
        else if (Users[userid].switched){    //switched
            Stations[stationIdReturn].addBike(Users[userid].occupiedBikeKind, Users[userid].occupiedBikeId);
            int delta = timeReturn - Users[userid].rentTime;
            if (Users[userid].occupiedBikeKind == 0){
                if (delta <= Map.graph[Users[userid].stationIdRent][stationIdReturn])
                    Revenue += delta * Discount.electricDiscountedRate * Discount.ReducedRateForSwitch;
                else
                    Revenue += delta * Discount.electricRegularRate  * Discount.ReducedRateForSwitch;
            }
            else if (Users[userid].occupiedBikeKind == 1){
                if (delta <= Map.graph[Users[userid].stationIdRent][stationIdReturn])
                    Revenue += delta * Discount.ladyDiscountedRate * Discount.ReducedRateForSwitch;
                else
                    Revenue += delta * Discount.ladyRegularRate  * Discount.ReducedRateForSwitch;
            }
            else if (Users[userid].occupiedBikeKind == 2){
                if (delta <= Map.graph[Users[userid].stationIdRent][stationIdReturn])
                    Revenue += delta * Discount.roadDiscountedRate * Discount.ReducedRateForSwitch;
                else
                    Revenue += delta * Discount.roadRegularRate  * Discount.ReducedRateForSwitch;
            }
        }     
        else{                                   //normally rented
            Stations[stationIdReturn].addBike(Users[userid].occupiedBikeKind, Users[userid].occupiedBikeId);
            int delta = timeReturn - Users[userid].rentTime;
            if (Users[userid].occupiedBikeKind == 0){
                if (delta <= Map.graph[Users[userid].stationIdRent][stationIdReturn])
                    Revenue += delta * Discount.electricDiscountedRate;
                else
                    Revenue += delta * Discount.electricRegularRate;
            }
            else if (Users[userid].occupiedBikeKind == 1){
                if (delta <= Map.graph[Users[userid].stationIdRent][stationIdReturn])
                    Revenue += delta * Discount.ladyDiscountedRate;
                else
                    Revenue += delta * Discount.ladyRegularRate;
            }
            else if (Users[userid].occupiedBikeKind == 2){
                if (delta <= Map.graph[Users[userid].stationIdRent][stationIdReturn])
                    Revenue += delta * Discount.roadDiscountedRate;
                else
                    Revenue += delta * Discount.roadRegularRate;
            }
        }

        Users[userid].occupiedBikeId = 0;
        Users[userid].occupiedBikeKind = 3;
        Users[userid].rentTime = 0;
        Users[userid].stationIdRent = 0;
        Users[userid].switched = false;
        //cout << delta << endl;
    }
}

string System2::Print(void){
    string ans = "";
    for(int i = 1; i < Map.numofStation; i++){
        ans += to_string(i) + ":\n";

        //cout << ans << endl;
        ans += "electric:";
        int* arr = Stations[i].getSorted(0);
        for(int j = 0; j < Stations[i].numofElectric; j++)
            ans += " " + to_string(arr[j]);
        ans += "\n";

        ans += "lady:";
        arr = Stations[i].getSorted(1);
        for(int j = 0; j < Stations[i].numofLady; j++)
            ans += " " + to_string(arr[j]);
        ans += "\n";

        ans += "road:";
        arr = Stations[i].getSorted(2);
        for(int j = 0; j < Stations[i].numofRoad; j++)
            ans += " " + to_string(arr[j]);
        ans += "\n";
    }
    ans += to_string((int)Revenue);

    return ans;
}

void System2::checkless(int arr[3]){

    bool flag = false;
    for(int i = 1; i < Map.numofStation; i++){
        //cout << i << endl;
        //cout << 0 << " " << Stations[i].ElectricToAdd << endl;
        //cout << 1 << " " << Stations[i].LadyToAdd << endl;
        //cout << 2 << " " << Stations[i].RoadToAdd << endl;
        if (Stations[i].numofElectric + Stations[i].ElectricToAdd < 1){
            //cout << "inElectric" << endl;
            //cout << Stations[i].ElectricToAdd << endl;
            arr[0] = i;
            arr[1] = 0;
            //cout << "setting here" << " " <<  arr[1] << endl;
            flag = true;
            break;
        }
        else if (Stations[i].numofLady + Stations[i].LadyToAdd < 1){
            //cout << "inLady" << endl;
            arr[0] = i;
            arr[1] = 1;
            flag = true;
            break;
        }
        else if (Stations[i].numofRoad + Stations[i].RoadToAdd < 1){
            //cout << "inRoad" << endl;
            arr[0] = i;
            arr[1] = 2;
            flag = true;
            break;
        }
    }
    //cout << "go here1" << endl;
    if (flag){

        if (arr[1] == 0){
            int max = Stations[0].numofElectric;
            for(int i = 1; i < Map.numofStation; i++){
                if (Stations[i].numofElectric > max){
                    max = Stations[i].numofElectric;
                    arr[2] = i;
                }
            }
        }
        else if (arr[1] == 1){
            int max = Stations[0].numofLady;
            for(int i = 1; i < Map.numofStation; i++){
                if (Stations[i].numofLady > max){
                    max = Stations[i].numofLady;
                    arr[2] = i;
                }
            }
        }
        else if (arr[1] == 2){
            int max = Stations[0].numofRoad;
            for(int i = 1; i < Map.numofStation; i++){
                if (Stations[i].numofRoad > max){
                    max = Stations[i].numofRoad;
                    arr[2] = i;
                }
            }
        }
    }
}
void System2::generatePseudoRentTestCase(int stationIdRent, int bikeType, int userId, int timeRent){
    pRentTCs[pRentTCsnum].stationId = stationIdRent;
    if (bikeType == 0)
        pRentTCs[pRentTCsnum].bikeType = "electric";
    else if (bikeType == 1)
        pRentTCs[pRentTCsnum].bikeType = "lady";
    else if (bikeType == 2)
        pRentTCs[pRentTCsnum].bikeType = "road";
    pRentTCs[pRentTCsnum].userId = userId;
    pRentTCs[pRentTCsnum++].timeRent = timeRent+1;
    
    buildheap(pRentTCs,pRentTCsnum);
    
}

void System2::generatePseudoReturnTestCase(int stationIdReturn, int bikeType, int userId, int timeReturn){
    pReturnTCs[pRentTCsnum].stationId = stationIdReturn;
    if(bikeType == 0){
        Stations[stationIdReturn].ElectricToAdd++;
        //cout << "runhere" << endl;
    }
    else if(bikeType == 1)
        Stations[stationIdReturn].LadyToAdd++;
    else if(bikeType == 2)
        Stations[stationIdReturn].RoadToAdd++;
    pRentTCs[pReturnTCsnum].userId = userId;
    pRentTCs[pReturnTCsnum++].timeRent = timeReturn;
    buildheap(pReturnTCs,pReturnTCsnum);
}
int System2::calculator(bool electricIsAllowed, bool ladyIsAllowed, bool roadIsAllowed, int stationId, string bikeType, int timeRent){
    
    //calculate estimatedWaitRevenue
    int estimatedWaitRevenue = 0;
    for(int i = 1; i < Map.numofStation; i++){
        estimatedWaitRevenue += Map.get_length(stationId, i);
        estimatedWaitRevenue /= (Map.numofStation - 1);
    }
    if(bikeType == "electric"){
        estimatedWaitRevenue *= Discount.electricRegularRate;
    }
    if(bikeType == "lady"){
        estimatedWaitRevenue *= Discount.ladyRegularRate;
    }
    if(bikeType == "road"){
        estimatedWaitRevenue *= Discount.roadRegularRate;
    }
    for(int i = 0; i < 500; i++){
        if (pReturnTCs[i].stationId == stationId){
            estimatedWaitRevenue -= (pReturnTCs[i].timeReturn - timeRent) * Discount.RateOfWaitingFee;
            estimatedWaitRevenue /= 10;
            break;
        }    
    }

    //calculate estimatedTransferToElectric
    int estimatedTransferToElectric = 0;
    for(int i = 1; i < Map.numofStation; i++){
        estimatedTransferToElectric += Map.get_length(stationId, i);
        estimatedTransferToElectric /= (Map.numofStation - 1);
    }
    estimatedTransferToElectric *= 1.5 * Discount.electricRegularRate * Discount.ReducedRateForSwitch;

    //calculate estimatedTransferToLady
    int estimatedTransferToLady = 0;
    for(int i = 1; i < Map.numofStation; i++){
        estimatedTransferToLady += Map.get_length(stationId, i);
        estimatedTransferToLady /= (Map.numofStation - 1);
    }
    estimatedTransferToLady *= 1.5 * Discount.ladyRegularRate * Discount.ReducedRateForSwitch;

    //calculate estimatedTransferToRoad
    int estimatedTransferToRoad = 0;
    for(int i = 1; i < Map.numofStation; i++){
        estimatedTransferToRoad += Map.get_length(stationId, i);
        estimatedTransferToRoad /= (Map.numofStation - 1);
    }
    estimatedTransferToRoad *= 1.5 * Discount.roadRegularRate * Discount.ReducedRateForSwitch;

    if(!electricIsAllowed)
        estimatedTransferToElectric = -1;
    
    if(!ladyIsAllowed)
        estimatedTransferToLady = -1;
    
    if(!roadIsAllowed)
        estimatedTransferToRoad = -1;

    int tmp[4] = {estimatedTransferToElectric, estimatedTransferToLady, estimatedTransferToRoad, estimatedWaitRevenue};
    int max = tmp[0];
    int key;
    for(int i = 0; i < 4; i++){
        //cout << tmp[i] << " ";
        if (tmp[i] > max)
            max = tmp[i];
            key = i;
    }
    //cout << endl;

    //cout << "the choose" << " " << key << endl;



    if(max < 0)
        return 4;
    else
        return key;

}
bool System2::timer(int situation, int time){
    bool flag = true;
    if(situation == 0){
        if(pRentTCsnum != 0){
            if(pRentTCs[0].timeRent < time){
                flag = false;
            }; 
        }
    }
    else if(situation == 1){
        if(pReturnTCsnum != 0){
            if(pReturnTCs[0].timeReturn < time){
                flag = false;
            }
        }
    }
    return flag;
}        
void System2::heapify(pseudoReturnTestCase arr[], int n, int i){
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l].timeReturn < arr[smallest].timeReturn)
        smallest = l;
    
    if (r < n && arr[r].timeReturn < arr[smallest].timeReturn)
        smallest = r;
    
    if(smallest != i){
        int tmp = arr[i].timeReturn;
        arr[i].timeReturn = arr[smallest].timeReturn;
        arr[smallest].timeReturn = tmp;
        heapify(arr,n,smallest);
    }

} 
void System2::buildheap(pseudoReturnTestCase arr[], int n){
    int startIdx = (n/2)-1;

    for (int i = startIdx; i >= 0; i--){
        heapify(arr,n,i);
    }
}
void System2::heapify(pseudoRentTestCase arr[], int n, int i){
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l].timeRent < arr[smallest].timeRent)
        smallest = l;
    
    if (r < n && arr[r].timeRent < arr[smallest].timeRent)
        smallest = r;
    
    if(smallest != i){
        int tmp = arr[i].timeRent;
        arr[i].timeRent = arr[smallest].timeRent;
        arr[smallest].timeRent = tmp;
        heapify(arr,n,smallest);
    }

} 
void System2::buildheap(pseudoRentTestCase arr[], int n){
    int startIdx = (n/2)-1;

    for (int i = startIdx; i >= 0; i--){
        heapify(arr,n,i);
    }
}
/*
System2::~System2(void){
    delete Users;
    delete Stations;
    delete pRentTCs;
    delete pReturnTCs;
}
*/


#endif