#include "list.h"
#include <string.h>
#include <jansson.h>
#include "city.h"

int List_findById(List* self, int id) {
    for(int i = 0; i < List_count(self); i++) {
        City * node = List_get(self, i);
        if(City_getId(node) == id) {
            return i;
        }
    }
    return -1;
}

List* List_filter(List* self, char* key, char* value) {
    if(strcmp(key, "name") == 0) {
        return List_filterByName(self, value);
    } else if(strcmp(key, "id") == 0) {
        return List_filterById(self, atoi(value));
    } else if(strcmp(key, "country") == 0) {
        return List_filterByCountry(self, value);
    } else if(strcmp(key, "age") == 0) {
        return List_filterByAge(self, atoi(value));
    } else if(strcmp(key, "region") == 0) {
        return List_filterByRegion(self, value);
    } else {
        return NULL;
    }
}

List* List_filterByName(List* self, char* name) {
    List* list = List_new();
    for(int i = 0; i < List_count(self); i++) {
        City * site = List_get(self, i);
        if(strcmp(City_getName(site),name) == 0) {
            List_add(list, site);
        }
    }
    return list;
}

List* List_filterById(List* self, int id) {
    List* list = List_new();
    List_add(list, List_get(self, List_findById(self, id)));
    return list;
}

List* List_filterByCountry(List* self, char* country) {
    List* list = List_new();
    for(int i = 0; i < List_count(self); i++) {
        City * site = List_get(self, i);
        if(strcmp(City_getCountry(site),country) == 0) {
            List_add(list, site);
        }
    }
    return list;
}

List* List_filterByAge(List* self, int age) {
    List* list = List_new();
    for(int i = 0; i < List_count(self); i++) {
        City * city = List_get(self, i);
        if(City_getAge(city) == age) {
            List_add(list, city);
        }
    }
    return list;
}

List* List_filterByRegion(List* self, char* region) {
    List* list = List_new();
    for(int i = 0; i < List_count(self); i++) {
        City * city = List_get(self, i);
        if(strcmp(City_getRegion(city),region) == 0) {
            List_add(list, city);
        }
    }
    return list;
}

char * List_toJson(List* self) {
    json_t* root = json_array();
	json_t * json = NULL;
	
	for(int i = 0; i < List_count(self); i++) {
        City * site = List_get(self, i);
	
		json = json_object();
	
		json_object_set_new(json, "name", json_string(City_getName(site)));
		json_object_set_new(json, "id", json_integer(City_getId(site)));
        json_object_set_new(json, "country", json_string(City_getCountry(site)));
		json_object_set_new(json, "age", json_integer(City_getAge(site)));
        json_object_set_new(json, "region", json_string(City_getRegion(site)));
		
		json_array_append(root, json);
	}
	
	char *jStr = json_dumps(root, JSON_COMPACT);

	for(int i = 0; i < List_count(self); i++) {
		json_decref(json_array_get(root, i));
	}
	json_decref(root);
    return jStr;
}