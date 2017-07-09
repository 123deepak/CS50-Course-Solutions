/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    for(int z=0;z<n;z++){
        if(values[z]==value)
        return true;
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int a[], int n)
{
    // TODO: implement a sorting algorithm
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i;j++){
            if(a[i]>a[j]){
                int temp = a[j];
                a[j]=a[i];
                a[i]=temp;
            }
        }
    }
    return;
}
