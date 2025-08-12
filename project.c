#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAX_EDGES 3794
#define MAX_NAME_LENGTH 100
#define CSV_LINE_MAX_LENGTH 1024

char doctorIndices[MAX_EDGES][MAX_NAME_LENGTH];
int docIndex = 0;

int not_in(char *doctor) {
    for (int i = 0; i < docIndex; i++) {
        if (strcmp(doctor, doctorIndices[i]) == 0)
            return i;
    }
    strcpy(doctorIndices[docIndex], doctor);
    int index = docIndex;
    docIndex++;
    return index;
}

int max(int edgeData[][3], int totalEdges) {
    int maxNode = 0;
    for (int i = 0; i < totalEdges; i++) {
        if (edgeData[i][0] > maxNode)
            maxNode = edgeData[i][0];
        if (edgeData[i][1] > maxNode)
            maxNode = edgeData[i][1];
    }
    return maxNode;
}

int readCSVFile(const char *filename, int edgeData[][3]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return 0;
    }

    char line[CSV_LINE_MAX_LENGTH];
    int totalEdges = 0;

    // Read each line from the file
    while (fgets(line, CSV_LINE_MAX_LENGTH, file) != NULL) {
        // Tokenize the line
        char *source = strtok(line, ",");
        char *target = strtok(NULL, ",");
        char *weight = strtok(NULL, ",");
        strtok(NULL, ","); // Skipping Type

        if (source != NULL && target != NULL && weight != NULL) {
            // Store the indices of source, target, and weight in edgeData array
            int sourceIndex = not_in(source) + 1; // Increment by 1
            int targetIndex = not_in(target) + 1; // Increment by 1

            // Store the data in edgeData array
            edgeData[totalEdges][0] = sourceIndex;
            edgeData[totalEdges][1] = targetIndex;
            edgeData[totalEdges][2] = atoi(weight); // Convert weight to integer
            totalEdges++;
        }
    }

    fclose(file);
    return totalEdges;
}

void calculateShortestPaths(int edgeData[][3], int totalNodes, int totalEdges, int pathCount, int startNode, int endNode) {
    // Check if startNode or endNode is out of bounds
    if (startNode < 1 || startNode > totalNodes || endNode < 1 || endNode > totalNodes) {
        printf("Start node or end node is out of bounds.\n");
        return;
    }

    // Graph initialization
    int graph[totalNodes + 1][totalNodes + 1];
    for (int i = 0; i <= totalNodes; i++) {
        for (int j = 0; j <= totalNodes; j++) {
            graph[i][j] = INT_MAX;
        }
    }

    for (int i = 0; i < totalEdges; i++) {
        // Storing edges
        graph[edgeData[i][0]][edgeData[i][1]] = edgeData[i][2];
    }

    // Array to store distances
    int distances[totalNodes + 1][pathCount];
    for (int i = 1; i <= totalNodes; i++) {
        for (int j = 0; j < pathCount; j++) {
            distances[i][j] = INT_MAX;
        }
    }

    // Dynamically allocate memory for the priority queue
    int **priorityQueue = (int **)malloc((totalNodes * totalEdges) * sizeof(int *));
    for (int i = 0; i < (totalNodes * totalEdges); i++) {
        priorityQueue[i] = (int *)malloc(2 * sizeof(int));
    }

    // Check if memory allocation is successful
    if (priorityQueue == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    // Initialize queueSize
    int queueSize = 0;

    // Enqueue startNode into the priority queue
    priorityQueue[queueSize][0] = 0;
    priorityQueue[queueSize++][1] = startNode;
    distances[startNode][0] = 0;

    // While priority queue has elements
    while (queueSize > 0) {
        // Storing the node value
        int minIndex = 0;
        for (int i = 1; i < queueSize; i++) {
            if (priorityQueue[i][0] < priorityQueue[minIndex][0])
                minIndex = i;
        }
        int currentNode = priorityQueue[minIndex][1];
        int currentDistance = priorityQueue[minIndex][0];
        queueSize--;
        priorityQueue[minIndex][0] = priorityQueue[queueSize][0];
        priorityQueue[minIndex][1] = priorityQueue[queueSize][1];

        if (distances[currentNode][pathCount - 1] < currentDistance)
            continue;

        // Traversing the adjacency list
        for (int i = 1; i <= totalNodes; i++) {
            if (graph[currentNode][i] != INT_MAX) {
                int nextNode = i;
                int edgeWeight = graph[currentNode][i];

                // Checking for the cost
                if (currentDistance + edgeWeight < distances[nextNode][pathCount - 1]) {
                    distances[nextNode][pathCount - 1] = currentDistance + edgeWeight;

                    // Sorting the distances
                    for (int j = pathCount - 1; j > 0; j--) {
                        if (distances[nextNode][j] < distances[nextNode][j - 1]) {
                            int temp = distances[nextNode][j];
                            distances[nextNode][j] = distances[nextNode][j - 1];
                            distances[nextNode][j - 1] = temp;
                        } else {
                            break;
                        }
                    }

                    // Pushing elements to priority queue
                    priorityQueue[queueSize][0] = currentDistance + edgeWeight;
                    priorityQueue[queueSize++][1] = nextNode;
                }
            }
        }
    }

    // Printing K shortest paths
    for (int i = 0; i < pathCount; i++) {
        printf("%d ", distances[endNode][i]);
    }

    // Free the dynamically allocated memory for the priority queue
    for (int i = 0; i < (totalNodes * totalEdges); i++) {
        free(priorityQueue[i]);
    }
    free(priorityQueue);
}

int main() {
    const char *filename = "classic-who.csv";
    int edgeData[MAX_EDGES][3];

    // Read CSV file and construct edgeData array
    int totalEdges = readCSVFile(filename, edgeData);
    if (totalEdges == 0) {
        return 1; // Error reading file
    }

    int pathCount = 10;
    int totalNodes = max(edgeData, totalEdges);
    printf("n = %d\n", totalNodes);
    printf("e = %d\n", totalEdges);

    // Function call
    calculateShortestPaths(edgeData, totalNodes, totalEdges, pathCount, 80, 270);

    return 0;
}