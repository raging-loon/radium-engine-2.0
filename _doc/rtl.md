# Radium Template Library

## Table of Contents
1. `rtl::copy_on_write`
2. `rtl::basic_string`
3. `rtl::array`
4. `rtl::unordered_map`
5. `rtl::iterator`


### rtl::copy_on_write

This is a central component of the template library. *Most* data structures found here rely on COW.
This allows data structures to be passed around, and only copied when modified. Ideally, this will happen implicitly, 
behind the scenes. 

COW is a fairly simple data structure. It consists of:
1. A reference count
2. An object size
3. A raw array of objects

This information is stored all together in a single heap allocation.
```
0           32           64    
┌────────────┬───────────┬──────┐
│  Ref Count │ Data Size │ Data │    
└────────────┴───────────┴──────┘
```

Any functions that would modify the data (i.e, any non-const functions), will call `copy_on_write<T>::__copy_on_write`.

The copy-constructor/copy-assignment operators will increase the reference count, while the destructors will decrease it
If the destructor detects that the ref-count is 0 one of two things will happen:
1. If the `T` is `std::__is_trivially_destructable`, the destructor will loop through the array and call the destructores of its objects.
1. Other wise it will simply free the memory


### rtl::basic_string

This class relies on a `copy_on_write` object.

This is basically just a clone of `std::string`.

### rtl::array

This also relies on a `copy_on_write` object.

### rtl::unordered_map

This one was really fun to build.

This is the basic idea of a hash table:
1. Use non-secure hashing algorithms to generate a 32-64 bit ID for an object `T`
2. Use the total size of the hash table to find and index based on the hash
	- This typically involves finding the remainder e.g. 

	        size_t index = hash_function(object) % totalsize;
3. Store the object or around that index.
4. During a look-up, hash the object, find it's desired index, and look around for it.


### rtl::generic_iterator and rtl::generic_const_iterator

These are generic iterators that should be used (and perhaps aliased) in your class.

This takes two parameters, the type that is iterated over, and `meminc`.

If `meminc` is set to true, the iterator will increment a pointer to your data.

Otherwise, it will operate on your data as if it is a doubly linked list. Thus, your data MUST provide a `next` and `prev` function.

`meminc` is on by default.

### rtl::function

This is a type-erased functor object.
It supports
1. free-functions
2. Lambdas
3. Capturing lambdas

To use:
```C++

int add_function(int a, int b)
{
	return a + b;
}

// the template paramters are in the "ReturnType(Args)" format
rtl::function<int(int,int)> addFunctor(add_function);

// Call via
addFunctor(1, 2);
addFunctor(x,y);

/// With lambdas

rtl::function<void(int, int)> printAddFunctor(
	[](int a, int b)
	{
		printf("%d + %d = %d\n", a, b, a+b);
	}
);

// Functions with no arguments

void enableTheThing()
{
	...
}


rtl::function<void()> enabler = enableTheThing;

```

### rtl::shared_ptr and rtl::unique_ptr

#### rtl::shared_ptr
A reference counted container for pointers

Create via `rtl::make_shared<type>(constructorArgs...);`

Access via overloaded `*` and `->` operators.

```
struct mystruct
{
	int x;
	int y;

	mystruct(int _x, int _y) : x(_x), y(_y) {}

};

rtl::shared_ptr<mystruct> temp = rtl::make_shared<mystruct>(1,2);

assert(temp->x == 1); // true
assert(temp->y == 2); // true

// increases ref count
rtl::shared_ptr<mystruct> temp2 = temp;

```

#### rtl::unique_ptr
A container for a single, unique pointer

Create via `rtl::make_unique<type>(constructorArgs...);`

Access via overloaded `*` and `->` operators.
```
struct mystruct
{
	int x;
	int y;

	mystruct(int _x, int _y) : x(_x), y(_y) {}

};

rtl::unique_ptr<mystruct> temp = rtl::make_unique<mystruct>(1,2);

assert(temp->x == 1); // true
assert(temp->y == 2); // true

// moves temp to temp2
rtl::unique_ptr<mystruct> temp2 = temp;

```