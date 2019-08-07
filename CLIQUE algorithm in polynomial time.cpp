	/*
	 * Returns all possible Cliques of the given adjacency matrix of a graph
	 * as subarrays in the return array.
	 */
	std::vector<std::vector<int>> CLIQUE(std::vector<std::vector<int>>adjacencyMatrix) {

		std::vector<std::vector<int>> cl3;
		int i;
		int j;
		int k;
		int resultI;
		int resultJ;
		int resultK;
		counter = 0;
		int n = adjacencyMatrix.size();

		if(n>2) {

			// n choose 3 combinations for cliques of size 3
			for(int x=1; x<n-1;++x) {
				counter++;
				for(int y=2; y<n;++y) {
					counter++;
					for(int z=3; z<=n;++z) {
						counter++; //runtime
						if(z>y && y>x) {

						// binary addition and 1 result line to compare the addition's result to
						// array coordinates
						i = x-1;
						j = y-1;
						k = z-1;

						// Column Results for Binary Addition of lines i and j
						resultI = (adjacencyMatrix.at(i).at(i) + adjacencyMatrix.at(j).at(i))%2;
						resultJ = (adjacencyMatrix.at(i).at(j) + adjacencyMatrix.at(j).at(j))%2;
						resultK = (adjacencyMatrix.at(i).at(k) + adjacencyMatrix.at(j).at(k))%2;

						// Results equal to columns in line K?
						if(resultI == adjacencyMatrix.at(k).at(i)) {
							if(resultJ == adjacencyMatrix.at(k).at(j)) {
								if(resultK == adjacencyMatrix.at(k).at(k)) {
									if(!(resultI == resultJ && resultJ == resultK && resultK == 0)) {
										// new CLIQUE3 structure found
										std::vector<int> cl;
										cl.push_back(i+1);
										cl.push_back(j+1);
										cl.push_back(k+1);
										cl3.push_back(cl);

										// higher order cliques search
										for(int o=k+1; o<k+n; o++) {
											counter++; // runtime
											for(unsigned int c=0; c<cl3.at(cl3.size()-1).size(); c++) {
												counter++; // runtime
												if(adjacencyMatrix.at(o%n).at((cl3.at(cl3.size()-1).at(c))-1) == 1) {
													if(c==(cl3.at(cl3.size()-1).size()-1)) {
														cl.push_back((o%n)+1);
														cl3.push_back(cl);
													}
												}
												else {
													break;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
		    /* End of CLIQUE Algorithm.*/
			return cl3;
}
