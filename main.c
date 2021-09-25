#include <stdio.h>
#include <stdlib.h>

#include "graph_matrix.h"

//#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))
#define COUNT_OF(x) ((sizeof(x)/sizeof(x[0])))

int main(int argc, char** argv)
{
	matrix_graph m_graph;
	m_graph_init(&m_graph);

	size_t n1_ind = m_graph_add_node("n1", &m_graph);
	size_t n2_ind = m_graph_add_node("n2", &m_graph);
	size_t n3_ind = m_graph_add_node("n3", &m_graph);
	size_t n4_ind = m_graph_add_node("n4", &m_graph);
	size_t n5_ind = m_graph_add_node("n4", &m_graph);

	printf("Node count: %ld\n", m_graph.node_count);

	return EXIT_SUCCESS;
}
