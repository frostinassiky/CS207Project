//
// Created by Mengmeng Xu on 11/15/17.
//

#ifndef TANKCRAFT_STATEID_H
#define TANKCRAFT_STATEID_H
//assign each state a integer
namespace StatesID {
    enum ID {
        None,
        Menu,
        Game,
        Pause,
        Confirm,
        TODO,
        Player1Win,
        Player2Win,
    };
}


#endif //TANKCRAFT_STATEID_H
