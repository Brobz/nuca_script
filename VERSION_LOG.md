## Version Log

### **Current Version:** 1.7.0

- ##### 19/06/2024

  - Version 1.7.0 officially released!
    - Major compilation pipeline changes!
      - Previously, the NucaScript would write the generated intermediate object code directly into `VM/main.cpp` after every compilation cycle in order to generate the final executable output.
      - Initially, this seemed (to me, at least) clever and efficient, however after some further consideration, several cons began showing up, such as constant gigantic git diffs in that file, and the inabillity to easily add more custom NucaScript CLI commands that have to do with the intermediate object code.
      - This version bump begins the shift towards having the IOC be written into a different file and imported into the VM. After the exectuable is generated, the IOC file is deleted. It is not final, but prepares for a futher overhaul! (stay tuned)
      - As of now, the IOC is still written directly into C++ code (just not into `main.cpp`), but the plan is have it be written as text and parsed accordingly by the VM.
      - A new CLI argument has been added: `--keep-object`
      - When used, NucaScript does not delete intermediate object file after the VM generates its executable output (current default behavior)
      - More CLI arguments (and a whole CLI overhaul) are also planned for the future! (stay tuned)
    - Major Bug fix!
      - Fixed a very relevant (but hard to find) bug that has probably been plaguing NucaScript since its conception.
      - The bug consisted of an extra (unwanted) `IP` (_Instruction Pointer_) increment during OP 13 (the `!` (_not_) operator) in the VM execution cycle.
      - This meant the VM would always skip whatever OP came next in the QUAD list after every single `!` (_not_) operation. Ouch!
      - Lucky I caught it! (found by trying to print a `!bool` directly and never getting any output to the console). Talk about "findng a needle in a haystack"!
    - VM Code cleanup!
      - Added a new `Utils.cpp` file, cleaned up a lot of `main.cpp` code
      - In `Value.cpp`, added an ENUM for the `type` attribute (was previously an int, and had lots of comments thrown around)
      - Same (ENUM) thing for `OPCodes` in `main.cpp`
    - General Cleanups & Refactors!
      - A bunch of stale variable name refactoring
      - Some other small cleanups (unreferenced variables when popping stacks, comment & in-file documentation errors)
      - Updated README NucaScript Synopsis!
    - New Sprint TODO ideas!
      - It's getting busy, I am excited for NucaScript's future!
      - Stay tuned : )

- ##### 24/05/2024

  - Version 1.6.4 officially released!
    - Refactors a good chunk of the Compiler code, especially from `FunctionDirectory`
      - Previously passed arrays and a crazy amount of parameters everywhere
      - Was confusing, constantly required multiple comments to explain what each parameter or array index meant
      - Replaced all that with a new `Function` object, with neatly defined attributes that should avoid further confusion
      - Cleaned up a bunch of variable, parameter and method names pertaining to function-related operations
      - As promised in the previous bump notes : )
    - Some other tiny comment & variable naming cleanups all around

- ##### 22/05/2024

  - Version 1.6.3 officially released!
    - Refactors a good chunk of the `SymbolTable` code
      - Previously passed arrays and a crazy amount of parameters everywhere
      - Was confusing, constantly required multiple comments to explain what each parameter or array index meant
      - Replaced all that with a new `Symbol` object, with neatly defined attributes that should avoid further confusion
      - Cleaned up a bunch of variable, parameter and method names pertaining to symbol-related operations
    - Adds new top-priority Sprint TODO for doing the same with `FunctionDirectory` code

- ##### 19/05/2024

  - Version 1.6.2 officially released!
    - Multi-line comments are back (hurray!)
    - Cleaned up some comments
    - Cleaned up some of the NucaScript 101 docs & Example code

- ##### 19/05/2024

  - Version 1.6.1 officially released!
    - Small `ExceptionHandler` message changes
    - Cleaned up some of the NucaScript 101 docs & Example code

- ##### 18/05/2024

  - Version 1.6.0 officially released!
    - Refactors most of the Compiler code
      - `nuca_script.py` had over 2.2k lines of code, which are now spread over multiple different files under the Compiler package
        - `Grammar.py` -> Contains all of the Formal Grammar rules and PLY functions that define NucaScript
        - `Utils.py` -> Contains useful methods that are found all over compiler code
      - Added new classes to easily manage dependencies
        - `Bootsrapper` -> Initializes all of the necessary values for building the lexer & parser
        - `Globals` -> An abstract class that contains global values to be used between multiple files
      - Improved python code import structure
        - Removed (almost) all of the `import *` statements, replacing them with newer python3 module import syntaxis
      - Small `ExceptionHandler` message changes & typo fixes
    - Some variable naming refactoring in VM code

- ##### 15/05/2024

  - Version 1.5.1 officially released!
    - Small compile time Exception bug fixes
      - Mentioning a method identifier (that was previously declared) without a set of () now raises the correct exception at compile time.
      - TODO: Still need to fix this for VOID type methods, since those do not currently have any reference in the SymbolTable at all.
    - Small README changes & typo fixes
    - New Sprint TODO ideas!

- ##### 02/01/2022

  - Version 1.5.0 officially released!
    - Revamps exception system and refactors most of the symbol & type lookup logic
      - Adds a brand new `ExceptionHandler` object, which takes care of relaying useful error messages on exceptions
        - _**Hurray**_ for line numbers on error messages!!
        - Program now exits gracefully on exceptions with a neat message followed by python's `exit()`, which looks cleaner on the console in comparison to the old `raise Exception()` jargon
      - Refactors lookup logic inside of `FunctionDirectory` in order to completely remove all `try / except` logic
        - Replaced it with `return` values and `if` statements, which got rid of about 80% of the indentation levels in each section
    - Small changes to how `#DEF` statements work with booleans
      - Previously coded them as an integer (either 0 or 1), now actually writes them down as `True` or `False`, which will ensure the correct type check when using its value in the code

- ##### 01/01/2022

  - **Happy New Year!!!**
  - Version 1.4.0 officially released!
    - Adds C-like `#DEF` statements for all basic data types!
      - Just like in C, these work by replacing the actual source code text with whatever value the definition name is coupled with
      - Currently, this **WILL** replace **ALL** instances of the definition name on the source code, **INCLUDING** those that are inside a string (within quotations)
        - P.S. & TODO: This behavior will be patched as soon as I figure out a _lazy_ way to get rid of it : )

- ##### 17/11/2021

  - Version 1.3.0 officially released!

    - Bug Fixes
      - Fixes a compile time bug that allowed for typed methods to be accepted even when their return method was contained inside an impossible conditional
        - This would cause all sorts of memory leaks on runtime, even though the program would compile with no error!
        - Typed methods now require not only that the last instruction of the method is a return statement with the correct type, but also that it is contained within the topmost conditional depth of the method's scope
        - P.S.: _else_ statements don't count as a conditional, so feel free to write return statements under those! (if you love yourself some redundancy :P )

- ##### 07/07/2021

  - Version 1.2.0 officially released!

    - Bug Fixes
      - Fixes major structural bug that threw compiler errors upon declaring global variables after a global method
      - Fixes type checking bug when using the result value of a class method on an arithmetical expression
    - New Ideas
      - Came up with new architectural ideas for object constructors; Stay tuned for future updates!

- ##### 04/06/2021

  - Version 1.1.0 officially released!

    - Bug fixes
      - Fixes compile time bugs caused by referencing class attributes inside of a method from a different class
      - Fixes bugs related to naming variables "t" + a numerical value, which conflicted with temporal names
      - Temporal names now start with a numerical value, which is not allowed for other IDS, resolving the conflict
    - Major changes to the _object_ type variables
      - Object variables must now specify their class type upon declaration, and cannot change afterwards
      - Object variables are now automatically instantiated upon entering their scope block (including object arrays)
      - Direct assignment to object variables is now disallowed, except for instantiations with the _new_ keyword.
      - _using as_ keyword removed!
      - Documentation updated to reflect these changes

- ##### 02/06/2021
  - Version 1.0.0 officially released!
