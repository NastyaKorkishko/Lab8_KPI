/** @file
    @brief Search and filter functions for List of Cities
*/

#ifndef LIST_H
#define LIST_H

#include <progbase/list.h>

/**
    @brief finds City in list by its id
    @param id - id of City
    @returns index of City in list or -1 otherwise
*/
int List_findById(List* self, int id);

/**
    @brief filters list of Cities by specified field value
    @param key - name of field to be filtered by
    @returns new list of corresponding Cities
*/
List* List_filter(List* self, char* key, char* value);

/**
    @brief filters list of Cities by specific name value
    @param name - value of name field of City
    @returns new list of corresponding Cities
*/
List* List_filterByName(List* self, char* name);

/**
    @brief filters list of Cities by specific id value
    @param id - value of id field of City
    @returns new list of corresponding Cities
*/
List* List_filterById(List* self, int id);

/**
    @brief filters list of Cities by specific country value
    @param country - value of country of Cities to be filtered by
    @returns new list of corresponding Cities
*/
List* List_filterByCountry(List* self, char* country);

/**
    @brief filters list of Cities by specific age value
    @param age - value of age field of City
    @returns new list of corresponding Cities
*/
List* List_filterByAge(List* self, int age);

/**
    @brief filters list of Cities by specific region value
    @param region - region of City
    @returns new list of corresponding Cities
*/
List* List_filterByRegion(List* self, char* region);

/**
    @brief list of Cities representation in json string
    @returns json representation of list of Cities
*/
char* List_toJson(List* self);
#endif