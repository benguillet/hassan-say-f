/* 
 * File:   trains.h
 * Author: ludovic
 *
 * Created on 8 décembre 2011, 18:36
 */

#ifndef TRAIN_H
#define	TRAIN_H

void* TGV_thread_fn(void* tgv);
void* GL_thread_fn(void* ter);
void* M_thread_fn(void* mar);

#endif	/* TRAIN_H */

