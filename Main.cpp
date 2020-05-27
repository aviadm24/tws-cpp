﻿/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */
/*in linker settings add pthread for external lib thread
*/
#include "StdAfx.h"

#include <stdio.h>
#include <stdlib.h>

#include <chrono>
#include <thread>

#include "TestCppClient.h"
//#include "Aviad.h"
#include <fstream>

const unsigned MAX_ATTEMPTS = 50;
const unsigned SLEEP_TIME = 10;

std::string stock_name;
int stock_amount;

void make_file(){
    std::ofstream MyFile("data.txt");
    MyFile << "QQQ" << std::endl << 200;
    MyFile.close();
}

int readFile(){
    std::ifstream fin("data.txt");
    std::string name;
    int amount;
    fin >> name;
    printf("stockName: %s\n", name);
    printf("stockAmount: %s\n", amount);
//    while (fin >> name >> amount)
//    {
//        stock_name = name;
//        stock_amount = amount;
//        printf("stockName: %s\n", stock_name);
//        printf("stockAmount: %s\n", stock_amount);
//        //std::cout << stockName << stockAmount << std::endl;
//    }

    fin.close();
    return amount;
}
/* IMPORTANT: always use your paper trading account. The code below will submit orders as part of the demonstration. */
/* IB will not be responsible for accidental executions on your live account. */
/* Any stock or option symbols displayed are for illustrative purposes only and are not intended to portray a recommendation. */
/* Before contacting our API support team please refer to the available documentation. */
int main(int argc, char** argv)
{
	const char* host = argc > 1 ? argv[1] : "";
	int port = argc > 2 ? atoi(argv[2]) : 0;
	if (port <= 0)
		port = 7497;
	const char* connectOptions = argc > 3 ? argv[3] : "";
	int clientId = 0;

	unsigned attempt = 0;
	printf( "Start of C++ Socket Client Test %u\n", attempt);
    //make_file();
    //readFile();
	for (;;) {
		++attempt;
		printf( "Attempt %u of %u\n", attempt, MAX_ATTEMPTS);

		TestCppClient client;

		// Run time error will occur (here) if TestCppClient.exe is compiled in debug mode but TwsSocketClient.dll is compiled in Release mode
		// TwsSocketClient.dll (in Release Mode) is copied by API installer into SysWOW64 folder within Windows directory

		if( connectOptions) {
			client.setConnectOptions( connectOptions);
		}

		client.connect( host, port, clientId);

		while( client.isConnected()) {

			client.processMessages();
		}
		if( attempt >= MAX_ATTEMPTS) {
			break;
		}

		printf( "Sleeping %u seconds before next attempt\n", SLEEP_TIME);
		std::this_thread::sleep_for(std::chrono::seconds(SLEEP_TIME));
	}

	printf ( "End of C++ Socket Client Test\n");
}

