#ifndef DATABASE_H_
#define DATABASE_H_

//#include "google"

class database {
    private:

    public:
        database();

        void insert_sensor_data(double moisture_level, double moisture);
        void insert_sensor_data(double pH, double moisture_level, double moisture);
};

#endif /* DATABASE_H_ */