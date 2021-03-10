```bash
#event-loop最终会被uv_run()启动
This event loop is encapsulated by uv_run()

#伪代码描述如下
In pseudocode

#而不是一大堆的数据处理
rather than a lot of number-crunching

#对于需要高性能的的程序来说，这是一个主要的障碍因为其他活动和I/O操作都在保持等待
For programs which require high performance this is a major roadblock as other activities and other I/O operations are kept waiting

#当某个线程一旦阻塞
When the blocking function gets invoked in the thread



```