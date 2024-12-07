Currently working on the project

## Computorv2

### Introduction

This project focuses on developing a powerful mathematical interpreter that can handle complex computations.

Computorv2 combines versatility and precision to process a wide range of mathematical constructs.

It allows users to solve equations, manipulate variables, and perform matrix operations effortlessly within an intuitive command-line interface.

<br>

### Project description

Computor v2 is an instruction-based mathematical interpreter that facilitates advanced computations in a structured environment.

It is designed to handle a various mathematical types and operations while maintaining user-friendly interaction.

The interpreter supports the following features:

- variable assignments: rational numbers, complex numbers, matrices, and polynomial functions
- mathematical operations: basic arithmetic, matrix multiplication, powers, and modulos
- equation resolution Solve polynomial equations up to degree 2 with real or complex solutions
- function handling: define, evaluate, and compose single-variable functions.

<br>

### Mandatory Part

the primary goal is to develop a fully functional mathematical interpreter capable of:

- managing diverse mathematical types and operations
- resolving equations with accuracy and efficiency
- handling variable assignments and reassignments

the interpreter must be robust, ensuring correct results and preventing errors during user interaction.

<br>

### Parsing with the class ReadLine

To streamline the parsing process and enhance input handling, computor v2 leverages a custom-built utility class called `ReadLine`.

This class was specifically developed to handle user input efficiently, ensuring a smoother and more intuitive parsing.

Click [here](https://github.com/sleepychloe/ReadLine) for more details about the ReadLine class and its implementation

<br>


### Abstract Syntax Tree(AST): A Core Data Structure

To simplfy the process of parsing and evaluating mathematical expressions, computor v2 employs an Abstract Syntax Tree (AST) as its core data structure.

The AST is designed to handle complex expressions efficiently while maintaining a clear, hierarchical representation of operations and operands.



#### What is Abstract Syntax Tree?

An Abstract Syntax Tree (AST) is a hierarchical representation of the structure of code or expressions.

Each node in the tree represents a construct occurring in the input, such as an operator, operand, or function call.



#### Why Use an AST?

1. hierarchical representation
	- facilitates logical evaluation, respecting operator precedence and associativity
2. operator precedence and associativity
	- ensures correct evaluation order of operations(higher precedence -> lower precedence)
3. flexibility in traversal
	- allows various traversal orders (pre-order, in-order, post-order) for different use cases
4. simplified evaluation
	- recursive node processing makes expression evaluation straightforward
5. extensibility
	- easily adaptable to support additional features
6. debuggability
	- visualizing the tree structure simplifies debugging and understanding



#### How the AST works in this code

- class ASTNode: Represents a node in the tree
- class AST: responsible for building and processing the AST

1. tokenizing the input
	- reaks input into sub-expressions, operators (+, -, *, /, %, **), and operands (numbers, variables, etc.)
2. handling parentheses
	- recursively processes sub-expressions within parentheses
3. operator precedence
	- ensures correct evaluation order using precedence rules
4. build subtree
	- combines nodes into subtrees based on operators and operands
5. combining subtree
	- constructs the complete AST by integrating all subtrees

this process provides a robust framework for evaluating mathematical and logical expressions.

<br>


### `std::unique_ptr` and memory management in ASTNode

#### What is `std::unique_ptr`?

`std::unique_ptr` is a modern C++ smart pointer that ensures exclusive ownership of a dynamically allocated resource.

It automatically deallocates the resource when it goes out of scope, eliminating the need for manual memory management.



#### Key Characteristics

- exclusive ownership
	+ a single std::unique_ptr owns a resource
- move-only semantics
	+ ownership can be transferred using std::move
- automatic cleanup
	+ automatically calls delete when destroyed
- custom deleters
	+ supports user-defined cleanup logic



#### Advantages of `std::unique_ptr`

- safety: prevents memory leaks and double-deletion issues
- simplicity: reduces complexity in destructors and copy constructors
- modern practice: encourages clear ownership semantics
- performance: negligible runtime overhead compared to raw pointers



#### Code1: manual memory management with raw pointers

```
class ASTNode
{
public:
	ASTNode(std::string term)
		: type(NodeType::TERM), value(term), left(nullptr), right(nullptr) {  };
	ASTNode(std::string op, ASTNode *left, ASTNode *right)
		: type(NodeType::OPERATOR), value(op)
	{
		this->left = new ASTNode(*left);
		this->right = new ASTNode(*right);
	};
	ASTNode(const ASTNode& astnode) { *this = astnode; };
	ASTNode& operator=(const ASTNode& astnode)
	{
		if (this == &astnode)
			return (*this);
		this->type = astnode.type;
		this->value = astnode.value;
		this->left = (astnode.left == nullptr) ? nullptr : new ASTNode(*astnode.left);
		this->right = (astnode.right == nullptr) ? nullptr : new ASTNode(*astnode.right);
	};
	~ASTNode()
	{
		delete this->left;
		delete this->right;
	};

	NodeType			type;
	std::string			value;
	ASTNode*			left;
	ASTNode*			right;

private:
	ASTNode();
};

```

- advantages
	+ familiar for developers accustomed to raw pointers
	+ full control over allocation and deallocation

- disadvantages
	+ prone to errors (memory leaks, dangling pointers)
	+ requires explicit delete calls for cleanup
	+ hard to maintain in larger, complex codebases



#### Code2: using `std::unique_ptr`

```
#include <memory>

class ASTNode
{
public:
	ASTNode(std::string term)
		: type(NodeType::TERM), value(term), left(nullptr), right(nullptr) {  };
	ASTNode(std::string op, std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right)
		:type(NodeType::OPERATOR), value(op), left(std::move(left)), right(std::move(right)) {  };
	ASTNode(const ASTNode& astnode) { *this = astnode; };
	ASTNode& operator=(const ASTNode& astnode)
	{
		if (this == &astnode)
			return (*this);
		this->type = astnode.type;
		this->value = astnode.value;
		this->left = (astnode.left == nullptr) ? nullptr : std::make_unique<ASTNode>(*astnode.left);
		this->right = (astnode.right == nullptr) ? nullptr: std::make_unique<ASTNode>(*astnode.right);
	};
	~ASTNode() {  };

	NodeType			type;
	std::string			value;
	std::unique_ptr<ASTNode>	left;
	std::unique_ptr<ASTNode>	right;

private:
	ASTNode();
};

```

- advantages
	+ automatic memory management: simplifies destructors and eliminates leaks
	+ exception safety: resources are cleaned up even if exceptions occur
	+ clarity: ownership semantics are explicit and clear

- disadvantages
	+ move-only semantics: requires refactoring to use `std::move` for ownership transfers
