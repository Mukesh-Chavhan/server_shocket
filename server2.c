
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>

#define PORT 8080
#define ROWS 3
#define COLS 3

int main() {
    int server_socket, client_socket1, client_socket2, client_socket3;
   
    struct sockaddr_in server_addr, client_addr1, client_addr2, client_addr3;
   
    int matrixmain[ROWS][COLS] = {{1, 2, 5}, {4, 1, 6}, {7, 2, 9}};
   
    int matrix[ROWS][COLS] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
   
    int row1[COLS], row2[COLS], result1[COLS], result2[COLS], result3[COLS];
   
    time_t t1;
   
    time_t start, end;
    start = time(NULL);

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Initialize server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the specified port
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, 2) == -1) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }


    printf("Server listening on port %d...\n", PORT);

//---------------------------------------------------------------------------------------------------------------------

//CONNECTION ESTABLISHED WITH EVERY CLIENT OR NOT

    // Accept connection from the first client
    socklen_t client_addr_len1 = sizeof(client_addr1);
    client_socket1 = accept(server_socket, (struct sockaddr*)&client_addr1, &client_addr_len1);
    if (client_socket1 == -1) {
        perror("Accept failed for client 1");
        exit(EXIT_FAILURE);
    }

    printf("Client 1 connected\n");

//----------------------------------------------------------------------------------------------------------------------
   
    // Accept connection from the second client
    socklen_t client_addr_len2 = sizeof(client_addr2);
    client_socket2 = accept(server_socket, (struct sockaddr*)&client_addr2, &client_addr_len2);
    if (client_socket2 == -1) {
        perror("Accept failed for client 2");
        exit(EXIT_FAILURE);
    }

    printf("Client 2 connected\n");
//-------------------------------------------------------------------------------------------------------------------------


    // Accept connection from the third client
    socklen_t client_addr_len3 = sizeof(client_addr3);
    client_socket3 = accept(server_socket, (struct sockaddr*)&client_addr3, &client_addr_len3);
    if (client_socket3 == -1) {
        perror("Accept failed for client 3");
        exit(EXIT_FAILURE);
    }
   
    printf("Client 3 connected\n");



//----------------------------------------------------------------------------------------------------

//SENDING MAIN MATRIX AND EACH ROW OF SECOND MATRIX TO EACH CLIENT

    // Send the first row to the first client
    send(client_socket1, matrixmain, sizeof(matrixmain), 0);
    send(client_socket1, matrix[0], sizeof(matrix[0]), 0);
    //printf(matrix[0]);
       
//----------------------------------------------------------------------------------------------------
    // Send the second row to the second client
    send(client_socket2, matrixmain, sizeof(matrixmain), 0);
    send(client_socket2, matrix[1], sizeof(matrix[1]), 0);
    //printf(matrix[1]);
       
    //------------------------------------------------------------------------------------------------
   
    // Send the third row to the third client
    send(client_socket3, matrixmain, sizeof(matrixmain), 0);
    send(client_socket3, matrix[2], sizeof(matrix[2]), 0);
    //printf(matrix[2]);
       
   
//-----------------------------------------------------------------------------------------------------------------

//RECIEVING MULTIPLICATION FROM EVERY CLIENT  
     
    // Receive the results from all clients
    recv(client_socket1, result1, sizeof(result1), 0);
    recv(client_socket2, result2, sizeof(result2), 0);
    recv(client_socket3, result3, sizeof(result3), 0);
   
 
   
   
//--------------------------------------------------------------------------------------------------------------------

    // Display the received results
    printf("Result received from client 1: ");
    for (int i = 0; i < COLS; i++) {
        printf("%d ", result1[i]);
    }
    printf("\n");

    printf("Result received from client 2: ");
    for (int i = 0; i < COLS; i++) {
        printf("%d ", result2[i]);
    }
    printf("\n");
   
    printf("Result received from client 3: ");
    for (int i = 0; i < COLS; i++) {
        printf("%d ", result3[i]);
    }
    printf("\n");
   
   
    printf("\n");
   
   
   
    //--------------------------------------------------------------------------
   
    //FOR PRINTING MATRIX
   
    for (int i = 0; i < COLS; i++) {
        printf("%d ", result1[i]);
    }
    printf("\n");
    for (int i = 0; i < COLS; i++) {
        printf("%d ", result2[i]);
    }
    printf("\n");
    for (int i = 0; i < COLS; i++) {
        printf("%d ", result3[i]);
    }
    printf("\n");
 
//--------------------------------------------------------------------------------------------
 
    // Close sockets
    close(client_socket1);
    close(client_socket2);
    close(client_socket3);
    close(server_socket);
   
    end = time(NULL);
    printf("Time taken : %.2f seconds.\n", difftime(end, start));

    return 0;
}











/*


{{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}}
*/
