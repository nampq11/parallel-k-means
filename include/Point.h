#include<printf.h>
#ifndef K_MEANS_MIO_CPP_POINT_H
#define K_MEANS_MIO_CPP_POINT_H

class Point {
    private:
        double x;
        double y;
        int cluster_id;

    public:
        Point(double x, double y){
            this-> x = x;
            this-> y = y;
            cluster_id = 0;
        }

        Point() {
            x = 0;
            y = 0;
            cluster_id = 0;
        }

        double getX(){
            return this->x;
        }

        double getY(){
            return this->y;
        }
        
        int getClusterId(){
            return cluster_id;
        }

        void setClusterId(int cluster_id){
            this->cluster_id = cluster_id;
        }
    
};
#endif //K_MEANS_MIO_CPP_POINT_H