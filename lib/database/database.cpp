#include "database.h"

Database::Database() {}

void Database::connect_to_database(std::string project, std::string server, std::string table) {}

void Database::set_projectID(std::string project) {}

void Database::set_serverID(std::string server) {}

void Database::set_tableID(std::string table) {}

std::string Database::get_projectID() {
    return projectID;
}

std::string Database::get_serverID() {
    return serverID;
}

std::string Database::get_tableID() {
    return tableID;
}

void Database::insert_sensor_data(double moisture_level, double moisture) {}

void Database::insert_sensor_data(double pH, double moisture_level, double moisture) {}

std::tuple<double, double> Database::get_data_from_date_time(std::string date, std::string time) {
    std::tuple<double, double> data = {0,0};
    return data;
}