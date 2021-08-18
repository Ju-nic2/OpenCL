## NDRange 
kernel makes kernel instance. and it called work-item.   
all kernel instances are dispatched in device's PE(process elemens)    
Ex) GPU can execute 64 work-tiems in one SMID unit using hardware thread.     
If they are in same control flow it can combine work-group.   
NDRange is a sapce for kernel instances   
### Work-item, Work-Group
Work-Item  is an kernel instance for simple operation
It same with CUDA Thread     
operate on process elements    
Work-Group is group of work-items    
It same with CUDA Thread Block    
operate on Compute units     
You can understand more easily, if you think associated with cpu programing   
work-item - process(fork) , work-group(process group)    
This concept is not matched perfectrly, just description.     
### Function    
clEnqueueNDRangeKernel() has many parameters. some of them  global_work_size,local_work_size    
global_work_size : Total Size Of NDRange's line. if 1 dimension, it meas l line size.
if 2 dimension, you must write n*m -> {n,m}.    
local_work_size : 1 work-group size.    
** global_work_size % local_work_size == 0 if not, CL_INVALID_WORK_GROUP_SIZE is accured.     
## Barrier
openCL C has barrier() function.     
OpenCl provide global level synchronization. If two work-items are blong to different work-group, it can't be garanted orderly execution.
It makes work-items'synchronization in same work-group.    
contol flow must wait, untill all work-items In same work-group arrive barrier.
## Memory
### Buffer,KernelArg
Buffer is allocated space in device.    
Kernel Arg is specific location of space    

### kernel Arg identifiers 
__private -> is for only one work-item(thread),Process Element       
__local -> is for work-group(block), Compute Unit     
__constance -> is for device, maybe share all compute unit      
__global -> is for device and more far than constance location.     
access speed p<l<c<g


