#ifndef KMEANS_H
#define KMEANS_H

#include<string>
#include"Point.h"
#include"Cluster.h"
#include<vector>

class Kmeans {
    private:
        int max_range;
        int num_point;
        int num_cluster;
        int max_iterations;
    
    public:
        Kmeans(int max_range, int num_point, int num_cluster, int max_iterations) {
            this->max_range = max_range;
            this->num_point = num_point;
            this->num_cluster = num_cluster;
            this->max_iterations = max_iterations;
        }

        std::vector<Point> init_point(int num_point, int cluster, int max_range);
        std::vector<Cluster> init_cluster(int num_cluster);
        double euclidean_distance(Point point, Cluster cluster);
        bool update_clusters(std::vector<Cluster> &clusters);
        void draw_chart_gnu(std::vector<Point> &points);

        virtual void run() = 0;
        virtual void compute_distance(std::vector<Point> &points, std::vector<Cluster> &clusters) = 0;

        void set_max_range(int max_range) {
            this->max_range = max_range;
        }

        void set_num_point(int num_point) {
            this->num_point = num_point;
        }

        void set_num_cluster(int num_cluster) {
            this->num_cluster = num_cluster;
        }

        void set_max_iterations(int max_iterations) {
            this->max_iterations = max_iterations;
        }

        int get_max_range() {
            return max_range;
        }

        int get_num_point() {
            return num_point;
        }

        int get_num_cluster() {
            return num_cluster;
        }

        int get_max_iterations() {
            return max_iterations;
        }
};

#endif //KMEANS_H