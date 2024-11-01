#ifndef PARALLEL_H
#define PARALLEL_H

#include "Kmeans.h"
#include "Point.h"
#include "Cluster.h"
#include <vector>

class Parallel: public Kmeans {
    public:
        Parallel(int max_range, int num_point, int num_cluster, int max_iterations): Kmeans(max_range, num_point, num_cluster, max_iterations) {}        

        void compute_distance(std::vector<Point> &points, std::vector<Cluster> &clusters) override;
        void run() override;
};

#endif //PARALLEL_H