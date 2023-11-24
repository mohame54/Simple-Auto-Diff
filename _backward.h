#ifndef _BACKWARD_H
#define _BACKWARD_H

#include<unordered_map>
#include<string>
#include"ops_backward.cpp"

typedef float(*_backward_un)(const float& left);
typedef float(*_backward_bin)(const float&, const float&, int&);

class VarOpsBack
{
private:    
    std::string m_name; // var name
    std::string m_op; // var ops

public:    
    float m_value; // var value
    int num_childs = 0; // var num of children
    float grad = 0.0f; //grad value
    bool is_constant = false; // if the variable is constant

    VarOpsBack(float, std::string);
    
    bool is_un(std::string);

    float backward_fun(std::string, const float&, const float&, int&);
    
    float backward_fun(std::string, const float&);

    std::string get_name() const;
    std::string get_op() const;
    void set_name(std::string);
    void add_op(std::string);
    void handle_name(VarOpsBack*, const char*); 
        
protected:
    std::unordered_map<std::string, _backward_bin> backward_bin_map;
    std::unordered_map<std::string, _backward_un> backward_un_map;    
    
};
#endif