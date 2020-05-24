/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   board_manager.h
 * Author: raphael
 *
 * Created on May 23, 2020, 9:35 AM
 */

#ifndef BOARD_MANAGER_H
#define BOARD_MANAGER_H

#include <unistd.h>
#include "core_simulation.h"
#include "mydevices.h"

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif

class Board_manager{
public:
    void connect_to_Internet(Board& ma_board);
    void connect_to_Bluetooth();
    int compute_mean_pulse_10values(Board& ma_board);
    void send_music_request(Board& ma_board, int mean_pulse);
    void send_music_to_bluetooth_device(Board& ma_board, Bibliotheque& ma_biblio,char* music);
};

#endif /* BOARD_MANAGER_H */

