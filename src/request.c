#include <string.h>
#include <ctype.h>
#include <jansson.h>
#include "request.h"
#include "city.h"
#include "list.h"
#include "storage.h"
#include <time.h>

void Response_badRequest(Response* responce) {
    responce->status = 400;
    strcpy(responce->description,"Bad request");
}

void Response_notFound(Response* responce) {
    responce->status = 404;
    strcpy(responce->description,"Not found");
}

void Response_success(Response* responce, char* data) {
    responce->status = 200;
    strcpy(responce->description, "OK");
    strcpy(responce->data, data);
}

void Response_init(Response * self) {
	self->status = 0;
	strcpy(self->description, "");
    strcpy(self->data, "");
}

char* Response_serverInfo(void) {
    const char name[] = "HTTP server";
    const char surname[] = "Korkishko";
    
    time_t now = time(NULL);
    struct tm * local = localtime(&now);
    char serverTime[50];
    strftime(serverTime, 50, "%X", local);
    
    json_t * jobj = json_object();
    json_object_set(jobj, "name", json_string(name));
    json_object_set(jobj, "developer", json_string(surname));
    json_object_set(jobj, "time", json_string(serverTime));

	char *jStr = json_dumps(jobj, JSON_COMPACT);
	json_decref(jobj);
    return jStr;
}

Request Request_parse(const char * str) {
    Request req = {
		.command = ""
	};
    if(str[0] != '\0') {
        char* pch = strstr(str, " HTTP");
        strncpy(req.command, str, pch-str);
    }
    return req;
}

void Request_process(Request* request, Response* response, List* cities) {
    char* command = request->command;
    if(strncmp(command, "GET",3) == 0) {
        char* begin = strchr(command, '/')+1;
        if(*begin == ' ' || strlen(begin) == 0) {
            Response_success(response, Response_serverInfo());
        } else {
            if(strstr(begin,"favourites") != NULL) {
                begin += strlen("favourites");
                if(*begin == ' ' || strlen(begin) == 0) {
                    Response_success(response, List_toJson(cities));
                } else if(*begin == '?') {
                    begin++;
                    char key[20];
                    char value[20];
                    char* sign = strchr(begin, '=');
                    strncpy(key, begin, sign-begin);
                    sign++;
                    strcpy(value, sign);
                    
                    List* list = List_filter(cities,key, value);
                    if(list == NULL || List_count(list) == 0) {
                        Response_notFound(response);
                    } else {
                        Response_success(response, List_toJson(list));
                    }
                } else if(*begin == '/') {
                    int id = -1;
                    sscanf(begin,"/%i",&id);
                    int index = List_findById(cities, id);
                    if(index != -1) {
                        City * node = List_get(cities,index);
                        Response_success(response,City_toJsonString(node));
                    } else {
                        Response_notFound(response);
                    }
                } else {
                    Response_badRequest(response);
                }
            } else if(strstr(begin, "file") != NULL) {
                begin += strlen("file");
                if(strlen(begin)==0) {
                    Response_success(response, Storage_fileToJson("data.txt"));
                } else if(strstr(begin, "/data") != NULL) {
                    Response_success(response, Storage_fileContentInfo("data.txt"));
                } else {
                    Response_badRequest(response);
                }
            } else {
                Response_badRequest(response);
            }
        }
    } else {
        Response_badRequest(response);
    }
}

void Response_toMessage(Response* res,NetMessage * message) {
    char msg[BUFFER_SIZE];
    if(strlen(res->data)!=0) {
        sprintf(msg,"HTTP/1.0 %i %s\n"
        "Content-type: text/json\n"
        "Content-length: %i\n"
        "%s",res->status,res->description,(int)strlen(res->data),res->data);
    } else {
        sprintf(msg,"HTTP/1.0 %i %s",res->status,res->description);
    }
    NetMessage_setDataString(message, msg);
}