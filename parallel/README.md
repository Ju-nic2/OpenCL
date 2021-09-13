# Introduce 
This folder is for Testing Optimized Open CL code 

# Parallel.cpp + tack.cl + data.cl
Data set : 256*4   

## Task vs Data 
** In GPU -> Task <<< Data (Approximately 10x faster use all compute unit)   
** In CPU -> Task =< Data (almost same)    

## Time efficiency per compute unit (Data parallel)
**seting : set work_group_size == 256 / compute unit num    
use  1 compute unit -> 100   
use  2 compute unit -> 85    
use  4 compute unit -> 75    
use 16 compute unit -> 72    

# OptimizeTest.cpp + cellMatrix.cl
I use last semester's code (in Linux System Programing repository)    
I compared multiprocess vs multithread.     
Input Data : 8192*8192 Matrix 
## Optimize with data caching(use local memory)
In GPU accessing global memory takes a long time compare to accessing local memeory   
I learned accessing local memory is much faster than accessing global memory   

This Operation(cell metrix game) need to 10 times accessing global mem for one cell.    
But if i load data to local mem from global mem, only 1time for one cell.    

So i designed this program    
I made work-group that's size is 16*16 (same with max work-item size 256)     
This program use all compute unit.    

### Conclusion
1 iteration -> 88ms vs 77 ms      
100 iteration -> 4000ms vs 3800 ms     

So, Optimized kernel is faster than nomal kernerl.    
But Its difference is not noticeably large.    


## CPU vs GPU
This is meaningless. Because My PC's CPU GPU performance gap is very large.     
When i check this, Always CPU is faster than GPU    
   
## Memory copy problem 
In this program , Moving data between CPU and GPU is longer than kernel working.   
It's biger than Optimization with local memory. So, Proper memory use is necessary.    

## Optimize with vector data vs nomal data
preparing...   
