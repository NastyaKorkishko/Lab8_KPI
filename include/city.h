/** @file
    @brief City module
*/

#ifndef CITY_H
#define CITY_H

#include <progbase/list.h>

/**
    @struct City
    @brief defines a City data type
*/
typedef struct City City;

/**
    @brief City constructor
*/
City* City_new(void);

/**
    @brief City constructor setter
    @param name - name of city
    @param id - unique id of city
    @param country - country of city
    @param age - age of city
    @param region - region of city
*/
City* City_setNew(char* name, int id, char* country, int age, char* region);

/**
    @brief City destructor
*/
void City_free(City** self);

/**
    @brief City name getter
    @returns name of City
*/
char* City_getName(City * self);

/**
    @brief City id getter
    @returns id of City
*/
int City_getId(City * self);

/**
    @brief City country getter
    @returns country of City
*/
char* City_getCountry(City * self);

/**
    @brief City age getter
    @returns age of City
*/
int City_getAge(City * self);

/**
    @brief City region getter
    @returns region of City
*/
char* City_getRegion(City * self);

/**
    @brief City name setter
    @param name - name of City
*/
void City_setName(City * self,char* name);

/**
    @brief City id setter
    @param id - unique id of City
*/
void City_setId(City * self,int id);

/**
    @brief City country setter
    @param country - origin country of City
*/
void City_setCountry(City * self,char* country);

/**
    @brief City age setter
    @param age - age of City
*/
void City_setAge(City * self,int age);

/**
    @brief City type setter
    @param region - region of City
*/
void City_setRegion(City * self,char* region);

/**
    @brief City representation in json string
    @returns json representation of City
*/
char* City_toJsonString(City * self);

#endif