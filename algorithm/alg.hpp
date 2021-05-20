#define INT_MAX (~(1<<(sizeof(int)*8-1)))

typedef struct List
{
    int data;
    struct List* next;
    List(int a, struct List* nn = nullptr):data(a),next(nn){};
}mylist;

void showList(mylist* root);
mylist* reverse(mylist* root);
mylist* erase(mylist* root, int a);

//little-top-heap
class Heap
{
public:
    Heap(int ca):capacity(ca),count(0),heap( new int[capacity+1] ){};
    void showHeap();
    int getCount(){ return count; };
    int getTop(){ return getCount()>0?heap[1]:INT_MAX; };
    void changeTop(int a){ heap[1]=a; };
    void uphandle(int pos);
    void downhandle(int pos, int end);
    bool insert(int a);
private:
    int capacity;
    int count;
    int* heap;
};
