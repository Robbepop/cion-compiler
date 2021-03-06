ToDo list for Cion Compiler

- put source files in associated folders as their include header files
- add error token type and output it in the lexer whenever an error appeared
- make lexer output Tokens with start- and end SourceLocation (adapt Tokens for this change)
- add more specific binary, unary and assign nodes to the AST inherited from AssignExpr, BinaryExpr or UnaryExpr.
- make all include files part of a cion directory.
- add DeclStmnt AST node to make it possible again to have declarations as statements.
- add type component with getter and setter methods to all Expr nodes.
- add new Node subclasses Type and Declaration and adapt existing AST subclasses to them.
- remove ast/node as root AST node class type. (no root type afterwards)
- remove ast/expression_list class and adapt classees depending on it to use vectors of expression instead since expression_lists are no expressions in Cion.
- add DeclStmnt AST node to ASTVisitor.
- add relational and equality operator overloading for SourceLocation.
- rewrite Scanner (Lexer) as its current implementation has huge problems with long structured tokens.
- RecursiveTraverser now traverses Expr's type.
- improve ASTVisitor inheritance hierarchie to make it possible to improve the ASTWritePass so
  that it only requires one function for every AST node which is less error prone.
- create an IntegerExpr and FloatingExpr for all possible IntegerTypes and FloatingTypes
  to optimize memory consumption and to make it possible to save all possible values as
  int64_t does not capture all. the storage argumentation could be invalid due to alignment.
- add IntegerTypeFabric and FloatingTypeFabric in order to create a centralized creation
  of all the new IntegerType and FloatingType types.
- create a forward declaration collection for all AST nodes. (can be included by parser.hpp and i_ast_visitor.hpp)
	- make existing code use the ErrorHandler in order to output
	  and handle errors and warning while lexing or parsing
	- add a new type node AutoDeduceType to indicate that the expression has to be deduced before it is valid.
	- add a set_type method to all AST node types which offer a type() method to change type with semantic passes.
	- provide literal enhancements for int and float literals to also express literals of
	  type uint and all types with specified bit-size. adapt changes to make IntToken and FloatToken
	  take new layout into consideration.
	- add Identifier AST component with a reference to a string and to its entry within the SymbolTable
	- add a TokenStorageManager to store all processed tokens. AST nodes should reference to their tokens.
	- add startLocation() and endLocation() method to all AST nodes.
	- add SourceLocation to all AST nodes for all important locations (e.g. start, end) within an node
	- implement a fully working symbol table for Cion Compiler
	- use forward declarations instead of includes when smart pointers are used.
	- extend the parser to make it possible to parse ref, ptr and [x]-array combined type defines.
	- add sizeof() method to all Type inherited AST nodes.
	- add typeid() method to all Type inherited AST nodes.
	- create semantic check passes:
		1. fill SymbolTable
		2. check declared before defined
		3. set types
		4. check type matching

// Represents an ErrorType or WarningType.
// Can be used to polymorphely store them within a single data structure.
DebugInfoType

// Represents an ErrorType with a name, id and a bool indicating if
// it should be printed or not.
ErrorType : public DebugInfoType
	uint32_t id      // to compare error types
	std::string name // to output names
	bool active      // to access availability (especially for warnings)

// Represents a WarningType with a name, id and a bool indicating if
// it should be printed or not.
WarningType : public DebugInfoType
	uint32_t id      // to compare warning types
	std::string name // to output name
	bool active      // to access availability

// Error- and WarningType collection for the Cion programming language.
// Contains all possible errors and warnings.
// Control over the error output of the program for errors and warnings.
// Control over what errors and warnings are to be output.
CionErrorHandler // singleton managing different error- and warning types
	error_member_{0,...n}   // different const error type members for direct access
	warning_member_{0,...n} // different const warning type members for direct access

// Represents an actual Error or Warning instance.
DebugInfo

// Represents an actual Error with an ErrorType, a TranslationUnit and a SourceLocation
Error : DebugInfo

// Represents an actual Warning with a WarningType, a TranslationUnit and a SourceLocation
Warning : DebugInfo





// Manages access to the current scope, scope stack
// as well as several helper methods and handles the ownership
// of existing scopes.
SymbolTable
	// the root Scope where all global definitions are stored
	Scope global_scope;

	// method to access the global Scope (getter)
	+global_scope();

	// method to access the current Scope (getter/setter)
	+current_scope();

// Represents a scope of e.g. a function, module or even a compound_statement.
// Manages ownership of all of its ScopeEntries.
// Should have fast insertion of ScopeEntries and even faster ScopeEntry lookup.
Scope
	// map from identifiers (std::string) to ScopeEntries.
	// insertion and especially lookup should be fast.
	unordered_map<std::string, ScopeEntry>

	// method to add a new entry to this Scope
	// throws exception if entry already exists.
	+add_entry(std::string s, ScopeEntry entry);

	// method to lookup if this Scope already has got
	// a certain ScopeEntry. This method should work very fast.
	+has_entry(std::string s);

// Represents a ScopeEntry which can be inserted into a scope.
// This is an abstract class. Subclasses of this class stand for different types
// of ScopeEntries.
ScopeEntry



Cion Type System:

builtin-types:
	bool
	utf8, utf16, utf32
	int16, int32, int64
	float16, float32, float64

custom-types:
	<custom-type-list>

qualified-type:
	qualified-type '.' type-qualifier | builtin-type | custom-type

type-qualifier:
	ptr | ref | mutable | [n]



Syntax for Types, Type Qualifiers etc.

Example Syntaxes:

==========================================================================================
Syntax 1 - method-like attributing
==========================================================================================

int                     // an int
int.ptr                 // a pointer to an int
int.ref                 // a reference to an int
int.mut                 // a mutable int
int[10]                 // an array of 10 ints
int.mut.ptr             // a pointer to a mutable int
int.mut.ref             // a reference to a mutable int
int.ptr.mut             // a mutable pointer to an int
int.ref.mut             // error: forbidden: references can't be mutable
int.mut.ref[10]         // an array of 10 references to mutable ints
int.mut.ptr[10]         // an array of 10 pointers to mutable ints
int.mut.ptr.mut         // a mutable pointer to a mutable int
int.ref[10].ptr         // a pointer to an array of 10 references to ints
int.mut.ref[10].ptr     // a pointer to an array of 10 references to mutable ints
int.mut.ref[10].ptr.mut // a mutable pointer to an array of 10 references to mutable ints
int[10][10][10].ptr.ptr // a pointer to a pointer of an array of 10 arrays of arrays of 10 arrays of array of 10 ints
int.mut.ptr.mut.ptr.mut // a mutable pointer to a mutable pointer to a mutable int

==========================================================================================
Syntax 2 - function-like attributing
==========================================================================================

int                          // an int
ptr(int)                     // a pointer to an int
ref(int)                     // a reference to an int
mut(int)                     // a mutable int
int[10]                      // an array of 10 ints
ptr(mut(int))                // a pointer to a mutable int
ref(mut(int))                // a reference to a mutable int
mut(ptr(int))                // a mutable pointer to an int
mut(ref(int))                // error: forbidden: references can't be mutable
ref(mut(int))[10]            // an array of 10 references to mutable ints
ptr(mut(int))[10]            // an array of 10 pointers to mutable ints
mut(ptr(mut(int)))           // a mutable pointer to a mutable int
ptr(ref(int)[10])            // a pointer to an array of 10 references to ints
ptr(ref(mut(int))[10])       // a pointer to an array of 10 references to mutable ints
mut(ptr(ref(mut(int))[10]))  // a mutable pointer to an array of 10 references to mutable ints
ptr(ptr(int[10][10][10]))    // a pointer to a pointer of an array of 10 arrays of arrays of 10 arrays of arrays of 10 ints
mut(ptr(mut(ptr(mut(int))))) // a mutable pointer to a mutable pointer to a mutable int

==========================================================================================
Syntax 3 - paired method- and function-like attributing
==========================================================================================

int                       // an int
ptr(int)                  // a pointer to an int
ref(int)                  // a reference to an int
mut.int                   // a mutable int
int[10]                   // an array of 10 ints
ptr(mut.int)              // a pointer to a mutable int
ref(mut.int)              // a reference to a mutable int
mut.ptr(int)              // a mutable pointer to an int
mut.ref(int)              // error: forbidden: references can't be mutable
ref(mut.int)[10]          // an array of 10 references to mutable ints
ptr(mut.int)[10]          // an array of 10 pointers to mutable ints
mut.ptr(mut.int)          // a mutable pointer to a mutable int
ptr(ref(int)[10])         // a pointer to an array of 10 references to ints
ptr(ref(mut.int)[10])     // a pointer to an array of 10 references to mutable ints
mut.ptr(ref(mut.int)[10]) // a mutable pointer to an array of 10 references to mutable ints
ptr(ptr(int[10][10][10])) // a pointer to a pointer of an array of 10 arrays of arrays of 10 arrays of arrays of 10 ints
mut.ptr(mut.ptr(mut.int)) // a mutable pointer to a mutable pointer to a mutable int

==========================================================================================
Syntax 4 - paired method-like spaced attributing
==========================================================================================

int                       // an int
ptr(int)                  // a pointer to an int
ref(int)                  // a reference to an int
mut int                   // a mutable int
int[10]                   // an array of 10 ints
ptr(mut int)              // a pointer to a mutable int
ref(mut int)              // a reference to a mutable int
mut ptr(int)              // a mutable pointer to an int
mut ref(int)              // error: forbidden: references can't be mutable
ref(mut int)[10]          // an array of 10 references to mutable ints
ptr(mut int)[10]          // an array of 10 pointers to mutable ints
mut ptr(mut int)          // a mutable pointer to a mutable int
ptr(ref(int)[10])         // a pointer to an array of 10 references to ints
ptr(ref(mut int)[10])     // a pointer to an array of 10 references to mutable ints
mut ptr(ref(mut int)[10]) // a mutable pointer to an array of 10 references to mutable ints
ptr(ptr(int[10][10][10])) // a pointer to a pointer of an array of 10 arrays of arrays of 10 arrays of arrays of 10 ints
mut ptr(mut ptr(mut int)) // a mutable pointer to a mutable pointer to a mutable int

==========================================================================================
Syntax 5 - reverse method-like attributing
==========================================================================================

int                     // an int
ptr.int                 // a pointer to an int
ref.int                 // a reference to an int
mut.int                 // a mutable int
int[10]                 // an array of 10 ints
ptr.mut.int             // a pointer to a mutable int
ref.mut.int             // a reference to a mutable int
mut.ptr.int             // a mutable pointer to an int
mut.ref.int             // error: forbidden: references can't be mutable
ref[10].mut.int         // an array of 10 references to mutable ints
ptr[10].mut.int         // an array of 10 pointers to mutable ints
mut.ptr.mut.int         // a mutable pointer to a mutable int
ptr.ref[10].int         // a pointer to an array of 10 references to ints
ptr.ref[10].mut.int     // a pointer to an array of 10 references to mutable ints
mut.ptr.ref[10].mut.int // a mutable pointer to an array of 10 references to mutable ints
ptr.ptr.int[10][10][10] // a pointer to a pointer of an array of 10 arrays of arrays of 10 arrays of array of 10 ints
mut.ptr.mut.ptr.mut.int // a mutable pointer to a mutable pointer to a mutable int

==========================================================================================
Syntax 6 - pointy-paired method-like spaced attributing
==========================================================================================

int                                   // an int
ptr<int>                              // a pointer to an int
ref<int>                              // a reference to an int
mutable int                           // a mutable int
int[10]                               // an array of 10 ints
ptr<mutable int>                      // a pointer to a mutable int
ref<mutable int>                      // a reference to a mutable int
mutable ptr<int>                      // a mutable pointer to an int
mutable ref<int>                      // error: forbidden: references can't be mutable
ref<mutable int>[10]                  // an array of 10 references to mutable ints
ptr<mutable int>[10]                  // an array of 10 pointers to mutable ints
mutable ptr<mutable int>              // a mutable pointer to a mutable int
ptr<ref<int>[10]>                     // a pointer to an array of 10 references to ints
ptr<ref<mutable int>[10]>             // a pointer to an array of 10 references to mutable ints
mutable ptr<ref<mutable int>[10]>     // a mutable pointer to an array of 10 references to mutable ints
ptr<ptr<int[10][10][10]>>             // a pointer to a pointer of an array of 10 arrays of arrays of 10 arrays of arrays of 10 ints
mutable ptr<mutable ptr<mutable int>> // a mutable pointer to a mutable pointer to a mutable int

==========================================================================================
Syntax 7 - pointy-paired method-like attributing
==========================================================================================

int                       // an int
ptr<int>                  // a pointer to an int
ref<int>                  // a reference to an int
mut<int>                  // a mutable int
int[10]                   // an array of 10 ints
ptr.mut<int>              // a pointer to a mutable int
ref.mut<int>              // a reference to a mutable int
mut.ptr<int>              // a mutable pointer to an int
mut.ref<int>              // error: forbidden: references can't be mutable
ref.mut<int>[10]          // an array of 10 references to mutable ints
ptr.mut<int>[10]          // an array of 10 pointers to mutable ints
mut.ptr.mut<int>          // a mutable pointer to a mutable int
ptr<ref<int>[10]>         // a pointer to an array of 10 references to ints
ptr<ref.mut<int>[10]>     // a pointer to an array of 10 references to mutable ints
mut.ptr<ref.mut<int>[10]> // a mutable pointer to an array of 10 references to mutable ints
ptr.ptr<int[10][10][10]>  // a pointer to a pointer of an array of 10 arrays of arrays of 10 arrays of arrays of 10 ints
mut.ptr<mut.ptr<mut<int>> // a mutable pointer to a mutable pointer to a mutable int

========================
Type Specifier Keywords:
========================

Type Modifiers:
================
uref // universal reference
ref  // l-value type reference
rref // r-value type reference
ptr  // pointer

Quantity Modifiers:
===================
[x] // array of x elements

State Modifiers:
================
mut | mutab | mutable | mutable // mutable modifier
imm | immut | immutab | immutable // immutable modifier

Grammar:
========

QualifiedType :=
	  PrimaryType
	| TypeModifier '(' QualifiedType ')'
	| QualifiedType QuantityModifier
	| StateModifier QualifiedType

PrimaryType := BuiltinType | CustomType

BuiltinType :=
	  bool
	        |   utf8   |   utf16  |   utf32
	| int   |   int8   |   int16  |   int32  |   int64 |   int128
	| uint  |  uint8   |  uint16  |  uint32  |  uint64 |  uint128
	| float            | float16  | float32  | float64 | float128

CustomType := identifier | identifier '.' CustomType

TypeModifier := uref | ref | rref | ptr

StateModifier :=
	  mutable
	| immutable
	| const
	| fixed
	| readonly
	| static
	| steady




CompilerPass <abstract>
=======================
	+ visit(*)
-----------------------
Note: This is the base class for all CompilerPasses.
It defines its visit methods to call up in the inheritance
hierarchie of the AST up to the top nodes. This is the
default behaviour of all inheriting CompilerPasses.


RecursiveTraverser : CompilerPass
=================================
	+ visit(*)
	# traverse(*)
---------------------------------
	- CompilerPass pass
---------------------------------
Note: The RecursiveTraverser is capable of fully traversing
the Cion AST. It calls the passed visitor on a node before
it traverses the node.


PrePostTraverser : RecursiveTraverser
=====================================
	+ visit(*) override
-------------------------------------
	- CompilerPass pre, post
-------------------------------------
Note: This is a specialized version of the RecursiveTraverser.
It basically does the same but also features a call to a second
CompilerPass which is called after a node has been traversed.
This might be important for some CompilerPasses to clean up
or reset things.


CompoundPass : CompilerPass
===========================
	+ visit(*)
---------------------------
	- CompilerPass[] passes
---------------------------
Note: This CompilerPass is capable to compounding several
CompilerPasses together which can be executed at the same time
in parallel which might increase the performance of compilation
for some devices with many cores.


CustomPass : CompilerPass
=========================
	+ visit(*)
	? otherMethods(?)
-------------------------
	? otherMembers
-------------------------
Note: This represents a custom CompilerPass which encapsulates
a specific functionality and work on the AST.



Enhancing int and float literals to express their types more explicitely
========================================================================

C++ Type | C++ <cstdint>     || Cion          | Cion Type
---------|-------------------||---------------|-----------
int      | 1337              || 1337, 1337i   | int
int8_t   | N/A               || 1337i8        | int8
int16_t  | N/A               || 1337i16       | int16
int32_t  | 1337              || 1337i32       | int32
int64_t  | 1337L             || 1337i64       | int64
uint     | 1337u             || 1337u         | uint
uint8_t  | N/A               || 1337u8        | uint8
uint16_t | N/A               || 1337u16       | uint16
uint32_t | 1337u             || 1337u32       | uint32
uint64_t | 1337U             || 1337u64       | uint64
float    | 1.337f            || 1.337, 1.337f | float
half (?) | N/A               || 1.337f16      | float16
float    | 1.337f            || 1.337f32      | float32
double   | 1.337, 1.337d     || 1.337f64      | float64
N/A      | N/A               || 1.337f128     | float128


=================================
=================================
Integer Byte Darstellungspräfixe:
=================================

0d | {} => Dezimal
0b      => Binär
0o      => Oktal
0x      => Sedezimal

Beispiele 1:
==========
0d42 | 42 => Dezimal
0b1001101 => Binär
0o7012492 => Oktal
0xF0A912D => Sedezimal

oder:
=====


#d | {} => Dezimal
#b      => Binär
#o      => Oktal
#x      => Sedezimal

Beispiele 2:
==========
#d42 | 42 => Dezimal
#b1001101 => Binär
#o7012492 => Oktal
#xF0A912D => Sedezimal


Complete Integer:
=================
Regex: {|0b|0o|0x}integer{|i{|8|16|32|64}|u{|8|16|32|64}}
Integer: {[0-9A-F_]}+
Usable Regex:
	Decimal:   (0d)?[0-9_]+(i(8|16|32|64)?|u(8|16|32|64)?)
	Binary:    (0b)[0-1_]+(i(8|16|32|64)?|u(8|16|32|64)?)
	Octal:     (0o)[0-7_]+(i(8|16|32|64)?|u(8|16|32|64)?)
	Sedezimal: (0x)[0-9A-F_]+(i(8|16|32|64)?|u(8|16|32|64)?)

Complete Float:
===============


=================================
=================================


With separators between digits:
===============================

Binary Integers:
0b1111_0101_0011_1100_0110
0b1111'0101'0011'1100'0110




Important Regexes:

whitespace: "\\s+"
line_comment: "//[^\\r\\n]*(\\r?\\n)?"
comment: "/\\*([^*]|[\\r\\n]|(\\*+([^*/]|[\\r\\n])))*\\*+/"

identifier: "[_a-zA-Z]\\w*"
integer_literal: "0|([1-9]\\d*)"
float_literal: "(((0|([1-9](\\d)*))\\.(\\d)*|\\.(\\d)+)([eE][+-]?(\\d)+)?)|((0|([1-9](\\d)*))([eE][+-]?(\\d)+))"
char_literal: "'[^']+'"
string_literal: "\\\"([^\"\\\\]|\\\\.)*\\\""




