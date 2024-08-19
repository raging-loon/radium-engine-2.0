# Radium's Threading Library

Headers are found in `/core/thread`, implementations are found in `/platform/<platform>/thread/`

## Abstraction

There is a single object for each major threading component. Thes objects contain aliased types for each platform.

| Major Object | Type Name | Windows Alias | Linux Alias |
|--------------|-----------|---------------|-------------|
|   `thread`   | `ThreadObject` | `HANDLE` | `pthread_t` |
| `Mutex`	   | `MutexObject` | `HANDLE` | `pthread_mutex_t` |		
| `Semaphore`  | `Semaphore Object` | `HANDLE` | `sem_t` |

## Creating a New Thread

```c++

// creates a new thread. 
// This will create a new thread for myfunction with myArg1 and myArg2

radium::thread mythread(myfunction, myArg1, myArg2);

// wait for the thread to exit
mythread.join()

```

`radium::thread` can take any number/type of arguments so long as they match with the target functions prototpye

### Backend

This is a bit tricky and will hopefully be refactored in the future.

When you create a new thread, it will use a dummy thread runner. This will run a global capturing
lambda function that in turns runs `myfunction` with its arguments.

The extra overhead is 1 function call.

## Mutexes and Thread Safe classes/functions

A mutex is very simple to create.

```C++

radium::Mutex mymutex;

mymutex.create();

mymutex.lock()

// critical section code

mymutex.unlock()

```

### Thread Safe classes/functions

In `thread.h` you will find three macros:
1. `THREAD_SAFE_CLASS`
2. `THREAD_SAFE_FUNCTION`
3. `THREAD_SAFE_INIT`

Using these functions, you can create a thread safe class.
Any functions that could possibly corrupt data under a race condition should be marked with `THREAD_SAFE_FUNCTION`
Your class' constructor should contain `THREAD_SAFE_INIT`.

Example:
```C++
class MyClassThatContainsCriticalCode
{
	THREAD_SAFE_CLASS

public:
	MyClassThatContainsCriticalCode()
	{
		THREAD_SAFE_INIT
	}

	int longFunction()
	{
		... this function doesn't need to be thread safe...
		return 0;
	}

	int longFunctionThatModifiesSomething()
	{
		THREAD_SAFE_FUNCTION
		... modify something...
		return 0;
	}
};
```

#### Best Practices
1. Don't put `THREAD_SAFE_FUNCTION` in the constructor
2. Don't put `THREAD_SAFE_FUNCTION` anywhere such that it would be called recursively

#### Backend
There exists a clas called `radium::ScopedMutexLocker`

This will take your classes mutex, lock it during constructor, and unlock it during destruction 
(e.g. when the locker goes out of scope)

### Mutex Backend
This is a thin wrapper over the Operating System's Mutex API (i.e `CreateMutex`/`pthread_mutex_init`)