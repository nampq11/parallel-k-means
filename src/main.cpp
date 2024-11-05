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
    int num_of_points = (argc > 2) ? stoi(argv[2]): 100000;
    int num_of_clusters = (argc > 3) ? stoi(argv[3]): 20;
    if (mode == "1") {
        printf("Running parallel version...\n");
        Parallel kmeans = Parallel(100000, num_of_points, num_of_clusters, 20);
        kmeans.run();
    } else if (mode == "2") {
        printf("Running sequential version...\n");
        Sequential kmeans = Sequential(100000, num_of_points, num_of_clusters, 20);
        kmeans.run();
    } else {
        printf("Invalid mode\n, Use '1' for parallel, '2' for sequential\n");
    }
}