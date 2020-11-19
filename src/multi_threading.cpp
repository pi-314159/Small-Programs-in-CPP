#include <iostream>
#include <thread>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <cstring>

using namespace std;

string exec(const char* cmd) {
    char buffer[128];
    string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

void process1(char *command, int *retVal)
{
    if (exec(command) == "Success!") {
        *retVal = 1;
    } else {
        *retVal = 0;
    }
}

void process2(char *command, int *retVal)
{
    if (exec(command) == "Success!") {
        *retVal = 1;
    } else {
        *retVal = 0;
    }
}

int main(int argc, char** argv)
{
    const char* nullSpace1 = "\" \"";
    const char* nullSpace2 = " \"";
    const char* qMark = "\"";

    int val1, val2;

    if (argc > 3) {

        char* param1 = (char*)malloc(strlen(argv[1]) + strlen(argv[3]) + strlen(argv[4]) + strlen(argv[5]) + strlen(argv[6]) + strlen(argv[7]) + 16);
        char* param2 = (char*)malloc(strlen(argv[2]) + strlen(argv[3]) + strlen(argv[4]) + strlen(argv[5]) + strlen(argv[6]) + 13);

        strcpy(param1, argv[1]);
        strcat(param1, nullSpace2);
        strcat(param1, argv[3]);
        strcat(param1, nullSpace1);
        strcat(param1, argv[4]);
        strcat(param1, nullSpace1);
        strcat(param1, argv[5]);
        strcat(param1, nullSpace1);
        strcat(param1, argv[6]);
        strcat(param1, nullSpace1);
        strcat(param1, argv[7]);
        strcat(param1, qMark);

        strcpy(param2, argv[2]);
        strcat(param2, nullSpace2);
        strcat(param2, argv[3]);
        strcat(param2, nullSpace1);
        strcat(param2, argv[4]);
        strcat(param2, nullSpace1);
        strcat(param2, argv[5]);
        strcat(param2, nullSpace1);
        strcat(param2, argv[6]);
        strcat(param2, qMark);

        thread th1(process1, param1, &val1);
        thread th2(process2, param2, &val2);
        th1.join();
        th2.join();

    } else {

        thread th1(process1, argv[1], &val1);
        thread th2(process2, argv[2], &val2);
        th1.join();
        th2.join();

    }

    if (val1 == 1 && val2 == 1) {
        cout << "Success!";
    } else {
        cout << "Failed.";
    }
}

// g++ -pthread -o multi_threading multi_threading.cpp
