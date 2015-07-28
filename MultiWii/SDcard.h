#ifndef SDCARD_H_
#define SDCARD_H_

#ifdef MWI_SDCARD
void init_SD(void);
void writeGPSLog(int32_t latitude, int32_t longitude, int32_t altitude);
void writePLogToSD(void);
void fillPlogStruct(char* key, char* value);
void readPLogFromSD(void);
#endif

#endif //SDcard_H_