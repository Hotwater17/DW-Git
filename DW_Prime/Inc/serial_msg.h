/*
 * @file	serial_msg.h
 * @brief	Contains serial interface message strings.
 * @author	Micha³ Gorywoda
 */


#ifndef SERIAL_MSG_H_
#define SERIAL_MSG_H_
#define SERIAL_TIMEOUT 50U

const uint8_t msgInitError[] = {"DW1000 Initialization ERROR!"};
const uint8_t msgInitOk[] = {"DW1000 Initialization ok"};
const uint8_t msgWaitRx[] = {"Polling for message"};
const uint8_t msgRxOk[] = {"Message reception OK"};

#endif
