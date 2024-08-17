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

This implementation uses the Robin Hood hash collosion resolution method (that is a mouthful).

Here is a psuedocode implementation:
```python
def insert(self, object):
	index = hash(object) % m_size

```
