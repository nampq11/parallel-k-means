#include<iostream>
#include<cmath>
#include<fstream>
#include<chrono>
#include<omp.h>
#include "Point.h"
#include "Cluster.h"
#include "Kmeans.h"
#include "Parallel.h"
#include "Kmeans.cpp"

using namespace std;
using namespace std::chrono;

void Parallel::compute_distance(std::vector<Point> &points, std::vector<Cluster> &clusters) {
    unsigned long points_size = points.size();
    unsigned long clusters_size = clusters.size();

    double min_distance;
    int min_index;

    #pragma omp parallel default(shared) private(min_distance, min_index) firstprivate(points_size, clusters_size)
    {
        #pragma omp for schedule(static)
        for (int i = 0; i < points_size; i++)
        {
            min_index = 0;
            min_distance = euclidean_distance(points[i], clusters[0]);

            for (int j = 0; j < clusters_size; j++)
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
}

void Parallel::run() {
    printf("Starting parallel..\n");
    int max_range = Parallel::get_max_range();
    int num_point = Parallel::get_num_point();
    int num_cluster = Parallel::get_num_cluster();
    int max_iterations = Parallel::get_max_iterations();

    printf("Number of points: %d\n", num_point);
    printf("Number of clusters: %d\n", num_cluster);
    printf("Number of processors: %d\n", omp_get_num_procs());

    srand(time(NULL));
    double time_point1 = omp_get_wtime();

    printf("Starting initialization..\n");
    vector<Point> points;
    vector<Cluster> clusters;

    omp_set_num_threads(12);
    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                printf("Creating points..\n");
                points = init_point(num_point, num_cluster, max_range);
                printf("Points created..\n");

                try {
                    printf("Drawing chart..\n");
                    Parallel::draw_chart_gnu(points);
                } catch (int e) {
                    printf("Chart not available, gnuplot not found\n");
                }
            }
            #pragma omp section
            {
                printf("Creating clusters..\n");
                clusters = init_cluster(num_cluster);
                printf("Clusters created..\n");
            }
        }
    }

    double time_point2 = omp_get_wtime();
    double duration = time_point2 - time_point1;
    printf("Points and clusters generated in %f seconds\n", duration);

    bool conv = true;
    int iterations = 0;
    while (conv && iterations < max_iterations)
    {
        iterations++;
        compute_distance(points, clusters);
        conv = Parallel::update_clusters(clusters);
        printf("Iteration %d done\n", iterations);
    }

    double time_point3 = omp_get_wtime();
    duration = time_point3 - time_point2;
    printf("Number of iterations: %d, total time: %f seconds, time per iteration: %f seconds\n",
            iterations, duration, duration/iterations);

    try {
        printf("Drawing chart..\n");
        Parallel::draw_chart_gnu(points);
    } catch (int e) {
        printf("Chart not available, gnuplot not found\n");
    }
}