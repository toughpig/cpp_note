```c++
//mutex
if(lock==0)
{
    lock=1;
    yield();//
}

//atomic Compare and Swap CAS
if(lock==0)
{
    lock=1;
}

//spinlock
label:
if(lock==0)
{
    goto label;
}
```