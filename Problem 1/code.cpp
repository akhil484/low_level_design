// Design a thermostat class that reads the room temperature per minute. Then, find the average temperature for the last hour. Assume Celsius or Kelvin

#include<iostream>
#include<queue>
#include <chrono>
#include <thread>
using namespace std;
queue<float> room_temp;
float sum = 0;
class Thermostat{

};
float get_temp()
{
    return 23.4;
}
void store_temp(){
    float temp = get_temp();
    room_temp.push(temp);
    sum += temp;
    if(room_temp.size()>60)
    {
        sum -= room_temp.front();
        room_temp.pop();
    }
}

void get_avg_temp(int c)
{
    cout<<"Avg Temp ->"<<sum/c
}

int main()
{
    int c=0;
    while(true)
    {
        store_temp();
        std::this_thread::sleep_for(std::chrono::seconds(60));
        ++c;
        if(c%5==0)
        {
            get_avg_temp(c);
            break;
        }
    }
    
    
}