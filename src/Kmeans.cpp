#include<iostream>
#include<cmath>
#include<fstream>
#include<stdio.h>
#include<omp.h>
#include<chrono>
#include<random>

#include "Point.h"
#include "Cluster.h"
#include "Kmeans.h"

using namespace std;

vector<Point> Kmeans::init_point(int num_point, int num_cluster, int ) {
    vector<Point> points(num_point);
    Point *ptr = &points[0];

    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::normal_distribution<double> dist(-max_range / 10.0, max_range / 10.0);

    vector<Point> cluster_centers(num_cluster);
    for (int i = 0; i < num_cluster; i++)
    {
        cluster_centers[i] = Point(rand() % max_range, rand() % max_range);
    }
    

    for (int i = 0; i < num_point; i++)
    {    
        int cluster_idx = i % num_cluster;
        double x = cluster_centers[cluster_idx].getX() + dist(gen);
        double y = cluster_centers[cluster_idx].getY() + dist(gen);
        Point* point = new Point(x, y);
        ptr[i] = *point;
    }

    return points;
}

vector<Cluster> Kmeans::init_cluster(int num_cluster) {
    vector<Cluster> clusters(num_cluster);
    Cluster *ptr = &clusters[0];
    for (int i = 0; i < num_cluster; i++)
    {
        Cluster* cluster = new Cluster(rand() % (int)max_range, rand() % (int)max_range);
        ptr[i] = *cluster;
    }

    return clusters;
}

bool Kmeans::update_clusters(vector<Cluster> &clusters) {
    bool converged = false;
    for (int i = 0; i < clusters.size(); i++)
    {
        converged = clusters[i].updateCoords();
        clusters[i].freePoint();
    }

    return converged;
}

double Kmeans::euclidean_distance(Point point, Cluster cluster) {
    double distance = sqrt(pow(point.getX() - cluster.getX(), 2) + pow(point.getY() - cluster.getY(), 2));
    return distance;
}

void Kmeans::draw_chart_gnu(vector<Point> &points) {
    ofstream outfile("data.txt");

    for(int i = 0; i < points.size(); i++) {
        Point point = points[i];
        outfile << point.getX() << " " << point.getY() << " " << point.getClusterId() << endl;
    }

    outfile.close();
    system("gnuplot -p -e \"plot 'data.txt' using 1:2:3 with points palette notitle\"");
    remove("data.txt");
}

void Kmeans::compute_distance(vector<Point> &points, vector<Cluster> &clusters) {
    unsigned long points_size = points.size();
    unsigned long clusters_size = clusters.size();

    double min_distance;
    int min_index;

    for (int i = 0; i < points_size; i++)
    {
        Point &point = points[i];

        min_distance = euclidean_distance(point, clusters[0]);
        min_index = 0;

        for (int j = 0; j < clusters_size; j++)
        {
            Cluster &cluster = clusters[j];

            double distance = euclidean_distance(point, cluster);

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