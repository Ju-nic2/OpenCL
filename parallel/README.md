# introduce 
This folder is for Testing Optimized Open CL code 
Data set : 256*4    
## Task vs Data 
** In GPU -> Task <<< Data (Approximately 100x faster use all compute unit)   
** In CPU -> Task =< Data (almost same)    

## Time efficiency per compute unit (Data parallel)
**seting : set work_group_size == 256 / compute unit num    
use  1 compute unit -> 100   
use  2 compute unit -> 85    
use  4 compute unit -> 75    
use 16 compute unit -> 72    
   
## Optimize with vector data vs nomal data
preparing

## Optimize with data caching(use local memory)
preparing
   
