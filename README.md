# Simple-Auto-Diff
**Simple Scaler Automatic Differentiation engine written in C++**

## Hyberpolic Sinh function
![Hyberpolic Sinh function](https://github.com/mohame54/Simple-Auto-Diff/blob/main/imgs/sinh.png)



##[Quadratic function
![Quadratic function](https://github.com/mohame54/Simple-Auto-Diff/blob/main/imgs/quad.png)

## Table of Contents

- [Overview](#overview)
- [Dependencies](#dependencies)
- [Building and Running](#building-and-running)
- [Usage](#usage)

## Overview

Simple but effictive automatic differtiation for scaler values it support many basic functions including unary which accept one input like **exp** and binary which accepts two inputs like addition **+**.

## Dependencies

- C++ compiler (e.g., g++)
- Graphizy (for plotting the function graph).


## Building and Running

You can integrate auto diff with ease and make your own code then run it.  

```bash
# Example build command
g++ -o your_executable source_file.cpp

# Example run command
./your_executable
```

## Usage

You can implement any function and take it's derivatives to it's inputs also you can visualize your function as graph of operations and inputs, but you have to follow the following limitations.

- You should always use diff::Var type in your inputs and outputs.
- You should also pass the inputs to your function by reference.
- You should look into the provided functions any function outside the provided will not work. 
- Once you create a graph and you don't want to use it anymore you should use diff::delete_graph.

```cpp
#include <iostream>
#include "Var.cpp"

//quadratic function
diff::Var& quad(diff::Var& v){
   
    return v.pow(2.0f) + v * 4.0f + 4.0f; // f = v^2 + 4v + 4
}
// Sinh function
diff::Var& sinh(diff::Var& v){
    
    return (v.exp() - (v * -1.0f).exp()) / 2.0f;
}

diff::Var& func(const diff::Var& x, const diff::Var& y){
    return x.pow(2.0f) - y.pow(2.0f);
}

int main() {
    // Example usage of the Var class
    Var a = 0.0f;
    // Perform operations on Var instances...
    Var res = sinh(a);
    // perform the backward pass
    res.backward();
    // print the derivative
    std::cout<<"dv"<< a.grad<< std::endl;
    // visulaize the graph
    diff::graph(res, dotfilename);
    return 0;
}
```
run the following script.
```bash
dot -Tpng dotfilename.dot -o img.png 
```

