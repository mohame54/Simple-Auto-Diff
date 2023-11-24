#include<cmath>


//////////////////// Backward Functions ///////////////////////////
// define every backward function scheme
// left operand, right operand, and idx to identify
// which child are we taking the derivative for left is 0 and right is 1.
// Binary function that takes two elements as arguments like addition.
float add_backward(const float& left, const float& right, int& child_idx){ return 1.0f;}

float sub_backward(const float& left, const float& right, int& child_idx){
    if(child_idx == 1){return -1.0f;}
    return 1.0f;
}

float mul_backward(const float& left, const float& right, int& child_idx){
    if (child_idx == 0){return right;}
    return left;
}

float div_backward(const float& left, const float& right, int& child_idx){
    // Gradient for power
    // derivative l.h.s 1/ denominator
    // derivative r.h.s - numerator / (denominator)**2
    if (child_idx == 0){
        return  1.0 / right;
    }else{
        return  -left / (right * right); 
    } 
}

float pow_backward(const float& left, const float& right, int& child_idx){
    // Gradient for power
    // derivative w.r.t. base is exponent * (base)^(exponent-1)
    // derivative w.r.t. exponent is (base^exponent) * log(base)
    if(child_idx == 0){
        return std::pow(left, right - 1) * right;
    }else{
        return std::log(left) * std::pow(left, right);
    }
}

// Unary functions that takes one element as an argument like exp
float exp_backward(const float& left){
    return std::exp(left);
}

float log_backward(const float& left){
    return 1.0f / left;
}