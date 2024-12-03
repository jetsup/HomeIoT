#pragma once

#include <Arduino.h>
#include <Wire.h>

#include <HomeAppliance.hpp>
#include <HomeConfig.hpp>
#include <HomeDHT.hpp>
#include <HomeDisplay.hpp>
#include <HomeNetworking.hpp>
#include <HomeRTC.hpp>
#include <HomeServer.hpp>

extern TaskHandle_t mainTaskHandle;
extern TaskHandle_t monitorTaskHandle;

extern HomeDHT dht;
extern HomeRTC *rtc;
extern HomeNetworking *networking;
extern HomeDisplay *display;
extern HomeServer *server;
extern HomeApplianceConfiguration *applianceConfig;
extern std::vector<HomeAppliance *> appliances;

extern bool SET_DATE_TIME;

/**
 * @brief Main task looper. The main task looper is responsible for all tasks
 * that are not time sensitive.
 * @param parameter void pointer to the parameter passed to the task
 */
void mainTaskLooper(void *parameter);

/**
 * @brief Monitor task looper. The monitor task looper is responsible for all
 * tasks that are time sensitive.
 * @param parameter void pointer to the parameter passed to the task
 */
void monitorTaskLooper(void *parameter);

/**
 * @brief Initialize the file system and create all files if they are not
 * present
 * @param formatFS boolean flag to format the file system during initialization
 */
void initFileSystem(bool formatFS=false);
