# CAB403 - Practical 5 notes

## Materials
- Hash table: [Hash table](https://www.hackerearth.com/practice/data-structures/hash-tables/basics-of-hash-tables/tutorial/)

## Notes
### 1. sampleThread.c:
- You may want to try this but I would recommend to use the solution provide in 'sampleThread_2.c':
```
if (pthread_create(&thread3, NULL, (void *(*)(void *))sum_number_function, (void *)&data3) != 0){
    printf("ERROR creating thread");
    return EXIT_FAILURE;
}
void sum_number_function(void *ptr)
{
    thsum *data;
    data = (thsum *)ptr;
    int result = 0;
    for (int x = 0; x <= data->sum_to; x++){
        result += x;
    }
    printf("Thread number %d reports that the sum of the first %d numbers is = %d\n", data->thread_no, data->sum_to, result);
    return;
}
```
### 2. msgq.c:
- The fflush() function in C is used to flush (or clear) the output buffer of a stream. Calling fflush(stdout) forces the buffer to be flushed and the data to be immediately written to the console.
