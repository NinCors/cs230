#include <iostream>;
#include <vector>;
#include <random>;
#include <chrono>;
#include <unordered_map>;
using namespace std;

/*
Test different processor number {5,10,100}
Load units [10,1000]
Time interval [100,1000]

program logic:
Initial a random load unit number for each processor
Run 1001 loop and treat each loop as time unit
    if the time match with schedule_time, 
        using the balance strategy
        check if all the processors reaches the balance state
            stop and return the time if it does

Definition of balance state:
    if all of the processors has same or -1 or +1 units with their two neighbors, then balanced.
balance strategy:
    Add the load units of three processor togather, and calculate the differece between average and the load unit number of all three processors
    Possible cases need to be handled for processors p1,p,p2 with average load unit x.
        p>x, p1<x, p2<x : give the extra unit to p1 to help it reaches x, if still have left unit, continue
        p>x, p1<x, p2>x : give the extra unit to p1 to help it reaches x
        p>x, p1>x, p2<x : give the extra unit to p2 to help it reacheds x
*/

struct processor{
    int load_units=-1;
};

int rand_uniform(int low, int high){
    /*
    Credit to the stackoverflow answer
    https://stackoverflow.com/questions/32575167/generate-random-numbers-with-uniform-distribution-getting-same-number-in-loop
    */
 
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    //unsigned seed = 0;
    static std::default_random_engine rand_engine(seed);

    std::uniform_int_distribution<int> res (low,high);
    int r = res(rand_engine);
    return r;
}

void load_balance(processor &p1, processor &p, processor &p2){
    int average = (p1.load_units + p.load_units + p2.load_units)/3;
    if(p.load_units > average){
        int diff = p.load_units - average;
        p.load_units -= diff;
        if(p1.load_units < average){
            int diff1 = average - p1.load_units;
            if(diff1 >= diff){
                p1.load_units += diff;
                diff = 0;
            }
            else{
                diff = diff - diff1;
                p1.load_units += diff;
            }
        }
        if(p2.load_units < average){
            int diff2 = average - p2.load_units;
            if(diff2 >= diff){
                p2.load_units += diff;
                diff = 0;
            }
            else{
                diff = diff - diff2;
                p2.load_units += diff;
            }
        }
        if(diff > 0){
            p.load_units += diff;
        }

    }

}

bool is_balance(vector<processor> processors,int k){
    for(int i =0;i< processors.size();i++){
        if(abs(processors[i].load_units - processors[(i-1)% k].load_units) > 1 || abs(processors[i].load_units - processors[(i+1)% k].load_units) > 1 ){
            return false;
        }
    }
    return true;
}

void print_processors(vector<processor> processors){
    for(int i =0;i < processors.size();i++){
        cout<<"The load unit for processor "<< i <<" is "<<processors[i].load_units<<endl;
    }
}
int process(int p_num){
    vector<processor> processors;
    unordered_map<int, int> map; 
    //initial a random load unit number and scheduling the load activity time for each processor
    for(int i =0;i<p_num;i++){
        processor p;
        p.load_units = rand_uniform(10,1000);
        int schedule_time = rand_uniform(100,1000);
        map[schedule_time] = i;
        processors.push_back(p);
    }
    int time_count = 0;
    for(int r = 0; r < 100; ++r){ // round
        for(int t = 0; t<=1000; ++t){ // time loop
            time_count++;
            if(map.count(t)!=0){
                int processor_index = map[t];
                load_balance(processors[(processor_index-1)%p_num],processors[processor_index],processors[(processor_index+1)%p_num]);
                if(is_balance(processors,p_num)){
                    return time_count;
                }
            }
        }
    }
    return -1;


}

int main(){
    int K[3] = {5,10,100};
    for (auto p_num:K){
        int time = process(p_num);
        cout<<"Took "<< time <<" circles to reach the balance of "<<p_num<<" processors"<<endl;
    }

}
