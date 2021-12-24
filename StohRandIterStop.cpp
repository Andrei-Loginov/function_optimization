#include "StohRandIterStop.h"

StohRandIterStop::StohRandIterStop(){

}

StohRandIterStop::StohRandIterStop(size_t max_iter, size_t max_after_improve) : StopCriterion(max_iter),
                                                                                max_iter_after_improvment(max_after_improve){
}

StohRandIterStop::StohRandIterStop(const StohRandIterStop& other) : StopCriterion(other),
                                                                    max_iter_after_improvment(other.max_iter_after_improvment){

}

StohRandIterStop::StohRandIterStop(StohRandIterStop&& other) : StopCriterion(other),
                                                               max_iter_after_improvment(other.max_iter_after_improvment){
    other.max_iter_after_improvment = 0;
}

bool StohRandIterStop::criterion(MethodStatus *status){

}
