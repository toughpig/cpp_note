```bash
gcc -c -o main.o main.c--> .o relocatable file
ar -rc test.a test.o --> .a static-library
gcc -o main main.o test.o other.so --> executable file

# include path
# 会自动在include的目录下遍历/搜索需要包含的文件
-I/path/to/include-dir

# lib path
# 不会自动遍历/加载所有目录下的库文件，需要手动添加需要的库名
-L/path/to/lib-dir
-lfmt
-luv --> find libuv.so* in lib-dir
```