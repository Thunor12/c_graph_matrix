#include <stdio.h>
#include <stdlib.h>

#include "graph_matrix.h"

//#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))
#define COUNT_OF(x) ((sizeof(x)/sizeof(x[0])))

int main(int argc, char** argv)
{
	matrix_graph m_graph;
	m_graph_init(&m_graph);

	m_graph_add_link("n1", "n2", &m_graph);

	printf("Node count: %ld\n", m_graph.node_count);
	
	size_t n1_ind = m_graph_get_node_index("n1", &m_graph);
	size_t n2_ind = m_graph_get_node_index("n2", &m_graph);

	printf("n1: %ld\nn2: %ld", n1_ind, n2_ind);

	printf("%d", m_graph.matrix[n1_ind][n2_ind]);

	return EXIT_SUCCESS;
}
