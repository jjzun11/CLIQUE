/*
 * Returns all possible Cliques of the given adjacency matrix of a graph
 * as subarrays in the return array.
 * Runtime is exponential, only if amount of cliques is exponential.
 * But its performance on average inputs is way better.
 * (@author: Jan Luegering)
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
			for(int y=x+1; y<n;++y) {
				counter++;
				for(int z=y+1; z<=n;++z) {
					counter++; //runtime

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

								}
							}
						}
					}
				}
			}
		}

		for(unsigned int pointer=0; pointer<cl3.size(); ++pointer) {
			// higher order cliques search for each CLIQUE3 structure; start with line of last element in it
			for(int o=cl3.at(pointer).at(cl3.at(pointer).size()-1); o<n; ++o) {
				++counter; // runtime
				for(unsigned int c=0; c<cl3.at(pointer).size(); ++c) {
					++counter; // runtime
					if(adjacencyMatrix.at(o).at((cl3.at(pointer).at(c))-1) == 1) {
						if(c==(cl3.at(pointer).size()-1)) {
							if(std::find(cl3.at(pointer).begin(),cl3.at(pointer).end(),o+1) == cl3.at(pointer).end()) {
								// insert in order into copy
								std::vector<int> cl = cl3.at(pointer);
								for(unsigned int insert=0;insert<cl.size();++insert) {
									if(cl.at(insert)>o+1) {
										cl.insert(cl.begin()+insert, o+1);
										break;
									}
									if(insert==cl.size()-1) {
										cl.push_back(o+1);
										break;
									}

								}
								cl3.push_back(cl);
							}
						}
					}
					else {
						break;
					}
				}
			}
		}
	}
	/* End of CLIQUE Algorithm.*/
	return cl3;
}
