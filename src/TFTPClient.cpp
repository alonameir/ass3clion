//
// Created by alonam on 1/17/17.
//

#include <iostream>
#include <connectionHandler.h>
#include <boost/thread.hpp>
#include <boost/core/ref.hpp>
#include <KeyboardTask.h>
#include <SocketTask.h>

using namespace std;

int main (int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
        return -1;
    }
    std::string host = argv[1];
    short port = atoi(argv[2]);

    ConnectionHandler connectionHandler(host, port);
    if (!connectionHandler.connect()) {
        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
        return 1;
    }

    cout << "I'm Connected" << endl;

    boost::mutex mutex;
    KeyboardTask task1(connectionHandler, &mutex);
    SocketTask task2(connectionHandler, &mutex);


    boost::thread th1(boost::bind(&KeyboardTask::run, &task1));

//    boost::thread th2(boost::bind(&SocketTask::run, &task2));
    th1.join();
//    th2.join();

    return 0;
}