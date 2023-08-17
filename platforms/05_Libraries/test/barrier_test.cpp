/* SPDX-License-Identifier: MIT-0 */
#include <cstdint>
#include <cstring>
#include <iostream>

#include <pthread.h>

#define BARRIER_READER() 
#define BARRIER_WRITER()

#define GAP 128

typedef unsigned char variable_t;

variable_t x01[GAP];
variable_t x02[GAP];
variable_t x03[GAP];
variable_t x04[GAP];
variable_t x05[GAP];
variable_t x06[GAP];
variable_t x07[GAP];
variable_t x08[GAP];

int count;

static inline void check_result(variable_t c[])
{
    int j;
    int k;

    for (j=0; j<8; j++) {
        for (k=j; k<8; k++) {
            if ((c[k] != 0) && (c[j] < c[k])) {
                count++;
            }
        }
    }
}

void reader_loop(int loop)
{
    int i;
    int j;
    variable_t c[8];

    for (i=0; i<loop; i++) {
        c[0] = x01[0];
        BARRIER_READER();
        c[1] = x02[0];
        BARRIER_READER();
        c[2] = x03[0];
        BARRIER_READER();
        c[3] = x04[0];
        BARRIER_READER();
        c[4] = x05[0];
        BARRIER_READER();
        c[5] = x06[0];
        BARRIER_READER();
        c[6] = x07[0];
        BARRIER_READER();
        c[7] = x08[0];

        check_result(c);
    }
}

void writer_loop(int loop)
{
    int i;
    variable_t s;

    for (i=0; i<loop; i++) {
        s = (variable_t)i;
        x01[0] = s;
        BARRIER_WRITER();
        x02[0] = s;
        BARRIER_WRITER();
        x03[0] = s;
        BARRIER_WRITER();
        x04[0] = s;
        BARRIER_WRITER();
        x05[0] = s;
        BARRIER_WRITER();
        x06[0] = s;
        BARRIER_WRITER();
        x07[0] = s;
        BARRIER_WRITER();
        x08[0] = s;
        BARRIER_WRITER();
    }
}

#define LOOP_COUNT 100000000

void* reader_thread(void* data)
{

    reader_loop(LOOP_COUNT);

    return NULL;
}

void* writer_thread(void* data)
{

    writer_loop(LOOP_COUNT);

    return NULL;
}

void clear_variable()
{
    count = 0;
    memset((char*)&x01[0], 0, GAP*sizeof(variable_t));
    memset((char*)&x02[0], 0, GAP*sizeof(variable_t));
    memset((char*)&x03[0], 0, GAP*sizeof(variable_t));
    memset((char*)&x04[0], 0, GAP*sizeof(variable_t));
    memset((char*)&x05[0], 0, GAP*sizeof(variable_t));
    memset((char*)&x06[0], 0, GAP*sizeof(variable_t));
    memset((char*)&x07[0], 0, GAP*sizeof(variable_t));
    memset((char*)&x08[0], 0, GAP*sizeof(variable_t));
}

int main(int argc, char** argv)
{
    pthread_t reader;
    pthread_t writer;

    clear_variable();

    pthread_create(&writer, NULL, writer_thread, NULL);
    pthread_create(&reader, NULL, reader_thread, NULL);

    pthread_join(reader, NULL);
    pthread_join(writer, NULL);

    std::cout << "count = " << count << std::endl;
    return 0;
}
