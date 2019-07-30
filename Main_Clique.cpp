#include <iostream>
#include <vector>


	void generateCombinationsRecursive(std::vector<std::vector<int> >& ans,
	    std::vector<int>& tmp, int n, int left, int k)
	{
	    if (k == 0) {
	        ans.push_back(tmp);
	        return;
	    }

	    for (int i = left; i <= n; ++i)
	    {
	        tmp.push_back(i);
	        generateCombinationsRecursive(ans, tmp, n, i + 1, k - 1);
	        tmp.pop_back();
	    }
	}

	// Prints all combinations of size k of numbers
	// from 1 to n.
	// We merely require the specific case k=3 for binary addition of each line i,j and 1 result line k to compare to.
	std::vector<std::vector<int> > generateCombinations(int n, int k)
	{
		std::vector<std::vector<int> > ans;
		std::vector<int> tmp;
	    generateCombinationsRecursive(ans, tmp, n, 1, k);
	    return ans;
	}

	void printVector(std::vector<std::vector<int>>vec) {
		std::printf("ALL CLIQUES:");
		for(int i=0; i<vec.size(); i++) {
			std::printf("\nCL%d: ", i);
			for(int j=0; j<vec.at(i).size(); j++) {
				std::printf("%d | ", vec.at(i).at(j));
			}
		}
		return;
	}

	bool binaryAdditionSuccess(std::vector<std::vector<int>> adj, int i, int j, int k) {

		// array coordinates
		i = i-1;
		j = j-1;
		k = k-1;

		// Column Results for Binary Addition of lines i and j
		int resultI = (adj.at(i).at(i) + adj.at(j).at(i))%2;
		int resultJ = (adj.at(i).at(j) + adj.at(j).at(j))%2;
		int resultK = (adj.at(i).at(k) + adj.at(j).at(k))%2;

		// 0 + 0 = 0 is valid in binary addition, but is not allowed
		if(resultI == resultJ && resultJ == resultK && resultK == 0) {
			return false;
		}

		// Results equal to columns in line K?
		if(resultI == adj.at(k).at(i)) {
			if(resultJ == adj.at(k).at(j)) {
				if(resultK == adj.at(k).at(k)) {
					return true;
				}
			}
		}
		return false;
	}

	/*
	 * Returns all possible Cliques of the given adjacency matrix of a graph
	 * as subarrays in the return array.
	 */
	std::vector<std::vector<int>> CLIQUE(std::vector<std::vector<int>>adjacencyMatrix) {

		std::vector<std::vector<int>> cl3;
		int i;
		int j;
		int k;
		int size;
		int last;
		int prelast;
		int first;
		int postfirst;

		// only n choose 3 combinations needed
		    int n = adjacencyMatrix.size();
		    std::vector<std::vector<int> > ans = generateCombinations(n, 3);

		    for(unsigned int combinations=0; combinations < ans.size(); combinations++) {

		    	// get Line/Column Combination
		    	i = ans.at(combinations).at(0);
		    	j = ans.at(combinations).at(1);
		    	k = ans.at(combinations).at(2);

		    	// binary addition and 1 result line to compare the addition's result to
		    	if(binaryAdditionSuccess(adjacencyMatrix, i, j, k)) {

		    		// new CLIQUE3 structure found
		    		std::vector<int> cl;
		    		cl.push_back(i);
		    		cl.push_back(j);
		    		cl.push_back(k);

		    		cl3.push_back(cl);
		    	}
		    }

		    /* End of CLIQUE3 Algorithm.
		     * NEXT SECTION:
		     * Converting the CLIQUE3 subarrays into Cliques of arbitrary size k.
		     */

			for(unsigned int i=0; i<cl3.size();i++) {

				// retrieve the last two digits of subarray
				size = cl3.at(i).size();
				last = cl3.at(i).at(size-1);
				prelast = cl3.at(i).at(size-2);

				for(unsigned int j=i+1; j<cl3.size();j++) {
					// retrieve first two digits of other subarray(s)
					first = cl3.at(j).at(0);
					postfirst = cl3.at(j).at(1);

					// compare to first two digits of every other subarray
					// -> higher order cliques consist of overlapping CLIQUE3 structures

					if(prelast == first && last == postfirst) {
						std::vector<int> K = cl3.at(i);

						for(unsigned int k=2; k<cl3.at(j).size(); k++) {
							K.push_back(cl3.at(j).at(k));
						}

						cl3.push_back(K);
					}
				}
			}
			return cl3;
	}



int main(int argc, char** argv) {

	// adjacency matrix

	// Beispiel Eingabe
	std::vector<int> l1 = {0,0,1,1,1,1,0,0};
	std::vector<int> l2 = {0,0,0,1,0,1,0,1};
	std::vector<int> l3 = {1,0,0,1,0,1,0,0};
	std::vector<int> l4 = {1,1,1,0,0,1,0,0};
	std::vector<int> l5 = {1,0,0,0,0,0,0,0};
	std::vector<int> l6 = {1,1,1,1,0,0,0,1};
	std::vector<int> l7 = {0,0,0,0,0,0,0,0};
	std::vector<int> l8 = {0,1,0,0,0,1,0,0};


	std::vector<std::vector<int>> adj = {l1, l2, l3, l4, l5, l6, l7, l8};

	// compute
	std::vector<std::vector<int>> cls = CLIQUE(adj);

	// output
	printVector(cls);

	return 0;
}




