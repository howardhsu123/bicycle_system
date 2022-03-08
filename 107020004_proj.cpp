#include <fstream>
#include <iostream>
#include "include/structure.hpp"

using namespace std;

int main(void){
    
    System A;
    System2 B;
    ofstream part1_response;
    ofstream part1_status;
    ofstream part2_response;
    ofstream part2_status;
    ifstream user;
    part1_response.open ("part1_response.txt");
    part1_status.open("part1_status.txt");
    part2_response.open("part2_response.txt");
    part2_status.open("part2_status.txt");
    user.open("test_case/user.txt");

    //read user.txt
    string cmd;
    int i = 100001;
    while(user >> cmd){
        //cout << i << endl;
        if(cmd == "rent"){
            int stationIdRent;
            string bikeType;
            int userId;
            int timeRent;
            user >> stationIdRent >> bikeType >> userId >> timeRent;


            
            //Part1
            part1_response << "rent" << " " << stationIdRent << " " << bikeType << " " << userId << " " << timeRent << "\n";
            string tmp = A.Rent(stationIdRent, bikeType, userId, timeRent);

            part1_response << tmp << endl;    
            
            
            //Part2
            
            int less[3] = {0,0,0};
            B.checkless(less);
            cout << less[0] << " " << less[1] << " " << less[2] << endl;
            if(less[0] != 0){
                int k = 7;
                while(k--){
                    B.generatePseudoRentTestCase(less[2], less[1], i++, timeRent);
                    B.generatePseudoReturnTestCase(less[0], less[1], i++, timeRent+B.Map.graph[less[0]][less[2]]);
                }
                if (less[1] == 0)
                    part2_response << "transfer" << " " << less[2] << " " << "electric" << " " <<  k  << " " << B.Map.graph[less[0]][less[2]] << "\n";
                else if (less[1] == 1)
                    part2_response << "transfer" << " " << less[2] << " " << "lady" << " " <<  k  << " " << B.Map.graph[less[0]][less[2]] << "\n";
                else if (less[2] == 0)
                    part2_response << "transfer" << " " << less[2] << " " << "road" << " " <<  k  << " " << B.Map.graph[less[0]][less[2]] << "\n";
            }
            

            
            while(!B.timer(0,timeRent)){
                B.Rent(B.pRentTCs[0].stationId, B.pRentTCs[0].bikeType, B.pRentTCs[0].userId, B.pRentTCs[0].timeRent);
                if(B.pRentTCs[0].userId > 100000)
                    i++;
                B.pRentTCs[0] = B.pRentTCs[--B.pRentTCsnum];
                B.buildheap(B.pRentTCs, B.pRentTCsnum);
            }     
                       
            part2_response << "rent" << " " << stationIdRent << " " << bikeType << " " << userId << " " << timeRent << "\n";
            tmp = B.Rent(stationIdRent, bikeType, userId, timeRent);
            part2_response << tmp << "\n";
            
        }
        else if (cmd == "return"){
            int stationIdReturn;
            int userId;
            int timeReturn;
            user >> stationIdReturn >> userId >> timeReturn;
            
            
            //Part1
            part1_response << "return" << " " << stationIdReturn << " " << userId << " " << timeReturn << endl;
            A.Return(stationIdReturn, userId, timeReturn);

            
            //Part2
            
            while(!B.timer(1,timeReturn)){
                //cout << B.pReturnTCsnum << endl;
                B.Return(B.pReturnTCs[0].stationId, B.pReturnTCs[0].userId, B.pReturnTCs[0].timeReturn);
                if(B.pReturnTCs[0].userId > 100000)
                    i++;
                B.pReturnTCs[0] = B.pReturnTCs[--B.pReturnTCsnum];
                B.buildheap(B.pReturnTCs, B.pReturnTCsnum);
            } 
                         
            part2_response << "return" << " " << stationIdReturn << " " << userId << " " << timeReturn << "\n";
            B.Return(stationIdReturn, userId, timeReturn);
            
        }
        //cout << "Rent" << " " << B.pRentTCsnum << endl;
        //cout << "Return" << " " << B.pReturnTCsnum << endl;   
    }
    part1_status << A.Print();
    part2_status << B.Print();
    part1_response.close();
    part1_status.close();
    part2_response.close();
    part2_response.close();
    user.close();

}