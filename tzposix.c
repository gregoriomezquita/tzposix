/*
	CGI to get timezone olson and posix strings from latitude and longitud coordinates.
	References:
	- ZoneDetect: https://github.com/BertoldVdb/ZoneDetect
	- Timezone Boundary Builder: https://github.com/evansiroky/timezone-boundary-builder
	- tzinfo: https://github.com/pgurenko/tzinfo
	Author: Mezquita (SOTech)
	Date: Jan-2020
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "zonedetect.h"

#define DATABASE_FILENAME				"timezone16.bin"
#define	POSIX_JSON_FILENAME			"tzinfo.txt"
//
// Read json data base
//
char *read_json_file(char *filename){
	struct stat st;
	FILE *fp;
	char *result;
	
  if(stat(filename, &st)!=0){	
  	printf("{\"error\":\"%s\"}\n", "Unable to find tzinfo json file");
  	return NULL; 
  }
  else{
  	result= (char*)malloc(st.st_size + 1);
  	if(!result){
  		printf("{\"error\":\"%s\"}\n", "Unable to alloc memory for tzinfo json data");
  		return NULL;
  	}
  	fp = fopen(filename, "r");
  	if (fp == NULL){
  		printf("{\"error\":\"%s\"}\n", "Unable to open tzinfo json file");
  		free(result);
  		return NULL;
  	}
  	fgets(result, st.st_size+ 1, fp);
  	fclose(fp);
  }
  return result;
}

int main(int argc, char *argv[]) {
	float lat, lon;
	char *query, *json= NULL, *olson, *posix;
	ZoneDetect *cd= NULL;
	
	// Send content-type header
  printf("Content-Type: application/json\n\n");
  // Extract query params
  if(argc > 1) {	// Local run. Just for testing
  	lat = (float)atof(argv[1]);
  	lon = (float)atof(argv[2]);
  }
  else{
  	query= getenv("QUERY_STRING");
  	if(query == NULL || strlen(query)==0) { 
  		printf("{\"error\":\"%s\"}\n", "No query string");
  		return 1; 
  	}
  	else if(sscanf(query,"lat=%f&lon=%f", &lat, &lon) !=2 ) { 
  		printf("{\"error\":\"%s\"}\n", "Query format: lat=%f&lon=%f");
  		return 1; 
  	}
  }
  // Open database
  cd = ZDOpenDatabase(DATABASE_FILENAME);
  if(cd){
  	// Get Olson string
  	olson= ZDHelperSimpleLookupString(cd, lat, lon);
  	if(olson){
  		json= read_json_file(POSIX_JSON_FILENAME);
  		if(json){
  			// Get posix string from olson in a json string
  			char *key= (char *)malloc(strlen(olson)+ 1+ 2+ 1+ 1);
  			if(key){
  				sprintf(key, "\"%s\": ", olson);
					char *pstr= strstr(json, key);
					if(pstr != NULL) {
						posix= pstr+strlen(key);
						pstr= strstr(posix+ 1, "\"");
  					pstr[1]= 0;
					}
					else printf("{\"olson\": \"%s\", \"posix\": \"\"}\n", olson);	// print result with empty posix
					
					free(key);
					// Print result
					printf("{\"olson\": \"%s\", \"posix\": %s}\n", olson, posix);
  			}
				else printf("{\"error\":\"%s\"}\n", "Unable to alloc memory for key");
  			
  			free(json);
  		}
  		free(olson);
  	}
  	else printf("{\"error\":\"%s\"}\n", "Database lookup failed");
  	ZDCloseDatabase(cd);
  }
  else printf("{\"error\":\"%s\"}\n", "Unable to open database");
  
  return 0;
}
