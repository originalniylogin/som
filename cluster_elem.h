#ifndef CLUSTER_ELEM_H
#define CLUSTER_ELEM_H

#include <vector>
#include <string>

class cluster_elem
{
public:
	
	cluster_elem(const std::vector<double>& data, int cluster_id = -1) : _data(data), _cluster_id(cluster_id) {}
	std::vector<double> get_data() const;
	int get_cluster_id() const;

private:
	
	std::vector<double> _data;
	int _cluster_id;

};

std::vector<cluster_elem> read_fisher_iris(std::string filename = "iris.txt");

#endif