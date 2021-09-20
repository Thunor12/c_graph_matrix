#include <stdio.h>
#include <stdlib.h>

#include "graph_matrix.h"

#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

int main(int argc, char** argv)
{
	matrix_graph m_graph;
	m_graph_init(m_graph);

	printf("%ld\n", COUNT_OF(m_graph.matrix));

	return EXIT_SUCCESS;
}
