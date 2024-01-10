#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a struct to store the data
typedef struct {
    char name[10];
    int arrTime;
    int burTime;
    int remTime;  // Only for NSJF && RR
    int waitTime; // only for NSJF
} TextData;

// only for RR
typedef struct{
   char name[10];
   int waitTime;
   int remTime;
}RRwait;

// all used methods
int compareByBurst(TextData a, TextData b);
void swap(TextData* a, int i, int j);
int compareByArrivalTime(const void* a, const void* b);
int compareByBurstTime(const void* a, const void* b);

int main() {
    
    FILE *output = fopen("Output.txt", "w");
    
    // This part will read the file and store data in a struct

    FILE *file = fopen("TaskSpec.txt", "r");
    TextData *data = NULL;
    int capacity = 4;  // initial capacity
    int size = 0; // this will be the size of tasks
    data = malloc(capacity * sizeof(TextData)); // this stores data for FCFS algorithm
    char line[32];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (size == capacity) {
            capacity *= 2;
            data = realloc(data, capacity * sizeof(TextData));
        }
        if (sscanf(line, "%9[^,],%d,%d", data[size].name, &data[size].arrTime, &data[size].burTime) == 3) {
            data[size].remTime=data[size].burTime;
            size++;
        }
    }
    fclose(file);
    

    // This is the execution of FCFS algorithm
    fprintf(output,"\nFCFS: \n");
    int waitTime[size];
    int currTime = 0;
    for (int i = 0; i < size; i++) {
        if (i != 0) {
            waitTime[i] = currTime - data[i].arrTime;
        } else {
            waitTime[i] = currTime;
        }
        if(currTime>=10){
            fprintf(output,"%s  %d  %d\n", data[i].name, currTime, currTime + data[i].burTime);
        }else{
            fprintf(output,"%s  %d   %d\n", data[i].name, currTime, currTime + data[i].burTime);
        }
        currTime += data[i].burTime;
    }
    int totalTime = 0;
    for (int i = 0; i < size; i++) {
        fprintf(output,"Waiting time %s: %d\n", data[i].name, waitTime[i]);
        totalTime += waitTime[i];
    }
    fprintf(output,"Average Waiting Time: %.2f\n", (float)totalTime / size);
    
    
    
    
    //This is the processing of RR
    fprintf(output,"\nRR: \n");
    TextData* dataForRR = malloc(size * sizeof(TextData)); // data for RR
    RRwait* waitForRR = malloc(size * sizeof(RRwait)); // wait for RR
    
    //initializing data
    for (int i = 0; i < size; i++) {
        strcpy(dataForRR[i].name, data[i].name);
        dataForRR[i].arrTime=data[i].arrTime;
        dataForRR[i].burTime=data[i].burTime;
        dataForRR[i].remTime=data[i].remTime;
        strcpy(waitForRR[i].name, data[i].name);
        waitForRR[i].waitTime=0;
        waitForRR[i].remTime=data[i].burTime;
    }
    
    int completed=0;
    currTime=0;
    int executeTime=0;
    int timeQuantum = 4;
    int newSize = size;
    int index = 0;

    while (completed<size) {
        if (dataForRR[index].remTime > 0) {
            if (dataForRR[index].remTime < timeQuantum) {
                executeTime = dataForRR[index].remTime;
            } else {
                executeTime = timeQuantum;
            }
            if(currTime>=10){
                fprintf(output,"%s  %d  %d\n", dataForRR[index].name, currTime, currTime + executeTime);
            }else{
                fprintf(output,"%s  %d   %d\n", dataForRR[index].name, currTime, currTime + executeTime);
            }
            
            dataForRR[index].remTime -= executeTime;
            currTime+=executeTime;
            for (int i = 0; i < size; i++) {
                if(strcmp(dataForRR[index].name,waitForRR[i].name)!=0 && waitForRR[i].remTime>0){
                    waitForRR[i].waitTime += executeTime; 
                }else if(strcmp(dataForRR[index].name, waitForRR[i].name) == 0){
                    waitForRR[i].remTime-=executeTime;
                }
            }
            
        }
        if (dataForRR[index].remTime !=0){
            int insertIndex = -1;
            for (int i = 0; i < newSize; i++) {
                if (dataForRR[index].arrTime < dataForRR[i].arrTime && currTime < dataForRR[i].arrTime) {
                    insertIndex = i;
                    break;
                }
                insertIndex=newSize;
            }
            
            if (insertIndex != -1) {
                newSize += 1;
                dataForRR = realloc(dataForRR, newSize * sizeof(TextData));
                for (int j = newSize - 1; j > insertIndex; j--) {
                    dataForRR[j] = dataForRR[j - 1];
                }
                dataForRR[insertIndex] = dataForRR[index];
            }
        }
        if(dataForRR[index].remTime==0){
            completed++;
        }
        index++;
    }
    totalTime = 0;
    for (int i = 0; i < size; i++) {
        fprintf(output,"Waiting time %s: %d\n", waitForRR[i].name, waitForRR[i].waitTime-data[i].arrTime);
        totalTime += waitForRR[i].waitTime-data[i].arrTime;
    }
    fprintf(output,"Average Waiting Time: %.2f\n", (float)totalTime / size);
    


    
    // This is the execution of NSJF algorithm
    TextData *data2 = malloc(size * sizeof(TextData));// This is the data for NSJF
    waitTime[size];
    int done = 0;
    while (!done) {
        done = 1;
        for (int i = 0; i < size; i++) {
            if (i == 0) {
                strcpy(data2[i].name, data[i].name);
                data2[i].arrTime = data[i].arrTime;
                data2[i].burTime = data[i].burTime;
            } else {
                if(i+1<size){
                    if (compareByBurst(data[i], data[i + 1]) == 0) {
                        swap(data, i, i + 1);
                        done = 0;
                    }
                }
                strcpy(data2[i].name, data[i].name);
                data2[i].arrTime = data[i].arrTime;
                data2[i].burTime = data[i].burTime;
            }
        }
    }
    fprintf(output,"\nNSJF: \n");
    currTime = 0;
    for (int i = 0; i < size; i++) {
        if (i != 0) {
            data2[i].waitTime = currTime - data2[i].arrTime;
        } else {
            data2[i].waitTime = currTime;
        }
        if(currTime>=10){
            fprintf(output,"%s  %d  %d\n", data2[i].name, currTime, currTime + data2[i].burTime);
        }else{
            fprintf(output,"%s  %d   %d\n", data2[i].name, currTime, currTime + data2[i].burTime);
        }
        currTime += data2[i].burTime;
    }
    
    totalTime = 0;
    qsort(data2, size, sizeof(TextData), compareByArrivalTime);
    for (int i = 0; i < size; i++) {
        fprintf(output,"Waiting time %s: %d\n", data2[i].name, data2[i].waitTime);
        totalTime += data2[i].waitTime;
    }
    fprintf(output,"Average Waiting Time: %.2f\n", (float)totalTime / size);
    qsort(data, size, sizeof(TextData), compareByArrivalTime);
    
    
    // this is PSJF
    fprintf(output,"\nPSJF:\n");
    int current_time = 0;
    completed = 0;
    int start = 0;
    int last = 0;
    int totalTimeOfBurst = 0;
    int waitingTime[size]; // Array to store waiting times for each process
    
    for (int i = 0; i < size; i++) {
        totalTimeOfBurst += data[i].burTime;
        waitingTime[i] = 0; // Initialize waiting time for each process
    }
    
    while (completed < size) {
        int shortest = -1;
        int min_remaining_time = 1000;
        
        //this part determine the shortest process
        for (int i = 0; i < size; i++) {
            if (data[i].arrTime <= current_time && data[i].remTime < min_remaining_time && data[i].remTime > 0) {
                shortest = i;
                min_remaining_time = data[i].remTime;
            }
        }
    
        if (shortest == -1) {
            current_time++;
        } else {
            if (data[shortest].name != data[last].name) {
                if(start>=10){
                    fprintf(output,"%s  %d  %d\n", data[last].name, start, current_time);
                }else{
                    fprintf(output,"%s  %d   %d\n", data[last].name, start, current_time);
                }
                start = current_time;
            }
    
            last = shortest;
            data[shortest].remTime--;
            current_time++;
    
            if (current_time == totalTimeOfBurst) {
                if(start>=10){
                    fprintf(output,"%s  %d  %d\n", data[last].name, start, current_time);
                }else{
                    fprintf(output,"%s  %d   %d\n", data[last].name, start, current_time);
                }
            }
    
            if (data[shortest].remTime == 0) {
                completed++;
            }
    
            // Update waiting time for processes that are not running
            for (int i = 0; i < size; i++) {
                if (i != shortest && data[i].arrTime < current_time && data[i].remTime > 0) {
                    waitingTime[i]++;
                }
            }
        }
    }
    
    // Print the waiting time for each process
    totalTime = 0;
    for (int i = 0; i < size; i++) {
        fprintf(output,"Waiting time %s: %d\n", data[i].name, waitingTime[i]);
        totalTime += waitingTime[i];
    }
    fprintf(output,"Average Waiting Time: %.2f\n\n", (float)totalTime / size);
    
    // Free memory for FCFS
    free(data);
    
    // Free memory for RR
    free(dataForRR);
    free(waitForRR);
    
    // Free memory for NSJF
    free(data2);
}

int compareByBurst(TextData a, TextData b) {
    if (a.burTime > b.burTime) {
        return 0;
    } else {
        return 1;
    }
}

void swap(TextData* a, int i, int j) {
    TextData temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

int compareByArrivalTime(const void* a, const void* b) {
    const TextData* textDataA = a;
    const TextData* textDataB = b;

    if (textDataA->arrTime < textDataB->arrTime) {
        return -1;
    } else if (textDataA->arrTime > textDataB->arrTime) {
        return 1;
    } else {
        return 0;
    }
}

int compareByBurstTime(const void* a, const void* b) {
    const TextData* textDataA = a;
    const TextData* textDataB = b;

    if (textDataA->burTime < textDataB->burTime) {
        return -1;
    } else if (textDataA->burTime > textDataB->burTime) {
        return 1;
    } else {
        return 0;
    }
}
