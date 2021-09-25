#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define NODE_INIT_SIZE 2

//#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))
//#define COUNT_OF(x) sizeof(x) / sizeof(x[0])

typedef struct MatrixGraph {
	bool** matrix;
	char** node_ids;
	size_t node_count;
	size_t node_capacity;
} matrix_graph;

void m_graph_init(matrix_graph* m_graph) {

	m_graph->matrix = (bool **) malloc(NODE_INIT_SIZE * sizeof(bool *));

	if(m_graph->matrix == NULL) {
		printf("Could not allocate to matrix\n");
		return;
	}

	for (size_t i = 0; i < NODE_INIT_SIZE; ++i) {
		m_graph->matrix[i] = (bool *) calloc(NODE_INIT_SIZE, sizeof(bool));
		if(m_graph->matrix[i] == NULL) {
			printf("Could not allocate to matrix row\n");
			return;
		}
	}
	
	m_graph->node_ids = (char **) malloc(NODE_INIT_SIZE * sizeof(char *));

	if(m_graph->node_ids == NULL) {
		printf("Could not allocate to node id array\n");
		return;
	}

	m_graph->node_count = 0;
	m_graph->node_capacity = NODE_INIT_SIZE;

}

void m_graph_check_capacity(matrix_graph* m_graph) {
	if(m_graph->node_count < m_graph->node_capacity)
		return;

	for (size_t i = 0; i < m_graph->node_capacity; ++i) {
		m_graph->matrix[i] = (bool *) realloc(m_graph->matrix[i], sizeof(bool) * m_graph->node_capacity * 2);			
		if(m_graph->matrix[i] == NULL) {
			printf("Failled to realloc matrix row\n");
			return;
		}
	}

	m_graph->matrix = (bool **) realloc(m_graph->matrix, sizeof(bool*) * m_graph->node_capacity * 2);
		
	if(m_graph->matrix == NULL) {
		printf("Failled to realloc matrix\n");
		return;
	}

	m_graph->node_capacity *= 2;

	//printf("Realloced\n");

}

bool m_graph_node_is_in_graph(char* node_id, matrix_graph* m_graph) {
	if(m_graph->node_count == 0) {
		printf("No nodes in graph\n");
		return false;
	}

	for (size_t i = 0; i < m_graph->node_count; ++i) {
		//printf("Is %s = to %s\n", node_id, m_graph->node_ids[i]);
		if(strcmp(node_id, m_graph->node_ids[i]) == 0){
			return true;
		}
	}

	return false;
}

size_t m_graph_add_node(char* node_id, matrix_graph* m_graph) {
	int64_t raw_index = m_graph_get_node_index(node_id, m_graph);

	if(raw_index >= 0) {
		printf("Node: %s allready in graph\n", node_id);
		return (size_t) raw_index;
	}

	m_graph_check_capacity(m_graph);
	m_graph->node_ids[m_graph->node_count] = (char*) malloc(sizeof(node_id));
	strcpy(m_graph->node_ids[m_graph->node_count], node_id);

	printf("Added: %s\n\n", m_graph->node_ids[m_graph->node_count]);
	m_graph->node_count++;
	return m_graph->node_count - 1;
}

int64_t m_graph_get_node_index(char* node_id, matrix_graph* m_graph) {

	if(m_graph->node_count == 0) {
		printf("No nodes in graph\n");
		return -1;

	int64_t i;
	bool found = false;

	for (i = 0; i < m_graph->node_count; i++)
	{
		if(node_id == m_graph->node_ids[i]) {
			found = true;
			break;
		}
	}

	if(!found) {
		return -1;
	}

	return i;
	
}

void m_graph_add_link(char* child_id, char* parent_id, matrix_graph* m_graph) {
	m_graph_add_node(child_id, m_graph);
	m_graph_add_node(parent_id, m_graph);
}

void m_graph_free(matrix_graph m_graph);
