// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define MAXLINE 1024
#define L_U32_DEFAULT_IP_ST_LEN            32U
#define L_ST_DEFAULT_IP                    "127.0.0.1"
// Driver code
int main(int argc, char* argv[]) {
	int port = 0;
	int one = 1;
	struct sockaddr_in servaddr;
	struct sockaddr_in cliaddr;
	char udp_addr[L_U32_DEFAULT_IP_ST_LEN] = L_ST_DEFAULT_IP;
	int sockfd;
	char buffer[MAXLINE];
	char argos[sizeof(argv[1])];

	if(argc > 1){
		strncpy(argos, argv[1], sizeof(argos));
		port = strtol(argv[1], &argos, 10);
	}
	if(argc > 2){
		strncpy(udp_addr, argv[2], sizeof(udp_addr));
		udp_addr[sizeof(udp_addr) - 1] = '\0';
	}

	uint8_t msg_cam[] = {1,2,0,0,7,169,62,6,64,89,205,226,247,109,137,95,112,32,0,0,0,0,48,212,30,0,0,15,223,255,254,130,240,141,0,3,255,5,255,248,0,0,13,255,255,127,255,216,206,63,255,128};
	uint8_t msg_denm[] = {1,1,0,0,7,169,225,128,0,3,212,128,0,145,49,101,152,82,68,76,89,102,20,147,94,62,66,70,180,205,166,223,255,255,254,17,219,186,31,0,150,3,230,10,0,48,0,0,0,0};
	uint32_t msg_mcm[] = {3841,11522,3919885575,3528026880,0,2693136640,33540,4194304,0,15074976,1078132768,0,4294967295,0,3965523668,32765,1269236432,32655,1271399680,32655,0,0,0,0,0,0,0,0,1271288000,32655,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1269202944,32655,1363130091,14025,2,0,14,2147483648,0,0,0,0,0,0,0,0,0,0,0,0,2,0,14,2147483648,0,0,0,0,0,0,0,0,0,0,0,0,1271736808,32655,0,0,0,0,0,0,1271282832,32655,335544324,0,1271338016,32655,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,896,896,896,896,896,896,896,896,896,896,896,896,896,896,896,896,896,896,896,896,896,896,896,896,896,896,0,0,256,64,4294967295,0,1271398400,32655,72,0,1271345502,32655,1271376928,100,594952192,1978679514,4294967295,0,1271283924,32655,0,0,64,0,8388608,0,15775231,0,194,0,3965524551,32765,3965524550,32765,1176617389,21942,1271251688,32655,1176617312,21942,0,0,1176232800,21942};
	int my_len;


	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = inet_addr(udp_addr);
	servaddr.sin_port = htons(port);
	printf("\nPort %d in socket\n", port);
	int len;
	cliaddr.sin_family = AF_INET; // IPv4
	cliaddr.sin_addr.s_addr = INADDR_ANY;
	cliaddr.sin_port = htons(port);

	// Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&cliaddr,
			sizeof(cliaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	len = sizeof(servaddr); //len is value/result
	int cont = 0;
	int n;
while(1){
	printf("----------------------------------------------------------------\n");
	
	printf("\n");
	if(port==2001){
		printf("Sending CAM\n");
		my_len = sizeof(msg_cam);
		printf("Message to send: %d\n", sizeof(msg_cam));
		for (int i = 0; i < my_len; i++){
				printf("%02hX", msg_cam[i]);
		}
		printf("\n");
		n= sendto(sockfd, (const uint8_t *)msg_cam, sizeof(msg_cam),
		MSG_CONFIRM, (const struct sockaddr *) &servaddr,sizeof(servaddr));
	}
	if(port==2002){
		printf("Sending DENM\n");
		my_len = sizeof(msg_denm);
		printf("Message to send: %d\n", sizeof(msg_denm));
		for (int i = 0; i < my_len; i++){
				printf("%02hX", msg_denm[i]);
		}
		printf("\n");
		n= sendto(sockfd, (const uint8_t *)msg_denm, sizeof(msg_denm),
		MSG_CONFIRM, (const struct sockaddr *) &servaddr,sizeof(servaddr));
	}
	if(port==2018){
		printf("Sending MCM\n");
		my_len = sizeof(msg_mcm);
		printf("Message to send: %d\n", sizeof(msg_mcm));
		for (int i = 0; i < my_len; i++){
				printf("%02hX", msg_mcm[i]);
		}
		printf("\n");
		n= sendto(sockfd, (const uint8_t *)msg_mcm, sizeof(msg_mcm),
		MSG_CONFIRM, (const struct sockaddr *) &servaddr,sizeof(servaddr));
	}
	printf("Message %d sent. Number of bytes= %d.\n", cont, n);
	cont++;
	printf("Message waiting\n");
	n = recvfrom(sockfd, (uint8_t *)buffer, MAXLINE,
				MSG_WAITALL, ( struct sockaddr *) &servaddr,
				&len);
	buffer[n] = '\0';
	printf("Message received: %d\n", n);
	for (int i = 0; i < n; i++){
				printf("%02hX", buffer[i]);
			}
	printf("\n");
	printf("----------------------------------------------------------------\n");
	sleep(3);
}
	return 0;
}
