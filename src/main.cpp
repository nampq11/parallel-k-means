#include<iostream>
#include<cmath>
#include<fstream>
#include<stdio.h>
#include<omp.h>
#include<chrono>

#include "Point.h"
#include "Cluster.h"
#include "parallel.cpp"
#include "sequential.cpp"

using namespace std;
using namespace std::chrono;

int main(int argc, char* argv[])
{
    srand(time(NULL));

    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <mode>" <<endl;
        cout << "mode: 1 for sequential, 2 for parallel" << endl;
        return 1;
    }

    string mode = argv[1];

    if (mode == "1") {
        printf("Running parallel version...\n");
        Parallel kmeans = Parallel(100000, 500000, 20, 20);
        kmeans.run();
    } else {
        printf("Running sequential version...\n");
        Sequential kmeans = Sequential(100000, 500000, 20, 20);
        kmeans.run();
    }
}