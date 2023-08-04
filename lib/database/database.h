#ifndef DATABASE_H_
#define DATABASE_H_

#include "tuple"

class database {
    private:
        std::string projectID, serverID, tableID;

    public:
        database();

        void connect_to_database(std::string project, std::string server, std::string table);

        void set_projectID(std::string project);
        void set_serverID(std::string server);
        void set_tableID(std::string table);
        std::string get_projectID();
        std::string get_serverID();
        std::string get_tableID();

        void insert_sensor_data(double moisture_level, double moisture);
        void insert_sensor_data(double pH, double moisture_level, double moisture);

        std::tuple<double, double> get_data_from_date_time(std::string date, std::string time);
};

#endif /* DATABASE_H_ */