#ifndef K_MEANS_MIO_CPP_CLUSTER_H
#define K_MEANS_MIO_CPP_CLUSTER_H

#include <queue>
#include "Point.h"
#include <omp.h>

class Cluster {
    private:
        double x;
        double y;

        double new_x;
        double new_y;

        int size;

    public:
        Cluster(double x, double y) {
            new_x = 0;
            new_y = 0;
            size = 0;
            this->x = x;
            this->y = y;
        }

        Cluster() {
            new_x = 0;
            new_y = 0;
            size = 0;
            this->x = 0;
            this->y = 0;
        }

        void addPoint(Point point) {
            #pragma omp atomic
            new_x += point.getX();
            #pragma omp atomic
            new_y += point.getY();
            #pragma omp atomic
            size++;
        }

        void freePoint() {
            this->new_x = 0;
            this->new_y = 0;
            this->size = 0;
        }

        double getX() {
            return x;
        }

        double getY() {
            return y;
        }

        bool updateCoords() {
            if (this-> x == new_x/this->size && this->y == new_y/this->size) {
                return false;
            }
            this->x = new_x/this->size;
            this->y = new_y/this->size;

            return true;
        }
    
};

#endif //K_MEANS_MIO_CPP_CLUSTER_H