#include <iostream>
#include <random>
#include <chrono>
using namespace std;

int time_circles = 1000;


/*

k
request_memory_list[]
wait_counter[]
connection_priority[]


memory_module[] 1 or connected, 0 for free
memory_wait_list[] 

For each time circle:

    For each processor, 
        if the memory request is -1:
            generate the memory request with uniform distribution
            request_memory_list[p] = random
            memory_wait_list[random].push[p]  add the processor number on the memory module wait

    For each memory module:
            Mark the memory module connected, 
            access the first element in memory_wait_list[memory]
            change the memory request = -1
            and move to the next processor
            Add the processor wait counter++

---------------------

float total_average_time = 0;
float pre_wait_time = -1;
For each time circle:
    float wait_time = 0;
    float average_time = 0;
    For p_index in processor:
        if the memory request is -1:
            random generate request based on the memory number:
            memory_request[p_index] = mem_num;   
            request_queue.push(p_index)

    For p_index in request_queue:
        if memory_module[request_memory_list[p_index]] == 0: if free
            mark memory_module as 1
            mark memory_request[p] = -1;
            remove the processor from request_queue
        else == 1; if connected
            add wait_counter[p_index]++;
            wait_time++;
    
    average_time = wait_time/num_processor;
    total_average += average_time
    if(abs(pre_wait_time - average_time) / pre_wait_time  >= 0.0002){
        return total_average_time;
    }

    pre_wait_time = average_time;


*/

int rand_uniform(int memory_num){
    /*
    Credit to the stackoverflow answer
    https://stackoverflow.com/questions/32575167/generate-random-numbers-with-uniform-distribution-getting-same-number-in-loop
    */
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::default_random_engine rand_engine (seed);
    std::uniform_real_distribution<int> res (0,memory_num);
    return res(rand_engine);
}

int rand_gaussian(int memory_num){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::default_random_engine rand_engine (seed);
    while(true){
        
    }
}



float getAverageTime(int processor_num, int memory_num){
    vector<int> memory_request; // the request memory index for each processor, -1 stands for no request
    //vector<int> wait_counter; // the total wait time for each 
    vector<int> request_queue; // the queue for the requests of each processor
    vector<int> memory_module; // 1 as connected, 0 as free

    //initial memory_request
    for(int i = 0; i<processor_num; ++i){
        memory_request.push_back(-1);
    }

    //initial memory_module
    for(int i = 0; i<memory_num; ++i){
        memory_module.push_back(0);
    }

    float total_wait_time = 0;
    float pre_wait_time = -1;

    for(int i=0; i<time_circles; ++i){
        float wait_time = 0;

        for(int p = 0; p<processor_num; ++w){
            //Loop all the processor, if the memory request is empty, then random generate one
            //And, push the processor with new memory request to the request_queue.
            if(memory_request[p] == -1){
                int memory_index = 0;
                memory_request[p] = memory_index;
                request_queue.push_back(p);
            }
        }

        int current = 0;
        while(current < request_queue.size()){
            int p_index = request_queue[current];
            if(memory_module[memory_request[p_index]] == 0){ //if the memory module is free  
                memory_module[memory_request[p_index]] = 1; //mark the memory module as connected
                memory_request[p_index] = -1;//mark the professor as free
                request_queue.erase(request_queue.begin());//remove the first request in the request queue
            }
            else{ //if the memory module is connected
                wait_time++;
                current++;// The current processor need to wait for the next time circle, skip it.
            }
        }
        total_wait_time += wait_time;
        
        if(abs(pre_wait_time - wait_time)/pre_wait_time < 0.0002){
            return total_wait_time/(i*processor_num);    
        }

        pre_wait_time = wait_time;
    }

    return total_wait_time/(time_circles*processor_num);  
}









int main() 
{
    cout << "Hello, World!";
    return 0;


}