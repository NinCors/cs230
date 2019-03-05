#include <iostream>;
#include <vector>;
#include <random>;
#include <chrono>;

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
    int schedule_time=-1;
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

int process(int p_num){
    vector<processor> processors;

    //initial a random load unit number and scheduling the load activity time for each processor
    for(int i =0;i<p_num;i++){
        processor p;
        p.load_units = rand_uniform(10,1000);
        p.schedule_time = rand_uniform(100,1000);
    }

}

int main(){
    int K[3] = {5,10,100};
    for (auto p_num:K){
        int time = process(p_num);
        cout<<"Took "<< time <<" circles to reach the balance of "<<p_num<<" processors"<<endl;
    }

}