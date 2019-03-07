#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Given a csv file, return the minimum of the specified column, excluding blanks
double getMin(char csvfile[], char column[])
{
    char *str = malloc(400*sizeof(char));
    char *temp = malloc(40*sizeof(char)); 
    FILE *fp = fopen(csvfile, "r");
    int i = 0;
    double min = 101.0;
    
    fgets(str, 300, fp);
    do {
        if (i == 46) {
            temp = str;
            break;
        }
        else temp = strsep(&str, ",");
        i++;    
    } while (strcmp(temp, column) != 0);

    fgets(str, 300, fp);
    while (1) {
        for (int k = 0; k <= i; k++) {
            if (k == 46) {
                temp = str;
                break;
            }
            else temp = strsep(&str, ","); 
        }
        if (atof(temp) < min && (strcmp(temp,"") != 0)) min = atof(temp);
        if (fgets(str, 300, fp) == NULL) break;
    }
    return min;
}
// Given a csv file, return the maximum of the specified column, excluding blanks
double getMax(char csvfile[], char column[])
{
    char *str = malloc(400*sizeof(char));
    char *temp = malloc(40*sizeof(char));
    FILE *fp = fopen(csvfile, "r");
    int i = 0;
    double max = 0;
   
    fgets(str, 300, fp);
    do {
        if (i == 46) {
            temp = str;
            break;
        }
        else temp = strsep(&str, ",");
        i++;
    } while (strcmp(temp, column) != 0);

    fgets(str, 300, fp);
    while (1) {
        for (int k = 0; k < i; k++) {  
            if (k == 46) {
                temp = str;
                break;
            }
            else temp = strsep(&str, ",");
        }
        if (atof(temp) > max && (strcmp(temp,"") != 0)) max = atof(temp);
        if (fgets(str, 300, fp) == NULL) break;
    }
    return max;
}
// Given a csv file, return the average of the specified column, excluding blanks
double getAvg(char csvfile[], char column[]) 
{
    char *str = malloc(400*sizeof(char));
    char *temp = malloc(40*sizeof(char));
    FILE *fp = fopen(csvfile, "r");
    int i = 0;
    double avg = 0;
    double sum = 0;
    double count = 0;

    fgets(str, 300, fp);
    do {
        if (i == 46) {
            temp = str;
            break;
        }
        else temp = strsep(&str, ",");
        i++;
    } while (strcmp(temp, column) != 0);

    fgets(str, 300, fp);
    while (1) {
        for (int k = 0; k < i; k++) {
            if (k == 46) {
                temp = str;
                break;
            }
            else temp = strsep(&str, ",");
        }
        if (strcmp(temp, "") != 0) {
            sum += atof(temp);
            count++;
        }
        if (fgets(str, 300, fp) == NULL) break; 
    }
    avg = sum/count;    
    return avg;
}
// Given a csv file, return the number of students with their column value >= threshold, excluding blanks
int getCount(char csvfile[], char column[], double threshold) 
{
    char *str = malloc(400*sizeof(char));
    char *temp = malloc(40*sizeof(char));
    FILE *fp = fopen(csvfile, "r");
    int i = 0; 
    double count = 0;
    
    fgets(str, 300, fp);
    do {
        if (i == 46) {
            temp = str;
            break;
        }
        else temp = strsep(&str, ",");
        i++;
    } while (strcmp(temp, column) != 0);
    
    fgets(str, 300, fp);
    while (1) {
        for (int k = 0; k < i; k++) {
            if (k == 46) {
                temp = str;
                break;
            }
            else temp = strsep(&str, ",");
        }
        if (strcmp(temp, "") != 0 & atof(temp) >= threshold) {
            count++;
        }
        if (fgets(str, 300, fp) == NULL) break;
    }
    return count;
}
// Given a csv file, return the weighted average of the specified student
// or -1.0 if there is no such student.
// A blank cell is viewed as 0
double getGrade(char csvfile[], char first[], char last[]) 
{
    FILE *fp = fopen(csvfile, "r");
    int i = 0;
    int j = 0;
    double q[11] = {0};
    char firstName[30];
    char lastName[30];
    char *firstCheck = malloc(40 * sizeof(char));;
    char *lastCheck = malloc(40 * sizeof(char));;
    char *headLine = malloc(400 * sizeof(char));
    char *temp = malloc(400 * sizeof(char));
    char *str = malloc(400 * sizeof(char));
    char *headName = malloc(40 * sizeof(char));
    double grade = 0;
    int flag = 0;
    double scoreL = 0;
    double scoreQ = 0;
    double scoreB = 0;
    double scoreP1 = 0;
    double scoreP2 = 0;
    double scoreP3 = 0;
    double scoreE1 = 0;
    double scoreE2 = 0;
    double min = 11;
    int studentDNE = 0;
    double score = 0;
    strcpy(firstName, first);
    strcpy(lastName, last);


    fgets(headLine, 300, fp);

    for (int o = 0; o < strlen(firstName); o++) {
        firstName[o] = tolower(firstName[o]);
    }
    for (int o = 0; o < strlen(lastName); o++) {
        lastName[o] = tolower(lastName[o]);
    }
    
    while(1) {
        fgets(str, 300, fp);
        if (isdigit(str[1])){
            grade = -1.0;
            studentDNE = 1;
            break;
        } 
        i++;
        firstCheck = strsep(&str, ",");
        lastCheck = strsep(&str, ",");
        for (int o = 0; o < strlen(firstCheck); o++) {
            *(firstCheck + o ) = tolower(*(firstCheck+o));
        }
        for (int o = 0; o < strlen(lastCheck); o++) {
            *(lastCheck + o) = tolower(*(lastCheck+o));
        }
        int f = strcmp(firstCheck,firstName);
        int d = strcmp(lastCheck, lastName);
        if ((f == 0) && (d== 0)) break;
    }

    if (studentDNE == 0) {
        for (int h = 0; h < 2; h++) headName = strsep(&headLine, ",");
        i = 0;

        while (i < 45) {
            headName = strsep(&headLine, ",");
            temp = strsep(&str, ",");
            if (temp == NULL || temp[0] == '\0') {
                temp = strdup("0");
            }
            sscanf(temp, "%lf", &score);
            if (headName[0] == 'L') {
                scoreL += score;
            }
            else if (headName[0] == 'Q') {
                q[j] = score;
                j++;
            }
            else if (headName[0] == 'B') {
                scoreB += score;
            }
            else if (headName[0] == 'P') {
                    if (headName[1] == '1') {
                    scoreP1 += (score)/100;
                }
                else if ((headName[1] == '2') || (headName[1] == '3')) {
                    scoreP2 += (score)/100;
                }
                else {
                    scoreP3 += (score)/100;
                } 
            }
            else if (headName[0] == 'E') {
                if (headName[1] == '1' || headName[1] == '2' || headName[1] == '3' || headName[1] == '4' || headName[1] == '5' || headName[1] == '6') {
                    scoreE1 += (score/50);
                }
                else {
                    scoreE2 += (score/75);
                }
            }
            i++;
        }

        for (int k = 0; k < 11; k++) {
            if (q[k] < min) min = q[k];
        }
        for (int k = 0; k < 11; k++) {
            if (q[k] == min & flag == 0) {
                flag = 1;
            }
            else scoreQ += q[k];
        }
        scoreE1 *= 5;
        scoreE2 *= 7.5;
        scoreP1 *= 2;
        scoreP2 *= 4;
        scoreP3 *= 5;
        scoreB /= 100;
        scoreQ /= 10;
        scoreL /= 100;
        grade = scoreE1 + scoreE2 + scoreP1 + scoreP2 + scoreP3 + scoreB + scoreQ + scoreL;
    }
    fclose(fp);
    return grade;
}
