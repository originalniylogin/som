#include "som.h"

double som::euclidian_distance(const std::vector<double>& vec1, const std::vector<double>& vec2)
{
	double distance = 0;
	for (int i = 0; i < vec1.size(); ++i)
		distance += (vec1[i] - vec2[i])*(vec1[i] - vec2[i]);
	return sqrt(distance);
}

double som::cluster_radius(std::vector<const cluster_elem*>& cluster, std::vector<double> center)
{
	std::vector<double> dispersion(_dim, 0);
	for (int i = 0; i < cluster.size(); ++i)
	{
		std::vector<double> cluster_elem = cluster[i]->get_data();
		for (int j = 0; j < cluster_elem.size(); ++j)
		{
			double dif = cluster_elem[j] - center[j];
			dispersion[j] += dif*dif;
		}
	}

	for (int k = 0; k < _dim; ++k)
		dispersion[k] /= cluster.size();

	return  euclidian_distance(std::vector<double>(_dim, 0), dispersion);
}

std::vector<double> som::cluster_center(std::vector<const cluster_elem*>& cluster)
{
	std::vector<double> center(_dim, 0);

	for (int i = 0; i < cluster.size(); ++i)
	{
		std::vector<double> cluster_elem = cluster[i]->get_data();
		for (int j = 0; j < _dim; ++j)
			center[j] += cluster_elem[j];
	}

	for (int i = 0; i < _dim; ++i)
		center[i] /= cluster.size();

	return center;
}

std::vector<std::vector<const cluster_elem*>> som::clustering(const std::vector<cluster_elem>& data)
{
	std::vector<std::vector<const cluster_elem*>> clusters(_weights.size(), std::vector<const cluster_elem*>());

	for (int i = 0; i < data.size(); ++i)
	{
		std::vector<double> elem = data[i].get_data();
		double min_dist = DBL_MAX;
		int min_ind = -1;

		for (int j = 0; j < _weights.size(); ++j)
		{
			double dist = euclidian_distance(elem, _weights[j]);
			if (dist < min_dist)
			{
				min_dist = dist;
				min_ind = j;
			}
		}

		clusters[min_ind].push_back(&data[i]);
	}

	bool were_unions;
	do
	{
		were_unions = false;

		for (int i = 0; i < clusters.size(); ++i)
		{
			std::vector<double> center = cluster_center(clusters[i]);
			double radius = cluster_radius(clusters[i], center);
			for (int j = 0; j < clusters.size(); ++j)
			{
				if (i != j && euclidian_distance(center, cluster_center(clusters[j])) < radius)
				{
					for (int k = 0; k < clusters[j].size(); ++k)
						clusters[i].push_back(clusters[j][k]);
					clusters.erase(clusters.begin() + j);
					were_unions = true;
					break;
				}
				if (were_unions) break;
			}
			if (were_unions) break;
		}
	} while (were_unions);

	return clusters;
}
