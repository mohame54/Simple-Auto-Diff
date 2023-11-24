#ifndef OPS_BACKWARD_H
#define OPS_BACKWARD_H

// Binary function that takes two elements as arguments like addition.
float add_backward(const float&, const float&, int&);

float sub_backward(const float&, const float&, int&);

float mul_backward(const float&, const float&, int&);

float div_backward(const float&, const float&, int&);

float pow_backward(const float&, const float&, int&);

// Unary functions that takes one element as an argument like exp
float exp_backward(const float&);

float log_backward(const float&);
#endif