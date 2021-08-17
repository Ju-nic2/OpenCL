## NDRange 
kernel makes kernel instance. and it called work-item.   
If they are in same control flow it can combine work-group.   
NDRange is a sapce for kernel instances     
### function    
clEnqueueNDRangeKernel() has many parameters. some of them  global_work_size,local_work_size    
global_work_size : Total Size Of NDRange's line. if 1 dimension, it meas l line size.
if 2 dimension, you must write n*m -> {n,m}.    
local_work_size : 1 work-group size.    
** global_work_size % local_work_size == 0 if not, CL_INVALID_WORK_GROUP_SIZE is accured.     
## barrier
openCL C has barrier() function.     
OpenCl provide global level synchronization. If two work-items are blong to different work-group, it can't be garanted orderly execution.
It makes work-items'synchronization in same work-group.    
contol flow must wait, untill all work-items In same work-group arrive barrier.




