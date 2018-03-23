/**
 *  BlockChain ADT : private implementation / algorithms
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

/***********************
 * BLOCKCHAIN private implementation details
 ***********************/
const int DEFAULT_DIFFICULTY = 2;              // Default difficulty for hashing puzzles, increase to make mining harder


/*
 * Constructor - return a new, empty BlockChain 
 * POST:  bcLen(chain) == 0
 */
BlockChain bcNew( ){
    const char* dummy_hash = "12345678901234567890";
    Block_t* dummy = blkCreate(tlistCreate(), DEFAULT_DIFFICULTY, NULL_NONCE);
    strcpy(dummy->hash, dummy_hash);
    BlockChain chain = {dummy, dummy};
    return chain;
}

/*
 * Destructor - remove all data and free all memory associated with the chain 
 * POST: bcLen(chain) == 0
 */
void bcDelete( BlockChain *chain ){
    while( chain->head != chain->tail){
        chain->tail = chain->tail->prev;
        free(chain->tail->next);
        chain->tail->next = NULL;
    }
    
}

/*
 * Print a text representation of this chain on STDOUT
 */
void bcPrint( const BlockChain chain ){
    int i;
    Block_t* cur = chain.head->next;
    while(cur!= NULL){
        printf("Block #%d:\n", cur->id);
        printHash(cur->hash);
        tlistPrint(cur->transactions);
        cur = cur->next;

    }
}

/*
 * Return the number of Blocks in the chain
 */
int bcLen( const BlockChain chain ){
    int len = 0;
    Block_t* cur = chain.head;
    while(cur->next != NULL){
        len++;
        cur = cur->next;
    }
    return len;
}

/*
 *  Return true iff blkIsValid(block) for every block in the chain
 */

bool bcIsValid(const BlockChain chain){
    Block_t* cur = chain.head->next;
    while(cur != NULL){
       if(blkIsValid(*cur) == true){
           cur = cur->next;
       }else{
           return 0;
       }
    }
    return 1;
}



/*
 * Return a pointer to the chain's tail Block
 */
Block_t* bcTail(const BlockChain chain){
    return chain.tail;
}

/*
 * Append the given block to the chain 
 *    iff blkValidates(new_block, bcTail->hash, new_block->proof_of_work)
 * POST: bcTail(*chain) == new_block && blkIsValid(*new_block)
 */
void bcAppend( BlockChain *chain, Block_t* new_block ){
    
    if (blkChainTo(chain->tail, new_block)) {
        chain->tail = new_block;
    }
    else
        assert(false);
    assert(blkIsValid(*new_block)); 
}
 