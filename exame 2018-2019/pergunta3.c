#define HSIZE 23
#define FREE -1
typedef struct entry {
    int probeC; // -1: free
    int key;
    int value;
} HTable [HSIZE];

int hash (int key, int size);

void insert(HTable t, int key, int value){
    int h = hash(key,HSIZE);
    for(int offset = 0; offset < HSIZE; offset++){
        int i = (h + offset) % HSIZE;
        t[i].probeC++;
        if(t[i].probeC == -1){
            t[i].probeC++;
            t[i].key = key;
            t[i].value = value;
            return;
        }
    }
}

int update(HTable t, int key, int value){
    int a = 0;
    for(int i = 0; i < HSIZE; i++)
        if(t[i].probeC > -1) a++;
    insert(t,key,value);
    return(a==HSIZE);
}