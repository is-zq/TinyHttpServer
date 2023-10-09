#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<string>

constexpr char IP[24]("192.168.251.124");
constexpr char path[16]("../content");
constexpr int OK = 200;
constexpr int BAD_REQUEST = 400;
constexpr int NOT_FOUND = 404;
constexpr int INTER_ERROR = 500;
constexpr int SERVER_PORT = 80;
