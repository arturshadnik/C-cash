/**
 *  BlockChain ADT : Test Drive
 *
 *  COMP220: Assignment 3
 *  Author:  Braeden Norman and Artur Shadnik
 *  Date:    2018/03/22
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>

#include "trnslist.h"
#include "puzzle.h"
#include "block.h"
#include "blockchain.h"



int main(){
    int i;
    BlockChain chain = bcNew();
    TransactionList Trans = tlistCreate();
    for (i=0; i<5; i++) {
        tlistAppend(&Trans, "Post Malone", (i+3)*2+99.0/(i+1), "Drake");
    }
    printf("Length of BlockChain is : %d \n", bcLen(chain));
    Block_t* block = blkCreate(Trans, 2, NULL_NONCE );
    Puzzle_t puzzle = blkCreatePuzzle(*block, chain.tail->hash);
    block->proof_of_work = puzzleMine(puzzle);
    printf("Block 1 POW: %ld\n", block->proof_of_work.i_nonce);
    bcAppend(&chain, block);
    TransactionList Trans2 = tlistCreate();
    for (i=0; i<7; i++) {
        tlistAppend(&Trans2, "Snoop Dogg", (i+4)*2+21.0/(i+1), "Travis Scott");
    }
    block = blkCreate(Trans2, 2, NULL_NONCE );
    puzzle = blkCreatePuzzle(*block, chain.tail->hash);
    block->proof_of_work = puzzleMine(puzzle);
    bcAppend(&chain, block);
    TransactionList Trans3 = tlistCreate();
    for (i=0; i<3; i++) {
        tlistAppend(&Trans3, "Desiigner", (i+2)*5+24.0/(i+7), "Dr.Dre");
    }
    block = blkCreate(Trans3, 2, NULL_NONCE );
    puzzle = blkCreatePuzzle(*block, chain.tail->hash);
    block->proof_of_work = puzzleMine(puzzle);
    bcAppend(&chain, block);
    bcPrint(chain);
    assert(bcIsValid(chain));
    printf("Block Chain is Valid\n");
    printf("Printing Tail of the Block Chain\n");
    tlistPrint(bcTail(chain)->transactions);
    printf("Length after appending is : %d \n", bcLen(chain));
    bcDelete(&chain);
    printf("Length after deleting is : %d \n", bcLen(chain));
}