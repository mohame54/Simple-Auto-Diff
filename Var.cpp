#include <iostream>
#include <vector>
#include <fstream>
#include "_backward.cpp"


namespace diff{
    class Var: public VarOpsBack
    {    
    private:
        std::string make_con_name(float val){
            std::string name = "con";
            name = name + "(" + std::to_string(static_cast<int>(val)) + ")";
            return name;
        }
    public:
        std::vector<Var*> childs; // var childs
        Var(float value=0.0, std::string name="", bool constant=false): VarOpsBack(value, name)
        { 
            this->is_constant = constant;  
        }
        ~Var(){
            for(auto child : this->childs){
                delete child;
            }
        }       
        Var& operator[](int idx){
            return *(this->childs[0]);
        }

        Var& operator+(Var& other){
            Var* res = new Var(m_value + other.m_value);
            res->add_op("+");
            res->add_child(this, "add");
            res->add_child(&other, "add");
            return (*res);   
        }
        Var& operator+(float val){
            Var* con = new Var(val, make_con_name(val), true);
            Var* res = new Var(m_value + val);
            res->add_op("+");
            res->add_child(this, "add");
            res->add_child(con, "add");
            return (*res);
        }

        Var& operator-(Var& other){
            Var* res = new Var(m_value - other.m_value);
            res->add_op("-");
            res->add_child(this, "sub");
            res->add_child(&other, "sub");
            return (*res);
        }
        Var& operator-(float val){
            Var* con = new Var(val, make_con_name(val), true);
            Var* res = new Var(m_value - val);
            res->add_op("-");
            res->add_child(this, "sub");
            res->add_child(con, "sub");
            return (*res);
        }

        Var& operator*(Var& other){
            Var* res = new Var(m_value * other.m_value);
            res->add_op("*");
            res->add_child(this, "mul");
            res->add_child(&other, "mul");
            return (*res);
        }
        
        Var& operator*(float val){
            Var* con = new Var(val, make_con_name(val), true);
            Var* res = new Var(m_value * val);
            res->add_op("*");
            res->add_child(this, "mul");
            res->add_child(con, "mul");
            return (*res);
        }
        Var& operator/(Var& other){
            Var* res = new Var(m_value / other.m_value);
            res->add_op("/");
            res->add_child(this, "div");
            res->add_child(&other, "div");
            return (*res);
        }
        Var& operator/(float val){
            Var* con = new Var(val, make_con_name(val), true);
            Var* res = new Var(m_value / val);
            res->add_op("/");
            res->add_child(this, "div");
            res->add_child(con, "div");
            return (*res);
        }
        Var& pow(Var& other){
            Var* res = new Var(std::pow(m_value, other.m_value));
            res->add_op("^");
            res->add_child(this, "pow");
            res->add_child(&other, "pow");
            return (*res);
        }
        Var& pow(float val){
            Var* con = new Var(val, make_con_name(val), true);
            Var* res = new Var(std::pow(m_value, val));
            res->add_op("^");
            res->add_child(this, "pow");
            res->add_child(con, "pow");
            return (*res);
        }
        Var& exp(){
            Var* res = new Var(std::exp(m_value));
            res->add_op("exp");
            res->add_child(this, "exp");
            return (*res);
        }
        Var& log(){
            Var* res = new Var(std::log(m_value));
            res->add_op("log");
            res->add_child(this, "log");
            return (*res);
        }
        void backward(float gradient=1.0f){
            // update the derivative if only it's not a constant
            grad += (gradient * static_cast<float>(is_constant == false)); 
            if(num_childs == 0 || is_constant){return;}
            std::string op = get_op();
            int i = 0;
            for (auto child : this->childs) {
                float child_gradient = gradient;
                // Compute the gradient based on the operation
                if(is_un(op) && num_childs == 1){ 
                    float left = child->m_value;
                    child_gradient *= backward_fun(op, left); 
                }
                else {
                    float left = childs[0]->m_value;
                    float right = childs[1]->m_value;
                child_gradient *= backward_fun(op, left, right, i);
                }
                i++;
                // Recursively propagate gradients to child nodes
                child->backward(child_gradient);
            }
            
        }
        void add_child(Var* child, const char* op_name){
        this->handle_name(child, op_name);
        this->childs.push_back(child);
        this->num_childs++;
        }
    };

    void intern(Var& root, std::ofstream& file, int n_ops=0){
        int num = root.num_childs;
        static int  n_chs = 0;
        if (num == 0) {return;}
        std::string content = "op" + std::to_string(n_ops);
        std::string root_op = root.get_op();
        file << content + "[label=" +"\"" + root_op +"\"\n" + "\tstyle=\"filled\"\n"+ "\tfillcolor=gold\n" +"\tshape=circle];\n";
        for (auto ch : root.childs){
            std::string ch_name;
            bool has_chs = ch->num_childs != 0;
            if (has_chs){
                n_ops++;
                ch_name = "op" + std::to_string(n_ops);
                file << ch_name + "[label=" +"\"" + ch->get_op() + "\"\n" + "\tstyle=\"filled\"\n"+ "\tfillcolor=gold\n" +"\tshape=circle];\n";
            }else{
                ch_name = "ch" + std::to_string(n_chs);
                file << ch_name + "[label=" +"\"" + ch->get_name() + "\"\n" + "\tstyle=\"filled\"\n"+ "\tfillcolor=pink\n" +"\tshape=circle];\n";
                n_chs++;
            }
            file << content + " -- " + ch_name + ";\n";     
            if(has_chs){intern(*ch, file, n_ops);}
        }
    }
    // To create a dot file for the given root of the graph.
    void graph(Var& root, const char* graph_name="graph"){
        std::string name;
        name = graph_name;
        name = name + ".dot";
        std::ofstream dotFile(name);
        dotFile << "graph G {\n";
        intern(root, dotFile);
        dotFile << "}\n";
        dotFile.close();
    }
    // To delete the graph an all it's associated nodes.
    void delete_graph(Var* root){
        if (root == nullptr){return;}
        for(auto ch : root->childs){
            delete_graph(ch);
        }
        delete root;
    }
}
