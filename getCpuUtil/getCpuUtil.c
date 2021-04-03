#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
//#define ONE_LINE 80
#define PAST 0
#define PRESENT 1
#define JIFFIES_NUM 4
enum jiffy{USER, USER_NICE, SYSTEM, IDLE} jiffy_enum;
void readCpuUtil(FILE* statFile, int WHEN, int jiffies[][JIFFIES_NUM]){
    int idx,totalJiffies;
    fscanf(statFile, "%*s %d %d %d %d", &jiffies[WHEN][USER], &jiffies[WHEN][USER_NICE], &jiffies[WHEN][SYSTEM], &jiffies[WHEN][IDLE]);
    fclose(statFile);
}
int main(void){
//  char loadDataBuf[ONE_LINE] = {0x0,};
  
  int jiffies[2][JIFFIES_NUM] = {0x0,}, totalJiffies;
  int diffJiffies[JIFFIES_NUM];
  int idx;
  FILE* statFile=fopen("/proc/stat","r");
  //readCpuUtil(statFile,PAST,jiffies);
  while(1){
        statFile=fopen("/proc/stat","r");
        readCpuUtil(statFile,PRESENT,jiffies);
        
        for(idx = 0, totalJiffies = 0; idx < JIFFIES_NUM; ++idx){
            diffJiffies[idx] = jiffies[PRESENT][idx] - jiffies[PAST][idx];
            totalJiffies = totalJiffies + diffJiffies[idx];
        }
        if(totalJiffies==0)
            continue;
    
        printf("Cpu usage : %f\n",
            (1.0-(diffJiffies[IDLE] / (double)totalJiffies))*100.0f);
    
        memcpy(jiffies[PAST], jiffies[PRESENT], sizeof(int)*JIFFIES_NUM);
    
        usleep(500000);
  }
  return 0;
}