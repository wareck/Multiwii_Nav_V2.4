#include "Arduino.h"
#include "config.h"
#include "def.h"
#include "types.h"
#include "EEPROM.h"
#include "SDcard.h"
#include "MultiWii.h"
#include "Alarms.h"
#include "GPS.h"

/* thanks to Rcnet team for there job !*/

#ifdef MWI_SDCARD
#include <SdFile.h>
#include <SdStream.h>
#include <SdFatUtil.h>

#define PERMANENT_LOG_FILENAME "PERM.TXT"
#define GPS_LOG_FILENAME "GPS_DATA.RAW"

SdFat sd;
ofstream gps_data;	// Log file for GPS raw data
ofstream permanent; // Log file for permanent logging
SdFile mission_file; // comma separated file for missions ( lat/lon/alt/heading )

uint8_t sdFlags = 0;
#define MFO_FLAG_ON 0x01			
#define MFO_FLAG_OFF 0xFE

/* Init SD card : assign OUTPUT mode to CSPIN and start SPI mode */
void init_SD(){

#if defined DROTEK_DROFLY_V3_GPS||defined DROTEK_DROFLY_V3
	DDRH |= (1 << 2);
#else
	pinMode(CSPIN, OUTPUT); 	// Put CSPIN to OUTPUT for SD library
#endif
	if (!sd.begin(CSPIN, SPI_HALF_SPEED)) {
		f.SDCARD = 0;      	// If init fails, tell the code not to try to write on it
		debug[1] = 999;
	}
	else {
		f.SDCARD = 1;
		debug[1] = 000;
	}
}

void writeGPSLog(int32_t latitude, int32_t longitude, int32_t altitude) {
	if (f.SDCARD == 0) return;
	gps_data.open(GPS_LOG_FILENAME, O_WRITE | O_CREAT | O_APPEND);
	char lat_c[11];
	char lon_c[11];
	char alt_c[11];

	snprintf(lat_c, 11, "%ld", latitude);
	snprintf(lon_c, 11, "%ld", longitude);
	snprintf(alt_c, 11, "%ld", altitude);

	gps_data << lat_c << ',' << lon_c << ',' << alt_c << endl;
	gps_data.flush();
	gps_data.close();

}

void writePLogToSD() {
	if (f.SDCARD == 0) return;
	char buf[12];
	plog.checksum = calculate_sum((uint8_t*)&plog, sizeof(plog));
     	permanent.open(PERMANENT_LOG_FILENAME, O_WRITE | O_CREAT | O_TRUNC);

	permanent << "arm=" << plog.arm << endl;
	permanent << "disarm=" << plog.disarm << endl;
	permanent << "start=" << plog.start << endl;
	permanent << "armed_time=" << plog.armed_time << endl;
	snprintf(buf, 11, "%lu", plog.lifetime);
	permanent << "lifetime=" << buf << endl;
	permanent << "failsafe=" << plog.failsafe << endl;
	permanent << "i2c=" << plog.i2c << endl;
	memset(buf, '\0', 12);
	snprintf(buf, 5, "%hhu", plog.running);
	permanent << "running=" << buf << endl;
	memset(buf, '\0', 12);
	snprintf(buf, 5, "%hhu", plog.checksum);
	permanent << "checksum=" << buf << endl;

	permanent.flush();
	permanent.close();

}

void fillPlogStruct(char* key, char* value) {
	if (strcmp(key, "arm") == 0)			sscanf(value, "%u", &plog.arm);
	if (strcmp(key, "disarm") == 0)		sscanf(value, "%u", &plog.disarm);
	if (strcmp(key, "start") == 0)		sscanf(value, "%u", &plog.start);
	if (strcmp(key, "armed_time") == 0)	sscanf(value, "%lu", &plog.armed_time);
	if (strcmp(key, "lifetime") == 0)	sscanf(value, "%lu", &plog.lifetime);
	if (strcmp(key, "failsafe") == 0)	sscanf(value, "%u", &plog.failsafe);
	if (strcmp(key, "i2c") == 0)			sscanf(value, "%u", &plog.i2c);
	if (strcmp(key, "running") == 0)		sscanf(value, "%hhu", &plog.running);
	if (strcmp(key, "checksum") == 0)	sscanf(value, "%hhu", &plog.checksum);
}

void readPLogFromSD() {
	if (f.SDCARD == 0) return;
	char key[12];
	char value[32];
	char* tabPtr = key;
	int c;
	uint8_t i = 0;

	ifstream file("perm.txt");

	while ((c = file.get()) >= 0) {
		switch ((char)c) {
		case ' ':
			break;
		case '=':
			*tabPtr = '\0';
			tabPtr = value;
			break;
		case '\n':
			*tabPtr = '\0';
			tabPtr = key;
			i = 0;
			fillPlogStruct(key, value);
			memset(key, '\0', sizeof(key));
			memset(value, '\0', sizeof(value));
			break;
		default:
			i++;
			if (i <= 12) {
				*tabPtr = (char)c;
				tabPtr++;
			}
			break;
		}
	}

	if (calculate_sum((uint8_t*)&plog, sizeof(plog)) != plog.checksum) {
#if defined(BUZZER) 
		alarmArray[7] = 3;
		blinkLED(9, 100, 3);
#endif
		// force load defaults
		plog.arm = plog.disarm = plog.start = plog.failsafe = plog.i2c = 11;
		plog.running = 1;
		plog.lifetime = plog.armed_time = 3;
		writePLogToSD();
	}
}

#endif
