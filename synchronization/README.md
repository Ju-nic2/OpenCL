# BarrierTest.cpp
This code is for Test NDRange, Buffer, Kernel Arg    
NDRange Setting : global size : 10, local size : 2   
copy data from global memory -> local memory (matched with NDRange)     
    
1. 1 work-group is executed, all work item copies data to local memory    
3. After all Work-item's copy operation is done,          
When Work-item's global index is odd    
kernel operate r[1] - r[0]   
When Work-item's global index is even     
kernel operate r[0] - r[1]   
ex)
a : 10 -1 10 -3 10 -5 10 -7 10 -9      
r : 10 -1, 10 -3, 10 -5, 10 -7, 10 -9,   
b : (10 - -1) (-1 - 10) ~~ .. 


