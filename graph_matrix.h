#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define NODE_INIT_SIZE 10

#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

typedef struct MatrixGraph {
	bool** matrix;
	char** node_ids;
	size_t node_count;
	size_t node_capacity;
} matrix_graph;

void m_graph_init(matrix_graph m_graph) {

	m_graph.matrix = (bool **) malloc(NODE_INIT_SIZE * sizeof(bool *));

	if(m_graph.matrix == NULL) {
		printf("Could not allocate to matrix\n");
		return;
	}

	for (size_t i = 0; i < NODE_INIT_SIZE; ++i) {
		m_graph.matrix[i] = (bool *) calloc(NODE_INIT_SIZE, sizeof(bool));
		if(m_graph.matrix[i] == NULL) {
			printf("Could not allocate to matrix row\n");
			return;
		}
	}
	
	m_graph.node_ids = (char **) malloc(NODE_INIT_SIZE * sizeof(char *));

	if(m_graph.node_ids == NULL) {
		printf("Could not allocate to node id array\n");
		return;
	}

	m_graph.node_count = 0;
	m_graph.node_capacity = NODE_INIT_SIZE;

}

void m_graph_check_capacity(matrix_graph m_graph) {
	if(m_graph.node_count < m_graph.node_capacity)
		return;

	for (size_t i = 0; i < m_graph.node_capacity; ++i) {
		m_graph.matrix[i] = (bool *) realloc(m_graph.matrix[i], sizeof(bool) * m_graph.node_capacity * 2);			
		if(m_graph.matrix[i] == NULL) {
			printf("Failled to realloc matrix row\n");
			return;
		}
	}

	m_graph.matrix = (bool **) realloc(m_graph.matrix, sizeof(bool*) * m_graph.node_capacity * 2);
		
	if(m_graph.matrix == NULL) {
		printf("Failled to realloc matrix\n");
		return;
	}

	m_graph.node_capacity *= 2;

}

void m_graph_add_node(char* node_id, matrix_graph m_graph) {
	m_graph_check_capacity(m_graph);

	/*Check if node in graph*/
	m_graph.node_ids[m_graph.node_count + 1] = node_id;
}

void m_graph_free(matrix_graph m_graph);

