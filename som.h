#ifndef SOM_H
#define SOM_H

#include "cluster_elem.h"
#include <math.h>

class som
{
public:
	som(int neurons_count, int dim, const std::vector<cluster_elem>& data, double radius)
	{
		_dim = dim;
		_weights = std::vector<std::vector<double>>(data.size(), std::vector<double>(_dim));
		clusters = std::vector<std::vector<const cluster_elem*>>(neurons_count, std::vector<const cluster_elem*>());

		for (int i = 0; i < data.size(); ++i)
			_weights[i] = data[i].get_data();
		for (int i = 0; i < data.size() - neurons_count; ++i)
			_weights.erase(_weights.begin() + (rand() % _weights.size()));

		for (int i = 0; i < data.size(); ++i)
		{
			std::vector<double> sample = data[i].get_data();
			double min_dist = DBL_MAX;
			int min_ind = -1;
			for (int j = 0; j < _weights.size(); ++j)
			{
				double dist = euclidian_distance(sample, _weights[j]);
				if (dist < min_dist)
				{
					min_dist = dist;
					min_ind = j;
				}

				clusters[min_ind].push_back(&data[i]);
			}

			for (int j = 0; j < _weights.size(); ++j)
			{
				double dist = euclidian_distance(_weights[j], _weights[min_ind]);
				double learning_rate = 0.1 * exp(-(double)i / data.size());
				double decay = 0.5 * exp(-(double)i / data.size());
				double adjust = exp(-(dist*dist)/(2*decay*decay));

				for (int k = 0; k < _dim; ++k)
					_weights[j][k] += adjust*learning_rate*(sample[k] - _weights[j][k]);
			}
		}


		for (int i = 0; i < clusters.size(); ++i)
			if (clusters[i].size() == 0) {
				clusters.erase(clusters.begin() + i);
				_weights.erase(_weights.begin() + i);
			}
	}

	std::vector<std::vector<const cluster_elem*>> clustering(const std::vector<cluster_elem>& data);

private:
	int _dim;
	std::vector<std::vector<double>> _weights;
	std::vector<std::vector<const cluster_elem*>> clusters;
	std::vector<double> rads;
	
	double euclidian_distance(const std::vector<double>& vec1, const std::vector<double>& vec2);

	double som::mahalanobis_distance(std::vector<const cluster_elem>& cluster1, std::vector<double> center2);

	double cluster_radius(std::vector<const cluster_elem*>& cluster, std::vector<double> center);

	std::vector<double> cluster_center(std::vector<const cluster_elem*>& cluster);
};

#endif