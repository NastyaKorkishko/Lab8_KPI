#include "city.h"
#include <stdlib.h>
#include <string.h>
#include <jansson.h>

#define NAME_MAXLEN 100

struct City {
    char name[NAME_MAXLEN];
    int id;
    char country[40];
    int age;
    char region[40];
};

City* City_new(void) {
    City* self = (City*)malloc(sizeof(City));
    strcpy(self->name,"");
    self->id = -1;
    strcpy(self->country,"");
    self->age = 0;
    strcpy(self->region,"");
    return self;
}

City* City_setNew(char* name, int id, char* country, int age, char* region) {
    City* self = (City*)malloc(sizeof(City));
    strcpy(self->name,name);
    self->id = id;
    strcpy(self->country,country);
    self->age = age;
    strcpy(self->region,region);
    return self;
}

void City_free(City** selfPtr) {
    City* self = *selfPtr;
    free(self);
	*selfPtr = NULL;
}

char* City_getName(City * self) {
    return self->name;
}

int City_getId(City * self) {
    return self->id;
}

char* City_getCountry(City * self) {
    return self->country;
}

int City_getAge(City * self) {
    return self->age;
}

char* City_getRegion(City * self) {
    return self->region;
}

void City_setName(City * self,char* name) {
    strcpy(self->name, name);
}
void City_setId(City * self,int id) {
    self->id = id;
}
void City_setCountry(City * self,char* country) {
    strcpy(self->country, country);
}
void City_setAge(City * self,int age) {
    self->age = age;
}
void City_setRegion(City * self,char* region) {
    strcpy(self->region, region);
}

char* City_toJsonString(City * self) {
    json_t * jobj = json_object();
    json_object_set(jobj, "name", json_string(self->name));
    json_object_set(jobj, "id", json_integer(self->id));
    json_object_set(jobj, "country", json_string(self->country));
    json_object_set(jobj, "age", json_integer(self->age));
    json_object_set(jobj, "region", json_string(self->region));

	char *jStr = json_dumps(jobj, JSON_COMPACT);
	json_decref(jobj);
    return jStr;
}


