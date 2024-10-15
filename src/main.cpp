#include<iostream>
#include<cmath>
#include<stdio.h>
#include<omp.h>
#include<chrono>

#include "Point.h"
#include "Cluster.h"

using namespace std;
using namespace std::chrono;

double max_range = 1000;
int num_point = 1000;
int num_cluster = 5;
vector<Point> init_point(int num_point);
vector<Cluster> init_cluster(int num_cluster);
void compute_distance(vector<Point> &points, vector<Cluster> &clusters);
bool update_clusters(vector<Cluster> &clusters);


vector<Point> init_point(int num_point) {
    vector<Point> points(num_point);
    Point *ptr = &points[0];
    for (int i = 0; i < num_point; i++)
    {
        Point* point = new Point(rand() % (int)max_range, rand() % (int)max_range);
        ptr[i] = *point;
    }

    return points;
}

vector<Cluster> init_cluster(int num_cluster) {
    vector<Cluster> clusters(num_cluster);
    Cluster *ptr = &clusters[0];
    for (int i = 0; i < num_cluster; i++)
    {
        Cluster* cluster = new Cluster(rand() % (int)max_range, rand() % (int)max_range);
        ptr[i] = *cluster;
    }

    return clusters;
}

// void compute_distance(vector<Point> &points, vector<Cluster> &clusters) {
//     unsigned long points_size = points.size();
//     unsigned long clusters_size = clusters.size();

//     double min_distance;
//     int min_index;

//     for (int i = 0; i < points_size; i++)
//     {
//         Point &point = points[i];

//         min_distance = euclidean_distance(point, clusters[0]);
//         min_index = 0;

//         for (int j = 0; j < clusters_size; j++)
//         {
//             Cluster &cluster = clusters[j];

//             double distance = euclidean_distance(point, cluster);

//             if (distance < min_distance)
//             {
//                 min_distance = distance;
//                 min_index = j;
//             }
//         }
//         points[i].setClusterId(min_index);
//         clusters[min_index].addPoint(points[i]);
//     }
    
// }

bool update_clusters(vector<Cluster> &clusters) {
    bool converged = false;
    for (int i = 0; i < clusters.size(); i++)
    {
        converged = clusters[i].updateCoords();
        clusters[i].freePoint();
    }

    return converged;
}


double euclidean_distance(Point point, Cluster cluster) {
    double distance = sqrt(pow(point.getX() - cluster.getX(), 2) + pow(point.getY() - cluster.getY(), 2));
    return distance;
}

int main()
{
    cout << "Hello World!" << endl;

    srand(time(NULL));
    printf("Number of points: %d\n", num_point);
    printf("Number of clusters %d\n", num_cluster);

    double time_point1 = omp_get_wtime();
    printf("Starting initialization..\n");
    Point *point = new Point(1, 2);
    printf("Point: %f, %f\n", point->getX(), point->getY());
    // vector<Point> points = init_point(num_point);
    printf("Initialization done!\n");

    return 0;
}