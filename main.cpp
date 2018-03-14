#include <iostream>
#include "som.h"
#include "cluster_elem.h"

int main()
{
	std::vector<cluster_elem> data = read_fisher_iris();
	som map(data.size()/10, 4, data, 13);
	std::vector<std::vector<const cluster_elem*>> clusters = map.clustering(data);

	for (int i = 0; i < clusters.size(); ++i)
	{
		for (int j = 0; j < clusters[i].size(); ++j)
			std::cout << clusters[i][j]->get_cluster_id() << ' ';
		std::cout << std::endl << std::endl;
	}

	system("Pause");
}