#include<iostream>
#include "_backward.h"



VarOpsBack::VarOpsBack(float value=0.0, std::string name=""):
    m_value(value), m_name(name)
{
    // functions that takes two arguments.
    backward_bin_map["+"] = &add_backward;
    backward_bin_map["-"] = &sub_backward;
    backward_bin_map["*"] = &mul_backward;
    backward_bin_map["/"] = &div_backward;
    backward_bin_map["^"] = &pow_backward;

    // functions that takes one argument.
    backward_un_map["exp"] = &exp_backward;
    backward_un_map["log"] = &log_backward;
}

std::string VarOpsBack::get_name() const {
    return m_name;
}

std::string VarOpsBack::get_op() const {
    return m_op;
}

void VarOpsBack::set_name(std::string new_name){
    m_name = new_name;
}

void VarOpsBack::add_op(std::string op_string){
    m_op = op_string;
}

void VarOpsBack::handle_name(VarOpsBack* child, const char* op_name){
    std::string name;
    std::string child_name = child->get_name();
    if (child_name == "") {
        name = op_name;
        name += std::to_string(num_childs);
        child->set_name(name);
    }
}

bool VarOpsBack::is_un(std::string op){
    return (backward_un_map.find(op) != backward_un_map.end());
}

float VarOpsBack::backward_fun(std::string op, const float& left, const float& right, int& child_idx){
    std::unordered_map<std::string, _backward_bin>::iterator it = backward_bin_map.find(op);
    return (*it->second)(left, right, child_idx);       
}
    
float VarOpsBack::backward_fun(std::string op, const float& left){
    std::unordered_map<std::string, _backward_un>::iterator it = backward_un_map.find(op);
    return (*it->second)(left); 
}


