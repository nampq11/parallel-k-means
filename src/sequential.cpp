#include<iostream>
#include<cmath>
#include<fstream>
#include<stdio.h>
#include<omp.h>
#include<chrono>

#include "Point.h"
#include "Cluster.h"
#include "Kmeans.h"
#include "Sequential.h"

using namespace std;
using namespace std::chrono;

void Sequential::compute_distance(std::vector<Point> &points, std::vector<Cluster> &clusters) {
    double min_distance;
    int min_index;

    for (int i = 0; i < points.size(); i++)
    {
        min_index = 0;
        min_distance = euclidean_distance(points[i], clusters[0]);

        for (int j = 0; j < clusters.size(); j++)
        {
            Cluster &cluster = clusters[j];

            double distance = euclidean_distance(points[i], cluster);

            if (distance < min_distance)
            {
                min_distance = distance;
                min_index = j;
            }
        }
        points[i].setClusterId(min_index);
        clusters[min_index].addPoint(points[i]);
    }
}

void Sequential::run() {
    printf("Starting sequential..\n");
    int max_range = Sequential::get_max_range();
    int num_point = Sequential::get_num_point();
    int num_cluster = Sequential::get_num_cluster();
    int max_iterations = Sequential::get_max_iterations();

    printf("Number of points: %d\n", num_point);
    printf("Number of clusters: %d\n", num_cluster);

    srand(time(NULL));
    double time_point1 = omp_get_wtime();

    printf("Creating points..\n");
    vector<Point> points = init_point(num_point);
    printf("Points initialized..\n"); 

    printf("Creating clusters..\n");
    vector<Cluster> clusters = init_cluster(num_cluster);
    printf("Clusters initialized..\n");

    double time_point2 = omp_get_wtime();
    auto duration = time_point2 - time_point1;

    printf("Points and clusters created in %f seconds\n", duration);

    bool conv = true;
    int iterations = 0;
    printf("Starting iterations..\n");

    while (conv && iterations < max_iterations)
    {
        iterations++;
     
        compute_distance(points, clusters);

        conv = Sequential::update_clusters(clusters);
        printf("Iteration %d done \n", iterations);
    }   

    double time_point3 = omp_get_wtime();
    duration = time_point3 - time_point2;
    printf("Number of iterations: %d, total time: %f seconds, time per iteration: %f seconds\n", 
            iterations, duration, duration/iterations);
    
    try {
        printf("Drawing chart..\n");
        Sequential::draw_chart_gnu(points);
    } catch (int e) {
        printf("Chart \n");
    }
}