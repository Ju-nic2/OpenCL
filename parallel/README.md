# introduce 
This folder is for Testing Optimized Open CL code 
## Task vs Data 
** In GPU -> Task <<< Data (Approximately 100x faster use all compute unit)   
** In CPU -> Task =< Data (almost same)    

## Time efficiency per compute unit (Data parallel)
use 1 compute unit -> 100   
use 2 compute unit -> 98    
use 4 compute unit -> 90    
use 24 compute unit -> 1    
   
   