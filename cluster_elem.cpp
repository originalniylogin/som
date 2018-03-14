#include "cluster_elem.h"
#include <fstream>

std::vector<double> cluster_elem::get_data() const
{
	return _data;
}

int cluster_elem::get_cluster_id() const
{
	return _cluster_id;
}

std::vector<cluster_elem> read_fisher_iris(std::string filename)
{
	std::ifstream ifs(filename);
	std::vector<cluster_elem> iris_data;

	while (ifs)
	{
		int iris_type;
		std::vector<double> vec(4);

		ifs >> iris_type;
		for (int i = 0; i < 4; ++i)
			ifs >> vec[i];

		iris_data.push_back(cluster_elem(vec, iris_type));
	}
	iris_data.pop_back();

	return iris_data;
}
