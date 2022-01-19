#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <random>
#include <iomanip>
#include <chrono>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>

using namespace std;

constexpr int FLOAT_MIN = 0;
constexpr int FLOAT_MAX = 1;

/*
Extracts numbers from a given (data) char array and returns it
*/
int extractNumbers(char* data, uint8_t len, int* output)
{
    int res = 0;
    char val = 0x0;
    int num = 0;
    const uint8_t numBufSize = 6;
    char numBuf[numBufSize] = {0};
    uint8_t iNumBuf = 0;
    uint8_t j = 0;
    char* pNumBuf = numBuf; 
    bool eos = false;
    for (uint8_t i = 0; i < len; i++)
    {
        val = *data;
        if (val == '\0' || val == 13 || val == 10 || val == 0)
            eos = true;    
        else
            cout << (int)(i) << ".\t" << val << "\t" << &data << endl;
        if (iNumBuf >= numBufSize || val == '|' || val == ',' || val == ';' || eos) 
        {
            num = atoi(numBuf); //EO Number?
            if (iNumBuf > 0) {
                cout << "> Number found: " << num << ", str: '" << numBuf << "', len:" << (int)iNumBuf << endl;
                *output = num; //Save value in output array
                output++;      //Move to next pointer
                res++;              //Increase the result number
                num = 0;            //Clear num
                iNumBuf = 0;        //Reset counter
                pNumBuf = numBuf;   //Reset pointer
                for ( j = 0; j < numBufSize; j++)
                    numBuf[j] = 0;  //Clear array
            }
        } 
        else if (val >= 48 && val <= 57) //Are we dealing with a number?
        {
            *pNumBuf = val;
            pNumBuf++;
            iNumBuf++;
        }
        if (eos)
            break;
        data++;
    }
    return res;
}

/*
Estimates PI by a given number of samples
*/
float esitmatePI(long samples) {
     //std::srand(std::time(nullptr)); 
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<float> distr(FLOAT_MIN, FLOAT_MAX);
    float pi = 0, r = 0.0, x = 0.0, y = 0.0, p = 0.0;
    int inside = 0;
    for (long i = 0; i < samples; i++)
    {
        x = distr(eng);
        y = distr(eng);
        r = sqrt((x * x) + (y * y));
        if (r < 1)
            inside++;
    }
    pi = ((float)inside / (float)samples)* 4.0;
    cout << " Samples: " << samples << ", PI = ~" << pi  << endl;
    return pi;
}

template <typename RAIter>
float esitmatePI_Parallel(RAIter first, RAIter last) {
     //std::srand(std::time(nullptr)); 
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<float> distr(FLOAT_MIN, FLOAT_MAX);
    float pi = 0, r = 0.0, x = 0.0, y = 0.0, p = 0.0;
    int inside = 0;

    const size_t n = std::distance(first, last);

    #pragma omp parallel for
    for (size_t i = 0; i < n; i++) {
        //--auto& elem = *(first + i);
        x = distr(eng);
        y = distr(eng);
        r = sqrt((x * x) + (y * y));
        if (r < 1)
            inside++;
    }
    pi = ((float)inside / (float)n)* 4.0;
    cout << " Samples: " << n << ", PI = ~" << pi  << endl;
    return pi;
}

int main() 
{
    
    cout << endl;
    cout << "-------------------" << endl;
    cout << " Find PI           " << endl;
    cout << "-------------------" << endl << endl;
    cout << "Calculation started... "<< endl;

    clock_t start = clock();

    int samples = 1000000000;
   
    esitmatePI(samples); 

    double s =  std::chrono::duration<double, std::milli>(clock()-start).count() / 1000;
    cout << "Serial calculation finished in " << (s) << " seconds" << endl;

    cout << endl << endl;
    cout << "Parallel Calculation started... "<< endl;

    std::vector<int> v(samples, 1);
    esitmatePI_Parallel(v.begin(), v.end()); 

    s =  std::chrono::duration<double, std::milli>(clock()-start).count() / 1000;
    cout << "Parallel calculation finished in " << (s) << " seconds" << endl;

    getchar();
}

